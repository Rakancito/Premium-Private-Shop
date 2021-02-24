SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `player_shop`
-- ----------------------------
DROP TABLE IF EXISTS `player_shop`;
CREATE TABLE `player_shop` (
  `shop_id` int(32) NOT NULL AUTO_INCREMENT,
  `owner_id` int(32) NOT NULL DEFAULT '0',
  `owner_name` varchar(16) NOT NULL,
  `map_index` int(16) NOT NULL DEFAULT '0',
  `x` int(32) NOT NULL DEFAULT '0',
  `y` int(32) NOT NULL DEFAULT '0',
  `z` int(32) NOT NULL DEFAULT '0',
  `date_close` varchar(40) NOT NULL DEFAULT '0',
  `race` int(32) NOT NULL DEFAULT '0',
  `count` int(32) NOT NULL DEFAULT '0',
  `name` varchar(16) NOT NULL DEFAULT '',
  `channel` int(16) NOT NULL DEFAULT '1',
  `gold` int(32) NOT NULL DEFAULT '0',
  `status` smallint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`shop_id`)
) ENGINE=MyISAM AUTO_INCREMENT=31 DEFAULT CHARSET=utf8;

