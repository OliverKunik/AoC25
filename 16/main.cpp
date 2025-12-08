// --- Part Two ---
//
//   The Elves were right; they definitely don't have enough extension cables. You'll need to keep connecting junction boxes together until they're all in one large circuit.
//
//   Continuing the above example, the first connection which causes all of the junction boxes to form a single circuit is between the junction boxes at 216,146,977 and 117,168,530. The Elves need to know how far those junction boxes are from the wall so they can pick the right extension cable; multiplying the X coordinates of those two junction boxes (216 and 117) produces 25272.
//
//   Continue connecting the closest unconnected pairs of junction boxes together until they're all in the same circuit. What do you get if you multiply together the X coordinates of the last two junction boxes you need to connect?


#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct junction
{
  std::size_t x, y, z;
};

struct dist
{
  std::size_t i, j;
  double d;
};

double distance(const junction& a, const junction& b)
{
  const double dx = static_cast<double>(a.x) - static_cast<double>(b.x);
  const double dy = static_cast<double>(a.y) - static_cast<double>(b.y);
  const double dz = static_cast<double>(a.z) - static_cast<double>(b.z);

  return std::sqrt(dx*dx + dy*dy + dz*dz);
}

int find(const std::vector<std::vector<std::size_t>> &circuits, const std::size_t id)
{
  for (int i = 0; i < circuits.size(); ++i)
  {
    for (const auto &junction : circuits[i])
    {
      if (junction == id)
      {
        return i;
      }
    }
  }
  return -1;
}

int main()
{
  std::vector<junction> junctions;

  std::string line;
  while (std::getline(std::cin, line))
  {
    junction j = {};
    char c;  // to consume commas

    std::stringstream ss(line);
    ss >> j.x >> c >> j.y >> c >> j.z;

    junctions.push_back(j);
  }

  std::vector<dist> distances;

  for (std::size_t i = 0; i < junctions.size(); ++i)
  {
    for (std::size_t j = i + 1; j < junctions.size(); ++j)
    {
      distances.push_back(dist{i, j, distance(junctions[i], junctions[j])});
    }
  }

  std::sort(distances.begin(), distances.end(),
               [](const dist& a, const dist& b) {
                   return a.d < b.d;
               });

  std::vector<std::vector<std::size_t>> circuits;

  for (std::size_t i = 0; ; ++i)
  {
    const int first = find(circuits, distances[i].i);
    const int second = find(circuits, distances[i].j);

    if (first == -1 && second == -1)
    {
      std::vector<std::size_t> t = {distances[i].i, distances[i].j};
      circuits.push_back(t);
    }
    else if (first == second)
    {

    }
    else if (first == -1)
    {
      circuits[second].push_back(distances[i].i);
    }
    else if (second == -1)
    {
      circuits[first].push_back(distances[i].j);
    }
    else
    {
      circuits[first].insert(circuits[first].end(), circuits[second].begin(), circuits[second].end());

      circuits[second].clear();
    }

    if (circuits[first].size() == junctions.size() || circuits[second].size() == junctions.size())
    {
      std::cout << junctions[distances[i].i].x * junctions[distances[i].j].x << std::endl;
      break;
    }
  }

  return 0;
}