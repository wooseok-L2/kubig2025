-- MySQL 테이블 생성을 위한 간소화된 쿼리문
-- 데이터베이스 생성 (없는 경우)
CREATE DATABASE IF NOT EXISTS smartfarm_db;
grant all privileges on smartfarm_db.* to 'myuser'@'%';
-- 데이터베이스 선택
USE smartfarm_db;
CREATE TABLE IF NOT EXISTS data_records (
    Time DATETIME NOT NULL PRIMARY KEY,
    Temperature INT NOT NULL,
    Humidity INT NOT NULL,
    SoilMoisture INT NOT NULL,
    Sunshine INT NOT NULL,
    Cond VARCHAR(20) NOT NULL
);
USE smartfarm_db;
CREATE TABLE IF NOT EXISTS hour_stats (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Month INT NOT NULL,
    Day INT NOT NULL,
    Hour INT NOT NULL,
    Temperature INT NOT NULL,
    Humidity INT NOT NULL,
    SoilMoisture INT NOT NULL,
    Sunshine INT NOT NULL
);
-- 샘플 데이터 삽입 (테스트용)
use smartfarm_db;
INSERT INTO data_records (Time, Temperature, Humidity, SoilMoisture, Sunshine, cond)
VALUES ('2023-04-01 22:15:44',20, 50, 180, 120, 'good'),
    ('2023-04-05 12:12:11', 25, 70, 210, 120, 'bad'),
    ('2023-04-10 13:12:45', 15, 80, 190, 210, 'good'),
    ('2023-04-15 15:54:54', 17, 60, 200, 241, 'good'),
    ('2023-04-20 18:45:48', 21, 50, 170, 141, 'bad'),
    ('2023-04-25 19:45:45', 32, 40, 160, 112, 'bad'),
    ('2023-05-02 20:58:45', 35, 78, 195, 145, 'good'),
    ('2023-05-07 08:05:20', 24, 25, 180, 156, 'bad'),
    ('2023-05-12 09:45:45', 20, 32, 200, 241, 'good'),
    ('2023-05-17 10:25:15', 26, 52, 210, 231, 'bad'),
    ('2023-05-22 14:25:54', 29, 72, 190, 145, 'bad'),
    ('2023-05-27 12:45:44', 32, 82, 185, 175, 'good'),
    ('2023-04-03 12:35:44', 35, 90, 150, 144, 'bad'),
    ('2023-04-08 13:45:45', 28, 57, 160, 121, 'bad'),
    ('2023-04-13 14:45:53', 26, 54, 170, 119, 'good'),
    ('2023-04-18 17:45:32', 18, 50, 180, 111, 'good'),
    ('2023-04-23 15:10:10', 10, 30, 175, 222, 'good'),
    ('2023-04-28 23:45:41', 35, 75, 165, 212, 'bad'),
    ('2023-05-01 00:45:44', 27, 65, 155, 121, 'bad')


use smartfarm_db;
select *    
from data_records;
--DATE_FORMAT(Time, '%Y-%m-%d %H:%i:%s') as Time


use smartfarm_db;
DROP TABLE IF EXISTS hour_stats;

use smartfarm_db;
DELETE FROM data_records;
