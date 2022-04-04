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
    void ConvertPlus(Path path);
    void ConvertMultiplication(Path path);
    // Добавить параллельные переходы
    void AddParallelTransitions(const Path& currentPath, std::vector<std::string> parallelTransitions);
    // Добавить последовательные переходы
    void AddConsecutiveTransitions(const Path& currentPath, std::vector<std::string> consecutiveTransitions);
    void DeletePath(const Path& path);

    void SplitTransitions();

    size_t m_stateCounter = 0;
    std::vector<Path> m_paths;
};

