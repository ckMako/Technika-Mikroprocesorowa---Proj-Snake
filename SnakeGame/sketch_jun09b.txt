#include <Wire.h>

#include <Adafruit_SH110X.h>

#include <Adafruit_GFX.h>

#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define NUMFLAKES 5
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

void setup()   {

  /**
  * OLED wpinamy do
  * SDA -> A4 //data
  * SCL -> A5 //clock
  * 11 -> button left
  * 12 -> button right
  */

  pinMode(11, INPUT_PULLUP); //lewo - domyslnie HIGH, inaczej nie dziala
  pinMode(12, INPUT_PULLUP); //prawo
  
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(i2c_Address, true); // Address 0x3C default
  // init done


  // Clear the buffer.
  display.clearDisplay();


  // text display tests
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(15, 5);
  display.println("WESOLYCH");
  display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
  display.setCursor(30, 25);
  display.println("SWIAT");
  display.display();
  delay(5000);
  display.clearDisplay();
//  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}
//  display.drawPixel(10, 10, SH110X_WHITE);



//czy resetowac gre
bool gameOver=false;

//odswiezanie i drganie styk
int repet = 30;
int debounceDEL =50; //15-30

//'stan' weza
int heig=SCREEN_HEIGHT / 2, widt=SCREEN_WIDTH / 2; //pozycja weza
int dir = 0; // 0 lub 4-gora, 1-prawo, 2-dol, 3-lewo

/**
wyswietl weza, size okrezla rozmiar kropki np 2x2
*/
int displSnake (int siz) {
  display.clearDisplay();
  if (siz >1 && siz < 5)
//    display.drawPixel(widt, heig, SH110X_WHITE);
    display.fillRect(widt, heig, siz, siz, SH110X_WHITE);
  else
    display.drawPixel(widt, heig, SH110X_WHITE);
//    display.drawPixel(widt, heig, SSD1306_WHITE);

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
  else {
      displSnake(2);
      makeFruit();
    }

}

//owoce poza rantem ekranu
int padding = 10;

//make fruit
void makeFruit () {
  int fruiHei=rand() % (SCREEN_HEIGHT-padding); 
  int fruuWid=rand() % (SCREEN_WIDTH-padding);
  display.fillRect(fruuWid, fruiHei, 2, 2, SH110X_WHITE);
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


//przerwania-

//resetowanie po gameOver
  if (gameOver) {
      display.clearDisplay();
      heig=SCREEN_HEIGHT / 2; widt=SCREEN_WIDTH / 2;
      gameOver=false;
  }

}
