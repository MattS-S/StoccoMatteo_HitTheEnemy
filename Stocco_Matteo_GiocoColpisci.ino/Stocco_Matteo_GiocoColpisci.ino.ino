#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int livello = 0;
int vite = 3;
int stato = 0;
bool passo = true;
bool cattivo = false;

int btnpremuto = 0;
int bottone  = 0;

int RIGHT = 0;
int UP  = 1;
int DOWN = 2;
int LEFT  = 3;
int SELECT = 4;
int NONE = 5;

//metodo che controlla il bottone premuto
int BottonePremuto() {
  bottone = analogRead(0);
  if (bottone > 1000) return NONE;
  if (bottone < 50)   return RIGHT;
  if (bottone < 250)  return UP;
  if (bottone < 400)  return DOWN;
  if (bottone < 600)  return LEFT;
  if (bottone < 920)  return SELECT;
  return NONE;
}

void aspetta(){
  btnpremuto = BottonePremuto();
  while (btnpremuto != SELECT)
  {
    btnpremuto = BottonePremuto();
  }
}

byte cuore[8] = {
  B00000, B00000, B01010, B11111, B11111, B01110, B00100, B00000
};

byte cuorevuoto[8] = {
  B00000, B00000, B01010, B10101, B10001, B01010, B00100, B00000
};

byte cuorerotto[8] = {
  B00000, B00000, B00010, B10101, B10001, B01000, B00100, B00000
};

byte cattivo_part1[8] = {
  B00011, B00100, B01100, B01010, B01011, B10000, B10000, B10001
};

byte cattivo_part2[8] = {
  B10000, B10000, B10001, B01010, B01000, B01000, B00100, B00011
};

byte cattivo_part3[8] = {
  B11000, B00100, B00110, B01010, B11010, B00001, B00001, B10001
};

byte cattivo_part4[8] = {
  B00001, B00001, B10001, B01010, B00010, B00010, B00100, B11000
};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.createChar(0, cuore);
  lcd.createChar(1, cuorevuoto);
  lcd.createChar(2, cuorerotto);
  lcd.setCursor(2,0); lcd.print("BENVENUTO IN"); lcd.setCursor(5,1); lcd.print("ENEMY");
  delay(3000); lcd.clear();
  lcd.setCursor(1,0); lcd.print("INIZIA PARTITA");
  aspetta(); lcd.clear();
  lcd.setCursor(2,0); lcd.print("3..."); delay(750); lcd.setCursor(6,0); lcd.print("2..."); delay(750); lcd.setCursor(9,0); lcd.print("1...."); delay(750);
  lcd.setCursor(6,1); lcd.print("VIA!"); delay(1000); lcd.clear();
  randomSeed(analogRead(A5));   
}

void rotturacuore()
{
  for(int i = 0; i < 5; i++)
  {
    if(i%2 == 0)
    {
      lcd.setCursor(vite + 10, 0);
      lcd.print(char(1));
      delay(400);
    } else{
      lcd.setCursor(vite + 10, 0);
      lcd.print(char(0));
      delay(400);
    }
  }
  lcd.setCursor(vite + 10, 0);
  lcd.print(char(2));
}

void uscita()
{
  long simbolo = random(1,14);
  if(simbolo <= 6)
  {
    lcd.createChar(3, cattivo_part1);
    lcd.createChar(4, cattivo_part2);
    lcd.createChar(5, cattivo_part3);
    lcd.createChar(6, cattivo_part4);
    lcd.setCursor(2,0); lcd.print(char(3));  lcd.print(char(5)); lcd.setCursor(2,1); lcd.print(char(4)); lcd.print(char(6));
    long durata = random(100,250) * 10; controllocattivo(durata); if(cattivo == true)
    {
      lcd.setCursor(0,0); lcd.print("      "); lcd.setCursor(2,1); lcd.print("      "); delay(1500); cattivo = false;
    } else{
       lcd.setCursor(0,0); lcd.print("      "); lcd.setCursor(2,1); lcd.print("      "); rotturacuore(); vite--; delay(400);
    }
  } 
  else if(simbolo <= 12)
  {
    lcd.setCursor(0,0); lcd.print("U"); 
    long durata = random(100,250) * 10; controllobuono(durata); lcd.setCursor(0,0); lcd.print("   "); delay(1500);
  } else if(simbolo == 13)
  {
    lcd.setCursor(0,0); lcd.print("+"); 
    long durata = random(100,250) * 10; Max(); 
    if(passo == true){controllovita(durata);} else{ delay(1000);}
    lcd.setCursor(0,0); lcd.print("   "); delay(1500);
  }
}
void controllocattivo(long durata)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == SELECT)
    {
      livello++; lcd.setCursor(0,1); lcd.print(livello); cattivo = true; finito = true;
    } else{
      i++; delay(1);
    }
  }
}

void controllobuono(long durata)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == SELECT)
    {
       lcd.setCursor(0,0); lcd.print("   "); rotturacuore(); lcd.setCursor(0,1); lcd.print(livello); vite--; finito = true;
    } else{
      i++; delay(1);
    }
  }
}

void controllovita(long durata)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == SELECT)
    {
      lcd.setCursor(0,1); lcd.print(livello); vite++; lcd.setCursor(vite + 10, 0);
      lcd.print(char(0)); finito = true;
    } else{
      i++; delay(1);
    }
  }
}

void Max()
{
  if(vite == 5)
  {
    passo = false;
  } else{
    passo = true;
  }
}

void fine()
{
  
}
void loop() {
  // put your main code here, to run repeatedly:
  if(stato == 0)
  {
     lcd.setCursor(0,1); lcd.print(livello);
     lcd.setCursor(11, 0); lcd.print(char(0)); lcd.print(char(0)); lcd.print(char(0)); lcd.print(char(1)); lcd.print(char(1)); 
     stato = 1;
  }
  uscita();
}
