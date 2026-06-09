#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

  //czysci pamiec micCon
  display.clearDisplay();

  // punkt w pozycji x=20, y=15
  display.drawPixel(20, 15, SSD1306_WHITE);

  //wiekszy rozmiar
  display.fillRect(12, 12, 4, 4, SSD1306_WHITE);

  //wyswietl
  display.display();
}

//czy resetowac gre
bool gameOver=false;

//odswiezanie i drganie styk
int repet = 50;
int debounceDEL =25; //15-30

//'stan' weza
int heig=SCREEN_HEIGHT / 2, widt=SCREEN_WIDTH / 2; //pozycja weza
int dir = 0; // 0 lub 4-gora, 1-prawo, 2-dol, 3-lewo

/**
wyswietl weza, size okrezla rozmiar kropki np 2x2
*/
int displSnake (int siz) {
  display.clearDisplay();
  if (siz >1 && siz < 5)
    display.fillRect(widt, heig, siz, siz, SSD1306_WHITE);
  else
    display.drawPixel(widt, heig, SSD1306_WHITE);

  display.display();
}

/**
Zmien kierunek
*/
int changeDir (int dire, bool change) { //true --right
  if (change) {
    dire = (dire + 1) % 4; //+1
  } else {
    dire = (dire + 3) % 4; //-1
  }
  return dire;
}

/**
przesun weza o 1
*/
void goSnake () {
  //zmieniamy poz
  switch (dir*3) {
    case 12: //gora
    case 0 : //gora
      heig--; //na OLED -- idzie w gore,
      break;
    case 3 : //prawo
      widt++;
      break;
    case 6 :  //dol
      heig++;
      break;
    case 9 : //prawo
      widt--;
      break;
  }

  if(heig > SCREEN_HEIGHT || heig < 0)
    gameOver =true;
  else if(widt>SCREEN_WIDTH || widt < 0)
    gameOver=true;
  else
    displSnake(2);
}

//obsluga czasu odswiezania snakea
unsigned long lastTime = 0;

//obsluga buttons
bool leftBut=false;
bool righBut=false;

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