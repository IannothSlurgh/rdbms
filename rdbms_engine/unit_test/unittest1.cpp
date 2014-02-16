#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include "Database.h"
#define INTEGER 0

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{		
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(attributeTest){
			attribute test_attribute("Testing Attribute...", 20);
			attribute name_of_some_kind = test_attribute;
			Assert::AreEqual(test_attribute.get_string_value(), name_of_some_kind.get_string_value());

			attribute test_attribute_two(32);
			name_of_some_kind = test_attribute_two;
			Assert::AreEqual(test_attribute_two.get_int_value(), name_of_some_kind.get_int_value());
		}

		TEST_METHOD(tableTest){
			Assert::Fail();
		}

		TEST_METHOD(entityTest){
			entity test_entity;
			attribute attr_one("first attribute", 20);
			attribute attr_two(64);
			test_entity.addStringAttribute("first attribute", 20);
			test_entity.addIntAttribute(64);
			Assert::AreEqual(test_entity.getAttribute(0).get_string_value(), attr_one.get_string_value());
			Assert::AreEqual(test_entity.getAttribute(1).get_int_value(), attr_two.get_int_value());
		}

		TEST_METHOD(conditionTest){
			Assert::Fail();
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
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			string name;

			vector<string> column_name2;
			vector<unsigned int> column_type2;
			vector<unsigned int> primary_key2;
			
			vector<string> column_name_combined;
			vector<unsigned int> column_type_combined;
			vector<unsigned int> primary_key_combined;

			column_name.push_back("Type1");
			column_name2.push_back("Type2");
			column_name_combined.push_back("Type1");
			column_name_combined.push_back("Type2");

			column_type.push_back(1);
			column_type2.push_back(2);
			column_type_combined.push_back(1);
			column_type_combined.push_back(2);

			primary_key.push_back(3);
			primary_key2.push_back(4);
			primary_key_combined.push_back(3);
			primary_key_combined.push_back(4);

			table table1(name, column_name, column_type, primary_key);
			table table2(name, column_name2, column_type2, primary_key2);
			table combined_table(name, column_name_combined, column_type_combined, primary_key_combined);

			entity entity1;
			entity entity2;
			entity combined_entity;

			entity1.addStringAttribute("first attribute", 10);
			entity2.addIntAttribute(64);
			combined_entity.addStringAttribute("first attribute", 10);
			combined_entity.addIntAttribute(64);
			
			table1.addEntity(entity1);
			table2.addEntity(entity2);
			combined_table.addEntity(combined_entity);

			Database d;

			Assert::AreEqual(d.crossProduct(table1, table2), combined_table);
		}

		TEST_METHOD(insertIntoTest){
			Assert::Fail();
		}

		TEST_METHOD(deleteFromTest){
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
			column_types.push_back(INTEGER);
			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);
			table characters("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity dart;
			dart.addStringAttribute("Dart", 10);
			dart.addIntAttribute(64);
			//Put into table
			characters.addEntity(dart);
			//Primary part being tested.
			vector <string> new_col_names;
			new_col_names.push_back("LoD_name");
			new_col_names.push_back("LoD_Attk_Pwr");
			Database d;
			table renamed = d.rename(new_col_names, characters);
			Assert::AreEqual(renamed.error_code, 0); //Success in renaming.
			Assert::AreEqual(renamed.getNumOfEntities(), characters.getNumOfEntities());
			Assert::AreEqual(renamed.numOfColumns(), characters.numOfColumns());
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
			column_types.push_back(INTEGER);
			//Primary key name
			vector <unsigned int> column_primary_keys;
			column_primary_keys.push_back(0);
			table characters("Characters", column_names, column_types, column_primary_keys);
			//Create row
			entity dart;
			dart.addStringAttribute("Dart", 10);
			dart.addIntAttribute(64);
			//Put into table
			characters.addEntity(dart);
			//Primary part being tested.
			vector <string> new_col_names;
			new_col_names.push_back("LoD_name");
			new_col_names.push_back("LoD_Attk_Pwr");
			new_col_names.push_back("LoD_Defense");
			Database d;
			table renamed = d.rename(new_col_names, characters);
			Assert::AreEqual(renamed.error_code, ERR_TOO_MANY_COLUMNS);
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
			vector<string> cn1;
			vector<string> cn2;
			vector<string> natural_join_column_name;
			string name = "natural join table";

			cn1.push_back("Location");
			cn1.push_back("Restaurant");
			cn2.push_back("Location");
			cn2.push_back("Customer");

			natural_join_column_name.push_back("Location");
			natural_join_column_name.push_back("Restaurant");
			natural_join_column_name.push_back("Customer");

			vector<unsigned int> pk1;
			pk1.push_back(1);
			pk1.push_back(2);

			vector<unsigned int> pk2;
			pk2.push_back(1);
			pk2.push_back(3);

			vector<unsigned int> natural_join_primary_key;
			natural_join_primary_key.push_back(1);
			natural_join_primary_key.push_back(2);
			natural_join_primary_key.push_back(3);

			vector<unsigned int> ct1;
			ct1.push_back(1);
			ct1.push_back(1);

			vector<unsigned int> ct2;
			ct2.push_back(1);
			ct2.push_back(1);

			vector<unsigned int> natural_join_column_type;
			natural_join_column_type.push_back(1);
			natural_join_column_type.push_back(1);
			natural_join_column_type.push_back(1);

			table table_one(name, cn1, ct1, pk1);
			table table_two(name, cn2, ct2, pk2);
			table new_table(name, natural_join_column_name, natural_join_column_type, natural_join_primary_key);
			Database d;
			Assert::AreEqual(d.naturalJoin(table_one, table_two), new_table);
		}

		TEST_METHOD(projectionTest){
			vector<attribute> attr_list;

			attribute test_attribute("Testing Attribute...", 20);
			attribute test_attribute2(1);
			attribute test_attribute3(2);

			attribute attribute_string = test_attribute;
			attribute attribute_int = test_attribute2;
			attribute attribute_int2 = test_attribute3;

			attr_list.push_back(attribute_string);
			attr_list.push_back(attribute_int);

			vector<string> cn;
			cn.push_back("Testing Attribute...");
			cn.push_back("some int");

			vector<unsigned int> ct;
			ct.push_back(1);
			ct.push_back(0);

			vector<unsigned int> pk;
			pk.push_back(1);
			pk.push_back(0);

			entity test_entity;
			test_entity.addStringAttribute("Testing Attribute...", 20);
			test_entity.addIntAttribute(1);
			test_entity.addIntAttribute(2);
			entity entity1;
			entity1.addStringAttribute("Testing Attribute...", 20);
			entity1.addIntAttribute(1);

			table test_table("", cn, ct, pk);
			test_table.addEntity(entity1);
			Database d;
			Assert::AreEqual(d.project(attr_list, test_entity), test_table); //call from database
		}
	};
}