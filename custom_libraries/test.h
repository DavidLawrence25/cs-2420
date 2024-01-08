#include <string>
#include <vector>

#ifndef CS1410_CUSTOMLIBRARIES_TEST_H_
#define CS1410_CUSTOMLIBRARIES_TEST_H_

namespace rose {

enum AssertionType {
  kEqual,
  kNotEqual,
  kGreater,
  kGreaterEqual,
  kLess,
  kLessEqual,
  kTrue,
  kFalse
};

struct AssertionFail {
  AssertionType type;
  std::string repr_a;
  std::string repr_b;
};

class TestCase {
 public:
  virtual void SetUp() = 0;
  virtual void TearDown() = 0;

  TestResult Run();

  template <typename T>
  void AssertEqual(T a, T b, std::string repr_a, std::string repr_b);
  template <typename T>
  void AssertNotEqual(T a, T b, std::string repr_a, std::string repr_b);
  template <typename T>
  void AssertGreater(T a, T b, std::string repr_a, std::string repr_b);
  template <typename T>
  void AssertGreaterEqual(T a, T b, std::string repr_a, std::string repr_b);
  template <typename T>
  void AssertLess(T a, T b, std::string repr_a, std::string repr_b);
  template <typename T>
  void AssertLessEqual(T a, T b, std::string repr_a, std::string repr_b);
  void AssertTrue(bool expression, std::string repr);
  void AssertFalse(bool expression, std::string repr);

 protected:
  std::string name_;
  TestResult result_;
};

class TestResult {
 public:
  size_t tests_ran();
  bool was_successful();

  void AddFailure(AssertionType type, std::string repr_a, std::string repr_b);
  void IncrementTestCounter();

 private:
  std::vector<AssertionFail> failures_;
  size_t tests_ran_ = 0;
  bool was_successful_ = true;
};

}  // namespace rose

#include "test.cc"

#endif  // CS1410_CUSTOMLIBRARIES_TEST_H_
