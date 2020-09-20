// Replaces normal image with funny one
// document.getElementById("BogdanImage").addEventListener("click", replaceImage);

function replaceImage_Pietrzi() {
            document.getElementById("PietrziImage").src = "kubd.jpg";
        }

function replaceImage_Bogdan() {
            document.getElementById("BogdanImage").src = "bogd.jpg";
        }

function replaceImage_Kacper() {
            document.getElementById("KacperImage").src = "kacpd.jpg";
        }

// POTEM ZASTANOWIĆ SIE CZY DA SIĘ ZOPTYMALIZOWAĆ KRÓCEJ TEN KOD (pamiętając
// o wczesniejszych nieudanych próbach z klasami, querySelectorem itp.)
// PYTANIE: jak nie wymyślisz to zapytaj Kacpra



function executeDropdownBogdan() {
    let x = document.getElementById("mySelect").selectedIndex;

    // let y = document.getElementsByClassName("image_position").src

	if (x === 1)
    {
        replaceImage_Bogdan();
    }
    else if (x === 2)
    {
        playVidB();
    }

}

function executeDropdownPietrzi() {
    let x = document.getElementById("mySelect").selectedIndex;

    // let y = document.getElementsByClassName("image_position").src

	if (x === 1)
    {
        // if (document.querySelector("img").src === "kubnor.jpg")
        // {
            replaceImage_Pietrzi();
        // }
        // else if (document.querySelector(".image_position").src === "bognor.jpg")
        // {
        //     replaceImage_Bogdan();
        // }
        // else if (document.querySelector(".image_position").src === "kacpnor.jpg")
        // {
        //     replaceImage_Kacper();
        // }
    }
    else if (x === 2)
    {
        // PYTANIE DO KACPRA: CZEMU TO DZIAŁA SKORO FUNKCJA JEST NA DOLE?
        playVidP();
    }
    else if (x === 3)
    {
        // TO DO
    }
}


function executeDropdownKacper() {
    let x = document.getElementById("mySelect").selectedIndex;

    // let y = document.getElementsByClassName("image_position").src

	if (x === 1)
    {
       replaceImage_Kacper();
    }
    else if (x === 2)
    {
        playVidK();
    }
}


// function hideVideo(){
//     document.getElementById("BogdanVideo").style.visibility = "hidden";
// }

// to też SPRÓBUJ ZOPTYMALIZOWAĆ!!!


let x = document.getElementById("BogdanVideo");
let y = document.getElementById("PietrziVideo");
let z = document.getElementById("KacperVideo");

// Bogdan
function playVidB() {
    x.play();
}

// function pauseVidB() {
//     x.pause();
// }

// Pietrzi
function playVidP() {
    y.play();
}

// function pauseVidP() {
//     y.pause();
// }

// Kacper
function playVidK() {
    z.play();
}

// function pauseVidK() {
//     z.pause();
// }
