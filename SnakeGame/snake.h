#pragma once

//max rozmiar weza
#define SnMAXsiz 10

//wymiary ekranu OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/**
 * @brief klasa segment weza
 */
struct snakeSeg{
    // uint_8
    int heig=0;
    int widt=0; //pozycja segm
}; 

/**
 * @brief snake tj tablica segmentow + aktualna dlugosc + kierunek
 */
struct snake{
  snakeSeg segs[SnMAXsiz];
  int CurrLen=3;
  int dir = 0; // 0 lub 4-gora, 1-prawo, 2-dol, 3-lewo
};

/**
 * @brief ustaw parametry weza
 * @param Obj ref do weza
 * @param seg numer segmentu weza
 * @param aheig wysokosc do ustaweina
 * @param awidt szer do ustawienia
 */
void setSeg(snake &Obj, int seg, int aheig, int awidt);


/**
 * @brief zmien kierunek weza
 * @param Obj ref do weza
 * @param ifRight czy skret w prawo
 */
void changeDir (snake &Obj, bool ifRight);

/**
 * @brief dodaj segment weza
 */
void addSegm(snake &Obj, int aHei, int aWid);

/**
 * @brief przesun pola tablicy segmentow o 1
 */
void moveSnake(snake &Obj);


/**
 * @brief 1 krok weza w dobra strone
 * @param Obj ref do snake
 * @return if gameOver --tj. czy wyszedl poza ekran
 */
bool goSnake (snake &Obj);

/**
 * @brief kolizja ze soba
 * @return true dla kollizji -- game Over;
 * @details najpierw dla każdego elementu porównujemy wysokośc, zamiast wys && szer, dzięki temu możemy odciąć połowę operacji od razu -- szybsze przetwarzanie
 */
bool selfColl (snake &Obj);
