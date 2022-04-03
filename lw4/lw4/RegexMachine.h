#pragma once
#include <string>
#include <vector>

const char EMPTY_TRANSITION_SYMBOL = 0;

class RegexMachine
{
public:
    RegexMachine(const std::string& regex);
    size_t size() const;

    struct Path
    {
        size_t from;
        size_t to;
        std::string transition;
    };

private:
    // Добавить параллельные переходы
    void AddParallelTransitions(size_t currentPathIndex, std::vector<std::string> parallelTransitions);
    // Добавить последовательные переходы
    void AddConsecutiveTransitions(size_t currentPathIndex, std::vector<std::string> consecutiveTransitions);
    bool SplitTransitions();

    size_t m_stateCounter = 0;
    std::vector<Path> m_paths;
};

