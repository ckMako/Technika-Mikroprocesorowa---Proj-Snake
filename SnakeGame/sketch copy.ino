#include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
/*
EduTar
*/
#include <Adafruit_SH110X.h>
#include <Wire.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//end

#include "snake.h"
#include "fruit.h"

//wielkosc PIXELI
#define ROZMIAR_PIX 3


//init ekran OLED
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
/*
EduTar
*/
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//end

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


  pinMode(2, INPUT_PULLUP); //lewo - domyslnie HIGH, inaczej nie dziala
  pinMode(3, INPUT_PULLUP); //prawo

  //interruption
  //TYLKO PINY 2 i 3 OBSLUGUJA PRZERWANIA
  attachInterrupt(digitalPinToInterrupt(2), interLEFT, FALLING);//lewo//falling -> czytamy LOW
  attachInterrupt(digitalPinToInterrupt(3), interrRIGHT, FALLING); //prawo

  Serial.begin(9600);
  //zaczyna wyswietlanie
  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.begin(i2c_Address, true); // Address 0x3C default

  //clear buffer
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(25, 5);
  display.println("SNAKE");
  display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
  display.setCursor(20, 25);
  display.println("The Game");
  display.display();
  delay(5000);

  //czysci pamiec OLED
  display.clearDisplay();

  // punkt w pozycji x=20, y=15
  // display.drawPixel(20, 15, SH110X_WHITE);
  // display.fillRect(12, 12, 4, 4, SH110X_WHITE);


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
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(64, 5);
    display.println(oSnake.CurrLen);

    //make snake segments
    for(int i = 0; i<oSnake.CurrLen; i++) {
        display.fillRect(oSnake.segs[i].widt, oSnake.segs[i].heig, ROZMIAR_PIX, ROZMIAR_PIX, SH110X_WHITE);
    }
    //make fruit
    display.fillRect(oFruit.widt, oFruit.heig, ROZMIAR_PIX*2, ROZMIAR_PIX*2, SH110X_WHITE);

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
        //print GAMEOVER
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(30, 5);
        display.println("GAME");
        display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
        display.setCursor(30, 25);
        display.println("OVER");
        display.display();
        delay(5000);
      //reset poz weza
      setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
      setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
      setSeg(Snake, 2, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);
      Snake.CurrLen=3;
      setFruit(Fruit);
      gameOver=false;
  }

//resetowanie po victory
  if (victory) {
        //print VICTORY
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SH110X_WHITE);
        display.setCursor(30, 20);
        display.println("VICTORY!!!");
        display.display();
        delay(5000);

      //reset poz weza
      setSeg(Snake, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
      setSeg(Snake, 1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
      setSeg(Snake, 2, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);
      Snake.CurrLen=3;
      setFruit(Fruit);
      victory=false;
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

