#include "app_commands.h"

// RESTAURANT(r_name, food_kind, r_location, #revs, avg_c, tot_c)
// CUSTOMER(c_name, age, c_location, #revs, gender)
// REVIEW(title, c_name, p_rat, q_rat, a_ra, c_rat, o_rat, r_name, r_location, c_location)

void addRestaurant( Database & my_database )
{
	string name, kind_of_food, location, avg_customers, total_customers;

	//Input values
	cout << "Please enter the name of the restaurant\n";
	getline(cin, name);
	cout << "Please enter the kind of food\n";
	getline(cin, kind_of_food);
	cout << "Please enter the location of the restaurant\n";
	getline(cin, location);
	cout << "What are the restaurant's average customers weekly?\n";
	cin >> avg_customers;
	cout << "What are the total customers the restaurant has?\n";
	cin >> total_customers;

	cout << endl;

	//Tell Database to parse and Insert into table
	string command;
	command = "INSERT INTO restaurants VALUES FROM (\"" + name + "\", \"" 
		+ kind_of_food + "\", \"" + location + "\", 0, " + avg_customers + "\", " + total_customers + ");";

	vector<string> results;
	my_database.execute( results, command, my_database );
	
	
	//Re-create hybrids. Overwrite occurs.
	command = "restaurant_pk <- project (r_name, r_location) restaurants;";
	my_database.execute( results, command, my_database );

	command = "review_title <- project (r_name, r_location, title) reviews;";
	my_database.execute( results, command, my_database );

	command = "restaurant_review_combo <- restaurant_pk JOIN review_title;";
	my_database.execute( results, command, my_database );

/*	command = "restaurant_review_combo <- (project (r_name, r_location) restaurants) JOIN ";
	command += "(project (r_name, r_location, title) reviews);";
	my_database.execute( results, command, my_database );*/
	
/*	command = "customer_restaurant_combo <- (rename (c_name, location) (project (c_name, c_location) customers)) ";
	command += "JOIN (rename (r_name, location) (project (r_name, r_location) restaurants));";	
	my_database.execute( results, command, my_database );*/
}

void addCustomer( Database & my_database )
{
	string name, age, location, gender;

	//Input values
	cout << "Please enter the name of the customer\n";
	getline(cin, name);
	cout << "Please enter the age of the customer\n";
	getline(cin, age);
	cout << "Please enter the location of the customer\n";
	getline(cin, location);
	cout << "Please enter the gender of the customer\n";
	getline(cin, gender);

	cout << endl;

	//Tell Database to parse and Insert into table
	string command;
	command = "INSERT INTO customers VALUES FROM (\"" + name + "\", " + age + ", \""
				+ location + "\", 0, \"" + gender + "\");";

	vector<string> results;
	my_database.execute( results, command, my_database );
	
	//Re-create hybrids. Overwrite occurs.
	/*command = "customer_restaurant_combo <- (rename (c_name, location) (project (c_name, c_location) customers)) ";
	command += "JOIN (rename (r_name, location) (project (r_name, r_location) restaurants));";
	my_database.execute( results, command, my_database );
	
	command = "customer_review_combo <- (project (c_name, c_location) customers) JOIN ";
	command += "(project (c_name, c_location, title) reviews);";
	my_database.execute( results, command, my_database );*/
}

void addReview( Database & my_database )
{
	string title, customer_name, restaurant_name, customer_location, restaurant_location; 
	double price_rating, quality_rating, atmosphere_rating, customer_service; 
	double overall_rating;

	//Input values
	cout << "Please enter the title of the review\n";
	getline(cin, title);
	cout << "Please enter the name of the customer who made the review\n";
	getline(cin, customer_name);
	cout << "Please enter the location of the customer\n";
	getline(cin, customer_location);
	cout << "Please enter the restaurant name the review is on\n";
	getline(cin, restaurant_name);
	cout << "Please enter the location of the restaurant\n";
	getline(cin, restaurant_location);
	cout << "Please rate the pricing(out of 10, 10 being expensive, 1 being cheap)\n";
	cin >> price_rating;
	cout << "Please rate the quality(out of 10, 10 being excellent, 1 being poor)\n";
	cin >> quality_rating;
	cout << "Please rate the atmosphere(out of 10, 10 being excellent, 1 being poor)\n";
	cin >> atmosphere_rating;
	cout << "Please rate the customer service(out of 10, 10 being excellent, 1 being poor)\n";
	cin >> customer_service;
	
	cout << endl;

	//Average 4 p_rat, q_rat, a_rat, and c_rat to gain o_rat
	overall_rating = (price_rating + quality_rating + atmosphere_rating + customer_service)/4;

	//Tell Database to parse and Insert into table
	string command = "INSERT INTO reviews VALUES FROM(\"" + title + "\", \"" + customer_name + "\", " + to_string( price_rating );
	command += ", " + to_string( quality_rating ) + ", " + to_string( atmosphere_rating ) + ", " + to_string( customer_service ) + ", " + to_string( overall_rating ) + ", \"" + restaurant_name;
	command += "\", \"" + restaurant_location + "\", \"" + customer_location + "\");";

	vector<string> results;
	my_database.execute( results, command, my_database );
	results.clear();

	//Re-create hybrids. Overwrite occurs.

	command = "restaurant_pk <- project (r_name, r_location) restaurants;";
	my_database.execute( results, command, my_database );

	command = "review_title <- project (r_name, r_location, title) reviews;";
	my_database.execute( results, command, my_database );

	command = "restaurant_review_combo <- restaurant_pk JOIN review_title;";
	my_database.execute( results, command, my_database );

	/*command = "restaurant_review_combo <- ((project (r_name, r_location) restaurants) JOIN ";
	command += "(project (r_name, r_location, title) reviews));";
	my_database.execute( results, command, my_database );*/

/*	command = "customer_review_combo <- (project (c_name, c_location) customers) JOIN ";
	command += "(project (c_name, c_location, title) reviews);";
	my_database.execute( results, command, my_database );*/
}

void removeRestaurant( Database & my_database )
{
	string restaurant_name, restaurant_location;

	//Input values
	cout << "Please enter the name of the restaurant to remove\n";
	getline(cin, restaurant_name);
	
	cout << "Please enter the location of that restaurant\n";
	getline(cin, restaurant_location);

	//Tell Database to parse and Delete from
	string command = "DELETE FROM restaurants WHERE (r_name == \"" + restaurant_name + "\" && r_location == \"" + restaurant_location + "\");"; 

	vector<string> results;
	my_database.execute( results, command, my_database );
	
	//Re-create hybrids. Overwrite occurs.

	command = "restaurant_pk <- project (r_name, r_location) restaurants;";
	my_database.execute( results, command, my_database );

	command = "review_title <- project (r_name, r_location, title) reviews;";
	my_database.execute( results, command, my_database );

	command = "restaurant_review_combo <- restaurant_pk JOIN review_title;";
	my_database.execute( results, command, my_database );

	/*command = "restaurant_review_combo <- (project (r_name, r_location) restaurants) JOIN ";
	command += "(project (r_name, r_location, title) reviews);";
	my_database.execute( results, command, my_database );
	
	command = "customer_restaurant_combo <- (rename (c_name, location) (project (c_name, c_location) customers)) ";
	command += "JOIN (rename (r_name, location) (project (r_name, r_location) restaurants));";	
	my_database.execute( results, command, my_database );*/
}

void removeCustomer( Database & my_database )
{
	string customer_name, customer_location;

	//Input values
	cout << "Please enter the name of the customer to remove\n";
	getline(cin, customer_name);

	cout << "Please enter the location of that customer\n";
	getline(cin, customer_location);

	//Tell Database to parse and Delete from
	string command = "DELETE FROM customers WHERE (c_name == \"" + customer_name + "\" && c_location == \"" + customer_location + "\");"; 
	vector<string> results;
	my_database.execute( results, command, my_database );
	
	//Re-create hybrids. Overwrite occurs.
	/*command = "customer_restaurant_combo <- (rename (c_name, location) (project (c_name, c_location) customers)) ";
	command += "JOIN (rename (r_name, location) (project (r_name, r_location) restaurants));";
	my_database.execute( results, command, my_database );
	
	command = "customer_review_combo <- (project (c_name, c_location) customers) JOIN ";
	command += "(project (c_name, c_location, title) reviews);";
	my_database.execute( results, command, my_database );*/
}

void removeReview( Database & my_database )
{
	string review_name, customer_name, customer_location, restaurant_name, restaurant_location;

	//Input values
	cout << "Please enter the title of the review to remove.\n";
	getline(cin, review_name);
	
	cout << "Please enter the name of the customer that wrote the review.\n";
	getline(cin, customer_name);
	
	cout << "Please enter that customer\'s location.\n";
	getline(cin, customer_location);
	
	cout << "Please enter the name of the restaurant.\n";
	getline(cin, restaurant_name);
	
	cout << "Please enter the location of the restaurant.\n";
	getline(cin, restaurant_location);

	cout << endl;
	
	//Tell Database to parse and Delete from
	string command = "DELETE FROM reviews WHERE (title == \"" + review_name + "\" && c_name == \"" + customer_name;
	command += "\" && c_location == \"" + customer_location + "\" && r_name == \"";
	command += restaurant_name + "\" && r_location == \"" + restaurant_location + "\");";
	
	vector<string> results;
	my_database.execute( results, command, my_database );
	
	//Re-create hybrids. Overwrite occurs.

	command = "restaurant_pk <- project (r_name, r_location) restaurants;";
	my_database.execute( results, command, my_database );

	command = "review_title <- project (r_name, r_location, title) reviews;";
	my_database.execute( results, command, my_database );

	command = "restaurant_review_combo <- restaurant_pk JOIN review_title;";
	my_database.execute( results, command, my_database );

	/*command = "restaurant_review_combo <- (project (r_name, r_location) restaurants) JOIN ";
	command += "(project (r_name, r_location, title) reviews);";
	my_database.execute( results, command, my_database );

	command = "customer_review_combo <- (project (c_name, c_location) customers) JOIN ";
	command += "(project (c_name, c_location, title) reviews);";
	my_database.execute( results, command, my_database );*/
}

void listRestaurants( Database & my_database )
{
	string command = "SHOW restaurants;";
	vector<string> results;
	
	//Print results from the parser in Database. All restaurants in Database.
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listCustomersByLocation( Database & my_database )
{
	//Input values
	cout<<"Please enter the name of location.\n";
	string location = "";
	getline( cin, location );
	
	vector <string> results;
	
	//Shrink to a table with only the customer's name.
	string command = "list_customers_by_location <- project (c_name) (select (c_location == \"";
	command += location;
	command += "\") customers);";
	my_database.execute( results, command, my_database );

	//Print results from the parser in Database. All customers with 'X' c_location
	command = "SHOW list_customers_by_location;";
	my_database.execute( results, command, my_database );
	
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listRestaurantsByLocation( Database & my_database )
{
	//Input values
	cout<<"Please enter the name of location.\n";
	string restaurant_location = "";
	getline( cin, restaurant_location );
	
	vector <string> results;
	
	//Shrink to a table with only the names of the restaurants in a location
	string command = "list_restaurants_by_location <- project (r_name) (select (r_location == \"";
	command += restaurant_location;
	command += "\") restaurants);";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database. All restaurants with 'X' r_location
	command = "SHOW list_restaurants_by_location;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listRestaurantsByKindOfFood( Database & my_database )
{
	//Input values
	cout<<"Please enter the kind of food.\n";
	string kind_of_food = "";
	getline( cin, kind_of_food );
	
	vector <string> results;
	
	//Shrink to a table with only the names of the restaurants of a particular food type.
	string command = "list_restaurants_by_kind_of_food <- project (r_name,  r_location) (select (food_kind == \"";
	command += kind_of_food;
	command += "\") restaurants);";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database. All restaurants with 'X' food_kind.
	command = "SHOW list_restaurants_by_kind_of_food;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listReviewsByTitle( Database & my_database )
{
	//Input values
	cout<<"Please enter the review title.\n";
	string title = "";
	getline( cin, title );
	
	vector <string> results;
	
	//Shrink to a table with all the other primary keys of a review (place reviewed, where it is, person reviewing, where he/she lives)
	string command = "list_reviews_by_title <- project (r_name, r_location, c_name, c_location) (select (title == \"";
	command += title;
	command += "\") reviews);";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database. All reviews with 'X' title.
	command = "SHOW list_reviews_by_title;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listRestaurantReviewsWithRatingOrBetter( Database & my_database )
{
	//Input values
	cout<<"Please enter name of restaurant.\n";
	string restaurant_name = "";
	getline( cin, restaurant_name );
	
	cout<<"Please enter location of restaurant.\n";
	string restaurant_location = "";
	getline( cin, restaurant_location );
	
	cout<<"Please enter the mininum overall rating (o_rat) of the reviews for which you seek.\n";
	string rating = "";
	getline( cin, rating );
	
	vector <string> results;
	
	//Give table of all reviews belonging to restaurant which have o_rat >= given number
	string command = "reviews_rated_or_better <- select (r_name == \"";
	command += restaurant_name;
	command += "\" && r_location == \"";
	command += restaurant_location;
	command += "\" && o_rat >= ";
	command += rating;
	command += ") reviews;";
	
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database. All reviews with o_rat >= 'x'.
	command = "SHOW reviews_rated_or_better;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listRestaurantAttributes( Database & my_database )
{
	//Input values
	cout<<"Please enter name of restaurant.\n";
	string name = "";
	getline( cin, name );
	
	cout<<"Please enter location of restaurant.\n";
	string location = "";
	getline( cin, location );
	
	/*Create query which selects all data associated with restaurant with certain name & location*/
	vector <string> results;
	string command = "restaurant_attr <- select (r_name == \"";
	command += name;
	command += "\" && r_location == \"";
	command += location;
	command += "\") restaurants;";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW restaurant_attr;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listCustomerAttributes( Database & my_database )
{
	//Input values
	cout<<"Please enter name of customer.\n";
	string name = "";
	getline( cin, name );
	
	cout<<"Please enter name of location.\n";
	string location = "";
	getline( cin, location );
	
	/*Create query which selects all data associated with customer with certain name & location*/
	vector <string> results;
	string command = "customer_attr <- select (c_name == \"";
	command += name;
	command += "\" && c_location == \"";
	command += location;
	command += "\") customers;";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW customer_attr;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listReviewAttributes( Database & my_database )
{
	//Input values
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
	getline( cin, restaurant_location );
	
	cout<<"Please enter title of the review.\n";
	string title = "";
	getline( cin, title );
	
	//Create query which selects all data associated with a review with
	//a title, a reviewer's name, that reviewer's home, the restaurant's name,
	// and the restaurant's location
	vector <string> results;
	string command = "review_attr <- select (c_name == \"";
	command += customer_name;
	command += "\" && c_location == \"";
	command += customer_location;
	command += "\" && r_name == \"";
	command += restaurant_name;
	command += "\" && r_location == \"";
	command += restaurant_location;
	command += "\" && title == \"";
	command += title;
	command += "\") reviews;";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW review_attr;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listRestaurantsInCustomerLocation( Database & my_database )
{
	//Input values
	cout<<"Please enter name of the customer that reviewed.\n";
	string customer_name = "";
	getline( cin, customer_name );
	
	cout<<"Please enter the customer's location\n";
	string location = "";
	getline( cin, location );
	
	//Find all the entries of restaurants in the given customer's home location
	vector<string> results;	
	string command = "restaurants_in_area <- select (c_name == \"";
	command += customer_name;
	command += "\" && location == \"";
	command += location;
	command += "\") customer_restaurant_combo";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW restaurants_in_area;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
	
}

void listReviewsByCustomer( Database & my_database )
{
	//Input values
	cout<<"Please enter the customer\'s name.\n";
	string name = "";
	getline( cin, name );
	
	cout<<"Please enter the customer\'s location.\n";
	string location = "";
	getline( cin, location );
	
	vector <string> results;
	
	//Find all the titles written by a customer.
	string command = "list_reviews_by_customer <- select (c_name == \"";
	command += name;
	command += "\" && c_location == \"";
	command += location;
	command += "\") customer_review_combo;";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW list_reviews_by_customer;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void listReviewsByRestaurant( Database & my_database )
{
	//Input values
	cout<<"Please enter the restaurant\'s name.\n";
	string name = "";
	getline( cin, name );
	
	cout<<"Please enter the restaurant\'s location.\n";
	string location = "";
	getline( cin, location );
	
	vector <string> results;
	
	//Find all the unique titles written about a restaurant
	string command = "list_reviews_by_restaurant <- select (r_name == \"";
	command += name;
	command += "\" && r_location == \"";
	command += location;
	command += "\") restaurant_review_combo;";
	my_database.execute( results, command, my_database );
	
	//Print results from the parser in Database.
	command = "SHOW list_reviews_by_restaurant;";
	my_database.execute( results, command, my_database );
	for( unsigned int i = 0; i < results.size(); ++i )
	{
		cout << results.at( i ) << endl;
	}
}

void init( Database & db )
{
	string command = "";
	vector<string> results;
	
	//Check if restaurants file exists.
	ifstream file_check("restaurants.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into restaurants table
		file_check.close();
		command = "OPEN restaurants;";
	}
	else
	{
		//Otherwise, create a new restaurants table.
		file_check.clear();
		command = "CREATE TABLE restaurants (r_name VARCHAR(10), food_kind VARCHAR(10)";
		command += ", r_location VARCHAR(10), #rev INTEGER, avg_c INTEGER";
		command +=", tot_c INTEGER) PRIMARY KEY (r_name, r_location);";
	}
	db.execute( results, command, db );
	
	//Check if customers file exists.
	file_check.open("customers.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into customers table
		file_check.close();
		command = "OPEN customers;";
	}
	else
	{
		//Otherwise, create a new customers table.
		file_check.clear();
		command = "CREATE TABLE customers (c_name VARCHAR(10), age INTEGER";
		command += ", c_location VARCHAR(10), #rev INTEGER, gender VARCHAR(10))";
		command +=" PRIMARY KEY (c_name, c_location);";
	}
	db.execute( results, command, db );
	
	//Check if reviews file exists.
	file_check.open("reviews.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into reviews table
		file_check.close();
		command = "OPEN reviews;";
	}
	else
	{
		//Otherwise, create a new reviews table.
		file_check.clear();
		command = "CREATE TABLE reviews (title VARCHAR(10), c_name VARCHAR(10)";
		command += ", p_rat INTEGER, q_rat INTEGER, a_rat INTEGER";
		command += ", c_rat INTEGER, o_rat INTEGER";
		command += ", r_name VARCHAR(10), r_location VARCHAR(10), c_location VARCHAR(10)) ";
		command += "PRIMARY KEY (title, r_name, r_location, c_name, c_location);";
	}
	db.execute( results, command, db );
	
	//Check if customer-restaurant same location file exists.
	file_check.open("customer_restaurant_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into customer-restaurant same location table
		file_check.close();
		command = "OPEN customer_restaurant_combo;";
	}
	else
	{
		//Otherwise, create a new hybrid table.
		file_check.clear();
		command = "customer_restaurant_combo <- (rename (c_name, location) (project (c_name, c_location) customers)) ";
		command += "JOIN (rename (r_name, location) (project (r_name, r_location) restaurants));";
	}
	db.execute( results, command, db );
	
	//Check if reviews about restaurant file exists.
	file_check.open("restaurant_review_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into reviews about restaurant table.
		file_check.close();
		command = "OPEN restaurant_review_combo;";
	}
	else
	{
		//Otherwise, create a new hybrid table.
		file_check.clear();
		command = "restaurant_review_combo <- (project (r_name, r_location) restaurants) JOIN ";
		command += "(project (r_name, r_location, title) reviews);";
	}
	db.execute( results, command, db );

	//Check if reviews written by customer file exists.
	file_check.open("customer_review_combo.db", std::ifstream::in);
	if(file_check.good())
	{
		//If it does, open and copy into reviews written by customer table
		file_check.close();
		command = "OPEN customer_review_combo;";
	}
	else
	{
		//Otherwise, create a new hybrid table.
		file_check.clear();
		command = "customer_review_combo <- (project (c_name, c_location) customers) JOIN ";
		command += "(project (c_name, c_location, title) reviews);";
	}
	db.execute( results, command, db );	
}

void quit( Database & db )
{
	vector<string> results;
	string command = "";
	
	//Check if restaurants file exists.
	ifstream file_check("restaurants.db", std::ifstream::in);	
	if( ! file_check.good())
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN restaurants;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}
	//Output to file.
	command = "WRITE restaurants;";
	db.execute( results, command, db );
	command = "CLOSE restaurants;";
	db.execute( results, command, db );
	
	//Check if customers file exists.
	file_check.open("customers.db", std::ifstream::in);
	if( ! file_check.good() )
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN customers;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}
	//Output to file.
	command = "WRITE customers;";
	db.execute( results, command, db );	
	command = "CLOSE customers;";
	db.execute( results, command, db );

	//Check if reviews file exists.
	file_check.open("reviews.db", std::ifstream::in);
	if( ! file_check.good() )
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN reviews;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}
	//Output to file.
	command = "WRITE reviews;";
	db.execute( results, command, db );	
	command = "CLOSE reviews;";
	db.execute( results, command, db );
	
	//Check if customer-restaurant same location file exists.
	file_check.open("customer_restaurant_combo.db", std::ifstream::in);
	if( ! file_check.good() )
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN customer_restaurant_combo;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}
	//Output to file.
	command = "WRITE customer_restaurant_combo;";
	db.execute( results, command, db );
	command = "CLOSE customer_restaurant_combo;";
	db.execute( results, command, db );	

	//Check if reviews about restaurant file exists.
	file_check.open("restaurant_review_combo.db", std::ifstream::in);
	if( ! file_check.good() )
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN restaurant_review_combo;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}
	//Output to file.
	command = "WRITE restaurant_review_combo;";
	db.execute( results, command, db );
	command = "CLOSE restaurant_review_combo;";
	db.execute( results, command, db );	
	
	//Check if reviews written by customer file exists.
	file_check.open("customer_review_combo.db", std::ifstream::in);
	if( ! file_check.good() )
	{
		//If file does not exist, open before writing to create new file.
		file_check.clear();
		command = "OPEN customer_review_combo;";
		db.execute( results, command, db );
	}
	else
	{
		//Otherwise, is already open.
		file_check.close();
	}	
	//Output to file.
	command = "WRITE customer_review_combo;";
	db.execute( results, command, db );
	command = "CLOSE customer_review_combo;";
	db.execute( results, command, db );	
	
	//Tell Database to accept no more input for parser.
	command = "EXIT;";
	db.execute( results, command, db );
}
void showMenu()
{
	// 3 new lines for formating
	//cout << "\n\n";
	cout << "**************\n";
	cout << "Restaurant App\n";
	cout << "**************\n\n";

	cout << "Please enter one of the following commands:\n";
	cout << "- Add new restaurant\n";
	cout << "- Add new customer\n";
	cout << "- Add new review\n";
	cout << "- Remove restaurant\n";
	cout << "- Remove customer\n";
	cout << "- Remove review\n";
	cout << "- List restaurants\n";
	cout << "- List restaurant\n";
	cout << "- List customer\n";
	cout << "- List review\n";
	cout << "- List reviews by restaurant\n";
	cout << "- List reviews by customer\n";
	cout << "- List reviews by title\n";
	cout << "- List customers by location\n";
	cout << "- List restaurants by location\n";
	cout << "- List restaurants by kind of food\n";
	cout << "- List restaurants in customer location\n";
	cout << "- List restaurant reviews with atleast minimum rating\n";
	cout << "- Quit\n";
	cout << "You may show this menu at any time by typing \'Help\'\n";
	cout << ">";
}