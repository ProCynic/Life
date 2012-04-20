#include <iostream>
#include <string>
#include <vector>

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
  
  bool isAlive(Position);
};

class AbstractCell {
 private:
  int numNeighbors;
  
 public:
  bool alive;
  virtual char name() = 0;
  virtual void countNeighbors(const Life* const) = 0;
  virtual void turn() = 0;

  operator bool () {return alive};
};

//class Cell {};

class FredkinCell : AbstractCell {
 private:
  int age;
 public:
  FredkinCell(char);
};

class ConwayCell : AbstractCell {
 public:
  ConwayCell(char);
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
Life<T>::Life(istream& in) : {
  generation = 0;
  int rows;
  int cols;
  in >> rows;
  in >> cols >> ws;

  for(unsigned int r = 0; r < rows; r++) {
    grid.push_back(vector<T>);
    for(unsigned int c = 0; c < cols; c++) {
      char cell;
      in >> cell;
      grid[r].push_back(T(cell));
    }
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
    for(unsigned int j = 0; j < grid[0].size(); j++)
      grid[i][j].countNeighbors();
  
  for(unsigned int i = 0; i < grid.size(); i++) {
    for(unsigned int j = 0; j < grid[0].size(); j++) {
      current.r = i;
      current.c = j;
      grid[i][j].turn();
      if (grid[i][j].alive)
        population++;
    }
  }
  generation++;
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
bool Life<T>::isAlive(Position adj) {
  Position p = current + p;
  if(p.r < 0 || p.r >= (int)grid.size() || p.c < 0 || p.c >= (int)grid[0].size()) 
    return false;
  return grid[p.r][p.c];
}

// -----------
// Conway Cell
// -----------

ConwayCell::ConwayCell(char c) {
  if (c == '.')
    this.alive = false;
  else if (c == '*')
    this.alive = true;
}

/**
 * Advance the cell state by one turn.
 */
void ConwayCell::turn() {
  if (numNeighbors == 3)
    alive = true;
  if (numNeighbors < 2 || numNeighbors > 3)
    alive = false;
}

void ConwayCell::countNeighbors(const Life* const board) {
  neighbors += board->isAlive(NORTH);
  neighbors += board->isAlive(NORTH_EAST);
  neighbors += board->isAlive(EAST);
  neighbors += board->isAlive(SOUTH_EAST);
  neighbors += board->isAlive(SOUTH);
  neighbors += board->isAlive(SOUTH_WEST);
  neighbors += board->isAlive(WEST);
  neighbors += board->isAlive(NORTH_WEST);
}

char ConwayCell::name() {
  if(alive)
    return '*';
  return '.';
}

// ------------
// Fredkin Cell
// ------------

FredkinCell::FredkinCell(char c) : age (0) {
  if (c == '-')
    alive = false;
  else {
    alive = true;
    age = (int) c;
  } 
}

/**
 * Construct a new Fredkin Cell with age 0.
 */
FredkinCell::FredkinCell() : age (age) {
}

void FredkinCell::countNeighbors(const Life& board) {
  neighbors += board->isAlive(NORTH);
  neighbors += board->isAlive(EAST);
  neighbors += board->isAlive(SOUTH);
  neighbors += board->isAlive(WEST);
}

/**
 * Advance the cell state by one turn.
 */
void FredkinCell::turn() {
  if (numNeighbors % 2 == 1)
    alive = true;
  else
    alive = false;
  age++;
}

char FredkinCell::name() {
  if(!alive)
    return '-';
  if(age > 9)
    return '+';
  return (char) age;
}
