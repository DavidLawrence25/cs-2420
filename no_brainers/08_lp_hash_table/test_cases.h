#include <stdlib.h>

#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/08_lp_hash_table/hash_table.h"
#include "no_brainers/08_lp_hash_table/out_of_space_error.h"

using rose::Assertion, rose::TestCase, rose::TestResult;
using rose::HashTable, rose::OutOfSpaceError;

class HashTableConstructorTest : public TestCase {
 public:
  HashTableConstructorTest() { Repair(); }
  void Repair() override {
    table0_ = HashTable<int>();
    table1_ = HashTable<int>(13);
  }

  void Run() override {
    TestDefaultSize();
    TestDefaultCapacity();
    TestDefaultEmpty();
    TestExplicitCapacitySize();
    TestExplicitCapacity();
    TestExplicitCapacityEmpty();
  }

  void TestDefaultSize() { ASSERT_EQUAL(table0_.size(), size_t{0}); }
  void TestDefaultCapacity() { ASSERT_EQUAL(table0_.capacity(), size_t{17}); }
  void TestDefaultEmpty() { ASSERT_TRUE(table0_.empty()); }

  void TestExplicitCapacitySize() { ASSERT_EQUAL(table1_.size(), size_t{0}); }
  void TestExplicitCapacity() { ASSERT_EQUAL(table1_.capacity(), size_t{13}); }
  void TestExplicitCapacityEmpty() { ASSERT_TRUE(table1_.empty()); }

 private:
  HashTable<int> table0_;
  HashTable<int> table1_;
};

class HashTableInsertTest : public TestCase {
 public:
  void Repair() override { table_ = HashTable<int>(); }
  void Run() override {
    table_.Insert(2);
    TestStage1Size();
    TestStage1Contains2();
    TestStage1DoesntContain12();
    TestStage1NotEmpty();
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
  void TestStage1NotEmpty() { ASSERT_FALSE(table_.empty()); }

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
  HashTableErrorTest() { Repair(); }

  void Repair() override {
    table0_ = HashTable<int>();
    for (int x = 0; x < 16; ++x) table0_.Insert(x);
    table1_ = HashTable<int>(7);
    for (int x = 0; x < 6; ++x) table1_.Insert(x);
  }

  void Run() override {
    TestDefaultCapacityFilled();
    TestDefaultCapacityOverfilled();
    TestExplicitCapacityFilled();
    TestExplicitCapacityOverfilled();
  }

  void TestDefaultCapacityFilled() {
    ASSERT_DOESNT_THROW(table0_.Insert(16));
    Repair();
  }

  void TestDefaultCapacityOverfilled() {
    table0_.Insert(16);
    ASSERT_THROWS_AS(OutOfSpaceError, table0_.Insert(17));
    Repair();
  }

  void TestExplicitCapacityFilled() {
    ASSERT_DOESNT_THROW(table1_.Insert(6));
    Repair();
  }

  void TestExplicitCapacityOverfilled() {
    table1_.Insert(6);
    ASSERT_THROWS_AS(OutOfSpaceError, table1_.Insert(7));
    Repair();
  }

 private:
  HashTable<int> table0_;
  HashTable<int> table1_;
};
