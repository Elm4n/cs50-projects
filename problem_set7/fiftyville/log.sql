-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT *FROM crime_scene_reports WHERE street = "Humphrey Street";
 -- bakery witnesses
SELECT *FROM interviews WHERE transcript LIKE '%bakery%';
 -- clues from Eugene
SELECT account_number, amount
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location ='Leggett Street'
   AND transaction_type = 'withdraw';
-- find names associated with the corresponding account number
SELECT name, atm_transactions.amount
  FROM people
  JOIN bank_accounts
  ON people.id = bank_accounts.person_id
  JOIN atm_transactions
  ON bank_accounts.account_number = atm_transactions.account_number
 WHERE  atm_transactions.year = 2021
   AND atm_transactions.month = 7
   AND atm_transactions.day = 28
   AND atm_transactions.atm_location ='Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';
-- Clues from Raymond
SELECT abbreviation, full_name, city FROM airports WHERE city = 'Fiftyville';
--flights the next day of theft
SELECT abbreviation, full_name, city, flights.hour, flights.minute
  FROM airports
  JOIN flights
    ON airports.id = flights.destination_airport_id
WHERE flights.origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
 AND flights.year = 2021
 AND flights.month = 7
 AND flights.day = 28
ORDER BY flights.hour, flights.minute;
--checking the list of passengers on that flight
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
    WHERE  flights.year = 2021
    AND flights.month = 7
    AND flights.day = 28
    AND flights.hour = 8
    AND flights.minute = 20
    ORDER BY passengers.passport_number;
    -- checking the phone call records
SELECT name, phone_calls.duration
   FROM people
   JOIN phone_calls
     ON people.phone_number = phone_calls.caller
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration <= 60
    ORDER BY phone_calls.duration;
    -- checking call receivers
SELECT name, phone_calls.duration
   FROM people
   JOIN phone_calls
     ON people.phone_number = phone_calls.receiver
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration <= 60
    ORDER BY phone_calls.duration;
    -- clues by ruth
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute
   FROM people
   JOIN bakery_security_logs
     ON people.license_plate = bakery_security_logs.license_plate
  WHERE bakery_security_logs.year = 2021
  AND bakery_security_logs.month = 7
  AND bakery_security_logs.day = 28
  AND bakery_security_logs.activity = 'exit'
  AND bakery_security_logs.hour = 10
  AND bakery_security_logs.minute >= 15
  AND bakery_security_logs.minute <= 25
ORDER BY bakery_security_logs.minute;

