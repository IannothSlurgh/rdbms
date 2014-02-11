#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "attribute.h"
#include "entity.h"
#include "table.h"
#include <string>
#define INTEGER 0

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unit_test
{		
	TEST_CLASS(unittest1)
	{
	public:
		
		TEST_METHOD(attributeTest){
			string_attribute test_attribute("Testing Attribute...");
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
			/*entity test_entity;
			string_attribute attr_one("first attribute");
			int_attribute attr_two(64);
			test_entity.addStringAttribute("first attribute");
			test_entity.addIntAttribute(4);
			Assert::AreEqual(((string_attribute)(test_entity.getAttribute(0))).get_string_value(), attr_one.get_string_value());
			Assert::AreEqual(((int_attribute)(test_entity.getAttribute(1))).get_int_value(), attr_two.get_int_value());
		*/}

		TEST_METHOD(differenceTest){
			Assert::Fail();
			
		}
		TEST_METHOD(createTableTest){
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			string name = "create table test";

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);
			table new_table(name, column_name, column_type, primary_key);

			database d;
			d.createTable(name, column_name, column_type, primary_key);
			Assert::IsTrue(d.findTable(name) == new_table);
		}
		TEST_METHOD(dropTableTest){
			vector<string> column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> primary_key;
			string name = "drop table test";

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);

			table empty_table();
			database d;
			d.createTable(name, column_name, column_type, primary_key);
			d.dropTable(name);
			bool check = d.findTable(name) == empty_table;
			Assert::IsTrue(check);
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
			column_name_combined.push_back("Type2$");

			column_type.push_back(1);
			column_type2.push_back(0);
			column_type_combined.push_back(1);
			column_type_combined.push_back(0);

			primary_key.push_back(0);
			primary_key2.push_back(0);
			primary_key_combined.push_back(0);
			primary_key_combined.push_back(1);

			table table1(name, column_name, column_type, primary_key);
			table table2(name, column_name2, column_type2, primary_key2);
			table combined_table(name, column_name_combined, column_type_combined, primary_key_combined);

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

			Assert::AreEqual(crossProduct(table1, table2), combined_table);
		}

		TEST_METHOD(insertIntoTest){
			
		}

		TEST_METHOD(DeleteFromTest){
			vector<string> column_name;
			vector<string> new_column_name;
			vector<unsigned int> column_type;
			vector<unsigned int> new_column_type;
			vector<unsigned int> primary_key;
			vector<unsigned int> new_primary_key;
			string name = "create table test";
			vector<attribute> attr_list;

			attr_list.push_back(attribute(0));

			column_name.push_back("ints");
			column_type.push_back(0);
			primary_key.push_back(0);

			table new_table(name, new_column_name, new_column_type, new_primary_key);

			Database d;
			d.createTable(name, column_name, column_type, primary_key);
			d.insertIntoTable(name, attr_list);
			Condition con(name, "==");
			con.addFirstOperand("ints");
			con.addSecondOperand(attr_list[0]);

			d.deleteFromTable(name, con);
			Assert::IsTrue(d.findTable(name).getNumOfEntities == 0);
		}

		TEST_METHOD(renameTest){
			Assert::Fail();
		}

		TEST_METHOD(unionTest){
			Assert::Fail();
		}
		TEST_METHOD(updateEntityTest){
			string table_name = "Table";
			vector<string> cn;
			vector<unsigned int> ct;
			vector<unsigned int> pk;
			vector<string> cn_test;
			vector<unsigned int> ct_test;
			vector<unsigned int> pk_test;
			vector<attribute> attr_list;
			vector<attribute> attr_list_test;

			cn.push_back("test_strings");
			cn_test.push_back("test_strings");
			cn.push_back("test_ints");
			cn_test.push_back("test_ints");

			ct.push_back(1);
			ct_test.push_back(1);
			ct.push_back(1);
			ct_test.push_back(1);

			pk.push_back(1);
			pk_test.push_back(1);
			pk.push_back(2);
			pk_test.push_back(2);

			entity test_entity_one;
			entity test_entity_two;

			string_attribute test_attribute_one("Testing Attribute...");
			attribute attr_one = test_attribute_one;

			int_attribute test_attribute_two(1);
			attribute attr_two = test_attribute_two;
			
			test_entity_one.addStringAttribute(attr_one);
			test_entity_one.addIntAttribute(attr_two);


			string_attribute test_attribute_three("different");
			attr_one = test_attribute_three;

			int_attribute test_attribute_three(64);
			attr_two = test_attribute_three;

			test_entity_two.addIntAttribute(attr_two);
			test_entity_two.addStringAttribute(attr_one);

			attr_list.push_back(attr_one);
			attr_list.push_back(attr_two);
			
			test_entity_one.addStringAttribute(attr_one);
			test_entity_one.addStringAttribute(attr_two);

			Condition con;
			con = new Condition(*test_table, "==");

			table test_table(table_name, cn, ct, pk);
			test_table.addEntity(test_entity_one);

			table new_table(table_name, cn, ct, pk);
			new_table.addEntity(test_entity_two);

			Database database();
			database.createTable(table_name, cn_test, ct_test, pk_test);
			database.updateEntity(table_name, attr_names, attr_list, con);
			bool check = new_table == database.findTable(table_name);
			Assert::IsTrue(check);
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
			Assert::AreEqual(naturalJoin(table_one, table_two), new_table);
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

			table test_table_one("project table", cn_one, ct_one, pk_one);
			table test_table_two("project table", attr_list, ct_two, pk_two);
			Assert::AreEqual(project(attr_list, test_table_two), test_table_one);
		}
	};
}