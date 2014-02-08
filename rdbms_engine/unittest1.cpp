#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "attribute.h"
#include "entity.h"
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
			entity test_entity;
			string_attribute attr_one("first attribute");
			int_attribute attr_two(64);
			Assert::AreEqual(test_entity.getAttribute(0).get_string_value(), attr_one.get_string_value());
			Assert::AreEqual(test_entity.getAttribute(1).get_int_value(), attr_one.get_int_value());
		}

		TEST_METHOD(differenceTest){
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

		TEST_METHOD(renameTest){
			Assert::Fail();
		}

		TEST_METHOD(unionTest){
			Assert::Fail();
		}

		TEST_METHOD(productTest){
			Assert::Fail();
		}

		TEST_METHOD(naturalJoinTest){
			Assert::Fail();
		}
	};
}