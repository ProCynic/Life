// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2011
// Glenn P. Downing
// -------------------------

/*
  To run the program:
  % g++ -ansi -pedantic -Wall RunLife.c++ -o RunLife.c++.app
  % valgrind RunLife.c++.app > RunLife.out
  
  To configure Doxygen:
  doxygen -g
  That creates the file Doxyfile.
  Make the following edits:
  EXTRACT_ALL            = YES
  EXTRACT_PRIVATE        = YES
  EXTRACT_STATIC         = YES
  GENERATE_LATEX         = NO
  
  To document the program:
  doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <fstream>


#include "Life.h"

// ----
// main
// ----

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
  
  // -----------------------
  // life conway cell 109x69
  // -----------------------
  try {
    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    /*
      read LifeConwayCell.in // assume all Conway cells
      Print grid.
      Simulate 283 moves.
      Print grid.
      Simulate 40 moves.
      Print grid.
      Simulate 2500 moves.
      Print grid.
    */
    ifstream file;
    file.open("RunLifeConway.in");
    assert(file.good());

    Life<ConwayCell> l(file);

    file.close();

    l.print(cout);

    l.simulate(283);
    l.print(cout);
    
    l.simulate(40);
    l.print(cout);
    
    l.simulate(2500);
    l.print(cout);
  }
  catch (const invalid_argument&) {
    assert(false);
  }
  catch (const out_of_range&) {
    assert(false);
  }

  // -----------------------
  // life fredkin cell 20x20
  // -----------------------
  
  try {
    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /*
      read LifeFredkinCell.in // assume all Fredkin cells
      Print grid.
      Simulate 2 moves.
      Print every grid.
    */

    ifstream file;
    file.open("RunLifeFredkin.in");    
    assert(file.good());    

    Life<FredkinCell> l(file);

    file.close();

    l.print(cout);

    l.simulate(1);
    l.print(cout);

    l.simulate(1);
    l.print(cout);
  }
  catch (const invalid_argument&) {
    assert(false);
  }
  catch (const out_of_range&) {
    assert(false);
  }
  
  // ---------------
  // life cell 20x20
  // ---------------
  
  try {
    cout << "*** Life<Cell> 20x20 ***" << endl;
    /*
      read LifeCell.in // assume all Fredkin cells
      Print grid.
      Simulate 5 moves.
      Print every grid.
    */
    /*
    ifstream file;
    file.open("RunLife.in");    
    assert(file.good());    
    
    Life<Cell> l(file);

    file.close();

    l.print(cout);

    for(int x = 0; x < 5; x++) {
      l.simulate(1);
      l.print(cout);
    }
    */

  }
  catch (const invalid_argument&) {
    assert(false);
  }
  catch (const out_of_range&) {
    assert(false);
  }
  
  return 0;
}
