#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define MAXsize 10

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//'stan' weza
struct snakeSeg{
  // int heig=SCREEN_HEIGHT / 2;
  // int widt=SCREEN_WIDTH / 2; //pozycja weza
  int heig=0;
  int widt=0; //pozycja weza
}; 

struct snake{
  snakeSeg segs[MAXsize];
  int CurrLen=3;
  int dir = 0; // 0 lub 4-gora, 1-prawo, 2-dol, 3-lewo
};
snake Snake;

void setSeg(int arg, int heig, int widts) {
  if(arg<MAXsize) {
    Snake.segs[arg].heig=heig;
    Snake.segs[arg].widt=widts;
  }
}

setSeg(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2);
setSeg(1, (SCREEN_HEIGHT / 2)-1, SCREEN_WIDTH / 2);
setSeg(1, (SCREEN_HEIGHT / 2)-2, SCREEN_WIDTH / 2);

int fruiHei = 30, fruiWidt = 30;
int padd=10;

void setFruit () {
  fruiHei=rand()%(SCREEN_HEIGHT-padd)+padd;
  fruiWidt=rand()%(SCREEN_WIDTH-padd)+padd;
}

bool ateFruit() {
  return (snake[0].widt==fruiWidt) && (sake[0].heig==fruiWidt);
}



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



/**
wyswietl weza, size okrezla rozmiar kropki np 2x2
*/
int displSnake (int siz) {
  display.clearDisplay();
  if (siz >1 && siz < 5)
    for(int i = 0; i<Snake.CurrLen; i++) {
      display.fillRect(Snake.segs[i].widt, Snake.segs[i].heig, siz, siz, SSD1306_WHITE);
    }
    
  else
    for(int i = 0; i<Snake.CurrLen; i++) {
      display.drawPixel(elem.widt, elem.heig, SSD1306_WHITE);
    }
  //make fruit
  display.drawPixel(fruiWidt, fruiHei, SSD1306_WHITE);
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
  for (int i = snake.CurrLen; i > 0; i--) {
  tab[i] = tab[i - 1];
}
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
    if (snake.segs[0].heig== && snake.segs[0].widt==)
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