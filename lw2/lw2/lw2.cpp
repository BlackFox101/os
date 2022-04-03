#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int INDENT = 10;

struct Element
{
    int group;      // A, B, C
    int condition;  // S1, S2
    int out;        // Y1, Y2
};

using Machine = vector<vector<Element>>;
using EquivalenceMatrix = map<int, vector<int>>;

EquivalenceMatrix GetEquivalenceMatrix(const Machine& machine, const vector<int>& groupIndexes)
{
    EquivalenceMatrix matrix;
    int group = 0;
    matrix[group].push_back(groupIndexes[0]);

    for (int i = 1; i < groupIndexes.size(); i++)
    {
        bool isDifferentGroup = true;
        auto it = matrix.begin();

        while (it != matrix.end() && isDifferentGroup)
        {
            isDifferentGroup = false;
            for (int j = 0; j < machine.size(); j++)
            {
                if (machine[j][it->second[0]].group == machine[j][groupIndexes[i]].group)
                {
                    continue;
                }

                isDifferentGroup = true;
                it++;
                break;
            }
        }

        if (isDifferentGroup)
        {
            matrix[++group].push_back(groupIndexes[i]);
        }
        else
        {
            matrix[it->first].push_back(groupIndexes[i]);
        }
    }

    return matrix;
}

void UpdateMachine(Machine& machine, EquivalenceMatrix& equivalenceMatrix)
{
    for (int i = 0; i < machine.size(); i++)
    {
        for (int j = 0; j < machine[0].size(); j++)
        {
            auto it = equivalenceMatrix.begin();

            while (find((it->second).begin(), (it->second).end(), machine[i][j].condition) == (it->second).end())
            {
                it++;
            }
            machine[i][j].group = it->first;
        }
    }
}

bool Minimization(Machine& machine, EquivalenceMatrix& equivalenceMatrix)
{
    size_t initialNumberOfGroups = equivalenceMatrix.size();

    auto tempMatrix = equivalenceMatrix;
    equivalenceMatrix.clear();
    int i = 0;
    for (auto& item : tempMatrix)
    {
        auto tempEquivalenceMatrix = GetEquivalenceMatrix(machine, item.second);
        for (auto equivalence : tempEquivalenceMatrix)
        {
            equivalenceMatrix[i] = equivalence.second;
            i++;
        }
    }

    UpdateMachine(machine, equivalenceMatrix);

    return initialNumberOfGroups == equivalenceMatrix.size();
}

struct Result
{
    Machine resultMachine;
    vector<int> resultIndexes;
};

Result GetResult(Machine& machine, EquivalenceMatrix& equivalenceMatrix)
{
    vector<int> resultIndexes;
    Machine resultMachine(machine.size(), vector<Element>(equivalenceMatrix.size()));
    auto it = equivalenceMatrix.begin();

    for (int i = 0; i < resultMachine[0].size(); i++)
    {
        for (int j = 0; j < resultMachine.size(); j++)
        {
            resultMachine[j][i] = machine[j][it->second[0]];

            auto n = equivalenceMatrix.begin();
            while (find((n->second).begin(), (n->second).end(), machine[j][it->second[0]].condition) == (n->second).end())
            {
                n++;
            }
            resultMachine[j][i].condition = n->second[0];
        }
        resultIndexes.push_back(it->second[0]);
        it++;
    }

    return { resultMachine, resultIndexes };
}

void WriteMilli(const Result& result, ostream& output)
{
    auto machine = result.resultMachine;
    auto indexes = result.resultIndexes;
    for (int i = 0; i < indexes.size(); i++)
    {
        output << setw(INDENT) << "S" + to_string(indexes[i] + 1);
    }
    output << endl;           

    for (int i = 0; i < machine.size(); i++)
    {
        output << "X" << i + 1;
        for (int j = 0; j < machine[0].size(); j++)
        {
            output << setw(INDENT) << right << "[S" + to_string(machine[i][j].condition + 1) + ", Y" + to_string(machine[i][j].out + 1) + "]";
        }
        output << endl;
    }
}

void WriteMurra(const Result& result, ostream& output)
{
    auto machine = result.resultMachine;
    auto indexes = result.resultIndexes;
    for (int i = 0; i < indexes.size(); i++)
    {
        output << setw(INDENT) << "Y" + to_string(machine[0][i].out + 1);
    }
    output << endl;

    for (int i = 0; i < indexes.size(); i++)
    {
        output << setw(INDENT) << "S" + to_string(indexes[i] + 1);
    }
    output << endl;

    for (int i = 0; i < machine.size(); i++)
    {
        output << "X" << i + 1;
        for (int j = 0; j < machine[0].size(); j++)
        {
            string out = "[S" + to_string(machine[i][j].condition + 1) + "]";
            output << setw(INDENT) << right << out;
        }
        output << endl;
    }
}

void WriteMachine(Machine& machine, EquivalenceMatrix& equivalenceMatrix, const string& type, ostream& output)
{
    auto result = GetResult(machine, equivalenceMatrix);
    if (type == "Mi")
    {
        WriteMilli(result, output);
    }
    else
    {
        WriteMurra(result, output);
    }
}

void ReamMilli(Machine& machine, istream& input)
{
    string lineS;
    string lineY;
    getline(input, lineS);

    for (size_t i = 0; i < machine.size(); i++)
    {
        getline(input, lineS);
        getline(input, lineY);

        stringstream strS(lineS);
        stringstream strY(lineY);

        string temp;
        for (size_t j = 0; j < machine[i].size(); j++)
        {
            strS >> temp;
            string stringNum = temp.erase(0, 1);
            int numS = stoi(stringNum);

            strY >> temp;
            stringNum = temp.erase(0, 1);
            int numY = stoi(stringNum);

            machine[i][j].condition = numS - 1;
            machine[i][j].group = numY - 1;
            machine[i][j].out = numY - 1;
        }
    }
}

void ReadMurra(Machine& machine, istream& input)
{
    string lineS;
    string lineY;
    getline(input, lineS);

    getline(input, lineY);
    stringstream strY(lineY);
    string temp;
    for (size_t i = 0; i < machine[0].size(); i++)
    {
        strY >> temp;
        string stringNum = temp.erase(0, 1);
        int numY = stoi(stringNum);

        for (size_t j = 0; j < machine.size(); j++)
        {
            machine[j][i].group = numY - 1;
            machine[j][i].out = numY - 1;
        }
    }

    for (size_t i = 0; i < machine.size(); i++)
    {
        getline(input, lineS);
        stringstream strS(lineS);

        for (size_t j = 0; j < machine[i].size(); j++)
        {
            strS >> temp;
            string stringNum = temp.erase(0, 1);
            int numS = stoi(stringNum);

            machine[i][j].condition = numS - 1;
        }
    }
}

void ReadMachine(Machine& machine, const string& type, istream& input)
{
    if (type == "Mi")
    {
        ReamMilli(machine, input);
    }
    else
    {
        ReadMurra(machine, input);
    }
}

int main()
{
    ifstream input;
    input.open("input4.txt");

    string type;
    int x, y;
    input >> type >> x >> y;

    Machine machine(y, vector<Element>(x));
    ReadMachine(machine, type, input);

    EquivalenceMatrix equivalenceMatrix;
    for (int i = 0; i < x; i++)
    {
        equivalenceMatrix[0].push_back(i);
    }

    while (!Minimization(machine, equivalenceMatrix)) {}

    ofstream output;
    output.open("output.txt");
    WriteMachine(machine, equivalenceMatrix, type, output);
}