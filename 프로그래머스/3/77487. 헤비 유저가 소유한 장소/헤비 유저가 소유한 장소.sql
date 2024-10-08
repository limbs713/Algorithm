-- 코드를 입력하세요
SELECT PLACES.ID, PLACES.NAME, PLACES.HOST_ID
FROM PLACES RIGHT JOIN  (
    SELECT *
    FROM PLACES
    GROUP BY HOST_ID
    HAVING COUNT(*) >= 2
)AS T USING (HOST_ID)
ORDER BY PLACES.ID