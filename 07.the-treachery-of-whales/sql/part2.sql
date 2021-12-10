
SELECT LEAST(SUM(distance1 * (distance1 + 1) / 2), SUM(distance2 * (distance2 + 1) / 2))
    FROM (
        SELECT
            ABS((SELECT FLOOR(AVG(value)) FROM day7) - value) AS distance1,
            ABS((SELECT CEIL(AVG(value)) FROM day7) - value) AS distance2
            FROM day7
    ) AS distances;

