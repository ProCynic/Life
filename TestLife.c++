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

  void test_Position_constructor_0_0(){
    Position p(0, 0);
    CPPUNIT_ASSERT_EQUAL(0, p.r);
    CPPUNIT_ASSERT_EQUAL(0, p.c);
  }
  
  void test_Position_constructor_3_4(){
    Position p(3, 4);
    CPPUNIT_ASSERT_EQUAL(3, p.r);
    CPPUNIT_ASSERT_EQUAL(4, p.c);
  }

  void test_Position_constructor_neg4_5(){
    Position p(-4, 5);
    CPPUNIT_ASSERT_EQUAL(-4, p.r);
    CPPUNIT_ASSERT_EQUAL(5, p.c);
  }

  void test_Position_plusEqual_1() {
    Position p(-1, -2);
    Position q(1, 5);
    p += q;
    CPPUNIT_ASSERT_EQUAL(0, p.r);
    CPPUNIT_ASSERT_EQUAL(3, p.c);
    CPPUNIT_ASSERT_EQUAL(1, q.r);
    CPPUNIT_ASSERT_EQUAL(5, q.c);    
  }
  
    void test_Position_plusEqual_2() {
    Position p(0, 0);
    Position q(3, 3);
    p += q;
    CPPUNIT_ASSERT_EQUAL(3, p.r);
    CPPUNIT_ASSERT_EQUAL(3, p.c);
    CPPUNIT_ASSERT_EQUAL(3, q.r);
    CPPUNIT_ASSERT_EQUAL(3, q.c);    
  }

  void test_Position_plusEqual_3() {
    Position p(12, 34);
    Position q(56, 78);
    p += q;
    CPPUNIT_ASSERT_EQUAL(68, p.r);
    CPPUNIT_ASSERT_EQUAL(112, p.c);
    CPPUNIT_ASSERT_EQUAL(56, q.r);
    CPPUNIT_ASSERT_EQUAL(78, q.c);    
  }
  
  void test_Position_plus_1() {
    Position p(-1, -2);
    Position q(1, 5);
    Position r = p + q;
    CPPUNIT_ASSERT_EQUAL(0, r.r);
    CPPUNIT_ASSERT_EQUAL(3, r.c);
    CPPUNIT_ASSERT_EQUAL(-1, p.r);
    CPPUNIT_ASSERT_EQUAL(-2, p.c);   
    CPPUNIT_ASSERT_EQUAL(1, q.r);
    CPPUNIT_ASSERT_EQUAL(5, q.c);    
  }
  
    void test_Position_plus_2() {
    Position p(0, 0);
    Position q(3, 3);
    Position r = p + q;
    CPPUNIT_ASSERT_EQUAL(3, r.r);
    CPPUNIT_ASSERT_EQUAL(3, r.c);
    CPPUNIT_ASSERT_EQUAL(0, p.r);
    CPPUNIT_ASSERT_EQUAL(0, p.c);   
    CPPUNIT_ASSERT_EQUAL(3, q.r);
    CPPUNIT_ASSERT_EQUAL(3, q.c);    
  }

  void test_Position_plus_3() {
    Position p(12, 34);
    Position q(56, 78);
    Position r = p + q;
    CPPUNIT_ASSERT_EQUAL(68, r.r);
    CPPUNIT_ASSERT_EQUAL(112, r.c);
    CPPUNIT_ASSERT_EQUAL(12, p.r);
    CPPUNIT_ASSERT_EQUAL(34, p.c);   
    CPPUNIT_ASSERT_EQUAL(56, q.r);
    CPPUNIT_ASSERT_EQUAL(78, q.c);    
  }
  
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

  void test_Life_countNeighbors_conway() {
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    
    int expected[3][3] = {{1, 2, 1}, {2, 2, 2}, {1, 2, 1}};
    
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        l.countNeighbors(l.grid[x][y]);
      }
    }
    
    CPPUNIT_ASSERT_EQUAL(expected[0][0], l.grid[0][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][1], l.grid[0][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][2], l.grid[0][2].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][0], l.grid[1][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][1], l.grid[1][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][2], l.grid[1][2].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][0], l.grid[2][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][1], l.grid[2][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][2], l.grid[2][2].numNeighbors);
  }

  void test_Life_countNeighbors_fredkin() {
    istringstream in("3\n3\n0--\n-0-\n--0\n");
    Life<FredkinCell> l(in);
    
    int expected[3][3] = {{0, 2, 0}, {2, 0, 2}, {0, 2, 0}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        l.countNeighbors(l.grid[x][y]);
      }
    }
    
    CPPUNIT_ASSERT_EQUAL(expected[0][0], l.grid[0][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][1], l.grid[0][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][2], l.grid[0][2].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][0], l.grid[1][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][1], l.grid[1][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][2], l.grid[1][2].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][0], l.grid[2][0].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][1], l.grid[2][1].numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][2], l.grid[2][2].numNeighbors);
  }

  void test_Life_countNeighbors_cell() {
    istringstream in("3\n3\n*..\n-0-\n..*\n");
    Life<Cell> l(in);
    
    int expected[3][3] = {{1, 2, 1}, {2, 0, 2}, {1, 2, 1}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        l.countNeighbors(l.grid[x][y]);
      }
    }
    
    CPPUNIT_ASSERT_EQUAL(expected[0][0], l.grid[0][0].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][1], l.grid[0][1].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[0][2], l.grid[0][2].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][0], l.grid[1][0].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][1], l.grid[1][1].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[1][2], l.grid[1][2].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][0], l.grid[2][0].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][1], l.grid[2][1].ptr->numNeighbors);
    CPPUNIT_ASSERT_EQUAL(expected[2][2], l.grid[2][2].ptr->numNeighbors);
  }

  
  void test_isAlive_north(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, false, false}, {true, false, false}, {false, true, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(NORTH)); 
      }
    }
  }
  
  void test_isAlive_north_east(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, false, false}, {false, false, false}, {true, false, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(NORTH_EAST)); 
      }
    }
  }
  
  void test_isAlive_east(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, false, false}, {true, false, false}, {false, true, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(EAST)); 
      }
    }
  }
  
  void test_isAlive_south_east(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{true, false, false}, {false, true, false}, {false, false, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(SOUTH_EAST)); 
      }
    }
  }
  
  void test_isAlive_south(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, true, false}, {false, false, true}, {false, false, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(SOUTH)); 
      }
    }
  }
  
  void test_isAlive_south_west(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, false, true}, {false, false, false}, {false, false, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(SOUTH_WEST)); 
      }
    }
  }
  
  void test_isAlive_west(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, true, false}, {false, false, true}, {false, false, false}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(WEST)); 
      }
    }
  }
  
  void test_isAlive_north_west(){
    istringstream in("3\n3\n*..\n.*.\n..*\n");
    Life<ConwayCell> l(in);
    bool expected[3][3] = {{false, false, false}, {false, true, false}, {false, false, true}};
    for (int x = 0; x < 3; x++) {
      for (int y = 0; y < 3; y++) {
        l.current.r = x;
        l.current.c = y;
        CPPUNIT_ASSERT_EQUAL(expected[x][y], l.isAlive(NORTH_WEST)); 
      }
    }
  }
  

  
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
  
  void test_Cell_copyConstructor_dead() {
    Cell c('.');
    Cell d(c);
    CPPUNIT_ASSERT_EQUAL(false, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('.', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }
  
  void test_Cell_copyConstructor_alive() {
    Cell c('*');
    Cell d(c);
    CPPUNIT_ASSERT_EQUAL(true, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('*', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }
  
  void test_Cell_copyConstructor_fredkin() {
    Cell c('0');
    Cell d(c);
    CPPUNIT_ASSERT_EQUAL(true, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('0', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }

  // copy assignment
  void test_Cell_copyAssignment_conway() {
    Cell c('.');
    Cell d('*');
    CPPUNIT_ASSERT_EQUAL(true, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('*', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
    d = c;
    CPPUNIT_ASSERT_EQUAL(false, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('.', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }
  
  void test_Cell_copyAssignment_fredkin() {
    Cell c('-');
    Cell d('0');
    CPPUNIT_ASSERT_EQUAL(true, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('0', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
    d = c;
    CPPUNIT_ASSERT_EQUAL(false, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('-', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }
  
  void test_Cell_copyAssignment_ftoc() {
    Cell c('*');
    Cell d('-');
    CPPUNIT_ASSERT_EQUAL(false, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('-', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
    d = c;
    CPPUNIT_ASSERT_EQUAL(true, d.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('*', d.name());
    CPPUNIT_ASSERT(c.ptr != d.ptr);
  }

  // turn
  void test_Cell_turn_conway(){
    Cell myCell('*');
    myCell.ptr->numNeighbors = 4;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.ptr->alive);
  }
  void test_Cell_turn_fredkin(){
    Cell myCell('0');
    myCell.ptr->numNeighbors = 4;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(false, myCell.ptr->alive);
  }
  void test_Cell_turn_ftoc(){
    Cell myCell('0');
    myCell.ptr->numNeighbors = 3;
    dynamic_cast<FredkinCell*>(myCell.ptr)->age = 1;
    myCell.turn();
    CPPUNIT_ASSERT_EQUAL(true, myCell.ptr->alive);
    CPPUNIT_ASSERT_EQUAL('*', myCell.name());
  }
  // neighbors
  
  void test_Cell_neighbors_conway(){
    Cell myCell('.');
    const vector<Position>* p = &myCell.neighbors();
    CPPUNIT_ASSERT_EQUAL(p, &conwayNeighbors);
  }
  
  void test_Cell_neighbors_fredkin(){
    Cell myCell('-');
    const vector<Position>* p = &myCell.neighbors();
    CPPUNIT_ASSERT_EQUAL(p, &fredkinNeighbors);
  }
  
  // name
  
  void test_Cell_name_conway(){
    Cell myCell('*');
    CPPUNIT_ASSERT_EQUAL('*', myCell.name());
  }
  
  void test_Cell_name_fredkin_3(){
    Cell myCell('3');
    CPPUNIT_ASSERT_EQUAL('3', myCell.name());
  }
  
  void test_Cell_name_fredkin_dead(){
    Cell myCell('-');
    CPPUNIT_ASSERT_EQUAL('-', myCell.name());
  }

  // setNeighbors

  void test_Cell_setNeighbors_conway(){
    Cell myCell('*');
    myCell.setNeighbors(4);
    CPPUNIT_ASSERT_EQUAL(4, myCell.ptr->numNeighbors);
  }
  
  void test_Cell_setNeighbors_fredkin(){
    Cell myCell('*');
    myCell.setNeighbors(4);
    CPPUNIT_ASSERT_EQUAL(4, myCell.ptr->numNeighbors);
  }

  void test_Cell_setNeighbors_fredkin_dead(){
    Cell myCell('-');
    myCell.setNeighbors(4);
    CPPUNIT_ASSERT_EQUAL(4, myCell.ptr->numNeighbors);
  }
  
  // operator bool
  
  void test_Cell_operator_bool_dead(){
    Cell myCell('.');
    CPPUNIT_ASSERT_EQUAL(false, (bool)myCell);
  }
  
  void test_Cell_operator_bool_alive(){
    Cell myCell('*');
    CPPUNIT_ASSERT_EQUAL(true, (bool)myCell);
  }
  
  void test_Cell_operator_bool_fredkin(){
    Cell myCell('-');
    CPPUNIT_ASSERT_EQUAL(false, (bool)myCell);
  }
  
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
  
  CPPUNIT_TEST(test_Position_constructor_0_0);
  CPPUNIT_TEST(test_Position_constructor_3_4);
  CPPUNIT_TEST(test_Position_constructor_neg4_5);
  
  CPPUNIT_TEST(test_Position_plusEqual_1);
  CPPUNIT_TEST(test_Position_plusEqual_2);
  CPPUNIT_TEST(test_Position_plusEqual_3);
  
  CPPUNIT_TEST(test_Position_plus_1);
  CPPUNIT_TEST(test_Position_plus_2);
  CPPUNIT_TEST(test_Position_plus_3);
  
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
  
  CPPUNIT_TEST(test_Life_countNeighbors_conway);
  CPPUNIT_TEST(test_Life_countNeighbors_fredkin);
  CPPUNIT_TEST(test_Life_countNeighbors_cell);
  
  CPPUNIT_TEST(test_isAlive_north);
  CPPUNIT_TEST(test_isAlive_north_east);
  CPPUNIT_TEST(test_isAlive_east);
  CPPUNIT_TEST(test_isAlive_south_east);
  CPPUNIT_TEST(test_isAlive_south);
  CPPUNIT_TEST(test_isAlive_south_west);
  CPPUNIT_TEST(test_isAlive_west);
  CPPUNIT_TEST(test_isAlive_north_west);
  
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_alive);
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_dead);
  CPPUNIT_TEST(test_AbstractCell_operator_bool_conway_rise);
  
  CPPUNIT_TEST(test_AbstractCell_operator_int_conway);
  CPPUNIT_TEST(test_AbstractCell_operator_int_fredkin_0);
  CPPUNIT_TEST(test_AbstractCell_operator_int_fredkin_14);
  
  CPPUNIT_TEST_EXCEPTION(test_AbstractCell_setNeighbors_exception, invalid_argument);
  CPPUNIT_TEST(test_AbstractCell_setNeighbors_conway);
  CPPUNIT_TEST(test_AbstractCell_setNeighbors_fredkin);
  
  CPPUNIT_TEST(test_Cell_copyConstructor_dead);
  CPPUNIT_TEST(test_Cell_copyConstructor_alive);
  CPPUNIT_TEST(test_Cell_copyConstructor_fredkin);
  
  CPPUNIT_TEST(test_Cell_copyAssignment_conway);
  CPPUNIT_TEST(test_Cell_copyAssignment_fredkin);
  CPPUNIT_TEST(test_Cell_copyAssignment_ftoc);
  
  CPPUNIT_TEST(test_Cell_turn_conway);
  CPPUNIT_TEST(test_Cell_turn_fredkin);
  CPPUNIT_TEST(test_Cell_turn_ftoc);
  
  CPPUNIT_TEST(test_Cell_neighbors_conway);
  CPPUNIT_TEST(test_Cell_neighbors_fredkin);
  
  CPPUNIT_TEST(test_Cell_name_conway);
  CPPUNIT_TEST(test_Cell_name_fredkin_3);
  CPPUNIT_TEST(test_Cell_name_fredkin_dead);
  
  CPPUNIT_TEST(test_Cell_setNeighbors_conway);
  CPPUNIT_TEST(test_Cell_setNeighbors_fredkin);
  CPPUNIT_TEST(test_Cell_setNeighbors_fredkin_dead);
  
  CPPUNIT_TEST(test_Cell_operator_bool_dead);
  CPPUNIT_TEST(test_Cell_operator_bool_alive);
  CPPUNIT_TEST(test_Cell_operator_bool_fredkin);
  
  CPPUNIT_TEST(test_ConwayCell_constructor_alive);
  CPPUNIT_TEST(test_ConwayCell_constructor_dead);
  CPPUNIT_TEST(test_ConwayCell_constructor_3);
  
  CPPUNIT_TEST(test_ConwayCell_turn_dtod);
  CPPUNIT_TEST(test_ConwayCell_turn_dtoa);
  CPPUNIT_TEST(test_ConwayCell_turn_atoa);
  CPPUNIT_TEST(test_ConwayCell_turn_atod);
  
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
