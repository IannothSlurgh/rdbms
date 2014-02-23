#ifndef APP_COMMANDS_GUARD
#define APP_COMMANDS_GUARD

#include <string>
#include "Database.h"

	/* Addition-Deletion */

//Add to restaurants table, recompute restaurant_review_combo and customer_review_combo
unsigned int addRestaurant( Database & my_database );

//Add to customers table, recompute customer_restaurant and customer_review_combo
unsigned int addCustomer( Database & my_database );

//Add to reviews table, recompute restaurant_review_combo and customer_review_combo
unsigned int addReview( Database & my_database );

//Remove a row from restaurants, recompute two hybrid tables
unsigned int removeRestaurant( Database & my_database );

//Remove a row from customers, recompute two hybrid tables
unsigned int removeCustomer( Database & my_database );

//Remove a row from reviews, recompute two hybrid tables
unsigned int removeReview( Database & my_database );

	/*Complete table show*/

//Show restaurants table
unsigned int listRestaurants( Database & my_database );

	/*Specify attribute value, get other primary keys of table which have*/

//Give the names of all the customers in a location
unsigned int listCustomersByLocation( Database & my_database );

//Give the names of all the restaurants in a location
unsigned int listRestaurantsByLocation( Database & my_database );

//Give the locations and names of all restaurants with a particular food kind.
unsigned int listRestaurantsByKindOfFood( Database & my_database );

//Look for all reviews in a database with a particular title.
unsigned int listReviewsByTitle( Database & my_database );

//Show all reviews for a particular restaurant with a given overall rating or better.
unsigned int listRestaurantReviewsWithRatingOrBetter( Database & my_database );

	/*Specify primary keys, get non-primary key information*/

//Print out details of a particular restaurant
unsigned int listRestaurantAttributes( Database & my_database );

//Print out details of a particular customer
unsigned int listCustomerAttributes( Database & my_database );

//Print out details of a particular review
unsigned int listReviewAttributes( Database & my_database );

	/*Utilize Three Hybrid tables*/

//Gives all titles written about a restuarant
unsigned int listReviewsByRestaurant( Database & my_database );

//Gives all titles written by a customer
unsigned int listReviewsByCustomer( Database & my_database );

//Gives all restaurants in a customer's location
unsigned int listRestaurantsInCustomerLocation( Database & my_database );

//Print commands for user.
unsigned int showMenu();

#endif