-- select iban, address
-- from account, filial
-- where account.filial_id = filial.filial_id;

-- select amount 
-- from  operation, account
-- where operation.source_account_id = account.account_id and account.balance < 6000;

-- select count(distinct a.account_id)
-- from account a join operation o on a.account_id = o.source_account_id
-- where a.balance > 4000;

-- select count(distinct c.type)
-- from account a join client c on a.client_id = c.client_id
-- where a.balance < 
-- 	(select avg(balance) from account)

-- (select distinct filial_id from account where balance < 6000)
-- intersect
-- (select distinct filial_id from filial where type = 'універсальна')

-- для клієнта по імені все

-- select client.name, account_id, iban, balance, filial.name
-- from client, account, filial
-- where client.client_id = account.client_id and account.filial_id = filial.filial_id 
-- and client.name = 'ТОВ "Клієнт1"';


-- клієнти, які мали загальну суму операцій менше ніж 1000

select c.client_id, c.name, sum(operation.amount)
from client c join account a on c.client_id = a.client_id 
	join operation on a.account_id = operation.source_account_id
group by c.client_id, c.name
having sum(operation.amount) < 1000
