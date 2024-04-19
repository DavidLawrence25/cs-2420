#ifndef CS2420_NOBRAINERS_11GRAPH_PATHFINDER_H_
#define CS2420_NOBRAINERS_11GRAPH_PATHFINDER_H_

#include <list>
#include <unordered_map>

#include "no_brainers/11_graph/edge_table.h"

namespace rose {

// Uses Dijkstra's algorithm to find the shortest path between two vertices
// of a weighted undirected graph.
template <typename V>
class PathFinder {
 public:
  explicit PathFinder(sptr<EdgeTable<V>> table) : table_(table) {
    for (uindex_t i = 0; i < table->num_vertices(); ++i) {
      unvisited_[table->operator[](i)] = VertexData{};
    }
  }
  ~PathFinder() = default;

  // Returns a doubly-linked list of vertex pointers that define a path
  // of minimum weight between `from` and `to`. List is empty if such a path
  // does not exist.
  std::list<sptr<V>> ShortestPath(sptr<V> from, sptr<V> to);

  // Resets internal vertex maps to their initial states, allowing the object
  // to explore the graph again.
  void Reset();

 private:
  // Stores data about a vertex in a path.
  struct VertexData {
    sptr<V> previous = nullptr;
    weight_t min_weight = kWeightMax;
  };

  using VertexMap = std::unordered_map<sptr<V>, VertexData>;

  // Returns a pointer to a vertex in the unvisited map that has the smallest
  // minimum weight so far.
  sptr<V> CheapestUnvisitedVertex() const;

  // Moves `vertex` from the unvisited map to the visited map.
  void Visit(sptr<V> vertex);

  sptr<EdgeTable<V>> table_;
  VertexMap visited_;
  VertexMap unvisited_;
};

}  // namespace rose

#include "no_brainers/11_graph/path_finder.cc"

#endif  // CS2420_NOBRAINERS_11GRAPH_PATHFINDER_H_
