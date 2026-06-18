#include "snake.h"


void setSeg(snake &Obj, int seg, int aheig, int awidt) {
  if(seg<SnMAXsiz) {
    Obj.segs[seg].heig=aheig;
    Obj.segs[seg].widt=awidt;
  }
}

void changeDir (snake &Obj, bool ifRight) { //true -->right
    if (ifRight) {
        //go right
        Obj.dir = (Obj.dir + 1) % 4; //+1
    } else {
        //go left
        Obj.dir = (Obj.dir + 3) % 4; //-1
    }
}


bool goSnake (snake &Obj) {

  switch (Obj.dir*3) {
    case 12: //gora
    case 0 : //gora
        for (int i = Obj.CurrLen; i > 0; i--) {
            Obj.segs[i].heig--;
        }
    //   heig--; //na OLED -- idzie w gore,
      break;
    case 3 : //prawo
        for (int i = Obj.CurrLen; i > 0; i--) {
            Obj.segs[i].widt++;
        }
    //   widt++;
      break;
    case 6 :  //dol
        for (int i = Obj.CurrLen; i > 0; i--) {
            Obj.segs[i].heig++;
        }
    //   heig++;
      break;
    case 9 : //prawo
        for (int i = Obj.CurrLen; i > 0; i--) {
            Obj.segs[i].widt--;
        }
    //   widt--;
      break;
  }

  //czy snake wyszedl poza ekran
  if(Obj.segs[0].heig > SCREEN_HEIGHT || Obj.segs[0].heig < 0)
    return true;
  else if(Obj.segs[0].widt>SCREEN_WIDTH || Obj.segs[0].widt < 0)
    return true;
  else {
    return false;
  }
    // displSnake(2);
}