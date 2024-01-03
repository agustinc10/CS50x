-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description
  FROM crime_scene_reports
 WHERE year = 2021 AND month = 7 AND day = 28
   AND street = 'Humphrey Street';

-- Find transcripts of interviews
SELECT name, transcript
  FROM interviews
 WHERE year = 2021 AND month = 7 AND day = 28
   AND transcript LIKE '%bakery%';

-- Find possible plate of the car and name
SELECT hour, minute, activity, b.license_plate, p.name
  FROM bakery_security_logs AS b
       JOIN people AS p ON p.license_plate = b.license_plate
 WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10
   AND minute between 0 and 25;

-- Find ATM activity
SELECT a.transaction_type, a.amount, p.name
  FROM atm_transactions AS a
       JOIN bank_accounts AS b ON b.account_number = a.account_number
       JOIN people AS p ON p.id = b.person_id
 WHERE a.year = 2021 AND a.month = 7 AND a.day = 28
   AND a.atm_location LIKE '%Leggett Street%';

-- Find caller and receiver of phone call
SELECT ph.duration, p1.name, p2.name
  FROM phone_calls AS ph
       JOIN people AS p1 ON p1.phone_number = ph.caller
       JOIN people AS p2 ON p2.phone_number = ph.receiver
 WHERE year = 2021 AND month = 7 AND day = 28
   AND duration <= 60;

-- Find Flight and passengers
SELECT f.hour, f.minute, p.name, a2.city
  FROM people AS p
       JOIN passengers AS pas ON pas.passport_number = p.passport_number
       JOIN flights as f ON f.id = pas.flight_id
       JOIN airports as a1 ON a1.id = f.origin_airport_id
       JOIN airports as a2 ON a2.id = f.destination_airport_id

 WHERE f.year = 2021 AND f.month = 7 AND f.day = 29
   AND a1.city = 'Fiftyville'
   AND p.name IN ('Bruce', 'Diana', 'Robin', 'Philip')
 ORDER BY f.hour, f.minute;

/*
| hour | minute | activity | license_plate |  name   |
+------+--------+----------+---------------+---------+
| 10   | 8      | entrance | R3G7486       | Brandon |
| 10   | 14     | entrance | 13FNH73       | Sophia  |
| 10   | 16     | exit     | 5P2BI95       | Vanessa |
| 10   | 18     | exit     | 94KL13X       | Bruce   |--
| 10   | 18     | exit     | 6P58WS2       | Barry   |
| 10   | 19     | exit     | 4328GD8       | Luca    |--
| 10   | 20     | exit     | G412CB7       | Sofia   |
| 10   | 21     | exit     | L93JTIZ       | Iman    |--
| 10   | 23     | exit     | 322W7JE       | Diana   |--
| 10   | 23     | exit     | 0NTHK55       | Kelsey  |


| transaction_type | amount |  name   |
+------------------+--------+---------+
| withdraw         | 50     | Bruce   |--
| deposit          | 10     | Kaelyn  |
| withdraw         | 35     | Diana   |--
| withdraw         | 80     | Brooke  |
| withdraw         | 20     | Kenny   |
| withdraw         | 20     | Iman    |--
| withdraw         | 48     | Luca    |--
| withdraw         | 60     | Taylor  |
| withdraw         | 30     | Benista |

+----------+---------+------------+
| duration |  name   |    name    |
+----------+---------+------------+
| 51       | Sofia   | Jack       |
| 36       | Kelsey  | Larry      |
| 45       | Bruce   | Robin      |--
| 60       | Kathryn | Luca       |
| 50       | Kelsey  | Melissa    |
| 43       | Taylor  | James      |
| 49       | Diana   | Philip     |--
| 38       | Carina  | Jacqueline |
| 55       | Kenny   | Doris      |
| 54       | Benista | Anna       |
+----------+---------+------------+
