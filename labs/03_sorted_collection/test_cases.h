#include <stdlib.h>

#include <sstream>
#include <string>

#include "custom_libraries/unit_test/unit_test.h"
#include "labs/03_sorted_collection/sorted_collection.h"

using rose::SortedCollection, rose::TestCase, rose::TestResult;

class SortedCollectionIntTest : public TestCase {
 public:
  void Repair() override { nums_ = SortedCollection<int>(); }
  void Run() override {
    TestAdd1Time();
    TestAdd4Times();
    TestItemAt0();
    TestItemAtNegative1();
    TestRemoveEnd1Time();
    TestRemoveEnd3Times();
    TestRemoveEndOfEmpty();
    TestExpand1Time();
    TestExpand4Times();
    TestStreamExtraction();
  }

  void TestAdd1Time() {
    nums_.Add(69);
    ASSERT_EQUAL(nums_.length(), size_t{1});
    Repair();
  }

  void TestAdd4Times() {
    for (int x : std::vector<int>({69, 42, 17, 21})) nums_.Add(x);
    ASSERT_EQUAL(nums_.length(), size_t{4});
    Repair();
  }

  void TestItemAt0() {
    for (int x : std::vector<int>({69, 42, 17, 21})) nums_.Add(x);
    ASSERT_EQUAL(nums_.ItemAt(0), 17);
    Repair();
  }

  void TestItemAtNegative1() {
    for (int x : std::vector<int>({69, 42, 17, 21})) nums_.Add(x);
    ASSERT_EQUAL(nums_.ItemAt(-1), 69);
    Repair();
  }

  void TestRemoveEnd1Time() {
    for (int x : std::vector<int>({69, 42, 17, 21})) nums_.Add(x);
    nums_.RemoveEnd();
    ASSERT_EQUAL(nums_.length(), size_t{3});
    Repair();
  }

  void TestRemoveEnd3Times() {
    for (int x : std::vector<int>({42, 17, 21})) nums_.Add(x);
    for (int i = 0; i < 3; ++i) nums_.RemoveEnd();
    ASSERT_EQUAL(nums_.length(), size_t{0});
    Repair();
  }

  void TestRemoveEndOfEmpty() {
    nums_.RemoveEnd();
    ASSERT_EQUAL(nums_.length(), size_t{0});
    Repair();
  }

  void TestExpand1Time() {
    for (int x = 0; x < 9; ++x) nums_.Add(x);
    ASSERT_EQUAL(nums_.capacity(), size_t{16});
    Repair();
  }

  void TestExpand4Times() {
    for (int x = 0; x < 65; ++x) nums_.Add(x);
    ASSERT_EQUAL(nums_.capacity(), size_t{128});
    Repair();
  }

  void TestStreamExtraction() {
    std::stringstream expected;
    expected << '[';
    for (int x = 0; x < 64; ++x) {
      expected << x << ", ";
      nums_.Add(x);
    }
    expected << "64]";
    nums_.Add(64);
    std::stringstream sout;
    sout << nums_;
    ASSERT_EQUAL(sout.str(), expected.str());
    Repair();
  }

 private:
  SortedCollection<int> nums_;
};

class SortedCollectionCharTest : public TestCase {
 public:
  void Repair() override { str_ = SortedCollection<char>(); }
  void Run() override {
    TestAdd5Times();
    TestItemAt4();
    TestRemoveEnd1Time();
    TestExpand2Times();
    TestStreamExtraction();
    TestStreamExtractionOnEmpty();
  }

  void TestAdd5Times() {
    for (char c : "apple") {
      if (c == '\0') break;
      str_.Add(c);
    }
    ASSERT_EQUAL(str_.length(), size_t{5});
    Repair();
  }

  void TestItemAt4() {
    for (char c : "apple") {
      if (c == '\0') break;
      str_.Add(c);
    }
    ASSERT_EQUAL(str_.ItemAt(4), 'p');
    Repair();
  }

  void TestRemoveEnd1Time() {
    for (char c : "apple") {
      if (c == '\0') break;
      str_.Add(c);
    }
    str_.RemoveEnd();
    ASSERT_EQUAL(str_.length(), size_t{4});
    Repair();
  }

  void TestExpand2Times() {
    for (char c : "apples taste pretty good") {
      if (c == '\0') break;
      str_.Add(c);
    }
    ASSERT_EQUAL(str_.capacity(), size_t{32});
    Repair();
  }

  void TestStreamExtraction() {
    std::stringstream expected;
    expected << '[';
    // apples taste prett good
    for (char c : "   aadeeeglooppprsstttt") {
      if (c == '\0') break;
      expected << c << ", ";
    }
    expected << "y]";
    std::stringstream sout;
    for (char c : "apples taste pretty good") {
      if (c == '\0') break;
      str_.Add(c);
    }
    sout << str_;
    ASSERT_EQUAL(sout.str(), expected.str());
    Repair();
  }

  void TestStreamExtractionOnEmpty() {
    std::stringstream sout;
    sout << str_;
    ASSERT_EQUAL(sout.str(), std::string("[]"));
  }

 private:
  SortedCollection<char> str_;
};
