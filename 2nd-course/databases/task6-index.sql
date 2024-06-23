CREATE INDEX idx_filial_id ON Filial USING btree (filial_id);
CREATE INDEX idx_client_id ON Client USING btree (client_id);
CREATE INDEX idx_account ON Account USING btree (account_id, balance);
CREATE INDEX idx_operation ON Operation USING btree (operation_id, amount);