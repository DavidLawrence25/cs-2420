#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "json_writer.h"
#include "test.h"

namespace rose {

std::string Step::parent_func() const { return parent_func_; }
std::vector<LocalTag> Step::relevant_locals() const { return relevant_locals_; }

std::vector<GlobalTag> Step::relevant_globals() const {
  return relevant_globals_;
}

std::string Step::step_type() const { return "unknown"; }

AssertionType Assertion::type() const { return type_; }
bool Assertion::passed() const { return passed_; }
std::string Assertion::repr0() const { return repr0_; }
std::optional<std::string> Assertion::repr1() const { return repr1_; }

std::string Assertion::step_type() const {
  switch (type_) {
    case kEqual:
      return "assert_equal";
    case kNotEqual:
      return "assert_not_equal";
    case kGreater:
      return "assert_greater";
    case kGreaterEqual:
      return "assert_greater_equal";
    case kLess:
      return "assert_less";
    case kLessEqual:
      return "assert_less_equal";
    case kTrue:
      return "assert_true";
    case kFalse:
      return "assert_false";
    default:
      return "";  // Should never happen, but compiler gets grumpy if forgotten.
  }
}

void Assertion::WriteTo(JsonWriter &writer) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateString("step_type", step_type());
  if (type_ == kTrue || type_ == kFalse) {
    writer.CreateString("expression", repr0_);
  } else {
    writer.CreateString("repr0", repr0_);
    writer.CreateString("repr1", repr1_.value());
  }

  writer.EndObject();
}

void Assertion::WriteTo(JsonWriter &writer, size_t index,
                        const std::vector<IndexedStep> &context) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateInt("step", index);
  writer.CreateString("step_type", step_type());
  if (type_ == kTrue || type_ == kFalse) {
    writer.CreateString("expression", repr0_);
  } else {
    writer.CreateString("repr0", repr0_);
    writer.CreateString("repr1", repr1_.value());
  }

  writer.BeginArray("context");
  for (const IndexedStep &step : context) {
    step.step->WriteTo(writer, step.index);
  }
  writer.EndArray();

  writer.EndObject();
}

std::string FuncCall::repr() const { return repr_; }
std::string FuncCall::step_type() const { return "function_call"; }

void FuncCall::WriteTo(JsonWriter &writer) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateString("step_type", step_type());
  writer.CreateString("repr", repr_);

  writer.BeginArray("relevant_locals");
  for (LocalTag tag : relevant_locals_) writer.CreateString(tag);
  writer.EndArray();

  writer.BeginArray("relevant_globals");
  for (GlobalTag tag : relevant_globals_) writer.CreateString(tag);
  writer.EndArray();

  writer.EndObject();
}

void FuncCall::WriteTo(JsonWriter &writer, size_t index) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateInt("step", index);
  writer.CreateString("step_type", step_type());
  writer.CreateString("repr", repr_);

  writer.BeginArray("relevant_locals");
  for (LocalTag tag : relevant_locals_) writer.CreateString(tag);
  writer.EndArray();

  writer.BeginArray("relevant_globals");
  for (GlobalTag tag : relevant_globals_) writer.CreateString(tag);
  writer.EndArray();

  writer.EndObject();
}

bool ValueSet::is_init() const { return is_init_; }
bool ValueSet::is_global() const { return is_global_; }
std::string ValueSet::value_name() const { return value_name_; }
std::string ValueSet::value() const { return value_; }

std::string ValueSet::step_type() const {
  if (is_global_) {
    return (is_init_) ? "global_init" : "global_set";
  }
  return (is_init_) ? "local_init" : "local_set";
}

void ValueSet::WriteTo(JsonWriter &writer) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateString("step_type", step_type());
  if (is_global_) {
    writer.CreateString("global_name", value_name_);
  } else {
    writer.CreateString("local_name", value_name_);
  }
  writer.CreateString("value", value_);

  writer.EndObject();
}

void ValueSet::WriteTo(JsonWriter &writer, size_t index) const {
  writer.BeginObject();

  writer.CreateString("name", parent_func_);
  writer.CreateInt("step", index);
  writer.CreateString("step_type", step_type());
  if (is_global_) {
    writer.CreateString("global_name", value_name_);
  } else {
    writer.CreateString("local_name", value_name_);
  }
  writer.CreateString("value", value_);

  writer.EndObject();
}

bool __cmp__(const IndexedStep &a, const IndexedStep &b) {
  return (a.index < b.index);
}

size_t TestResult::tests_ran() const { return tests_ran_; }

size_t TestResult::tests_failed() const { return tests_failed_; }

std::vector<IndexedStep> TestResult::GetLocalSteps(LocalTag tag,
                                                   size_t before) {
  std::string func = timeline_.at(before)->parent_func();
  std::vector<IndexedStep> steps;
  for (size_t i = 0; i < before; ++i) {
    Step *step = timeline_.at(i);
    if (step->parent_func() != func) continue;  // Must be the same exact local.
    const std::vector<LocalTag> &locals = step->relevant_locals();

    if (std::find(locals.begin(), locals.end(), tag) != locals.end()) {
      steps.push_back({i, step});
    }
  }

  return steps;
}

std::vector<IndexedStep> TestResult::GetGlobalSteps(GlobalTag tag,
                                                    size_t before) {
  std::vector<IndexedStep> steps;
  size_t start = 0;
  if (most_recent_global_set_.contains(tag)) {
    start = most_recent_global_set_.at(tag);
  }
  for (size_t i = start; i < before; ++i) {
    Step *step = timeline_.at(i);
    const std::vector<LocalTag> &globals = step->relevant_globals();

    if (std::find(globals.begin(), globals.end(), tag) != globals.end()) {
      steps.push_back({i, step});
    }
  }

  return steps;
}

void TestResult::AddStep(Step *step) { timeline_.push_back(step); }

void TestResult::AddStep(Assertion *step) {
  if (step->passed()) {
    passed_.push_back({timeline_.size(), step});
  } else {
    failed_.push_back({timeline_.size(), step});
  }

  timeline_.push_back(step);
}

void TestResult::AddStep(ValueSet *step) {
  if (step->is_global()) {
    most_recent_global_set_[step->value_name()] = timeline_.size();
  }

  timeline_.push_back(step);
}

void TestResult::IncrementTestCounter() { ++tests_ran_; }

void TestResult::IncrementFailCounter() { ++tests_failed_; }

void TestResult::LogJson(const std::string &file_path) {
  using Context = std::vector<IndexedStep>;

  std::stringstream path;
  path << file_path;
  if (!file_path.ends_with(".json")) path << ".json";

  std::ofstream file(path.str());
  auto writer = JsonWriter(file);
  writer.BeginObject();

  writer.BeginObject("meta");
  writer.CreateInt("tests_ran", tests_ran_);
  writer.CreateInt("steps_taken", timeline_.size());
  writer.CreateInt("fails", tests_failed_);
  writer.EndObject();

  // BUG: If an assertion involves multiple variables, this context-collection
  // process may grab multiple copies of the same Step. Fixing this would
  // require changing the Context type to a set of some sort.

  writer.BeginArray("tests_failed");
  for (IndexedAssertion fail : failed_) {
    Context full_context;
    for (LocalTag tag : fail.assertion->relevant_locals()) {
      Context partial_context = GetLocalSteps(tag, fail.index);
      full_context.insert(full_context.end(), partial_context.begin(),
                          partial_context.end());
    }
    for (GlobalTag tag : fail.assertion->relevant_globals()) {
      Context partial_context = GetGlobalSteps(tag, fail.index);
      full_context.insert(full_context.end(), partial_context.begin(),
                          partial_context.end());
    }
    std::sort(full_context.begin(), full_context.end(), __cmp__);
    fail.assertion->WriteTo(writer, fail.index, full_context);
  }
  writer.EndArray();

  writer.BeginArray("tests_passed");
  for (IndexedAssertion pass : passed_) {
    Context full_context;
    for (LocalTag tag : pass.assertion->relevant_locals()) {
      Context partial_context = GetLocalSteps(tag, pass.index);
      full_context.insert(full_context.end(), partial_context.begin(),
                          partial_context.end());
    }
    for (GlobalTag tag : pass.assertion->relevant_globals()) {
      Context partial_context = GetGlobalSteps(tag, pass.index);
      full_context.insert(full_context.end(), partial_context.begin(),
                          partial_context.end());
    }
    std::sort(full_context.begin(), full_context.end(), __cmp__);
    pass.assertion->WriteTo(writer, pass.index, full_context);
  }
  writer.EndArray();

  writer.BeginArray("timeline");
  for (const Step *step : timeline_) {
    step->WriteTo(writer);
  }
  writer.EndArray();

  writer.EndObject();
}

template <typename GlobalType>
TestResult TestCase<GlobalType>::Run() {
  return result_;
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::RunTest(void (T::*test_func)(),
                                   const std::string &test_name) {
  test_name_ = test_name;
  std::invoke(test_func, static_cast<T *>(this));
  test_name_ = "";
  result_.IncrementTestCounter();
}

template <typename GlobalType>
void TestCase<GlobalType>::AddGlobal(GlobalTag tag, Global<GlobalType> global) {
  globals_[tag] = global;

  AddValueSet(/*relevant_locals=*/{}, /*relevant_globals=*/{tag},
              /*is_init=*/true, /*is_global=*/true, /*value_name=*/tag,
              /*value=*/global.init_repr);
}

template <typename GlobalType>
void TestCase<GlobalType>::ResetGlobal(GlobalTag tag) {
  Global<GlobalType> *global = &globals_.at(tag);
  *(global->ptr) = global->init_value;

  AddValueSet(/*relevant_locals=*/{}, /*relevant_globals=*/{tag},
              /*is_init=*/false, /*is_global=*/true, /*value_name=*/tag,
              /*value=*/global->init_repr);
}

template <typename GlobalType>
void TestCase<GlobalType>::AddStep(Step *step) {
  result_.AddStep(step);
}

template <typename GlobalType>
void TestCase<GlobalType>::AddFuncCall(
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals, const std::string &repr) {
  auto *func_call =
      new FuncCall(test_name_, relevant_locals, relevant_globals, repr);
  result_.AddStep(func_call);
}

template <typename GlobalType>
void TestCase<GlobalType>::AddValueSet(
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals, bool is_init,
    bool is_global, const std::string &value_name, const std::string &value) {
  auto *value_set = new ValueSet(test_name_, relevant_locals, relevant_globals,
                                 is_init, is_global, value_name, value);
  result_.AddStep(value_set);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertEqual(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 == arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kEqual, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertNotEqual(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 != arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kNotEqual, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertGreater(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 > arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kGreater, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertGreaterEqual(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 >= arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kGreaterEqual, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertLess(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 < arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kLess, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
template <typename T>
void TestCase<GlobalType>::AssertLessEqual(
    T arg0, T arg1, const std::string &repr0, const std::string &repr1,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  bool passed = (arg0 <= arg1);
  if (!passed) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kLessEqual, passed, repr0, repr1);
  result_.AddStep(assertion);
}

template <typename GlobalType>
void TestCase<GlobalType>::AssertTrue(
    bool expression, const std::string &repr,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  if (!expression) result_.IncrementFailCounter();
  auto *assertion = new Assertion(test_name_, relevant_locals, relevant_globals,
                                  /*type=*/kTrue, /*passed=*/expression, repr);
  result_.AddStep(assertion);
}

template <typename GlobalType>
void TestCase<GlobalType>::AssertFalse(
    bool expression, const std::string &repr,
    const std::vector<LocalTag> &relevant_locals,
    const std::vector<GlobalTag> &relevant_globals) {
  if (expression) result_.IncrementFailCounter();
  auto *assertion =
      new Assertion(test_name_, relevant_locals, relevant_globals,
                    /*type=*/kFalse, /*passed=*/!expression, repr);
  result_.AddStep(assertion);
}

}  // namespace rose
