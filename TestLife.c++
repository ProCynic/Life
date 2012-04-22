/*
  To test the program:
  % ls /usr/include/cppunit/
  ...
  HelperMacros.h
  ...
  % locate libcppunit.a
  /usr/lib/libcppunit.a
  % g++ -ansi -pedantic -lcppunit -ldl -Wall TestVoting.c++ -o TestVoting.c++.app
  % valgrind TestVoting.c++.app >& TestVoting.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public
#include "Life.h"

// -----------
// TestLife
// -----------

using namespace std;
struct TestLife : CppUnit::TestFixture {

  // ----
  // Life
  // ----

  void test_life_constructor_1x1_dead() {
    istringstream in("1\n1\n.\n");
    Life<ConwayCell> l(in);
    CPPUNIT_ASSERT_EQUAL(1, (int)l.grid.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)l.grid[0].size());
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
  }

  void test_life_constructor_2x2_alive() {
    istringstream in("2\n2\n**\n**\n");
    Life<ConwayCell> l(in);
    CPPUNIT_ASSERT_EQUAL(2, (int)l.grid.size());
    CPPUNIT_ASSERT_EQUAL(2, (int)l.grid[0].size());
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][1].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][1].alive);
    CPPUNIT_ASSERT_EQUAL(4, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
  }

  void test_life_constructor_1x1_fredkin() {
    istringstream in("1\n1\n-\n");
    Life<FredkinCell> l(in);
    CPPUNIT_ASSERT_EQUAL(1, (int)l.grid.size());
    CPPUNIT_ASSERT_EQUAL(1, (int)l.grid[0].size());
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.grid[0][0].age);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
  }

  void test_life_simulate_1x1() {
    istringstream in("1\n1\n*\n");
    Life<ConwayCell> l(in);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(1, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    l.simulate(500);
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(500, l.generation);
  }

  void test_life_simulate_2x2() {
    istringstream in("2\n2\n**\n**\n");
    Life<ConwayCell> l(in);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][1].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][1].alive);
    CPPUNIT_ASSERT_EQUAL(4, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    l.simulate(500);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][1].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[1][1].alive);
    CPPUNIT_ASSERT_EQUAL(4, l.population);
    CPPUNIT_ASSERT_EQUAL(500, l.generation);
  }

  void test_life_simulate_flipper() {
    istringstream in("3\n3\n.*.\n.*.\n.*.\n");
    Life<ConwayCell> l(in);
    const bool expected1[3][3] = {{false, true, false}, {false, true, false}, {false, true, false}};
    const bool expected2[3][3] = {{false, false, false}, {true, true, true}, {false, false, false}};
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        CPPUNIT_ASSERT_EQUAL(expected1[r][c], l.grid[r][c].alive);
    CPPUNIT_ASSERT_EQUAL(3, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    l.simulate(333);
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        CPPUNIT_ASSERT_EQUAL(expected2[r][c], l.grid[r][c].alive);
    CPPUNIT_ASSERT_EQUAL(3, l.population);
    CPPUNIT_ASSERT_EQUAL(333, l.generation);
  }


  // -----
  // suite
  // -----
  
  CPPUNIT_TEST_SUITE(TestLife);
  CPPUNIT_TEST(test_life_constructor_1x1_dead);
  CPPUNIT_TEST(test_life_constructor_2x2_alive);
  CPPUNIT_TEST(test_life_constructor_1x1_fredkin);
  CPPUNIT_TEST(test_life_simulate_1x1);
  CPPUNIT_TEST(test_life_simulate_2x2);
  CPPUNIT_TEST(test_life_simulate_flipper);
  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
  cout << "TestLife.c++" << endl;
  
  CppUnit::TextTestRunner tr;
  tr.addTest(TestLife::suite());
  tr.run();
  
  cout << "Done." << endl;
  return 0;
}
