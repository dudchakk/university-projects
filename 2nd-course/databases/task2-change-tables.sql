INSERT INTO Filial (name, address, contact_info, type) VALUES ('Філія 4', 'вул. Четверта, 4', 'тел. 456-789', 'універсальна');
-- select * from filial;

UPDATE Client SET contact_phone = 'тел. 555-666' WHERE client_id = 2;
-- select * from client;

delete from filial where name = 'Філія 4';
select * from filial;