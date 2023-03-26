SELECT
    DISTINCT people.name
FROM
    stars
    JOIN people ON stars.person_id = people.id
WHERE
    stars.movie_id IN (
        SELECT
            stars.movie_id
        FROM
            stars
            JOIN people ON people.id = stars.person_id
            AND people.name = 'Kevin Bacon'
            and people.birth = 1958
    )