#ifndef CS2420_NOBRAINERS_11GRAPH_GRAPH_H_
#define CS2420_NOBRAINERS_11GRAPH_GRAPH_H_

#include <list>
#include <ostream>

#include "custom_libraries/aliases.h"
#include "custom_libraries/d_linked_list.h"
#include "no_brainers/11_graph/edge_table.h"

namespace rose {

// A weighted undirected graph with vertices of type `V`.
template <typename V>
class Graph {
 public:
  using Path = std::list<sptr<V>>;

  explicit Graph(sptr<EdgeTable<V>> table) : table_(table) {}
  // Constructs a deep copy of `other`.
  Graph(const Graph &other) : table_(other.table_->MakeCopy()) {}
  // Assigns this to `other` via a deep copy.
  Graph &operator=(const Graph &other);
  ~Graph() = default;

  // Returns the number of vertices in the graph.
  size_t order() const { return table_->num_vertices(); }
  // Returns the number of edges in the graph.
  size_t size() const { return table_->num_edges(); }

  // Returns the index of `vertex` in the graph's internal vertex list.
  // Returns std::nullopt if `vertex` is not in the graph.
  opt<uindex_t> IndexOf(const V &vertex) const {
    return table_->IndexOf(vertex);
  }

  // Returns the degree of the vertex at index `i` in the graph's internal
  // vertex list. Returns std::nullopt if no vertex exists at index `i`.
  opt<u64> DegreeOfVertexAt(uindex_t i) const {
    return table_->DegreeOfVertexAt(i);
  }

  // Returns true if `v0` and `v1` are adjacent.
  // Returns false if either vertex is absent in the graph.
  bool Adjacent(const V &v0, const V &v1) const {
    return table_->Adjacent(v0, v1);
  }

  // Adds `vertex` to the graph's internal vertex list.
  // Assumes `vertex` is unique for the sake of speed.
  void AddVertex(const V &vertex) { table_->AddVertex(vertex); }

  // Adds a weighted undirected edge between `v0` and `v1`.
  // Adds any missing vertices to ensure proper operation.
  void AddEdge(const V &v0, const V &v1, weight_t weight = 1) {
    table_->AddEdge(v0, v1, weight);
  }

  // Returns the shortest path between `start` and `end` along the graph.
  // Behavior not guaranteed if multiple shortest paths exist.
  Path PathfindDijkstra(const V &start, const V &end) const;

  // Extracts a string representation of `graph` into `out`.
  // Each line of the string representation looks something like...
  // A: <B, 3> <F, 1> <E, 4>
  template <typename _V>
  friend std::ostream &operator<<(std::ostream &out, const Graph<_V> &graph) {
    for (uindex_t i = 0; i < graph.order(); ++i) {
      out << *graph.table_->operator[](i) << ": ";
      for (EdgeData<_V> data : graph.table_->GetAdjacent(i)) {
        out << data << ' ';
      }
      out << '\n';
    }
    return out;
  }

 private:
  sptr<EdgeTable<V>> table_;
};

}  // namespace rose

#include "no_brainers/11_graph/graph.cc"

#endif  // CS2420_NOBRAINERS_11GRAPH_GRAPH_H_
