/*
 Navicat Premium Data Transfer

 Source Server         : termsystem
 Source Server Type    : MySQL
 Source Server Version : 50743
 Source Host           : localhost:3306
 Source Schema         : termsystem

 Target Server Type    : MySQL
 Target Server Version : 50743
 File Encoding         : 65001

 Date: 18/02/2025 18:11:21
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for alembic_version
-- ----------------------------
DROP TABLE IF EXISTS `alembic_version`;
CREATE TABLE `alembic_version`  (
  `version_num` varchar(32) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`version_num`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for classbytermchart
-- ----------------------------
DROP TABLE IF EXISTS `classbytermchart`;
CREATE TABLE `classbytermchart`  (
  `term` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `grade` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `type` tinyint(1) NOT NULL,
  `classNameList` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failedNum` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failedRate` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `totalNum` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`term`, `grade`, `type`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for classbytermtable
-- ----------------------------
DROP TABLE IF EXISTS `classbytermtable`;
CREATE TABLE `classbytermtable`  (
  `className` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `term` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `totalNum` int(11) NOT NULL,
  `failedNum` int(11) NOT NULL,
  `failedThreeNum` int(11) NOT NULL,
  `failedNum2` int(11) NOT NULL,
  `failedRate` float NOT NULL,
  `failedRange` float NOT NULL,
  PRIMARY KEY (`className`, `term`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for coursebytermtable
-- ----------------------------
DROP TABLE IF EXISTS `coursebytermtable`;
CREATE TABLE `coursebytermtable`  (
  `id` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `term` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `courseName` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failed_nums` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gradeDistribute` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `pass_rate` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failStudentsList` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `sumFailedNums` int(11) NOT NULL,
  PRIMARY KEY (`id`, `term`, `courseName`, `major`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for courses
-- ----------------------------
DROP TABLE IF EXISTS `courses`;
CREATE TABLE `courses`  (
  `courseName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `credit` float NOT NULL,
  `term` int(11) NOT NULL,
  `grade` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `type` int(5) NOT NULL DEFAULT 0,
  PRIMARY KEY (`courseName`, `term`, `grade`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for excellentstudyclass
-- ----------------------------
DROP TABLE IF EXISTS `excellentstudyclass`;
CREATE TABLE `excellentstudyclass`  (
  `grade` int(11) NOT NULL,
  `year` int(11) NOT NULL,
  `totalClassNum` int(11) NULL DEFAULT NULL,
  `excellentClassNum` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`grade`, `year`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for filedb
-- ----------------------------
DROP TABLE IF EXISTS `filedb`;
CREATE TABLE `filedb`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `fileName` varchar(40) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `md5` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `owner_id` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `fileType` varchar(3) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `ix_filedb_id`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for gradebyterm
-- ----------------------------
DROP TABLE IF EXISTS `gradebyterm`;
CREATE TABLE `gradebyterm`  (
  `term` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `grade` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `courseName` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failed_nums` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failed_rates` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`term`, `grade`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for majorchart
-- ----------------------------
DROP TABLE IF EXISTS `majorchart`;
CREATE TABLE `majorchart`  (
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gradeNameList` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gradeFailedNum` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gradeFailedRate` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `gradeTotalNum` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `classNameList` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failedNum` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `failedRate` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `totalNum` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `showLabel` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`major`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for resultreadstate
-- ----------------------------
DROP TABLE IF EXISTS `resultreadstate`;
CREATE TABLE `resultreadstate`  (
  `key` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`key`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for scores
-- ----------------------------
DROP TABLE IF EXISTS `scores`;
CREATE TABLE `scores`  (
  `stuID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `courseName` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `score` int(20) NOT NULL,
  `failed` tinyint(1) NOT NULL,
  `grade` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `term` int(10) NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`stuID`, `courseName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for stuanalysis
-- ----------------------------
DROP TABLE IF EXISTS `stuanalysis`;
CREATE TABLE `stuanalysis`  (
  `stuID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuName` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuType` int(11) NOT NULL,
  `term` int(11) NOT NULL,
  `failSubjectName` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `stuClass` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `content1` varchar(850) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `content2` varchar(850) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `content3` varchar(850) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`stuID`, `stuType`, `term`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for studentinfo
-- ----------------------------
DROP TABLE IF EXISTS `studentinfo`;
CREATE TABLE `studentinfo`  (
  `stuID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `grade` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuName` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuClass` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `totalWeightedScore` float NULL DEFAULT NULL,
  `failedSubjectNames` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `failedSubjectTermNames` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `failedSubjectNums` int(11) NULL DEFAULT NULL,
  `sumFailedCreditALL` float NULL DEFAULT NULL,
  `totalCreditALL` float NULL DEFAULT NULL,
  `sumFailedCreditUnclassified` float NULL DEFAULT NULL,
  `totalCreditUnclassified` float NULL DEFAULT NULL,
  `sumFailedCreditPublicCompulsory` float NULL DEFAULT NULL,
  `totalCreditPublicCompulsory` float NULL DEFAULT NULL,
  `sumFailedCreditProfessionalCompulsory` float NULL DEFAULT NULL,
  `totalCreditProfessionalCompulsory` float NULL DEFAULT NULL,
  `sumFailedCreditProfessionalElective` float NULL DEFAULT NULL,
  `totalCreditProfessionalElective` float NULL DEFAULT NULL,
  `sumFailedCreditPublicElective` float NULL DEFAULT NULL,
  `totalCreditPublicElective` float NULL DEFAULT NULL,
  `failedSubjectNumsTerm` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `totalWeightedScoreTerm` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `totalFailedCreditTerm` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `totalCreditExcludePublicElective` float NULL DEFAULT NULL,
  `totalCreditIncludePublicElective` float NULL DEFAULT NULL,
  `requiredCreditExcludePublicElective` float NULL DEFAULT NULL,
  `requiredCreditIncludePublicElective` float NULL DEFAULT NULL,
  `excludePublicElectiveType` int(10) NULL DEFAULT NULL,
  `includePublicElectiveType` int(10) NULL DEFAULT NULL,
  PRIMARY KEY (`stuID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for studentinfoconfig
-- ----------------------------
DROP TABLE IF EXISTS `studentinfoconfig`;
CREATE TABLE `studentinfoconfig`  (
  `grade` varchar(2) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `redRate` float NOT NULL,
  `yellowRate` float NOT NULL,
  `requiredCreditExcludePublicElective` float NOT NULL,
  `requiredCreditIncludePublicElective` float NOT NULL,
  PRIMARY KEY (`grade`, `major`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for students
-- ----------------------------
DROP TABLE IF EXISTS `students`;
CREATE TABLE `students`  (
  `stuID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuName` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuClass` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`stuID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for teachers
-- ----------------------------
DROP TABLE IF EXISTS `teachers`;
CREATE TABLE `teachers`  (
  `tID` varchar(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tCourse` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `tClass` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`tID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `cID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '工号',
  `cName` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `hashed_password` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `is_active` tinyint(1) NULL DEFAULT NULL,
  `is_superuser` tinyint(1) NULL DEFAULT NULL,
  PRIMARY KEY (`cID`, `cName`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('admin', 'admin', '$2b$12$mYYomWAxvFsnRwZPScLS.uzajt7ne5RgzolgB4Loc7dCGKM9X/oGC', 1, 1);
INSERT INTO `user` VALUES ('test', 'test', '$2b$12$HN7sB5Gka7Qok7oRxPZFEeJ2ARzJ9NkkuGgquFk30131ixpdq7tWq', 1, 0);

-- ----------------------------
-- Table structure for weightscorebyterm
-- ----------------------------
DROP TABLE IF EXISTS `weightscorebyterm`;
CREATE TABLE `weightscorebyterm`  (
  `grade` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `term` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `info` longtext CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`grade`, `term`, `major`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for weightscores
-- ----------------------------
DROP TABLE IF EXISTS `weightscores`;
CREATE TABLE `weightscores`  (
  `stuID` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `stuName` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `score` float(20, 3) NOT NULL,
  `term` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `grade` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `major` varchar(5) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`stuID`, `term`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
