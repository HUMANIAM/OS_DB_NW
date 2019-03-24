-- create database for stanford course
create database stanford_course_db

/**
delete an existing database
*/
--drop database test_db


--backup database : create a full back up of an existing sql database
/**
backup database stanford_course_db
to disk = 'F:\programming music\stanford_course_buckup_db';
*/


-- backup only the different between the last backup and the current version of the db
/**
backup database stanford_course_db
to disk = 'F:\programming music\stanford_course_buckup_db'
with DIFFERENTIAL;
*/


--create student table
/*
create table Student(
	ID int,
	name varchar(50),
	GPA int,
	photo varbinary(8000)
);
**/

--create faculty table
/*
create table Faculty(
	name varchar(50),
	state char(2),
	enrollment int
);
**/