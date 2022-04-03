#include "RegexMachine.h"
#include "ReadRegex.h"

RegexMachine::RegexMachine(const std::string& regex)
{
	m_paths.push_back({ m_stateCounter , ++m_stateCounter, regex });

	while (!SplitTransitions()) {};
}

size_t RegexMachine::size() const
{
	return m_paths.size();
}

bool RegexMachine::SplitTransitions()
{
    size_t initialPaths = m_paths.size();

	auto paths = m_paths;
	for (size_t i = 0; i < paths.size(); i++)
	{
		auto consecutiveTransitions = ConvertConcatenation(paths[i].transition);
		AddConsecutiveTransitions(i, consecutiveTransitions);
	}

	paths = m_paths;
	for (size_t i = 0; i < paths.size(); i++)
	{
		auto parallelTransitions = ConvertUnion(paths[i].transition);
		AddParallelTransitions(i, parallelTransitions);
	}

    return initialPaths == m_paths.size();
}

void RegexMachine::AddConsecutiveTransitions(size_t currentPathIndex, std::vector<std::string> consecutiveTransitions)
{
	size_t from = m_paths.at(currentPathIndex).from;
	size_t to = m_paths.at(currentPathIndex).to;

	m_paths.erase(m_paths.begin() + currentPathIndex);
	std::vector<Path> newPaths;
	auto stateFrom = from;
	size_t stateTo;
	for (size_t i = 0; i < consecutiveTransitions.size(); i++)
	{
		if (i == consecutiveTransitions.size() - 1)
		{
			stateTo = to;
		}
		else
		{
			stateTo = ++m_stateCounter;
		}
		newPaths.push_back({ stateFrom, stateTo, consecutiveTransitions[i]});
		stateFrom = stateTo;
	}
	m_paths.insert(m_paths.begin() + currentPathIndex, newPaths.begin(), newPaths.end());
}

void RegexMachine::AddParallelTransitions(size_t currentPathIndex, std::vector<std::string> parallelTransitions)
{
	// TODO: Обработать параллельные переходы
}