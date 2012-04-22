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

struct TestLife : CppUnit::TestFixture {

  void test_ConwayCell_constructor_alive(){
    ConwayCell myCell = new ConwayCell('*');
    bool myCellAlive = myCell.alive;
    CPPUNIT_ASSERT_EQUALS(true, myCellAlive);
  }
  
  void test_ConwayCell_constructor_dead(){
    ConwayCell myCell = new ConwayCell('.');
    bool myCellAlive = myCell.alive;
    CPPUNIT_ASSERT_EQUALS(false, myCellAlive);
  }
  
  void test_ConwayCell_constructor_3(){
    
    //CPPUNIT_ASSERT_EQUALS();
  }
  void test_FredkinCell_constructor_alive(){
    FredkinCell myCell = new FredkinCell('4');
    bool myCellAlive = myCell.alive;
    CPPUNIT_ASSERT_EQUALS(true, myCellAlive);
  }
  
  void test_FredkinCell_constructor_dead(){
    FredkinCell myCell = new FredkinCell('-');
    bool myCellAlive = myCell.alive;
    CPPUNIT_ASSERT_EQUALS(false, myCellAlive);
  }
  
  void test_FredkinCell_constructor_3(){
    
    //CPPUNIT_ASSERT_EQUALS();
  }
  
  void test_ConwayCell_name_alive(){
    ConwayCell myCell = new ConwayCell('*');
    bool myCellName = myCell.name();
    CPPUNIT_ASSERT_EQUALS('*', myCellName);
  }
  
  void test_ConwayCell_name_dead(){
    ConwayCell myCell = new ConwayCell('.');
    bool myCellName = myCell.name();
    CPPUNIT_ASSERT_EQUALS('.', myCellName);
  }
  
  void test_ConwayCell_name_3(){
    
    //CPPUNIT_ASSERT_EQUALS();
  }
  
  void test_FredkinCell_name_age3(){
    FredkinCell myCell = new FredkinCell('3');
    bool myCellName = myCell.name();
    CPPUNIT_ASSERT_EQUALS('3', myCellName);
  }
  
  void test_FredkinCell_name_dead(){
    FredkinCell myCell = new FredkinCell('-');
    bool myCellName = myCell.name();
    CPPUNIT_ASSERT_EQUALS('-', myCellName);
  }
  
  void test_FredkinCell_name_age14(){
    FredkinCell myCell = new FredkinCell('0');
    myCell.age = 14;
    bool myCellName = myCell.name();
    CPPUNIT_ASSERT_EQUALS('+', myCellName);
  }
  
  void test_ConwayCell_neighbors_1(){
    ConwayCell myCell = new ConwayCell('*');
    unsigned char myCellNeighbors = myCell.neighbors();
    CPPUNIT_ASSERT_EQUALS(0xAA, myCellNeighbors);
  }

  // -----
  // suite
  // -----
  
  CPPUNIT_TEST_SUITE(TestLife);
  
  CPPUNIT_TEST(test_ConwayCell_constructor_alive);
  CPPUNIT_TEST(test_ConwayCell_constructor_dead);
  CPPUNIT_TEST(test_ConwayCell_constructor_3);
  
  CPPUNIT_TEST(test_FredkinCell_constructor_alive);
  CPPUNIT_TEST(test_FredkinCell_constructor_dead);
  CPPUNIT_TEST(test_FredkinCell_constructor_3);
  
  CPPUNIT_TEST(test_ConwayCell_name_alive);
  CPPUNIT_TEST(test_ConwayCell_name_dead);
  CPPUNIT_TEST(test_ConwayCell_name_3);
  
  CPPUNIT_TEST(test_FredkinCell_name_age3);
  CPPUNIT_TEST(test_FredkinCell_name_dead);
  CPPUNIT_TEST(test_FredkinCell_name_age14);
  
  
  
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
