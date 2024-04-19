#ifndef CS2420_LABS_11MISSIONARIESCANNIBALS_TESTCASES_H_
#define CS2420_LABS_11MISSIONARIESCANNIBALS_TESTCASES_H_

#include <list>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/11_missionaries_cannibals/missionaries_cannibals.h"
#include "labs/11_missionaries_cannibals/state.h"

using rose::MissionariesCannibals, rose::State;
using rose::TestCase, rose::TestResult;

class MissionariesCannibalsTest final : public TestCase {
 public:
  void Repair() override { solution_.clear(); }
  void Run() override {
    TestNoSolution2PairsWithBoatFor1();
    solution_ = simulation_2_pairs_with_boat_for_2_.Solve();
    TestSolutionLength2PairsWithBoatFor2();
    TestSolutionStart2PairsWithBoatFor2();
    TestSolutionEnd2PairsWithBoatFor2();
    TestSolutionValidity2PairsWithBoatFor2();
    solution_ = simulation_3_pairs_with_boat_for_2_.Solve();
    TestSolutionLength3PairsWithBoatFor2();
    TestSolutionStart3PairsWithBoatFor2();
    TestSolutionEnd3PairsWithBoatFor2();
    TestSolutionValidity3PairsWithBoatFor2();
    TestNoSolution4PairsWithBoatFor2();
    solution_ = simulation_5_pairs_with_boat_for_3_.Solve();
    TestSolutionLength5PairsWithBoatFor3();
    TestSolutionStart5PairsWithBoatFor3();
    TestSolutionEnd5PairsWithBoatFor3();
    TestSolutionValidity5PairsWithBoatFor3();
    Repair();
  }

  void TestNoSolution2PairsWithBoatFor1() {
    ASSERT_FALSE(simulation_2_pairs_with_boat_for_1_.IsSolvable());
  }

  void TestSolutionLength2PairsWithBoatFor2() {
    ASSERT_EQUAL(solution_.size(), size_t{6});
  }

  void TestSolutionStart2PairsWithBoatFor2() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.front(), State(2, 2, true, 2));
  }

  void TestSolutionEnd2PairsWithBoatFor2() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.back(), State::Goal(/*pairs=*/2));
  }

  void TestSolutionValidity2PairsWithBoatFor2() {
    bool is_valid_solution = true;
    auto it = solution_.cbegin();
    auto prev = it;
    if (it != solution_.cend()) ++it;
    for (; it != solution_.cend(); ++it, ++prev) {
      if (State::AreNeighbors(**prev, **it, /*boat_capacity=*/2)) continue;
      is_valid_solution = false;
      break;
    }
    ASSERT_TRUE(is_valid_solution);
  }

  void TestSolutionLength3PairsWithBoatFor2() {
    ASSERT_EQUAL(solution_.size(), size_t{12});
  }

  void TestSolutionStart3PairsWithBoatFor2() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.front(), State(3, 3, true, 3));
  }

  void TestSolutionEnd3PairsWithBoatFor2() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.back(), State::Goal(/*pairs=*/3));
  }

  void TestSolutionValidity3PairsWithBoatFor2() {
    bool is_valid_solution = true;
    auto it = solution_.cbegin();
    auto prev = it;
    if (it != solution_.cend()) ++it;
    for (; it != solution_.cend(); ++it, ++prev) {
      if (State::AreNeighbors(**prev, **it, /*boat_capacity=*/2)) continue;
      is_valid_solution = false;
      break;
    }
    ASSERT_TRUE(is_valid_solution);
  }

  void TestNoSolution4PairsWithBoatFor2() {
    ASSERT_FALSE(simulation_4_pairs_with_boat_for_2_.IsSolvable());
  }

  void TestSolutionLength5PairsWithBoatFor3() {
    ASSERT_EQUAL(solution_.size(), size_t{12});
  }

  void TestSolutionStart5PairsWithBoatFor3() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.front(), State(5, 5, true, 5));
  }

  void TestSolutionEnd5PairsWithBoatFor3() {
    if (bool you_fricked_up = solution_.empty()) {
      ASSERT_FALSE(you_fricked_up);
      return;
    }
    ASSERT_EQUAL(*solution_.back(), State::Goal(5));
  }

  void TestSolutionValidity5PairsWithBoatFor3() {
    bool is_valid_solution = true;
    auto it = solution_.cbegin();
    auto prev = it;
    if (it != solution_.cend()) ++it;
    for (; it != solution_.cend(); ++it, ++prev) {
      if (State::AreNeighbors(**prev, **it, /*boat_capacity=*/3)) continue;
      is_valid_solution = false;
      break;
    }
    ASSERT_TRUE(is_valid_solution);
  }

 private:
  std::list<sptr<State>> solution_;
  MissionariesCannibals simulation_2_pairs_with_boat_for_1_{{2, 2, true, 2}, 1};
  MissionariesCannibals simulation_2_pairs_with_boat_for_2_{{2, 2, true, 2}, 2};
  MissionariesCannibals simulation_3_pairs_with_boat_for_2_{{3, 3, true, 3}, 2};
  MissionariesCannibals simulation_4_pairs_with_boat_for_2_{{4, 4, true, 4}, 2};
  MissionariesCannibals simulation_5_pairs_with_boat_for_3_{{5, 5, true, 5}, 3};
};

#endif  // CS2420_LABS_11MISSIONARIESCANNIBALS_TESTCASES_H_
