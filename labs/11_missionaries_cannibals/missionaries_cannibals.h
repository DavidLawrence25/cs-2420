#ifndef CS2420_LABS_11MISSIONARIESCANNIBALS_MISSIONARIESCANNIBALS_H_
#define CS2420_LABS_11MISSIONARIESCANNIBALS_MISSIONARIESCANNIBALS_H_

#include <list>
#include <ostream>

#include "custom_libraries/aliases.h"
#include "labs/11_missionaries_cannibals/state.h"
#include "no_brainers/11_graph/edge_table.h"
#include "no_brainers/11_graph/graph.h"

namespace rose {

class MissionariesCannibals {
 public:
  explicit MissionariesCannibals(const State &start_state = {3, 3, true, 3},
                                 const u32 boat_capacity = 2)
      : start_state_(start_state),
        boat_capacity_(boat_capacity),
        graph_(std::make_unique<AdjacencyList<State>>()) {
    graph_.AddVertex(start_state_);
    BuildGraph(start_state_);
  }
  MissionariesCannibals(const MissionariesCannibals &other) = default;
  ~MissionariesCannibals() = default;

  Graph<State> graph() const { return graph_; }

  bool IsSolvable() const;
  std::list<sptr<State>> Solve() const;

 private:
  opt<State> TryMove(const State &state, u32 missionaries, u32 cannibals) const;
  void BuildGraph(const State &state);

  const State start_state_;
  const u32 boat_capacity_;
  Graph<State> graph_;
};

std::ostream &operator<<(std::ostream &out, const std::list<State> &solution);

}  // namespace rose

#endif  // CS2420_LABS_11MISSIONARIESCANNIBALS_MISSIONARIESCANNIBALS_H_
