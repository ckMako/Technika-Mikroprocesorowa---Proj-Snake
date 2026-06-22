#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "snake.h"
#include "fruit.h"

//wielkosc PIXELI
#define ROZMIAR_PIX 3


//init ekran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//init snake
snake Snake;

//fruit init
fruit Fruit;


//restart gry
bool gameOver=false;
bool victory = false;

//odswiezanie i drganie stykow
int repet = 50;
int debounceDEL =150; //15-30

//obsluga czasu odswiezania snakea
unsigned long lastTime = 0;


void setup() {
  /**
  * OLED wpinamy do
  * SDA -> A4 //data
  * SCL -> A5 //clock
  * 2 -> button left
  * 3 -> button right
  */

  /*
  display score
  display victory or loose
  check collision with yourself+
  interruption+
  
  */

  pinMode(2, INPUT_PULLUP); //lewo - domyslnie HIGH, inaczej nie dziala
  pinMode(3, INPUT_PULLUP); //prawo

  //interruption
  //TYLKO PINY 2 i 3 OBSLUGUJA PRZERWANIA
  attachInterrupt(digitalPinToInterrupt(2), interLEFT, FALLING);//lewo//falling -> czytamy LOW
  attachInterrupt(digitalPinToInterrupt(3), interrRIGHT, FALLING); //prawo

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

  //init pozycji Snake i Fruit
  setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
  setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
  setSeg(Snake, 2, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);
  Snake.CurrLen=3;
  setFruit(Fruit);
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
    display.fillRect(oFruit.widt, oFruit.heig, ROZMIAR_PIX*2, ROZMIAR_PIX*2, SSD1306_WHITE);

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

    //czy wyszedl poza ekran
    gameOver=goSnake(Snake);

    //czy zderzyl sie ze soba
    if(!gameOver) {
      gameOver=selfColl(Snake);
    }
    displSnake(Snake, Fruit);
    victory=ateFruit(Snake, Fruit);
  }


//resetowanie po gameOver
  if (gameOver) {

      //reset poz weza
      setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
      setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
      setSeg(Snake, 2, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);
      Snake.CurrLen=3;
      setFruit(Fruit);
  }

//resetowanie po victory
  if (victory) {

      //reset poz weza
      setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
      setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
      setSeg(Snake, 2, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);
      Snake.CurrLen=3;
      setFruit(Fruit);
  }

}

/**
 * @brief przerwanie LEWE
 * @details po przerwaniu zmienia kieruneka na lewo
 * zmienna debounce określa co ile czytamy -- redukcja drgania stykow
 */
void interLEFT() {
  static unsigned long lastTimeLEFT;
  if (millis() - lastTimeLEFT < debounceDEL)
    return;
  changeDir(Snake, false);
  lastTimeLEFT=millis();
}

/**
 * @brief przerwanie PRAWE
 * analogicznie
 */
void interrRIGHT() {
  static unsigned long lastTimeRIGHT;
  if (millis() - lastTimeRIGHT < debounceDEL)
    return;

  changeDir(Snake, true);
  lastTimeRIGHT=millis();
}

