#include "labs/11_missionaries_cannibals/state.h"

#include <ostream>

#include "custom_libraries/aliases.h"

namespace rose {

bool State::IsValid() const {
  return !(missionaries_ && missionaries_ < cannibals_)
      && !(missionaries_ < pairs_ && missionaries_ > cannibals_)
      && !(missionaries_ > pairs_ || cannibals_ > pairs_);
}

bool State::IsNeighborOf(const State &other, const u32 boat_capacity) const {
  return AreNeighbors(*this, other, boat_capacity);
}

constexpr u32 DistanceBetween(const u32 x, const u32 y) {
  return x > y ? x - y : y - x;
}

bool State::AreNeighbors(const State &a, const State &b, const u32 boat_capacity) {
  if (a.is_boat_on_left_ == b.is_boat_on_left_) return false;
  if (a.pairs_ != b.pairs_) return false;
  u32 missionaries_in_boat = DistanceBetween(a.missionaries_, b.missionaries_);
  u32 cannibals_in_boat = DistanceBetween(a.cannibals_, b.cannibals_);
  return missionaries_in_boat + cannibals_in_boat <= boat_capacity;
}

std::ostream &operator<<(std::ostream &out, const State &state) {
  if (!state.IsValid()) {
    out << state.missionaries_ << ',' << state.cannibals_ << ','
        << state.is_boat_on_left_ << " (invalid)";
    return out;
  }
  u32 missionaries_on_right = state.pairs_ - state.missionaries_;
  u32 cannibals_on_right = state.pairs_ - state.cannibals_;
  for (u32 _ = 0; _ < missionaries_on_right; ++_) out << '_';
  for (u32 _ = 0; _ < state.missionaries_; ++_) out << 'M';
  out << ' ';
  for (u32 _ = 0; _ < cannibals_on_right; ++_) out << '_';
  for (u32 _ = 0; _ < state.cannibals_; ++_) out << 'C';
  out << " |" << (state.is_boat_on_left_ ? "B~~" : "~~B") << "| ";
  for (u32 _ = 0; _ < state.missionaries_; ++_) out << '_';
  for (u32 _ = 0; _ < missionaries_on_right; ++_) out << 'M';
  out << ' ';
  for (u32 _ = 0; _ < state.cannibals_; ++_) out << '_';
  for (u32 _ = 0; _ < cannibals_on_right; ++_) out << 'C';
  return out;
}

}  // namespace rose
