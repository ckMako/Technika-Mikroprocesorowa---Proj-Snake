#include "fruit.h"

#include <stdlib.h>


void setFruit (fruit &Obj) {
  Obj.heig=rand()%(SCREEN_HEIGHT-2*Obj.padd)+Obj.padd;
//   =random(SCREEN_HEIGHT-padd)+(padd/2);
  Obj.widt=rand()%(SCREEN_WIDTH-2*Obj.padd)+Obj.padd;
}

//bool?
void ateFruit(snake &oSnake, fruit &oFruit) {
    if((oSnake.segs[0].widt==oFruit.widt) &&  (oSnake.segs[0].heig==oFruit.heig)) {
        //jak zwiekszac rozmiar weza??
        oSnake.CurrLen++;
        if(oSnake.CurrLen >= SnMAXsiz) {
            //VICTORY
        }
        setFruit(oFruit);
    }
//   return;
}