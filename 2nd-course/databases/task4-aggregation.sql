-- select count(distinct a.account_id)
-- from account a join operation o on a.account_id = o.source_account_id
-- where a.balance > 4000;

-- select count(distinct c.type)
-- from account a join client c on a.client_id = c.client_id
-- where a.balance < 
-- 	(select avg(balance) from account)

(select distinct filial_id from account where balance < 6000)
intersect
(select distinct filial_id from filial where type = 'універсальна')