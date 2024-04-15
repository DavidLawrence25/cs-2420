#ifndef CS2420_NOBRAINERS_11GRAPH_EDGETABLE_H_
#define CS2420_NOBRAINERS_11GRAPH_EDGETABLE_H_

#include <list>
#include <ostream>

#include "custom_libraries/aliases.h"

namespace rose {

using weight_t = u64;

// Used for the same thing as infinity in Dijkstra's algorithm.
static constexpr weight_t kWeightMax = kU64Max;

// Stores data about an edge. Meant to be paired with a vertex pointer.
template <typename V>
struct EdgeData {
  sptr<V> vertex;
  weight_t weight;

  template <typename _V>
  friend std::ostream &operator<<(std::ostream &out, const EdgeData<_V> &data) {
    out << '<';
    if (data.vertex == nullptr) {
      out << "???";
    } else {
      out << *data.vertex;
    }
    out << ", " << data.weight << '>';
    return out;
  }
};

// An interface for a structure that stores a list of vertices in an undirected
// graph and keeps track of how they are connected.
template <typename V>
class EdgeTable {
 public:
  virtual uptr<EdgeTable> MakeCopy() const = 0;

  virtual ~EdgeTable() = default;

  virtual size_t num_vertices() const = 0;
  virtual size_t num_edges() const = 0;
  // Returns the vertex pointer at index `i` in the vertex list.
  virtual sptr<V> operator[](uindex_t i) const = 0;

  // Returns the index of a vertex with value `vertex` in the vertex list.
  virtual opt<uindex_t> IndexOf(const V &vertex) const = 0;
  // Returns the degree of the vertex at index `i` in the vertex list.
  // The degree of a vertex is defined as the number of vertices adjacent to it.
  virtual opt<u64> DegreeOfVertexAt(uindex_t i) const = 0;
  // Returns true if a vertex with value `vertex` exists in the graph.
  virtual bool Contains(const V &vertex) const;
  // Returns true if two vertices exist with values `v0` and `v1` respectively
  // that are adjacent to one another.
  virtual bool Adjacent(const V &v0, const V &v1) const = 0;
  // Returns a singly-linked list of the edges connected
  // to the vertex at index `i` in the vertex list.
  virtual std::list<EdgeData<V>> GetAdjacent(uindex_t i) const = 0;
  // Returns a singly-linked list of the edges connected
  // to a vertex with value `vertex`.
  virtual std::list<EdgeData<V>> GetAdjacent(const V &vertex) const = 0;

  // Adds a vertex with value `vertex` to the graph.
  // Assumes no vertex in the graph shares that value.
  virtual void AddVertex(const V &vertex) = 0;
  // Adds a weighted undirected edge between two vertices with values `v0` and
  // `v1` respectively. Adds any missing vertices to ensure proper operation.
  // Assumes the vertices are not already connected.
  virtual void AddEdge(const V &v0, const V &v1, weight_t weight) = 0;
};

// An edge table that assigns each vertex its own linked list of adjacent
// vertices and the weights of the edges connecting them.
// Best suited for sparse graphs.
template <typename V>
class AdjacencyList final : public EdgeTable<V> {
 public:
  uptr<EdgeTable<V>> MakeCopy() const override;

  AdjacencyList() = default;
  // Constructs a deep copy of `other`.
  AdjacencyList(const AdjacencyList<V> &other);
  // Assigns this to `other` via a deep copy.
  AdjacencyList<V> &operator=(const AdjacencyList<V> &other);
  ~AdjacencyList() override = default;

  size_t num_vertices() const override { return vertices_.size(); }
  size_t num_edges() const override;
  sptr<V> operator[](uindex_t i) const override { return vertices_[i]; }

  opt<uindex_t> IndexOf(const V &vertex) const override;
  opt<u64> DegreeOfVertexAt(uindex_t i) const override;
  bool Adjacent(const V &v0, const V &v1) const override;
  std::list<EdgeData<V>> GetAdjacent(uindex_t i) const override;
  std::list<EdgeData<V>> GetAdjacent(const V &vertex) const override;

  void AddVertex(const V &vertex) override;
  void AddEdge(const V &v0, const V &v1, weight_t weight) override;

 private:
  vector<sptr<V>> vertices_;
  vector<std::list<EdgeData<V>>> edge_lists_;
};

// An edge table that represents adjacency by a 2D matrix of optional weights.
// Best suited for dense graphs.
template <typename V>
class AdjacencyMatrix final : public EdgeTable<V> {
 public:
  uptr<EdgeTable<V>> MakeCopy() const override;

  AdjacencyMatrix() = default;
  // Constructs a deep copy of `other`.
  AdjacencyMatrix(const AdjacencyMatrix<V> &other);
  // Assigns this to `other` via a deep copy.
  AdjacencyMatrix<V> &operator=(const AdjacencyMatrix<V> &other);
  ~AdjacencyMatrix() override = default;

  size_t num_vertices() const override { return vertices_.size(); }
  size_t num_edges() const override;
  sptr<V> operator[](uindex_t i) const override { return vertices_[i]; }

  opt<uindex_t> IndexOf(const V &vertex) const override;
  opt<u64> DegreeOfVertexAt(uindex_t i) const override;
  bool Adjacent(const V &v0, const V &v1) const override;
  std::list<EdgeData<V>> GetAdjacent(uindex_t i) const override;
  std::list<EdgeData<V>> GetAdjacent(const V &vertex) const override;

  void AddVertex(const V &vertex) override;
  void AddEdge(const V &v0, const V &v1, weight_t weight) override;

 private:
  vector<sptr<V>> vertices_;
  vector<vector<opt<weight_t>>> matrix_;
};

}  // namespace rose

#include "no_brainers/11_graph/edge_table.cc"

#endif  // CS2420_NOBRAINERS_11GRAPH_EDGETABLE_H_
