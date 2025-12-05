// --- Part Two ---
//
//   The Elves start bringing their spoiled inventory to the trash chute at the back of the kitchen.
//
//   So that they can stop bugging you when they get new inventory, the Elves would like to know all of the IDs that the fresh ingredient ID ranges consider to be fresh. An ingredient ID is still considered fresh if it is in any range.
//
//   Now, the second section of the database (the available ingredient IDs) is irrelevant. Here are the fresh ingredient ID ranges from the above example:
//
//   3-5
//   10-14
//   16-20
//   12-18
//
//   The ingredient IDs that these ranges consider to be fresh are 3, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, and 20. So, in this example, the fresh ingredient ID ranges consider a total of 14 ingredient IDs to be fresh.
//
//   Process the database file again. How many ingredient IDs are considered to be fresh according to the fresh ingredient ID ranges?

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::vector<std::pair<std::size_t, std::size_t>> intervals;
  std::string line;
  while(std::getline(std::cin, line), !line.empty())
  {
    // Find the dash
    const std::size_t pos = line.find('-');

    // Parse the two numbers
    intervals.emplace_back(std::pair(std::stoull(line.substr(0, pos)),std::stoull(line.substr(pos + 1))));
  }

  std::sort(intervals.begin(), intervals.end());

  std::size_t sum = 0;

  for (std::size_t i = 0; i < intervals.size(); )
  {
    const std::size_t low = intervals[i].first;
    std::size_t high = intervals[i].second;

    while (++i < intervals.size() && intervals[i].first <= high + 1)
    {
      high = std::max(high, intervals[i].second);
    }
    sum += high - low + 1;
  }

  std::cout << sum << std::endl;

  return 0;
}