-- 코드를 입력하세요
SELECT COUNT(USER_ID) AS USERS
FROM USER_INFO
WHERE AGE >= 20 AND AGE <= 29 AND JOINED >= '2021-01-01' AND JOINED < '2022-01-01'