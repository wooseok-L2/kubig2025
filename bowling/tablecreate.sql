-- MySQL 테이블 생성을 위한 간소화된 쿼리문
-- 데이터베이스 생성 (없는 경우)
CREATE DATABASE IF NOT EXISTS bowling_db;
grant all privileges on bowling_db.* to 'myuser' @'%';
-- 데이터베이스 선택
USE bowling_db;
-- 점수 기록용 테이블 생성 - 사용자 이름, 날짜, 점수를 저장
CREATE TABLE IF NOT EXISTS score_records (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    play_date DATE NOT NULL,
    score INT NOT NULL
);
USE bowling_db;
-- 사용자 월별 통계 테이블 - 집계용 (C 프로그램에서 업데이트)
CREATE TABLE IF NOT EXISTS user_monthly_stats (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    year INT NOT NULL,
    month INT NOT NULL,
    play_count INT NOT NULL DEFAULT 0,
    -- 유니크 제약조건 (사용자-연도-월 조합은 중복될 수 없음)
    UNIQUE KEY unique_user_month (username, year, month)
);
-- 샘플 데이터 삽입 (테스트용)
use bowling_db;
INSERT INTO score_records (username, play_date, score)
VALUES ('player1', '2023-04-01', 180),
    ('player1', '2023-04-05', 210),
    ('player1', '2023-04-10', 190),
    ('player1', '2023-04-15', 200),
    ('player1', '2023-04-20', 170),
    ('player1', '2023-04-25', 160),
    ('player1', '2023-05-02', 195),
    ('player1', '2023-05-07', 180),
    ('player1', '2023-05-12', 200),
    ('player1', '2023-05-17', 210),
    ('player1', '2023-05-22', 190),
    ('player1', '2023-05-27', 185),
    ('player2', '2023-04-03', 150),
    ('player2', '2023-04-08', 160),
    ('player2', '2023-04-13', 170),
    ('player2', '2023-04-18', 180),
    ('player2', '2023-04-23', 175),
    ('player2', '2023-04-28', 165),
    ('player2', '2023-05-01', 155),
    ('player2', '2023-05-06', 160),
    ('player2', '2023-05-11', 170),
    ('player2', '2023-05-16', 180),
    ('player2', '2023-05-21', 175),
    ('player2', '2023-05-26', 165),
    ('player3', '2023-04-02', 220),
    ('player3', '2023-04-07', 210),
    ('player3', '2023-04-12', 200),
    ('player3', '2023-04-17', 190),
    ('player3', '2023-04-22', 180),
    ('player3', '2023-04-27', 170),
    ('player3', '2023-05-02', 220),
    ('player3', '2023-05-07', 210),
    ('player3', '2023-05-12', 200),
    ('player3', '2023-05-17', 190),
    ('player3', '2023-05-22', 180),
    ('player3', '2023-05-27', 170);
-- C 프로그램에서 사용할 수 있는 쿼리 예시:
-- 1. 새 게임 점수 기록하기:
-- INSERT INTO score_records (username, play_date, score) VALUES ('사용자명', CURDATE(), 점수);
-- 2. 월별 통계 업데이트하기:
-- INSERT INTO user_monthly_stats (username, year, month, play_count)
-- SELECT username, YEAR(play_date), MONTH(play_date), COUNT(*)
-- FROM score_records
-- GROUP BY username, YEAR(play_date), MONTH(play_date)
-- ON DUPLICATE KEY UPDATE play_count = VALUES(play_count);
-- 3. 특정 사용자의 기록 조회:
-- SELECT * FROM score_records WHERE username = '사용자명' ORDER BY play_date DESC;
-- 4. 특정 월의 모든 게임 조회:
-- SELECT * FROM score_records WHERE YEAR(play_date) = 연도 AND MONTH(play_date) = 월;
-- 5. 사용자별 월간 플레이 횟수 조회:
-- SELECT * FROM user_monthly_stats WHERE username = '사용자명' ORDER BY year DESC, month DESC;
use bowling_db;
select *
from score_records;