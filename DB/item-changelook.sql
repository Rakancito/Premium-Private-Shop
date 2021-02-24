ALTER TABLE `item`
ADD COLUMN `price`  int(32) NOT NULL DEFAULT 0 AFTER `transmutation`,
ADD COLUMN `shop_id`  int(32) NOT NULL DEFAULT 0 AFTER `price`;
