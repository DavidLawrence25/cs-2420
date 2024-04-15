#ifndef CS2420_NOBRAINERS_11GRAPH_TESTCASES_H_
#define CS2420_NOBRAINERS_11GRAPH_TESTCASES_H_

#include <array>
#include <sstream>
#include <string>

#include "custom_libraries/aliases.h"
#include "custom_libraries/unit_test/unit_test.h"
#include "no_brainers/11_graph/edge_table.h"
#include "no_brainers/11_graph/graph.h"

using rose::AdjacencyList, rose::Graph, rose::TestCase, rose::TestResult;

class GraphTest final : public TestCase {
 public:
  GraphTest() : graph_(std::make_unique<AdjacencyList<u32>>()) { Repair(); }
  void Repair() override {
    graph_ = Graph<u32>(std::make_unique<AdjacencyList<u32>>());
    for (u32 vertex : std::array<u32, 10>{9, 2, 1, 7, 5, 4, 8, 3, 6, 0}) {
      graph_.AddVertex(vertex);
    }
    graph_.AddEdge(0, 1);
    graph_.AddEdge(0, 2);
    graph_.AddEdge(0, 3);
    graph_.AddEdge(1, 4);
    graph_.AddEdge(4, 5);
    graph_.AddEdge(5, 6);
    graph_.AddEdge(3, 6);
    graph_.AddEdge(6, 7);
    graph_.AddEdge(2, 7);
    graph_.AddEdge(6, 8);
    graph_.AddEdge(5, 8);
    graph_.AddEdge(5, 9);
    graph_.AddEdge(9, 8);
  }

  void Run() override {
    TestOrder();
    TestIndexOf7();
    Test1AdjacentTo4();
    Test1AdjacentTo0();
    Test0NotAdjacentTo4();
    TestStreamExtraction();
  }

  void TestOrder() { ASSERT_EQUAL(graph_.order(), size_t{10}); }

  void TestIndexOf7() {
    ASSERT_EQUAL(graph_.IndexOf(7).value_or(kU64Max), uindex_t{3});
  }

  void Test1AdjacentTo4() { ASSERT_TRUE(graph_.Adjacent(1, 4)); }
  void Test1AdjacentTo0() { ASSERT_TRUE(graph_.Adjacent(1, 0)); }
  void Test0NotAdjacentTo4() { ASSERT_FALSE(graph_.Adjacent(0, 4)); }

  void TestStreamExtraction() {
    static const std::string expected =
        "9: <8, 1> <5, 1> \n"
        "2: <7, 1> <0, 1> \n"
        "1: <4, 1> <0, 1> \n"
        "7: <2, 1> <6, 1> \n"
        "5: <9, 1> <8, 1> <6, 1> <4, 1> \n"
        "4: <5, 1> <1, 1> \n"
        "8: <9, 1> <5, 1> <6, 1> \n"
        "3: <6, 1> <0, 1> \n"
        "6: <8, 1> <7, 1> <3, 1> <5, 1> \n"
        "0: <3, 1> <2, 1> <1, 1> \n";
    std::stringstream sout;
    sout << graph_;
    ASSERT_EQUAL(sout.str(), expected);
  }

 private:
  Graph<u32> graph_;
};

#endif  // CS2420_NOBRAINERS_11GRAPH_TESTCASES_H_
