/*
Q: Write an instead-of trigger that enables deletions from view NoRating. 
Policy: Deletions from view NoRating should add a new rating for the deleted 
movie with rID = 201, stars = 1, and NULL ratingDate.
*/
create trigger noRating_delete
instead of delete on NoRating
for each row
when old.mID in (select mID from NoRating)
begin	
	insert into Rating values(201, old.mID, 1, null);

end;

/*
Q:Write an instead-of trigger that enables deletions from view NoRating. 
Policy: Deletions from view NoRating should delete the corresponding
 movie from the Movie table. 
*/
create trigger noRating_delete
instead of delete on NoRating
for each row
when old.mID in (select mID from NoRating)
begin	
	delete from Movie where mID = old.mID;
	delete from Rating where mID = old.mID;
end;
/*
Q: Write an instead-of trigger that enables insertions into view NoRating. 
Policy: An insertion should be accepted only when the (mID,title) pair already exists
 in the Movie table. (Otherwise, do nothing
Insertions into view NoRating should delete all ratings for the corresponding movie.
*/
create trigger noRating_insert
instead of insert on NoRating
for each row
when exists (select mID, title from Movie where mID = new.mID and title = new.title)
begin	
	delete from Rating where mID = new.mID;
end;
/*
Q: Write an instead-of trigger that enables insertions into view HighlyRated. 
Policy: An insertion should be accepted only when the (mID,title) pair already exists
 in the Movie table. (Otherwise, do nothing.) Insertions into view HighlyRated should add a new 
rating for the inserted movie with rID = 201, stars = 5, and NULL ratingDate.
*/
create trigger HighlyRated_insert
instead of insert on HighlyRated
for each row
when exists (select mID, title from Movie where mID = new.mID and title = new.title)
begin	
	insert into Rating values(201, new.mID, 5, null);
end;
/*
Q: Write an instead-of trigger that enables deletions from view HighlyRated. 
Policy: Deletions from view HighlyRated should update all ratings for the corresponding 
movie that have stars > 3 so they have stars = 3.
*/
create trigger HighlyRated_delete
instead of delete on HighlyRated
for each row
when old.mID in (select mID from HighlyRated)
begin	
	update Rating set stars = 3 where mID = old.mID and stars > 3;
end;

/*
Q: Write an instead-of trigger that enables deletions from view HighlyRated. 
	Deletions from view HighlyRated should delete all ratings for the corresponding 
	movie that have stars > 3
*/
create trigger HighlyRated_delete
instead of delete on HighlyRated
for each row
when old.mID in (select mID from HighlyRated)
begin	
	delete from Rating where mID = old.mID and stars > 3;
end;

/*
Q:  write a single instead-of trigger that combines all three of the previous triggers to enable
 simultaneous updates to attributes mID, title, and/or stars in view LateRating.
*/
create trigger LateRating_update
instead of update of mID, title, stars on LateRating
for each row
when old.mID in (select mID from LateRating) and new.ratingDate  == old.ratingDate 
begin
	-- update title of Movie
	update Movie 
	set title = new.title
	where mID = old.mID;
	
	-- update stars in rating table
	update Rating
	set stars =  new.stars
	where mID = old.mID and ratingDate = old.ratingDate;
	
	-- update mID of Movie and mID of Rating when update mID of latRating view
	--update mID of Movie
	update Movie
	set mID =  new.mID
	where mID = old.mID;

	-- update mID of Rating
	update Rating
	set mID =  new.mID
	where mID = old.mID;
	 
end;

/*
Q: Write an instead-of trigger that enables updates to the mID attribute of view LateRating. 
*/
create trigger LateRating_mID_update
instead of update of mID on LateRating
for each row
when old.mID in (select mID from LateRating)
begin	
	update Movie
	set mID =  new.mID
	where mID = old.mID;

	update Rating
	set mID =  new.mID
	where mID = old.mID; 
end;
/*
Q: Write an instead-of trigger that enables updates to the title attribute of view LateRating. 
*/
create trigger LateRating_title_update
instead of update of title on LateRating
for each row
when new.mID in (select mID from LateRating)
begin
	update Movie
	set title =  new.title
	where mID = new.mID;
end;

/*
Q: Write an instead-of trigger that enables updates to the stars attribute of view LateRating. 
*/
create trigger LateRating_stars_update
instead of update of stars on LateRating
for each row
when new.mID in (select mID from LateRating)
begin
	update Rating
	set stars =  new.stars
	where mID = new.mID and ratingDate = new.ratingDate;
end;
