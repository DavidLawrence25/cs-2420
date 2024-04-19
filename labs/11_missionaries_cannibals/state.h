#ifndef CS2420_LABS_11MISSIONARIESCANNIBALS_STATE_H_
#define CS2420_LABS_11MISSIONARIESCANNIBALS_STATE_H_

#include <ostream>

#include "custom_libraries/aliases.h"

namespace rose {

class State {
 public:
  static constexpr State Goal(const u32 pairs = 3) {
    return {0, 0, false, pairs};
  }

  State(const u32 missionaries, const u32 cannibals, const bool is_boat_on_left,
        const u32 pairs = 3) : missionaries_(missionaries),
                               cannibals_(cannibals),
                               is_boat_on_left_(is_boat_on_left),
                               pairs_(pairs) {}
  State(const State &other) = default;
  ~State() = default;

  u32 missionaries() const { return missionaries_; }
  u32 cannibals() const { return cannibals_; }
  bool is_boat_on_left() const { return is_boat_on_left_; }
  u32 pairs() const { return pairs_; }

  bool IsValid() const;
  bool IsNeighborOf(const State &other, u32 boat_capacity) const;
  static bool AreNeighbors(const State &a, const State &b, u32 boat_capacity);

  bool operator==(const State &other) const = default;
  friend std::ostream &operator<<(std::ostream &out, const State &state);

 private:
  u32 missionaries_;
  u32 cannibals_;
  bool is_boat_on_left_;
  u32 pairs_;
};

}  // namespace rose

#endif  // CS2420_LABS_11MISSIONARIESCANNIBALS_STATE_H_
