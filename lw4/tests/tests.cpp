#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../lw4/ReadRegex.h"
#include "../lw4/RegexMachine.h"

using namespace std;

TEST_CASE("AddTransition")
{
	WHEN("a + b")
	{
		vector<string> transitions = { "a" };
		AddConcatenation(transitions, "b");

		CHECK(transitions.size() == 2);
		CHECK(transitions[0] == "a");
		CHECK(transitions[1] == "b");
	}

	WHEN("[a, b|] + a")
	{
		vector<string> transitions = { "a", "b|" };
		AddConcatenation(transitions, "a");

		THEN("[a, b|a]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "a");
			CHECK(transitions[1] == "b|a");
		}
	}

	WHEN("[a, b] + |a")
	{
		vector<string> transitions = { "a", "b" };
		AddConcatenation(transitions, "|a");

		THEN("[a, b|a]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "a");
			CHECK(transitions[1] == "b|a");
		}
	}
}

TEST_CASE("ConvertConcatenation")
{
	string regex = "(x|y*)|(xa)+";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[(x|y*)|(xa)+]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "(x|y*)|(xa)+");
		}
	}

	regex = "ab";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[a, b]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "a");
			CHECK(transitions[1] == "b");
		}
	}

	regex = "a|b";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[a|b]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "a|b");
		}
	}

	regex = "ab|a";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[a, b|a]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "a");
			CHECK(transitions[1] == "b|a");
		}
	}

	regex = "(xy)";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[(xy)]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "(xy)");
		}
	}

	regex = "123(4(5|6))(5)ab*c+(d)";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[1, 2, 3, (4(5|6)), (5), a, b*, c+, (d)]")
		{
			CHECK(transitions.size() == 9);
			CHECK(transitions[0] == "1");
			CHECK(transitions[1] == "2");
			CHECK(transitions[2] == "3");
			CHECK(transitions[3] == "(4(5|6))");
			CHECK(transitions[4] == "(5)");
			CHECK(transitions[5] == "a");
			CHECK(transitions[6] == "b*");
			CHECK(transitions[7] == "c+");
			CHECK(transitions[8] == "(d)");
		}
	}

	regex = "(xy*|ab|(x|a*))(x|y*)|()";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[xy*|ab|(x|a*), (x|y*)|()]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "(xy*|ab|(x|a*))");
			CHECK(transitions[1] == "(x|y*)|()");
		}
	}

	regex = "(xy*|ab|(x|a*))(x|y*)";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[xy*|ab|(x|a*), x|y*]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "(xy*|ab|(x|a*))");
			CHECK(transitions[1] == "(x|y*)");
		}
	}
	regex = "(x|y*)|(a)+";
	WHEN(regex)
	{
		vector<string> transitions = ConvertConcatenation(regex);

		THEN("[(x|y*)|(a)+")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "(x|y*)|(a)+");
		}
	}
}

TEST_CASE("ClearExtraBrackets")
{
	string transition = "(xa)+";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("(xa)+")
		{
			CHECK(transition == "(xa)+");
		}
	}

	transition = "((a))";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("a")
		{
			CHECK(transition == "a");
		}
	}

	transition = "a";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("a")
		{
			CHECK(transition == "a");
		}
	}

	transition = "(a)";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("a")
		{
			CHECK(transition == "a");
		}
	}

	transition = "(a)(b|a)";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("(a)(b|a)")
		{
			CHECK(transition == "(a)(b|a)");
		}
	}

	transition = "(xy*)|(x|y*)|(b)";
	WHEN(transition)
	{
		ClearExtraBrackets(transition);

		THEN("(xy*)|(x|y*)|(b)")
		{
			CHECK(transition == "(xy*)|(x|y*)|(b)");
		}
	}
}

TEST_CASE("AddUnion")
{
	WHEN(" + (a)")
	{
		vector<string> transitions;
		AddUnion(transitions, "(a)");

		THEN("[a]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "a");
		}
	}

	WHEN(" + (a)(b|a)")
	{
		vector<string> transitions;
		AddUnion(transitions, "(a)(b|a)");

		THEN("[(a)(b|a)]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "(a)(b|a)");
		}
	}
}

TEST_CASE("ConvertUnion")
{
	string regex = "(x|y*)|(xa)+";
	WHEN(regex)
	{
		vector<string> transitions = ConvertUnion(regex);

		THEN("[x|y*, (xa)+]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "x|y*");
			CHECK(transitions[1] == "(xa)+");
		}
	}

	WHEN("(a|b)")
	{
		const string regex = "(a|b)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[a, b]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "a");
			CHECK(transitions[1] == "b");
		}
	}

	WHEN("xy*|ab|(x|a*)")
	{
		const string regex = "xy*|ab|(x|a*)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[xy*, ab, x|a*]")
		{
			CHECK(transitions.size() == 3);
			CHECK(transitions[0] == "xy*");
			CHECK(transitions[1] == "ab");
			CHECK(transitions[2] == "x|a*");
		}
	}

	WHEN("(xy*|ab|(x|a*))(x|y*)|(a)")
	{
		const string regex = "(xy*|ab|(x|a*))(x|y*)|(a)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[(xy*|ab|(x|a*))(x|y*), a]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "(xy*|ab|(x|a*))(x|y*)");
			CHECK(transitions[1] == "a");
		}
	}

	WHEN("(xy*|ab|(x|a*))|(x|y*)|(b)")
	{
		const string regex = "(xy*|ab|(x|a*))|(x|y*)|(b)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[xy*|ab|(x|a*), x|y*, b]")
		{
			CHECK(transitions.size() == 3);
			CHECK(transitions[0] == "xy*|ab|(x|a*)");
			CHECK(transitions[1] == "x|y*");
			CHECK(transitions[2] == "b");
		}
	}
}

TEST_CASE("DeleteSpecialChar")
{
	string regex = "(a)|(ab)+";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("(a)|(ab)+")
		{
			CHECK(regex == "(a)|(ab)+");
		}
	}

	regex = "((ab))+";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("ab")
		{
			CHECK(regex == "ab");
		}
	}

	regex = "(ab)+";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("ab")
		{
			CHECK(regex == "ab");
		}
	}

	regex = "ab+";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("ab+")
		{
			CHECK(regex == "ab+");
		}
	}

	regex = "a|b";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("a|b")
		{
			CHECK(regex == "a|b");
		}
	}

	regex = "a+b";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("a+b")
		{
			CHECK(regex == "a+b");
		}
	}

	regex = "a+b";
	WHEN(regex)
	{
		DeleteSpecialChar(regex);
		THEN("a+b")
		{
			CHECK(regex == "a+b");
		}
	}
}