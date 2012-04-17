#include <iostream>
#include <cassert>
#include <vector>


template <typename T>
class Life {
    private:
      vector< vector<T> > grid;
      void read(istream& in);
    
    public:
      Life(istream& in);
      void simulate(int numTurns);    
      void takeTurn();
      void print(ostream& out);
};

// Abstract cell
class AbstractCell {
    private:
      bool alive;
      int numNeighbors;
    
    public:
      virtual void countNeighbors() = 0;
      virtual void turn() = 0;
};

class Cell {};

class FredkinCell : AbstractCell {
    private:
      int age;
    public:
      FredkinCell() : age (0) {
      }
};

class ConwayCell : AbstractCell {
    
};

void Life::takeTurn() {
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++)
                grid[i][j].countNeighbors();
        
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++)
                grid[i][j].turn();
    }
    
void ConwayCell::turn() {
  if (numNeighbors == 3)
    alive = true;
  if (numNeighbors < 2 || numNeighbors > 3)
    alive = false;
}

void FredkinCell::turn() {
    if (numNeighbors % 2 == 1)
      alive = true;
    else
      alive = false;
    age++;
}
