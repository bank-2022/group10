-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: bank
-- ------------------------------------------------------
-- Server version	8.0.23

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `id_asiakas` int unsigned NOT NULL AUTO_INCREMENT,
  `nimi` varchar(45) NOT NULL,
  `osoite` varchar(45) NOT NULL,
  `puhelinnumero` varchar(45) NOT NULL,
  PRIMARY KEY (`id_asiakas`),
  UNIQUE KEY `id_asiakas_UNIQUE` (`id_asiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Teppo Testi','Blaablaa','0451234567'),(2,'Maija Meikäläinen','Liirumlaarum','0407654321');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `asiakastili`
--

DROP TABLE IF EXISTS `asiakastili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakastili` (
  `id_asiakas` int unsigned NOT NULL,
  `id_tili` int unsigned NOT NULL,
  PRIMARY KEY (`id_tili`,`id_asiakas`),
  KEY `id_asiakas_idx` (`id_asiakas`),
  CONSTRAINT `id_asiakas_asiakastili` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `id_tili_asiakastili` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakastili`
--

LOCK TABLES `asiakastili` WRITE;
/*!40000 ALTER TABLE `asiakastili` DISABLE KEYS */;
INSERT INTO `asiakastili` VALUES (1,1),(2,2);
/*!40000 ALTER TABLE `asiakastili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `id_kortti` int unsigned NOT NULL AUTO_INCREMENT,
  `korttinumero` varchar(255) DEFAULT NULL,
  `pin` varchar(255) DEFAULT NULL,
  `id_tili` int unsigned NOT NULL,
  `id_asiakas` int unsigned NOT NULL,
  `locked` varchar(225) NOT NULL,
  `login_tries` int DEFAULT NULL,
  PRIMARY KEY (`id_kortti`),
  UNIQUE KEY `id_kortti_UNIQUE` (`id_kortti`),
  UNIQUE KEY `korttinro_UNIQUE` (`korttinumero`),
  KEY `fk_kortti_tili1_idx` (`id_tili`),
  KEY `fk_kortti_asiakas1_idx` (`id_asiakas`),
  CONSTRAINT `id_asiakas_kortti` FOREIGN KEY (`id_asiakas`) REFERENCES `asiakas` (`id_asiakas`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `id_tili_kortti` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES (1,'05009B22B2','$2a$10$Y61m2.ZoIJgDq9rHX3we/uX3ca7ZdqHD1tT2kT/uBYvLfCZQGIb7e',1,1,'FALSE',0),(2,'06000620AD','$2a$10$hdPTewBxl4dbJMf8HN2pfupJ/X9Cfuuc/bWL4w5UVUqZBWjE8I.Km',2,2,'FALSE',0);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `id_tili` int unsigned NOT NULL AUTO_INCREMENT,
  `tilinumero` varchar(45) DEFAULT NULL,
  `saldo` float unsigned DEFAULT NULL,
  PRIMARY KEY (`id_tili`),
  UNIQUE KEY `id_tili_UNIQUE` (`id_tili`),
  UNIQUE KEY `tilinumero_UNIQUE` (`tilinumero`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (1,'FI4950009420028730',530),(2,'FI4966010001234568',1000);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `id_tilitapahtumat` int unsigned NOT NULL AUTO_INCREMENT,
  `paivays` datetime DEFAULT NULL,
  `tapahtuma` varchar(45) DEFAULT NULL,
  `summa` float DEFAULT NULL,
  `id_kortti` int unsigned DEFAULT NULL,
  `id_tili` int unsigned NOT NULL,
  PRIMARY KEY (`id_tilitapahtumat`),
  UNIQUE KEY `id_tilitapahtumat_UNIQUE` (`id_tilitapahtumat`),
  KEY `fk_tilitapahtumat_tili1_idx` (`id_tili`),
  KEY `id_kortti_tilitapahtumat_idx` (`id_kortti`),
  CONSTRAINT `id_kortti_tilitapahtumat` FOREIGN KEY (`id_kortti`) REFERENCES `kortti` (`id_kortti`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `id_tili_tilitapahtumat` FOREIGN KEY (`id_tili`) REFERENCES `tili` (`id_tili`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (1,'2022-03-31 18:00:00','otto',-50,1,1),(2,'2022-04-21 17:55:02','otto',-200,1,1),(3,'2022-04-21 18:01:59','otto',-50,1,1),(4,'2022-04-21 18:02:45','otto',-20,1,1),(5,'2022-04-21 19:45:29','otto',-20,1,1),(6,'2022-04-21 19:45:43','otto',-100,1,1),(7,'2022-04-21 21:05:18','otto',-20,1,1),(8,'2022-04-21 21:05:38','otto',-30,1,1),(9,'2022-04-21 23:14:14','otto',-30,1,1),(10,'2022-04-26 13:12:14','otto',-500,1,1);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bank'
--
/*!50003 DROP PROCEDURE IF EXISTS `debit_transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `debit_transfer`(IN card_id INT, IN account_id INT, IN amount FLOAT )
BEGIN
DECLARE test1 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE tili SET saldo=saldo+amount WHERE id_tili=account_id AND saldo>=amount;
  SET test1=ROW_COUNT();
  
    IF (test1 > 0 AND amount<0 ) THEN   
      COMMIT;    
      INSERT INTO tilitapahtumat(paivays,tapahtuma,summa,id_kortti, id_tili) VALUES(NOW(),'otto', amount, card_id, account_id);
    ELSE
      ROLLBACK;
  END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-26 13:33:27
