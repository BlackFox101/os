#include "RegexMachine.h"
#include "ReadRegex.h"

RegexMachine::RegexMachine(const std::string& regex)
{
	m_paths.push_back({ m_stateCounter , ++m_stateCounter, regex });

	SplitTransitions();
}

size_t RegexMachine::size() const
{
	return m_paths.size();
}

void RegexMachine::SplitTransitions()
{
	size_t initialPaths;
	do
	{
		initialPaths = m_paths.size();
		auto paths = m_paths;
		for (auto& path : paths)
		{
			auto consecutiveTransitions = ConvertConcatenation(path.transition);
			AddConsecutiveTransitions(path, consecutiveTransitions);
		}

		paths = m_paths;
		for (auto path : paths)
		{
			auto parallelTransitions = ConvertUnion(path.transition);
			AddParallelTransitions(path, parallelTransitions);
		}

		for (auto path : paths)
		{
			auto transition = path.transition;
			if (transition[transition.size() - 1] == '+')
			{
				ConvertPlus(path);
			}
			else if (transition[transition.size() - 1] == '*')
			{
				ConvertMultiplication(path);
			}
		}

	} while (initialPaths != m_paths.size());
}

void RegexMachine::AddConsecutiveTransitions(const Path& currentPath, std::vector<std::string> consecutiveTransitions)
{
	size_t from = currentPath.from;
	size_t to = currentPath.to;
	DeletePath(currentPath);

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
	m_paths.insert(m_paths.end(), newPaths.begin(), newPaths.end());
}

void RegexMachine::AddParallelTransitions(const Path& currentPath, std::vector<std::string> parallelTransitions)
{
	size_t from = currentPath.from;
	size_t to = currentPath.to;
	DeletePath(currentPath);

	std::vector<Path> newPaths;
	for (size_t i = 0; i < parallelTransitions.size(); i++)
	{
		newPaths.push_back({ from, to, parallelTransitions[i] });
	}
	m_paths.insert(m_paths.end(), newPaths.begin(), newPaths.end());
}

void RegexMachine::DeletePath(const Path& path)
{
	size_t index = 0;
	for (; index < m_paths.size(); index++)
	{
		auto currentPath = m_paths[index];
		if (currentPath.from == path.from && currentPath.to == path.to && currentPath.transition == path.transition)
		{
			break;
		}
	}
	m_paths.erase(m_paths.begin() + index);
}

void RegexMachine::ConvertPlus(Path path)
{
	size_t from = path.from;
	size_t to = path.to;
	std::string transition = path.transition;
	DeleteSpecialChar(transition);
	if (transition.size() == path.transition.size())
	{
		return;
	}
	DeletePath(path);

	m_paths.push_back({ from, ++m_stateCounter, transition });
	m_paths.push_back({ m_stateCounter, m_stateCounter, transition });
	m_paths.push_back({ m_stateCounter, to, std::string(1, EMPTY_TRANSITION_SYMBOL) });
}

void RegexMachine::ConvertMultiplication(Path path)
{
	size_t from = path.from;
	size_t to = path.to;
	std::string transition = path.transition;
	DeleteSpecialChar(transition);
	if (transition.size() == path.transition.size())
	{
		return;
	}
	DeletePath(path);

	m_paths.push_back({ from, ++m_stateCounter, std::string(1, EMPTY_TRANSITION_SYMBOL) });
	m_paths.push_back({ m_stateCounter, m_stateCounter, transition });
	m_paths.push_back({ m_stateCounter, to, std::string(1, EMPTY_TRANSITION_SYMBOL) });
}