-- titles of all movies in which both JP and HBC starred
SELECT DISTINCT title FROM movies
JOIN stars ON id = movie_id
WHERE id IN (SELECT movie_id FROM stars
WHERE person_id IN(SELECT id FROM people WHERE name = "Johnny Depp"))
INTERSECT
SELECT DISTINCT title FROM movies
JOIN stars ON id = movie_id
WHERE id IN (SELECT movie_id FROM stars
WHERE person_id IN(SELECT id FROM people WHERE name = "Helena Bonham Carter"));


