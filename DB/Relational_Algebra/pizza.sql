/*
	Author : Ibrahim Saad
	date : 12/3/2019
	about : relational algebra queries 
*/
/*
	It's a simple database has just 4 tables in pizza.sqlite
*/

/*
	Q1 : Find all pizzas eaten by at least one female over the age of 20. 
*/
validPizzas :- \project_{pizza} \select_{gender = 'female' and age > 20} (Eats \join Person);

/*
	Q2 : Find the names of all females who eat at least one pizza served by Straw Hat. (Note: The pizza need not be eaten at Straw Hat.) 
*/

T1 :- \project_{name, pizza} \select_{gender = 'female' } (Eats \join Person);

T2 :- \project_{name} \select_{pizzeria = 'Straw Hat'} (T1 \join Serves);

/*
	Q3 : Find all pizzerias that serve at least one pizza for less than $10 that either Amy or Fay (or both) eat. 
*/
T1 :- \project_{pizzeria} \select_{price < 10 and (name = 'Fay' or name = 'Amy')} (Eats \join Serves)

/*
	Q4 : Find all pizzerias that serve at least one pizza for less than $10 that both Amy and Fay eat. 
*/

T1 :- (\project_{pizza} \select_{name = 'Fay'} Eats ) \intersect  (\project_{pizza} \select_{name = 'Amy'} Eats);

T2 :- \project_{pizzeria} \select_{price < 10} (Serves \join T1);

/*
	Q5: Find the names of all people who eat at least one pizza served by Dominos but who do not frequent Dominos. 
*/

T1 :- \select_{pizzeria = 'Dominos'} (Eats \join Serves);

T2 :- \project_{name} \select_{pizzeria = 'Dominos'} Frequents;

R :- \project_{name} T1 \diff T2;

/*
	Q6 : Find all pizzas that are eaten only by people younger than 24, or that cost less than $10 everywhere they're served. 
*/
olderPeoplePizza :- \project_{pizza} \select_{age >= 24} (Eats \join Person);

youngerPeoplePizza :- \project_{pizza} \select_{age < 24} (Eats \join Person);

validPizza_people :- youngerPeoplePizza \diff olderPeoplePizza;

pizza_less10 :- \project_{pizza} \select_{price < 10} Serves;

pizza_greater10 :- \project_{pizza} \select_{price > 10} Serves;

valid_pizza_pizzera :- pizza_less10 \diff pizza_greater10;

valid_pizza :- valid_pizza_pizzera \union validPizza_people;


/*
	Q7 : Find the age of the oldest person (or people) who eat mushroom pizza. 
*/
mushroomEaters :- \project_{name, age} \rename_{name, pizza, age, gender}\select_{pizza = 'mushroom'} (Eats \join Person);

joinedTable :- \project_{T1_name, T1_age} (\rename_{T1_name, T1_age} mushroomEaters \join_{T1_age < T2_age} \rename_{T2_name, T2_age} mushroomEaters); 

oldestAge :- \project_{age} (mushroomEaters \diff joinedTable);


/*
	Q8 : Find all pizzerias that serve only pizzas eaten by people over 30. 
*/

T1 :- \project_{pizza} \select_{age > 30} (Eats \join Person);

T2 :- Serves \join T1;
T3 :- Serves \diff T2;

R :- \project_{pizzeria} T2 \diff \project_{pizzeria} T3;


/*
	Q9 : Find all pizzerias that serve every pizza eaten by people over 30. 
*/
T1 :- \project_{pizza} \select_{age > 30} (Eats \join Person);

T2 :- \project_{pizzeria}(Serves); 

T3 :- T2 \cross T1;

T4 :- \project_{pizzeria,pizza}(Serves);

T5 :- \project_{pizzeria} (T3 \diff T4);

R :- T2 \diff T5 ;

