#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // invalid_argument, out_of_range

using namespace std;
class Position {
  /**
   * + operator for Position
   * @param lhs the Position on the left hand side of the operator
   * @param rhs the Position on the right hand side of the operator
   * @return Position with lhr.r + rhs.r and lhs.c + rhs.c by value.
   */
  friend Position operator+(Position lhs, const Position& rhs) {
    return lhs += rhs;
  }
  
 public:
  int r;
  int c;
  
  Position(int, int);
  
  Position& operator+=(const Position& rhs);
};

const static Position NORTH(-1, 0);
const static Position NORTH_EAST(-1, 1);
const static Position EAST(0, 1);
const static Position SOUTH_EAST(1, 1);
const static Position SOUTH(1, 0);
const static Position SOUTH_WEST(1, -1);
const static Position WEST(0, -1);
const static Position NORTH_WEST(-1, -1);

static const Position cnarr[] = {NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST};
static const Position fnarr[] = {NORTH, EAST, SOUTH, WEST};
static const vector<Position> conwayNeighbors(cnarr, cnarr + 8);
static const vector<Position> fredkinNeighbors(fnarr, fnarr + 4);

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
  
  void countNeighbors(T&);
  bool isAlive(Position);
};

class AbstractCell {
 protected:
  int numNeighbors;
  
 public:
  bool alive;
  virtual char name() const = 0;
  virtual void turn() = 0;
  virtual const vector<Position>& neighbors() const = 0;
  
  virtual operator bool ();
  virtual operator int ();
  
  virtual void setNeighbors(int);
  
  virtual AbstractCell* clone() const = 0;
};

class Cell {
 private:
  AbstractCell* ptr;
 public:
  Cell(char);
  Cell(const Cell&);
  Cell& operator = (Cell);
  ~Cell();
  
  void turn();
  const vector<Position>& neighbors() const;
  char name() const;
  
  void setNeighbors(int);
  
  operator bool();
  operator int();
};


class ConwayCell : public AbstractCell {
 public:
  ConwayCell(char);
  
  void turn();
  const vector<Position>& neighbors() const;
  char name() const;
  
  AbstractCell* clone() const;
};

class FredkinCell : public AbstractCell {
 private:
  int age;
 public:
  FredkinCell(char);
  
  void turn();
  const vector<Position>& neighbors() const;
  char name() const;
  
  AbstractCell* clone() const;
  operator int();
};

// --------
// position
// --------

/**
 * Two int constructor for position
 * @param r the row value of the position
 * @param c the col value of the position
 */
Position::Position(int r = 0, int c = 0) : r (r), c(c) {
}

/**
 * The += operator of Position
 * @param rhs The right hand side of the operator
 * @return reference to *this
 */
Position& Position::operator +=(const Position& rhs) {
  r += rhs.r;
  c += rhs.c;
  return *this;
}

// ----
// Life
// ----

/**
 * istream& Life Constructor
 * @param in the istream& to read input from
 */
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
      if(grid[r][c])
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
      countNeighbors(grid[i][j]);
    }
  
  for(unsigned int i = 0; i < grid.size(); i++) {
    for(unsigned int j = 0; j < grid[0].size(); j++) {
      grid[i][j].turn();
      if (grid[i][j])
        population++;
    }
  }
  generation++;
}

/**
 * Run the game the specified number of turns
 * @param numTurns the number of turns to run for.
 */
template <typename T>
void Life<T>::simulate(int numTurns) {
  while(numTurns-- > 0)
    takeTurn();
}

/**
 * Print out the current state of the game
 * @param out the ostream& to print out to.
 */
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

/**
 * Count and set the number of alive neighbors of the specified cell.
 * @param cell the cell to count the neighbors of
 */
template <typename T>
void Life<T>::countNeighbors(T& cell) {
  vector<Position> adjacent = cell.neighbors();
  int numNeighbors = 0;
  for(unsigned int i = 0; i < adjacent.size(); i++) {
    numNeighbors += isAlive(adjacent[i]);
  }
  cell.setNeighbors(numNeighbors);
}

/**
 * see if the specified cell is alive
 * @param adj a Position specifying the grid location of the cell to check relative to current location.
 * @return bool representing if the cell is alive or not.
 */
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

/**
 * Set the neighbor count to the given value
 * @param n the value to set numNeighbors to.
 */
void AbstractCell::setNeighbors(int n) {
  if(n < 0 || n > 8) throw(invalid_argument("n must be between 0 and 8, inclusive"));
  numNeighbors = n;
}

/**
 * Conversion to bool representing the aliveness of the cell.
 * @return bool representing whether the cell is alive or not
 */
AbstractCell::operator bool() {
  return alive;
}

/**
 * Conversion to int representing the age of the cell.  Defaults to 0.
 * @return 0
 */
AbstractCell::operator int() {
  return 0;
}

// ----
// Cell
// ----

/**
 * char constructor for Cell.  Creates a new Conway or Fredkin cell depending on input.
 * @param c char representing the type and state of the cell to be created.
 */
Cell::Cell(char c){
  if(c == '.'|| c == '*')
    ptr = new ConwayCell(c);
  else
    ptr = new FredkinCell(c);
}

/**
 * Copy constructor
 * @param other the Cell to copy
 */
Cell::Cell(const Cell& other) {
  if (!other.ptr)
    ptr = 0;
  else
    ptr = other.ptr->clone();
}

/**
 * Copy assignment
 * @param other the Cell to copy
 */
Cell& Cell::operator = (Cell other) {
  swap(ptr, other.ptr);
  return *this;
}

/**
 * Destructor.  Deletes ptr.
 */  
Cell::~Cell() {
  delete ptr;
}

/**
 * Advance the state of the Cell by one turn.  Assumes numNeighbors has been set
 */
void Cell::turn() {
  ptr->turn();
  if(*ptr == 2 && *ptr) {
    delete ptr;
    ptr = new ConwayCell('*');  
  }
}

/**
 * Get a Position vector representing the Positions to consider as neighbors.
 * @return const vector<Position>& representing the relative Positions to consider as neighbors.
 */
const vector<Position>& Cell::neighbors() const {
  return ptr->neighbors();
}

/**
 * Get the character representing the current state of the Cell
 * @return char representing the state of the cell
 */
char Cell::name() const {
  return ptr->name();
}

/**
 * set the neighbor count of the Cell
 * @param n the value to set the neighbor count to.
 */
void Cell::setNeighbors(int n) {
  ptr->setNeighbors(n);
}

/**
 * Conversion to bool
 * return the conversion to bool of the contained AbstractCell
 */
Cell::operator bool(){
  return *ptr;
}

/**
 * Conversion to int
 * return the conversion to int of the contained AbstractCell
 */
Cell::operator int() {
  return *ptr;
}

// -----------
// Conway Cell
// -----------

/**
 * char constructor for ConwayCell
 * @param char representing the initial state of the cell.
 */
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

/**
 * Get a Position vector representing the Positions to consider as neighbors.
 * @return const vector<Position>& representing the relative Positions to consider as neighbors.
 */
const vector<Position>& ConwayCell::neighbors() const {
  return conwayNeighbors;
}

/**
 * Get the character representing the current state of the Cell
 * @return char representing the state of the cell
 */
char ConwayCell::name() const {
  if(alive)
    return '*';
  return '.';
}

/**
 * Create a clone of the cell
 * @return pointer to the new cell.
 */
AbstractCell* ConwayCell::clone() const {
  return new ConwayCell(*this);
}


// ------------
// Fredkin Cell
// ------------

/**
 * char constructor for FredkinCell
 * @param char representing the initial state of the cell.
 */
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
    if(alive)
      age++;
    alive = true;
  }
  else
    alive = false;
}

/**
 * Get a Position vector representing the Positions to consider as neighbors.
 * @return const vector<Position>& representing the relative Positions to consider as neighbors.
 */
const vector<Position>& FredkinCell::neighbors() const {
  return fredkinNeighbors;
}

/**
 * Get the character representing the current state of the Cell
 * @return char representing the state of the cell
 */
char FredkinCell::name() const {
  if(!alive)
    return '-';
  if(age > 9)
    return '+';
  return (char) (age + 0x30);
}

/**
 * Conversion to int.
 * @return the age of the cell.
 */
FredkinCell::operator int() {
  return age;
}

/**
 * Create a clone of the cell
 * @return pointer to the new cell.
 */
AbstractCell* FredkinCell::clone() const {
  return new FredkinCell(*this);
}
