#include "app_commands.h"

// RESTAURANT(restaurant_name, kind_of_food, location, num_reviews, avg_customers, total_customers)
// CUSTOMER(customer_name, age, location, num_reviews, gender)
// REVIEW(title, customer_name, price_rating, quality_rating, atmosphere_rating, customer_service, overall_rating)

unsigned int listCustomersByLocation( Database & my_database )
{
	cout<<"Please enter the name of location.\n";
	string location = "";
	getline( cin, location );
	vector <string> results;
	string command = "list_customers_by_location <- project (customer_name) (select (customer_location == \"";
	command += location;
	command += "\") customers);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_customers_by_location;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listRestaurantsByLocation( Database & my_database )
{
	cout<<"Please enter the name of location.\n";
	string location = "";
	getline( cin, restaurant_location );
	vector <string> results;
	string command = "list_restaurants_by_location <- project (restaurant_name) (select (restaurant_location == \"";
	command += restaurant_location;
	command += "\") restaurants);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_restaurants_by_location;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listRestaurantsByKindOfFood( Database & my_database )
{
	cout<<"Please enter the kind of food.\n";
	string kind_of_food = "";
	getline( cin, kind_of_food );
	vector <string> results;
	string command = "list_restaurants_by_kind_of_food <- project (restaurant_name,  restaurant_location) (select (kind_of_food == \"";
	command += kind_of_food;
	command += "\") restaurants);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_restaurants_by_kind_of_food;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listReviewsByTitle( Database & my_database )
{
	cout<<"Please enter the review title.\n";
	string title = "";
	getline( cin, title );
	vector <string> results;
	string command = "list_reviews_by_title <- project (restaurant_name,  restaurant_location, customer_name, customer_location) select (title == \""";
	command += title;
	command += "\") reviews);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_reviews_by_title;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listRestaurantReviewsWithRatingOrBetter( Database & my_database )
{
	cout<<"Please enter name of restaurant.\n";
	string restaurant_name = "";
	getline( cin, name );
	cout<<"Please enter location of restaurant.\n";
	string restaurant_location = "";
	getline( cin, location );
	cout<<"Please enter the mininum overall rating of the reviews for which you seek.\n";
	string rating = "";
	getline( cin, rating );
	string command = "reviews_rated_or_better <- select (restaurant_name == \"";
	command += restaurant_name;
	command += "\" && restaurant_location == \"";
	command += restaurant_location;
	command += "\" && overall_rating >= ";
	command += rating;
	command += ");";
	my_database.execute( results, command, my_database );
	command = "SHOW reviews_rated_or_better;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listRestaurantAttributes( Database & my_database )
{
	cout<<"Please enter name of restaurant.\n";
	string name = "";
	getline( cin, name );
	cout<<"Please enter location of restaurant.\n";
	string location = "";
	getline( cin, location );
	/*Create query which selects all data associated with restaurant with certain name & location*/
	vector <string> results;
	string command = "restaurant_attr <- select (restaurant_name == \"";
	command += name;
	command += "\" && location_name == \"";
	command += location;
	command += "\");";
	my_database.execute( results, command, my_database );
	command = "SHOW restaurant_attr;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listCustomerAttributes( Database & my_database )
{
	cout<<"Please enter name of customer.\n";
	string name = "";
	getline( cin, name );
	cout<<"Please enter name of location.\n";
	string location = "";
	getline( cin, location );
	/*Create query which selects all data associated with customer with certain name & location*/
	vector <string> results;
	string command = "customer_attr <- select (name == \"";
	command += name;
	command += "\" && location == \""
	command += location;
	command += "\");";
	my_database.execute( results, command, my_database );
	command = "SHOW customer_attr;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listReviewAttributes( Database & my_database )
{
	cout<<"Please enter name of the customer that reviewed.\n";
	string customer_name = "";
	getline( cin, customer_name );
	cout<<"Please enter the customer's location\n";
	string customer_location = "";
	getline( cin, customer_location );
	cout<<"Please enter name of the restaurant that was reviewed.\n";
	string restaurant_name = "";
	getline( cin, restaurant_name );
	cout<<"Please enter location of the restaurant that was reviewed.\n";
	string restaurant_location = "";
	getline( cin, customer_name );
	cout<<"Please enter title of the review.\n";
	string title = "";
	getline( cin, title );
	//Create query which selects all data associated with customer with certain name
	vector <string> results;
	string command = "review_attr <- select (customer_name == \"";
	command += customer_name;
	command += "\" && customer_location == \"";
	command += customer_location;
	command += "\" && restaurant_name == \"";
	command += restaurant_name;
	command += "\" && restaurant_location == \"";
	command += restaurant_location;
	command += "\" && title == \"";
	command += title;
	command += "\");";
	my_database.execute( results, command, my_database ); //SELF, what does it put in results?
	command = "SHOW review_attr;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listRestaurantsInCustomerLocation( Database & my_database )
{
	cout<<"Please enter name of the customer that reviewed.\n";
	string customer_name = "";
	getline( cin, customer_name );
	cout<<"Please enter the customer's location\n";
	string location = "";
	getline( cin, location );
	vector<string> results;	
	string command = "restaurants_in_area <- select (customer_name == \"";
	command += customer_name;
	command += "\" && location == \"";
	command += location
	command += "\") customer_restaurant_combo";
	my_database.execute( results, command, my_database );
	command = "SHOW restaurants_in_area;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
	
}

unsigned int listReviewsByCustomer( Database & my_database )
{
	cout<<"Please enter the customer\'s name.\n";
	string name = "";
	getline( cin, name );
	cout<<"Please enter the customer\'s location.\n";
	string location = "";
	getline( cin, location );
	vector <string> results;
	string command = "list_reviews_by_customer <- (select (customer_name == \"";
	command += name;
	command += "\" && customer_location == \"";
	command += location;
	command += "\") customer_review_combo);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_reviews_by_customer;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

unsigned int listReviewsByRestaurant( Database & my_database )
{
	cout<<"Please enter the restaurant\'s name.\n";
	string name = "";
	getline( cin, name );
	cout<<"Please enter the restaurant\'s location.\n";
	string location = "";
	getline( cin, location );
	vector <string> results;
	string command = "list_reviews_by_restaurant <- (select (restaurant_name == \"";
	command += name;
	command += "\" && restaurant_location == \"";
	command += location;
	command += "\") review_restaurant_combo);";
	my_database.execute( results, command, my_database );
	command = "SHOW list_reviews_by_restaurant;";
	my_database.execute( results, command, my_database );
	for( int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i );
	}
}

void init( Database & db )
{
	ifstream file_check("restaurants.db", std::ifstream::in);
	string command = "";
	vector<string> results;
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN restaurants;"
	}
	else
	{
		file_check.clear();
		command = "CREATE TABLE restaurants (restaurant_name VARCHAR(20), kind_of_food VARCHAR(20)";
		command += ", restaurant_location VARCHAR(20), num_reviews INTEGER, avg_customers INTEGER";
		command +=", total_customers INTEGER) PRIMARY KEY (restaurant_name, restaurant_location);";
	}
	db.execute( results, command, db );
	
	file_check.open("customers.db", std::ifstream::in);
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN customers;"
	}
	else
	{
		file_check.clear();
		command = "CREATE TABLE customers (customer_name VARCHAR(20), customer_location VARCHAR(20)";
		command += ", gender VARCHAR(10), age INTEGER, num_reviews INTEGER)";
		command +=" PRIMARY KEY (customer_name, customer_location);";
	}
	db.execute( results, command, db );
	
	file_check.open("reviews.db", std::ifstream::in);
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN reviews;"
	}
	else
	{
		file_check.clear();
		command = "CREATE TABLE reviews (title VARCHAR(20), customer_name VARCHAR(20)";
		command += ", price_rating INTEGER, quality_rating INTEGER, atmosphere_rating INTEGER";
		command += " , customer_service INTEGER, overall_rating INTEGER";
		command += " , restaurant_name VARCHAR(20), restaurant_location VARCHAR(20), customer_location VARCHAR(20)) ";
		command += "PRIMARY KEY (title, restaurant_name, restaurant_location, customer_name, customer_location);";
	}
	db.execute( results, command, db );
	
	file_check.open("customer_restaurant_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN customer_restaurant_combo;"
	}
	else
	{
		file_check.clear();
		command = "customer_restaurant_combo <- (rename (customer_name, location) (project (customer_name, customer_location) customers)) "
		command += "JOIN (rename (restaurant_name, location) (project (restaurant_name, restaurant_location) restaurants));";
	}
	db.execute( results, command, db );
	
	file_check.open("restaurant_review_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN restaurant_review_combo;"
	}
	else
	{
		file_check.clear();
		command = "restaurant_review_combo <- (project (restaurant_name, restaurant_location) restaurants) JOIN ";
		command += "(project (restaurant_name, restaurant_location, title) reviews);";
	}
	db.execute( results, command, db );

	file_check.open("customer_review_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		file_check.close();
		command = "OPEN customer_review_combo;"
	}
	else
	{
		file_check.clear();
		command = "customer_review_combo <- (project (customer_name, customer_location) customers) JOIN ";
		command += "(project (customer_name, customer_location, title) reviews);";
	}
	db.execute( results, command, db );	
}

void quit( Database & db )
{
	vector<string> results;
	string command = "";
	command = "WRITE restaurants;"
	db.execute( results, command, db );
	command = "WRITE customers;"
	db.execute( results, command, db );
	command = "WRITE reviews;"
	db.execute( results, command, db );
	command = "WRITE customer_restaurant_combo;"
	db.execute( results, command, db );
	command = "WRITE restaurant_review_combo;"
	db.execute( results, command, db );
	command = "WRITE customer_review_combo;"
	db.execute( results, command, db );
	
	command = "CLOSE restaurants;"
	db.execute( results, command, db );
	command = "CLOSE customers;"
	db.execute( results, command, db );
	command = "CLOSE reviews;"
	db.execute( results, command, db );
	command = "CLOSE customer_restaurant_combo;"
	db.execute( results, command, db );
	command = "CLOSE restaurant_review_combo;"
	db.execute( results, command, db );
	command = "CLOSE customer_review_combo;"
	db.execute( results, command, db );
	
	command = "EXIT;"
	db.execute( results, command, db );
}