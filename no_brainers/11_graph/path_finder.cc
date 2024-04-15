#include "no_brainers/11_graph/path_finder.h"

#include "no_brainers/11_graph/edge_table.h"

namespace rose {

template <typename V>
std::list<sptr<V>> PathFinder<V>::ShortestPath(sptr<V> from, sptr<V> to) {
  std::list<sptr<V>> path;
  // Helps prevent segfaults if users are incompetent.
  if (from == nullptr || to == nullptr) return path;

  unvisited_[from].min_weight = 0;  // Doing nothing is free.
  sptr<V> current = from;
  Visit(from);
  while (!unvisited_.empty() && current != to) {
    for (const auto &[neighbor, weight] : table_->GetAdjacent(*current)) {
      if (visited_.contains(neighbor)) continue;
      weight_t new_weight = weight + unvisited_[current].min_weight;
      if (new_weight < unvisited_[neighbor].min_weight) {
        unvisited_[neighbor].previous = current;
        unvisited_[neighbor].min_weight = new_weight;
      }
    }
    current = CheapestUnvisitedVertex();
    if (current == nullptr) return path;
    Visit(current);
  }

  while (current != nullptr) {
    // Because we're at the end of the path, we need to push to the front to get
    // the vertices in the intended order of `from` -> ... -> `to`. This is the
    // entire reason why this method returns a linked list instead of a vector.
    path.push_front(current);
    current = visited_[current].previous;
  }
  return path;
}

template <typename V>
void PathFinder<V>::Reset() {
  unvisited_.merge(visited_);
  visited_.clear();
  for (auto &[vertex, data] : unvisited_) {
    data.previous = nullptr;
    data.min_weight = EdgeTable<V>::kWeightMax;
  }
}

template <typename V>
sptr<V> PathFinder<V>::CheapestUnvisitedVertex() const {
  EdgeData<V> best_candidate{nullptr, EdgeTable<V>::kWeightMax};
  for (const auto &[vertex, data] : unvisited_) {
    if (data.min_weight < best_candidate.weight) {
      best_candidate.vertex = vertex;
      best_candidate.weight = data.min_weight;
    }
  }
  return best_candidate.vertex;
}

template <typename V>
void PathFinder<V>::Visit(sptr<V> vertex) {
  // Should always be true, but we check in case the user
  // decided to revisit a vertex for some reason.
  if (unvisited_.contains(vertex)) {
    visited_[vertex] = unvisited_[vertex];
    unvisited_.erase(vertex);
  }
}

}  // namespace rose
