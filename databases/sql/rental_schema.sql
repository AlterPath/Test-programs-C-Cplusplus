
DROP DATABASE airbnb_db_2;
DROP TABLE Reservations, Reviews, Rooms, Users;
CREATE DATABASE airbnb_db_2;
USE airbnb_db;


CREATE TABLE Users (
    user_id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(255) UNIQUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Rooms (
    room_id INT AUTO_INCREMENT PRIMARY KEY,
    host_id INT,
    title VARCHAR(255),
    description TEXT,
    price_per_night DECIMAL(10,2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (host_id) REFERENCES Users(user_id)
);

CREATE TABLE Reservations (
    reservation_id INT AUTO_INCREMENT PRIMARY KEY,
    room_id INT,
    guest_id INT,
    start_date DATE,
    end_date DATE,
    total_price DECIMAL(10,2),
    status VARCHAR(50) DEFAULT 'confirmed',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (room_id) REFERENCES Rooms(room_id),
    FOREIGN KEY (guest_id) REFERENCES Users(user_id)
);

CREATE TABLE Reviews (
    review_id INT AUTO_INCREMENT PRIMARY KEY,
    reservation_id INT,
    rating INT CHECK (rating >= 1 AND rating <= 5),
    comment TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (reservation_id) REFERENCES Reservations(reservation_id)
);


INSERT INTO Users (name, email) VALUES 
('Иван Петров', 'ivan@example.com'),
('Мария Сидорова', 'maria@example.com'),
('Алексей Козлов', 'alex@example.com');

INSERT INTO Rooms (host_id, title, price_per_night) VALUES 
(1, 'Уютная студия', 2500),
(2, 'Апартаменты', 4500),
(1, 'Комната', 1800);

INSERT INTO Reservations (room_id, guest_id, start_date, end_date) VALUES 
(1, 2, '2022-03-21', '2022-03-25'),
(2, 3, '2022-03-22', '2022-03-26'),
(3, 2, '2022-04-01', '2022-04-05'),
(1, 3, '2022-02-15', '2022-02-20');