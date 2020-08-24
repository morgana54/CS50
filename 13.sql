-- names of people who starred in movie in which Kevin Bacon also starred
-- only select the Kevin Bacon born in 1958
-- Kevin Bacon himself should not be included in the resulting list


-- nie zrobiłeś tego sam, ale i tak byś pewnie tego nie wykminił

SELECT DISTINCT name FROM people
WHERE id IN
(SELECT person_id FROM stars
WHERE movie_id IN
(SELECT movie_id FROM stars
WHERE person_id IN
(SELECT id FROM people
WHERE name = "Kevin Bacon" AND birth = 1958)))
AND name != "Kevin Bacon";