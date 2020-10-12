import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# API_KEY value: pk_24e22e4311254a7fb2b8a1c7e96ae5a2



""" DISCLAIMER:
KOD JEST BARDZO NIEOPTYMALNY I NIE DO KOŃCA POPRAWNY, ALE NAUCZYŁEŚ SIĘ I TAK CAŁEJ LOGIKI
WIESZ JUŻ JAK TO ZROBIĆ 100% POPRAWNIE, ALE NIE CHCESZ POŚWIĘCAĆ CZASU NA ZMIANY
WSZYSTKO ZALEŻAŁO OD DOBREGO ZAPROJEKTOWANIA TABEL
MASZ ŁADNIE TO POKAZANE W FILMIKACH:
https://www.youtube.com/watch?v=pm1eYkpzn-0
https://www.youtube.com/watch?v=G93FzYTlGp8
"""


@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    """Show history of transactions"""

    if request.method == "GET":

        transactions = db.execute("SELECT * FROM transactions JOIN stocks ON transactions.stock_id = stocks.id WHERE user_id=?;", session["user_id"])

        return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Inform user about successful login
        flash("Successful login!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""


    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("register.html")

    # Via POST (eg. by submitting something)
    else:

        row = db.execute("SELECT username FROM users WHERE username=?;", request.form.get("username"))

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was confirmed
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 403)

        # Check if username is in the database
        elif row:
            return apology("username already taken")

        # Ensure passwords match each other
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords do not match", 403)

        # Insert the user into the finance database (users TABLE)
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashUsed)",
                    username=request.form.get("username"),
                    hashUsed=generate_password_hash(request.form.get("password")))

        return redirect("/login")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    else:
        # Declare quote as a dictionary
        quote = lookup(request.form.get("symbol"))

        # Check if symbol is valid (i.e. if lookup did or did not return None)
        if quote == None: # alternative: "if not quote:"
            return apology("invalid symbol", 400)
        else:
            # Display quote
            name = quote['name']
            symbol = quote['symbol']
            price = quote['price']
            return render_template("quoted.html",
                                    name=name,
                                    symbol=symbol,
                                    price=price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # DISCLAIMER: dałoby się to zrobić samym typem danym w SQL ! (timestamp)

    # Get current time and date
    time = datetime.datetime.now()

    # Write it in correct format
    transactionTime = time.strftime("%Y-%m-%d %H:%M:%S")

    if request.method == "GET":
        return render_template("buy.html")

    # via POST method
    else:

        # Get number of shares that user wants to buy
        shares = request.form.get("shares") # Just for making code more readable

        # Check if symbol is valid or input is blank
        if lookup(request.form.get("symbol")) == None: # lookup returns None if symbol is not valid
            return apology("invalid symbol", 400)

        # Check if number of shares is a positive integer
        elif shares.isnumeric() == False or shares == '0':
            return apology("number of shares must be a positive integer", 400)


        #   tutaj już jest błąd, którego nie chce się tobie naprawiać (złe zaprojektowanie tabeli)
        # - po prostu musisz wpisywać wszystko w jednej tabeli transactions, gdzie

        # Get the symbol
        symbol = lookup(request.form.get("symbol"))['symbol']

        # Get name of the company
        companyName = lookup(request.form.get("symbol"))['name']

        # Get price of one share
        price = lookup(request.form.get("symbol"))['price']

        # Check if company is already in the database (by if statement below)
        row = db.execute("SELECT * FROM stocks WHERE symbol = ?", symbol) # row is saved as a dictionary

        # If it's not in the database (i.e. the list is empty)
        if len(row) == 0:
            # Add stock data of given company
            db.execute("INSERT INTO stocks (companyName, symbol, price) VALUES (?, ?, ?)", companyName, symbol, price )

        # Get stock id
        stock_id = db.execute("SELECT id FROM stocks WHERE symbol=?", symbol) # it is returned as a one element dict

        # Convert shares from string to a float
        sharesNum = float(shares)

        # Calculate total price of given stock
        totalPrice = price * sharesNum

        # Get current user's data from the database
        user = db.execute("SELECT * FROM users WHERE id=?;", session["user_id"])

        # Get amount of user's cash after purchasing the stock
        moneyLeft = user[0]['cash'] - totalPrice

        if moneyLeft < 0:
            return apology("can't afford", 400)

        else:
            # Purchase the stock
            db.execute("INSERT INTO transactions (shares, user_id, stock_id, time) VALUES (?, ?, ?, ?);", int(sharesNum), session["user_id"], stock_id[0]['id'], transactionTime)

            # Update user's total cash
            db.execute("UPDATE users SET cash=? WHERE id=?;", moneyLeft, session["user_id"])

            flash("Bought!")

            return redirect("/")


# Lists that hold current info about user's stock (you have to reset them in each function if want to use them)
totalShares = [] # summed up shares of one stock         # (arrayindex+1) = id in stocks TABLE
totalValue = [] # total value of stock shares

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Reset global lists
    totalShares.clear()
    totalValue.clear()

    stocks = db.execute("SELECT * FROM stocks;") # price, name, symbol

    for i in range(len(stocks)):

        # Select transactions of the same stock
        rows = db.execute("SELECT shares FROM transactions WHERE user_id=? AND stock_id=?;", session["user_id"], i+1)

        shares = 0

        for row in rows:

            # Add up all shares with the same stock_id
            shares = shares + row['shares']

        totalShares.append(shares)

    for i in range(len(stocks)):
        # Count total value of user's given stock holdings
        value = format(totalShares[i] * stocks[i]['price'], ".2f")
        totalValue.append(value)

    # Get user's cash
    row = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

    # Add up all total stock holdings
    total = 0
    for i in range(0, len(stocks)):
        total = float(total) + float(totalValue[i])

    # Count user's total money
    totalMoney = format(row[0]['cash'] + float(total), ".2f")

    cash = format(row[0]['cash'], ".2f")

    # Change zeroes to Nones (to perform if statement logic in index.html)
    for i in range(len(stocks)):

        if totalShares[i] == 0:
            totalShares[i] = None

    # Adjust value type for totalMoney to be displayed properly
    money = float(totalMoney)

    return render_template("index.html", stocks=stocks, totalShares=totalShares, totalValue=totalValue,
                                        cash=cash, totalMoney=usd(money))


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Restart totalValue (totalShares will be just updated)
    totalValue.clear()

    # Get current time and date
    time = datetime.datetime.now()

    # Write it in correct format
    transactionTime = time.strftime("%Y-%m-%d %H:%M:%S")

    if request.method == "GET":

        # Select dictionary of symbols of companies' stock that user has purchased
        rows = db.execute("SELECT symbol FROM stocks;")

        # Save symbols as a list
        symbols = []

        # If there are any shares add element to the list of symbols
        for i in range(len(rows)):

            # If the user owns given stock add it to the list
            if totalShares[i]: # totalShares index goes with stocks TABLE

                symbols.append(rows[i]['symbol'])

        return render_template("sell.html", symbols=symbols)


    else:

        chosenSymbol = request.form.get("symbol")

        if chosenSymbol == None:
            return apology("Choose symbol")

        # Get number of shares that user wants to buy
        shares = request.form.get("shares")

        # Check if number of shares is a positive integer
        if shares.isnumeric() == False or shares == '0':
            return apology("number of shares must be a positive integer", 400)

        # Convert string to integer
        shares = int(shares)

        # Tutaj masz logikę dzieki temu że index listy totalShares współgra +1 ze stocks TABLE)
        stockID = db.execute("SELECT id FROM stocks WHERE symbol=?;", chosenSymbol)

        # Get the right totalShares index
        totalSharesIndex = stockID[0]['id'] - 1

        if shares > totalShares[totalSharesIndex]:
            return apology("too many shares")

        # Substract given shares from total amount (i.e. update it)
        totalShares[totalSharesIndex] = totalShares[totalSharesIndex] - shares


        # Write the sale to the database
        db.execute("INSERT INTO transactions (shares, user_id, stock_id, time) VALUES (?, ?, ?, ?);", -shares, session["user_id"], stockID[0]['id'], transactionTime)

        cashBeforeSale = db.execute("SELECT cash FROM users WHERE id=?;", session["user_id"])

        price = db.execute("SELECT price FROM stocks WHERE symbol=?;", chosenSymbol)

        cashAfterSale = cashBeforeSale[0]['cash'] + (shares*price[0]['price'])

        # Update user's total cash
        db.execute("UPDATE users SET cash=? WHERE id=?;", cashAfterSale, session["user_id"])


        stocks = db.execute("SELECT * FROM stocks;")

        # Count total value of user's given stock holdings
        for i in range(len(stocks)):

            # Consider the case when element of a list is None (then append zero)
            if totalShares[i] == None:

                totalValue.append(0)

            else:
                # Count total value of user's given stock holdings
                value = float(format(totalShares[i] * stocks[i]['price'], ".2f"))
                totalValue.append(value)

        # Add up all total stock holdings
        total = 0
        for i in range(0, len(stocks)):
            total = total + totalValue[i]

        # Count user's total money
        totalMoney = format(cashAfterSale + float(total), ".2f")

        # Set floating precision
        cash = format(cashAfterSale, ".2f")

        # Change zeroes to Nones (to perform if statement logic in index.html)
        for i in range(len(stocks)):

            if totalShares[i] == 0:
                totalShares[i] = None

        flash("Sold!")

        # Render updated table
        return render_template("index.html", stocks=stocks, totalShares=totalShares, totalValue=totalValue,
                                        cash=cash, totalMoney=totalMoney)

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changePassword():

        if request.method == "POST":

            # Ensure current password was submitted
            if not request.form.get("current_password"):
                return apology("must provide current password", 403)

            # Ensure new password was submitted
            elif not request.form.get("new_password"):
                return apology("must provide new password", 403)

            # Ensure new password was conirmed
            elif not request.form.get("confirm_password"):
                return apology("must confirm new password", 403)

            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE id=?",
                              session["user_id"])

            # Ensure current password is correct
            if check_password_hash(rows[0]["hash"], request.form.get("current_password")) == False:
                return apology("invalid current password", 403)

                    # Ensure passwords match each other
            elif request.form.get("new_password") != request.form.get("confirm_password"):
                return apology("passwords do not match", 403)

            # Update user's password
            db.execute("UPDATE users SET hash = :newHash WHERE id = :ID", newHash=generate_password_hash(request.form.get("new_password")), ID=session["user_id"])

            flash("Password successfuly changed!")

            return redirect("/")

        else:

            return render_template("changepassword.html")

        return apology("TO DO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
