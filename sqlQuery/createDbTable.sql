create database mydb;
grant all privileges on mydb.* to myuser @'%';
use mydb;
create table book (
    bookid integer primary key,
    bookname varchar(40),
    publisher varchar(40),
    price integer
);

