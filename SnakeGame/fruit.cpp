#include "fruit.h"


void setFruit (fruit &Obj) {
  Obj.heig=rand()%(SCREEN_HEIGHT-padd)+padd;
//   =random(SCREEN_HEIGHT-padd)+(padd/2);
  Obj.widt=rand()%(SCREEN_WIDTH-padd)+padd;
}

//bool?
void ateFruit(snake &oSnake, fruit &oFruit) {
    if((oSnake[0].widt==oFruit.widt) &&  (oSnake[0].heig==oFruit.heig)) {
        //jak zwiekszac rozmiar weza??
        oSnake.CurrLen++;
        if(oSnake.CurrLen >= SnMAXsiz) {
            //VICTORY
        }
        setFruit(oFruit);
    }
//   return;
}