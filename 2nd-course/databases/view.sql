-- CREATE VIEW client_accounts AS
-- SELECT 
--     c.client_id AS client_id,
--     c.name AS client_name,
--     c.tax_code,
--     r.account_id AS account_id,
--     r.iban,
--     r.balance
-- FROM 
--     client c
-- JOIN 
--     account r ON c.client_id = r.client_id;

-- select * from client_accounts;


-- CREATE VIEW account_operations AS
-- SELECT 
--     op.operation_id AS operation_id,
--     op.source_account_id,
--     op.amount,
--     op.operation_date,
--     op.purpose,
--     a.iban AS source_account_iban
-- FROM 
--     operation op
-- JOIN 
--     account a ON op.source_account_id = a.account_id;

-- select * from account_operations;