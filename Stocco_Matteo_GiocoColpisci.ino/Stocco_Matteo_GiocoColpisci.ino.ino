#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int livello = 0;
int vite = 3;
int stato = 0;
bool passo = true;
bool cattivo = false;
bool difficolta = false;
float tempo1 = 0;
float tempo2 = 0;

int delay1 = 150;
int delay2 = 250;

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

byte buono_part1[8]{
   B00011, B00100, B01100, B01000, B01011, B10000, B10000, B10001
};

byte buono_part2[8]{
  B10000, B10000, B10010, B01001, B01000, B01000, B00100, B00011
};

byte buono_part3[8]{
   B11000, B00100, B00110, B00010, B11010, B00001, B00001, B10001
};

byte buono_part4[8]{
   B00001, B00001, B01001, B10010, B00010, B00010, B00100, B11000
};

byte vita_part1[8]{
  B00000, B00000, B00110, B01001, B01000, B10000, B10000, B10000
};

byte vita_part2[8]{
  B00000, B00000, B01100, B10010, B00010, B00001, B00001, B00001
};

byte vita_part3[8]{
  B10000, B10000, B01000, B01000, B00100, B00010, B00001, B00000
};

byte vita_part4[8]{
  B00001, B00001, B00010, B00010, B00100, B01000, B10000, B00000
};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.createChar(0, cuore);
  lcd.createChar(1, cuorevuoto);
  lcd.createChar(2, cuorerotto);
  randomSeed(analogRead(A5));   
}

void Intro()
{
  lcd.setCursor(2,0); lcd.print("BENVENUTO IN"); lcd.setCursor(5,1); lcd.print("ENEMY");
  delay(3000); lcd.clear();
  lcd.setCursor(1,0); lcd.print("INIZIA PARTITA");
  aspetta(); lcd.clear();
  lcd.setCursor(2,0); lcd.print("3..."); delay(750); lcd.setCursor(6,0); lcd.print("2..."); delay(750); lcd.setCursor(9,0); lcd.print("1...."); delay(750);
  lcd.setCursor(6,1); lcd.print("VIA!"); delay(1000); lcd.clear();
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
  setDifficulty();
  changeDifficulty();
  long simbolo = random(1,14);
  if(simbolo <= 7)
  {
    lcd.createChar(3, cattivo_part1); lcd.createChar(4, cattivo_part2); lcd.createChar(5, cattivo_part3); lcd.createChar(6, cattivo_part4);
    long posto = random(1,4);
    lcd.setCursor(Cursore(posto),0); lcd.print(char(3));  lcd.print(char(5)); lcd.setCursor(Cursore(posto),1); lcd.print(char(4)); lcd.print(char(6));
    long durata = random(delay1,delay2) * 10; controllocattivo(durata, Cursore(posto)); if(cattivo == true)
    {
      lcd.setCursor(Cursore(posto),0); lcd.print("  "); lcd.setCursor(Cursore(posto),1); lcd.print("  "); delay(750); cattivo = false;  
    } else{
       lcd.setCursor(Cursore(posto),0); lcd.print("  "); lcd.setCursor(Cursore(posto),1); lcd.print("  "); rotturacuore(); vite--; delay(400); fine();
    }
  } 
  else if(simbolo <= 12)
  {
    lcd.createChar(3, buono_part1); lcd.createChar(4, buono_part2); lcd.createChar(5, buono_part3); lcd.createChar(6, buono_part4);
    long posto = random(1,4);
    lcd.setCursor(Cursore(posto),0); lcd.print(char(3));  lcd.print(char(5)); lcd.setCursor(Cursore(posto),1); lcd.print(char(4)); lcd.print(char(6));
    long durata = random(delay1,delay2) * 10; controllobuono(durata, Cursore(posto)); lcd.setCursor(Cursore(posto),0); lcd.print("  "); lcd.setCursor(Cursore(posto),1); lcd.print("  "); delay(750); fine();
  } else if(simbolo == 13)
  {
    lcd.createChar(3, vita_part1); lcd.createChar(4, vita_part2); lcd.createChar(5, vita_part3); lcd.createChar(6, vita_part4);
    long posto = random(1,4);
    lcd.setCursor(Cursore(posto),0); lcd.print(char(3)); lcd.print(char(4)); lcd.setCursor(Cursore(posto),1); lcd.print(char(5)); lcd.print(char(6)); 
    long durata = random(delay1,delay2) * 10; Max(); 
    if(passo == true){controllovita(durata, Cursore(posto));} else{ delay(durata);}
    lcd.setCursor(Cursore(posto),0); lcd.print("  "); lcd.setCursor(Cursore(posto),1); lcd.print("  "); delay(750);
  }
}

int Cursore(long p)
{
  if(p == 1)
  {
    return 2;
  } else if(p == 2)
  {
    return 4;
  } else if(p == 3)
  {
    return 7;
  }
}

void controllocattivo(long durata, int posto)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == LEFT && posto == 2)
    {
      livello++; lcd.setCursor(11,1); lcd.print("Lv:" + (String)livello); cattivo = true; finito = true;
    } else if(btnpremuto == UP && posto == 4)
    {
      livello++; lcd.setCursor(11,1); lcd.print("Lv:" + (String)livello); cattivo = true; finito = true;
    } else if(btnpremuto == RIGHT && posto == 7)
    {
      livello++; lcd.setCursor(11,1); lcd.print("Lv:" + (String)livello); cattivo = true; finito = true;
    } else{
      i++; delay(1);
    }
  }
}

void controllobuono(long durata, int posto)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == LEFT && posto == 2)
    {
      lcd.setCursor(posto,0); lcd.print("  "); lcd.setCursor(posto,1); lcd.print("  "); rotturacuore(); vite--; finito = true;
    } else if(btnpremuto == UP && posto == 4)
    {
      lcd.setCursor(posto,0); lcd.print("  "); lcd.setCursor(posto,1); lcd.print("  "); rotturacuore(); vite--; finito = true;
    } else if(btnpremuto == RIGHT && posto == 7)
    {
      lcd.setCursor(posto,0); lcd.print("  "); lcd.setCursor(posto,1); lcd.print("  "); rotturacuore(); vite--; finito = true;
    } else{
      i++; delay(1);
    }
  }
}

void controllovita(long durata, int posto)
{
  bool finito = false;
  int i = 0;
  while((!finito) && (i < durata))
  {
    btnpremuto = BottonePremuto();
    if(btnpremuto == LEFT && posto == 2)
    {
      lcd.setCursor(0,1); vite++; lcd.setCursor(vite + 10, 0);
      lcd.print(char(0)); finito = true;
    } else if(btnpremuto == UP && posto == 4)
    {
      lcd.setCursor(0,1); vite++; lcd.setCursor(vite + 10, 0);
      lcd.print(char(0)); finito = true;
    } else if(btnpremuto == RIGHT && posto == 7)
    {
      lcd.setCursor(0,1); vite++; lcd.setCursor(vite + 10, 0);
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
  if(vite <= 0)
  {
    stato = 2;
  }
}

void setDifficulty()
{
  if(livello <= 10)
  {
    delay1 = 120;
    delay2 = 220;
  } else if(livello <= 20)
  {
    delay1 = 90;
    delay2 = 180;
  }else if(livello <= 25)
  {
    delay1 = 65;
    delay2 = 140;
  }else if(livello > 25)
  {
    delay1 = 40;
    delay2 = 80;
  }
}

void changeDifficulty()
{
  if(livello == 10 && difficolta == false)
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("DIFFICOLTA"); lcd.setCursor(6,1); lcd.print("MEDIA"); delay(1500);
    difficolta = true;
    messaggio();
  } else if(livello == 20 && difficolta == true)
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("DIFFICOLTA"); lcd.setCursor(3,1); lcd.print("DIFFICILE"); delay(1500);
    difficolta = false;
    messaggio();
  } else if(livello == 25 && difficolta == false)
  {
    lcd.clear();
    lcd.setCursor(3,0); lcd.print("DIFFICOLTA"); lcd.setCursor(2,1); lcd.print("IMPOSSIBILE"); delay(1500);
    difficolta = true;
    messaggio();
  }
}

void messaggio()
{
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("|"); lcd.setCursor(0,1); lcd.print("|"); lcd.setCursor(10,0); lcd.print("|"); lcd.setCursor(10,1); lcd.print("|");
  lcd.setCursor(11,1); lcd.print("Lv:" + (String)livello); lcd.setCursor(11, 0);
  for(int i = 0; i< vite; i++)
  {
     lcd.print(char(0));
  }
  for(int i = 0; i< 5 - vite; i++)
  {
     lcd.print(char(1));
  }
  delay(750);
}

void messaggioSconfitta()
{
  tempo1 = tempo1/1000;
  tempo2 = millis()/1000;
  float t = tempo2-tempo1;
  lcd.clear();
  lcd.setCursor(3,0); lcd.print("FINE GIOCO");
  lcd.setCursor(0,1); lcd.print("Lv: " + String(livello) + "    " + String(t) + "s");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(stato == 0)
  {
    Intro();
    lcd.setCursor(3,0); lcd.print("DIFFICOLTA"); lcd.setCursor(5,1); lcd.print("FACILE"); delay(1500);
    messaggio();
    tempo1 = millis();
    stato = 1;
  } else if(stato == 1){
    uscita();
  } else if(stato == 2)
  {
    messaggioSconfitta();
    aspetta();
  }
}
