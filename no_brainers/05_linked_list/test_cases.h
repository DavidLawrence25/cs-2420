#include <stdlib.h>

#include <sstream>
#include <string>

#include "custom_libraries/d_linked_list.h"
#include "custom_libraries/unit_test/unit_test.h"

using /*rose::Assertion,*/ rose::TestCase, rose::TestResult, rose::TestSuite;
using rose::DLinkedList, rose::DLinkedListIterator;

class EmptyLinkedListTest : public TestCase {
 public:
  void Repair() override {}
  void Run() override {
    TestIsEmpty();
    TestPeekFront();
    TestPeekBack();
    TestPeek3();
    TestPeekNegative2();
    TestStreamExtraction();
  }

  void TestIsEmpty() { ASSERT_TRUE(list_.empty()); }
  void TestPeekFront() { ASSERT_FALSE(list_.PeekFront().has_value()); }
  void TestPeekBack() { ASSERT_FALSE(list_.PeekBack().has_value()); }
  void TestPeek3() { ASSERT_FALSE(list_.Peek(3).has_value()); }
  void TestPeekNegative2() { ASSERT_FALSE(list_.Peek(-2).has_value()); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << list_;
    ASSERT_EQUAL(sout.str(), std::string());
  }

 private:
  const DLinkedList<int> list_;
};

class IntLinkedListTest : public TestCase {
 public:
  IntLinkedListTest() { Repair(); }

  void Repair() override {
    pi_ = DLinkedList<int>();
    for (int digit : kDigitsOfPi) pi_.PushBack(digit);
  }

  void Run() override {
    TestPushFront1Item();
    TestPushFront20Items();
    TestPushBack1Item();
    TestPushBack20Items();
    TestPeekFront();
    TestPeekBack();
    TestPeekFrontAndBack();
    TestPeek1stDigitOfPi();
    TestPeek27thDigitOfPi();
    TestPeek100thDigitOfPi();
    TestInsertFront();
    TestInsertMiddle();
    TestInsertBack();
    TestPopFront();
    TestPopBack();
    TestEraseFront();
    TestEraseMiddle();
    TestEraseBack();
    TestRemove();
    TestStreamExtraction();
  }

  void TestPushFront1Item() {
    DLinkedList<int> list;
    list.PushFront(5);
    ASSERT_EQUAL(list.size(), size_t{1});
  }

  void TestPushFront20Items() {
    DLinkedList<int> list;
    for (int x = 10; x > -10; --x) list.PushFront(x);
    ASSERT_EQUAL(list.size(), size_t{20});
  }

  void TestPushBack1Item() {
    DLinkedList<int> list;
    list.PushBack(5);
    ASSERT_EQUAL(list.size(), size_t{1});
  }

  void TestPushBack20Items() {
    DLinkedList<int> list;
    for (int x = 10; x > -10; --x) list.PushBack(x);
    ASSERT_EQUAL(list.size(), size_t{20});
  }

  void TestPeekFront() {
    DLinkedList<int> list;
    for (int x = 0; x < 4; ++x) list.PushFront(x);
    ASSERT_EQUAL(list.PeekFront().value(), 3);
  }

  void TestPeekBack() {
    DLinkedList<int> list;
    for (int x = 0; x < 4; ++x) list.PushFront(x);
    ASSERT_EQUAL(list.PeekBack().value(), 0);
  }

  void TestPeekFrontAndBack() {
    DLinkedList<int> list;
    list.PushBack(42);
    ASSERT_EQUAL(list.PeekFront().value(), list.PeekBack().value());
  }

  void TestPeek1stDigitOfPi() { ASSERT_EQUAL(pi_.Peek(0).value(), 3); }
  void TestPeek27thDigitOfPi() { ASSERT_EQUAL(pi_.Peek(26).value(), 8); }
  void TestPeek100thDigitOfPi() { ASSERT_EQUAL(pi_.Peek(99).value(), 7); }

  void TestInsertFront() {
    DLinkedList<int> fibonacci;
    fibonacci.PushBack(1);
    fibonacci.PushBack(1);
    fibonacci.PushBack(2);
    fibonacci.PushBack(3);
    fibonacci.PushBack(5);
    fibonacci.PushBack(8);
    fibonacci.PushBack(13);
    // Wait, we could go backwards.
    fibonacci.Insert(0, 0);
    ASSERT_EQUAL(fibonacci.PeekFront().value(), 0);
  }

  void TestInsertMiddle() {
    DLinkedList<int> primes;
    primes.PushBack(2);
    primes.PushBack(3);
    primes.PushBack(7);
    primes.PushBack(11);
    primes.PushBack(13);
    // Oh no, I *totally* forgot to put 5 in there...
    primes.Insert(2, 5);
    ASSERT_EQUAL(primes.Peek(2).value(), 5);
  }

  void TestInsertBack() {
    DLinkedList<int> e;
    e.PushBack(2);
    e.PushBack(7);
    e.PushBack(1);
    e.PushBack(8);
    e.PushBack(2);
    e.PushBack(8);
    e.PushBack(1);
    e.PushBack(8);
    e.PushBack(2);
    // Eh, enough of not having to think about the index.
    e.Insert(9, 8);
  }

  void TestPopFront() {
    DLinkedList<int> list;
    for (int x = 0; x < 16; ++x) list.PushBack(x);
    list.PopFront();
    ASSERT_EQUAL(list.PeekFront().value(), 1);
  }

  void TestPopBack() {
    DLinkedList<int> list;
    for (int x = -8; x < 8; ++x) list.PushBack(x);
    list.PopBack();
    ASSERT_EQUAL(list.PeekBack().value(), 6);
  }

  void TestEraseFront() {
    DLinkedList<int> list;
    for (int x = -4; x < 4; ++x) list.PushBack(x);
    list.Erase(0);
    ASSERT_EQUAL(list.PeekFront().value(), -3);
  }

  void TestEraseMiddle() {
    DLinkedList<int> list;
    for (int x = -4; x < 4; ++x) list.PushBack(x);
    list.Erase(2);
    ASSERT_EQUAL(list.Peek(2).value(), -1);
  }

  void TestEraseBack() {
    DLinkedList<int> list;
    for (int x = -4; x < 4; ++x) list.PushBack(x);
    list.Erase(7);
    ASSERT_EQUAL(list.PeekBack().value(), 2);
  }

  void TestRemove() {
    DLinkedList<int> list;
    for (int x = -4; x < 4; ++x) list.PushBack(x);
    list.Remove(2);
    ASSERT_EQUAL(list.Peek(6).value(), 3);
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << pi_;
    const std::string expected =
        "3 1 4 1 5 9 2 6 5 3 5 8 9 7 9 3 2 3 8 4 "
        "6 2 6 4 3 3 8 3 2 7 9 5 0 2 8 8 4 1 9 7 "
        "1 6 9 3 9 9 3 7 5 1 0 5 8 2 0 9 7 4 9 4 "
        "4 5 9 2 3 0 7 8 1 6 4 0 6 2 8 6 2 0 8 9 "
        "9 8 6 2 8 0 3 4 8 2 5 3 4 2 1 1 7 0 6 7";
    ASSERT_EQUAL(sout.str(), expected);
  }

 private:
  const int kDigitsOfPi[100] = {
      3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4,
      6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7,
      1, 6, 9, 3, 9, 9, 3, 7, 5, 1, 0, 5, 8, 2, 0, 9, 7, 4, 9, 4,
      4, 5, 9, 2, 3, 0, 7, 8, 1, 6, 4, 0, 6, 2, 8, 6, 2, 0, 8, 9,
      9, 8, 6, 2, 8, 0, 3, 4, 8, 2, 5, 3, 4, 2, 1, 1, 7, 0, 6, 7};
  DLinkedList<int> pi_;
};

class StringLinkedListTest : public TestCase {
 public:
  StringLinkedListTest() { Repair(); }

  void Repair() override {
    sentence_ = DLinkedList<std::string>();
    for (std::string word : kDefaultSentence) sentence_.PushBack(word);
  }

  void Run() override {
    TestPushFront1Item();
    TestPushFront25Items();
    TestPushBack1Item();
    TestPushBack24Items();
    TestPeekFront();
    TestPeekBack();
    TestPeekFrontAndBack();
    TestPeek1stWord();
    TestPeek7thWord();
    TestPeek13thWord();
    TestInsertFront();
    TestInsertMiddle();
    TestInsertBack();
    TestPopFront();
    TestPopBack();
    TestEraseFront();
    TestEraseMiddle();
    TestEraseBack();
    TestRemove();
    TestStreamExtraction();
  }

  void TestPushFront1Item() {
    DLinkedList<std::string> list;
    list.PushFront("strawberry");
    ASSERT_EQUAL(list.size(), size_t{1});
  }

  void TestPushFront25Items() {
    DLinkedList<std::string> list;
    // if you think penguins are fat and waddle, you have never been attacked by
    // one running at you in excess of 100 miles per hour
    // - linus torvalds
    list.PushFront("hour");
    list.PushFront("per");
    list.PushFront("miles");
    list.PushFront("100");
    list.PushFront("of");
    list.PushFront("excess");
    list.PushFront("in");
    list.PushFront("you");
    list.PushFront("at");
    list.PushFront("running");
    list.PushFront("one");
    list.PushFront("by");
    list.PushFront("attacked");
    list.PushFront("been");
    list.PushFront("never");
    list.PushFront("have");
    list.PushFront("you");
    list.PushFront("waddle,");
    list.PushFront("and");
    list.PushFront("fat");
    list.PushFront("are");
    list.PushFront("penguins");
    list.PushFront("think");
    list.PushFront("you");
    list.PushFront("if");
    ASSERT_EQUAL(list.size(), size_t{25});
  }

  void TestPushBack1Item() {
    DLinkedList<std::string> list;
    list.PushBack("pineapple");
    ASSERT_EQUAL(list.size(), size_t{1});
  }

  void TestPushBack24Items() {
    DLinkedList<std::string> list;
    // i never try to make any far-reaching predictions, so much can happen that
    // it simply only makes you look stupid a few years later
    // - linus torvalds
    list.PushBack("i");
    list.PushBack("never");
    list.PushBack("try");
    list.PushBack("to");
    list.PushBack("make");
    list.PushBack("any");
    list.PushBack("far-reaching");
    list.PushBack("predictions,");
    list.PushBack("so");
    list.PushBack("much");
    list.PushBack("can");
    list.PushBack("happen");
    list.PushBack("that");
    list.PushBack("it");
    list.PushBack("simply");
    list.PushBack("only");
    list.PushBack("makes");
    list.PushBack("you");
    list.PushBack("look");
    list.PushBack("stupid");
    list.PushBack("a");
    list.PushBack("few");
    list.PushBack("years");
    list.PushBack("later");
    ASSERT_EQUAL(list.size(), size_t{24});
  }

  void TestPeekFront() {
    ASSERT_EQUAL(sentence_.PeekFront().value(), std::string("but"));
  }

  void TestPeekBack() {
    ASSERT_EQUAL(sentence_.PeekBack().value(), std::string("it"));
  }

  void TestPeekFrontAndBack() {
    DLinkedList<std::string> list;
    list.PushBack("mango");
    ASSERT_EQUAL(list.PeekFront().value(), list.PeekBack().value());
  }

  void TestPeek1stWord() {
    ASSERT_EQUAL(sentence_.Peek(0).value(), std::string("but"));
  }

  void TestPeek7thWord() {
    ASSERT_EQUAL(sentence_.Peek(6).value(), std::string("even"));
  }

  void TestPeek13thWord() {
    ASSERT_EQUAL(sentence_.Peek(12).value(), std::string("it"));
  }

  void TestInsertFront() {
    DLinkedList<std::string> rick_roll;
    rick_roll.PushBack("gonna");
    rick_roll.PushBack("give");
    rick_roll.PushBack("you");
    rick_roll.PushBack("up");
    // Wait, that's not good.
    rick_roll.Insert(0, "never");
    ASSERT_EQUAL(rick_roll.PeekFront().value(), std::string("never"));
  }

  void TestInsertMiddle() {
    DLinkedList<std::string> all_star;
    all_star.PushBack("somebody");
    all_star.PushBack("once");
    all_star.PushBack("told");
    all_star.PushBack("me");
    all_star.PushBack("world");
    all_star.PushBack("is");
    all_star.PushBack("gonna");
    all_star.PushBack("roll");
    all_star.PushBack("me");
    // Oh no, I *totally* forgot to put "the" in there...
    all_star.Insert(4, "the");
    ASSERT_EQUAL(all_star.Peek(4).value(), std::string("the"));
  }

  void TestInsertBack() {
    DLinkedList<std::string> egg_quote;
    egg_quote.PushBack("what,");
    egg_quote.PushBack("you");
    egg_quote.PushBack("egg!");
    egg_quote.PushBack("[he");
    egg_quote.PushBack("stabs");
    // Eh, enough of not having to think about the index.
    egg_quote.Insert(5, "him]");
  }

  void TestPopFront() {
    sentence_.PopFront();
    ASSERT_EQUAL(sentence_.PeekFront().value(), std::string("i"));
    Repair();
  }

  void TestPopBack() {
    sentence_.PopBack();
    ASSERT_EQUAL(sentence_.PeekBack().value(), std::string("in"));
    Repair();
  }

  void TestEraseFront() {
    sentence_.Erase(0);
    ASSERT_EQUAL(sentence_.PeekFront().value(), std::string("i"));
    Repair();
  }

  void TestEraseMiddle() {
    sentence_.Erase(9);
    ASSERT_EQUAL(sentence_.Peek(9).value(), std::string("believe"));
    Repair();
  }

  void TestEraseBack() {
    sentence_.Erase(12);
    ASSERT_EQUAL(sentence_.PeekBack().value(), std::string("in"));
    Repair();
  }

  void TestRemove() {
    sentence_.Remove("don't");
    ASSERT_EQUAL(sentence_.Peek(9).value(), std::string("believe"));
    Repair();
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << sentence_;
    const std::string expected =
        "but i have heard it works even if you don't believe in it";
    ASSERT_EQUAL(sout.str(), expected);
  }

 private:
  const std::string kDefaultSentence[13] = {
      "but", "i",   "have",  "heard",   "it", "works", "even",
      "if",  "you", "don't", "believe", "in", "it"};
  DLinkedList<std::string> sentence_;
};
