-- select iban, address
-- from account, filial
-- where account.filial_id = filial.filial_id;

select amount 
from  operation, account
where operation.source_account_id = account.account_id and account.balance < 6000;