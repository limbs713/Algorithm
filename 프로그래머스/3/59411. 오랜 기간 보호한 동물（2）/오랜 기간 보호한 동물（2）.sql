-- 코드를 입력하세요
SELECT R.ANIMAL_ID , R.NAME
FROM ANIMAL_INS L JOIN ANIMAL_OUTS R USING (ANIMAL_ID)
ORDER BY DATEDIFF(R.DATETIME,L.DATETIME) DESC
LIMIT 2