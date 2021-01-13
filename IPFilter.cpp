#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <ostream>

std::vector<std::vector<int>> FilterVector(std::vector<std::vector<int>> vec, std::function<bool(std::vector<int>)> predicate)
{
	auto pos = vec.begin();
	std::vector<std::vector<int>> result;

	while (pos != vec.end())
	{
		auto valuePos = std::find_if(pos, vec.end(), predicate);
		if (valuePos != vec.end())
		{
			result.push_back(*valuePos);
			pos = valuePos + 1;
		}
		else
		{
			break;
		}
	}

	return result;
}

bool SorterNum(int first, int second)
{
	return first < second;
}

bool SorterVec(std::vector<int> first, std::vector<int> second)
{
	for (auto i = 0; i < first.size(); i++)
	{
		if (first[i] != second[i])
		{
			return SorterNum(first[i], second[i]);
		}
	}
	return false;
}

bool IsFirstEqualOne(std::vector<int> vec)
{
	return vec[0] == 1;
}

bool IsFirstFourtySixSecondSeventy(std::vector<int> vec)
{
	return (vec[0] == 46) && (vec[1] == 70);
}

bool IsAnyFourtySix(std::vector<int> vec)
{
	return std::find(vec.begin(), vec.end(), 46) != vec.end();
}

void ReadFileToVector(const std::string& line, std::vector<std::vector<int>>& result)
{
	std::vector<int> ipNums;
	std::string delimiter = "\t";
	std::string ip = line.substr(0, line.find(delimiter));

	std::string delimiter2 = ".";

	size_t pos = 0;
	while ((pos = ip.find(delimiter2)) != std::string::npos) {
		ipNums.push_back(std::stoi(ip.substr(0, pos)));
		ip.erase(0, pos + delimiter.length());
	}
	ipNums.push_back(std::stoi(ip));
	result.push_back(ipNums);
}

void PrintVector(const std::vector<std::vector<int>>& result)
{
	auto it = result.begin();

	while (it != result.end())
	{
		std::string str = "";
		for (int i = 0; i < it->size(); i++)
		{
			str += std::to_string((*it)[i]);
			if (i != it->size() - 1)
			{
				str += ".";
			}
		}

		std::cout << str << std::endl;
		it++;
	}
}

int main(int argc, char const *argv[])
{
	std::string line;
	std::vector<std::vector<int>> ipAddresses;
	std::vector<std::vector<int>> sortedIps;

	std::ifstream in("ip_filter.tsv");
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			ReadFileToVector(line, ipAddresses);
		}
	}
	in.close();

	std::sort(ipAddresses.begin(), ipAddresses.end(), SorterVec);
	sortedIps = ipAddresses;

	auto result = FilterVector(ipAddresses, IsFirstEqualOne);
	sortedIps.insert(sortedIps.end(), std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));

	result = FilterVector(ipAddresses, IsFirstFourtySixSecondSeventy);
	sortedIps.insert(sortedIps.end(), std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));

	result = FilterVector(ipAddresses, IsAnyFourtySix);
	sortedIps.insert(sortedIps.end(), std::make_move_iterator(result.begin()), std::make_move_iterator(result.end()));

	PrintVector(sortedIps);

    return 0;
}
