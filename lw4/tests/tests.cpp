#include <iostream>
#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../lw4/ReadRegex.h"
#include "../lw4/RegexMachine.h"

using namespace std;

/*TEST_CASE("AddTransition")
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
}*/

/*TEST_CASE("ConvertConcatenation")
{
	string regex = "ab";
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
}*/

/*TEST_CASE("ConvertUnion")
{
	WHEN("(a|b)")
	{
		const string regex = "(a|b)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[(a|b)]")
		{
			CHECK(transitions.size() == 1);
			CHECK(transitions[0] == "(a|b)");
		}
	}

	WHEN("xy*|ab|(x|a*)")
	{
		const string regex = "xy*|ab|(x|a*)";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[xy*, ab, (x|a*)]")
		{
			CHECK(transitions.size() == 3);
			CHECK(transitions[0] == "xy*");
			CHECK(transitions[1] == "ab");
			CHECK(transitions[2] == "(x|a*)");
		}
	}

	WHEN("(xy*|ab|(x|a*))(x|y*)|()")
	{
		const string regex = "(xy*|ab|(x|a*))(x|y*)|()";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[(xy*|ab|(x|a*))(x|y*), ()]")
		{
			CHECK(transitions.size() == 2);
			CHECK(transitions[0] == "(xy*|ab|(x|a*))(x|y*)");
			CHECK(transitions[1] == "()");
		}
	}

	WHEN("(xy*|ab|(x|a*))|(x|y*)|()")
	{
		const string regex = "(xy*|ab|(x|a*))|(x|y*)|()";
		vector<string> transitions = ConvertUnion(regex);

		THEN("[(xy*|ab|(x|a*)), (x|y*), ()]")
		{
			CHECK(transitions.size() == 3);
			CHECK(transitions[0] == "(xy*|ab|(x|a*))");
			CHECK(transitions[1] == "(x|y*)");
			CHECK(transitions[2] == "()");
		}
	}
}*/

TEST_CASE("GetMachine")
{
	const string regex = "(xy*|ab|(x|a*))(x|y*)";
	RegexMachine machine(regex);
	WHEN("")
	{
		THEN("")
		{

		}
	}
}