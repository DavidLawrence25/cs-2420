#include "custom_libraries/unit_test/unit_test.h"
#include "labs/07_gumball_guess/person.h"
#include "labs/07_gumball_guess/queue.h"

using rose::Assertion, rose::TestCase, rose::TestResult;
using rose::Person, rose::Queue;

class QueueTest : public TestCase {
 public:
  QueueTest() { Repair(); }

  void Repair() override {
    nums_ = Queue<int>();  // Doesn't rely on Clear method to work.
    for (int x = 0; x < 5; ++x) nums_.Enqueue(x);
  }

  void Run() override {
    TestCopyConstructor();
    TestCopyConstructorIsDeep();
    TestAssignOperatorIsDeep();
    TestEnqueue();
    TestDequeue();
    TestClear();
    TestRedundantDequeue();
  }

  void TestCopyConstructor() {
    Queue<int> copy = nums_;
    std::stringstream copy_sout;
    copy_sout << copy;
    ASSERT_EQUAL(copy_sout.str(), std::string("0\n1\n2\n3\n4\n"));
  }

  void TestCopyConstructorIsDeep() {
    Queue<int> copy = nums_;
    copy.Dequeue();
    ASSERT_NOT_EQUAL(copy.PeekFront().value(), nums_.PeekFront().value());
    Repair();  // Redundant unless the test failed.
  }

  void TestAssignOperatorIsDeep() {
    Queue<int> copy;
    copy = nums_;
    copy.Dequeue();
    ASSERT_NOT_EQUAL(copy.PeekFront().value(), nums_.PeekFront().value());
    Repair();  // Redundant unless the test failed.
  }

  void TestEnqueue() {
    // Enqueue stuff is done in Repair method.
    ASSERT_EQUAL(nums_.PeekFront().value_or(-1), 0);
  }

  void TestDequeue() {
    nums_.Dequeue();
    ASSERT_EQUAL(nums_.PeekFront().value_or(-1), 1);
    Repair();
  }

  void TestClear() {
    nums_.Clear();
    ASSERT_TRUE(nums_.empty());
    Repair();
  }

  void TestRedundantDequeue() {
    nums_.Clear();
    // Why would you crash the program if your
    // user tries to dequeue an extra time?
    ASSERT_DOESNT_THROW(nums_.Dequeue());
    Repair();
  }

 private:
  Queue<int> nums_;
};

class GumballGuessTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestRound1();
    TestRound2();
  }

  void TestRound1() {
    Queue<Person> players;
    players.Enqueue(Person("Sarah", 105));
    players.Enqueue(Person("Kim", 96));
    players.Enqueue(Person("Bob", 95));
    players.Enqueue(Person("Brook", 93));
    players.Enqueue(Person("Zed", 106));
    players.Enqueue(Person("Brock", 104));
    players.Enqueue(Person("Ted", 105));
    std::stringstream real_sout;
    real_sout << Person::FindWinners(100, players);
    ASSERT_EQUAL(real_sout.str(), std::string("Kim: 96\nBrock: 104\n"));
  }

  void TestRound2() {
    Queue<Person> players;
    players.Enqueue(Person("Sarah", 40));
    players.Enqueue(Person("Kim", 60));
    players.Enqueue(Person("Bob", 45));
    players.Enqueue(Person("Brook", 44));
    players.Enqueue(Person("Zed", 55));
    players.Enqueue(Person("Brock", 48));
    players.Enqueue(Person("Ted", 52));
    players.Enqueue(Person("Ana", 48));
    std::stringstream real_sout;
    real_sout << Person::FindWinners(50, players);
    ASSERT_EQUAL(real_sout.str(), std::string("Brock: 48\nTed: 52\nAna: 48\n"));
  }
};
