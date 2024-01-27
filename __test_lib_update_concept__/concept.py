from __future__ import annotations
from dataclasses import dataclass, field
from enum import Enum, auto
from typing import Any, Callable, NamedTuple


VoidPtr = Any
LocalTag = str
GlobalTag = str


class StepType(Enum):
    ASSERTION = auto()
    FUNC_CALL = auto()
    LOCAL_INIT = auto()
    LOCAL_SET = auto()
    GLOBAL_INIT = auto()
    GLOBAL_SET = auto()


class AssertionType(Enum):
    EQUAL = auto()
    NOT_EQUAL = auto()
    GREATER = auto()
    GREATER_EQUAL = auto()
    LESS = auto()
    LESS_EQUAL = auto()
    TRUE = auto()
    FALSE = auto()


@dataclass
class Step:
    parent_func: str
    relevant_locals: list[LocalTag]
    relevant_globals: list[GlobalTag]


class IndexedStep(NamedTuple):
    index: int
    step: Step


@dataclass
class Assertion(Step):
    tp: AssertionType
    passed: bool
    repr0: str
    repr1: str | None = None


@dataclass
class FuncCall(Step):
    repr: str


@dataclass
class ValueSet(Step):
    is_init: bool
    is_global: bool
    value_name: str
    value: str


@dataclass
class TestResult:
    timeline: list[Step] = field(default_factory=list)
    tests_ran: int = 0
    most_recent_global_set: dict[GlobalTag, int] = field(default_factory=dict)

    def add_step(self, step: Step) -> None:
        if isinstance(step, ValueSet) and step.is_global:
            self.most_recent_global_set[step.value_name] = len(self.timeline)
        self.timeline.append(step)

    def get_local_steps(self, tag: LocalTag, before: int) -> list[IndexedStep]:
        steps: list[IndexedStep] = []
        for i, step in enumerate(self.timeline[:before]):
            if tag in step.relevant_locals:
                steps.append(IndexedStep(i, step))
        return steps

    def get_global_steps(self, tag: GlobalTag, before: int) -> list[IndexedStep]:
        steps: list[IndexedStep] = []
        start: int = self.most_recent_global_set[tag]
        for i, step in enumerate(self.timeline[start:before]):
            if tag in step.relevant_globals:
                steps.append(IndexedStep(i, step))
        return steps

    def increment_test_counter(self) -> None:
        self.tests_ran += 1

    def report(self) -> None:
        ...

    def log_txt(self, file_name: str) -> None:
        ...

    def log_json(self, file_name: str) -> None:
        ...


@dataclass
class TestCase:
    result: TestResult = field(default_factory=TestResult)
    global_ptrs: dict[GlobalTag, VoidPtr] = field(default_factory=dict)
    global_inits: dict[GlobalTag, Any] = field(default_factory=dict)
    _test_name: str = "__TestCaseConstructor__"

    def run(self) -> TestResult:
        return self.result

    def run_test(self, func: Callable[[], None], name: str) -> None:
        self._test_name = name
        func()
        self._test_name = ""
        self.result.increment_test_counter()

    def reset_global(self, tag: GlobalTag) -> None:
        self.global_ptrs[tag] = self.global_inits[tag]

    def assert_equal[T](self, /, arg0: T, arg1: T, *, repr0: str, repr1: str,
                        relevant_locals: list[LocalTag],
                        relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.EQUAL,
            passed=(arg0 == arg1),
            repr0=repr0,
            repr1=repr1
        ))

    def assert_not_equal[T](self, /, arg0: T, arg1: T, *, repr0: str,
                            repr1: str, relevant_locals: list[LocalTag],
                            relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.NOT_EQUAL,
            passed=(arg0 != arg1),
            repr0=repr0,
            repr1=repr1
        ))

    def assert_greater[T](self, /, arg0: T, arg1: T, *, repr0: str, repr1: str,
                          relevant_locals: list[LocalTag],
                          relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.GREATER,
            passed=(arg0 > arg1),  # type: ignore
            repr0=repr0,
            repr1=repr1
        ))

    def assert_greater_equal[T](self, /, arg0: T, arg1: T, *, repr0: str,
                                repr1: str, relevant_locals: list[LocalTag],
                                relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.GREATER_EQUAL,
            passed=(arg0 >= arg1),  # type: ignore
            repr0=repr0,
            repr1=repr1
        ))

    def assert_less[T](self, /, arg0: T, arg1: T, *, repr0: str, repr1: str,
                       relevant_locals: list[LocalTag],
                       relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.LESS,
            passed=(arg0 < arg1),  # type: ignore
            repr0=repr0,
            repr1=repr1
        ))

    def assert_less_equal[T](self, /, arg0: T, arg1: T, *, repr0: str,
                             repr1: str, relevant_locals: list[LocalTag],
                             relevant_globals: list[LocalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.LESS_EQUAL,
            passed=(arg0 <= arg1),  # type: ignore
            repr0=repr0,
            repr1=repr1
        ))

    def assert_true(self, /, expression: bool, *, repr: str,
                    relevant_locals: list[LocalTag],
                    relevant_globals: list[GlobalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.TRUE,
            passed=expression,
            repr0=repr
        ))

    def assert_false(self, /, expression: bool, *, repr: str,
                     relevant_locals: list[LocalTag],
                     relevant_globals: list[GlobalTag]) -> None:
        self.result.add_step(Assertion(
            parent_func=self._test_name,
            relevant_locals=relevant_locals,
            relevant_globals=relevant_globals,
            tp=AssertionType.FALSE,
            passed=(not expression),
            repr0=repr
        ))

# def main() -> None:
#     test_test = TestCase()
#     test_test.run().log_json("test_test_log")
