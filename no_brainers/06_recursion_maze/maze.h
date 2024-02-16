#include <algorithm>
#include <ostream>
#include <string>
#include <vector>

#ifndef CS2420_NOBRAINERS_06RECURSIONMAZE_MAZE_H_
#define CS2420_NOBRAINERS_06RECURSIONMAZE_MAZE_H_

namespace rose {

// Represents a 2D maze which can solve itself.
class Maze {
 public:
  Maze() = default;
  // `maze` is only meant to include '#' (for walls), '.' (for explored),
  // ' ' (for empty spaces), and '\n' (to delimit rows).
  // Note: Do not include redundant new line characters.
  Maze(const std::string &maze, int x_start, int y_start, int x_end, int y_end);

  // Returns true if the maze is solvable. Uses default start values.
  bool Solve();
  // Returns true if the maze is solvable from `(x, y)`.
  bool Solve(int x, int y);

  // Returns true if the tile at `(x, y)` is out of bounds.
  bool TileOutOfBounds(int x, int y) const {
    return x < 0 || x >= width_ || y < 0 || y >= height_;
  }

  // Returns true if the tile at `(x, y)` is a valid empty tile.
  bool ShouldExplore(int x, int y) const {
    return TileOutOfBounds(x, y) ? false : (maze_[y][x] == ' ');
  }

  // Marks the tile at `(x, y)` as explored.
  void Explore(int x, int y) {
    if (TileOutOfBounds(x, y)) return;
    maze_[y][x] = '.';
  }

  // Streams a success/failure message into `out` based on the result of Solve.
  std::ostream &PrintSuccess(std::ostream &out);
  friend std::ostream &operator<<(std::ostream &out, const Maze &maze);

 private:
  std::vector<std::string> maze_;
  int x_start_, y_start_;
  int x_end_, y_end_;
  int width_, height_;
};

}  // namespace rose

#endif  // CS2420_NOBRAINERS_06RECURSIONMAZE_MAZE_H_
