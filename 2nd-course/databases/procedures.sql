-- CREATE OR REPLACE PROCEDURE add_client(
--     p_tax_code TEXT,
-- 	p_name TEXT,
-- 	p_contact_address TEXT,
-- 	p_contact_phone TEXT,
-- 	p_contact_email TEXT,
--     p_type TEXT
-- )
-- AS $$
-- BEGIN
--     INSERT INTO client(tax_code, name, contact_address, contact_phone, contact_email, type) 
-- 	VALUES (p_tax_code, p_name, p_contact_address, p_contact_phone, p_contact_email, p_type);
-- END;
-- $$ LANGUAGE plpgsql;

-- CALL add_client('1234567890', 'ТОВ "Клієнт8"', 'вул. Клієнта, 18', 'тел. 555-222', 'client8@example.com', 'юридична');

-- select * from client;

-- DROP FUNCTION calculate_total_balance(integer);

-- CREATE OR REPLACE FUNCTION calculate_total_balance(p_client_id INT)
-- RETURNS NUMERIC
-- AS $$
-- DECLARE
--     total_balance NUMERIC := 0;
-- BEGIN
--     SELECT SUM(balance) INTO total_balance FROM account WHERE client_id = p_client_id;
--     RETURN total_balance;
-- END;
-- $$ LANGUAGE plpgsql;

-- SELECT calculate_total_balance(2);


-- CREATE OR REPLACE PROCEDURE add_account(
--     p_iban TEXT,
--     p_opening_date TEXT,
--     p_balance NUMERIC,
--     p_client_id INT,
--     p_filial_id INT
-- )
-- AS $$
-- BEGIN
--     INSERT INTO account(iban, opening_date, balance, client_id, filial_id) 
-- 	VALUES (p_iban, p_opening_date, p_balance, p_client_id, p_filial_id);
-- END;
-- $$ LANGUAGE plpgsql;

-- call add_account('UA123456789012345689', '2023-01-01', 4000.00, 1, 1);

-- select * from account;