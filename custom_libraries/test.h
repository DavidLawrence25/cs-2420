#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "json_writer.h"

#ifndef CS2420_CUSTOMLIBRARIES_TEST_H_
#define CS2420_CUSTOMLIBRARIES_TEST_H_

namespace rose {

// Used to identify local variables in a test function.
using LocalTag = std::string;
// Used to identify "global" variables in a test case.
// "Globals" are defined as member variables of a class derived from TestCase
// that are used in multiple test functions.
using GlobalTag = std::string;

// Stores important information about a "global" variable, including a pointer
// to the actual variable, its initial value, and a string representation of its
// initial value.
template <typename T>
struct Global {
  T *ptr;
  T init_value;
  std::string init_repr;
};

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

struct IndexedStep;  // Forward declaration to inform Step types of existence.

// Represents an abstract timestep in a TestResult.
class Step {
 public:
  Step(std::string parent_func, std::vector<LocalTag> relevant_locals,
       std::vector<GlobalTag> relevant_globals)
      : parent_func_(parent_func),
        relevant_locals_(relevant_locals),
        relevant_globals_(relevant_globals) {}

  std::string parent_func() const;
  std::vector<LocalTag> relevant_locals() const;
  std::vector<GlobalTag> relevant_globals() const;
  virtual std::string step_type() const;

  // Writes Step data to a JSON object.
  virtual void WriteTo(JsonWriter &writer) const = 0;
  // Writes Step data (including its index) to a JSON object.
  virtual void WriteTo(JsonWriter &writer, size_t index) const = 0;

 protected:
  // The name of the test function that caused this Step to be created.
  std::string parent_func_;
  // Local variables relevant to the Step.
  std::vector<LocalTag> relevant_locals_;
  // "Global" variables relevant to the Step.
  std::vector<GlobalTag> relevant_globals_;
};

// Represents a timestep in which an assertion was made.
class Assertion : public Step {
 public:
  Assertion(std::string parent_func, std::vector<LocalTag> relevant_locals,
            std::vector<GlobalTag> relevant_globals, AssertionType type,
            bool passed, std::string repr0,
            std::optional<std::string> repr1 = std::nullopt)
      : Step(parent_func, relevant_locals, relevant_globals),
        type_(type),
        passed_(passed),
        repr0_(repr0),
        repr1_(repr1) {}

  AssertionType type() const;
  bool passed() const;
  std::string repr0() const;
  std::optional<std::string> repr1() const;
  std::string step_type() const override;

  // Writes Assertion data to a JSON object.
  void WriteTo(JsonWriter &writer) const override;
  // Writes Assertion data (including its index) to a JSON object.
  // Has an empty definition because it should never be called.
  void WriteTo(JsonWriter &writer, size_t index) const override {}
  // Writes Assertion data (including its index and context) to a JSON object.
  void WriteTo(JsonWriter &writer, size_t index,
               const std::vector<IndexedStep> &context) const;

 private:
  AssertionType type_;
  bool passed_;
  // A string representation of the first argument.
  std::string repr0_;
  // A string representation of the optional second argument.
  // Will have a value for all binary assertion types.
  std::optional<std::string> repr1_;
};

// Represents a timestep in which an impure function was called, causing some
// relevant variable to change its state.
// BUG: FuncCalls are not considered when determining when a "global" was most
// recently modified.
class FuncCall : public Step {
 public:
  FuncCall(std::string parent_func, std::vector<LocalTag> relevant_locals,
           std::vector<GlobalTag> relevant_globals, std::string repr)
      : Step(parent_func, relevant_locals, relevant_globals), repr_(repr) {}

  std::string repr() const;
  std::string step_type() const override;

  // Writes FuncCall data to a JSON object.
  void WriteTo(JsonWriter &writer) const override;
  // Writes FuncCall data (including its index) to a JSON object.
  void WriteTo(JsonWriter &writer, size_t index) const override;

 private:
  // A string representation of the function call.
  std::string repr_;
};

// Represents a timestep in which a value was explicitly set.
class ValueSet : public Step {
 public:
  ValueSet(std::string parent_func, std::vector<LocalTag> relevant_locals,
           std::vector<GlobalTag> relevant_globals, bool is_init,
           bool is_global, std::string value_name, std::string value)
      : Step(parent_func, relevant_locals, relevant_globals),
        is_init_(is_init),
        is_global_(is_global),
        value_name_(value_name),
        value_(value) {}

  bool is_init() const;
  bool is_global() const;
  std::string value_name() const;
  std::string value() const;
  std::string step_type() const override;

  // Writes ValueSet data to a JSON object.
  void WriteTo(JsonWriter &writer) const override;
  // Writes ValueSet data (including its index) to a JSON object.
  void WriteTo(JsonWriter &writer, size_t index) const override;

 private:
  // Whether or not the variable is being initialized.
  bool is_init_;
  // Whether or not the variable is "global".
  bool is_global_;
  // The name of the variable being set.
  std::string value_name_;
  // A string representation of the variable's new value.
  std::string value_;
};

struct IndexedStep {
  size_t index;
  Step *step;
};

// Compares two IndexedStep objects, returning true if `a` has a lower index
// than `b` (i.e., `a` happened before `b`).
bool __cmp__(const IndexedStep &a, const IndexedStep &b);

struct IndexedAssertion {
  size_t index;
  Assertion *assertion;
};

// Holds information about the results of a TestCase.
class TestResult {
 public:
  size_t tests_ran() const;
  size_t tests_failed() const;
  // Returns a list of timesteps involving the local `tag` before `before`.
  std::vector<IndexedStep> GetLocalSteps(LocalTag tag, size_t before);
  // Returns a list of timesteps involving the global `tag` before `before`.
  std::vector<IndexedStep> GetGlobalSteps(GlobalTag tag, size_t before);

  // Adds a Step to the timeline.
  void AddStep(Step *step);
  // Adds an Assertion to the timeline.
  // Also adds the Assertion to the corresponding IndexedAssertion vector.
  void AddStep(Assertion *step);
  // Adds a ValueSet to the timeline.
  // Also updates `most_recent_global_set_` if the variable is global.
  void AddStep(ValueSet *step);
  // Adds one to the internal test counter.
  void IncrementTestCounter();
  // Adds one to the internal fail counter.
  void IncrementFailCounter();

  // Reports information about the TestCase to the terminal.
  // Information is condensed to only feature tests that failed.
  void Report();
  // Logs information about the TestCase to the text file at `file_path`.
  // Includes all tests and a detailed timeline of events.
  void LogTxt(const std::string &file_path);
  // Logs information about the TestCase to the JSON file at `file_path`.
  // Includes all tests and a detailed timeline of events.
  void LogJson(const std::string &file_path);

 private:
  // The number of tests ran.
  size_t tests_ran_ = 0;
  // The number of tests failed.
  size_t tests_failed_ = 0;
  // An ordered list of timesteps.
  std::vector<Step *> timeline_;
  // All the assertions that failed.
  std::vector<IndexedAssertion> failed_;
  // All the assertions that passed.
  std::vector<IndexedAssertion> passed_;
  // A mapping of GlobalTags to the highest indices at which they were set.
  std::unordered_map<GlobalTag, size_t> most_recent_global_set_;
};

// Runs a series of related test functions defined by the user.
// All "global" variables must be of type `GlobalType`.
// "Globals" are defined as member variables of a class derived from TestCase
// that are used in multiple test functions.
template <typename GlobalType>
class TestCase {
 public:
  // Runs the tests given in its definition and returns the result.
  // Default implementation simply returns the result.
  // A derived definition may look like this:
  // `TestResult Run() {`
  // `  RunTest(foo, "foo");`
  // `  RunTest(bar, "bar");`
  // `  RunTest(baz, "baz");`
  // `  return result_;`
  // `}`
  virtual TestResult Run();

  // Runs a class method `test_func` and updates the results accordingly.
  template <typename T>
  void RunTest(void (T::*test_func)(), const std::string &test_name);

  // Begins tracking `global` by `tag`, allowing it to appear in timesteps.
  void AddGlobal(GlobalTag tag, Global<GlobalType> global);
  // Resets the "global" corresponding to `tag` to its initial value.
  void ResetGlobal(GlobalTag tag);

  // Adds `step` to the timeline.
  void AddStep(Step *step);
  // Adds a FuncCall step with the given data to the timeline.
  void AddFuncCall(const std::vector<LocalTag> &relevant_locals,
                   const std::vector<GlobalTag> &relevant_globals,
                   const std::string &repr);
  // Adds a ValueSet step with the given data to the timeline.
  void AddValueSet(const std::vector<LocalTag> &relevant_locals,
                   const std::vector<GlobalTag> &relevant_globals, bool is_init,
                   bool is_global, const std::string &value_name,
                   const std::string &value);

  // Asserts that `arg0 == arg1` and adds the result to the timeline.
  template <typename T>
  void AssertEqual(T arg0, T arg1, const std::string &repr0,
                   const std::string &repr1,
                   const std::vector<LocalTag> &relevant_locals,
                   const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `arg0 != arg1` and adds the result to the timeline.
  template <typename T>
  void AssertNotEqual(T arg0, T arg1, const std::string &repr0,
                      const std::string &repr1,
                      const std::vector<LocalTag> &relevant_locals,
                      const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `arg0 > arg1` and adds the result to the timeline.
  template <typename T>
  void AssertGreater(T arg0, T arg1, const std::string &repr0,
                     const std::string &repr1,
                     const std::vector<LocalTag> &relevant_locals,
                     const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `arg0 >= arg1` and adds the result to the timeline.
  template <typename T>
  void AssertGreaterEqual(T arg0, T arg1, const std::string &repr0,
                          const std::string &repr1,
                          const std::vector<LocalTag> &relevant_locals,
                          const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `arg0 < arg1` and adds the result to the timeline.
  template <typename T>
  void AssertLess(T arg0, T arg1, const std::string &repr0,
                  const std::string &repr1,
                  const std::vector<LocalTag> &relevant_locals,
                  const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `arg0 <= arg1` and adds the result to the timeline.
  template <typename T>
  void AssertLessEqual(T arg0, T arg1, const std::string &repr0,
                       const std::string &repr1,
                       const std::vector<LocalTag> &relevant_locals,
                       const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `expression == true` and adds the result to the timeline.
  void AssertTrue(bool expression, const std::string &repr,
                  const std::vector<LocalTag> &relevant_locals,
                  const std::vector<GlobalTag> &relevant_globals);
  // Asserts that `expression == false` and adds the result to the timeline.
  void AssertFalse(bool expression, const std::string &repr,
                   const std::vector<LocalTag> &relevant_locals,
                   const std::vector<GlobalTag> &relevant_globals);

 protected:
  TestResult result_;
  std::unordered_map<GlobalTag, Global<GlobalType>> globals_;

 private:
  // The name of the test currently being ran.
  std::string test_name_ = "__TestCaseConstructor__";
};

}  // namespace rose

#include "test.cc"

#endif  // CS2420_CUSTOMLIBRARIES_TEST_H_
