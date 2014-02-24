using namespace std;
#include <iostream>
#include "Database.h"
#include "app_commands.h"

int main(){
	Database db;
	init( db );
	bool appOperational = true;
	string input = "";
	showMenu();
	while( appOperational )
	{
		getline( cin, input );
		if( input == "Help" )
		{
			showMenu();
		}
		else
		{
			if( input == "Add new restaurant" )
			{
				addRestaurant( db );
			}
			else if( input == "Add new customer" )
			{
				addCustomer( db );
			}
			else if( input == "Add new review" )
			{
				addReview( db );
			}
			else if( input == "Remove restaurant" )
			{ 
				removeRestaurant( db );
			}
			else if( input == "Remove customer" )
			{
				removeCustomer( db );
			}
			else if( input == "Remove review" )
			{
				removeReview( db );
			}
			else if( input == "List restaurants" )
			{
				listRestaurants( db );
			}
			else if( input == "List restaurant" )
			{
				listRestaurantAttributes( db );
			}
			else if( input == "List customer" )
			{
				listCustomerAttributes( db );
			}
			else if( input == "List review" )
			{
				listReviewAttributes( db );
			}
			else if( input == "List reviews by restaurant" )
			{
				listReviewsByRestaurant( db );
			}
			else if( input == "List reviews by customer" )
			{
				listReviewsByCustomer( db );
			}
			else if( input == "List reviews by title" )
			{
				listReviewsByTitle( db );
			}
			else if( input == "List customers by location" )
			{
				listCustomersByLocation( db );
			}
			else if( input == "List restaurants by location" )
			{
				listRestaurantsByLocation( db );
			}
			else if( input == "List restaurants by kind of food" )
			{
				listRestaurantsByKindOfFood( db );
			}
			else if( input == "List restaurants in customer location" )
			{
				listRestaurantsInCustomerLocation( db );
			}
			else if( input == "List restaurant reviews with atleast minimum rating" )
			{
				listRestaurantReviewsWithRatingOrBetter( db );
			}
			else if( input == "Quit" )
			{
				quit( db );
				appOperational = false;
			}
			else if(input == "")
			{
				continue;
			}
			else
			{
				cout << "INPUT_ERR" << endl;
			}
			input = "";
			cout << ">";
		}
	}
}