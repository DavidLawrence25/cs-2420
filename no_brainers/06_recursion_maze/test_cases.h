#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/06_recursion_maze/maze.h"

using rose::Maze, rose::TestCase, rose::TestResult;

class TrivialMazeTest : public TestCase {
 public:
  TrivialMazeTest() { Repair(); }

  void Repair() override {
    maze_ = Maze(kMazeInitializer_, /*x_start=*/0, /*y_start=*/0,
                 /*x_end=*/0, /*y_end=*/0);
  }

  void Run() override {
    TestStreamExtraction();
    TestSolve();
    TestPrintSuccess();
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << maze_;
    ASSERT_EQUAL(sout.str(), kMazeInitializer_);
  }

  void TestSolve() {
    ASSERT_TRUE(maze_.Solve());
    Repair();
  }

  void TestPrintSuccess() {
    std::stringstream sout;
    maze_.PrintSuccess(sout);
    ASSERT_EQUAL(sout.str(), std::string("Success"));
    Repair();
  }

 private:
  const std::string kMazeInitializer_ = " ";

  Maze maze_;
};

class EasyMazeTest : public TestCase {
 public:
  EasyMazeTest() { Repair(); }

  void Repair() override {
    maze_ = Maze(kMazeInitializer_, /*x_start=*/5, /*y_start=*/0,
                 /*x_end=*/5, /*y_end=*/10);
  }

  void Run() override {
    TestShouldExploreOutOfBounds();
    TestShouldExploreEmpty();
    TestShouldExplorePath();
    TestShouldExploreWall();
    TestStreamExtraction();
    TestSolve();
    TestPrintSuccess();
  }

  void TestShouldExploreOutOfBounds() {
    ASSERT_FALSE(maze_.ShouldExplore(-1, 12));
  }

  void TestShouldExploreEmpty() { ASSERT_TRUE(maze_.ShouldExplore(3, 5)); }

  void TestShouldExplorePath() {
    maze_.Explore(1, 3);
    ASSERT_FALSE(maze_.ShouldExplore(1, 3));
    Repair();
  }

  void TestShouldExploreWall() { ASSERT_FALSE(maze_.ShouldExplore(0, 0)); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << maze_;
    ASSERT_EQUAL(sout.str(), kMazeInitializer_);
  }

  void TestSolve() {
    ASSERT_TRUE(maze_.Solve());
    Repair();
  }

  void TestPrintSuccess() {
    std::stringstream sout;
    maze_.PrintSuccess(sout);
    ASSERT_EQUAL(sout.str(), std::string("Success"));
    Repair();
  }

 private:
  const std::string kMazeInitializer_ =
      "##### #####\n"
      "#     #   #\n"
      "# ### # # #\n"
      "# #     # #\n"
      "### ### # #\n"
      "#     # # #\n"
      "# ##### # #\n"
      "#   #   # #\n"
      "### # ### #\n"
      "#   # #   #\n"
      "##### #####";

  Maze maze_;
};

class GivenMazeTest : public TestCase {
 public:
  GivenMazeTest() { Repair(); }

  void Repair() override {
    maze_ = Maze(kMazeInitializer_, /*x_start=*/0, /*y_start=*/2,
                 /*x_end=*/11, /*y_end=*/4);
  }

  void Run() override {
    TestShouldExploreOutOfBounds();
    TestShouldExploreEmpty();
    TestShouldExplorePath();
    TestShouldExploreWall();
    TestStreamExtraction();
    TestSolve();
    TestPrintSuccess();
  }

  void TestShouldExploreOutOfBounds() {
    ASSERT_FALSE(maze_.ShouldExplore(3, 12));
  }

  void TestShouldExploreEmpty() { ASSERT_TRUE(maze_.ShouldExplore(2, 1)); }

  void TestShouldExplorePath() {
    maze_.Explore(1, 10);
    ASSERT_FALSE(maze_.ShouldExplore(1, 10));
    Repair();
  }

  void TestShouldExploreWall() { ASSERT_FALSE(maze_.ShouldExplore(0, 0)); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << maze_;
    ASSERT_EQUAL(sout.str(), kMazeInitializer_);
  }

  void TestSolve() {
    ASSERT_TRUE(maze_.Solve());
    Repair();
  }

  void TestPrintSuccess() {
    std::stringstream sout;
    maze_.PrintSuccess(sout);
    ASSERT_EQUAL(sout.str(), std::string("Success"));
    Repair();
  }

 private:
  const std::string kMazeInitializer_ =
      "############\n"
      "#   #      #\n"
      "  # # #### #\n"
      "### #    # #\n"
      "#    ### #  \n"
      "#### # # # #\n"
      "#  # # # # #\n"
      "## # # # # #\n"
      "#        # #\n"
      "###### ### #\n"
      "#      #   #\n"
      "############";

  Maze maze_;
};

class HardMazeTest : public TestCase {
 public:
  HardMazeTest() { Repair(); }

  void Repair() override {
    maze_ = Maze(kMazeInitializer_, /*x_start=*/0, /*y_start=*/1,
                 /*x_end=*/30, /*y_end=*/29);
  }

  void Run() override {
    TestShouldExploreOutOfBounds();
    TestShouldExploreEmpty();
    TestShouldExplorePath();
    TestShouldExploreWall();
    TestStreamExtraction();
    TestSolve();
    TestPrintSuccess();
  }

  void TestShouldExploreOutOfBounds() {
    ASSERT_FALSE(maze_.ShouldExplore(31, 0));
  }

  void TestShouldExploreEmpty() { ASSERT_TRUE(maze_.ShouldExplore(0, 1)); }

  void TestShouldExplorePath() {
    maze_.Explore(1, 29);
    ASSERT_FALSE(maze_.ShouldExplore(1, 29));
    Repair();
  }

  void TestShouldExploreWall() { ASSERT_FALSE(maze_.ShouldExplore(30, 30)); }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << maze_;
    ASSERT_EQUAL(sout.str(), kMazeInitializer_);
  }

  void TestSolve() {
    ASSERT_TRUE(maze_.Solve());
    Repair();
  }

  void TestPrintSuccess() {
    std::stringstream sout;
    maze_.PrintSuccess(sout);
    ASSERT_EQUAL(sout.str(), std::string("Success"));
    Repair();
  }

 private:
  const std::string kMazeInitializer_ =
      "###############################\n"
      "    #         #       #       #\n"
      "### # ####### # ####### ### ###\n"
      "#   # #     # #     #   #   # #\n"
      "# ######### # # # # ##### ### #\n"
      "#     #   #   # # #     # # # #\n"
      "### # # ##### # # ####### # # #\n"
      "#   #   #     # # #       # # #\n"
      "# # ### # # ### # # # ##### # #\n"
      "# # # # # #   # #   #     # # #\n"
      "# ### ####### # ### ####### # #\n"
      "#   #         # # #       #   #\n"
      "# ####### ##### # ### ####### #\n"
      "#   #     #         #   #   # #\n"
      "# # # ##### ### ########### # #\n"
      "# # # #       #     #     # # #\n"
      "# # # ####### ####### ##### # #\n"
      "# # #   # # # #       #   # # #\n"
      "# # # ### # # # ### ##### # # #\n"
      "# # #       #   # #           #\n"
      "### ##### ### # # # # ##### # #\n"
      "# #   # # #   # # # # #     # #\n"
      "# # ### # # ### # ##### ### # #\n"
      "#   # #   # # #   #     #   # #\n"
      "### # ### # # # ##### ##### # #\n"
      "#         #   #   # # #   # # #\n"
      "# # # ##### # ##### # ### # # #\n"
      "# # # # #   #     # #   #   # #\n"
      "### # # ### # ### # # ####### #\n"
      "#   #       #   # #         #  \n"
      "###############################";

  Maze maze_;
};

class DonutMazeTest : public TestCase {
 public:
  DonutMazeTest() { Repair(); }

  void Repair() override {
    maze_ = Maze(kMazeInitializer_, /*x_start=*/1, /*y_start=*/1,
                 /*x_end=*/1, /*y_end=*/0);
  }

  void Run() override {
    TestStreamExtraction();
    TestSolve();
    TestPrintSuccess();
  }

  void TestStreamExtraction() {
    std::stringstream sout;
    sout << maze_;
    ASSERT_EQUAL(sout.str(), kMazeInitializer_);
  }

  void TestSolve() {
    ASSERT_FALSE(maze_.Solve());
    Repair();
  }

  void TestPrintSuccess() {
    std::stringstream sout;
    maze_.PrintSuccess(sout);
    ASSERT_EQUAL(sout.str(), std::string("Could not be solved"));
    Repair();
  }

 private:
  const std::string kMazeInitializer_ =
      "###\n"
      "# #\n"
      "###";

  Maze maze_;
};
