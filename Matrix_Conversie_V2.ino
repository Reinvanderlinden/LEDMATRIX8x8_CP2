byte Translation1(int in[]);
byte Translation2(int in[]);
const int shiftClockPin = 5;  //SH
const int latchClockPin = 6;  //ST
const int serialInputPin = 9; //DS
const int swPin = 2; //SW3
const int sw2Pin = 3; //SW3
byte rows[2][8] = { {0b00010110,0b00010110,0b00010110,0b00000110,0b00010110,0b00010010,0b00010100,0b00010110},
                    {0b01010110,0b10010110,0b11010010,0b11010110,0b11010100,0b11010110,0b11010110,0b11000110}};
byte t1;
byte t2;
int row = 0;
int del = 200;
boolean shiftLeftRight = false;

int IN[8][8]={   {1,0,0,0,0,0,0,0},
                 {0,1,0,0,0,0,0,0},
                 {0,0,1,0,0,0,0,0},
                 {0,0,0,1,0,0,0,0},
                 {0,0,0,0,1,0,0,0},
                 {0,0,0,0,0,1,0,0},
                 {0,0,0,0,0,0,1,0},
                 {0,0,0,0,0,0,0,1}};
                 
int IN2[8][8]={  {0,0,0,0,0,0,0,1},
                 {0,0,0,0,0,0,1,0},
                 {0,0,0,0,0,1,0,0},
                 {0,0,0,0,1,0,0,0},
                 {0,0,0,1,0,0,0,0},
                 {0,0,1,0,0,0,0,0},
                 {0,1,0,0,0,0,0,0},
                 {1,0,0,0,0,0,0,0}};                 


void setup() {
  Serial.begin(115200);
  //Instelen van de uitgangspinnen
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);
  pinMode(swPin, INPUT);
  pinMode(sw2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(swPin),blink, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw2Pin),blink2, FALLING);
}

void loop() {
  byte s2;
  byte s1;
  
  for (int i = 0; i <=7;i++){
   row = i;
   t1 = rows[0][i];
   t2 = rows[1][i];
   s2 = Translation1(IN);
   s1 = Translation2(IN);
   displayData(s1);
   displayData(s2);
   delay(del); 
  }
  for (int i = 0; i <=7;i++){
   row = i;
   t1 = rows[0][i];
   t2 = rows[1][i];
   s2 = Translation1(IN2);
   s1 = Translation2(IN2);
   displayData(s1);
   displayData(s2);
   delay(del); 
  }
}

void Klick () {
  del -=10;
  }

void Klik2 () {
  del +=100;
  }

 byte Translation1(int in[8][8]){
  byte temp;
  //KOLOM 1
  t2 ^= in[row][0];
  //KOLOM 2
    temp = in[row][1];
    temp <<= 5;
    t2 ^= temp;
  //KOLOM 4
    temp = in[row][3];
    temp <<= 3;
    t2 ^= temp;
  return t2;
  }

byte Translation2(int in[8][8]){
    byte temp;
    //KOLOM 3
    temp = in[row][2];
    temp <<= 6;
    t1 ^= temp;
  //KOLOM 5
    temp = in[row][4];
    temp <<= 7;
    t1 ^= temp;
  //KOLOM 6
    temp = in[row][5];
    temp <<= 5;
    t1 ^= temp;
  //KOLOM 7
    temp = in[row][6];
    temp <<= 0;
    t1 ^= temp;
  //KOLOM 8
    temp = in[row][7];
    temp <<= 3;
    t1 ^= temp;
  return t1;
  }

  void displayData(byte message) {
  for (int i = 0; i <= 7; i++) {
    digitalWrite(serialInputPin, bitRead(message, i));
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(shiftClockPin, LOW);
  }
  digitalWrite(latchClockPin, HIGH);
  digitalWrite(latchClockPin, LOW);
}

  
