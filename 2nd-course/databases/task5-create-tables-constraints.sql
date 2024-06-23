DROP TABLE IF EXISTS Operation;
DROP TABLE IF EXISTS Account;
DROP TABLE IF EXISTS Client;
DROP TABLE IF EXISTS Filial;

CREATE TABLE Filial(
	filial_id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL UNIQUE,
    address VARCHAR(255),
    contact_info VARCHAR(255),
    type VARCHAR(255) CONSTRAINT valid_type CHECK (type IN ('каса', 'універсальна', 'VIP'))
);

INSERT INTO Filial(name, address, contact_info, type) VALUES
	('Філія 1', 'вул. Перша, 1', 'тел. 123-456', 'каса'),
	('Філія 2', 'вул. Друга, 2', 'тел. 789-012', 'універсальна'),
	('Філія 3', 'вул. Третя, 3', 'тел. 345-678', 'VIP'),
    ('Філія 4',	'вул. Перша, 12', 'тел. 124-456', 'каса'),
    ('Філія 5',	'вул. Друга, 23', 'тел. 787-012', 'універсальна'),
    ('Філія 6',	'вул. Третя, 34', 'тел. 349-678', 'VIP');

Select * from Filial;


CREATE TABLE Client(
	client_id SERIAL PRIMARY KEY,
    tax_code VARCHAR(255),
    name VARCHAR(255) NOT NULL,
    contact_address VARCHAR(255),
    contact_phone VARCHAR(20),
    contact_email VARCHAR(255),
    type VARCHAR(255) CONSTRAINT valid_type CHECK (type IN ('фізична', 'юридична'))
);

INSERT INTO Client(tax_code, name, contact_address, contact_phone, contact_email, type) VALUES
	('1234567890', 'ТОВ "Клієнт1"', 'вул. Клієнта, 10', 'тел. 111-222', 'client1@example.com', 'юридична'),
	('0987654321', 'Іван Іванов', 'вул. Іванова, 20', 'тел. 333-444', 'ivan@example.com', 'фізична'),
    ('4567893450', 'ТОВ "Клієнт3"', 'вул. Клієнта, 14', 'тел. 123-222', 'client3@example.com', 'юридична'),
    ('4567893450', 'ТОВ "Клієнт4"', 'вул. Клієнта, 15', 'тел. 123-222', 'client4@example.com', 'юридична'),
    ('5234567490', 'ТОВ "Клієнт5"', 'вул. Клієнта, 16', 'тел. 331-222', 'client5@example.com', 'юридична'),
    ('0987654321', 'Іван Іваненко', 'вул. Іванова, 24', 'тел. 453-444', 'ivanov@example.com', 'фізична'),
    ('0507654321', 'Роман Іванов', 'вул. Іванова, 26', 'тел. 763-444', 'roman@example.com', 'фізична');

Select * from Client;


CREATE TABLE Account(
	account_id SERIAL PRIMARY KEY,
    iban VARCHAR(34) UNIQUE,
    opening_date VARCHAR(255),
    balance DECIMAL(10, 2) CONSTRAINT positive_balance NOT NULL CHECK (balance >= 0),
    client_id INT NOT NULL,
    filial_id INT NOT NULL,
    FOREIGN KEY (client_id) REFERENCES Client(client_id),
    FOREIGN KEY (filial_id) REFERENCES Filial(filial_id)
);

INSERT INTO Account(iban, opening_date, balance, client_id, filial_id) VALUES
	('UA123456789012345678', '2023-01-01', 10000.00, 1, 1),
	('UA987654321098765432', '2023-01-01', 5000.00, 1, 2),
	('UA135792468013579246', '2023-01-01', 2000.00, 2, 3),
    ('UA345456789017345678', '2023-02-01', 9000.00, 6, 4),
    ('UA471654321098965432', '2023-02-02', 6000.00, 7, 5),
    ('UA075792468013579246', '2023-01-03', 3000.00, 3, 6);

Select * from Account;


CREATE TABLE Operation(
	operation_id SERIAL PRIMARY KEY,
    source_account_id INT NOT NULL,
    destination_account_id INT NOT NULL,
    amount DECIMAL(10, 2) CONSTRAINT positive_amount NOT NULL CHECK (amount > 0),
    document_number VARCHAR(255) UNIQUE,
    operation_date VARCHAR(255),
    purpose TEXT,
    FOREIGN KEY (source_account_id) REFERENCES Account(account_id),
    FOREIGN KEY (destination_account_id) REFERENCES Account(account_id)
);

INSERT INTO Operation(source_account_id, destination_account_id, amount, document_number, operation_date, purpose) VALUES 
	(1, 3, 500.00, 'DOC123', '2023-01-02 10:00:00', 'Переказ коштів'),
	(2, 3, 1000.00, 'DOC456', '2023-01-03 11:00:00', 'Переказ коштів'),
    (4, 3, 500.00, 'DOC143', '2023-01-02 10:00:00', 'Переказ коштів'),
    (2, 5, 1000.00, 'DOC256', '2023-01-03 12:00:00', 'Оплата податків'),
    (3, 1, 500.00, 'DOC023', '2023-01-02 10:00:00', 'Переказ коштів'),
    (2, 4, 1000.00, 'DOC856', '2023-01-03 12:00:00', 'Купівля');

Select * from Operation;