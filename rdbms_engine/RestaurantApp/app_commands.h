#ifndef APP_COMMANDS_GUARD
#define APP_COMMANDS_GUARD

#include <string>
#include "Database.h"

	/* Addition-Deletion */

//Add to restaurants table, recompute restaurant_review_combo and customer_review_combo
void addRestaurant( Database & my_database );

//Add to customers table, recompute customer_restaurant and customer_review_combo
void addCustomer( Database & my_database );

//Add to reviews table, recompute restaurant_review_combo and customer_review_combo
void addReview( Database & my_database );

//Remove a row from restaurants, recompute two hybrid tables
void removeRestaurant( Database & my_database );

//Remove a row from customers, recompute two hybrid tables
void removeCustomer( Database & my_database );

//Remove a row from reviews, recompute two hybrid tables
void removeReview( Database & my_database );

	/*Complete table show*/

//Show restaurants table
void listRestaurants( Database & my_database );

	/*Specify attribute value, get other primary keys of table which have*/

//Give the names of all the customers in a location
void listCustomersByLocation( Database & my_database );

//Give the names of all the restaurants in a location
void listRestaurantsByLocation( Database & my_database );

//Give the locations and names of all restaurants with a particular food kind.
void listRestaurantsByKindOfFood( Database & my_database );

//Look for all reviews in a database with a particular title.
void listReviewsByTitle( Database & my_database );

//Show all reviews for a particular restaurant with a given overall rating or better.
void listRestaurantReviewsWithRatingOrBetter( Database & my_database );

	/*Specify primary keys, get non-primary key information*/

//Print out details of a particular restaurant
void listRestaurantAttributes( Database & my_database );

//Print out details of a particular customer
void listCustomerAttributes( Database & my_database );

//Print out details of a particular review
void listReviewAttributes( Database & my_database );

	/*Utilize Three Hybrid tables*/

//Gives all titles written about a restuarant
void listReviewsByRestaurant( Database & my_database );

//Gives all titles written by a customer
void listReviewsByCustomer( Database & my_database );

//Gives all restaurants in a customer's location
void listRestaurantsInCustomerLocation( Database & my_database );

	/*Primary Control*/
	
//Print commands for user.
void showMenu();

//Writes to 6 files as necessary and kills execution of Database object.
void quit( Database & db );

//Get tables from text files if they exist
void init( Database & db );

#endif