#include <stdlib.h>

#include "custom_libraries/number_utils.h"
#include "custom_libraries/unit_test/unit_test.h"
#include "labs/08_dynamic_hash_table/hash_table.h"

using rose::Assertion, rose::HashTable, rose::TestCase, rose::TestResult;

class HashTableConstructorTest : public TestCase {
 public:
  HashTableConstructorTest() { Repair(); }
  void Repair() override {
    table0_ = HashTable<int>();
    table1_ = HashTable<int>(13);
    table2_ = HashTable<int>(19, 0.5);
  }

  void Run() override {
    TestDefaultSize();
    TestDefaultCapacity();
    TestDefaultEmpty();
    TestDefaultLFT();
    TestExplicitCapacitySize();
    TestExplicitCapacity();
    TestExplicitCapacityEmpty();
    TestExplicitCapacityLFT();
    TestAllExplicitSize();
    TestAllExplicitCapacity();
    TestAllExplicitEmpty();
    TestAllExplicitLFT();
  }

  void TestDefaultSize() { ASSERT_EQUAL(table0_.size(), size_t{0}); }
  void TestDefaultCapacity() { ASSERT_EQUAL(table0_.capacity(), size_t{17}); }
  void TestDefaultEmpty() { ASSERT_TRUE(table0_.empty()); }
  void TestDefaultLFT() { ASSERT_EQUAL(table0_.load_factor_threshold(), 0.65); }

  void TestExplicitCapacitySize() { ASSERT_EQUAL(table1_.size(), size_t{0}); }
  void TestExplicitCapacity() { ASSERT_EQUAL(table1_.capacity(), size_t{13}); }
  void TestExplicitCapacityEmpty() { ASSERT_TRUE(table1_.empty()); }
  void TestExplicitCapacityLFT() {
    ASSERT_EQUAL(table1_.load_factor_threshold(), 0.65);
  }

  void TestAllExplicitSize() { ASSERT_EQUAL(table2_.size(), size_t{0}); }
  void TestAllExplicitCapacity() {
    ASSERT_EQUAL(table2_.capacity(), size_t{19});
  }
  void TestAllExplicitEmpty() { ASSERT_TRUE(table2_.empty()); }
  void TestAllExplicitLFT() {
    ASSERT_EQUAL(table2_.load_factor_threshold(), 0.5);
  }

 private:
  HashTable<int> table0_;
  HashTable<int> table1_;
  HashTable<int> table2_;
};

class HashTableInsertTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(2);
    TestStage1Size();
    TestStage1Contains2();
    TestStage1DoesntContain12();
    TestStage1IsntEmpty();
    table_.Insert(5);
    TestStage2Size();
    TestStage2Contains5();
    table_.Insert(64);
    TestStage3Size();
    TestStage3Contains64();
    TestStage3DoesntContain13();
    table_.Insert(13);
    TestStage4Contains13();
    TestStage4Contains64();
    table_.Insert(30);
    TestStage5Contains30();
    table_.Insert(47);
    TestStage6Contains47();
    TestStage6Contains13();
    TestStage6Contains64();
    Repair();
  }

  void TestStage1Size() { ASSERT_EQUAL(table_.size(), size_t{1}); }
  void TestStage1Contains2() { ASSERT_TRUE(table_.Contains(2)); }
  void TestStage1DoesntContain12() { ASSERT_FALSE(table_.Contains(12)); }
  void TestStage1IsntEmpty() { ASSERT_FALSE(table_.empty()); }

  void TestStage2Size() { ASSERT_EQUAL(table_.size(), size_t{2}); }
  void TestStage2Contains5() { ASSERT_TRUE(table_.Contains(5)); }

  void TestStage3Size() { ASSERT_EQUAL(table_.size(), size_t{3}); }
  void TestStage3Contains64() { ASSERT_TRUE(table_.Contains(64)); }
  void TestStage3DoesntContain13() { ASSERT_FALSE(table_.Contains(13)); }

  void TestStage4Contains13() { ASSERT_TRUE(table_.Contains(13)); }
  void TestStage4Contains64() { ASSERT_TRUE(table_.Contains(64)); }

  void TestStage5Contains30() { ASSERT_TRUE(table_.Contains(30)); }

  void TestStage6Contains47() { ASSERT_TRUE(table_.Contains(47)); }
  void TestStage6Contains13() { ASSERT_TRUE(table_.Contains(13)); }
  void TestStage6Contains64() { ASSERT_TRUE(table_.Contains(64)); }

 private:
  HashTable<int> table_;
};

class HashTableRemoveTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(3);
    table_.Remove(3);
    TestStage1Size();
    TestStage1Empty();
    TestStage1DoesntContain3();
    table_.Insert(6);
    table_.Insert(1);
    table_.Insert(20);
    TestStage2Contains6();
    TestStage2Contains1();
    TestStage2Contains20();
    table_.Remove(6);
    table_.Remove(1);
    table_.Remove(20);
    TestStage3DoesntContain6();
    TestStage3DoesntContain1();
    TestStage3DoesntContain20();
    TestStage3Size();
    TestStage3Empty();
    table_.Insert(4);
    table_.Insert(21);
    table_.Insert(38);
    table_.Insert(55);
    table_.Remove(21);
    TestStage4Contains4();
    TestStage4Contains38();
    TestStage4Contains55();
    TestStage4DoesntContain21();
    Repair();
  }

  void TestStage1Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage1Empty() { ASSERT_TRUE(table_.empty()); }
  void TestStage1DoesntContain3() { ASSERT_FALSE(table_.Contains(3)); }

  void TestStage2Contains6() { ASSERT_TRUE(table_.Contains(6)); }
  void TestStage2Contains1() { ASSERT_TRUE(table_.Contains(1)); }
  void TestStage2Contains20() { ASSERT_TRUE(table_.Contains(20)); }

  void TestStage3DoesntContain6() { ASSERT_FALSE(table_.Contains(6)); }
  void TestStage3DoesntContain1() { ASSERT_FALSE(table_.Contains(1)); }
  void TestStage3DoesntContain20() { ASSERT_FALSE(table_.Contains(20)); }
  void TestStage3Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage3Empty() { ASSERT_TRUE(table_.empty()); }

  void TestStage4Contains4() { ASSERT_TRUE(table_.Contains(4)); }
  void TestStage4Contains38() { ASSERT_TRUE(table_.Contains(38)); }
  void TestStage4Contains55() { ASSERT_TRUE(table_.Contains(55)); }
  void TestStage4DoesntContain21() { ASSERT_FALSE(table_.Contains(21)); }

 private:
  HashTable<int> table_;
};

class HashTableClearTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(5);
    table_.Clear();
    TestStage1Size();
    TestStage1Empty();
    table_.Insert(374);
    table_.Insert(234);
    table_.Clear();
    TestStage2Size();
    TestStage2Empty();
    table_.Insert(4);
    table_.Insert(374);
    table_.Remove(374);
    table_.Clear();
    TestStage3Size();
    TestStage3Empty();
    TestStage3DoesntContain4();
    TestStage3DoesntContain5();
    TestStage3DoesntContain374();
    Repair();
  }

  void TestStage1Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage1Empty() { ASSERT_TRUE(table_.empty()); }

  void TestStage2Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage2Empty() { ASSERT_TRUE(table_.empty()); }

  void TestStage3Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage3Empty() { ASSERT_TRUE(table_.empty()); }
  void TestStage3DoesntContain4() { ASSERT_FALSE(table_.Contains(4)); }
  void TestStage3DoesntContain5() { ASSERT_FALSE(table_.Contains(5)); }
  void TestStage3DoesntContain374() { ASSERT_FALSE(table_.Contains(374)); }

 private:
  HashTable<int> table_;
};

class HashTableResizeTest : public TestCase {
 public:
  HashTableResizeTest() { Repair(); }
  void Repair() override {
    table0_ = HashTable<int>(7);
    table1_ = HashTable<int>(7, 0.5);
  }

  void Run() override {
    table0_.Insert(5);
    table0_.Insert(15);
    table0_.Insert(23);
    table0_.Insert(34);
    TestStage1Capacity();
    table0_.Insert(18);
    TestStage2Capacity();
    TestStage2IndexOf5();
    TestStage2IndexOf15();
    TestStage2IndexOf34();
    TestStage2IndexOf18();
    for (int x = 50; x < 60; ++x) table0_.Insert(x);
    TestStage3Capacity();
    TestStage3Contains50();
    TestStage3Contains51();
    TestStage3Contains52();
    TestStage3Contains53();
    TestStage3Contains54();
    TestStage3Contains55();
    TestStage3Contains56();
    TestStage3Contains57();
    TestStage3Contains58();
    TestStage3Contains59();
    for (int x = 150; x < 170; ++x) table0_.Insert(x);
    TestStage4Capacity();
    TestStage4Contains150();
    TestStage4Contains151();
    TestStage4Contains152();
    TestStage4Contains153();
    TestStage4Contains154();
    TestStage4Contains155();
    TestStage4Contains156();
    TestStage4Contains157();
    TestStage4Contains158();
    TestStage4Contains159();
    TestStage4Contains160();
    TestStage4Contains161();
    TestStage4Contains162();
    TestStage4Contains163();
    TestStage4Contains164();
    TestStage4Contains165();
    TestStage4Contains166();
    TestStage4Contains167();
    TestStage4Contains168();
    TestStage4Contains169();
    table1_.Insert(5);
    table1_.Insert(15);
    table1_.Insert(23);
    TestStage5Capacity();
    table1_.Insert(34);
    TestStage6Capacity();
    Repair();
  }

  void TestStage1Capacity() { ASSERT_EQUAL(table0_.capacity(), size_t{7}); }

  void TestStage2Capacity() { ASSERT_EQUAL(table0_.capacity(), size_t{17}); }
  void TestStage2IndexOf5() { ASSERT_EQUAL(table0_.Index(5).value_or(-1), 5); }
  void TestStage2IndexOf15() {
    ASSERT_EQUAL(table0_.Index(15).value_or(-1), 15);
  }
  void TestStage2IndexOf34() {
    ASSERT_EQUAL(table0_.Index(34).value_or(-1), 0);
  }
  void TestStage2IndexOf18() {
    ASSERT_EQUAL(table0_.Index(18).value_or(-1), 1);
  }

  void TestStage3Capacity() { ASSERT_EQUAL(table0_.capacity(), size_t{37}); }
  void TestStage3Contains50() { ASSERT_TRUE(table0_.Contains(50)); }
  void TestStage3Contains51() { ASSERT_TRUE(table0_.Contains(51)); }
  void TestStage3Contains52() { ASSERT_TRUE(table0_.Contains(52)); }
  void TestStage3Contains53() { ASSERT_TRUE(table0_.Contains(53)); }
  void TestStage3Contains54() { ASSERT_TRUE(table0_.Contains(54)); }
  void TestStage3Contains55() { ASSERT_TRUE(table0_.Contains(55)); }
  void TestStage3Contains56() { ASSERT_TRUE(table0_.Contains(56)); }
  void TestStage3Contains57() { ASSERT_TRUE(table0_.Contains(57)); }
  void TestStage3Contains58() { ASSERT_TRUE(table0_.Contains(58)); }
  void TestStage3Contains59() { ASSERT_TRUE(table0_.Contains(59)); }

  void TestStage4Capacity() { ASSERT_EQUAL(table0_.capacity(), size_t{79}); }
  void TestStage4Contains150() { ASSERT_TRUE(table0_.Contains(150)); }
  void TestStage4Contains151() { ASSERT_TRUE(table0_.Contains(151)); }
  void TestStage4Contains152() { ASSERT_TRUE(table0_.Contains(152)); }
  void TestStage4Contains153() { ASSERT_TRUE(table0_.Contains(153)); }
  void TestStage4Contains154() { ASSERT_TRUE(table0_.Contains(154)); }
  void TestStage4Contains155() { ASSERT_TRUE(table0_.Contains(155)); }
  void TestStage4Contains156() { ASSERT_TRUE(table0_.Contains(156)); }
  void TestStage4Contains157() { ASSERT_TRUE(table0_.Contains(157)); }
  void TestStage4Contains158() { ASSERT_TRUE(table0_.Contains(158)); }
  void TestStage4Contains159() { ASSERT_TRUE(table0_.Contains(159)); }
  void TestStage4Contains160() { ASSERT_TRUE(table0_.Contains(160)); }
  void TestStage4Contains161() { ASSERT_TRUE(table0_.Contains(161)); }
  void TestStage4Contains162() { ASSERT_TRUE(table0_.Contains(162)); }
  void TestStage4Contains163() { ASSERT_TRUE(table0_.Contains(163)); }
  void TestStage4Contains164() { ASSERT_TRUE(table0_.Contains(164)); }
  void TestStage4Contains165() { ASSERT_TRUE(table0_.Contains(165)); }
  void TestStage4Contains166() { ASSERT_TRUE(table0_.Contains(166)); }
  void TestStage4Contains167() { ASSERT_TRUE(table0_.Contains(167)); }
  void TestStage4Contains168() { ASSERT_TRUE(table0_.Contains(168)); }
  void TestStage4Contains169() { ASSERT_TRUE(table0_.Contains(169)); }

  void TestStage5Capacity() { ASSERT_EQUAL(table1_.capacity(), size_t{7}); }

  void TestStage6Capacity() { ASSERT_EQUAL(table1_.capacity(), size_t{17}); }

 private:
  HashTable<int> table0_;
  HashTable<int> table1_;
};

class HashTableIndexTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(5);
    TestStage1IndexOf5();
    TestStage1IndexOf3();
    table_.Insert(18);
    TestStage2IndexOf18();
    table_.Insert(1);
    TestStage3IndexOf1();
    Repair();
  }

  void TestStage1IndexOf5() { ASSERT_EQUAL(table_.Index(5).value_or(-1), 5); }
  void TestStage1IndexOf3() { ASSERT_FALSE(table_.Index(3).has_value()); }

  void TestStage2IndexOf18() { ASSERT_EQUAL(table_.Index(18).value_or(-1), 1); }

  void TestStage3IndexOf1() { ASSERT_EQUAL(table_.Index(1).value_or(-1), 2); }

 private:
  HashTable<int> table_;
};

class HashTableQuadProbeTest : public TestCase {
 public:
  HashTableQuadProbeTest() { Repair(); }
  void Repair() override {
    table_ = HashTable<double>();
    table_.Insert(4);   // 4 + 0**2
    table_.Insert(21);  // 4 + 1**2
    table_.Insert(38);  // 4 + 2**2
    table_.Insert(55);  // 4 + 3**2
    table_.Insert(72);  // 4 + 4**2
  }

  void Run() override {
    TestIndexOf4();
    TestIndexOf21();
    TestIndexOf38();
    TestIndexOf55();
    TestIndexOf72();
  }

  void TestIndexOf4() { ASSERT_EQUAL(table_.Index(4).value_or(-1), 4); }
  void TestIndexOf21() { ASSERT_EQUAL(table_.Index(21).value_or(-1), 5); }
  void TestIndexOf38() { ASSERT_EQUAL(table_.Index(38).value_or(-1), 8); }
  void TestIndexOf55() { ASSERT_EQUAL(table_.Index(55).value_or(-1), 13); }
  void TestIndexOf72() { ASSERT_EQUAL(table_.Index(72).value_or(-1), 3); }

 private:
  // Not sure why this is a table of f64's when
  // we only write integer values, but okay.
  HashTable<double> table_;
};

class HashTableDeepCopyTest : public TestCase {
 public:
  HashTableDeepCopyTest() { Repair(); }

  void Repair() override { Repair(/*stage=*/0); }
  void Repair(int stage) {
    table_ = HashTable<int>();
    copy_ = std::make_unique<HashTable<int>>();
    if (stage < 1) return;
    table_.Insert(12);
    table_.Insert(2);
    table_.Insert(15);
    copy_ = std::make_unique<HashTable<int>>(table_);
    if (stage == 1) return;
    table_.Insert(8);
    if (stage == 2) return;
    table_.Insert(18);
    *copy_ = table_;
    if (stage == 3) return;
    copy_->Remove(18);
  }

  void Run() override {
    Repair(/*stage=*/1);
    TestStage1OriginalSize();
    TestStage1DeepCopySize();
    TestStage1DeepCopyContains12();
    Repair(/*stage=*/2);
    TestStage2DeepCopyDoesntContain8();
    Repair(/*stage=*/3);
    TestStage3DeepCopyContains18();
    TestStage3OriginalSize();
    TestStage3DeepCopySize();
    Repair(/*stage=*/4);
    TestStage4OriginalContains18();
    Repair();
  }

  void TestStage1OriginalSize() { ASSERT_EQUAL(table_.size(), size_t{3}); }
  void TestStage1DeepCopySize() { ASSERT_EQUAL(copy_->size(), size_t{3}); }
  void TestStage1DeepCopyContains12() { ASSERT_TRUE(copy_->Contains(12)); }

  void TestStage2DeepCopyDoesntContain8() { ASSERT_FALSE(copy_->Contains(8)); }

  void TestStage3DeepCopyContains18() { ASSERT_TRUE(copy_->Contains(18)); }
  void TestStage3OriginalSize() { ASSERT_EQUAL(table_.size(), size_t{5}); }
  void TestStage3DeepCopySize() { ASSERT_EQUAL(copy_->size(), size_t{5}); }

  void TestStage4OriginalContains18() { ASSERT_TRUE(table_.Contains(18)); }

 private:
  HashTable<int> table_;
  std::unique_ptr<HashTable<int>> copy_;
};

class HashTableErrorTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(9);
    TestStage1NoErrorOnRemove();
    TestStage1Size();
    TestStage1IsntEmpty();
    TestStage2NoErrorOnRemove();
    TestStage2Contains9();
    TestStage2Size();
    table_.Clear();
    TestStage3NoErrorOnClear();
    TestStage3NoErrorOnRemove();
    TestStage3Size();
    TestStage3Empty();
    Repair();
  }

  void TestStage1NoErrorOnRemove() { ASSERT_DOESNT_THROW(table_.Remove(8)); }
  void TestStage1Size() { ASSERT_EQUAL(table_.size(), size_t{1}); }
  void TestStage1IsntEmpty() { ASSERT_FALSE(table_.empty()); }

  void TestStage2NoErrorOnRemove() { ASSERT_DOESNT_THROW(table_.Remove(26)); }
  void TestStage2Contains9() { ASSERT_TRUE(table_.Contains(9)); }
  void TestStage2Size() { ASSERT_EQUAL(table_.size(), size_t{1}); }

  void TestStage3NoErrorOnClear() { ASSERT_DOESNT_THROW(table_.Clear()); }
  void TestStage3NoErrorOnRemove() { ASSERT_DOESNT_THROW(table_.Remove(15)); }
  void TestStage3Size() { ASSERT_EQUAL(table_.size(), size_t{0}); }
  void TestStage3Empty() { ASSERT_TRUE(table_.empty()); }

 private:
  HashTable<int> table_;
};

class PrimeFunctionsTest : public TestCase {
 public:
  void Repair() override {}  // Intentionally unused.
  void Run() override {
    Test349IsPrime();
    Test343IsntPrime();
    Test5IsPrime();
    Test2017IsPrime();
    Test993IsntPrime();
    Test101IsPrime();
    Test93NextPrime();
    Test102NextPrime();
    Test984NextPrime();
    Test258NextPrime();
  }

  void Test349IsPrime() { ASSERT_TRUE(rose::IsPrime(349)); }
  void Test343IsntPrime() { ASSERT_FALSE(rose::IsPrime(343)); }
  void Test5IsPrime() { ASSERT_TRUE(rose::IsPrime(5)); }
  void Test2017IsPrime() { ASSERT_TRUE(rose::IsPrime(2017)); }
  void Test993IsntPrime() { ASSERT_FALSE(rose::IsPrime(993)); }
  void Test101IsPrime() { ASSERT_TRUE(rose::IsPrime(101)); }

  void Test93NextPrime() { ASSERT_EQUAL(rose::NextPrime(93), 97); }
  void Test102NextPrime() { ASSERT_EQUAL(rose::NextPrime(102), 103); }
  void Test984NextPrime() { ASSERT_EQUAL(rose::NextPrime(984), 991); }
  void Test258NextPrime() { ASSERT_EQUAL(rose::NextPrime(258), 263); }
};
