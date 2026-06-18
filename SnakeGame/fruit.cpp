#include "fruit.h"




void setFruit (fruit &Obj) {
  Obj.heig=rand()%(SCREEN_HEIGHT-2*Obj.padd)+Obj.padd;
//   =random(SCREEN_HEIGHT-padd)+(padd/2);
  Obj.widt=rand()%(SCREEN_WIDTH-2*Obj.padd)+Obj.padd;
}

//bool?
bool ateFruit(snake &oSnake, fruit &oFruit) {
    if((oSnake.segs[0].widt <= oFruit.widt + oFruit.siz) && (oSnake.segs[0].widt >= oFruit.widt - oFruit.siz) ) {
        if ((oSnake.segs[0].heig <= oFruit.heig + oFruit.siz) && (oSnake.segs[0].heig >= oFruit.heig - oFruit.siz)) {
        //jak zwiekszac rozmiar weza??
        oSnake.CurrLen++;
        if(oSnake.CurrLen >= SnMAXsiz) {
            return true;
        }
        setFruit(oFruit);
    }
    }
  return false;
}