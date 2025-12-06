// --- Part Two ---
//
//   The big cephalopods come back to check on how things are going. When they see that your grand total doesn't match the one expected by the worksheet, they realize they forgot to explain how to read cephalopod math.
//
//   Cephalopod math is written right-to-left in columns. Each number is given in its own column, with the most significant digit at the top and the least significant digit at the bottom. (Problems are still separated with a column consisting only of spaces, and the symbol at the bottom of the problem is still the operator to use.)
//
//   Here's the example worksheet again:
//
//   123 328  51 64
//    45 64  387 23
//     6 98  215 314
//   *   +   *   +
//
//   Reading the problems right-to-left one column at a time, the problems are now quite different:
//
//       The rightmost problem is 4 + 431 + 623 = 1058
//       The second problem from the right is 175 * 581 * 32 = 3253600
//       The third problem from the right is 8 + 248 + 369 = 625
//       Finally, the leftmost problem is 356 * 24 * 1 = 8544
//
//   Now, the grand total is 1058 + 3253600 + 625 + 8544 = 3263827.
//
//   Solve the problems on the math worksheet again. What is the grand total found by adding together all of the answers to the individual problems?

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
  std::vector<std::string> vec;
  std::string line;
  while(std::getline(std::cin, line))
  {
    vec.emplace_back(line);
  }

  std::size_t sum = 0;

  for (size_t i = 0; i < vec.back().size(); )
  {
    std::size_t size = 1;
    while (i + size < vec.back().size() && vec.back()[i + size] == ' ')
    {
      ++size;
    }

    std::size_t partial = vec.back()[i] == '+' ? 0 : 1;

    for (std::size_t j = i + size - (i + size == vec.back().size() ? 1 : 2); j >= i; --j)
    {
      std::size_t num = 0;
      for (std::size_t k = 0; k < vec.size() - 1; ++k)
      {
        if (vec[k][j] != ' ')
        {
          num = num * 10 + vec[k][j] - '0';
        }
      }
      std::cout << num << std::endl;
      partial = vec.back()[i] == '+' ? partial + num : partial * num;
      if (j == 0)
      {
        break;
      }
    }

    std::cout << partial << std::endl << std::endl;
    sum += partial;

    i += size;

  }

  std::cout << sum << std::endl;

  return 0;
}

