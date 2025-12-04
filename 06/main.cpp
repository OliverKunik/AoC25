// --- Part Two ---
//
//   The escalator doesn't move. The Elf explains that it probably needs more joltage to overcome the static friction of the system and hits the big red "joltage limit safety override" button. You lose count of the number of times she needs to confirm "yes, I'm sure" and decorate the lobby a bit while you wait.
//
//   Now, you need to make the largest joltage by turning on exactly twelve batteries within each bank.
//
//   The joltage output for the bank is still the number formed by the digits of the batteries you've turned on; the only difference is that now there will be 12 digits in each bank's joltage output instead of two.
//
//   Consider again the example from before:
//
//   987654321111111
//   811111111111119
//   234234234234278
//   818181911112111
//
//   Now, the joltages are much larger:
//
//       In 987654321111111, the largest joltage can be found by turning on everything except some 1s at the end to produce 987654321111.
//       In the digit sequence 811111111111119, the largest joltage can be found by turning on everything except some 1s, producing 811111111119.
//       In 234234234234278, the largest joltage can be found by turning on everything except a 2 battery, a 3 battery, and another 2 battery near the start to produce 434234234278.
//       In 818181911112111, the joltage 888911112111 is produced by turning on everything except some 1s near the front.
//
//   The total output joltage is now much larger: 987654321111 + 811111111119 + 434234234278 + 888911112111 = 3121910778619.
//
//   What is the new total output joltage?

#include <iostream>
#include <string>

int main()
{
  std::size_t sum = 0;

  std::string line;
  while (std::getline(std::cin, line))
  {
    constexpr int count = 12;
    char bats[count] = {};

    for (int i = 0; i < line.size(); ++i)
    {
      for (int j = 0; j < count; ++j)
      {
        if (i + count - j > line.size())
        {
          continue;
        }

        if (line[i] > bats[j])
        {
          bats[j] = line[i];
          for (int k = j + 1; k < count; ++k)
          {
            bats[k] = '0';
          }
          break;
        }
      }
    }

    std::size_t num = 0;

    for (const char bat : bats)
    {
      num = num * 10 + bat - '0';
    }

    sum += num;
  }

  std::cout << sum << std::endl;

  return 0;
}