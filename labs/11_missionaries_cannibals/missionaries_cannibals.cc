#include "labs/11_missionaries_cannibals/missionaries_cannibals.h"

#include "custom_libraries/aliases.h"

namespace rose {

bool MissionariesCannibals::IsSolvable() const {
  if (boat_capacity_ < 2) return false;
  if (boat_capacity_ == 2) return start_state_.pairs() < 4;
  if (boat_capacity_ == 3) return start_state_.pairs() < 6;
  return true;
}

std::list<sptr<State>> MissionariesCannibals::Solve() const {
  return IsSolvable()
      ? graph_.PathfindDijkstra(start_state_, State::Goal(start_state_.pairs()))
      : std::list<sptr<State>>();
}

opt<State> MissionariesCannibals::TryMove(const State &state,
                                          const u32 missionaries,
                                          const u32 cannibals) const {
  u32 people_to_move = missionaries + cannibals;
  if (people_to_move == 0 || people_to_move > boat_capacity_) {
    return std::nullopt;
  }
  u32 missionaries_on_left = state.missionaries();
  u32 cannibals_on_left = state.cannibals();
  if (state.is_boat_on_left()) {
    if (missionaries > missionaries_on_left) return std::nullopt;
    missionaries_on_left -= missionaries;
    if (cannibals > cannibals_on_left) return std::nullopt;
    cannibals_on_left -= cannibals;
  } else {
    missionaries_on_left += missionaries;
    if (missionaries_on_left > state.pairs()) return std::nullopt;
    cannibals_on_left += cannibals;
    if (cannibals_on_left > state.pairs()) return std::nullopt;
  }
  State next_state(missionaries_on_left, cannibals_on_left,
                   !state.is_boat_on_left(), state.pairs());
  return next_state.IsValid() ? std::make_optional<State>(next_state)
                              : std::nullopt;
}

void MissionariesCannibals::BuildGraph(const State &state) {
  if (!state.IsValid() || state == State::Goal()) return;
  for (u32 m = 0; m <= state.pairs(); ++m) {
    for (u32 c = 0; c <= state.pairs(); ++c) {
      opt<State> next_state = TryMove(state, m, c);
      if (!next_state.has_value()) continue;
      bool should_recurse = !graph_.IndexOf(next_state.value()).has_value();
      if (!graph_.Adjacent(state, next_state.value())) {
        graph_.AddEdge(state, next_state.value());
      }
      if (should_recurse) BuildGraph(next_state.value());
    }
  }
}

std::ostream &operator<<(std::ostream &out, const std::list<State> &solution) {
  for (State state : solution) out << state << '\n';
  return out;
}

}  // namespace rose
