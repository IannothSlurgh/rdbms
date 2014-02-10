#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "attribute.h"
#include "entity.h"
#include <string>
#define INTEGER 0
#define STRING 1
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{		
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(attributeTest){
			string_attribute test_attribute("Testing Attribute...", 40);
			attribute* name_of_some_kind = &test_attribute;
			Assert::AreEqual(test_attribute.get_string_value(), name_of_some_kind->get_string_value());

			int_attribute test_attribute_two(32);
			name_of_some_kind = &test_attribute_two;
			Assert::AreEqual(test_attribute_two.get_int_value(), name_of_some_kind->get_int_value());
		}

		TEST_METHOD(tableTest){
			Assert::Fail();
		}

		TEST_METHOD(entityTest){
			entity test_entity;
			string_attribute attr_one("first attribute", 30);
			int_attribute attr_two(64);
			test_entity.addStringAttribute("first attribute", 20);
			test_entity.addIntAttribute(64);
			Assert::AreEqual(test_entity.getAttribute(0).get_string_value(), attr_one.get_string_value());
			Assert::AreEqual(test_entity.getAttribute(1).get_int_value(), attr_two.get_int_value());
		}

		TEST_METHOD(differenceTest){

			/*Database d;

			//Two test columns
			vector <string> column_names;
			column_names.push_back("Name");
			column_names.push_back("Attack_Power");

			//Two types
			vector <unsigned int> column_types;
			column_types.push_back(STRING);
			column_types.push_back(INT);

			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);

			//Create two tables.
			table characters("Characters", column_names, column_types, column_primary_keys); //Has Dart, Rose
			table characters_prime("Characters\'", column_names, column_types, column_primary_keys); //Has Dart, Zeig

			//Create rows
			entity dart;
			dart.add_string_attribute("Dart");
			dart.add_int_attribute(64);
			entity rose;
			rose.add_string_attribute("Rose");
			rose.add_int_attribute(128);
			entity zeig;
			zeig.add_string_attribute("Zeig");
			zeig.add_int_attribute(256);

			//Put into table
			characters.addEntity(dart);
			characters.addEntity(rose);
			characters_prime.addEntity(dart);
			characters_prime.addEntity(zeig);

			table result = d.setDifference(characters, characters_prime);

			Assert::IsEqual(result.error_code, 0); //No errors in setUnion
			Assert::IsEqual(result.numColumns(), characters.numColumns());
			//Do some select checking.*/
			Assert::Fail();
			
		}

		TEST_METHOD(crossMultiplyTest){
			Assert::Fail();
		}

		TEST_METHOD(openTableTest){
			Assert::Fail();
		}

		TEST_METHOD(closeTableTest){
			Assert::Fail();
		}

		TEST_METHOD(writeTableTest){
			Assert::Fail();
		}

		TEST_METHOD(exitTest){
			Assert::Fail();
		}

		TEST_METHOD(showTest){
			Assert::Fail();
		}

		TEST_METHOD(renameTestSucceed){ //Broken because database, condition, and rename undefined.

			//Two test columns
			vector <string> column_names;
			column_names.push_back("Name");
			column_names.push_back("Attack_Power");
			//Two types
			vector <unsigned int> column_types;
			column_types.push_back(STRING);
			column_types.push_back(INT);
			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);
			table characters("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity dart;
			dart.add_string_attribute("Dart");
			dart.add_int_attribute(64);
			//Put into table
			characters.addEntity(dart);
			//Primary part being tested.
			vector <string> new_col_names;
			new_col_names.push_back("LoD_name");
			new_col_names.push_back("LoD_Attk_Pwr");
			table renamed = d.rename(new_col_names, characters);
			Assert::IsEqual(renamed.error_code, 0); //Success in renaming.
			Assert::IsEqual(renamed.numEntities(), characters.numEntities());
			Assert::IsEqual(renamed.numColumns(), characters.numColumns());
			//Do some select checking.
		}

		TEST_METHOD(renameTestColumnException){ //For when too many column names are sent in vector.
			//Two test columns
			vector <string> column_names;
			column_names.push_back("Name");
			column_names.push_back("Attack_Power");
			//Two types
			vector <unsigned int> column_types;
			column_types.push_back(STRING);
			column_types.push_back(INT);
			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);
			table characters("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity dart;
			dart.add_string_attribute("Dart");
			dart.add_int_attribute(64);
			//Put into table
			characters.addEntity(dart);
			//Primary part being tested.
			vector <string> new_col_names;
			new_col_names.push_back("LoD_name");
			new_col_names.push_back("LoD_Attk_Pwr");
			new_col_names.push_back("LoD_Defense");
			table renamed = d.rename(new_col_names, characters);
			Assert::IsEqual(renamed.error_code, ERR_TOO_MANY_COLUMNS);
		}

		TEST_METHOD(unionTest){

			/*Database d;

			//Two test columns
			vector <string> column_names;
			column_names.push_back("Name");
			column_names.push_back("Attack_Power");
			//Two types
			vector <unsigned int> column_types;
			column_types.push_back(STRING);
			column_types.push_back(INT);
			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);
			table characters("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity dart;
			dart.add_string_attribute("Dart", 10);
			dart.add_int_attribute(64);
			//Put into table
			characters.addEntity(dart);

			//A different, but union compatible table

			column_primary_keys.push_back(0);
			table characters_prime("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity rose;
			rose.add_string_attribute("Rose", 10);
			rose.add_int_attribute(128);
			//Put into table
			characters_prime.addEntity(rose);
			table result = d.setUnion(characters, characters_prime);
			Assert::IsEqual(result.error_code, 0); //No errors in setUnion
			Assert::IsEqual(result.numEntities(), characters.numEntities()+characters_prime.numEntities()); //This is only true if primary key is not equivalent.
			Assert::IsEqual(result.numColumns(), characters.numColumns());
			Assert::IsEqual(result.numColumns(), characters_prime.numColumns());
			//Do select testing.*/
			Assert::Fail();

		}

		TEST_METHOD(productTest){
			Assert::Fail();
		}

		TEST_METHOD(naturalJoinTest){
			Assert::Fail();
		}

		TEST_METHOD(updateTest){
			Assert::Fail();
		}
	};
}