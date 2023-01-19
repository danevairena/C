-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT day, month, year, street, description
FROM crime_scene_reports
WHERE description LIKE '%duck%';
-- | 28  | 7     | 2021 | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

SELECT name, transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021
AND transcript LIKE '%bakery%';
-- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage
-- from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM
-- on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they
-- were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30;
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |

SELECT * FROM people
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30);
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw';
-- | 28500762       |
-- | 28296815       |
-- | 76054385       |
-- | 49610011       |
-- | 16153065       |
-- | 25506511       |
-- | 81061156       |
-- | 26013199       |

SELECT id, name, phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30);
-- | 686048 | Bruce | (367) 555-5533 |
-- | 514354 | Diana | (770) 555-1861 |
-- | 396669 | Iman  | (829) 555-5269 |
-- | 467400 | Luca  | (389) 555-5198 |

SELECT caller, receiver, duration FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021;
-- | (367) 555-5533 | (375) 555-8161 | 45       |
-- | (770) 555-1861 | (725) 555-3243 | 49       |

SELECT * FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021);
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021));
-- | 18        |
-- | 24        |
-- | 36        |
-- | 54        |

SELECT id, origin_airport_id, destination_airport_id FROM flights
WHERE day = 28 + 1 AND month = 7 AND year = 2021
AND id IN (SELECT flight_id FROM passengers
WHERE passport_number IN (SELECT passport_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021)))
ORDER BY hour ASC LIMIT 1;
-- | 36 | 8                 | 4                      |

SELECT passport_number FROM passengers
WHERE flight_id = 36
AND passport_number IN (SELECT passport_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021));
-- | 5773159633      |

SELECT name, phone_number FROM people
WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id = 36
AND passport_number IN (SELECT passport_number FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021)));
-- | Bruce | (367) 555-5533 |

SELECT caller, receiver, duration FROM phone_calls
WHERE caller IN (SELECT phone_number FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN (SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND atm_location LIKE 'Leggett%' AND transaction_type = 'withdraw')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2021
AND activity = 'exit' AND hour = 10 AND minute > 15 AND minute < 30))
AND duration < 60 AND day = 28 AND month = 7 AND year = 2021
AND caller = '(367) 555-5533';
-- | (367) 555-5533 | (375) 555-8161 | 45       |

SELECT name FROM people
WHERE phone_number = '(375) 555-8161';
-- | Robin |

SELECT city FROM airports
WHERE id = 4;
-- | New York City |