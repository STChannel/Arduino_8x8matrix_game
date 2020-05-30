int speedDelay = 9;
String input = (" press x to start game  ");
String rec;

char slova[100];
char levoSlovo;
char desnoSlovo;

const int duration = 13;
const int pillarDuration = 20;

bool startGame = 1;
bool gameOver = 0;

int val = 1;
int timer = 0;

int shift = 0;
int rng;
bool rngInit = 1;

int scrHeight = 4;
int yValue;
int xValue;

int left = B0;
bool initLeft = B1;
int leftTimer = 0;

int right = B0;
bool initRight = B0;
int rightTimer = B0;

int up = B0; 
bool initUp = B0;
int upTimer = B0;

int down = B0;
bool initDown = B0;
int downTimer = B0;

#include <FrequencyTimer2.h>

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

#define joyX A4
#define joyY A5

byte screen[] = {B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00000000};
byte a1[] = {B00011000,B00100100,B01000010,B10000001,B10000001,B10011001,B01100110, B00000000};
byte a2[] = {B00011000,B00100100,B01000010,B10000001,B10001001,B10010001,B01101110, B00000000};
byte a3[] = {B00011000,B00100100,B01000010,B10010001,B10001001,B10010001,B01101110, B00000000};
byte a4[] = {B00011000,B00100100,B01001010,B10010001,B10001001,B10010001,B01101110, B00000000};
byte a5[] = {B00110100,B01001010,B10010101,B00101000,B00010100,B00101000,B11000111, B00000000};
byte a6[] = {B01100000,B10010001,B00100010,B01000100,B00100010,B01000100,B10000011, B00000000};
byte a7[] = {B11000000,B00100000,B01000001,B10000010,B01000001,B10000010,B00000001, B00000000};
byte a8[] = {B10000000,B01000000,B10000000,B00000001,B10000000,B00000001,B00000000, B00000000};
byte a9[] = { B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
byte a10[] = { B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};

byte NOT[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte a[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00011000,B00000000};

byte e[] = {B00000000,B00111100,B00000100,B00111100,B00000100,B00000100,B00111100,B00000000};

byte g[] = {B00000000,B00011000,B00100100,B00010100,B00000100,B00100100,B00011000,B00000000};

byte m[] = {B00000000,B01000100,B01000100,B01000100,B01010100,B01101100,B01000100,B00000000};

byte o[] = {B00000000,B00011000,B00100100,B00100100,B00100100,B00100100,B00011000,B00000000};

byte p[] = {B00000000,B00000100,B00000100,B00011100,B00100100,B00100100,B00011100,B00000000};

byte r[] = {B00000000,B00100100,B00100100,B00011100,B00100100,B00100100,B00011100,B00000000};

byte s[] = {B00000000,B00011000,B00100100,B00010000,B00001000,B00100100,B00011000,B00000000};

byte t[] = {B00000000,B00001000,B00001000,B00001000,B00001000,B00001000,B00111110,B00000000};

byte x[] = {B00000000,B01000100,B00101000,B00101000,B00010000,B00101000,B01000100,B00000000};

byte desni[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte levi[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte levo[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte desno[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

byte trenutni[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

int timeCount = 0;
int charCount = 0;
int shift1 = 0;

byte pillar[8];
byte total[8];

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

void setup() {
  //rec = (" " + input + " ");
  for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A6, INPUT);
  
  Serial.begin(9600);

  

  randomSeed(18239);
}

void  drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], LOW);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (buffer2[i] >> 7-a) & 0x01); // initiate whole column
          
          //delay(30);
          delayMicroseconds(100);       // uncoment deley for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[a], 0);      // reset whole column
        }
        digitalWrite(rows[i], HIGH);     // reset whole row
        // otherwise last row will intersect with next row
    }
}
 
void loop() {
  
  timer+=1;
  if(timer<0){
    timer=0;
  }
  if(startGame){
    
  timeCount++;
  delay(5);
  
  if(timeCount == speedDelay) {
    shift1++;
    timeCount = 0; 
  }
  
  if(shift1 == 8){                        //promena karaktera
    charCount++;
    shift1 = 0;
  }
  
  if(charCount == input.length()){
    charCount = 0;
  }
  
  desnoSlovo = input[charCount];
  levoSlovo = input[charCount + 1];
  
  switch (desnoSlovo) {
    case 'a': {
      for(int i = 0; i < 8; i++) {
        desni[i] = a[i];
      }
    break;
    }
    
    case 'e': {
      for(int i = 0; i < 8; i++) {
        desni[i] = e[i];
      }
    break;
    }
        
    case 'g': {
      for(int i = 0; i < 8; i++) {
        desni[i] = g[i];
      }
    break;
    }
  
    case 'm': {
      for(int i = 0; i < 8; i++) {
        desni[i] = m[i];
      }
    break;
    }

    case 'o': {
      for(int i = 0; i < 8; i++) {
        desni[i] = o[i];
      }
    break;
    }
    
    case 'p': {
      for(int i = 0; i < 8; i++) {
        desni[i] = p[i];
      }
    break;
    }

    case 'r': {
      for(int i = 0; i < 8; i++) {
        desni[i] = r[i];
      }
    break;
    }
    
    case 's': {
      for(int i = 0; i < 8; i++) {
        desni[i] = s[i];
      }
    break;
    }
    
    case 't': {
      for(int i = 0; i < 8; i++) {
        desni[i] = t[i];
      }
    break;
    }

    case 'x': {
      for(int i = 0; i < 8; i++) {
        desni[i] = x[i];
      }
    break;
    }

    case ' ': {
      for(int i = 0; i < 8; i++) {
        desni[i] = NOT[i];
      }
    break;
    }
  }

  switch (levoSlovo) {
    
    case 'a': {
      for(int i = 0; i < 8; i++) {
        levi[i] = a[i];
      }
    break;
    }
    
    case 'e': {
      for(int i = 0; i < 8; i++) {
        levi[i] = e[i];
      }
    break;
    }
    
    case 'g': {
      for(int i = 0; i < 8; i++) {
        levi[i] = g[i];
      }
    break;
    }
     
    case 'm': {
      for(int i = 0; i < 8; i++) {
        levi[i] = m[i];
      }
    break;
    }
    
    case 'o': {
      for(int i = 0; i < 8; i++) {
        levi[i] = o[i];
      }
    break;
    }
    
    case 'p': {
      for(int i = 0; i < 8; i++) {
        levi[i] = p[i];
      }
    break;
    }
   
    case 'r': {
      for(int i = 0; i < 8; i++) {
        levi[i] = r[i];
      }
    break;
    }
    
    case 's': {
      for(int i = 0; i < 8; i++) {
        levi[i] = s[i];
      }
    break;
    }
    
    case 't': {
      for(int i = 0; i < 8; i++) {
        levi[i] = t[i];
      }
    break;
    }
   
    case 'x': {
      for(int i = 0; i < 8; i++) {
        levi[i] = x[i];
      }
    break;
    }
    
    case ' ': {
      for(int i = 0; i < 8; i++) {
        levi[i] = NOT[i];
      }
    break;
    }

  }
  
  for(int i = 0; i < 8; i++) {          // siftovanje u stranu

    levo[i] = levi[i]* expInt(2,7-shift1);
    //levo[i]<<expInt(2,shift1);
    desno[i] = (desni[i]* expInt(2,7-shift1))*0.00390625;
    //desno[i]<<expInt(2,shift1);
    trenutni[i] = levo[i] | desno[i];
  }

  drawScreen(trenutni);
  
  if(analogRead(A6)<100&&timer>50){
      startGame = 0;
      timer = 0;
    }
  }

  
  else if(gameOver){
    
    shift = 0;
    rngInit = 1;
    byte screen[] = {B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00000000};
    if(timer <  40)
    {
    drawScreen(a1);
    }
    else if (timer <  80)
    {
    drawScreen(a2);
    } 
    else if (timer <  120) 
    {
    drawScreen(a3);
    } 
    else if (timer <  160) 
    {
    drawScreen(a4);
    } 
    else if (timer <  200) 
    {
    drawScreen(a5);
    } 
    else if (timer <  240) 
    {
    drawScreen(a6);
    } 
    else if (timer <  280) 
    {
    drawScreen(a7);
    } 
    else if (timer <  320) 
    {
    drawScreen(a8);
    } 
    else if (timer <  360) 
    {
    drawScreen(a9);
    }
    else if (timer <  400) 
    {
    drawScreen(a10);
    }     
    else {
    timer = 0;
    }
    if(analogRead(A6)<100){
      startGame = 1;
      charCount=0;
      gameOver = 0;
      timer = 0;
    }
  }
  
  else{
    
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  if(xValue>820){
    right = 1;
    left = 0;
  }
  else if(xValue<80){
    left = 1;
    right = 0;
  }
  else{
    left = 0;
    right = 0;
  }
  
  if(yValue>820){
    down = 1;
    up = 0;
  }
  else if(yValue<80){
    down = 0;
    up = 1;
  }
  else{
    down = 0;
    up = 0;
  }
  
  if(down == 1 and scrHeight != 0){
    if(initDown == 1){
      screen[scrHeight - 1] = screen[scrHeight];
      scrHeight--;
      screen[scrHeight + 1] = 0;
    }
    initDown = 0;
    downTimer++;
    if(downTimer == duration){
      screen[scrHeight - 1] = screen[scrHeight];
      scrHeight--;
      screen[scrHeight + 1] = 0;
      downTimer = 0; 
    }
  }
  
  if(up == 1 and scrHeight != 7){
    if(initUp == 1){
      screen[scrHeight + 1] = screen[scrHeight];
      scrHeight++;
      screen[scrHeight - 1] = 0;
    }
    initUp = 0;
    upTimer++;
    if(upTimer == duration){
      screen[scrHeight + 1] = screen[scrHeight];
      scrHeight++;
      screen[scrHeight - 1] = 0;
      upTimer = 0; 
    }
  }
  
  if(down == 0){
    initDown = 1;
    downTimer = 0;
  }
  
  if(up == 0){
    initUp = 1;
    upTimer = 0;
  }
  
  if(right == 1 and screen[scrHeight] != 128){
    if(initRight == 1)
      screen[scrHeight] = screen[scrHeight] * 2;
    initRight =0;
    rightTimer++;
    if(rightTimer == duration){
      screen[scrHeight] = screen[scrHeight] * 2;
      rightTimer = 0; 
    }
  }
  
  if(left == 1 and screen[scrHeight] != 1){
    if(initLeft == 1)
      screen[scrHeight] = screen[scrHeight] / 2;
    initLeft =0;
    leftTimer++;
    if(leftTimer == duration){
      screen[scrHeight] = screen[scrHeight] / 2;
      leftTimer = 0; 
    }
  }

  if(left == 0){
    initLeft = 1;
    leftTimer = 0;
  }
  
  if(right == 0){
    initRight = 1;
    rightTimer = 0;
  }
  
//-------------------------------------------------------------------|-------------------|-------------------------------------------------------------------------------------------------
//###################################################################|  POMERANJE  ZIDA  |#################################################################################################
//------------------------------------------------------------------\|/-----------------\|/------------------------------------------------------------------------------------------------
  
  if (rngInit){
    rng = random(7);
    rngInit = 0;
  }
  
  if(timer >= pillarDuration){
    for (int i = 0; i < 8; i++){
      pillar[i] = pillar[i] / 2;
    }
    shift++;
    timer = 0;
  }
  
  if (shift == 9){
    rngInit = 1;
    shift = 1;
  }
  
  gameOver = 0;
  
  for(int i = 0; i < 8; i++){
    if(rng != i and rng + 1 != i)
      pillar[i] = expInt(2,(8 - shift));
    else{
      pillar[i] = 0;
    }
    //total[i] = screen[i]; 
    total[i] = screen[i] | pillar[i];
  }
  
  gameOver = screen[scrHeight] & pillar[scrHeight];
    
  drawScreen(total);
  
    
  }
  //Serial.println(timer);
  //Serial.print("\t");
  //Serial.print(shift1);
  //Serial.print("\t");
  //Serial.print(charCount);
  //Serial.print("\t");
  //Serial.print(up);
  //Serial.print("\t");
  //Serial.println(left);
  //Serial.print("\t");
  //Serial.println(scrHeight);

}

int expInt(int a, int b){
  int x = 1;
  for(int i = 0; i < b; i++){
    x = x * a;
  }
  return x;
}



