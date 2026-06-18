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

/**
 * petle musza ustawiac nowy head i kopiowac wszystkie inne elem
 */
bool goSnake (snake &Obj) {
    moveSnake(Obj);

  switch (Obj.dir*3) {

    case 12: //gora
    case 0 : //gora
        Obj.segs[0].heig--;
    //   heig--; //na OLED -- idzie w gore,
        break;

    case 3 : //prawo
        Obj.segs[0].widt++;
    //   widt++;
      break;

    case 6 :  //dol
        Obj.segs[0].heig++;
    //   heig++;
      break;

    case 9 : //prawo
        Obj.segs[0].widt--;
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

void addSegm(snake &Obj, int aHei, int aWid) {
    if(Obj.CurrLen<SnMAXsiz) {
        for (int i = Obj.CurrLen; i > 0; i--) {
            Obj.segs[i] = Obj.segs[i - 1];
        }
        Obj.segs[0].heig=aHei;
        Obj.segs[0].widt=aWid;
        Obj.CurrLen++;
    }
}

void moveSnake(snake &Obj) {
    if(Obj.CurrLen<SnMAXsiz) {
        for (int i = Obj.CurrLen-1; i > 0; i--) {
            Obj.segs[i] = Obj.segs[i - 1];
        }
    }
}

bool selfColl (snake &Obj){
    for(int i =Obj.CurrLen; i>0; i--) {
        if(Obj.segs[0].heig==Obj.segs[i].heig && Obj.segs[0].widt==Obj.segs[i].widt) {
        return true;
        }
    }
    return false;
}