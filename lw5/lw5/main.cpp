#include <fstream>
#include <functional>
#include <iomanip>
#include "TokenStorage.h"

using namespace std;
using namespace placeholders;

void WriteTokenData(ostream& output, const TokenStorage& tokens, const TokenStorage::Token& token, size_t line, size_t pos)
{
    if (token == "")
    {
        return;
    }
    auto data = tokens.GetTokenData(token);

    output << setw(19) << data << ' ' << setw(17) << token << ' ' << line << setw(6) << pos << endl;
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");
    TokenStorage tokens;
    output << setw(19) << "TOKEN" << setw(18) << "VALUE" << setw(5) <<" LINE" << setw(6) << "POS\n";
    const auto WriteToken = bind(WriteTokenData, _1, tokens, _2, _3, _4);

    string line;
    size_t stringCounter = 0;

    // TODO можно заменить на состояния например enum
    // std variant
    bool isBlockComment = false;      // /*

    while (getline(input, line))
    {
        bool isLineComment = false;   // //
        bool isString = false;        // "

        string word;
        for (size_t pos = 0; pos < line.size(); pos++)
        {
            char ch = line[pos];

            if (isLineComment)
            {
                break;
            }

            if (isBlockComment)
            {
                if (line[pos] == '*' && line[pos + 1] == '/')
                {
                    isBlockComment = false;
                    pos += 2;
                }
                continue;
            }

            if (isString)
            {
                if (ch == '"')
                {
                    isString = false;
                    WriteToken(output, word + '"', stringCounter, pos - word.length() - 1);
                    word = "";
                }
                else
                {
                    word += ch;
                }
                continue;
            }

            switch (ch)
            {
            case '/':
                if (line[pos + 1] == '*')
                {
                    isBlockComment = true;
                    WriteToken(output, word, stringCounter, pos - word.length() - 1);
                    word = "";
                    continue;
                }
                if (line[pos + 1] == '/')
                {
                    isLineComment = true;
                }
                break;
            case '"':
                isString = true;
                WriteToken(output, word, stringCounter, pos - word.length() - 1);
                word = '"';
                break;
            case '=':
            case '+':
            case '-':
            case '*':
            case ',':
            case '.':
            case ':':
            case ';':
            case '(':
            case ')':
            case '{':
            case '}':
            case '[':
            case ']':
            case '<':
            case '>':
                WriteToken(output, word, stringCounter, pos - word.length());
                WriteToken(output, string(1, ch), stringCounter, pos);
                word = "";
                break;
            default:

                if (ch == ' ')
                {
                    WriteToken(output, word, stringCounter, pos - word.length());
                    word = "";
                }
                else
                {
                    word += ch;
                }

                if (pos == line.length() - 1)
                {
                    WriteToken(output, word, stringCounter, pos);
                    word = "";
                }

                break;
            }
        }
        stringCounter++;
    }
}
