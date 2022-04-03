#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

enum class Type
{
    Left,
    Right
};

struct Machine
{
    using To = string;
    using From = string;
    using Transition = char;

    using PathsOfTo = map<Transition, set<To>>;
    using Cells = map<From, PathsOfTo>;

    Type type = Type::Left;
    Cells cells;
};

const char SEPARATOR1 = ':';
const char SEPARATOR2 = '|';
const char END_CHARACTER = 'H';

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

vector<string> GetStringVectorOfPaths(string paths, size_t startPos)
{
    vector<string> stringPaths;
    size_t prevPos = startPos;
    size_t nextPos;
    while ((nextPos = paths.find(SEPARATOR2, prevPos)) != string::npos)
    {
        stringPaths.push_back(paths.substr(prevPos, nextPos - prevPos));
        prevPos = nextPos + 1;
    }
    stringPaths.push_back(paths.substr(prevPos));

    return stringPaths;
}

void ReadRightGrammar(ifstream& input, Machine& machine)
{
    string line;
    getline(input, line);

    while (getline(input, line))
    {
        size_t prevPos = line.find(SEPARATOR1);
        string from = line.substr(0, prevPos);
        prevPos += 1;

        vector<string> stringPaths = GetStringVectorOfPaths(line, prevPos);

        Machine::PathsOfTo paths;
        for (auto& path : stringPaths)
        {
            Machine::Transition transition = path[0];
            if (path.length() == 2)
            {
                paths[transition].insert(string(1, path[1]));
            }
            else
            {
                paths[transition].insert(string(1, END_CHARACTER));
            }
        }
        machine.cells[from] = paths;
    }
}

void ReadLeftGrammar(ifstream& input, Machine& machine)
{
    string line;
    getline(input, line);

    while (getline(input, line))
    {
        size_t prevPos = line.find(SEPARATOR1);
        string to = line.substr(0, prevPos);
        prevPos += 1;

        vector<string> stringPaths = GetStringVectorOfPaths(line, prevPos);
        for (auto& path : stringPaths)
        {
            string from;
            Machine::Transition transition;
            if (path.length() == 2)
            {
                from = path[0];
                transition = path[1];
            }
            else
            {
                from = string(1, END_CHARACTER);
                transition = path[0];
            }
            machine.cells[from][transition].insert(to);
        }
    }
}

void Determinization(Machine& machine)
{
    Machine::Cells cells;

    Machine::PathsOfTo paths = machine.cells["S"];
    if (machine.type == Type::Right)
    {
        paths = machine.cells["S"];
        cells["S"] = paths;
    }
    else
    {
        paths = machine.cells["H"];
        cells["H"] = paths;
    }

    stack<Machine::To> nextStates;
    for (auto& path : paths)
    {
        string to;
        for (auto& state : path.second)
        {
            to += state;
        }
        nextStates.push(to);
    }

    while (!nextStates.empty())
    {
        auto from = nextStates.top();
        nextStates.pop();

        if (cells.find(from) != cells.end())
        {
            continue;
        }

        for (auto ch : from)
        {
            string state = string(1, ch);
            auto currentStatePathsIt = machine.cells.find(state);

            if (currentStatePathsIt == machine.cells.end())
            {
                continue;
            }

            for (auto currentStatePaths : currentStatePathsIt->second)
            {
                for (auto currentTo : currentStatePaths.second)
                {
                    cells[from][currentStatePaths.first].insert(currentTo);
                }
            }

            for (auto cell : cells[from])
            {
                string to;
                for (auto str : cell.second)
                {
                    to += str;
                }

                nextStates.push(to);
            }
        }
    }
    
    machine.cells = cells;
}

void WriteMachine(ofstream& output, const Machine& machine)
{
    queue<Machine::Cells::const_iterator> queue;
    if (machine.type == Type::Right)
    {
        queue.push(machine.cells.find("S"));
    }
    else
    {
        queue.push(machine.cells.find("H"));
    }

    set<Machine::To> visitedStates;
    while (!queue.empty())
    {
        auto cell = queue.front();
        visitedStates.insert(cell->first);
        queue.pop();
        if (cell == machine.cells.end())
        {
            continue;
        }
        output << cell->first << " -> ";
        size_t count = 0;
        for (auto& to : cell->second)
        {
            count++;
            output << to.first;
            Machine::To stateTo;
            for (auto& state : to.second)
            {
                stateTo += state;
            }
            output << stateTo;
            if (cell->second.size() != count)
            {
                output << " | ";
            }
            auto newState = machine.cells.find(stateTo);
            if (newState == machine.cells.end())
            {
                continue;
            }
            if (visitedStates.find(newState->first) == visitedStates.end())
            {
                queue.push(machine.cells.find(stateTo));
                visitedStates.insert(stateTo);
            }
        }
        output << endl;
    }
}

Machine GetMachine(ifstream& input)
{
    Machine machine;
    input >> machine.type;

    if (machine.type == Type::Right)
    {
        ReadRightGrammar(input, machine);
    }
    else
    {
        ReadLeftGrammar(input, machine);
    }

    return machine;
}

int main()
{
    ifstream input("input.txt");

    Machine machine = GetMachine(input);
    Determinization(machine);

    ofstream output("output.txt");
    WriteMachine(output, machine);
}
