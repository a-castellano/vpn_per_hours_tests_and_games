-- MySQL dump 10.13  Distrib 5.5.47, for debian-linux-gnu (x86_64)
--
-- Host: paula.es.una.ninja    Database: vpn
-- ------------------------------------------------------
-- Server version	5.5.47-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `countries`
--

DROP TABLE IF EXISTS `countries`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `countries` (
  `id` int(11) NOT NULL,
  `capital` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `citizenship` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `country_code` char(3) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `currency` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `currency_code` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `currency_sub_unit` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `currency_symbol` varchar(3) COLLATE utf8_unicode_ci DEFAULT NULL,
  `full_name` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `iso_3166_2` char(2) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `iso_3166_3` char(3) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `region_code` char(3) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `sub_region_code` char(3) COLLATE utf8_unicode_ci NOT NULL DEFAULT '',
  `eea` tinyint(1) NOT NULL DEFAULT '0',
  `calling_code` varchar(3) COLLATE utf8_unicode_ci DEFAULT NULL,
  `flag` varchar(6) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `countries_id_index` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `countries`
--

LOCK TABLES `countries` WRITE;
/*!40000 ALTER TABLE `countries` DISABLE KEYS */;
INSERT INTO `countries` VALUES (4,'Kabul','Afghan','004','afghani','AFN','pul','؋','Islamic Republic of Afghanistan','AF','AFG','Afghanistan','142','034',0,'93','AF.png'),(8,'Tirana','Albanian','008','lek','ALL','(qindar (pl. qindarka))','Lek','Republic of Albania','AL','ALB','Albania','150','039',0,'355','AL.png'),(10,'Antartica','of Antartica','010','','','','','Antarctica','AQ','ATA','Antarctica','','',0,'672','AQ.png'),(12,'Algiers','Algerian','012','Algerian dinar','DZD','centime','DZD','People’s Democratic Republic of Algeria','DZ','DZA','Algeria','002','015',0,'213','DZ.png'),(16,'Pago Pago','American Samoan','016','US dollar','USD','cent','$','Territory of American','AS','ASM','American Samoa','009','061',0,'1','AS.png'),(20,'Andorra la Vella','Andorran','020','euro','EUR','cent','€','Principality of Andorra','AD','AND','Andorra','150','039',0,'376','AD.png'),(24,'Luanda','Angolan','024','kwanza','AOA','cêntimo','Kz','Republic of Angola','AO','AGO','Angola','002','017',0,'244','AO.png'),(28,'St John’s','of Antigua and Barbuda','028','East Caribbean dollar','XCD','cent','$','Antigua and Barbuda','AG','ATG','Antigua and Barbuda','019','029',0,'1','AG.png'),(31,'Baku','Azerbaijani','031','Azerbaijani manat','AZN','kepik (inv.)','ман','Republic of Azerbaijan','AZ','AZE','Azerbaijan','142','145',0,'994','AZ.png'),(32,'Buenos Aires','Argentinian','032','Argentine peso','ARS','centavo','$','Argentine Republic','AR','ARG','Argentina','019','005',0,'54','AR.png'),(36,'Canberra','Australian','036','Australian dollar','AUD','cent','$','Commonwealth of Australia','AU','AUS','Australia','009','053',0,'61','AU.png'),(40,'Vienna','Austrian','040','euro','EUR','cent','€','Republic of Austria','AT','AUT','Austria','150','155',1,'43','AT.png'),(44,'Nassau','Bahamian','044','Bahamian dollar','BSD','cent','$','Commonwealth of the Bahamas','BS','BHS','Bahamas','019','029',0,'1','BS.png'),(48,'Manama','Bahraini','048','Bahraini dinar','BHD','fils (inv.)','BHD','Kingdom of Bahrain','BH','BHR','Bahrain','142','145',0,'973','BH.png'),(50,'Dhaka','Bangladeshi','050','taka (inv.)','BDT','poisha (inv.)','BDT','People’s Republic of Bangladesh','BD','BGD','Bangladesh','142','034',0,'880','BD.png'),(51,'Yerevan','Armenian','051','dram (inv.)','AMD','luma','AMD','Republic of Armenia','AM','ARM','Armenia','142','145',0,'374','AM.png'),(52,'Bridgetown','Barbadian','052','Barbados dollar','BBD','cent','$','Barbados','BB','BRB','Barbados','019','029',0,'1','BB.png'),(56,'Brussels','Belgian','056','euro','EUR','cent','€','Kingdom of Belgium','BE','BEL','Belgium','150','155',1,'32','BE.png'),(60,'Hamilton','Bermudian','060','Bermuda dollar','BMD','cent','$','Bermuda','BM','BMU','Bermuda','019','021',0,'1','BM.png'),(64,'Thimphu','Bhutanese','064','ngultrum (inv.)','BTN','chhetrum (inv.)','BTN','Kingdom of Bhutan','BT','BTN','Bhutan','142','034',0,'975','BT.png'),(68,'Sucre (BO1)','Bolivian','068','boliviano','BOB','centavo','$b','Plurinational State of Bolivia','BO','BOL','Bolivia, Plurinational State of','019','005',0,'591','BO.png'),(70,'Sarajevo','of Bosnia and Herzegovina','070','convertible mark','BAM','fening','KM','Bosnia and Herzegovina','BA','BIH','Bosnia and Herzegovina','150','039',0,'387','BA.png'),(72,'Gaborone','Botswanan','072','pula (inv.)','BWP','thebe (inv.)','P','Republic of Botswana','BW','BWA','Botswana','002','018',0,'267','BW.png'),(74,'Bouvet island','of Bouvet island','074','','','','kr','Bouvet Island','BV','BVT','Bouvet Island','','',0,'47','BV.png'),(76,'Brasilia','Brazilian','076','real (pl. reais)','BRL','centavo','R$','Federative Republic of Brazil','BR','BRA','Brazil','019','005',0,'55','BR.png'),(84,'Belmopan','Belizean','084','Belize dollar','BZD','cent','BZ$','Belize','BZ','BLZ','Belize','019','013',0,'501','BZ.png'),(86,'Diego Garcia','Changosian','086','US dollar','USD','cent','$','British Indian Ocean Territory','IO','IOT','British Indian Ocean Territory','','',0,'246','IO.png'),(90,'Honiara','Solomon Islander','090','Solomon Islands dollar','SBD','cent','$','Solomon Islands','SB','SLB','Solomon Islands','009','054',0,'677','SB.png'),(92,'Road Town','British Virgin Islander;','092','US dollar','USD','cent','$','British Virgin Islands','VG','VGB','Virgin Islands, British','019','029',0,'1','VG.png'),(96,'Bandar Seri Begawan','Bruneian','096','Brunei dollar','BND','sen (inv.)','$','Brunei Darussalam','BN','BRN','Brunei Darussalam','142','035',0,'673','BN.png'),(100,'Sofia','Bulgarian','100','lev (pl. leva)','BGN','stotinka','лв','Republic of Bulgaria','BG','BGR','Bulgaria','150','151',1,'359','BG.png'),(104,'Yangon','Burmese','104','kyat','MMK','pya','K','Union of Myanmar/','MM','MMR','Myanmar','142','035',0,'95','MM.png'),(108,'Bujumbura','Burundian','108','Burundi franc','BIF','centime','BIF','Republic of Burundi','BI','BDI','Burundi','002','014',0,'257','BI.png'),(112,'Minsk','Belarusian','112','Belarusian rouble','BYR','kopek','p.','Republic of Belarus','BY','BLR','Belarus','150','151',0,'375','BY.png'),(116,'Phnom Penh','Cambodian','116','riel','KHR','sen (inv.)','៛','Kingdom of Cambodia','KH','KHM','Cambodia','142','035',0,'855','KH.png'),(120,'Yaoundé','Cameroonian','120','CFA franc (BEAC)','XAF','centime','FCF','Republic of Cameroon','CM','CMR','Cameroon','002','017',0,'237','CM.png'),(124,'Ottawa','Canadian','124','Canadian dollar','CAD','cent','$','Canada','CA','CAN','Canada','019','021',0,'1','CA.png'),(132,'Praia','Cape Verdean','132','Cape Verde escudo','CVE','centavo','CVE','Republic of Cape Verde','CV','CPV','Cape Verde','002','011',0,'238','CV.png'),(136,'George Town','Caymanian','136','Cayman Islands dollar','KYD','cent','$','Cayman Islands','KY','CYM','Cayman Islands','019','029',0,'1','KY.png'),(140,'Bangui','Central African','140','CFA franc (BEAC)','XAF','centime','FCF','Central African Republic','CF','CAF','Central African Republic','002','017',0,'236','CF.png'),(144,'Colombo','Sri Lankan','144','Sri Lankan rupee','LKR','cent','₨','Democratic Socialist Republic of Sri Lanka','LK','LKA','Sri Lanka','142','034',0,'94','LK.png'),(148,'N’Djamena','Chadian','148','CFA franc (BEAC)','XAF','centime','XAF','Republic of Chad','TD','TCD','Chad','002','017',0,'235','TD.png'),(152,'Santiago','Chilean','152','Chilean peso','CLP','centavo','CLP','Republic of Chile','CL','CHL','Chile','019','005',0,'56','CL.png'),(156,'Beijing','Chinese','156','renminbi-yuan (inv.)','CNY','jiao (10)','¥','People’s Republic of China','CN','CHN','China','142','030',0,'86','CN.png'),(158,'Taipei','Taiwanese','158','new Taiwan dollar','TWD','fen (inv.)','NT$','Republic of China, Taiwan (TW1)','TW','TWN','Taiwan, Province of China','142','030',0,'886','TW.png'),(162,'Flying Fish Cove','Christmas Islander','162','Australian dollar','AUD','cent','$','Christmas Island Territory','CX','CXR','Christmas Island','','',0,'61','CX.png'),(166,'Bantam','Cocos Islander','166','Australian dollar','AUD','cent','$','Territory of Cocos (Keeling) Islands','CC','CCK','Cocos (Keeling) Islands','','',0,'61','CC.png'),(170,'Santa Fe de Bogotá','Colombian','170','Colombian peso','COP','centavo','$','Republic of Colombia','CO','COL','Colombia','019','005',0,'57','CO.png'),(174,'Moroni','Comorian','174','Comorian franc','KMF','','KMF','Union of the Comoros','KM','COM','Comoros','002','014',0,'269','KM.png'),(175,'Mamoudzou','Mahorais','175','euro','EUR','cent','€','Departmental Collectivity of Mayotte','YT','MYT','Mayotte','002','014',0,'262','YT.png'),(178,'Brazzaville','Congolese','178','CFA franc (BEAC)','XAF','centime','FCF','Republic of the Congo','CG','COG','Congo','002','017',0,'242','CG.png'),(180,'Kinshasa','Congolese','180','Congolese franc','CDF','centime','CDF','Democratic Republic of the Congo','CD','COD','Congo, the Democratic Republic of the','002','017',0,'243','CD.png'),(184,'Avarua','Cook Islander','184','New Zealand dollar','NZD','cent','$','Cook Islands','CK','COK','Cook Islands','009','061',0,'682','CK.png'),(188,'San José','Costa Rican','188','Costa Rican colón (pl. colones)','CRC','céntimo','₡','Republic of Costa Rica','CR','CRI','Costa Rica','019','013',0,'506','CR.png'),(191,'Zagreb','Croatian','191','kuna (inv.)','HRK','lipa (inv.)','kn','Republic of Croatia','HR','HRV','Croatia','150','039',1,'385','HR.png'),(192,'Havana','Cuban','192','Cuban peso','CUP','centavo','₱','Republic of Cuba','CU','CUB','Cuba','019','029',0,'53','CU.png'),(196,'Nicosia','Cypriot','196','euro','EUR','cent','CYP','Republic of Cyprus','CY','CYP','Cyprus','142','145',1,'357','CY.png'),(203,'Prague','Czech','203','Czech koruna (pl. koruny)','CZK','halér','Kč','Czech Republic','CZ','CZE','Czech Republic','150','151',1,'420','CZ.png'),(204,'Porto Novo (BJ1)','Beninese','204','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Benin','BJ','BEN','Benin','002','011',0,'229','BJ.png'),(208,'Copenhagen','Danish','208','Danish krone','DKK','øre (inv.)','kr','Kingdom of Denmark','DK','DNK','Denmark','150','154',1,'45','DK.png'),(212,'Roseau','Dominican','212','East Caribbean dollar','XCD','cent','$','Commonwealth of Dominica','DM','DMA','Dominica','019','029',0,'1','DM.png'),(214,'Santo Domingo','Dominican','214','Dominican peso','DOP','centavo','RD$','Dominican Republic','DO','DOM','Dominican Republic','019','029',0,'1','DO.png'),(218,'Quito','Ecuadorian','218','US dollar','USD','cent','$','Republic of Ecuador','EC','ECU','Ecuador','019','005',0,'593','EC.png'),(222,'San Salvador','Salvadoran','222','Salvadorian colón (pl. colones)','SVC','centavo','$','Republic of El Salvador','SV','SLV','El Salvador','019','013',0,'503','SV.png'),(226,'Malabo','Equatorial Guinean','226','CFA franc (BEAC)','XAF','centime','FCF','Republic of Equatorial Guinea','GQ','GNQ','Equatorial Guinea','002','017',0,'240','GQ.png'),(231,'Addis Ababa','Ethiopian','231','birr (inv.)','ETB','cent','ETB','Federal Democratic Republic of Ethiopia','ET','ETH','Ethiopia','002','014',0,'251','ET.png'),(232,'Asmara','Eritrean','232','nakfa','ERN','cent','Nfk','State of Eritrea','ER','ERI','Eritrea','002','014',0,'291','ER.png'),(233,'Tallinn','Estonian','233','euro','EUR','cent','kr','Republic of Estonia','EE','EST','Estonia','150','154',1,'372','EE.png'),(234,'Tórshavn','Faeroese','234','Danish krone','DKK','øre (inv.)','kr','Faeroe Islands','FO','FRO','Faroe Islands','150','154',0,'298','FO.png'),(238,'Stanley','Falkland Islander','238','Falkland Islands pound','FKP','new penny','£','Falkland Islands','FK','FLK','Falkland Islands (Malvinas)','019','005',0,'500','FK.png'),(239,'King Edward Point (Grytviken)','of South Georgia and the South Sandwich Islands','239','','','','£','South Georgia and the South Sandwich Islands','GS','SGS','South Georgia and the South Sandwich Islands','','',0,'44','GS.png'),(242,'Suva','Fijian','242','Fiji dollar','FJD','cent','$','Republic of Fiji','FJ','FJI','Fiji','009','054',0,'679','FJ.png'),(246,'Helsinki','Finnish','246','euro','EUR','cent','€','Republic of Finland','FI','FIN','Finland','150','154',1,'358','FI.png'),(248,'Mariehamn','Åland Islander','248','euro','EUR','cent',NULL,'Åland Islands','AX','ALA','Åland Islands','150','154',0,'358',NULL),(250,'Paris','French','250','euro','EUR','cent','€','French Republic','FR','FRA','France','150','155',1,'33','FR.png'),(254,'Cayenne','Guianese','254','euro','EUR','cent','€','French Guiana','GF','GUF','French Guiana','019','005',0,'594','GF.png'),(258,'Papeete','Polynesian','258','CFP franc','XPF','centime','XPF','French Polynesia','PF','PYF','French Polynesia','009','061',0,'689','PF.png'),(260,'Port-aux-Francais','of French Southern and Antarctic Lands','260','euro','EUR','cent','€','French Southern and Antarctic Lands','TF','ATF','French Southern Territories','','',0,'33','TF.png'),(262,'Djibouti','Djiboutian','262','Djibouti franc','DJF','','DJF','Republic of Djibouti','DJ','DJI','Djibouti','002','014',0,'253','DJ.png'),(266,'Libreville','Gabonese','266','CFA franc (BEAC)','XAF','centime','FCF','Gabonese Republic','GA','GAB','Gabon','002','017',0,'241','GA.png'),(268,'Tbilisi','Georgian','268','lari','GEL','tetri (inv.)','GEL','Georgia','GE','GEO','Georgia','142','145',0,'995','GE.png'),(270,'Banjul','Gambian','270','dalasi (inv.)','GMD','butut','D','Republic of the Gambia','GM','GMB','Gambia','002','011',0,'220','GM.png'),(275,NULL,'Palestinian','275',NULL,NULL,NULL,'₪',NULL,'PS','PSE','Palestinian Territory, Occupied','142','145',0,'970','PS.png'),(276,'Berlin','German','276','euro','EUR','cent','€','Federal Republic of Germany','DE','DEU','Germany','150','155',1,'49','DE.png'),(288,'Accra','Ghanaian','288','Ghana cedi','GHS','pesewa','¢','Republic of Ghana','GH','GHA','Ghana','002','011',0,'233','GH.png'),(292,'Gibraltar','Gibraltarian','292','Gibraltar pound','GIP','penny','£','Gibraltar','GI','GIB','Gibraltar','150','039',0,'350','GI.png'),(296,'Tarawa','Kiribatian','296','Australian dollar','AUD','cent','$','Republic of Kiribati','KI','KIR','Kiribati','009','057',0,'686','KI.png'),(300,'Athens','Greek','300','euro','EUR','cent','€','Hellenic Republic','GR','GRC','Greece','150','039',1,'30','GR.png'),(304,'Nuuk','Greenlander','304','Danish krone','DKK','øre (inv.)','kr','Greenland','GL','GRL','Greenland','019','021',0,'299','GL.png'),(308,'St George’s','Grenadian','308','East Caribbean dollar','XCD','cent','$','Grenada','GD','GRD','Grenada','019','029',0,'1','GD.png'),(312,'Basse Terre','Guadeloupean','312','euro','EUR ','cent','€','Guadeloupe','GP','GLP','Guadeloupe','019','029',0,'590','GP.png'),(316,'Agaña (Hagåtña)','Guamanian','316','US dollar','USD','cent','$','Territory of Guam','GU','GUM','Guam','009','057',0,'1','GU.png'),(320,'Guatemala City','Guatemalan','320','quetzal (pl. quetzales)','GTQ','centavo','Q','Republic of Guatemala','GT','GTM','Guatemala','019','013',0,'502','GT.png'),(324,'Conakry','Guinean','324','Guinean franc','GNF','','GNF','Republic of Guinea','GN','GIN','Guinea','002','011',0,'224','GN.png'),(328,'Georgetown','Guyanese','328','Guyana dollar','GYD','cent','$','Cooperative Republic of Guyana','GY','GUY','Guyana','019','005',0,'592','GY.png'),(332,'Port-au-Prince','Haitian','332','gourde','HTG','centime','G','Republic of Haiti','HT','HTI','Haiti','019','029',0,'509','HT.png'),(334,'Territory of Heard Island and McDonald Islands','of Territory of Heard Island and McDonald Islands','334','','','','$','Territory of Heard Island and McDonald Islands','HM','HMD','Heard Island and McDonald Islands','','',0,'61','HM.png'),(336,'Vatican City','of the Holy See/of the Vatican','336','euro','EUR','cent','€','the Holy See/ Vatican City State','VA','VAT','Holy See (Vatican City State)','150','039',0,'39','VA.png'),(340,'Tegucigalpa','Honduran','340','lempira','HNL','centavo','L','Republic of Honduras','HN','HND','Honduras','019','013',0,'504','HN.png'),(344,'(HK3)','Hong Kong Chinese','344','Hong Kong dollar','HKD','cent','$','Hong Kong Special Administrative Region of the People’s Republic of China (HK2)','HK','HKG','Hong Kong','142','030',0,'852','HK.png'),(348,'Budapest','Hungarian','348','forint (inv.)','HUF','(fillér (inv.))','Ft','Republic of Hungary','HU','HUN','Hungary','150','151',1,'36','HU.png'),(352,'Reykjavik','Icelander','352','króna (pl. krónur)','ISK','','kr','Republic of Iceland','IS','ISL','Iceland','150','154',1,'354','IS.png'),(356,'New Delhi','Indian','356','Indian rupee','INR','paisa','₹','Republic of India','IN','IND','India','142','034',0,'91','IN.png'),(360,'Jakarta','Indonesian','360','Indonesian rupiah (inv.)','IDR','sen (inv.)','Rp','Republic of Indonesia','ID','IDN','Indonesia','142','035',0,'62','ID.png'),(364,'Tehran','Iranian','364','Iranian rial','IRR','(dinar) (IR1)','﷼','Islamic Republic of Iran','IR','IRN','Iran, Islamic Republic of','142','034',0,'98','IR.png'),(368,'Baghdad','Iraqi','368','Iraqi dinar','IQD','fils (inv.)','IQD','Republic of Iraq','IQ','IRQ','Iraq','142','145',0,'964','IQ.png'),(372,'Dublin','Irish','372','euro','EUR','cent','€','Ireland (IE1)','IE','IRL','Ireland','150','154',1,'353','IE.png'),(376,'(IL1)','Israeli','376','shekel','ILS','agora','₪','State of Israel','IL','ISR','Israel','142','145',0,'972','IL.png'),(380,'Rome','Italian','380','euro','EUR','cent','€','Italian Republic','IT','ITA','Italy','150','039',1,'39','IT.png'),(384,'Yamoussoukro (CI1)','Ivorian','384','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Côte d’Ivoire','CI','CIV','Côte d\'Ivoire','002','011',0,'225','CI.png'),(388,'Kingston','Jamaican','388','Jamaica dollar','JMD','cent','$','Jamaica','JM','JAM','Jamaica','019','029',0,'1','JM.png'),(392,'Tokyo','Japanese','392','yen (inv.)','JPY','(sen (inv.)) (JP1)','¥','Japan','JP','JPN','Japan','142','030',0,'81','JP.png'),(398,'Astana','Kazakh','398','tenge (inv.)','KZT','tiyn','лв','Republic of Kazakhstan','KZ','KAZ','Kazakhstan','142','143',0,'7','KZ.png'),(400,'Amman','Jordanian','400','Jordanian dinar','JOD','100 qirsh','JOD','Hashemite Kingdom of Jordan','JO','JOR','Jordan','142','145',0,'962','JO.png'),(404,'Nairobi','Kenyan','404','Kenyan shilling','KES','cent','KES','Republic of Kenya','KE','KEN','Kenya','002','014',0,'254','KE.png'),(408,'Pyongyang','North Korean','408','North Korean won (inv.)','KPW','chun (inv.)','₩','Democratic People’s Republic of Korea','KP','PRK','Korea, Democratic People\'s Republic of','142','030',0,'850','KP.png'),(410,'Seoul','South Korean','410','South Korean won (inv.)','KRW','(chun (inv.))','₩','Republic of Korea','KR','KOR','Korea, Republic of','142','030',0,'82','KR.png'),(414,'Kuwait City','Kuwaiti','414','Kuwaiti dinar','KWD','fils (inv.)','KWD','State of Kuwait','KW','KWT','Kuwait','142','145',0,'965','KW.png'),(417,'Bishkek','Kyrgyz','417','som','KGS','tyiyn','лв','Kyrgyz Republic','KG','KGZ','Kyrgyzstan','142','143',0,'996','KG.png'),(418,'Vientiane','Lao','418','kip (inv.)','LAK','(at (inv.))','₭','Lao People’s Democratic Republic','LA','LAO','Lao People\'s Democratic Republic','142','035',0,'856','LA.png'),(422,'Beirut','Lebanese','422','Lebanese pound','LBP','(piastre)','£','Lebanese Republic','LB','LBN','Lebanon','142','145',0,'961','LB.png'),(426,'Maseru','Basotho','426','loti (pl. maloti)','LSL','sente','L','Kingdom of Lesotho','LS','LSO','Lesotho','002','018',0,'266','LS.png'),(428,'Riga','Latvian','428','euro','EUR','cent','Ls','Republic of Latvia','LV','LVA','Latvia','150','154',1,'371','LV.png'),(430,'Monrovia','Liberian','430','Liberian dollar','LRD','cent','$','Republic of Liberia','LR','LBR','Liberia','002','011',0,'231','LR.png'),(434,'Tripoli','Libyan','434','Libyan dinar','LYD','dirham','LYD','Socialist People’s Libyan Arab Jamahiriya','LY','LBY','Libya','002','015',0,'218','LY.png'),(438,'Vaduz','Liechtensteiner','438','Swiss franc','CHF','centime','CHF','Principality of Liechtenstein','LI','LIE','Liechtenstein','150','155',1,'423','LI.png'),(440,'Vilnius','Lithuanian','440','euro','EUR','cent','Lt','Republic of Lithuania','LT','LTU','Lithuania','150','154',1,'370','LT.png'),(442,'Luxembourg','Luxembourger','442','euro','EUR','cent','€','Grand Duchy of Luxembourg','LU','LUX','Luxembourg','150','155',1,'352','LU.png'),(446,'Macao (MO3)','Macanese','446','pataca','MOP','avo','MOP','Macao Special Administrative Region of the People’s Republic of China (MO2)','MO','MAC','Macao','142','030',0,'853','MO.png'),(450,'Antananarivo','Malagasy','450','ariary','MGA','iraimbilanja (inv.)','MGA','Republic of Madagascar','MG','MDG','Madagascar','002','014',0,'261','MG.png'),(454,'Lilongwe','Malawian','454','Malawian kwacha (inv.)','MWK','tambala (inv.)','MK','Republic of Malawi','MW','MWI','Malawi','002','014',0,'265','MW.png'),(458,'Kuala Lumpur (MY1)','Malaysian','458','ringgit (inv.)','MYR','sen (inv.)','RM','Malaysia','MY','MYS','Malaysia','142','035',0,'60','MY.png'),(462,'Malé','Maldivian','462','rufiyaa','MVR','laari (inv.)','Rf','Republic of Maldives','MV','MDV','Maldives','142','034',0,'960','MV.png'),(466,'Bamako','Malian','466','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Mali','ML','MLI','Mali','002','011',0,'223','ML.png'),(470,'Valletta','Maltese','470','euro','EUR','cent','MTL','Republic of Malta','MT','MLT','Malta','150','039',1,'356','MT.png'),(474,'Fort-de-France','Martinican','474','euro','EUR','cent','€','Martinique','MQ','MTQ','Martinique','019','029',0,'596','MQ.png'),(478,'Nouakchott','Mauritanian','478','ouguiya','MRO','khoum','UM','Islamic Republic of Mauritania','MR','MRT','Mauritania','002','011',0,'222','MR.png'),(480,'Port Louis','Mauritian','480','Mauritian rupee','MUR','cent','₨','Republic of Mauritius','MU','MUS','Mauritius','002','014',0,'230','MU.png'),(484,'Mexico City','Mexican','484','Mexican peso','MXN','centavo','$','United Mexican States','MX','MEX','Mexico','019','013',0,'52','MX.png'),(492,'Monaco','Monegasque','492','euro','EUR','cent','€','Principality of Monaco','MC','MCO','Monaco','150','155',0,'377','MC.png'),(496,'Ulan Bator','Mongolian','496','tugrik','MNT','möngö (inv.)','₮','Mongolia','MN','MNG','Mongolia','142','030',0,'976','MN.png'),(498,'Chisinau','Moldovan','498','Moldovan leu (pl. lei)','MDL','ban','MDL','Republic of Moldova','MD','MDA','Moldova, Republic of','150','151',0,'373','MD.png'),(499,'Podgorica','Montenegrin','499','euro','EUR','cent',NULL,'Montenegro','ME','MNE','Montenegro','150','039',0,'382',NULL),(500,'Plymouth (MS2)','Montserratian','500','East Caribbean dollar','XCD','cent','$','Montserrat','MS','MSR','Montserrat','019','029',0,'1','MS.png'),(504,'Rabat','Moroccan','504','Moroccan dirham','MAD','centime','MAD','Kingdom of Morocco','MA','MAR','Morocco','002','015',0,'212','MA.png'),(508,'Maputo','Mozambican','508','metical','MZN','centavo','MT','Republic of Mozambique','MZ','MOZ','Mozambique','002','014',0,'258','MZ.png'),(512,'Muscat','Omani','512','Omani rial','OMR','baiza','﷼','Sultanate of Oman','OM','OMN','Oman','142','145',0,'968','OM.png'),(516,'Windhoek','Namibian','516','Namibian dollar','NAD','cent','$','Republic of Namibia','NA','NAM','Namibia','002','018',0,'264','NA.png'),(520,'Yaren','Nauruan','520','Australian dollar','AUD','cent','$','Republic of Nauru','NR','NRU','Nauru','009','057',0,'674','NR.png'),(524,'Kathmandu','Nepalese','524','Nepalese rupee','NPR','paisa (inv.)','₨','Nepal','NP','NPL','Nepal','142','034',0,'977','NP.png'),(528,'Amsterdam (NL2)','Dutch','528','euro','EUR','cent','€','Kingdom of the Netherlands','NL','NLD','Netherlands','150','155',1,'31','NL.png'),(531,'Willemstad','Curaçaoan','531','Netherlands Antillean guilder (CW1)','ANG','cent',NULL,'Curaçao','CW','CUW','Curaçao','019','029',0,'599',NULL),(533,'Oranjestad','Aruban','533','Aruban guilder','AWG','cent','ƒ','Aruba','AW','ABW','Aruba','019','029',0,'297','AW.png'),(534,'Philipsburg','Sint Maartener','534','Netherlands Antillean guilder (SX1)','ANG','cent',NULL,'Sint Maarten','SX','SXM','Sint Maarten (Dutch part)','019','029',0,'721',NULL),(535,NULL,'of Bonaire, Sint Eustatius and Saba','535','US dollar','USD','cent',NULL,NULL,'BQ','BES','Bonaire, Sint Eustatius and Saba','019','029',0,'599',NULL),(540,'Nouméa','New Caledonian','540','CFP franc','XPF','centime','XPF','New Caledonia','NC','NCL','New Caledonia','009','054',0,'687','NC.png'),(548,'Port Vila','Vanuatuan','548','vatu (inv.)','VUV','','Vt','Republic of Vanuatu','VU','VUT','Vanuatu','009','054',0,'678','VU.png'),(554,'Wellington','New Zealander','554','New Zealand dollar','NZD','cent','$','New Zealand','NZ','NZL','New Zealand','009','053',0,'64','NZ.png'),(558,'Managua','Nicaraguan','558','córdoba oro','NIO','centavo','C$','Republic of Nicaragua','NI','NIC','Nicaragua','019','013',0,'505','NI.png'),(562,'Niamey','Nigerien','562','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Niger','NE','NER','Niger','002','011',0,'227','NE.png'),(566,'Abuja','Nigerian','566','naira (inv.)','NGN','kobo (inv.)','₦','Federal Republic of Nigeria','NG','NGA','Nigeria','002','011',0,'234','NG.png'),(570,'Alofi','Niuean','570','New Zealand dollar','NZD','cent','$','Niue','NU','NIU','Niue','009','061',0,'683','NU.png'),(574,'Kingston','Norfolk Islander','574','Australian dollar','AUD','cent','$','Territory of Norfolk Island','NF','NFK','Norfolk Island','009','053',0,'672','NF.png'),(578,'Oslo','Norwegian','578','Norwegian krone (pl. kroner)','NOK','øre (inv.)','kr','Kingdom of Norway','NO','NOR','Norway','150','154',1,'47','NO.png'),(580,'Saipan','Northern Mariana Islander','580','US dollar','USD','cent','$','Commonwealth of the Northern Mariana Islands','MP','MNP','Northern Mariana Islands','009','057',0,'1','MP.png'),(581,'United States Minor Outlying Islands','of United States Minor Outlying Islands','581','US dollar','USD','cent','$','United States Minor Outlying Islands','UM','UMI','United States Minor Outlying Islands','','',0,'1','UM.png'),(583,'Palikir','Micronesian','583','US dollar','USD','cent','$','Federated States of Micronesia','FM','FSM','Micronesia, Federated States of','009','057',0,'691','FM.png'),(584,'Majuro','Marshallese','584','US dollar','USD','cent','$','Republic of the Marshall Islands','MH','MHL','Marshall Islands','009','057',0,'692','MH.png'),(585,'Melekeok','Palauan','585','US dollar','USD','cent','$','Republic of Palau','PW','PLW','Palau','009','057',0,'680','PW.png'),(586,'Islamabad','Pakistani','586','Pakistani rupee','PKR','paisa','₨','Islamic Republic of Pakistan','PK','PAK','Pakistan','142','034',0,'92','PK.png'),(591,'Panama City','Panamanian','591','balboa','PAB','centésimo','B/.','Republic of Panama','PA','PAN','Panama','019','013',0,'507','PA.png'),(598,'Port Moresby','Papua New Guinean','598','kina (inv.)','PGK','toea (inv.)','PGK','Independent State of Papua New Guinea','PG','PNG','Papua New Guinea','009','054',0,'675','PG.png'),(600,'Asunción','Paraguayan','600','guaraní','PYG','céntimo','Gs','Republic of Paraguay','PY','PRY','Paraguay','019','005',0,'595','PY.png'),(604,'Lima','Peruvian','604','new sol','PEN','céntimo','S/.','Republic of Peru','PE','PER','Peru','019','005',0,'51','PE.png'),(608,'Manila','Filipino','608','Philippine peso','PHP','centavo','Php','Republic of the Philippines','PH','PHL','Philippines','142','035',0,'63','PH.png'),(612,'Adamstown','Pitcairner','612','New Zealand dollar','NZD','cent','$','Pitcairn Islands','PN','PCN','Pitcairn','009','061',0,'649','PN.png'),(616,'Warsaw','Polish','616','zloty','PLN','grosz (pl. groszy)','zł','Republic of Poland','PL','POL','Poland','150','151',1,'48','PL.png'),(620,'Lisbon','Portuguese','620','euro','EUR','cent','€','Portuguese Republic','PT','PRT','Portugal','150','039',1,'351','PT.png'),(624,'Bissau','Guinea-Bissau national','624','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Guinea-Bissau','GW','GNB','Guinea-Bissau','002','011',0,'245','GW.png'),(626,'Dili','East Timorese','626','US dollar','USD','cent','$','Democratic Republic of East Timor','TL','TLS','Timor-Leste','142','035',0,'670','TL.png'),(630,'San Juan','Puerto Rican','630','US dollar','USD','cent','$','Commonwealth of Puerto Rico','PR','PRI','Puerto Rico','019','029',0,'1','PR.png'),(634,'Doha','Qatari','634','Qatari riyal','QAR','dirham','﷼','State of Qatar','QA','QAT','Qatar','142','145',0,'974','QA.png'),(638,'Saint-Denis','Reunionese','638','euro','EUR','cent','€','Réunion','RE','REU','Réunion','002','014',0,'262','RE.png'),(642,'Bucharest','Romanian','642','Romanian leu (pl. lei)','RON','ban (pl. bani)','lei','Romania','RO','ROU','Romania','150','151',1,'40','RO.png'),(643,'Moscow','Russian','643','Russian rouble','RUB','kopek','руб','Russian Federation','RU','RUS','Russian Federation','150','151',0,'7','RU.png'),(646,'Kigali','Rwandan; Rwandese','646','Rwandese franc','RWF','centime','RWF','Republic of Rwanda','RW','RWA','Rwanda','002','014',0,'250','RW.png'),(652,'Gustavia','of Saint Barthélemy','652','euro','EUR','cent',NULL,'Collectivity of Saint Barthélemy','BL','BLM','Saint Barthélemy','019','029',0,'590',NULL),(654,'Jamestown','Saint Helenian','654','Saint Helena pound','SHP','penny','£','Saint Helena, Ascension and Tristan da Cunha','SH','SHN','Saint Helena, Ascension and Tristan da Cunha','002','011',0,'290','SH.png'),(659,'Basseterre','Kittsian; Nevisian','659','East Caribbean dollar','XCD','cent','$','Federation of Saint Kitts and Nevis','KN','KNA','Saint Kitts and Nevis','019','029',0,'1','KN.png'),(660,'The Valley','Anguillan','660','East Caribbean dollar','XCD','cent','$','Anguilla','AI','AIA','Anguilla','019','029',0,'1','AI.png'),(662,'Castries','Saint Lucian','662','East Caribbean dollar','XCD','cent','$','Saint Lucia','LC','LCA','Saint Lucia','019','029',0,'1','LC.png'),(663,'Marigot','of Saint Martin','663','euro','EUR','cent',NULL,'Collectivity of Saint Martin','MF','MAF','Saint Martin (French part)','019','029',0,'590',NULL),(666,'Saint-Pierre','St-Pierrais; Miquelonnais','666','euro','EUR','cent','€','Territorial Collectivity of Saint Pierre and Miquelon','PM','SPM','Saint Pierre and Miquelon','019','021',0,'508','PM.png'),(670,'Kingstown','Vincentian','670','East Caribbean dollar','XCD','cent','$','Saint Vincent and the Grenadines','VC','VCT','Saint Vincent and the Grenadines','019','029',0,'1','VC.png'),(674,'San Marino','San Marinese','674','euro','EUR ','cent','€','Republic of San Marino','SM','SMR','San Marino','150','039',0,'378','SM.png'),(678,'São Tomé','São Toméan','678','dobra','STD','centavo','Db','Democratic Republic of São Tomé and Príncipe','ST','STP','Sao Tome and Principe','002','017',0,'239','ST.png'),(682,'Riyadh','Saudi Arabian','682','riyal','SAR','halala','﷼','Kingdom of Saudi Arabia','SA','SAU','Saudi Arabia','142','145',0,'966','SA.png'),(686,'Dakar','Senegalese','686','CFA franc (BCEAO)','XOF','centime','XOF','Republic of Senegal','SN','SEN','Senegal','002','011',0,'221','SN.png'),(688,'Belgrade','Serb','688','Serbian dinar','RSD','para (inv.)',NULL,'Republic of Serbia','RS','SRB','Serbia','150','039',0,'381',NULL),(690,'Victoria','Seychellois','690','Seychelles rupee','SCR','cent','₨','Republic of Seychelles','SC','SYC','Seychelles','002','014',0,'248','SC.png'),(694,'Freetown','Sierra Leonean','694','leone','SLL','cent','Le','Republic of Sierra Leone','SL','SLE','Sierra Leone','002','011',0,'232','SL.png'),(702,'Singapore','Singaporean','702','Singapore dollar','SGD','cent','$','Republic of Singapore','SG','SGP','Singapore','142','035',0,'65','SG.png'),(703,'Bratislava','Slovak','703','euro','EUR','cent','Sk','Slovak Republic','SK','SVK','Slovakia','150','151',1,'421','SK.png'),(704,'Hanoi','Vietnamese','704','dong','VND','(10 hào','₫','Socialist Republic of Vietnam','VN','VNM','Viet Nam','142','035',0,'84','VN.png'),(705,'Ljubljana','Slovene','705','euro','EUR','cent','€','Republic of Slovenia','SI','SVN','Slovenia','150','039',1,'386','SI.png'),(706,'Mogadishu','Somali','706','Somali shilling','SOS','cent','S','Somali Republic','SO','SOM','Somalia','002','014',0,'252','SO.png'),(710,'Pretoria (ZA1)','South African','710','rand','ZAR','cent','R','Republic of South Africa','ZA','ZAF','South Africa','002','018',0,'27','ZA.png'),(716,'Harare','Zimbabwean','716','Zimbabwe dollar (ZW1)','ZWL','cent','Z$','Republic of Zimbabwe','ZW','ZWE','Zimbabwe','002','014',0,'263','ZW.png'),(724,'Madrid','Spaniard','724','euro','EUR','cent','€','Kingdom of Spain','ES','ESP','Spain','150','039',1,'34','ES.png'),(728,'Juba','South Sudanese','728','South Sudanese pound','SSP','piaster',NULL,'Republic of South Sudan','SS','SSD','South Sudan','002','015',0,'211',NULL),(729,'Khartoum','Sudanese','729','Sudanese pound','SDG','piastre',NULL,'Republic of the Sudan','SD','SDN','Sudan','002','015',0,'249',NULL),(732,'Al aaiun','Sahrawi','732','Moroccan dirham','MAD','centime','MAD','Western Sahara','EH','ESH','Western Sahara','002','015',0,'212','EH.png'),(740,'Paramaribo','Surinamese','740','Surinamese dollar','SRD','cent','$','Republic of Suriname','SR','SUR','Suriname','019','005',0,'597','SR.png'),(744,'Longyearbyen','of Svalbard','744','Norwegian krone (pl. kroner)','NOK','øre (inv.)','kr','Svalbard and Jan Mayen','SJ','SJM','Svalbard and Jan Mayen','150','154',0,'47','SJ.png'),(748,'Mbabane','Swazi','748','lilangeni','SZL','cent','SZL','Kingdom of Swaziland','SZ','SWZ','Swaziland','002','018',0,'268','SZ.png'),(752,'Stockholm','Swedish','752','krona (pl. kronor)','SEK','öre (inv.)','kr','Kingdom of Sweden','SE','SWE','Sweden','150','154',1,'46','SE.png'),(756,'Berne','Swiss','756','Swiss franc','CHF','centime','CHF','Swiss Confederation','CH','CHE','Switzerland','150','155',1,'41','CH.png'),(760,'Damascus','Syrian','760','Syrian pound','SYP','piastre','£','Syrian Arab Republic','SY','SYR','Syrian Arab Republic','142','145',0,'963','SY.png'),(762,'Dushanbe','Tajik','762','somoni','TJS','diram','TJS','Republic of Tajikistan','TJ','TJK','Tajikistan','142','143',0,'992','TJ.png'),(764,'Bangkok','Thai','764','baht (inv.)','THB','satang (inv.)','฿','Kingdom of Thailand','TH','THA','Thailand','142','035',0,'66','TH.png'),(768,'Lomé','Togolese','768','CFA franc (BCEAO)','XOF','centime','XOF','Togolese Republic','TG','TGO','Togo','002','011',0,'228','TG.png'),(772,'(TK2)','Tokelauan','772','New Zealand dollar','NZD','cent','$','Tokelau','TK','TKL','Tokelau','009','061',0,'690','TK.png'),(776,'Nuku’alofa','Tongan','776','pa’anga (inv.)','TOP','seniti (inv.)','T$','Kingdom of Tonga','TO','TON','Tonga','009','061',0,'676','TO.png'),(780,'Port of Spain','Trinidadian; Tobagonian','780','Trinidad and Tobago dollar','TTD','cent','TT$','Republic of Trinidad and Tobago','TT','TTO','Trinidad and Tobago','019','029',0,'1','TT.png'),(784,'Abu Dhabi','Emirian','784','UAE dirham','AED','fils (inv.)','AED','United Arab Emirates','AE','ARE','United Arab Emirates','142','145',0,'971','AE.png'),(788,'Tunis','Tunisian','788','Tunisian dinar','TND','millime','TND','Republic of Tunisia','TN','TUN','Tunisia','002','015',0,'216','TN.png'),(792,'Ankara','Turk','792','Turkish lira (inv.)','TRY','kurus (inv.)','YTL','Republic of Turkey','TR','TUR','Turkey','142','145',0,'90','TR.png'),(795,'Ashgabat','Turkmen','795','Turkmen manat (inv.)','TMT','tenge (inv.)','m','Turkmenistan','TM','TKM','Turkmenistan','142','143',0,'993','TM.png'),(796,'Cockburn Town','Turks and Caicos Islander','796','US dollar','USD','cent','$','Turks and Caicos Islands','TC','TCA','Turks and Caicos Islands','019','029',0,'1','TC.png'),(798,'Funafuti','Tuvaluan','798','Australian dollar','AUD','cent','$','Tuvalu','TV','TUV','Tuvalu','009','061',0,'688','TV.png'),(800,'Kampala','Ugandan','800','Uganda shilling','UGX','cent','UGX','Republic of Uganda','UG','UGA','Uganda','002','014',0,'256','UG.png'),(804,'Kiev','Ukrainian','804','hryvnia','UAH','kopiyka','₴','Ukraine','UA','UKR','Ukraine','150','151',0,'380','UA.png'),(807,'Skopje','of the former Yugoslav Republic of Macedonia','807','denar (pl. denars)','MKD','deni (inv.)','ден','the former Yugoslav Republic of Macedonia','MK','MKD','Macedonia, the former Yugoslav Republic of','150','039',0,'389','MK.png'),(818,'Cairo','Egyptian','818','Egyptian pound','EGP','piastre','£','Arab Republic of Egypt','EG','EGY','Egypt','002','015',0,'20','EG.png'),(826,'London','British','826','pound sterling','GBP','penny (pl. pence)','£','United Kingdom of Great Britain and Northern Ireland','GB','GBR','United Kingdom','150','154',1,'44','GB.png'),(831,'St Peter Port','of Guernsey','831','Guernsey pound (GG2)','GGP (GG2)','penny (pl. pence)',NULL,'Bailiwick of Guernsey','GG','GGY','Guernsey','150','154',0,'44',NULL),(832,'St Helier','of Jersey','832','Jersey pound (JE2)','JEP (JE2)','penny (pl. pence)',NULL,'Bailiwick of Jersey','JE','JEY','Jersey','150','154',0,'44',NULL),(833,'Douglas','Manxman; Manxwoman','833','Manx pound (IM2)','IMP (IM2)','penny (pl. pence)',NULL,'Isle of Man','IM','IMN','Isle of Man','150','154',0,'44',NULL),(834,'Dodoma (TZ1)','Tanzanian','834','Tanzanian shilling','TZS','cent','TZS','United Republic of Tanzania','TZ','TZA','Tanzania, United Republic of','002','014',0,'255','TZ.png'),(840,'Washington DC','American','840','US dollar','USD','cent','$','United States of America','US','USA','United States','019','021',0,'1','US.png'),(850,'Charlotte Amalie','US Virgin Islander','850','US dollar','USD','cent','$','United States Virgin Islands','VI','VIR','Virgin Islands, U.S.','019','029',0,'1','VI.png'),(854,'Ouagadougou','Burkinabe','854','CFA franc (BCEAO)','XOF','centime','XOF','Burkina Faso','BF','BFA','Burkina Faso','002','011',0,'226','BF.png'),(858,'Montevideo','Uruguayan','858','Uruguayan peso','UYU','centésimo','$U','Eastern Republic of Uruguay','UY','URY','Uruguay','019','005',0,'598','UY.png'),(860,'Tashkent','Uzbek','860','sum (inv.)','UZS','tiyin (inv.)','лв','Republic of Uzbekistan','UZ','UZB','Uzbekistan','142','143',0,'998','UZ.png'),(862,'Caracas','Venezuelan','862','bolívar fuerte (pl. bolívares fuertes)','VEF','céntimo','Bs','Bolivarian Republic of Venezuela','VE','VEN','Venezuela, Bolivarian Republic of','019','005',0,'58','VE.png'),(876,'Mata-Utu','Wallisian; Futunan; Wallis and Futuna Islander','876','CFP franc','XPF','centime','XPF','Wallis and Futuna','WF','WLF','Wallis and Futuna','009','061',0,'681','WF.png'),(882,'Apia','Samoan','882','tala (inv.)','WST','sene (inv.)','WS$','Independent State of Samoa','WS','WSM','Samoa','009','061',0,'685','WS.png'),(887,'San’a','Yemenite','887','Yemeni rial','YER','fils (inv.)','﷼','Republic of Yemen','YE','YEM','Yemen','142','145',0,'967','YE.png'),(894,'Lusaka','Zambian','894','Zambian kwacha (inv.)','ZMW','ngwee (inv.)','ZK','Republic of Zambia','ZM','ZMB','Zambia','002','014',0,'260','ZM.png');
/*!40000 ALTER TABLE `countries` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `migrations`
--

DROP TABLE IF EXISTS `migrations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `migrations` (
  `migration` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `batch` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `migrations`
--

LOCK TABLES `migrations` WRITE;
/*!40000 ALTER TABLE `migrations` DISABLE KEYS */;
INSERT INTO `migrations` VALUES ('2014_10_12_000000_create_users_table',1),('2014_10_12_100000_create_password_resets_table',1),('2015_11_05_190606_setup_countries_table',1),('2015_11_05_190607_charify_countries_table',1),('2015_11_08_211352_servers',1),('2015_11_09_225525_vpnusers',1),('2015_11_14_113135_zones',1),('2015_11_29_113135_randomservers',1),('2015_12_22_113135_vpngroups',1),('2016_01_14_113135_vpnusersgroups',1),('2016_02_03_134600_serversvpngroups',1),('2016_02_20_144600_oldservers',1);
/*!40000 ALTER TABLE `migrations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `oldservers`
--

DROP TABLE IF EXISTS `oldservers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `oldservers` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL,
  `machine_id` int(11) DEFAULT NULL,
  `zone` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `true_zone` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `provider` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `ip` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `random` tinyint(1) NOT NULL DEFAULT '0',
  `token` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `time` double(8,2) NOT NULL DEFAULT '0.00',
  `transfer` int(11) NOT NULL DEFAULT '0',
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `oldservers_user_id_foreign` (`user_id`),
  CONSTRAINT `oldservers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `oldservers`
--

LOCK TABLES `oldservers` WRITE;
/*!40000 ALTER TABLE `oldservers` DISABLE KEYS */;
INSERT INTO `oldservers` VALUES (1,1,11314642,'3','lon1','DigitalOcean','uk.alvaro.castellano.vela.vpn.windmaker.net','188.166.149.170',0,'LrniZ9HHZNHWxG9bquCg0iTPWlFrQO0BjGYTvsPNGoKPYSZ829A3gsnZuC1Z',0.00,0,'2016-02-21 12:33:36','2016-02-21 12:33:36'),(2,1,11318907,'0','nyc3','DigitalOcean','usa.alvaro.castellano.vela.vpn.windmaker.net','159.203.97.48',0,'j1ydSDsCWXGuUc5l85NyQUJwnk2BtV5RZu8tcjxPXh80SrApOtzOJ6BOV5ih',0.00,0,'2016-02-21 18:02:22','2016-02-21 18:02:22'),(3,1,11385461,'4','ams2','DigitalOcean','ams.alvaro.castellano.vela.vpn.windmaker.net','198.211.126.13',0,'AEG4vwvzAvzKIDVBzmaZ84c69ZtY4eQ8qQKY9a6FnNAmT3YmLV4hE4Fgp2ST',0.00,0,'2016-02-23 15:45:54','2016-02-23 15:45:54');
/*!40000 ALTER TABLE `oldservers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `password_resets`
--

DROP TABLE IF EXISTS `password_resets`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `password_resets` (
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `token` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `password_resets_email_index` (`email`),
  KEY `password_resets_token_index` (`token`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `password_resets`
--

LOCK TABLES `password_resets` WRITE;
/*!40000 ALTER TABLE `password_resets` DISABLE KEYS */;
/*!40000 ALTER TABLE `password_resets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `randomservers`
--

DROP TABLE IF EXISTS `randomservers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `randomservers` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL,
  `number` int(11) NOT NULL,
  `requested` int(11) NOT NULL,
  `used` int(11) NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `randomservers_user_id_foreign` (`user_id`),
  CONSTRAINT `randomservers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `randomservers`
--

LOCK TABLES `randomservers` WRITE;
/*!40000 ALTER TABLE `randomservers` DISABLE KEYS */;
/*!40000 ALTER TABLE `randomservers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `servers`
--

DROP TABLE IF EXISTS `servers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `servers` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL,
  `machine_id` int(11) DEFAULT NULL,
  `zone` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `true_zone` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `provider` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `status` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `ip` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  `random` tinyint(1) NOT NULL DEFAULT '0',
  `token` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `time` double(8,2) NOT NULL DEFAULT '0.00',
  `transfer` int(11) NOT NULL DEFAULT '0',
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `servers_user_id_foreign` (`user_id`),
  CONSTRAINT `servers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `servers`
--

LOCK TABLES `servers` WRITE;
/*!40000 ALTER TABLE `servers` DISABLE KEYS */;
INSERT INTO `servers` VALUES (5,1,NULL,'1',NULL,NULL,NULL,'',NULL,0,'AZwXqz7ju2xkwDTeqjuxtoAdiDywNslcI3m0mbtxp3dqmRVW8wWmkTpeg3RZ',0.00,0,'2016-02-26 15:13:10','2016-02-26 15:13:10'),(6,1,NULL,'4',NULL,NULL,NULL,'',NULL,0,'ee9pDcnGvockCoIt8goIW9aJ24JUgJpuANwQjsfA4nXl7qM6eXfp0QaXvdIy',0.00,0,'2016-02-26 15:31:14','2016-02-26 15:31:14');
/*!40000 ALTER TABLE `servers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `serversvpngroups`
--

DROP TABLE IF EXISTS `serversvpngroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `serversvpngroups` (
  `user_id` bigint(20) unsigned NOT NULL,
  `vpn_server_id` bigint(20) unsigned NOT NULL,
  `vpn_group_id` bigint(20) unsigned NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `serversvpngroups_user_id_index` (`user_id`),
  KEY `serversvpngroups_vpn_server_id_index` (`vpn_server_id`),
  KEY `serversvpngroups_vpn_group_id_index` (`vpn_group_id`),
  CONSTRAINT `serversvpngroups_vpn_group_id_foreign` FOREIGN KEY (`vpn_group_id`) REFERENCES `vpngroups` (`id`) ON DELETE CASCADE,
  CONSTRAINT `serversvpngroups_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE,
  CONSTRAINT `serversvpngroups_vpn_server_id_foreign` FOREIGN KEY (`vpn_server_id`) REFERENCES `servers` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `serversvpngroups`
--

LOCK TABLES `serversvpngroups` WRITE;
/*!40000 ALTER TABLE `serversvpngroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `serversvpngroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `first_name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `last_name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `country` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `credit` double(8,2) NOT NULL DEFAULT '0.00',
  `password` varchar(60) COLLATE utf8_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8_unicode_ci DEFAULT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `activated` tinyint(1) NOT NULL DEFAULT '0',
  `confirmation_code` varchar(255) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `users_username_unique` (`username`),
  UNIQUE KEY `users_email_unique` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'Alvaro','Castellano','724','alvaro.castellano.vela','alvaro.castellano.vela@gmail.com',0.00,'$2y$10$KunDAaMrK99sbxupw73ACuIA0Ba.QYUKFbYWNvHVSkF7FvuJG8ggq',NULL,'2016-02-21 01:06:31','2016-02-21 01:06:47',1,NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vpngroups`
--

DROP TABLE IF EXISTS `vpngroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vpngroups` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `vpngroups_user_id_foreign` (`user_id`),
  CONSTRAINT `vpngroups_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vpngroups`
--

LOCK TABLES `vpngroups` WRITE;
/*!40000 ALTER TABLE `vpngroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `vpngroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vpnusers`
--

DROP TABLE IF EXISTS `vpnusers`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vpnusers` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` bigint(20) unsigned NOT NULL,
  `name` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(60) COLLATE utf8_unicode_ci NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`id`),
  KEY `vpnusers_user_id_foreign` (`user_id`),
  CONSTRAINT `vpnusers_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vpnusers`
--

LOCK TABLES `vpnusers` WRITE;
/*!40000 ALTER TABLE `vpnusers` DISABLE KEYS */;
INSERT INTO `vpnusers` VALUES (1,1,'test','pruebas123','2016-02-21 11:38:27','2016-02-21 11:38:27');
/*!40000 ALTER TABLE `vpnusers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `vpnusersgroups`
--

DROP TABLE IF EXISTS `vpnusersgroups`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `vpnusersgroups` (
  `user_id` bigint(20) unsigned NOT NULL,
  `vpn_user_id` bigint(20) unsigned NOT NULL,
  `vpn_group_id` bigint(20) unsigned NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `updated_at` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  KEY `vpnusersgroups_user_id_index` (`user_id`),
  KEY `vpnusersgroups_vpn_user_id_index` (`vpn_user_id`),
  KEY `vpnusersgroups_vpn_group_id_index` (`vpn_group_id`),
  CONSTRAINT `vpnusersgroups_vpn_group_id_foreign` FOREIGN KEY (`vpn_group_id`) REFERENCES `vpngroups` (`id`) ON DELETE CASCADE,
  CONSTRAINT `vpnusersgroups_user_id_foreign` FOREIGN KEY (`user_id`) REFERENCES `users` (`id`) ON DELETE CASCADE,
  CONSTRAINT `vpnusersgroups_vpn_user_id_foreign` FOREIGN KEY (`vpn_user_id`) REFERENCES `vpnusers` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `vpnusersgroups`
--

LOCK TABLES `vpnusersgroups` WRITE;
/*!40000 ALTER TABLE `vpnusersgroups` DISABLE KEYS */;
/*!40000 ALTER TABLE `vpnusersgroups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `zones`
--

DROP TABLE IF EXISTS `zones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `zones` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `zonename` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `zones`
--

LOCK TABLES `zones` WRITE;
/*!40000 ALTER TABLE `zones` DISABLE KEYS */;
INSERT INTO `zones` VALUES (1,'USA'),(2,'Germany'),(3,'Singapore'),(4,'United Kingdom'),(5,'Netherlands'),(6,'Canada');
/*!40000 ALTER TABLE `zones` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-02-26 17:31:43
