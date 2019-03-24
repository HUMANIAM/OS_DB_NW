/*Q : Remove all ratings where the movie's year is before 1970 or after 2000, and the rating is fewer than 4 stars. */
delete 
from Rating
where stars < 4 and exists (select year from Movie where Rating.mID = Movie.mID and (year < 1970 or year > 2000))

/*Q: Add the reviewer Roger Ebert to your database, with an rID of 209. */
insert into Reviewer values(209, 'Roger Ebert')

/*Q: Insert 5-star ratings by James Cameron for all movies in the database. Leave the review date as NULL. */
insert into Rating 
select 207, Movie.mID, 5, null
from Movie

/*Q : For all movies that have an average rating of 4 stars or higher, add 25 to the release year.
 (Update the existing tuples; don't insert new tuples.) */
update Movie
set year = year + 25
where 4 <= (select avg(stars) from Rating where Movie.mID = Rating.mID)



