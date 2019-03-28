-- all those queries written without using views and that results in queries with inefficient execution
/*Q : Find the name and grade of the student(s) with the greatest number of friends. */
select name, grade
from Highschooler join (select ID1, count(*) as frsPerstd from Friend group by ID1) on ID = ID1
where not exists(
				select * from (select count(*) as cnt from Friend group by ID1) R
				where R.cnt > frsPerstd
				)

/*Q : Find the number of students who are either friends with Cassandra or are friends of friends of Cassandra. 
		Do not count Cassandra, even though technically she is a friend of a friend. */
select count(*)
from Friend F1
where F1.ID1 != 1709 and (F1.ID2 = 1709 or exists(select * from Friend F2 where F2.ID1 = F1.ID2 and F2.ID2 = 1709))


/*Q : What is the average number of friends per student? (Your result should be just one number.) */
select avg(friendsPerStudent) 
from(
	select ID1, count(*) as friendsPerStudent 
	from Friend 
	group by ID1
	)

/*Q: Find those students for whom all of their friends are in different grades from themselves. Return the students' names and grades. */
select distinct H1.name, H1.grade
from Highschooler H1 join Friend F1 on H1.ID = F1.ID1
where (select count(*) from Friend join Highschooler on ID2 = ID and ID1 = H1.ID and grade = H1.grade) = 0

/*Q : For every situation where student A likes student B, but student B likes a different student C,
return the names and grades of A, B, and C. */

select INFO.name1, INFO.grade1, INFO.name2, INFO.grade2, CINFO.name, CINFO.grade
from ( (select ID1, ID2, name as name1, grade as grade1 from Likes join Highschooler on ID1 = ID) INFO1 join 
	   (select ID, name as name2, grade as grade2 from Highschooler)
	   on INFO1.ID2 = ID
	  ) INFO -- likes table with full information about A student and B student

	  -- If student B likes student C not return A, B, C 
	 join (select * from Likes join Highschooler on ID2 = ID) CINFO -- info about Liked C students
	 on
	-- liked student from B
	CINFO.ID1 = INFO.ID2
	-- and this student that liked from B is not A. get the triple students data
	and CINFO.ID2 != INFO.ID1

/*Q : Find the name and grade of all students who are liked by more than one other student. */
select distinct name, grade
from Likes join Highschooler on ID2 = ID
where (select count(*) from Likes where ID2 = ID) > 1

/*Q : Find the difference between the number of students in the school and the number of different first names.*/
select  students - uniqueNames
from 
(select count(*) as students from Highschooler),
(select count(*) as  uniqueNames
	from(
		select name, count(*)
		from Highschooler
		group by name
		)
)

/*Q : For each student A who likes a student B where the two are not friends, find if they have a friend C in common 
(who can introduce them!). For all such trios, return the name and grade of A, B, and C. */
select LNF.name1, LNF.grade1, LNF.name2, LNF.grade2, FriendsINFO.name, FriendsINFO.grade
from(
select *
from (
	(select ID1, ID2, name as name1, grade as grade1 from Likes join Highschooler on ID1 = ID) INFO1 join 
	(select ID, name as name2, grade as grade2 from Highschooler)
	on INFO1.ID2 = ID
) INFO -- likes table with full information 
where not exists(select * from Friend where INFO.ID1 = ID1 and INFO.ID2 = ID2)
) LNF -- relation of first likes the second but they are not friends
 
--find their common Friend
join (select * from Friend join Highschooler on ID2 = ID) FriendsINFO -- Friend info
on
-- select only friends for the first person
FriendsINFO.ID1 = LNF.ID1

-- and they are also friends to the second person
and FriendsINFO.ID2 in (select ID2 from Friend where ID1 = LNF.ID2)






