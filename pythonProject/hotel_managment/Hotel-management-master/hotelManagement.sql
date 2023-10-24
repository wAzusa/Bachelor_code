

DROP TABLE IF EXISTS `booking_client`;

CREATE TABLE `booking_client` (
  `cid` varchar(255) NOT NULL,
  `rid` varchar(255) NOT NULL,
  `start_time` date DEFAULT NULL,
  `end_time` date DEFAULT NULL,
  `booking_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`cid`,`rid`),
  KEY `rid` (`rid`),
  CONSTRAINT `booking_client_ibfk_1` FOREIGN KEY (`cid`) REFERENCES `client` (`cid`),
  CONSTRAINT `booking_client_ibfk_2` FOREIGN KEY (`rid`) REFERENCES `room` (`rid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;



LOCK TABLES `booking_client` WRITE;

INSERT INTO `booking_client` VALUES ('131989238123991309','203','2023-01-06','2023-01-08','2023-01-06 00:49:02','无行李');

UNLOCK TABLES;



DROP TABLE IF EXISTS `booking_team`;

CREATE TABLE `booking_team` (
  `tid` varchar(255) NOT NULL,
  `rid` varchar(255) NOT NULL,
  `start_time` date DEFAULT NULL,
  `end_time` date DEFAULT NULL,
  `booking_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`tid`,`rid`),
  KEY `rid` (`rid`),
  CONSTRAINT `booking_team_ibfk_1` FOREIGN KEY (`tid`) REFERENCES `team` (`tid`),
  CONSTRAINT `booking_team_ibfk_2` FOREIGN KEY (`rid`) REFERENCES `room` (`rid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `booking_team` WRITE;

INSERT INTO `booking_team` VALUES ('55','303','2023-01-06','2023-01-10','2023-01-06 00:52:27','新客户'),('55','305','2023-01-06','2023-01-10','2023-01-06 00:52:23','新客户'),('7','301','2023-01-10','2023-01-15','2023-01-04 09:19:22','可能晚一些'),('7','303','2023-01-10','2023-01-15','2023-01-04 09:19:36',NULL);

UNLOCK TABLES;



DROP TABLE IF EXISTS `checkin_client`;

CREATE TABLE `checkin_client` (
  `rid` varchar(255) NOT NULL,
  `cid` varchar(255) NOT NULL,
  `start_time` date DEFAULT NULL,
  `end_time` date DEFAULT NULL,
  `total_price` varchar(255) DEFAULT NULL,
  `check_in_sid` varchar(255) DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`rid`,`cid`),
  KEY `cid` (`cid`),
  KEY `check_in_sid` (`check_in_sid`),
  CONSTRAINT `checkin_client_ibfk_1` FOREIGN KEY (`rid`) REFERENCES `room` (`rid`),
  CONSTRAINT `checkin_client_ibfk_2` FOREIGN KEY (`cid`) REFERENCES `client` (`cid`),
  CONSTRAINT `checkin_client_ibfk_3` FOREIGN KEY (`check_in_sid`) REFERENCES `staff` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;



LOCK TABLES `checkin_client` WRITE;

INSERT INTO `checkin_client` VALUES ('201','189322199312262232','2023-01-06','2023-01-07','208','1','新客');

UNLOCK TABLES;

DELIMITER ;;

DELIMITER ;




DROP TABLE IF EXISTS `checkin_team`;

CREATE TABLE `checkin_team` (
  `rid` varchar(255) NOT NULL,
  `tid` varchar(255) NOT NULL,
  `start_time` date DEFAULT NULL,
  `end_time` date DEFAULT NULL,
  `total_price` varchar(255) DEFAULT NULL,
  `check_in_sid` varchar(255) DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`rid`,`tid`),
  KEY `teamsid` (`check_in_sid`),
  KEY `teamtid` (`tid`),
  CONSTRAINT `teamrid` FOREIGN KEY (`rid`) REFERENCES `room` (`rid`),
  CONSTRAINT `teamsid` FOREIGN KEY (`check_in_sid`) REFERENCES `staff` (`sid`),
  CONSTRAINT `teamtid` FOREIGN KEY (`tid`) REFERENCES `team` (`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `checkin_team` WRITE;

INSERT INTO `checkin_team` VALUES ('404','30','2023-01-05','2023-01-06','2940','8',NULL),('406','30','2023-01-05','2023-01-06','2940','8','团队入住');

UNLOCK TABLES;

DELIMITER ;;

DELIMITER ;



DROP TABLE IF EXISTS `client`;

CREATE TABLE `client` (
  `cname` varchar(255) NOT NULL,
  `cid` varchar(255) NOT NULL,
  `cphone` varchar(255) DEFAULT NULL,
  `cage` varchar(255) NOT NULL,
  `csex` varchar(255) DEFAULT NULL,
  `register_sid` varchar(255) DEFAULT NULL,
  `accomodation_times` int(11) DEFAULT NULL,
  `register_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`cid`),
  KEY `sid` (`register_sid`),
  KEY `cid` (`cid`,`register_sid`),
  CONSTRAINT `sid` FOREIGN KEY (`register_sid`) REFERENCES `staff` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


LOCK TABLES `client` WRITE;

INSERT INTO `client` VALUES ('吴超梦','130898199212233434','13898322223','28','女','4',1,'2023-01-04 10:48:42'),('黄荣','131989238123991309','13123323212','52','男','7',1,'2023-01-04 09:24:48'),('王潇','189322199312262232','13098722343','27','男','4',1,'2023-01-06 00:17:20'),('柯镇恶','289193212393128999','13310913888','50','男','6',0,'2023-01-04 09:16:01'),('段深','290389199412280303','13898767890','26','男','5',0,'2020-01-04 09:15:32'),('黄晓让','320198199812243456','13789098789','21','女','5',3,'2023-01-04 10:06:33'),('赵超','320222199102036712','13821322312','23','男','8',2,'2023-01-04 09:24:42'),('赵重样','320678199012243333','13765434212','30','男','2',0,'2023-01-04 09:12:44'),('黄穰','320876196510200099','13876534543','55','女','1',0,'2023-01-04 09:12:26'),('黄晓让','320897189722334567','13987667890','30','男','2',1,'2023-01-04 10:09:29'),('西羊羊','320987199012234444','19876556789','30','女','3',3,'2023-01-04 09:24:50');

UNLOCK TABLES;



DROP TABLE IF EXISTS `hotelorder`;

CREATE TABLE `hotelorder` (
  `id` varchar(255) NOT NULL,
  `ordertype` varchar(255) NOT NULL,
  `start_time` date NOT NULL,
  `end_time` date NOT NULL,
  `rid` varchar(255) NOT NULL,
  `pay_type` varchar(255) DEFAULT NULL,
  `money` varchar(255) DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  `order_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `register_sid` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`,`start_time`,`end_time`,`rid`,`ordertype`),
  KEY `rid` (`rid`),
  KEY `register_sid` (`register_sid`),
  CONSTRAINT `hotelorder_ibfk_1` FOREIGN KEY (`rid`) REFERENCES `room` (`rid`),
  CONSTRAINT `hotelorder_ibfk_2` FOREIGN KEY (`register_sid`) REFERENCES `staff` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `hotelorder` WRITE;

INSERT INTO `hotelorder` VALUES ('1','团队','2023-01-06','2023-01-09','307','微信','624','','2023-01-08 14:15:32','2'),('1','团队','2023-01-06','2023-01-09','308','微信','2064','','2023-01-08 14:15:33','2'),('130898199212233434','个人','2023-01-04','2023-01-07','201','微信','624','垃圾','2023-01-04 11:57:54','1'),('30','团队','2022-12-21','2022-12-31','406','支付宝','5555','好评','2023-01-04 09:23:38','2'),('30','团队','2022-12-30','2023-01-01','203','支付宝','221','好评','2023-01-04 09:23:44','2'),('30','团队','2023-01-03','2023-01-03','201','支付宝','231','好评','2023-01-04 09:23:42','1'),('320222199102036712','个人','2023-01-02','2023-01-03','406','微信','1176','好评','2023-01-04 09:23:34','4'),('320222199102036788','个人','2023-01-03','2023-01-03','201','微信','5616','好评','2023-01-04 09:23:01','3'),('320897189722334567','个人','2020-01-04','2023-01-05','404','微信','1764','打赏','2023-01-06 00:52:11','1'),('330987126376589900','个人','2023-01-05','2023-01-06','301','微信','208','好评','2023-01-05 06:44:44','2'),('43','团队','2023-01-04','2023-01-06','307','微信','624','垃圾','2023-01-06 00:52:02','1'),('43','团队','2023-01-04','2023-01-06','402','微信','804','垃圾','2023-01-06 00:51:59','1'),('7','团队','2023-01-01','2023-01-02','201','微信','258','中评','2023-01-04 09:23:54','5');

UNLOCK TABLES;



DROP TABLE IF EXISTS `room`;

CREATE TABLE `room` (
  `rid` varchar(255) NOT NULL,
  `rtype` varchar(255) NOT NULL,
  `rstorey` varchar(255) NOT NULL,
  `rprice` varchar(255) NOT NULL,
  `rdesc` varchar(255) DEFAULT NULL,
  `rpic` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`rid`),
  KEY `rid` (`rid`,`rprice`),
  KEY `rid_2` (`rid`,`rprice`,`rtype`),
  KEY `rid_3` (`rid`,`rtype`,`rprice`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `room` WRITE;

INSERT INTO `room` VALUES ('201','标准间（单人）','2','208','电视故障','D:/pictures/ss.jpg'),('203','标准间（单人）','2','208','无','D:/pictures/ss.jpg'),('205','标准间（双人）','2','268','没事','D:/pictures/sd.jpg'),('207','标准间（双人）','2','268','采光好','D:/pictures/sd.jpg'),('301','标准间（单人）','3','208','采光好','D:/pictures/ss.jpg'),('303','大床房','3','258','无','D:/pictures/b.jpg'),('305','大床房','3','258','设施新','D:/pictures/b.jpg'),('307','标准间（单人）','3','208','设施新','D:/pictures/ss.jpg'),('308','总统套房','3','688','古典','D:/pictures/pr1.jpg'),('402','标准间（双人）','4','268','空调故障','D:/pictures/sd.jpg'),('404','总统套房','4','588','好评率高','D:/pictures/pr1.jpg'),('406','总统套房','4','588','好评率高','D:/pictures/pr2.jpg'),('410','标准间（单人）','4','232','新房','D:/pictures/ss.jpg');

UNLOCK TABLES;



DROP TABLE IF EXISTS `staff`;

CREATE TABLE `staff` (
  `sid` varchar(255) NOT NULL,
  `sname` varchar(255) NOT NULL,
  `ssex` varchar(255) DEFAULT NULL,
  `stime` date DEFAULT NULL,
  `susername` varchar(255) NOT NULL,
  `spassword` varchar(255) NOT NULL,
  `srole` varchar(255) NOT NULL,
  `sidcard` varchar(255) NOT NULL,
  `sphone` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`sid`),
  UNIQUE KEY `susername` (`susername`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `staff` WRITE;

INSERT INTO `staff` VALUES ('1','张三','男','2022-12-23','zs123','123456','1','310572199012233421','13977766253'),('2','李四','女','2022-12-06','ls123','123456','2','329123199102021234','13823209876'),('3','张萍','女','2022-12-26','zp123','123456','1','332987199812262512','13782765657'),('4','赵六','女','2023-01-01','zl123','123456','1','332987199811164512','13888909890'),('5','王五','男','2023-01-01','wu123','123456','2','332987199812264512','13988767890'),('6','黄让','男','2023-01-01','hr123','123456','2','332987199811263333','13962334343'),('7','黄小平','女','2020-12-04','hxp123','123456','1','332987199811262222','13962334222'),('8','阿斯顿','男','2020-12-02','asd123','123456','1','332987199810102222','13962334333');

UNLOCK TABLES;


DROP TABLE IF EXISTS `team`;

CREATE TABLE `team` (
  `tname` varchar(255) NOT NULL,
  `tid` varchar(255) NOT NULL,
  `tphone` varchar(255) DEFAULT NULL,
  `check_in_sid` varchar(255) DEFAULT NULL,
  `accomodation_times` int(11) DEFAULT NULL,
  `register_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`tid`),
  KEY `team_sid` (`check_in_sid`),
  CONSTRAINT `team_sid` FOREIGN KEY (`check_in_sid`) REFERENCES `staff` (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;




LOCK TABLES `team` WRITE;

INSERT INTO `team` VALUES ('hit','1','13896534534','1',2,'2023-01-06 00:50:46'),('zkl','11','13976523423','6',0,'2023-01-04 09:10:02'),('大工','16','13987667890','3',0,'2023-01-04 09:06:55'),('大工','30','13898700998','1',5,'2023-01-05 11:09:25'),('先行创业者社团','32','13962463676','2',0,'2023-01-04 09:06:37'),('腾讯','43','13829833333','1',3,'2023-01-04 11:55:01'),('家家悦','55','13678998789','2',0,'2023-01-05 06:41:05'),('合唱团','7','17878989098','6',1,'2023-01-04 09:25:37'),('alibaba','8','18978978909','4',0,'2023-01-04 09:07:48');

UNLOCK TABLES;


