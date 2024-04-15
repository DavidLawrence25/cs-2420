#include "no_brainers/11_graph/edge_table.h"

#include "custom_libraries/aliases.h"

namespace rose {

template <typename V>
bool EdgeTable<V>::Contains(const V &vertex) const {
  return IndexOf(vertex).has_value();
}

template <typename V>
uptr<EdgeTable<V>> AdjacencyList<V>::MakeCopy() const {
  return std::make_unique<AdjacencyList<V>>(*this);
}

template <typename V>
AdjacencyList<V>::AdjacencyList(const AdjacencyList<V> &other) {
  for (sptr<V> vertex : other.vertices_) {
    vertices_.push_back(std::make_shared<V>(*vertex));
  }
  edge_lists_ = other.edge_lists_;
}

template <typename V>
AdjacencyList<V> &AdjacencyList<V>::operator=(const AdjacencyList<V> &other) {
  vertices_.clear();
  for (sptr<V> vertex : other.vertices_) {
    vertices_.push_back(std::make_shared<V>(*vertex));
  }
  edge_lists_ = other.edge_lists_;
  return *this;
}

template <typename V>
size_t AdjacencyList<V>::num_edges() const {
  size_t sum = 0;
  for (const std::list<EdgeData<V>> &ls : edge_lists_) {
    sum += ls.size();
  }
  size_t half_sum = sum >> 1;
  return sum & 1 ? half_sum + 1 : half_sum;
}

template <typename V>
opt<uindex_t> AdjacencyList<V>::IndexOf(const V &vertex) const {
  uindex_t i = 0;
  for (sptr<V> v : vertices_) {
    if (*v == vertex) return i;
    ++i;
  }
  return std::nullopt;
}

template <typename V>
opt<u64> AdjacencyList<V>::DegreeOfVertexAt(uindex_t i) const {
  return i < vertices_.size() ? opt<u64>{edge_lists_[i].size()} : std::nullopt;
}

template <typename V>
bool AdjacencyList<V>::Adjacent(const V &v0, const V &v1) const {
  opt<uindex_t> i = IndexOf(v0);
  // We only need to search for `v0` at first
  // because this is for an undirected graph.
  if (!i.has_value()) return false;
  for (EdgeData<V> data : edge_lists_[i.value()]) {
    if (*data.vertex == v1) return true;
  }
  return false;
}

template <typename V>
std::list<EdgeData<V>> AdjacencyList<V>::GetAdjacent(uindex_t i) const {
  return i < num_vertices() ? edge_lists_[i] : std::list<EdgeData<V>>{};
}

template <typename V>
std::list<EdgeData<V>> AdjacencyList<V>::GetAdjacent(const V &vertex) const {
  opt<uindex_t> i = IndexOf(vertex);
  return i.has_value() ? edge_lists_[i.value()] : std::list<EdgeData<V>>{};
}

template <typename V>
void AdjacencyList<V>::AddVertex(const V &vertex) {
  // For speed, we will assume `vertex` doesn't exist in the graph yet.
  vertices_.push_back(std::make_shared<V>(vertex));
  edge_lists_.push_back(std::list<EdgeData<V>>());
}

template <typename V>
void AdjacencyList<V>::AddEdge(const V &v0, const V &v1, weight_t weight) {
  // For speed, we will assume `v0` and `v1` are not already connected.
  opt<uindex_t> i0 = IndexOf(v0);
  if (!i0.has_value()) {
    i0 = vertices_.size();
    AddVertex(v0);
  }
  opt<uindex_t> i1 = IndexOf(v1);
  if (!i1.has_value()) {
    i1 = vertices_.size();
    AddVertex(v1);
  }
  EdgeData<V> data0 = {.vertex = vertices_[i1.value()], .weight = weight};
  // You would normally push to the back instead of the front, but because we're
  // using a singly-linked list, operations on the back are expensive.
  edge_lists_[i0.value()].push_front(data0);
  // If we just made a loop, we don't want to make the same exact loop.
  if (i0 != i1) {
    EdgeData<V> data1 = {.vertex = vertices_[i0.value()], .weight = weight};
    edge_lists_[i1.value()].push_front(data1);
  }
}

template <typename V>
uptr<EdgeTable<V>> AdjacencyMatrix<V>::MakeCopy() const {
  return std::make_unique<AdjacencyMatrix<V>>(*this);
}

template <typename V>
AdjacencyMatrix<V>::AdjacencyMatrix(const AdjacencyMatrix<V> &other) {
  for (sptr<V> vertex : other.vertices_) {
    vertices_.push_back(std::make_shared<V>(*vertex));
  }
  matrix_ = other.matrix_;
}

template <typename V>
AdjacencyMatrix<V> &AdjacencyMatrix<V>::operator=(
    const AdjacencyMatrix<V> &other) {
  vertices_.clear();
  for (sptr<V> vertex : other.vertices_) {
    vertices_.push_back(std::make_shared<V>(*vertex));
  }
  matrix_ = other.matrix_;
  return *this;
}

template <typename V>
size_t AdjacencyMatrix<V>::num_edges() const {
  size_t count = 0;
  uindex_t i = 0;
  for (vector<opt<weight_t>> row : matrix_) {
    for (uindex_t j = i; j < row.size(); ++j) {
      if (row[j].has_value()) ++count;
    }
    ++i;
  }
  return count;
}

template <typename V>
opt<uindex_t> AdjacencyMatrix<V>::IndexOf(const V &vertex) const {
  uindex_t i = 0;
  for (sptr<V> v : vertices_) {
    if (*v == vertex) return i;
    ++i;
  }
  return std::nullopt;
}

template <typename V>
opt<u64> AdjacencyMatrix<V>::DegreeOfVertexAt(uindex_t i) const {
  if (i >= num_vertices) return std::nullopt;
  u64 degree = 0;
  for (opt<s32> weight : vertices_[i]) {
    if (weight.has_value()) ++degree;
  }
  return degree;
}

template <typename V>
bool AdjacencyMatrix<V>::Adjacent(const V &v0, const V &v1) const {
  opt<uindex_t> i = IndexOf(v0);
  if (!i.has_value()) return false;
  opt<uindex_t> j = IndexOf(v1);
  if (!j.has_value()) return false;
  return matrix_[i.value()][j.value()].has_value();
}

template <typename V>
std::list<EdgeData<V>> AdjacencyMatrix<V>::GetAdjacent(uindex_t i) const {
  std::list<EdgeData<V>> adjacent_vertices;
  for (opt<weight_t> weight : matrix_[i]) {
    if (weight.has_value()) {
      adjacent_vertices.push_back(EdgeData<V>{vertices_[i], weight.value()});
    }
  }
  return adjacent_vertices;
}

template <typename V>
std::list<EdgeData<V>> AdjacencyMatrix<V>::GetAdjacent(const V &vertex) const {
  std::list<EdgeData<V>> adjacent_vertices;
  opt<uindex_t> i = IndexOf(vertex);
  if (!i.has_value()) return adjacent_vertices;
  for (opt<weight_t> weight : matrix_[i.value()]) {
    if (weight.has_value()) {
      adjacent_vertices.push_back(
          EdgeData<V>{vertices_[i.value()], weight.value()});
    }
  }
  return adjacent_vertices;
}

template <typename V>
void AdjacencyMatrix<V>::AddVertex(const V &vertex) {
  vertices_.push_back(std::make_shared<V>(vertex));
  for (vector<opt<weight_t>> row : matrix_) row.emplace_back(std::nullopt);
  matrix_.push_back(vector<opt<weight_t>>(num_vertices(), std::nullopt));
}

template <typename V>
void AdjacencyMatrix<V>::AddEdge(const V &v0, const V &v1, weight_t weight) {
  // For speed, we will assume `v0` and `v1` are not already connected.
  opt<uindex_t> i0 = IndexOf(v0);
  if (!i0.has_value()) {
    i0 = vertices_.size();
    AddVertex(v0);
  }
  opt<uindex_t> i1 = IndexOf(v1);
  if (!i1.has_value()) {
    i1 = vertices_.size();
    AddVertex(v1);
  }
  matrix_[i0.value()][i1.value()] = weight;
  matrix_[i1.value()][i0.value()] = weight;
}

}  // namespace rose
