create database mydb;
grant all privileges on mydb.* to myuser @'%';
use mydb;

create table SRecord (
    username varchar(20) primary key,
    playdate date,
    score integer
);

create table TRecord (
    username varchar(20) primary key,
    playmonth date,
    numgames integer
);
