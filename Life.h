#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Position {
  friend const Position operator+(Position lhs, const Position& rhs) {
    return lhs += rhs;
  }

 public:
  int r;
  int c;
  
  Position(int, int);
  
  Position operator+=(const Position& rhs) {
    r += rhs.r;
    c += rhs.c;
    return *this;
  }
};

const static Position NORTH(1, 0);
const static Position NORTH_EAST(1, 1);
const static Position EAST(0, 1);
const static Position SOUTH_EAST(-1, 1);
const static Position SOUTH(-1, 0);
const static Position SOUTH_WEST(-1, -1);
const static Position WEST(0, -1);
const static Position NORTH_WEST(1, -1);

template <typename T>
class Life {
 private:
  vector< vector<T> > grid;
  int generation;
  int population;
  Position current;
  
  void takeTurn();
  
 public:
  Life(istream& in);
  void simulate(int numTurns);    
  void print(ostream& out);
  
  int countNeighbors(unsigned char);
  bool isAlive(Position);
};

class AbstractCell {
 protected:
  int numNeighbors;
  
 public:
  bool alive;
  virtual char name() = 0;
  virtual void turn() = 0;
  virtual unsigned char neighbors() = 0;
  
  virtual operator bool ();
  
  virtual void setNeighbors(int);
};

// --------
/*
class Cell : public AbstractCell {
 private:
  AbstractCell* ptr;
 public:
  Cell(char);
  Cell(const Cell&);
  Cell& operator = (Cell);
  ~Cell();

  void turn();
  unsigned char neighbors();
  char name();

  void setNeighbors(int);
  
  operator bool();
};
*/
class FredkinCell : public AbstractCell {
 private:
  int age;
 public:
  FredkinCell(char);

  void turn();
  unsigned char neighbors();
  char name();
};

class ConwayCell : public AbstractCell {
 public:
  ConwayCell(char);

  void turn();
  unsigned char neighbors();
  char name();
};


// --------
// position
// --------

Position::Position(int r = 0, int c = 0) : r (r), c(c) {
}

// ----
// Life
// ----

template <typename T>
Life<T>::Life(istream& in) {
  generation = 0;
  population = 0;
  int rows;
  int cols;
  in >> rows;
  in >> cols >> ws;

  for(int r = 0; r < rows; r++) {
    grid.push_back(vector<T>());
    for(int c = 0; c < cols; c++) {
      char cell;
      in >> cell;
      grid[r].push_back(T(cell));
      if(grid[r][c].alive)
        population++;
    }
    if(in)
      in >> ws;
  }
}

/**
 * Advance the board by one turn.
 */
template <typename T>
void Life<T>::takeTurn() {
  population = 0;
  for(unsigned int i = 0; i < grid.size(); i++)
    for(unsigned int j = 0; j < grid[0].size(); j++) {
      current.r = i;
      current.c = j;
      grid[i][j].setNeighbors(countNeighbors(grid[i][j].neighbors()));
    }
  
  for(unsigned int i = 0; i < grid.size(); i++) {
    for(unsigned int j = 0; j < grid[0].size(); j++) {
      grid[i][j].turn();
      if (grid[i][j].alive)
        population++;
    }
  }
  generation++;
}

template <typename T>
void Life<T>::simulate(int numTurns) {
  while(numTurns-- > 0)
    takeTurn();
}

template <typename T>
void Life<T>::print(ostream& out) {
  out << "Generation = " << generation << ", Population = " << population << "." << endl;
  for(unsigned int i = 0; i < grid.size(); i++) {
    for(unsigned int j = 0; j < grid[0].size(); j++)
      out << grid[i][j].name();
    out << endl;
  }
  out << endl;
}

template <typename T>
int Life<T>::countNeighbors(unsigned char neighbors) {
  int numNeighbors = 0;
  if(neighbors & 0x80)
    numNeighbors += isAlive(NORTH);
  if(neighbors & 0x40)
    numNeighbors += isAlive(NORTH_EAST);
  if(neighbors & 0x20)
    numNeighbors += isAlive(EAST);
  if(neighbors & 0x10)
    numNeighbors += isAlive(SOUTH_EAST);
  if(neighbors & 0x08)
    numNeighbors += isAlive(SOUTH);
  if(neighbors & 0x04)
    numNeighbors += isAlive(SOUTH_WEST);
  if(neighbors & 0x02)
    numNeighbors += isAlive(WEST);
  if(neighbors & 0x01)
    numNeighbors += isAlive(NORTH_WEST);
  return numNeighbors;
}


template <typename T>
bool Life<T>::isAlive(Position adj) {
  Position p = current + adj;
  if(p.r < 0 || p.r >= (int)grid.size() || p.c < 0 || p.c >= (int)grid[0].size()) 
    return false;
  return grid[p.r][p.c];
}

// -------------
// Abstract Cell
// -------------

void AbstractCell::setNeighbors(int n) {
  numNeighbors = n;
}

AbstractCell::operator bool() {
  return alive;
}

// ----
// Cell
// ----
/*
Cell::Cell(char c){
  cerr << "c";
  if(c == '.'|| c == '*')
    ptr = new ConwayCell(c);
  else
    ptr = new FredkinCell(c);
}

Cell::Cell(const Cell& other) {
  if (!other.ptr)
    ptr = 0;
  else
    ptr = other.ptr->clone();
}

Cell& Cell::operator = (Cell other) {
  swap(ptr, other.ptr);
}

Cell::~Cell() {
  cerr << "destructing" << endl;
  delete ptr;
}

void Cell::turn() {
  ptr->turn();
}

unsigned char Cell::neighbors() {
  return ptr->neighbors();
}

char Cell::name(){
  return ptr->name();
}

void Cell::setNeighbors(int n) {
  ptr->setNeighbors(n);
}

Cell::operator bool(){
  return *ptr;
}
*/
// -----------
// Conway Cell
// -----------

ConwayCell::ConwayCell(char c) {
  if (c == '.')
    alive = false;
  else if (c == '*')
    alive = true;
}

/**
 * Advance the cell state by one turn.
 */
void ConwayCell::turn() {
  if (numNeighbors == 3)
    alive = true;
  else if (numNeighbors < 2 || numNeighbors > 3)
    alive = false;
  else
    alive = alive; //do nothing
}

unsigned char ConwayCell::neighbors() {
  return 0xFF;
}


char ConwayCell::name() {
  if(alive)
    return '*';
  return '.';
}

// ------------
// Fredkin Cell
// ------------

FredkinCell::FredkinCell(char c) {
  age = 0;
  if (c == '-')
    alive = false;
  else {
    alive = true;
    age = c & 0xF;
  } 
}

/**
 * Advance the cell state by one turn.
 */
void FredkinCell::turn() {
  if (numNeighbors % 2 == 1) {
    alive = true;
    age++;
  }
  else
    alive = false;
}

unsigned char FredkinCell::neighbors() {
  return 0xAA;
}

char FredkinCell::name() {
  if(!alive)
    return '-';
  if(age > 9)
    return '+';
  return (char) (age + 0x30);
}
