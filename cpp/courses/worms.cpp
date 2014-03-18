/*-
  worms.cpp -- A primitive game example of wiggly worms moving about
 
  (c) 2013 pmateti@wright.edu 
 
  Build it: 'g++ -o worms worms.cpp -lncurses'
  Run   it: './worms 3'
*/
 
// TBD  signals ^C
#include "worms.h"
using namespace std; 

///////////////////////////////////////////
// Implementation of UiControl class.
///////////////////////////////////////////

void UiControl::endCurses()
{
  if (!isendwin())
    endwin();
}
 
void UiControl::startCurses()
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
 
int UiControl::getOneChar()
{
  nodelay(stdscr, FALSE);   // wait until a char is typed
  int c =  getChar();
  nodelay(stdscr, TRUE);
  return c;
}
 
// ncurses code ends here
 
void UiControl::showScreen()
{
  ASOG * sp = screen;
  for (int y = 0; y < asogRows; y++) {
    mvCursor(y, 0);
    for (int x = 0; x < asogCols; x++, sp++)
      putChar(sp->getOnec() | sp->getAttr());
  }
  screenFlush();
}
 
void UiControl::showMsg(int y)
{
  msg[1023] = '\0';
  mvCursor(y, 0);
  putString(msg);
  screenFlush();
}

void UiControl::sprinkleCarrots()
{
  for(ASOG *p = asog(passive, asogRows, 1); p-- > passive;) {
    p->setAttr(WA_DIM);
    p->setOnec(CARROT);
  }
}
 
///////////////////////////////////////////////////////////
// Implementation of worm classes. 
///////////////////////////////////////////////////////////

/* Show a single worm.  pre: wp != 0.  post: It is drawn on passive[]
   if it is dead.  If alive, it is drawn on screen[].  If eaten, not
   drawn. ; */
 
void Worm::showOneWorm()
{
  if (wp->getStatus() != EATEN) {
    ASOG *f = (wp->getStatus() == ALIVE ? screen : passive);
    SEGMENT *bp, *hp = headSeg(wp);
    for (bp = wp->body + 1; bp <= hp; bp++) {
      ASOG *g = asog(f, bp->getY(), bp->getX());
      g->setAttr(worm_info[wp->getType()].getColor());
      g->setOnec(bp->getC());
    }
  }
}
 
/* Display the carrots, the dead worms, and the current positions of
   one (pre: wp != 0) or all (pre: wp == 0) worms.  globals: passive[]
   read-only.  pre: none; post: ... ; */
void Worm::showWormsAndCarrots()
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
 
int Worm::isHungry()
{
  int m = wp->getStomach();
  int n = wp->getNsegs() * wp->worm_info[wp->getType()].getCapacity();
  return (wp->getStatus() == ALIVE && 4*m < 3*n);
}
 
/* pre: wp != 0 */
void Worm::gotEaten()
{
  if (wp->getStatus() == ALIVE) {
    wp->setStatus(EATEN);
    xworms[wp->getType()] --;
  }
}
 
/* pre: wp->status == ALIVE; post: if stomach is 0 or less, mark it
   dead, and send its body to the cemetary. */
void Worm::checkStomach()
{
  if (wp->getStomach() <= 0) {
    wp->setStatus(DEAD);
    xworms[wp->getType()] --;
    showOneWorm(wp);        // mv the body to passive
  }
}
 
/* Eat a carrot, if available.  pre: wp->status == ALIVE; post:
   ...; */
 
void eatACarrot(WORM * wp)
{
  ASOG *sg = asog(passive, yOf(wp), xOf(wp));
  if (CARROT == sg->getOnec()) {
    wp->setStomach(wp->getStomach() + 2);        // food value of one carrot
    sg->setOnec(' ');
  }
}
 
/* Check if any segment of worm wp is at (col, row).  Return this
   segment's number.  Recall that body[0] is just an eraser-blank, not
   really a part of the worm.  pre: wp != 0; post: ...; */
 
int Worm::isAt(int row, int col)
{
  SEGMENT *bp = headSeg(wp);
  for (int sn = wp->getNsegs(); sn > 0; sn--, bp--)
    if ((bp->getY() == row) && (bp->getX() == col))
      return sn;
}
 

 
/* Find a worm that is on the same square as "my" head.  pre: me != 0;
   post: victimSegNum > 0 => victimWormp != 0 and victimWormp's
   victimSegNum segment is at the same square as the head of me.  */
 
void Worm::setVictimWorm()
{
  WORM *headWorm = worm + hxWorms, *wp;
  victimWormp = 0;
  victimSegNum = 0;
  for (wp = worm; wp < headWorm; wp++) {
    if (wp != me && wp->getStatus() == ALIVE) {
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
WORM * UiControl::findSlot()
{
  WORM * zp = worm + hxWorms;
  if (hxWorms < MAXworms) {
    hxWorms++;
    return zp;
  }
  /* see if there are any dead/eaten worms */
  for (WORM * wp = worm; wp < zp; wp++)
    if (wp->getStatus() != ALIVE)
      return wp;
  return 0;
}
 
/* Copy the body segments.  pre: vp != 0 && 0 < vsn <= vp->nsegs;
   post: old body[vsn+1..end] should become new body[1..new-length];
   body[0] remains as the eraser-blank */
 
void Worm::shiftBodyDown(int vsn)
{
  SEGMENT *dp = vp->body + 1;        // dp destination, sp source
  SEGMENT *hp = headSeg(vp);
  for (SEGMENT *sp = vp->body + vsn + 1; sp <= hp; )
    *dp++ = *sp++;
  int tsegs = vp->getNsegs();
  vp->setNsegs(vp->getNsegs() - vsn);
  vp->setStomach(vp->getStomach() / tsegs * vp->getNsegs());
  checkStomach(vp);
}
 
/* A scissor-head or cannibal hit the victim at segment number vsn.
   Slice the victim into two.  pre: vp != 0 && 0 < vsn <= vp->nsegs;
   post: The first one with vp->body[1..vsn-1] and the second one with
   vp->body[vsn+1..vp->nsegs] as its new body.  */
 
WORM * Worm::sliceTheVictim(int vsn)
{
  int tsegs = vp->getNsegs();
  WORM *wp = findSlot();
  if (wp == 0)          // could not find a slot
    return vp;
 
  xworms[vp->getType()]++;
 
  *wp = *vp;            // bottom-half
  wp->setNsegs(vsn - 1);
  wp->setStomach(vp->getStomach() / tsegs * wp->getNsegs());
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
  if (wp->getType() != VEGETARIAN) {
    setVictimWorm(wp);
    if (victimWormp != 0) {
      wp->setStomach(wp->getStomach() +worm_info[victimWormp->getType()].getFoodValue());
      WORM * zp = sliceTheVictim(victimWormp, victimSegNum);
      if (wp->getType() == CANNIBAL && zp->getStatus() == ALIVE) {
	wp->setStomach(wp->getStomach()+ zp->getNsegs() * worm_info[zp->getType()].getFoodValue());
	gotEaten(zp);
      }
    }
  }
  eatACarrot(wp);
}
 
/* One moment in the life of a worm: crawl by one step using one unit
   of food, may change direction, eat if hungry, mark as dead if
   stomach is now empty.  */
 
void Worm::live()
{
  SEGMENT *hp = headSeg(wp);
  for (SEGMENT * bp = wp->body; bp < hp; bp++) // < not <=
    bp->setX((bp + 1)->getX()), bp->setY((bp + 1)->getY());  // crawl
 
  wp->setDirection((wp->getDirection() + nextTurn[random(16)]) % 8);
  int dir = wp->getDirection();
  hp->setY(hp->getY()+dya[dir]);
  hp->setX(hp->getX()+dxa[dir]);
  if (hp->getY() < 0) hp->setY(asogRows-1);
  if (hp->getX() < 0) hp->setX(asogCols-1);
  if (hp->getY() >= asogRows) hp->setY(0);
  if (hp->getX() >= asogCols) hp->setX(0);
 
  wp->setStomach(wp->getStomach()-1);
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
 
  wp->setNsegs(min(strlen(sy), MAXsegs - 1));
  int n = wp->getNsegs();
  wp->setStomach(n * worm_info[type].getCapacity());
  wp->setDirection(NORTH);
  wp->setStatus(ALIVE);
  wp->setType(type);
 
  SEGMENT * bp = wp->body;
  bp->setY(random(asogRows)); // birth place of this worm
  int yy = bp->getY();
  bp->setX(random(asogCols));
  int xx = bp->getX();
  bp->setC(' ');               // works as an "eraser"
 
  SEGMENT * hp = headSeg(wp);
  for (bp++; bp <= hp; bp++) {
    bp->setC(*sy++);       // store the phrase s[]
    bp->setX(xx);          // worm hangs down in the z-axis
    bp->setY(yy);
  }
  xworms[type] ++;
}

int UiControl::userKeyPress(int c)
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
 
int UiControl::userControl()
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
	if (wp->getStatus() == ALIVE)
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

