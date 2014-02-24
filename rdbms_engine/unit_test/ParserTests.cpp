#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "Database.h"
#define INTEGER 0

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{		
	TEST_CLASS(ParserTests)
	{
	public:	
		TEST_METHOD(commandTest){
			Database d;
			string input = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			string table_name = "animals";
			vector<string> empty_results;
			d.execute( empty_results,input, d);
			Assert::IsTrue("animals" == d.findTable("animals").getName());
			// Read in input
			// Compare find's return number with what is defined as a command
			// Return true
		}
		TEST_METHOD(queryTest){
			Database d;
			string input_one = "CREATE TABLE friends (fname VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			string input_two = "project_test <- project (fname, lname) friends;";
			vector<string> empty_results;
			Parser p_one(input_one, d, empty_results);
			Parser p_two(input_two, d, empty_results);
			Assert::IsTrue(empty_results[0] != "Error: Parser was unsuccessfull.");
			// Read in input
			// Compare find's return number with what is defined as a query
			// Return true
		}
		TEST_METHOD(createTableCommandTest){
			Database d;
			// Create String for parsing
			string input = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			// Create Parser
			vector<string> empty_results;
			d.execute(empty_results, input, d);
			// Create variables for making a table
			string table_name = "animals";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("name");
			cn.push_back("kind");
			cn.push_back("years");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			//pk.push_back(2);
			// Create Widths
			cw.push_back(20);
			cw.push_back(8);
			cw.push_back(15);
			// Create tables
			table test_table(table_name, cn, ct, pk, cw);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable("animals"));
		}
		TEST_METHOD(insertTableCommandTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			string input_two = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
			// Create parsers
			vector<string> empty_results;
			d.execute(empty_results, input_one, d);
			d.execute(empty_results, input_two, d);
			// Create variables for making a table
			string table_name = "animals";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("name");
			cn.push_back("kind");
			cn.push_back("years");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			//pk.push_back(2);
			// Create Widths
			cw.push_back(20);
			cw.push_back(8);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Create expected entities
			entity e;
			e.addAttribute(attribute("Joe"));
			e.addAttribute(attribute("cat"));
			e.addAttribute(attribute(4));
			// Add entity to the table
			test_table.addEntity(e);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable("animals"));
		}
		TEST_METHOD(showTableCommandTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			string input_two = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
			string input_three = "INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);";
			string input_four = "INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);";
			string input_five = "INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);";
			string input_six = "INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);";
			string input_seven = "SHOW animals;";
			// Create parsers
			vector<string> empty_results;
			vector<string> empty_results2;
			d.execute(empty_results, input_one, d );
			d.execute(empty_results, input_two, d );
			d.execute(empty_results, input_three, d );
			d.execute(empty_results, input_four, d );
			d.execute(empty_results, input_five, d );
			d.execute(empty_results, input_six, d);
			d.execute(empty_results2, input_seven, d);
			// Create variables for creating a table
			string table_name = "animals";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("name");
			cn.push_back("kind");
			cn.push_back("years");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			//pk.push_back(2);
			// Create Widths
			cw.push_back(20);
			cw.push_back(8);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Add expected entities
			entity e1;
			e1.addAttribute(attribute("Joe"));
			e1.addAttribute(attribute("cat"));
			e1.addAttribute(attribute(4));

			entity e2;
			e2.addAttribute(attribute("Spot"));
			e2.addAttribute(attribute("dog"));
			e2.addAttribute(attribute(10));

			entity e3;
			e3.addAttribute(attribute("Snoopy"));
			e3.addAttribute(attribute("dog"));
			e3.addAttribute(attribute(3));

			entity e4;
			e4.addAttribute(attribute("Tweety"));
			e4.addAttribute(attribute("bird"));
			e4.addAttribute(attribute(1));

			entity e5;
			e5.addAttribute(attribute("Joe"));
			e5.addAttribute(attribute("bird"));
			e5.addAttribute(attribute(2));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			test_table.addEntity(e3);
			test_table.addEntity(e4);
			test_table.addEntity(e5);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(empty_results2.size() == 8);
			//note: it is one more for cushion between inputs and outputs
		}
		TEST_METHOD(writeTableCommandTest){
			Database d;
			// Create String for parsing
			string input_one = "CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);";
			string input_two = "INSERT INTO animals VALUES FROM (\"Joe\", \"cat\", 4);";
			string input_three = "INSERT INTO animals VALUES FROM (\"Spot\", \"dog\", 10);";
			string input_four = "INSERT INTO animals VALUES FROM (\"Snoopy\", \"dog\", 3);";
			string input_five = "INSERT INTO animals VALUES FROM (\"Tweety\", \"bird\", 1);";
			string input_six = "INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);";
			string input_seven = "WRITE animals;";
			string input_eight = "CLOSE animals;";
			
			vector<string> empty_results;
			// Create parsers
			d.execute(empty_results, input_one, d );
			d.execute(empty_results, input_two, d );
			d.execute(empty_results, input_three, d );
			d.execute(empty_results, input_four, d );
			d.execute(empty_results, input_five, d );
			d.execute(empty_results, input_six, d );
			d.execute(empty_results, input_seven, d );
			d.execute(empty_results, input_eight, d );
			// Create variables for the expected table
			string table_name = "animals";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("name");
			cn.push_back("kind");
			cn.push_back("years");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			// Create Widths
			cw.push_back(20);
			cw.push_back(8);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Add expected entities
			entity e1;
			e1.addAttribute(attribute("Joe"));
			e1.addAttribute(attribute("cat"));
			e1.addAttribute(attribute(4));

			entity e2;
			e2.addAttribute(attribute("Spot"));
			e2.addAttribute(attribute("dog"));
			e2.addAttribute(attribute(10));

			entity e3;
			e3.addAttribute(attribute("Snoopy"));
			e3.addAttribute(attribute("dog"));
			e3.addAttribute(attribute(3));

			entity e4;
			e4.addAttribute(attribute("Tweety"));
			e4.addAttribute(attribute("bird"));
			e4.addAttribute(attribute(1));

			entity e5;
			e5.addAttribute(attribute("Joe"));
			e5.addAttribute(attribute("bird"));
			e5.addAttribute(attribute(2));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			test_table.addEntity(e3);
			test_table.addEntity(e4);
			test_table.addEntity(e5);
			// Create file and input a the expected table
			ofstream myfile;
			myfile.open ("writeTableTest.txt");
			myfile << test_table;
			myfile.close();
			// Compare the two tables written in the files
			fstream file_one("writeTableTest.txt"), file_two("animals.db");
			while(!file_one.eof())
			{
				string string_one = "";
				string string_two = "";
				getline(file_one, string_one);
				getline(file_two, string_two);
				if(string_one == string_two)
				{
					Assert::IsTrue(true);	// Return false if the tables are not equal
				}
				else
				{
					Assert::IsTrue(false);	// Return true if the tables are equal
				}
			}
		}

		TEST_METHOD(exitTest){
			// Check if exited
			Database d;
			string input_one = "EXIT;";
			vector<string> empty_results;
			Parser p(input_one, d, empty_results);
			Assert::IsTrue(d.isFinished());
			
		}
		TEST_METHOD(projectQueryTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE friends (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_two = "INSERT INTO friends VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_three = "INSERT INTO friends VALUES FROM (\"Smith\", \"Smith\", \"Annoying\", 5);";
			string input_four = "INSERT INTO friends VALUES FROM (\"Algebra\", \"Homework\", \"Boring\", -100);";
			string input_five = "SHOW friends;";
			string input_six = "project_test <- project (fname, lname) friends;";

			vector<string> empty_results;
			// Create parsers
			d.execute(empty_results, input_one, d );
			d.execute(empty_results, input_two, d );
			d.execute(empty_results, input_three, d );
			d.execute(empty_results, input_four, d );
			d.execute(empty_results, input_five, d );
			d.execute(empty_results, input_six, d );
			// Create variables for the table
			string table_name = "friends";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("fname");
			cn.push_back("lname");
			cn.push_back("personality");
			cn.push_back("value");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			// Create Widths
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Add expected entities to the table
			entity e1;
			e1.addAttribute(attribute("X"));
			e1.addAttribute(attribute("N/A"));
			e1.addAttribute(attribute("Awesome!"));
			e1.addAttribute(attribute(100));

			entity e2;
			e2.addAttribute(attribute("Smith"));
			e2.addAttribute(attribute("Smith"));
			e2.addAttribute(attribute("Annoying"));
			e2.addAttribute(attribute(5));

			entity e3;
			e3.addAttribute(attribute("Algebra"));
			e3.addAttribute(attribute("Homework"));
			e3.addAttribute(attribute("Boring"));
			e3.addAttribute(attribute(-100));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			test_table.addEntity(e3);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable(table_name));
		}
		TEST_METHOD(renameQueryTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_two = "INSERT INTO enemies VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_three = "INSERT INTO enemies VALUES FROM (\"The\", \"Penguin\", \"Weird\", 100);";
			string input_four = "INSERT INTO enemies VALUES FROM (\"Joker\", \"N/A\", \"Weird\", 150);";
			string input_five = "rename_test <- rename (v_fname, v_lname, v_personality, v_bounty) enemies;";

			vector<string> empty_results;
			// Create parsers
			d.execute(empty_results, input_one, d );
			d.execute(empty_results, input_two, d );
			d.execute(empty_results, input_three, d );
			d.execute(empty_results, input_four, d );
			d.execute(empty_results, input_five, d );
			// Create variables for the expected table
			string table_name = "rename_test";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("v_fname");
			cn.push_back("v_lname");
			cn.push_back("v_personality");
			cn.push_back("v_bounty");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			// Create Widths
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Create and add expected entities
			entity e1;
			e1.addAttribute(attribute("X"));
			e1.addAttribute(attribute("N/A"));
			e1.addAttribute(attribute("Awesome!"));
			e1.addAttribute(attribute(100));

			entity e2;
			e2.addAttribute(attribute("The"));
			e2.addAttribute(attribute("Penguin"));
			e2.addAttribute(attribute("Weird"));
			e2.addAttribute(attribute(100));

			entity e3;
			e3.addAttribute(attribute("Joker"));
			e3.addAttribute(attribute("N/A"));
			e3.addAttribute(attribute("Weird"));
			e3.addAttribute(attribute(150));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			test_table.addEntity(e3);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable("rename_test"));
		}
		TEST_METHOD(unionQueryTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE friends (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_two = "INSERT INTO friends VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_three = "INSERT INTO friends VALUES FROM (\"Smith\", \"Smith\", \"Annoying\", 5);";
			string input_four = "INSERT INTO friends VALUES FROM (\"Algebra\", \"Homework\", \"Boring\", -100);";
			string input_five = "CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_six = "INSERT INTO enemies VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_seven = "INSERT INTO enemies VALUES FROM (\"The\", \"Penguin\", \"Weird\", 100);";
			string input_eight = "INSERT INTO enemies VALUES FROM (\"Joker\", \"N/A\", \"Weird\", 150);";
			string input_nine = "good_and_bad_guys <- friends + enemies;";

			vector<string> empty_results;
			// Create parsers
			d.execute(empty_results, input_one, d);
			d.execute(empty_results, input_two, d);
			d.execute(empty_results, input_three, d);
			d.execute(empty_results, input_four, d);
			d.execute(empty_results, input_five, d);
			d.execute(empty_results, input_six, d);
			d.execute(empty_results, input_seven, d);
			d.execute(empty_results, input_eight, d);
			d.execute(empty_results, input_nine, d);
			// Create variables for the expected table
			string table_name = "good_and_bad_guys";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("fname");
			cn.push_back("lname");
			cn.push_back("personality");
			cn.push_back("value");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			// Create Widths
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Create and add expected entities
			entity e1;
			e1.addAttribute(attribute("X"));
			e1.addAttribute(attribute("N/A"));
			e1.addAttribute(attribute("Awesome!"));
			e1.addAttribute(attribute(100));

			entity e2;
			e2.addAttribute(attribute("Smith"));
			e2.addAttribute(attribute("Smith"));
			e2.addAttribute(attribute("Annoying"));
			e2.addAttribute(attribute(5));


			entity e3;
			e3.addAttribute(attribute("Algebra"));
			e3.addAttribute(attribute("Homework"));
			e3.addAttribute(attribute("Boring"));
			e3.addAttribute(attribute(-100));

			entity e4;
			e4.addAttribute(attribute("X"));
			e4.addAttribute(attribute("N/A"));
			e4.addAttribute(attribute("Awesome!"));
			e4.addAttribute(attribute(100));

			entity e5;
			e5.addAttribute(attribute("The"));
			e5.addAttribute(attribute("Penguin"));
			e5.addAttribute(attribute("Weird"));
			e5.addAttribute(attribute(100));

			entity e6;
			e6.addAttribute(attribute("Joker"));
			e6.addAttribute(attribute("N/A"));
			e6.addAttribute(attribute("Weird"));
			e6.addAttribute(attribute(150));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			test_table.addEntity(e3);
			test_table.addEntity(e5);
			test_table.addEntity(e6);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable(table_name));
		}
		TEST_METHOD(differenceQueryTest){
			Database d;
			// Create Strings for parsing
			string input_one = "CREATE TABLE friends (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_two = "INSERT INTO friends VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_three = "INSERT INTO friends VALUES FROM (\"Smith\", \"Smith\", \"Annoying\", 5);";
			string input_four = "INSERT INTO friends VALUES FROM (\"Algebra\", \"Homework\", \"Boring\", -100);";
			string input_five = "CREATE TABLE enemies (fname VARCHAR(20), lname VARCHAR(20), personality VARCHAR(20), value INTEGER) PRIMARY KEY (fname, lname);";
			string input_six = "INSERT INTO enemies VALUES FROM (\"X\", \"N/A\", \"Awesome!\", 100);";
			string input_seven = "INSERT INTO enemies VALUES FROM (\"The\", \"Penguin\", \"Weird\", 100);";
			string input_eight = "INSERT INTO enemies VALUES FROM (\"Joker\", \"N/A\", \"Weird\", 150);";
			string input_nine = "diff_test <- friends - enemies;";

			vector<string> empty_results;
			// Create parsers
			d.execute(empty_results, input_one, d );
			d.execute(empty_results, input_two, d );
			d.execute(empty_results, input_three, d );
			d.execute(empty_results, input_four, d );
			d.execute(empty_results, input_five, d );
			d.execute(empty_results, input_six, d );
			d.execute(empty_results, input_seven, d );
			d.execute(empty_results, input_eight, d );
			d.execute(empty_results, input_nine, d );
			// Create expected variables
			string table_name = "diff_test";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<unsigned int> cw;
			// Push back expected column names
			cn.push_back("fname");
			cn.push_back("lname");
			cn.push_back("personality");
			cn.push_back("value");
			// Push back expected column types
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(1);
			ct.push_back(0);
			// Push back expected primary keys
			pk.push_back(0);
			pk.push_back(1);
			// Create Widths
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(20);
			cw.push_back(15);
			// Create table
			table test_table(table_name, cn, ct, pk, cw);
			// Create and add expected entities
			entity e1;
			e1.addAttribute(attribute("Smith"));
			e1.addAttribute(attribute("Smith"));
			e1.addAttribute(attribute("Annoying"));
			e1.addAttribute(attribute(5));

			entity e2;
			e2.addAttribute(attribute("Algebra"));
			e2.addAttribute(attribute("Homework"));
			e2.addAttribute(attribute("Boring"));
			e2.addAttribute(attribute(-100));

			test_table.addEntity(e1);
			test_table.addEntity(e2);
			// Check if there's a table on the database with the same inputs as the expected table
			Assert::IsTrue(test_table == d.findTable(table_name));
		}
	};
}