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
  

  // -----
  // suite
  // -----
  
  CPPUNIT_TEST_SUITE(TestLife);
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
