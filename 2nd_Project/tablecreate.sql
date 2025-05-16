-- MySQL 테이블 생성을 위한 간소화된 쿼리문
-- 데이터베이스 생성 (없는 경우)
CREATE DATABASE IF NOT EXISTS parking_db;
grant all privileges on parking_db.* to 'myuser' @'%';
-- 데이터베이스 선택
USE parking_db;
CREATE TABLE parking_log (
    RFID_num VARCHAR(20) PRIMARY KEY,  -- RFID 번호 (고유 ID)
    entry_time DATETIME NOT NULL,      -- 입차 시간
    exit_time DATETIME DEFAULT NULL,   -- 출차 시간 (출차 전에는 NULL)
    total_usage_time TIME DEFAULT NULL, -- 총 이용 시간 (분 단위, 출차 후 계산)
    current_status ENUM('입차', '출차') NOT NULL  -- 현재 상태 ('입차' 또는 '출차')
);

CREATE TABLE parking_slots (
    slot_number VARCHAR(5) NOT NULL PRIMARY KEY, -- 주차칸 번호 (예: A1, B2)
    status ENUM('사용 중', '비어 있음') NOT NULL DEFAULT '비어 있음', -- 현재 상태
    entry_time DATETIME DEFAULT NULL, -- 입차 시간
    exit_time DATETIME DEFAULT NULL -- 출차 시간
);

-- 샘플 데이터 삽입 (테스트용)
use parking_db;
-- 입차 시 INSERT (새로운 행 추가)
INSERT INTO parking_log (RFID_num, entry_time, current_status)
VALUES ('1234567890', NOW(), '입차');
-- 출차 시 UPDATE (기존 행 수정)
UPDATE parking_log 
SET exit_time = NOW(), 
    total_usage_time = SEC_TO_TIME(TIMESTAMPDIFF(SECOND, entry_time, NOW())), 
    current_status = '출차'
WHERE RFID_num = '1234567890' AND current_status = '입차';

use parking_db;
INSERT INTO parking_log (RFID_num, entry_time, current_status)
VALUES ('3456789012', NOW(), '입차');

use parking_db;
UPDATE parking_log 
SET exit_time = NOW(), 
    total_usage_time = SEC_TO_TIME(TIMESTAMPDIFF(SECOND, entry_time, NOW())), 
    current_status = '출차'
WHERE RFID_num = '3456789012' AND current_status = '입차';

-- 샘플 데이터 삽입 (테스트용)
use parking_db;
-- 입차 시 INSERT (새로운 행 추가)
INSERT INTO parking_slots (slot_number, status, entry_time)
VALUES ('A1', '사용 중', NOW());
-- 출차 시 UPDATE (기존 행 수정)
UPDATE parking_slots 
SET status = '비어 있음', exit_time = NOW()
WHERE slot_number = 'A1';

use parking_db;
INSERT INTO parking_slots (slot_number, status, entry_time)
VALUES ('A3', '사용 중', NOW());

use parking_db;
ALTER TABLE parking_log
MODIFY total_usage_time TIME;

use parking_db;
UPDATE parking_log
SET total_usage_time = SEC_TO_TIME(TIMESTAMPDIFF(SECOND, entry_time, NOW()));

use parking_db;
TRUNCATE TABLE parking_log;

use parking_db;
select *
from parking_log;

-- drop DATABASE parking_db;