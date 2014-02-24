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
		TEST_METHOD(createTableTest){
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			vector<unsigned int> cw;
			string name = "create table test";

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);
			cw.push_back(10);

			table new_table(name, column_name, column_type, primary_key, cw);

			Database d;
			d.createTable(name, column_name, column_type, primary_key, cw);
			Assert::IsTrue(d.findTable(name) == new_table);
		}
		TEST_METHOD(dropTableTest){
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			vector<unsigned int> cw;
			string name = "drop table test";

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);
			cw.push_back(10);

			table empty_table;
			Database d;
			d.createTable(name, column_name, column_type, primary_key, cw);
			d.dropTable(name);
			Assert::IsTrue(d.getNumOfTables() == 0);
		}
		
		TEST_METHOD(attributeTest){
			attribute test_attribute("Testing Attribute...");
			attribute name_of_some_kind = test_attribute;
			Assert::AreEqual(test_attribute.get_string_value(), name_of_some_kind.get_string_value());

			attribute test_attribute_two(32);
			name_of_some_kind = test_attribute_two;
			Assert::AreEqual(test_attribute_two.get_int_value(), name_of_some_kind.get_int_value());
		}

		TEST_METHOD(tableTest){
			string name = "Some Test Table";

			vector<unsigned int> types;
			types.push_back(STRING);
			types.push_back(INTEGER);

			vector<string> names;
			names.push_back("Some String Attribute");
			names.push_back("Some Integer Attribute");

			vector<unsigned int> primary_key;
			primary_key.push_back(0);

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);

			table test_table(name, names, types, primary_key, cw);

			entity e1;
			e1.addStringAttribute("test value");
			e1.addIntAttribute(50);
			test_table.addEntity(e1);

			entity e2;
			e2.addStringAttribute("another test value");
			e2.addIntAttribute(33);
			test_table.addEntity(e2);

			Assert::AreEqual(test_table.getNumOfEntities(), 2);

			test_table.removeEntity(0);
			Assert::AreNotEqual(test_table.getNumOfEntities(), 2);

			vector<attribute> pkeys;
			pkeys.push_back(attribute("another test value"));
			entity test_entity = test_table.getEntityWith(pkeys);
			Assert::AreEqual(test_entity.getAttribute(1).get_int_value(), 33);

			test_table.renameColumn("This works!", 0);

			int test_num = test_table.getColumnNames()[0].compare("This works!");
			Assert::AreEqual(test_num ,0);

			Assert::IsTrue(test_table == test_table);
		}

		TEST_METHOD(entityTest){
			entity test_entity;
			attribute attr_one("first attribute");
			attribute attr_two(64);
			test_entity.addStringAttribute("first attribute");
			test_entity.addIntAttribute(64);
			Assert::AreEqual(test_entity.getAttribute(0).get_string_value(), attr_one.get_string_value());
			Assert::AreEqual(test_entity.getAttribute(1).get_int_value(), attr_two.get_int_value());
		}

		TEST_METHOD(conditionTest){
			string name = "Some Test Table";

			vector<unsigned int> types;
			types.push_back(STRING);
			types.push_back(INTEGER);

			vector<string> names;
			names.push_back("Some String Attribute");
			names.push_back("Some Integer Attribute");

			vector<unsigned int> primary_key;
			primary_key.push_back(0);

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);

			table test_table(name, names, types, primary_key, cw);

			entity e1;
			e1.addStringAttribute("test value");
			e1.addIntAttribute(50);
			test_table.addEntity(e1);

			entity e2;
			e2.addStringAttribute("another test value");
			e2.addIntAttribute(33);
			test_table.addEntity(e2);

			Condition test_condition(test_table, "==");
			Condition test_condition_two(test_table, "==");

			test_condition.addFirstOperand("Some Integer Attribute");
			test_condition.addSecondOperand(attribute(50));

			test_condition_two.addFirstOperand("Some String Attribute");
			test_condition_two.addSecondOperand(attribute("another test value"));
			
			Assert::IsTrue(test_condition_two.result(1));
			Assert::IsTrue(test_condition.result(0));
			
		}

		TEST_METHOD(differenceTest){

			Database d;

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

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);
			//Create two tables.
			table characters("Characters", column_names, column_types, column_primary_keys, cw); //Has Dart, Rose
			table characters_prime("Characters\'", column_names, column_types, column_primary_keys, cw); //Has Dart, Zieg

			//Create rows
			entity dart;
			dart.addStringAttribute("Dart");
			dart.addIntAttribute(64);
			entity rose;
			rose.addStringAttribute("Rose");
			rose.addIntAttribute(128);
			entity zieg;
			zieg.addStringAttribute("Zieg");
			zieg.addIntAttribute(256);

			//Put into table
			characters.addEntity(dart);
			characters.addEntity(rose);
			characters_prime.addEntity(dart);
			characters_prime.addEntity(zieg);

			table result = d.setDifference(characters, characters_prime);

			Assert::AreEqual(result.error_code, 0); //No errors in setUnion
			Assert::AreEqual(result.numOfColumns(), characters.numOfColumns());
			Assert::AreEqual(result.getNumOfEntities(), 1);
			//Check if single row is Rose (it should be) Dart, Rose - Dart, Zieg
			entity e = result.getEntityAt(0);
			Assert::IsTrue(e==rose);//Answer should be Rose.
			
		}

		TEST_METHOD(crossMultiplyTest){
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			string name = "cross product table";

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

			primary_key.push_back(0);
			primary_key2.push_back(0);
			primary_key_combined.push_back(0);
			primary_key_combined.push_back(1);

			vector<unsigned int> cw;
			cw.push_back(10);

			vector<unsigned int> col_w;
			col_w.push_back(10);
			col_w.push_back(10);

			table table1(name, column_name, column_type, primary_key, cw);
			table table2(name, column_name2, column_type2, primary_key2, cw);
			table combined_table(name, column_name_combined, column_type_combined, primary_key_combined, col_w);

			entity entity1;
			entity entity2;
			entity combined_entity;

			entity1.addStringAttribute("first attribute");
			entity2.addIntAttribute(64);
			combined_entity.addStringAttribute("first attribute");
			combined_entity.addIntAttribute(64);
			
			table1.addEntity(entity1);
			table2.addEntity(entity2);
			combined_table.addEntity(combined_entity);

			Database d;

			Assert::IsTrue(d.crossProduct(table1, table2) == combined_table);
		}

		TEST_METHOD(insertTableTest1){
			vector <string> column_names;
			vector <unsigned int> primary_keys;
			vector <unsigned int> column_types;

			column_names.push_back("Name");
			column_names.push_back("Attack Power");
			primary_keys.push_back(0);
			column_types.push_back(STRING);
			column_types.push_back(INTEGER);

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);

			Database d;
			d.createTable("characters", column_names, column_types, primary_keys, cw);

			table enemies("enemies", column_names, column_types, primary_keys, cw);

			entity lloyd;
			lloyd.addStringAttribute("Lloyd");
			lloyd.addIntAttribute(270);

			enemies.addEntity(lloyd);

			d.insertIntoTable("characters", enemies);

			table get = d.findTable("characters");

			Assert::IsTrue(get==enemies);
		}

		TEST_METHOD(insertTableTest2){
			vector <string> column_names;
			vector <unsigned int> primary_keys;
			vector <unsigned int> column_types;

			column_names.push_back("Name");
			column_names.push_back("Attack Power");
			primary_keys.push_back(0);
			column_types.push_back(STRING);
			column_types.push_back(INTEGER);

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);

			Database d;
			d.createTable("characters", column_names, column_types, primary_keys, cw);

			table enemies("enemies", column_names, column_types, primary_keys, cw);

			entity lloyd;
			attribute a("Lloyd");
			attribute b(270);
			lloyd.addAttribute(a);
			lloyd.addAttribute(b);
			vector <attribute> attr_list;
			attr_list.push_back(a);
			attr_list.push_back(b);
			
			enemies.addEntity(lloyd);



			d.insertIntoTable("characters", attr_list);

			table get = d.findTable("characters");

			Assert::IsTrue(get==enemies);
	}

		TEST_METHOD(DeleteFromTest){
			vector<string> column_name;
			vector<string> new_column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> new_column_type;
			vector<unsigned int> primary_key;
			vector<unsigned int> new_primary_key;
			vector<unsigned int> col_w;
			vector<unsigned int> new_col_w;
			string name = "create table test";
			vector<attribute> attr_list;

			attr_list.push_back(attribute(0));

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);
			new_col_w.push_back(10);
			col_w.push_back(10);

			table new_table(name, new_column_name, new_column_type, new_primary_key, new_col_w);

			Database d;
			d.createTable(name, column_name, column_type, primary_key, col_w);
			d.insertIntoTable(name, attr_list);
			Condition con(d.findTable(name), "==");
			con.addFirstOperand("ints");
			con.addSecondOperand(attr_list[0]);

			d.deleteFromTable(name, con);
			Assert::IsTrue(d.findTable(name).getNumOfEntities() == 0);
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

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);
			table characters("Characters", column_names, column_types, column_primary_keys, cw);
			//Create row
			entity dart;
			dart.addStringAttribute("Dart");
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
			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);
			table characters("Characters", column_names, column_types, column_primary_keys, cw);
			//Create row
			entity dart;
			dart.addStringAttribute("Dart");
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

			Database d;

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
			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);
			table characters("Characters", column_names, column_types, column_primary_keys, cw);
			//Create two rows
			entity dart;
			dart.addStringAttribute("Dart");
			dart.addIntAttribute(64);
			entity rose;
			rose.addStringAttribute("Rose");
			rose.addIntAttribute(128);
			//Put into table
			characters.addEntity(dart);
			characters.addEntity(rose);

			//A different, but union compatible table
			
			//Create two new row
			entity rose2;
			rose2.addStringAttribute("Rose");
			rose2.addIntAttribute(43);
			entity zieg;
			zieg.addStringAttribute("Zieg");
			zieg.addIntAttribute(256);
			vector<unsigned int> cw2;
			cw2.push_back(10);
			cw2.push_back(10);
			table characters_prime("Characters", column_names, column_types, column_primary_keys, cw2);
			//Put into table
			characters_prime.addEntity(rose2);
			characters_prime.addEntity(zieg);
			table result = d.setUnion(characters, characters_prime);
			Assert::AreEqual(result.error_code, 0); //No errors in setUnion
			//Columns should all be same.
			Assert::AreEqual(result.numOfColumns(), characters.numOfColumns());
			Assert::AreEqual(result.numOfColumns(), characters_prime.numOfColumns());
			//Do select testing.
			Assert::AreEqual(result.getNumOfEntities(), 3);
			entity e = result.getEntityAt(0);
			Assert::IsTrue(e==dart);
			e = result.getEntityAt(1); //A duplicate case
			Assert::IsTrue(e==rose);
			e = result.getEntityAt(2);
			Assert::IsTrue(e==zieg);
			Assert::AreEqual(result.getNumOfEntities(), 3);
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
			natural_join_primary_key.push_back(0);
			natural_join_primary_key.push_back(1);
			natural_join_primary_key.push_back(2);

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

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);

			vector<unsigned int> cw2;
			cw2.push_back(10);
			cw2.push_back(10);
			cw2.push_back(10);

			table table_one(name, cn1, ct1, pk1, cw);
			table table_two(name, cn2, ct2, pk2, cw);
			table new_table(name, natural_join_column_name, natural_join_column_type, natural_join_primary_key, cw2);
			Database d;
			Assert::IsTrue(d.naturalJoin(table_one, table_two) == new_table);
		}

		TEST_METHOD(projectionTest){
			vector<string> attr_list;
			attr_list.push_back("string");
			attr_list.push_back("int");

			vector<string> cn_one;
			vector<unsigned int> ct_one;
			vector<unsigned int> pk_one;

			vector<unsigned int> ct_two;
			vector<unsigned int> pk_two;

			cn_one.push_back("string");
			cn_one.push_back("int");
			cn_one.push_back("disappear");

			ct_one.push_back(1);
			ct_one.push_back(0);
			ct_one.push_back(1);
			
			ct_two.push_back(1);
			ct_two.push_back(0);
			
			pk_one.push_back(0);
			pk_one.push_back(1);
			pk_one.push_back(2);

			pk_two.push_back(0);
			pk_two.push_back(1);

			vector<unsigned int> cw;
			cw.push_back(10);
			cw.push_back(10);
			cw.push_back(10);

			vector<unsigned int> cw2;
			cw2.push_back(10);
			cw2.push_back(10);

			table test_table_one("project table", cn_one, ct_one, pk_one, cw);
			table test_table_two("project table", attr_list, ct_two, pk_two, cw2);
			Database d;
			
			Assert::IsTrue(d.project(attr_list, test_table_one) == test_table_two);
		}

		TEST_METHOD(updateEntityTest){
			string table_name = "something";
			vector<string> cn;
			cn.push_back("String Column");
			vector<unsigned int> ct;
			ct.push_back(STRING);
			vector<unsigned int> pk;
			pk.push_back(0);

			vector<unsigned int> cw;
			cw.push_back(10);

			table compare_table(table_name, cn, ct, pk, cw);
			entity new_entity;
			new_entity.addAttribute(attribute("string"));
			compare_table.addEntity(new_entity);

			table new_table(table_name, cn, ct, pk, cw);
			vector<attribute> n;
			n.push_back(attribute("test"));
			

			Database d;
			d.createTable(table_name, cn, ct, pk, cw);
			d.insertIntoTable(table_name, n);

			vector<attribute> attr_l;
			attr_l.push_back(attribute("string"));

			Condition cond(d.findTable(table_name), "==");
			cond.addFirstOperand("String Column");
			cond.addSecondOperand(attribute("test"));

			d.updateEntity(table_name, cn, attr_l, cond);
			Assert::IsTrue(d.getNumOfTables() == 1);
			Assert::IsTrue(d.findTable(table_name).getEntityAt(0).getAttribute(0).get_string_value().compare("string") == 0);
		}

		TEST_METHOD(selectTest){
			Database d;
			string name = "something";
			vector<string> cn;
			cn.push_back("String Column");

			vector<unsigned int> ct;
			ct.push_back(STRING);

			vector<unsigned int> pk;
			pk.push_back(0);

			vector<unsigned int> cw;
			cw.push_back(10);

			d.createTable(name, cn, ct, pk, cw);
			
			vector<attribute> a1;
			a1.push_back(attribute("name"));
			d.insertIntoTable(name, a1);

			vector<attribute> a2;
			a2.push_back(attribute("wrong"));
			d.insertIntoTable(name, a2);

			Condition cond(d.findTable(name), "==");
			cond.addFirstOperand("String Column");
			cond.addSecondOperand(attribute("name"));

			table test_table("", cn, ct, pk,cw);
			entity e;
			e.addAttribute(attribute("name"));
			test_table.addEntity(e);

			Assert::IsTrue(d.select(cond, d.findTable(name)) == test_table);
		}
	};
}