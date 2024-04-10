#include "pch.h"
#include "CppUnitTest.h"
#include "../RPN/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RPNTest
{
	TEST_CLASS(RPNTest)
	{
	public:
		
		TEST_METHOD(CalculationTest)
		{
			string expression = "11 + 7 - (5 + 2)";
			ExpressionForNotation E(expression);

			Assert::AreEqual(11., E.calculateResult());
		}

		TEST_METHOD(ConventionTest)
		{
			string expression = "11 + 7 - (5 + 2)";
			ExpressionForNotation e(expression);
			string expected_result = "11 7 + 5 2 + -";
			Assert::AreEqual(expected_result, e.converter());
		}

		TEST_METHOD(InvalidOperatorTest)
		{
			string expression = "(34 * 2) ^ 3 - 1078 + (56 - 105)";
			ExpressionForNotation e(expression);
			string expected = "34 2 * 3 ^ 1078 - 56 105 - +";

			Assert::AreEqual(expected, e.converter());
			Assert::AreEqual(313305., e.calculateResult());
		}
	};
}
