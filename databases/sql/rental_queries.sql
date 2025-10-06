SELECT Rooms.*
FROM Rooms
JOIN Reservations ON Rooms.room_id = Reservations.room_id
WHERE YEAR(Reservations.start_date) = 2022 AND WEEK(Reservations.start_date, 1) = 12;