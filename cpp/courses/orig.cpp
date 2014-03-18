/*-
  worms.cpp -- A primitive game example of wiggly worms moving about
 
  (c) 2013 pmateti@wright.edu 
 
  Build it: 'g++ -o worms worms.cpp -lncurses'
  Run   it: './worms 3'
*/
 
// TBD  signals ^C
 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
#define random(x)   (rand() % x)
#define isDigit(x)  ('0' <= x && x <= '9')
#define min(a, b)   ((a) < (b)? (a) : (b))
#define ESC     '\033'  // the ESCape char
#define CARROT      '.' // a carrot is shown as a dot
 
const char * say[] = {      // worms carry these strings
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
#define Nsay sizeof(say)/sizeof(char *) // #sayings we have
 
typedef struct {
  int onec;         // one character
  int attr;         // its color
} ASOG;             // A Square On the Ground
 
typedef enum {
  NORTH, NORTHEAST, EAST, SE, S, SW, W, NW
} DIRECTION;            // as numbers: 0 .. 7
 
typedef enum {
  VEGETARIAN, CANNIBAL, SCISSORHEAD
} WORM_KIND;            // 0, 1, 2
 
typedef struct {
  int color;
  int capacity;         // stomach size
  int foodValue;
} WORM_INFO;
 
typedef enum {
  EATEN, DEAD, ALIVE
} LIFE;
 
typedef struct {
  int x, y;         // coordinates of the segment
  char c;           // the letter it carries
} SEGMENT;
 
#define MAXsegs  100        // max # segments per worm
typedef struct {
  WORM_KIND type;       // once set, type does not change
  int direction;        // its (head's) direction
  int nsegs;            // # of segs in this worm
  int stomach;          // food value
  LIFE status;          // EATEN, DEAD, or ALIVE
  SEGMENT body[MAXsegs];    // body parts
} WORM;
#define headSeg(wp) (wp->body + wp->nsegs)
#define xOf(wp)     (headSeg(wp)->x)
#define yOf(wp)     (headSeg(wp)->y)
 
#define MAXworms 100        // max # worms in our program
WORM worm[MAXworms];        // vars for the worms
int hxWorms;            // high water mark of the worm[]
int xworms[3];          // counts of different worms
#define nVegetarians    xworms[0]
#define nCannibals  xworms[1]
#define nScissors   xworms[2]
#define nAllWorms   (nVegetarians + nCannibals + nScissors)
 
#define MAXrow 100
#define MAXcol 100
ASOG passive[MAXrow * MAXcol];  // for carrots and dead worms
ASOG screen[MAXrow * MAXcol];   // what gets displayed
int asogRows, asogCols;     // the actual size of 'worm area'
#define asog(ptr, row, col) (ptr + row*asogCols + col)
 
#include <ncurses.h>
#define mvCursor(y, x) move(y, x)
#define putChar(c) addch(c)
#define putString(s) addstr(s)
#define getChar() getch()
#define screenFlush() refresh()
#define screenClear() clear()
#define EOLN "\n"       // End Of LiNe string
 
void endCurses()
{
  if (!isendwin())
    endwin();
}
 
void startCurses()
{
  initscr();            // ncurses init
  cbreak();         // unbuffered getChar
  noecho();         // no echoing of keys pressed
  //  intrflush(stdscr, 0); // TBD
  nodelay(stdscr, TRUE);    // get a char *if* available
  atexit(endCurses);
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_GREEN, -1);
  init_pair(3, COLOR_BLUE, -1);
  getmaxyx(stdscr, asogRows, asogCols);
  if (asogCols > MAXcol) asogCols = MAXcol;
  if (asogRows > MAXrow) asogRows = MAXrow;
  asogRows -= 6;     // 6 lines for msgs, asogRows needs to be > 0
}
 
int getOneChar()
{
  nodelay(stdscr, FALSE);   // wait until a char is typed
  int c =  getChar();
  nodelay(stdscr, TRUE);
  return c;
}
 
// ncurses code ends here
 
void showScreen()
{
  ASOG * sp = screen;
  for (int y = 0; y < asogRows; y++) {
    mvCursor(y, 0);
    for (int x = 0; x < asogCols; x++, sp++)
      putChar(sp->onec | sp->attr);
  }
  screenFlush();
}
 
char msg[1024];
 
void showMsg(int y)
{
  msg[1023] = '\0';
  mvCursor(y, 0);
  putString(msg);
  screenFlush();
}
 
void sprinkleCarrots()
{
  for(ASOG *p = asog(passive, asogRows, 1); p-- > passive;) {
    p->attr = WA_DIM;
    p->onec = CARROT;
  }
}
 
WORM_INFO worm_info[] = {   // indexed by WORM_KIND
  {COLOR_PAIR(1), 3, 3},    // from <ncurses.h>
  {COLOR_PAIR(2), 4, 5},
  {COLOR_PAIR(3), 5, 4}
};
 
/* Show a single worm.  pre: wp != 0.  post: It is drawn on passive[]
   if it is dead.  If alive, it is drawn on screen[].  If eaten, not
   drawn. ; */
 
void showOneWorm(WORM * wp)
{
  if (wp->status != EATEN) {
    ASOG *f = (wp->status == ALIVE ? screen : passive);
    SEGMENT *bp, *hp = headSeg(wp);
    for (bp = wp->body + 1; bp <= hp; bp++) {
      ASOG *g = asog(f, bp->y, bp->x);
      g->attr = worm_info[wp->type].color;
      g->onec = bp->c;
    }
  }
}
 
/* Display the carrots, the dead worms, and the current positions of
   one (pre: wp != 0) or all (pre: wp == 0) worms.  globals: passive[]
   read-only.  pre: none; post: ... ; */
 
void showWormsAndCarrots(WORM * wp)
{
  ASOG *sp = screen, *se = asog(screen, asogRows, 1);
  for (ASOG *pp = passive; sp < se; )
    *sp++ = *pp++;      // copy the carrots + dead worms
  WORM * headWorm = worm + (wp? 1 : hxWorms);
  for (WORM * wp = worm; wp < headWorm; )
    showOneWorm(wp++);
  showScreen();
}
 
/* It is hungry if its tummy is at least 25% empty.  pre: wp != 0;
   post: Return 1 if worm wp is hungry; otherwise return 0.  */
 
int isHungry(WORM * wp)
{
  int m = wp->stomach;
  int n = wp->nsegs * worm_info[wp->type].capacity;
  return (wp->status == ALIVE && 4*m < 3*n);
}
 
/* pre: wp != 0 */
 
void gotEaten(WORM * wp)
{
  if (wp->status == ALIVE) {
    wp->status = EATEN;
    xworms[wp->type] --;
  }
}
 
/* pre: wp->status == ALIVE; post: if stomach is 0 or less, mark it
   dead, and send its body to the cemetary. */
 
void checkStomach(WORM * wp)
{
  if (wp->stomach <= 0) {
    wp->status = DEAD;
    xworms[wp->type] --;
    showOneWorm(wp);        // mv the body to passive
  }
}
 
/* Eat a carrot, if available.  pre: wp->status == ALIVE; post:
   ...; */
 
void eatACarrot(WORM * wp)
{
  ASOG *sg = asog(passive, yOf(wp), xOf(wp));
  if (CARROT == sg->onec) {
    wp->stomach += 2;        // food value of one carrot
    sg->onec = ' ';
  }
}
 
/* Check if any segment of worm wp is at (col, row).  Return this
   segment's number.  Recall that body[0] is just an eraser-blank, not
   really a part of the worm.  pre: wp != 0; post: ...; */
 
int isAt(WORM * wp, int row, int col)
{
  SEGMENT *bp = headSeg(wp);
  for (int sn = wp->nsegs; sn > 0; sn--, bp--)
    if ((bp->y == row) && (bp->x == col))
      return sn;
}
 
/* The following two vars should be 'out' parameters (var params), but
   for ease of understanding, let us declare these as globals. */
 
WORM *victimWormp;
int victimSegNum;
 
/* Find a worm that is on the same square as "my" head.  pre: me != 0;
   post: victimSegNum > 0 => victimWormp != 0 and victimWormp's
   victimSegNum segment is at the same square as the head of me.  */
 
void setVictimWorm(WORM * me)
{
  WORM *headWorm = worm + hxWorms, *wp;
  victimWormp = 0;
  victimSegNum = 0;
  for (wp = worm; wp < headWorm; wp++) {
    if (wp != me && wp->status == ALIVE) {
      victimSegNum = isAt(wp, yOf(me), xOf(me));
      if (victimSegNum > 0) {
    victimWormp = wp;
    return;         // found the victim
      }
    }
  }
}
 
/* We have a new worm about to join.  Find a slot for it in our worm[]
   array.  pre: 0 <= hxWorms <= MAXworms; post: Return a ptr to a slot
   for the new work, or 0, if we do not succeed in finding a slot.  */
 
WORM * findSlot()
{
  WORM * zp = worm + hxWorms;
  if (hxWorms < MAXworms) {
    hxWorms++;
    return zp;
  }
  /* see if there are any dead/eaten worms */
  for (WORM * wp = worm; wp < zp; wp++)
    if (wp->status != ALIVE)
      return wp;
  return 0;
}
 
/* Copy the body segments.  pre: vp != 0 && 0 < vsn <= vp->nsegs;
   post: old body[vsn+1..end] should become new body[1..new-length];
   body[0] remains as the eraser-blank */
 
void shiftBodyDown(WORM * vp, int vsn)
{
  SEGMENT *dp = vp->body + 1;        // dp destination, sp source
  SEGMENT *hp = headSeg(vp);
  for (SEGMENT *sp = vp->body + vsn + 1; sp <= hp; )
    *dp++ = *sp++;
  int tsegs = vp->nsegs;
  vp->nsegs -= vsn;
  vp->stomach = vp->stomach / tsegs * vp->nsegs;
  checkStomach(vp);
}
 
/* A scissor-head or cannibal hit the victim at segment number vsn.
   Slice the victim into two.  pre: vp != 0 && 0 < vsn <= vp->nsegs;
   post: The first one with vp->body[1..vsn-1] and the second one with
   vp->body[vsn+1..vp->nsegs] as its new body.  */
 
WORM * sliceTheVictim(WORM * vp, int vsn)
{
  int tsegs = vp->nsegs;
  WORM *wp = findSlot();
  if (wp == 0)          // could not find a slot
    return vp;
 
  xworms[vp->type]++;
 
  *wp = *vp;            // bottom-half
  wp->nsegs = vsn - 1;
  wp->stomach = vp->stomach / tsegs * wp->nsegs;
  checkStomach(wp);
 
  shiftBodyDown(vp, vsn);   // the top-half
  return wp;
}
 
/* Eat whatever you find at the wp's head position.  If wp is a
   cannibal or scissor-head it will also eat a carrot, if available.
   Update the stomach contents.  pre: isHungry(wp) && wp->status ==
   ALIVE; post: ...; */
 
void eat(WORM * wp)
{
  if (wp->type != VEGETARIAN) {
    setVictimWorm(wp);
    if (victimWormp != 0) {
      wp->stomach += worm_info[victimWormp->type].foodValue;
      WORM * zp = sliceTheVictim(victimWormp, victimSegNum);
      if (wp->type == CANNIBAL && zp->status == ALIVE) {
    wp->stomach += zp->nsegs * worm_info[zp->type].foodValue;
    gotEaten(zp);
      }
    }
  }
  eatACarrot(wp);
}
 
// dx/dy changes, indexed by DIRECTION; (+0 just to line up)
const int dxa[] = { +0, +1, +1, +1, +0, -1, -1, -1 };
const int dya[] = { -1, -1, +0, +1, +1, +1, +0, -1 };
 
const int nextTurn[16] = {  // experiment with other values
  0, 0, 0, 0,  0, 0, 0, 0,  // think: why 16?
  1, 1, 1, 7,  7, 7, 2, 6
};
 
/* One moment in the life of a worm: crawl by one step using one unit
   of food, may change direction, eat if hungry, mark as dead if
   stomach is now empty.  */
 
void live(WORM * wp)
{
  SEGMENT *hp = headSeg(wp);
  for (SEGMENT * bp = wp->body; bp < hp; bp++) // < not <=
    bp->x = (bp + 1)->x, bp->y = (bp + 1)->y;  // crawl
 
  int dir = wp->direction = (wp->direction + nextTurn[random(16)]) % 8;
  hp->y += dya[dir];
  hp->x += dxa[dir];
  if (hp->y < 0) hp->y = asogRows-1;
  if (hp->x < 0) hp->x = asogCols-1;
  if (hp->y >= asogRows) hp->y = 0;
  if (hp->x >= asogCols) hp->x = 0;
 
  wp->stomach--;
  if (isHungry(wp))
    eat(wp);
  checkStomach(wp);
}
 
/* Create a worm.  It should be just long enough to carry the phrase
   sy[].  It is going to crawl out of a random hole.  pre: s != 0;
   post: ...; */
 
void createWorm(WORM_KIND type, const char * sy)
{
  WORM *wp = findSlot();
  if (wp == 0)
    return;         // no room for a new worm
 
  int n = wp->nsegs = min(strlen(sy), MAXsegs - 1);
  wp->stomach = n * worm_info[type].capacity;
  wp->direction = NORTH;
  wp->status = ALIVE;
  wp->type = type;
 
  SEGMENT * bp = wp->body;
  int yy = bp->y = random(asogRows); // birth place of this worm
  int xx = bp->x = random(asogCols);
  bp->c = ' ';               // works as an "eraser"
 
  SEGMENT * hp = headSeg(wp);
  for (bp++; bp <= hp; bp++) {
    bp->c = *sy++;       // store the phrase s[]
    bp->x = xx;          // worm hangs down in the z-axis
    bp->y = yy;
  }
  xworms[type] ++;
}
 
/* parameters for the 'graphical' (such as it is) display */
int slowness;           // slowness number
int paused = 0;         // == 1 iff paused
int idelay = 10;        // delay increment
int tdelay;         // total delay yet to do
 
int userKeyPress(int c)
{
  switch (c) {
  case '+': slowness -= min(slowness, 100); break;
  case '-': slowness += 100; break;
  case 'f': slowness = 0; break;
  case 's': /* for you todo: highlight a worm */ break;
  case 'k': /* for you todo: kill the highlighted worm */ break;
  case 'w': createWorm((WORM_KIND)random(3), say[random(Nsay)]); break;
  case ' ': paused ^= 1; break;
  }
  return c;
}
 
/* User can control the speed, etc.  The total delay required, tdelay,
   is doled out in increments of idelay so that keyboard interaction
   is more responsive.  pre: none; post: returns ESC or '\0';; */
 
int userControl()
{
  sprintf
    (msg, 
     "SPC %s, ESC terminates, k kills-, w creates-, s shows-a-worm" EOLN
     "%2d Vegetarians,%2d Cannibals,%2d Scissor-heads,%2d hi-water-mark" EOLN
     "%04d slowness, - increases, + reduces, f full-speed" EOLN,
     (paused? "resumes" : "pauses "), 
     nVegetarians, nCannibals, nScissors, hxWorms, slowness);
  showMsg(asogRows + 1);
  for (tdelay = slowness+1; tdelay > 0; tdelay -= idelay) {
    char c = userKeyPress(getChar()); // no-delay
    if (c == ESC) return ESC;
    if (paused) tdelay += idelay;
    if (idelay > 0)
      usleep(1000 * idelay);
  }
  return '\0';
}
 
int main(int argc, char * argv[])
{
  slowness = 10*(argc > 1? argv[1][0] - '0' : 1);
  if (slowness < 0) slowness = 0;
  srand(time(0));       // pseudo-random number generator seed
  for (int ch = 0; ch != ESC; ) {
    startCurses();
    sprinkleCarrots();
    hxWorms = nVegetarians = nCannibals = nScissors = 0;
    for (int i = random(6) + 3; i > 0; i--)
      createWorm((WORM_KIND) random(3), say[random(Nsay)]);
 
    while (ch != ESC && nAllWorms > 0) {
      for (WORM * wp = worm; wp < worm + hxWorms; wp++) // hxWorms may +-
    if (wp->status == ALIVE)
      live(wp);
      showWormsAndCarrots(0);
      ch = userControl();
    }
 
    sprintf(msg, "press ESC to terminate, or any other key to re-run"
        EOLN  EOLN  EOLN  EOLN);
    showMsg(asogRows + 1);
    ch = getOneChar();
    endCurses();
  }
  return 0;
}
 
/* -eof- */
