#include "no_brainers/06_recursion_maze/maze.h"

#include <algorithm>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>

namespace rose {

Maze::Maze(const std::string &maze, int x_start, int y_start, int x_end,
           int y_end)
    : x_start_(x_start), y_start_(y_start), x_end_(x_end), y_end_(y_end) {
  int new_lines = std::count(maze.begin(), maze.end(), '\n');
  height_ = new_lines + 1;
  width_ = (maze.length() - new_lines) / height_;

  std::stringstream sin(maze);
  for (std::string line; std::getline(sin, line, '\n');) {
    maze_.push_back(line);
  }
  maze_.resize(height_);  // Not necessary, but nice to have.
}

bool Maze::Solve() { return Solve(x_start_, y_start_); }

bool Maze::Solve(int x, int y) {
  if (!ShouldExplore(x, y)) return false;
  if (x == x_end_ && y == y_end_) return true;

  Explore(x, y);
  bool above = Solve(x, y - 1);
  bool below = Solve(x, y + 1);
  bool to_left = Solve(x - 1, y);
  bool to_right = Solve(x + 1, y);

  return above || below || to_left || to_right;
}

std::ostream &Maze::PrintSuccess(std::ostream &out) {
  out << (Solve() ? "Success" : "Could not be solved");
  return out;
}

std::ostream &operator<<(std::ostream &out, const Maze &maze) {
  using std::string, std::views::counted;
  for (const string &line : counted(maze.maze_.begin(), maze.height_ - 1)) {
    out << line << '\n';
  }
  out << maze.maze_.at(maze.height_ - 1);
  return out;
}

}  // namespace rose
