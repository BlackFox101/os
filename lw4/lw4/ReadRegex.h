#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

void AddConcatenation(std::vector<std::string>& transitions, const std::string& transition);

std::vector<std::string> ConvertConcatenation(const std::string& regex);

std::vector<std::string> ConvertUnion(const std::string& regex);