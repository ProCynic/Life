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
  
  bool isAlive(Position);
};

class AbstractCell {
 protected:
  int numNeighbors;
  
 public:
  bool alive;

  virtual char name() = 0;
  virtual void turn() = 0;
};

// --------

//class Cell {};

class FredkinCell : public AbstractCell {
 private:
  int age;
 public:
  FredkinCell(char);

  void turn();
  void countNeighbors(Life<FredkinCell>&);
  char name();
};

class ConwayCell : public AbstractCell {
 public:
  ConwayCell(char);

  void turn();
  void countNeighbors(Life<ConwayCell>&);
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
    in >> ws;
  }
  print(cerr);
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
      grid[i][j].countNeighbors(*this);
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
bool Life<T>::isAlive(Position adj) {
  Position p = current + adj;
  if(p.r < 0 || p.r >= (int)grid.size() || p.c < 0 || p.c >= (int)grid[0].size()) 
    return false;
  return grid[p.r][p.c].alive;
}

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
  if (numNeighbors < 2 || numNeighbors > 3)
    alive = false;
}

void ConwayCell::countNeighbors(Life<ConwayCell>& board) {
  numNeighbors += board.isAlive(NORTH);
  numNeighbors += board.isAlive(NORTH_EAST);
  numNeighbors += board.isAlive(EAST);
  numNeighbors += board.isAlive(SOUTH_EAST);
  numNeighbors += board.isAlive(SOUTH);
  numNeighbors += board.isAlive(SOUTH_WEST);
  numNeighbors += board.isAlive(WEST);
  numNeighbors += board.isAlive(NORTH_WEST);
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

void FredkinCell::countNeighbors(Life<FredkinCell>& board) {
  numNeighbors += board.isAlive(NORTH);
  numNeighbors += board.isAlive(EAST);
  numNeighbors += board.isAlive(SOUTH);
  numNeighbors += board.isAlive(WEST);
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

char FredkinCell::name() {
  if(!alive)
    return '-';
  if(age > 9)
    return '+';
  return (char) (age + 0x30);
}
