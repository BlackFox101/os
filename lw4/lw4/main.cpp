#include <iostream>
#include <fstream>
#include <string>

#include "RegexMachine.h"

using namespace std;

struct Machine
{
    using To = std::string;
    using From = std::string;
    using Transition = char;

    using PathsOfTo = std::map<Transition, std::set<To>>;
    using Cells = std::map<From, PathsOfTo>;

    Cells cells;
};

void DeleteEmptyTransitions(Machine& machine)
{

}

void Determinization(Machine& machine)
{

}

void WriteMachine(ofstream& output, const Machine& machine)
{

}

int main()
{
    ifstream input("input.txt");
    string regex;
    input >> regex;

    RegexMachine machine(regex);

    //DeleteEmptyTransitions(machine);
    //Determinization(machine);

    //ofstream output("output.txt");
    //WriteMachine(output, machine);
}