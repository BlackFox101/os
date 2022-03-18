#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>

using namespace std;

enum class Type
{
    Left,
    Right
};

std::ostream& operator<<(std::ostream& stream, const Type& type)
{
    if (type == Type::Left)
    {
        stream << "Left";
    }
    else
    {
        stream << "Right";
    }

    return stream;
}
std::istream& operator>>(std::istream& stream, Type& type)
{
    std::string str;
    stream >> str;

    if (str == "L")
    {
        type = Type::Left;
    }
    else
    {
        type = Type::Right;
    }

    return stream;
}

using Cell = map<string, set<string>>;
using Machine = map<string, Cell>;

void ReadRightGrammar(ifstream& input, Machine& machine)
{
    string line;

    while (getline(input, line))
    {

    }
}

void ReadLeftGrammar(ifstream& input, Machine& machine)
{
    string line;

    while (getline(input, line))
    {

    }
}

void Init(Machine& machine, Type& type)
{
    ifstream input;
    input.open("input.txt");
    input >> type;

    if (type == Type::Right)
    {
        ReadRightGrammar(input, machine);
    }
    else
    {
        ReadLeftGrammar(input, machine);
    }
}

int main()
{
    Machine machine;
    Type type;

    Init(machine, type);
}
