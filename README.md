# kuBig2025

이 저장소는 고려대 세종캠퍼스에서 C 수업을 할때 쓰는 저장소입니다.

---

## C 언어

---

---

## 2025-03-04

---

- 1교시
  - Vmware 설치
  - Ubuntu 22.04 설치
- 2교시
  - Github 계정 생성
  - Github 저장소 생성
  - Github 저장소 Clone
- 3교시
  - 리눅스 설명
- 4교시
  - 간단한 프로그램 작성 nano (infinit.c)
- 5교시
  - C 언어 설명
  - 자료형
  - 숫자형 - 정수형, 실수형
- 6교시
  - 온도 예제 작성 celcius2fahr.c
- 7교시
  - makefile 작성
  - make 실행
  - char 설명 및 예제 작성 charNumber.c
- 8교시
  - 복습 및 정리

---

## 2025-03-05

---

- 1교시
  - 복습
  - 구글 슬라이드 작성(교육생 페이지)
- 2교시
  - 연산자
  - 폰 노이만 머신
  - 메모리 연산
- 3교시
  - 연산자
    - 산술 연산자
    - 증감연산자 - 예제 (전위 후위)
    - 복합 대입연산자
  - 리터럴 상수
- 4교시
  - 리터럴 상수 예제 - literal.c
- 5교시
  - 연산자
    - 관계 연산자
    - 논리 연산자
    - 비트 연산자
- 6교시
  - 연산자 예제 작성 - genderRatio compare compare2 sizeof oddeven
- 7교시
  - 비트 연산자 예제 - fourBIt.c
- 8교시
  - 정리

---

## 2025-03-06

---

- 1교시
  - 복습
  - 시험 - 데이터베이스
- 2교시
  - 흐름 제어 설명
    - 조건문 : if, switch, if else
    - 반복문 : for, while, do while
- 3교시
  - if 문 예제 - absolute.c, leapYear.c
- 4교시
  - main argument 설명 argc, argv
- 5교시
  - 분기문 예제 - absolute leafYear passFail grade grade2 posZeroNeg bigLetter
- 6교시
  - for 문 설명
  - for 문 예제 - one2Ten.c, one2TenSum.c
- 7교시
  - 구구단 출력하기
  - 이중 for 문 예제 - start.c
- 8교시
  - 정리

---

## 2025-03-07

---

- 1교시
  - 복습
  - 반복문
- 2교시
  - while 문 설명
  - while 문 예제 - one2TenSumWhile.c
- 3교시
- 4교시
  - do while 문 설명
  - do while 문 예제 - one2TenSumDoWhile.c
- 5교시
  - 함수
  - 전역변수, 지역변수, 정적지역변수
- 6교시
  - break, continue 설명
  - break, continue 예제 - break.c, continue.c
  - 배열
- 7교시
  - 배열 예제 - dice.c, sumArray.c
  - 이중 배열
  - 이중 배열 예제 - sumMatrix.c findValueArray.c
- 8교시
  - baseball 게임 설명

---

## 2025-03-10

---

- 1교시
  - 복습
  - baseball 게임 - 정답 풀이
- 2교시
  - 배열 설명
  - swap 함수
- 3교시
  - 정렬 - 선택정렬, 버블정렬, qsort
- 4교시
  - endian 설명
  - 포인터, 이중 포인터 설명
- 5교시
  - 함수 포인터
  - 보이드 포인터
  - 배열과 포인터
- 6교시
  - 배열 과 포인터 예제
- 7교시
  - 함수에서 포인터를 쓰는 예제 - swapFunction sumArrayFunction sumMatrixFunction
- 8교시
  - sumMatrixFunction2 - 일차원 배열로 변경 해서 넘기기
  - 함수 에서 포인터가 쓰이는 종류 정리

---

## 2025-03-11

---

- 1교시
  - 복습
  - 함수 포인터
  - 분할 컴파일 - 현대 차 번호
- 2교시
  - 분할 컴파일 - 랜덤
  - makefile 로 분할 컴파일
- 3교시
  - 구조체 설명
- 4교시
  - date 구조체 예시
  - 다양한 선언
- 5교시
  - 문자열 - 문자열 상수, 문자열 배열
- 6교시
  - 문자열 함수 예제 - stringExample.c
  - 파일 생성- 파일 포인터, 파일 디스크립터
- 7교시
  - 문자열 라이브러리 작성
  - myString.h
- 8교시

---

## 2025-03-12

---

- 1교시
  - 복습
  - MySQL 설명
- 2교시
  - MySQL 설치
  - 권한 설정, DB 생성, TABLE 생성
  - MySQL 종료
- 3교시
  - root 계정으로 user 생성, 데이터베이스 생성, 테이블 생성
  - Book 테이블 생성 후 insert 로 데이터 입력
- 4교시
  - libmysqlclient 설치 (sudo apt install libmysql++*)
- 5교시
  - ip 해석 및 포트포워딩과 포트오픈 실습실의 상황 설명
- 6교시
  - bookSql.c 작성 - mysql 연결, 데이터베이스 선택, 쿼리 실행
- 7교시
  - CMake 설명 및 예제
  - cmake 설치 - sudo apt install cmake build-essential gdb gcc ( 반드시 build-essential 설치 )
  - CMakeLists.txt 작성
  - 디버깅 사용 방법 - c89 Vscode 에서의 cmake kit 설정 문제가 있음
    -> /home/aa/.local/share/CMakeTools/cmake-tools-kits.json 내용 변경.
- 8교시
  - 정리
  - [과제] bookSql.c 에 함수 추가 - insertBook

---

## 2025-03-13

---

- 1교시
  - 복습
  - CMake VsCode 설정 - 디버깅
- 2교시
  - cmake 프로젝트의 subdirectory 설정
  - c89 Vscode 에서의 cmake kit 설정 문제가 있음
    -> /home/aa/.local/share/CMakeTools/cmake-tools-kits.json 내용 변경.
  - 동적 할당 설명 - malloc, calloc, realloc, free
- 3교시
  - 동적 할당 예제
  - 공용체, 열거형 설명 - union, enum
- 4교시
  - 공용체, 열거형 예제 - unionExample.c enumExample.c
- 5교시
  - bookSql 에 enum, 동적할당 적용
- 6교시
  - sql 예제 - bookSql.c
  - [과제]함수 추가 - deleteBook, updateBook, queryBook
- 7교시
  - 과제 수행
- 8교시
  - 정리

---

## 2025-03-14

---

- 1교시
  - 복습
  - CMakeLists.txt sub_directory 추가
- 2교시
  - [과제]함수 추가 - deleteBook, updateBook, queryBook
- 3교시
  - 표준 입력 함수 - scanf, sscanf, fscanf, getchar, gets, fgetc, fgets
- 4교시
  - 표준 출력 함수 - printf, sprintf, fprintf, putchar, puts, fputc, fputs
  - fflush() 예제
- 5교시
  - Sql 분할 컴파일
- 6교시
  - 교재 살펴보기
- 7교시
  - 교재 살펴보기
  - 볼링 게임 안내 [C 언어] 메인 과제
  - 규칙: 개인전
    - [각자 자신의 점수를 기록하고 마지막에 총점을 계산하여 승자를 결정한다.](https://m.blog.naver.com/stupidon9876/221436908915)
    - [점수 계산 링크](https://appbokk.com/entry/%EB%B3%BC%EB%A7%81-%EC%A0%90%EC%88%98-%EA%B3%84%EC%82%B0-%EB%B0%A9%EB%B2%95)
- 8교시
  - 정리

---

## 2025-03-17

---

- 1교시
  - 복습 - 표준 입출력 함수
  - [실습]볼링 게임
- 2교시
  - [실습]볼링 게임
- 3교시
- 4교시
  - [실습]볼링 게임
- 4교시
  - [실습]볼링 게임
- 5교시
- 6교시
  - [실습]볼링 게임
- 7교시
  - 시험 - 구글 폼
- 8교시
  - 정리

---

## Atmega128 - embedded programming

---

- 수업 목표
  - Atmega128을 이용한 임베디드 프로그래밍을 통해 하드웨어와 소프트웨어를 연결하는 방법을 익힌다.
  - Atmega128의 기본적인 사용법을 익히고 이를 이용한 프로젝트를 수행한다.
  - Atmega128의 입출력을 이용한 프로젝트를 수행한다.
- [과정 진행 사항](doc/atmega128.md)
