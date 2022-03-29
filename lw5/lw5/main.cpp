#include <fstream>
#include "TokenStorage.h"

using namespace std;

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");
    TokenStorage tokes;

    string line;
    size_t stringCounter = 0;
    while (getline(input, line))
    {
        bool isBlockComment = false;  // /*
        bool isParenthesis = false;   // (
        bool isCurlyBracket = false;  // {
        bool isSqeareBracket = false; // [
        bool isString = false;        // "

        string word;
        for (size_t i = 0; i < line.size(); i++)
        {
            const auto letter = line[i];
        }

        stringCounter++;
    }
}
