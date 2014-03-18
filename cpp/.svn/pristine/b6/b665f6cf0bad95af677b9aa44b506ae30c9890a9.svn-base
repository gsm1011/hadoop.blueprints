#ifndef WORMS_H_
#define WORMS_H_

#include <cstdlib>
#include <string>
#include <unistd.h>
#include <time.h>
#include <cassert>
//using namespace ncurses; 
 
#define random(x)   (rand() % x)
#define isDigit(x)  ('0' <= x && x <= '9')
#define min(a, b)   ((a) < (b)? (a) : (b))
#define ESC     '\033'  // the ESCape char
#define CARROT      '.' // a carrot is shown as a dot
#define headSeg(wp) (wp->body + wp->getNsegs())
#define xOf(wp)     (headSeg(wp)->getX())
#define yOf(wp)     (headSeg(wp)->getY())
 
#define MAXworms 100        // max # worms in our program
#define MAXsegs  100        // max # segments per worm

#define MAXrow 100
#define MAXcol 100
#define asog(ptr, row, col) (ptr + row*asogCols + col)
 
#include <ncurses.h>
#define mvCursor(y, x) move(y, x)
#define putChar(c) addch(c)
#define putString(s) addstr(s)
#define getChar() getch()
#define screenFlush() refresh()
#define screenClear() clear()
#define EOLN "\n"       // End Of LiNe string
#define Nsay sizeof(say)/sizeof(char *) // #sayings we have

typedef enum {
  NORTH, NORTHEAST, EAST, SE, S, SW, W, NW
} DIRECTION;

class ASOG{
private:
  int onec, attr;
public:
  void setOnec(int onec){
    this->onec = onec;
  }
  int getOnec(){
    return this->onec;
  }
  void setAttr(int attr){
    this->attr = attr;
  }
  int getAttr(){
    return this->attr;
  }
};

// segment class. 
class Segment {
private:
  int x, y;
  char c;
public:
		
  int getX(){
    return this->x;		
  }
  void setX(int x){
    this->x = x;
  }
  int getY(){
    return this->y;
  }
  void setY(int y){
    this->y = y;
  }
  void setC(char c){
    this->c = c;
  }
  char getC(){
    return this->c;
  }
};

/* worm class. */
class Worm {
 private:
  enum WORM_KIND {
    VEGETARIAN, CANNIBAL, SCISSORHEAD
  }; 
  enum LIFE {
    EATEN, DEAD, ALIVE
  };

  WORM_KIND type;       // once set, type does not change
  int direction;        // its (head's) direction
  int nsegs;            // # of segs in this worm
  int stomach;          // food value
  LIFE status;          // EATEN, DEAD, or ALIVE
  SEGMENT body[MAXsegs]; 

  // worm info. 
  int color;
  int capacity;         // stomach size
  int foodValue;

 public: 
  // constructors and destructors. 
  Worm(); 
  Worm(const char * sy); 

  // setters and getters here.
int getColor(){
    return this->color;
  }
  int getCapacity(){
    return this->capacity;
  }
  int getFoodValue(){
    return this->foodValue;
  }
  void setColor(int color){
    this->color = color;
  }
  void setCapacity(int capacity){
    this->capacity = capacity;
  }
  void setFoodValue(int foodValue){
    this->foodValue = foodValue;
  } 
  // methods. 
  void showOneWorm(); 
  void showWormsAndCarrots(); 
  int isHungry();
  void gotEaten();
  void checkStomach(); 
  virtual void eatACarrot(); 
  int isAt(int row, int col);
  void setVictimWorm();
  void shiftBodyDown(int vsn); 
  Worm * sliceTheVictim(int vsn);
  virtual void eat();
  void live();
}; 

class  VegiWorm : public Worm {
 public: 
  // constructors. 
  VegiWorm() {
    type = VEGETARIAN;
    color = COLOR_PAIR(1); 
    capacity = 3; 
    foodValue = 3; 
  } 
 VegiWorm(const char *sy):Worm(sy) {
    type = VEGETARIAN; 
    color = COLOR_PAIR(1); 
    capacity = 3; 
    foodValue = 3; 
  } 

  void sprinkleCarrots();

};

class CanniWorm : public Worm {
 public: 
  CanniWorm() {
    type = CANNIBAL;
    color = COLOR_PAIR(2); 
    capacity = 4; 
    foodValue = 5; 
  }
  CanniWorm(const char *sy); 
};

class ScissorHeadWorm : public Worm {
 public: 
  ScissorHeadWorm() { type = SCISSORHEAD; }
}; 

class UiControl {
 private: 
  const char * say[];
  enum DIRECTION {
    NORTH, NORTHEAST, EAST, SE, S, SW, W, NW
  } ; 
 
  // dx/dy changes, indexed by DIRECTION; (+0 just to line up)
  const int dxa[] = { +0, +1, +1, +1, +0, -1, -1, -1 };
  const int dya[] = { -1, -1, +0, +1, +1, +1, +0, -1 };
 
  const int nextTurn[16] = {  // experiment with other values
    0, 0, 0, 0,  0, 0, 0, 0,  // think: why 16?
    1, 1, 1, 7,  7, 7, 2, 6
  };

  /* parameters for the 'graphical' (such as it is) display */
  int slowness;           // slowness number
  int paused = 0;         // == 1 iff paused
  int idelay = 10;        // delay increment
  int tdelay;         // total delay yet to do

  Worm worm[MAXworms];        // vars for the worms
  int hxWorms;            // high water mark of the worm[]
  int xworms[3];          // counts of different worms

  // worm info on the UI. 
  ASOG passive[MAXrow * MAXcol];  // for carrots and dead worms
  ASOG screen[MAXrow * MAXcol];   // what gets displayed
  int asogRows, asogCols;     // the actual size of 'worm area'
  char msg[1024];

  /* The following two vars should be 'out' parameters (var params), but
     for ease of understanding, let us declare these as globals. */
  WORM *victimWormp;
  int victimSegNum;
  
 public: 
  // constructors. 
  say = {      // worms carry these strings
  "do-not-optimize-too-soon*",
  "If it does not have to be correct, making the program efficient is easy.",
  "90% of code executes only 10% of the time!",
  "Is there a program, longer than say 1000 lines, that is correct?",
  "OS is not bug-free, the compiler is not bug-free, so is my program!",
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
  "98765432109876543210*",
  "Edsger-Dijkstra*",     // legendary programmers ...
  "C-A-R-Hoare*",
  "Donald-Knuth*",
  "Richard-Stallman*",
  "Linux-Torvalds*",
 };
  
  // getters and setters.
  int getNumVegeWorms() { return xworms[0]; }
  int getNumCanniWorms() { return xworms[1]; }
  int getNumScissorHeadWorms() { return xworms[2]; }

  int getAllWorms() { return xworms[0] + xworms[1] + xworms[2];  }

  // ui control. 
  void endCurses();
  void startCurses();

  int getOneChar();
  void showScreen();
  void showMsg(int y);

  // for user interface operations. 
  int userKeyPress(int c); 
  int userControl();

  Worm * findSlot(); 
};

#endif
