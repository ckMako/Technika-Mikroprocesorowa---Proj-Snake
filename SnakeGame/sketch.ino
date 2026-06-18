#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "snake.h"

//wielkosc PIXELI
#define ROZMIAR_PIX 3


//init ekran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//init snake
snake Snake;

//init 3 pierwsze seg
setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);

//fruit init
fruit Fruit;
setFruit(Fruit);

//restart gry
bool gameOver=false;

//odswiezanie i drganie stykow
int repet = 50;
int debounceDEL =25; //15-30

//obsluga czasu odswiezania snakea
unsigned long lastTime = 0;

//obsluga buttons
bool leftBut=false;
bool righBut=false;

void setup() {
  /**
  * OLED wpinamy do
  * SDA -> A4 //data
  * SCL -> A5 //clock
  * 11 -> button left
  * 12 -> button right
  */

  pinMode(11, INPUT_PULLUP); //lewo - domyslnie HIGH, inaczej nie dziala
  pinMode(12, INPUT_PULLUP); //prawo

  //zaczyna wyswietlanie
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  //czysci pamiec OLED
  display.clearDisplay();

  // punkt w pozycji x=20, y=15
  display.drawPixel(20, 15, SSD1306_WHITE);

  //wiekszy rozmiar
  display.fillRect(12, 12, 4, 4, SSD1306_WHITE);

  //wyswietl
  display.display();
}

/**
 * @brief wyswietl weza oraz owoc
 */
int displSnake (snake &oSnake, fruit &oFruit) {

    //clear display
    display.clearDisplay();

    //make snake segments
    for(int i = 0; i<oSnake.CurrLen; i++) {
        display.fillRect(oSnake.segs[i].widt, oSnake.segs[i].heig, ROZMIAR_PIX, ROZMIAR_PIX, SSD1306_WHITE);
    }
    //make fruit
    display.fillRect(oFruit.widt, oFruit.heig, ROZMIAR_PIX, ROZMIAR_PIX, SSD1306_WHITE);

    display.display();
}


/**
*Potrzebne sa min 2 przyciski, lewo-prawo
*przod i tyl i tak beda ignorowane
*(nie mozna zrobic 0deg i 180deg)
*/
void loop() {

  //przesun weza co repetetition
  if (millis() - lastTime > repet) { //millis() -> czas pracy
    lastTime = millis();
    goSnake();
  }

//read - musi byc duzo czesciej niz repetetition
  leftBut=digitalRead(11);
  delay(debounceDEL); //debounce 
  righBut=digitalRead(12);
  delay(debounceDEL); //debounce 
  if (leftBut != righBut) {
    if(leftBut)
      dir=changeDir(dir, true);
    else
      dir=changeDir(dir, false);

  }

//resetowanie po gameOver
  if (gameOver) {
      display.clearDisplay();
      heig=SCREEN_HEIGHT / 2; widt=SCREEN_WIDTH / 2;
      gameOver=false;
  }

}