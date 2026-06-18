#pragma once

#include "snake.h"

/**
 * @brief owoc dla weza, zjedzenie zwieksza dl weza
 */
struct fruit{
    // uint_8
    int heig=30;
    int widt=30; //pozycja segm
    int padd=10; //padding
}; 

/**
 * @brief wylosuj nowa pozycje weza
 */
void setFruit (fruit &Obj);

/**
 * @brief zwieksz rozmiar weza jezeli zje owoc
 */
//bool?
void ateFruit(snake &oSnake, fruit &oFruit);

