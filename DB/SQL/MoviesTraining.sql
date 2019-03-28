-- ratings data in a more readable format: reviewer name, movie title, stars, 
-- and ratingDate. Also, sort the data, first by reviewer name, then by movie title, and lastly by number of stars. 
select  Reviewer.name, Movie.title, Rating.stars, Rating.ratingDate
from (Reviewer natural join Rating ) natural join Movie
order by Reviewer.name, Movie.title, Rating.stars;

/**
-- For all cases where the same reviewer rated the same movie twice and
-- gave it a higher rating the second time, return the reviewer's name and the title of the movie. 
*/
-- first solution
select R.name, R.title
from (select * from Rating natural join Reviewer natural join Movie) R
where exists (select * from Rating R1 
				where R.rID = R1.rID and R.mID = R1.mID and R1.stars > R.stars and R1.ratingDate > R.ratingDate);

-- second solution
select name, title
from Reviewer natural join Movie natural join (
select R1.rID, R1.mID
from Rating R1 join Rating R2 using(rID, mID) 
where R1.stars < R2.stars and R1.ratingDate < R2.ratingDate
);

/*
For each movie that has at least one rating, find the highest number of stars that movie received.
Return the movie title and number of stars. Sort by movie title. 
*/
select Movie.title, maxStars
from Movie natural join (
select Rating.mID, max(Rating.stars) as maxStars
from Rating
group by mID
having count(*) >= 1)
order by Movie.title;

/*
For each movie, return the title and the 'rating spread', that is, the difference between highest
 and lowest ratings given to that movie. Sort by rating spread from highest to lowest, then by movie title. 
*/
select Movie.title, (MaxStars - minStars) as rateSpread
from Movie natural join (
select Rating.mID, max(Rating.stars) as maxStars, min(Rating.stars) as MinStars
from Rating
group by mID
having count(*) >= 1)
order by rateSpread desc, title;


/*
Find the difference between the average rating of movies released before 1980 and the average rating of movies released after 1980.
*/

select abs(avg(afteravgStars) - avg(beforeavgStars))
from
(select afteravgStars from Movie natural join (select mID, avg(stars) as afteravgStars from Rating group by mID) where year > 1980 ),
(select beforeavgStars from Movie natural join (select mID, avg(stars) as beforeavgStars from Rating group by mID) where year < 1980)
;

/*
Find the names of all reviewers who rated Gone with the Wind.
*/
select Reviewer.name 
from Reviewer
where Reviewer.rID in(select rID from Rating natural join Movie where Movie.title = 'Gone with the Wind');

-- second solution
select distinct Reviewer.name 
from Reviewer natural join Rating natural join Movie
where Movie.title = 'Gone with the Wind';

/*
For any rating where the reviewer is the same as the director of the movie,
 return the reviewer name, movie title, and number of stars.
*/
select distinct name, title, stars
from Movie natural join Rating natural join Reviewer
where Movie.director = Reviewer.name;

/*
Return all reviewer names and movie names together in a single list, alphabetized
*/

select name from Reviewer
union
select title from Movie
order by name, title;

/*Find the titles of all movies not reviewed by Chris Jackson. */
-- first solution
select R.title 
from(
select mID, title from Movie
except
select mID, title
from Movie natural join Reviewer natural join Rating
where name == 'Chris Jackson') R;

-- second solution
select Movie.title
from Movie
where Movie.mID not in (select mID from Rating natural join Reviewer where name = 'Chris Jackson');

/*
For all pairs of reviewers such that both reviewers gave a rating to the same movie, return the names of both reviewers
*/

select distinct R1.name, R2.name
from (Rating natural join Reviewer) R1 join (Rating natural join Reviewer) R2
where R1.rID < R2.rID and R1.mID = R2.mID


select distinct R1.name, R2.name
from (select * from Rating natural join Reviewer order by name) R1 join (select * from Rating natural join Reviewer order by name) R2
where R1.rID != R2.rID and R1.mID = R2.mID and R1.name < R2.name

/*
For each rating that is the lowest (fewest stars) currently in the database, return the reviewer name, movie title, and number of stars. 
*/
select R1.name, R1.title, R1.stars
from (Reviewer natural join Rating natural join Movie) R1
where not exists(select R2.mID from Rating R2 where R1.stars > R2.stars);

/*
List movie titles and average ratings, from highest-rated to lowest-rated. If two or more movies have the same 
average rating, list them in alphabetical order. 
*/
select title, avgstars
from Movie natural join( 
			select mID, avg(stars) as avgstars from Rating group by mID)
order by avgstars desc, title;

/* Find the names of all reviewers who have contributed three or more ratings.*/
-- first solution
select name
from Reviewer natural join(
			select rID
			from Rating
			group by rID
			having count(*) >= 3);
			
-- second solution
select name
from Reviewer natural join(
			select distinct rID
			from (Rating R1 natural join Rating R2) R 
			where (select count(*) from Rating R1 where R.rID = R1.rID) >= 3);

		
/*Some directors directed more than one movie. For all such directors, return the titles of all movies directed by them, 
along with the director name. Sort by director name, then movie title.*/
-- first solution
select Movie.title, Movie.director
from Movie join (
		select distinct R1.director
		from Movie R1
		where exists (select * from Movie R2 where R1.director = R2.director and R1.mID != R2.mID)) Directors
on Directors.director = Movie.director
order by Directors.director, Movie.title;


-- second solution
select R1.title, R1.director
from Movie R1 join Movie R2 on R1.mID != R2.mID and R1.director = R2.director
order by R1.director, R1.title;

-- third solution
select Movie.title, Movie.director
from Movie join(
		select Movie.director
		from Movie
		group by Movie.director
		having (count(*)>1) )R on R.director = Movie.director
order by Movie.director,  Movie.title;

-- Find the movie(s) with the highest average rating. Return the movie title(s) and average rating
-- read query from inner to outer

select Movie.title, avgStars
from Movie natural join (
		 (select mID, avg(stars) as avgStars from Rating group by mID)  natural join (
		 select max(avgStars) as avgStars from(select mID, avg(stars) as avgStars from Rating group by mID)))


/*Find the movie(s) with the lowest average rating. Return the movie title(s) and average rating. */
select Movie.title, avgStars
from Movie natural join (
		 (select mID, avg(stars) as avgStars from Rating group by mID)  natural join (
		 select min(avgStars) as avgStars from(select mID, avg(stars) as avgStars from Rating group by mID)))
		 

/*For each director, return the director's name together with the title(s) of the movie(s) they directed that received the highest rating 
among all of their movies, and the value of that rating. Ignore movies whose director is NULL*/

-- first solution --
select distinct R1.director, R1.title, R1.stars
from (select * from Rating natural join Movie where director is not null) R1 join

(select director, max(stars) as maxMVRate
from Rating natural join Movie where director is not null
group by director) R2

where R1.director = R2.director and R1.stars = maxMVRate

-- second solution
select distinct R.director, R.title, R.stars
from (select* from Movie natural join Rating where Movie.director not null )R
where R.stars = (select max(stars) from Rating natural join Movie where Movie.director = R.director)




