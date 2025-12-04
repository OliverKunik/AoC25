// --- Day 4: Printing Department ---
//
//   You ride the escalator down to the printing department. They're clearly getting ready for Christmas; they have lots of large rolls of paper everywhere, and there's even a massive printer in the corner (to handle the really big print jobs).
//
//   Decorating here will be easy: they can make their own decorations. What you really need is a way to get further into the North Pole base while the elevators are offline.
//
//   "Actually, maybe we can help with that," one of the Elves replies when you ask for help. "We're pretty sure there's a cafeteria on the other side of the back wall. If we could break through the wall, you'd be able to keep moving. It's too bad all of our forklifts are so busy moving those big rolls of paper around."
//
//   If you can optimize the work the forklifts are doing, maybe they would have time to spare to break through the wall.
//
//   The rolls of paper (@) are arranged on a large grid; the Elves even have a helpful diagram (your puzzle input) indicating where everything is located.
//
//   For example:
//
//   ..@@.@@@@.
//   @@@.@.@.@@
//   @@@@@.@.@@
//   @.@@@@..@.
//   @@.@@@@.@@
//   .@@@@@@@.@
//   .@.@.@.@@@
//   @.@@@.@@@@
//   .@@@@@@@@.
//   @.@.@@@.@.
//
//   The forklifts can only access a roll of paper if there are fewer than four rolls of paper in the eight adjacent positions. If you can figure out which rolls of paper the forklifts can access, they'll spend less time looking and more time breaking down the wall to the cafeteria.
//
//   In this example, there are 13 rolls of paper that can be accessed by a forklift (marked with x):
//
//   ..xx.xx@x.
//   x@@.@.@.@@
//   @@@@@.x.@@
//   @.@@@@..@.
//   x@.@@@@.@x
//   .@@@@@@@.@
//   .@.@.@.@@@
//   x.@@@.@@@@
//   .@@@@@@@@.
//   x.x.@@@.x.
//
//   Consider your complete diagram of the paper roll locations. How many rolls of paper can be accessed by a forklift?

#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main()
{
  std::size_t count = 0;

  std::string line;
  std::getline(std::cin, line);

  const std::size_t boardLength = line.length() + 2;

  std::vector<bool> board(boardLength, false);

  board.reserve(board.size() + boardLength);
  board.emplace_back(false);

  for (const char &c : line)
  {
    board.emplace_back(c == '@');
  }

  board.emplace_back(false);

  while (std::getline(std::cin, line))
  {
    board.reserve(board.size() + boardLength);
    board.emplace_back(false);

    for (const char &c : line)
    {
      board.emplace_back(c == '@');
    }

    board.emplace_back(false);

  }

  board.resize(board.size() + boardLength, false);

  auto free = [&b = std::as_const(board), &bl = std::as_const(boardLength)](const std::size_t index) -> bool
  {
    return static_cast<int>(index >= bl + 1            ? static_cast<bool>(b[index - bl - 1]) : false) +
           static_cast<int>(index >= bl                ? static_cast<bool>(b[index - bl])     : false) +
           static_cast<int>(index >= bl - 1            ? static_cast<bool>(b[index - bl + 1]) : false) +
           static_cast<int>(index >= 1                 ? static_cast<bool>(b[index - 1])      : false) +
           static_cast<int>(index <  b.size() - 1      ? static_cast<bool>(b[index + 1])      : false) +
           static_cast<int>(index <  b.size() - bl + 1 ? static_cast<bool>(b[index + bl - 1]) : false) +
           static_cast<int>(index <  b.size() - bl     ? static_cast<bool>(b[index + bl])     : false) +
           static_cast<int>(index <  b.size() - bl - 1 ? static_cast<bool>(b[index + bl + 1]) : false) < 4;
  };

  for (std::size_t index = 0; index < board.size(); ++index)
  {
    if (board[index])
    {
      count += free(index);
    }
  }

  std::cout << count << std::endl;

  return 0;
}