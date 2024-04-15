#include "no_brainers/11_graph/graph.h"

#include "custom_libraries/aliases.h"
#include "no_brainers/11_graph/path_finder.h"

namespace rose {

template <typename V>
Graph<V> &Graph<V>::operator=(const Graph<V> &other) {
  table_ = other.table_->MakeCopy();
  return *this;
}

template <typename V>
typename Graph<V>::Path Graph<V>::PathfindDijkstra(const V &start,
                                                   const V &end) const {
  sptr<V> from, to;
  {
    opt<uindex_t> temp = IndexOf(start);
    if (!temp.has_value()) return Path{};
    from = table_->operator[](temp.value());
  }
  {
    opt<uindex_t> temp = IndexOf(end);
    if (!temp) return Path{};
    to = table_->operator[](temp.value());
  }
  return PathFinder<V>(table_).ShortestPath(from, to);
}

}  // namespace rose
