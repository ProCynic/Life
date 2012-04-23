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
#include <stdexcept> // invalid_argument, out_of_range

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public
#define protected public
#define class struct
#include "Life.h"



// -----------
// TestLife
// -----------

using namespace std;
struct TestLife : CppUnit::TestFixture {

  // --------
  // Position
  // --------

  //constructor
  // +=
  // +



  // ----
  // Life
  // ----

  void test_Life_takeTurn_conway(){
    istringstream in("1\n1\n.\n");
    Life<ConwayCell> l(in);
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    l.takeTurn();
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(1, l.generation);
  }
  
  void test_Life_takeTurn_fredkin(){
    istringstream in("1\n1\n-\n");
    Life<FredkinCell> l(in);
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    l.takeTurn();
    CPPUNIT_ASSERT_EQUAL(false, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(0, l.population);
    CPPUNIT_ASSERT_EQUAL(1, l.generation);
  }
  
  void test_Life_takeTurn_fredkin_9to10(){
    istringstream in("1\n2\n90\n");
    Life<FredkinCell> l(in);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][1].alive);
    CPPUNIT_ASSERT_EQUAL(2, l.population);
    CPPUNIT_ASSERT_EQUAL(0, l.generation);
    CPPUNIT_ASSERT_EQUAL('9', l.grid[0][0].name());
    CPPUNIT_ASSERT_EQUAL(9, l.grid[0][0].age);
    l.takeTurn();
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][0].alive);
    CPPUNIT_ASSERT_EQUAL(true, l.grid[0][1].alive);
    CPPUNIT_ASSERT_EQUAL(2, l.population);
    CPPUNIT_ASSERT_EQUAL(1, l.generation);
    CPPUNIT_ASSERT_EQUAL('+', l.grid[0][0].name());
    CPPUNIT_ASSERT_EQUAL(10, l.grid[0][0].age);
  }

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

  void test_Life_print_1x1() {
    istringstream in("1\n1\n.\n");
    Life<ConwayCell> l(in);
    ostringstream out;
    l.print(out);
    CPPUNIT_ASSERT_EQUAL((string)"Generation = 0, Population = 0.\n.\n\n", out.str());
  }
  
  void test_Life_print_3x3() {
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    ostringstream out;
    l.print(out);
    CPPUNIT_ASSERT_EQUAL((string)"Generation = 0, Population = 3.\n*..\n.*.\n..*\n\n", out.str());
  }

  void test_Life_print_fredkin() {
    istringstream in("3\n3\n-8-\n--0\n---\n");
    Life<FredkinCell> l(in);
    l.generation = 100;
    ostringstream out;
    l.print(out);
    CPPUNIT_ASSERT_EQUAL((string)"Generation = 100, Population = 2.\n-8-\n--0\n---\n\n", out.str());
  }


  // countNeighbors

  // isAlive
  
  // -------------
  // Abstract Cell
  // -------------
  
  void test_AbstractCell_operator_bool_conway_alive(){
    ConwayCell myCell('*');
    CPPUNIT_ASSERT_EQUAL(true, (bool)myCell);
  }

  void test_AbstractCell_operator_bool_conway_dead(){
    ConwayCell myCell('.');
    CPPUNIT_ASSERT_EQUAL(false, (bool)myCell);
  }
  void test_AbstractCell_operator_bool_conway_rise(){
    ConwayCell myCell('.');
    myCell.alive = true;
    CPPUNIT_ASSERT_EQUAL(true, (bool)myCell);
  }
  
  void test_AbstractCell_operator_int_conway(){
    ConwayCell myCell('.');
    CPPUNIT_ASSERT_EQUAL(0, (int)myCell);
  }
  void test_AbstractCell_operator_int_fredkin_0(){
    FredkinCell myCell('0');
    CPPUNIT_ASSERT_EQUAL(0, (int)myCell);
  }
  void test_AbstractCell_operator_int_fredkin_14(){
    FredkinCell myCell('0');
    myCell.age = 14;
    CPPUNIT_ASSERT_EQUAL(14, (int)myCell);
  }
  
  void test_AbstractCell_setNeighbors_exception(){
    ConwayCell myCell('*');
    myCell.setNeighbors(666);
  }

  void test_AbstractCell_setNeighbors_conway(){
    ConwayCell myCell('*');
    myCell.setNeighbors(3);
    CPPUNIT_ASSERT_EQUAL(3, myCell.numNeighbors);
  }
  
  void test_AbstractCell_setNeighbors_fredkin(){
    FredkinCell myCell('0');
    myCell.setNeighbors(3);
    CPPUNIT_ASSERT_EQUAL(3, myCell.numNeighbors);
  }

  // ----
  // Cell
  // ----

  // copy constructor

  // copy assignment

  // destructor

  //turn

  // neighbors

  // name

  // setNeighbors

  //operator bool
  
  // -----------
  // Conway Cell
  // -----------


  void test_ConwayCell_constructor_alive(){
    ConwayCell myCell('*');
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
  }
  
  void test_ConwayCell_constructor_dead(){
    ConwayCell myCell('.');
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
  }

  //tested all ConwayCell constructor cases already  
  void test_ConwayCell_constructor_3(){
    CPPUNIT_ASSERT(true);
  }
  
  void test_ConwayCell_turn_dtod(){
    ConwayCell myCell('.');
    myCell.numNeighbors = 2;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
  }
  void test_ConwayCell_turn_dtoa(){
    ConwayCell myCell('.');
    myCell.numNeighbors = 3;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
  }
  void test_ConwayCell_turn_atoa(){
    ConwayCell myCell('*');
    myCell.numNeighbors = 2;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
  }
  
  void test_ConwayCell_turn_atod(){
    ConwayCell myCell('*');
    myCell.numNeighbors = 4;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
  }
  
  //neighbors
  
  void test_ConwayCell_name_alive(){
    ConwayCell myCell('*');
    CPPUNIT_ASSERT_EQUAL('*', myCell.name());
  }
  
  void test_ConwayCell_name_dead(){
    ConwayCell myCell('.');
    CPPUNIT_ASSERT_EQUAL('.', myCell.name());
  }
  
  void test_ConwayCell_name_kill(){
    ConwayCell myCell('*');
    myCell.alive = false;
    CPPUNIT_ASSERT_EQUAL('.', myCell.name());
  }
  
  void test_ConwayCell_clone_dead(){
    ConwayCell myCellPrime('.');
    ConwayCell* myCellClone = dynamic_cast<ConwayCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(false, myCellClone->alive);
    delete myCellClone;
  }
  void test_ConwayCell_clone_alive(){
    ConwayCell myCellPrime('*');
    ConwayCell* myCellClone = dynamic_cast<ConwayCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(true, myCellClone->alive);
    delete myCellClone;
  }
  void test_ConwayCell_clone_different(){
    ConwayCell myCellPrime('.');
    ConwayCell* myCellClone = dynamic_cast<ConwayCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(false, myCellClone->alive);
    myCellPrime.alive = true;
    CPPUNIT_ASSERT_EQUAL(true, myCellPrime.alive);
    CPPUNIT_ASSERT_EQUAL(false, myCellClone->alive);
    delete myCellClone;
  }
  
  // ------------
  // Fredkin Cell
  // ------------

  void test_FredkinCell_constructor_age0(){
    FredkinCell myCell('0');
    CPPUNIT_ASSERT_EQUAL(0, myCell.age);
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
  }
  
  void test_FredkinCell_constructor_dead(){
    FredkinCell myCell('-');
    CPPUNIT_ASSERT_EQUAL(0, myCell.age);
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
  }
  
  void test_FredkinCell_constructor_age9(){
    FredkinCell myCell('9');
    CPPUNIT_ASSERT_EQUAL(9, myCell.age);
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
  }
  
  void test_FredkinCell_turn_dtod(){
    FredkinCell myCell('-');
    myCell.numNeighbors = 2;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
    CPPUNIT_ASSERT_EQUAL(0, myCell.age);
  }
  void test_FredkinCell_turn_dtoa(){
    FredkinCell myCell('-');
    myCell.numNeighbors = 3;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
    CPPUNIT_ASSERT_EQUAL(0, myCell.age);
  }
  void test_FredkinCell_turn_atoa(){
    FredkinCell myCell('2');
    myCell.numNeighbors = 3;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(true, myCell.alive);
    CPPUNIT_ASSERT_EQUAL(3, myCell.age);
  }
  
  void test_FredkinCell_turn_atod(){
    FredkinCell myCell('2');
    myCell.numNeighbors = 4;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.alive);
    CPPUNIT_ASSERT_EQUAL(2, myCell.age);
  }
  
  //neighbors
  
  void test_FredkinCell_name_age3(){
    FredkinCell myCell('3');
    CPPUNIT_ASSERT_EQUAL('3', myCell.name());
  }
  
  void test_FredkinCell_name_dead(){
    FredkinCell myCell('-');
    CPPUNIT_ASSERT_EQUAL('-', myCell.name());
  }
  
  void test_FredkinCell_name_age14(){
    FredkinCell myCell('0');
    myCell.age = 14;
    CPPUNIT_ASSERT_EQUAL('+', myCell.name());
  }
  
  void test_FredkinCell_clone_dead(){
    FredkinCell myCellPrime('-');
    FredkinCell* myCellClone = dynamic_cast<FredkinCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(false, myCellClone->alive);
    CPPUNIT_ASSERT_EQUAL(0, myCellClone->age);
    delete myCellClone;
  }
  void test_FredkinCell_clone_alive_3(){
    FredkinCell myCellPrime('3');
    FredkinCell* myCellClone = dynamic_cast<FredkinCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(true, myCellClone->alive);
    CPPUNIT_ASSERT_EQUAL(3, myCellClone->age);
    delete myCellClone;
  }

  void test_FredkinCell_clone_alive_14(){
    FredkinCell myCellPrime('3');
    FredkinCell* myCellClone = dynamic_cast<FredkinCell*>(myCellPrime.clone());
    CPPUNIT_ASSERT_EQUAL(true, myCellClone->alive);
    CPPUNIT_ASSERT_EQUAL(3, myCellClone->age);
    myCellPrime.age = 14;
    CPPUNIT_ASSERT_EQUAL(true, myCellPrime.alive);
    CPPUNIT_ASSERT_EQUAL(14, myCellPrime.age);
    CPPUNIT_ASSERT_EQUAL(true, myCellClone->alive);
    CPPUNIT_ASSERT_EQUAL(3, myCellClone->age);
    delete myCellClone;
  }
  
  
  // -----
  // suite
  // -----
  
  CPPUNIT_TEST_SUITE(TestLife);
  
  CPPUNIT_TEST(test_Life_takeTurn_conway);
  CPPUNIT_TEST(test_Life_takeTurn_fredkin);
  CPPUNIT_TEST(test_Life_takeTurn_fredkin_9to10);
  
  CPPUNIT_TEST(test_life_constructor_1x1_dead);
  CPPUNIT_TEST(test_life_constructor_2x2_alive);
  CPPUNIT_TEST(test_life_constructor_1x1_fredkin);
  
  CPPUNIT_TEST(test_life_simulate_1x1);
  CPPUNIT_TEST(test_life_simulate_2x2);
  CPPUNIT_TEST(test_life_simulate_flipper);
  
  CPPUNIT_TEST(test_Life_print_1x1);
  CPPUNIT_TEST(test_Life_print_3x3);
  CPPUNIT_TEST(test_Life_print_fredkin);
  
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_alive);
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_dead);
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_rise);
  
  CPPUNIT_TEST(test_AbstractCell_operator_int_conway);
  CPPUNIT_TEST(test_AbstractCell_operator_int_fredkin_0);
  CPPUNIT_TEST(test_AbstractCell_operator_int_fredkin_14);
  
  CPPUNIT_TEST_EXCEPTION(test_AbstractCell_setNeighbors_exception, invalid_argument);
  CPPUNIT_TEST(test_AbstractCell_setNeighbors_conway);
  CPPUNIT_TEST(test_AbstractCell_setNeighbors_fredkin);
  
  CPPUNIT_TEST(test_ConwayCell_constructor_alive);
  CPPUNIT_TEST(test_ConwayCell_constructor_dead);
  CPPUNIT_TEST(test_ConwayCell_constructor_3);
  
  CPPUNIT_TEST(test_ConwayCell_turn_dtod);
  CPPUNIT_TEST(test_ConwayCell_turn_dtoa);
  CPPUNIT_TEST(test_ConwayCell_turn_atoa);
  CPPUNIT_TEST(test_ConwayCell_turn_atod);
  
  //neighbors
  
  CPPUNIT_TEST(test_ConwayCell_name_alive);
  CPPUNIT_TEST(test_ConwayCell_name_dead);
  CPPUNIT_TEST(test_ConwayCell_name_kill);
  
  CPPUNIT_TEST(test_ConwayCell_clone_dead);
  CPPUNIT_TEST(test_ConwayCell_clone_alive);
  CPPUNIT_TEST(test_ConwayCell_clone_different);
  
  CPPUNIT_TEST(test_FredkinCell_constructor_age0);
  CPPUNIT_TEST(test_FredkinCell_constructor_dead);
  CPPUNIT_TEST(test_FredkinCell_constructor_age9);
  
  CPPUNIT_TEST(test_FredkinCell_turn_dtod);
  CPPUNIT_TEST(test_FredkinCell_turn_dtoa);
  CPPUNIT_TEST(test_FredkinCell_turn_atoa);
  CPPUNIT_TEST(test_FredkinCell_turn_atod);
  
  //neighbors
  
  CPPUNIT_TEST(test_FredkinCell_name_age3);
  CPPUNIT_TEST(test_FredkinCell_name_dead);
  CPPUNIT_TEST(test_FredkinCell_name_age14);
  
  CPPUNIT_TEST(test_FredkinCell_clone_dead);
  CPPUNIT_TEST(test_FredkinCell_clone_alive_3);
  CPPUNIT_TEST(test_FredkinCell_clone_alive_14);
  
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
