// --- Part Two ---
//
//   The clerk quickly discovers that there are still invalid IDs in the ranges in your list. Maybe the young Elf was doing other silly patterns as well?
//
//   Now, an ID is invalid if it is made only of some sequence of digits repeated at least twice. So, 12341234 (1234 two times), 123123123 (123 three times), 1212121212 (12 five times), and 1111111 (1 seven times) are all invalid IDs.
//
//   From the same example as before:
//
//       11-22 still has two invalid IDs, 11 and 22.
//       95-115 now has two invalid IDs, 99 and 111.
//       998-1012 now has two invalid IDs, 999 and 1010.
//       1188511880-1188511890 still has one invalid ID, 1188511885.
//       222220-222224 still has one invalid ID, 222222.
//       1698522-1698528 still contains no invalid IDs.
//       446443-446449 still has one invalid ID, 446446.
//       38593856-38593862 still has one invalid ID, 38593859.
//       565653-565659 now has one invalid ID, 565656.
//       824824821-824824827 now has one invalid ID, 824824824.
//       2121212118-2121212124 now has one invalid ID, 2121212121.
//
//   Adding up all the invalid IDs in this example produces 4174379265.
//
//   What do you get if you add up all of the invalid IDs using these new rules?

#include <iostream>
#include <set>
#include <string>

int countCiph(const std::size_t num)
{
  int count = 0;
  for (std::size_t i = num; i > 0; i /= 10)
  {
    count++;
  }
  return count;
}

std::size_t getNum(const int ciph)
{
  std::size_t num = 1;
  for (int i = ciph; i > 1; --i)
  {
    num *= 10;
  }
  return num;
}

std::size_t multiplyNum(const std::size_t num, const std::size_t multiplier, const int times)
{
  std::size_t result = num;
  for (int i = 1; i < times; ++i)
  {
    result = result * multiplier + num;
  }
  return result;
}

int main()
{
  std::size_t sum = 0;
  for (std::string s; std::getline(std::cin, s, ','); )
  {
    // Find the dash
    const std::size_t pos = s.find('-');

    // Parse the two numbers
    const std::size_t lower = std::stoull(s.substr(0, pos));
    const std::size_t higher = std::stoull(s.substr(pos + 1));

    std::set<std::size_t> nums;

    for (int ciph = countCiph(lower); ciph <= countCiph(higher); ++ciph)
    {
      for (int c = 2; c <= ciph; ++c)
      {
        if (ciph % c != 0)
        {
          continue;
        }
        const std::size_t multiplier = getNum(ciph/c + 1);
        const std::size_t lb = std::max(lower, multiplyNum(multiplier/10, multiplier, c));
        const std::size_t hb = std::min(higher + 1, multiplyNum(multiplier, multiplier, c));

        std::size_t i = 1;
        while (multiplyNum(i, multiplier, c) < lb)
        {
          ++i;
        }

        for (; multiplyNum(i, multiplier, c) < hb; ++i)
        {
          nums.insert(multiplyNum(i, multiplier, c));
        }

      }
    }

    for (const std::size_t x : nums)
    {
      sum += x;
    }
  }
  std::cout << sum << std::endl;

  return 0;
}