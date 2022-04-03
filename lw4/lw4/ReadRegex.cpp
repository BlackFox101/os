#include "ReadRegex.h"

using namespace std;

void AddConcatenation(vector<string>& transitions, const string& transition)
{
    if (transition == "")
    {
        return;
    }

    if (transitions.size() > 0)
    {
        string& lastTransition = transitions[transitions.size() - 1];
        if (transition[0] == '|')
        {
            lastTransition += transition;
            return;
        }

        if (lastTransition[lastTransition.size() - 1] == '|')
        {
            lastTransition += transition;
            return;
        }
    }

    transitions.push_back(transition);
}

// Последовательные
vector<string> ConvertConcatenation(const string& regex)
{
    vector<string> transitions;

    size_t openParenthesis = 0;
    string transition;
    for (auto ch : regex)
    {
        if (ch == ' ')
        {
            continue;
        }

        if (openParenthesis > 0)
        {
            transition += ch;
        }

        switch (ch)
        {
        case '(':
            if (openParenthesis > 0)
            {
                openParenthesis++;
                break;
            }
            openParenthesis++;
            AddConcatenation(transitions, transition);
            transition = ch;
            break;
        case ')':
            openParenthesis--;
            break;
        case '|':
            if (openParenthesis == 0)
            {
                transition += ch;
            }
            break;
        case '*':
            if (openParenthesis > 0)
            {
                break;
            }
            AddConcatenation(transitions, transition + ch);
            transition = "";
            break;
        case '+':
            if (openParenthesis > 0)
            {
                break;
            }
            AddConcatenation(transitions, transition + ch);
            transition = "";
            break;
        default:
            if (openParenthesis > 0)
            {
                break;
            }
            AddConcatenation(transitions, transition);
            transition = ch;

            break;
        }
    }

    if (transition != "")
    {
        AddConcatenation(transitions, transition);
    }

    return transitions;
}

// Параллельные
vector<string> ConvertUnion(const string& regex)
{
    vector<string> transitions;

    size_t openParenthesis = 0;
    string transition;
    for (size_t i = 0; i < regex.size(); i++)
    {
        char ch = regex[i];
        if (ch == ' ')
        {
            continue;
        }

        if (openParenthesis > 0)
        {
            transition += ch;
        }

        switch (ch)
        {
        case '(':
            openParenthesis++;
            if (openParenthesis == 1)
            {
                transition += ch;
            }
            break;
        case ')':
            openParenthesis--;
            break;
        case '|':
            if (openParenthesis > 0)
            {
                break;
            }
            transitions.push_back(transition);
            transition = "";
            break;
        default:
            if (openParenthesis > 0)
            {
                break;
            }
            transition += ch;
            break;
        }
    }

    if (transition != "")
    {
        transitions.push_back(transition);
    }

    return transitions;
}