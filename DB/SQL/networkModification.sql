/*Q : For all cases where A is friends with B, and B is friends with C, add a new friendship for the pair A and C. 
Do not add duplicate friendships, friendships that already exist, or friendships with oneself.*/
insert into Friend 
	select distinct AID, CID 
	from (select ID1 as AID, ID2 as BID from Friend) join (select ID1 as BID, ID2 as CID from Friend) using(BID) 
	where AID != CID and not exists(select * from Friend where ID1 == AID and ID2 == CID)



/*Q: It's time for the seniors to graduate. Remove all 12th graders from Highschooler. */
delete from Highschooler
where Highschooler.grade = 12

/*Q : If two students A and B are friends, and A likes B but not vice-versa, remove the Likes tuple. */
delete from Likes
where 
	-- they are friends
	exists(select * from Friend where ID1 = Likes.ID1 and ID2 = Likes.ID2)
	and 
	-- the next student doesn't like the first
	not exists(select * from Likes L where L.ID1 = Likes.ID2 and L.ID2 = Likes.ID1)

	