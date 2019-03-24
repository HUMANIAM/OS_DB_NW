-- delete all rows in tables
/*
delete from Student;
delete from College;
delete from Apply;
*/

-- insert values 
/* insert into Student values (123, 'Amy', 3.9, 1000); */

-- ****************************************************************
				-- // Selection Queries // --
				--  *******************   --
-- ****************************************************************

-- students with gpa > 6
select * 
from Student
where GPA > 3.6;

-- students and majors that they apply to and accepted
select distinct sName, major
from Student, Apply
where Student.sID = Apply.sID ;

-- ambiguity query
select distinct College.cName
from College, Apply
where College.cName = Apply.cName and major = 'CS';

-- select with closure
select Student.sID, sName, GPA, Apply.cName, enrollment
from Student, College, Apply
where Apply.sID = Student.sID and Apply.cName = College.cName
order by GPA desc, enrollment;


-- like operator
select *
from Apply
where major like '%bio%';

-- cross product
select *
from Student, College;

-- add new column from result relation with a name
select sID, sName, GPA, sizeHS, GPA*(sizeHS/1000.0) as scaledGPA
from Student;


-- ****************************************************************
				-- // Table variables and set operator // --
				--  ***********************************   --
--TABLE VARIABLES AND SET OPERATORS
--Works for SQLite, Postgres
--MySQL doesn't support Intersect or Except
-- ****************************************************************

-- applications information
select distinct Student.sID, sName, GPA, Apply.cName, enrollment
from Student, College, Apply
where Apply.sID = Student.sID and Apply.cName = College.cName;

/*** Introduce table variables ***/
select S.sID, S.sName, S.GPA, A.cName, C.enrollment
from Student S, College C, Apply A
where A.sID = S.sID and A.cName = C.cName;

-- self join --
select *
from Student S1, Student S2
where S1.GPA = S2.GPA and S1.sID < S2.sID; 

-- set operator : union --

-- unset tuples --
select cName as name from College
union
select sName as name from Student;

-- multiset tuples --
/*** Notice not sorted any more (SQLite), add order by cName ***/
select cName as name from College
union all
select sName as name from Student
order by name;

-- set operator : intersect --
select sID from Apply where major = 'CS'
intersect
select sID from Apply where major = 'EE';

-- the same query without intersect by self join --
select distinct A1.sID
from Apply A1, Apply A2
where A1.sID = A2.sID and A1.major = 'CS' and A2.major = 'EE';

-- set operator : diff --
select sID from Apply where major = 'CS'
except
select sID from Apply where major = 'EE';

-- the same operator using self join --
select distinct A1.sID
from Apply A1, Apply A2
where A1.sID = A2.sID and A1.major = 'CS' and A2.major <> 'EE';


-- ****************************************************************
				-- // SUBQUERIES IN THE WHERE CLAUSE // --
				--  ***********************************   --
--SUBQUERIES IN THE WHERE CLAUSE
--Works for MySQL, Postgres
--SQLite doesn't support All or Any
-- ****************************************************************

-- using In clause --
select sID, sName
from Student
where sID in (select sID from Apply where major = 'CS');

-- without using in 
select distinct Student.sID, sName
from Student, Apply
where Student.sID = Apply.sID and major = 'CS';


/*
											-- Alter Table --
											******************
*/
-- alter table by change data type of column
Alter table Apply
ALTER COLUMN decision varchar(50);

-- alter table by dropping column
/*
ALTER TABLE Customers
DROP COLUMN Email;
*/

-- alter table by creating column
/*
ALTER TABLE Customers
ADD Email varchar(255);
*/

-- alter table by drop 
