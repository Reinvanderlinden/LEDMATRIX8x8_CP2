/*
Made By Rein van der Linden / Sam Knoors - 2019
*/
uint16_t Translation(int in[]);
uint16_t Translation2(int in[]);
const int shiftClockPin = 5;  //SH
const int latchClockPin = 6;  //ST
const int serialInputPin = 9; //DS
const int swPin = 2; //SW3
const int sw2Pin = 3; //SW3
uint16_t rows [8] = {0b0101011000010110,0b1001011000010110,0b1101001000010110,0b1101011000000110,0b1101010000010110,0b1101011000010010,0b1101011000010100,0b1100011000010110};
uint16_t t1;
uint16_t  t2;
int row = 0;
int del = 0;

boolean shiftLeftRight = false;

int IN[8][8]={   {2,3,4,5,6,7,8,9},
                 {29,30,31,32,33,34,35,10},
                 {28,49,50,51,52,53,36,11},
                 {27,48,61,62,63,54,37,12},
                 {26,47,60,65,64,55,38,13},
                 {25,46,59,58,57,56,39,14},
                 {24,45,44,43,42,41,40,15},
                 {23,22,21,20,19,18,17,16}};
//1 = always on 2 to ∞ verschillende stappen
int IN3[8][8]={  {0,0,0,0,0,0,0,0},
                 {0,0,1,0,0,1,0,0},
                 {0,0,1,0,0,1,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,2,3,3,3,3,2,0},
                 {0,3,2,2,2,2,3,0},
                 {0,0,0,0,0,0,0,0}}; 
                 
int IN2[8][8]={  {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0}};                 

int framecount = 300;

void setup() {
  Serial.begin(115200);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);
  pinMode(swPin, INPUT);
  pinMode(sw2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(swPin),Klick, FALLING);
  attachInterrupt(digitalPinToInterrupt(sw2Pin),Klik2, FALLING);
}

void loop() {
  uint16_t s1;
  
 for(int a = 2; a <=3;a++){
  for(int frames = 1; frames <=framecount;frames++){
   for (int b = 0; b <=7;b++){
     for (int c = 0; c <=7;c++){
       if(IN3[b][c]==a || IN3[b][c]==1)
        {
           IN2[b][c]=1;
        }
        else
        {
          IN2[b][c]=0;
        }
     }
   }
  
   for (int i = 0; i <=7;i++){
   //ROW  1 TO 8
   row = i;
   t1 = rows[i];
   s1 = Translation(IN2);
   Serial.println(s1);
   displayData(s1);
   delay(del); 
   }
  }
   }
   
}



void Klick () {
  del -=10;
  }

void Klik2 () {
  del +=100;
  }

uint16_t Translation (int in[8][8]){
  uint16_t temp = 0;
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

    temp = 0;
 //KOLOM 1
   temp ^= in[row][0];
   temp <<= 8;
   t1 ^= temp;
 //KOLOM 2
   temp = in[row][1];
   temp <<= 13;
   t1 ^= temp;
  //KOLOM 4
    temp = in[row][3];
    temp <<= 11;
    t1 ^= temp;
    
  return t1;
  }


  void displayData(uint16_t  message) {
   digitalWrite(latchClockPin, LOW);
  for (int i = 0; i <= 15; i++) {
    
    digitalWrite(shiftClockPin, HIGH);
    digitalWrite(serialInputPin, bitRead(message, i));
    
    digitalWrite(shiftClockPin, LOW);
  }
  digitalWrite(shiftClockPin, HIGH);
  digitalWrite(latchClockPin, HIGH);
  digitalWrite(latchClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);
}
