/*
Made By Rein van der Linden / Sam Knoors - 2019
*/

#define outputA 6                     //inputs rotaryencoder
#define outputB 7
const int swPin = 2;                  //mode switch
uint16_t Translation(uint8_t in[]);   //convert 8*8 to 16 bits
const int shiftClockPin = 5;          //SH
const int latchClockPin = 8;          //ST
const int serialInputPin = 9;         //DS
uint16_t rows [8] = {0b0101011000010110,0b1001011000010110,0b1101001000010110,0b1101011000000110,0b1101010000010110,0b1101011000010010,0b1101011000010100,0b1100011000010110};
uint16_t t1;                          
int row = 0;                          
int framecount = 30;                  //frames refresh
int maxframes = 16;                   //max number frames
int anilength = 5;                    //number of animation states
int Animation = 0;                    //current animation
void Speed();                         //speed of animation
int aState;                           //current state of rotary
int aLastState;                       //laststate rotary
                

uint8_t dataBase[4][8][27]={{                                             //Animation Array 1 
                   {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},     //animation 1
                   {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,0,1,1,3,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,3,3,1,1,2,3,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,2,1,1,4,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,2,1,1,3,4,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,2,3,0,0,0,0,0,0,0,0,0,0,0,0}},

                  {{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},     //animation 2
                   {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,3,1,1,0,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,3,2,1,1,3,3,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,2,1,1,2,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,4,1,1,2,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,4,3,1,1,2,0,0,0,0,0,0,0,0,0,0},
                   {0,0,0,0,0,0,0,0,0,0,0,0,3,2,0,0,0,0,0,0,0,0,0,0}},
                   
                 {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},      //animation 3
                  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
                  {0,0,0,1,0,0,0,0,2,2,2,1,1,1,1,1,0,0,0,0,0,1,0,0},
                  {0,0,0,0,0,0,0,0,2,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0}},
                  
                  {{0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},     //animation 4
                  {0,0,0,0,0,0,0,0,5,4,4,4,4,4,4,5,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,5,4,3,3,3,3,4,5,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,5,4,3,2,2,3,4,5,0,0,0,0,0,0,0,0},
                  {0,0,0,1,0,0,0,0,5,4,3,2,2,3,4,5,0,0,0,0,0,1,0,0},
                  {0,0,0,0,0,0,0,0,5,4,3,3,3,3,4,5,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,5,4,4,4,4,4,4,5,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0}}}; 

  
uint8_t IN2[8][8]={{0,0,0,0,0,0,0,0},       //Final Array this is where the projected image is created from the animation array   
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0},
                 {0,0,0,0,0,0,0,0}};                 

void setup() {
  Serial.begin(115200);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);
  pinMode(swPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(swPin),BTNpress, RISING);
}

void loop() {
 uint16_t s1;
 int AniPosistion = 0; 
 while(AniPosistion<=maxframes && AniPosistion >= 0){     
 for(int a = 2; a <=anilength;a++){
  for(int frames = 1; frames <=framecount;frames++){
   for (int b = 0; b <=7;b++){
     for (int c = 0; c <=7;c++){
       if(dataBase[Animation][b][c+AniPosistion]==a || dataBase[Animation][b][c+AniPosistion]==1)
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
   displayData(s1);
   Speed();
   }
  }
  }
  if(Animation==3){
    AniPosistion = 8;
    }
  else {
   AniPosistion++;
  }

  }
  
}

uint16_t Translation (uint8_t in[8][8]){    //set output shiftregister to readeble position
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

/*
 * send data parallel out to shiftregister
 * @param: string of bits
 * @return:-
 */
  void displayData(uint16_t  message) {
   digitalWrite(latchClockPin, LOW);
   for (int i = 0; i <= 15; i++) 
    {
      digitalWrite(shiftClockPin, HIGH);
      digitalWrite(serialInputPin, bitRead(message, i));
      digitalWrite(shiftClockPin, LOW);
    }
    
  digitalWrite(shiftClockPin, HIGH);
  digitalWrite(latchClockPin, HIGH);
  digitalWrite(latchClockPin, LOW);
  digitalWrite(shiftClockPin, LOW);
}
/*
 * select animation mode
 * @param: -
 * @return: -
 */
void BTNpress () {
  if(Animation == 1) {Animation = 2;}
  else if(Animation == 2) {Animation = 3;}
  else if(Animation == 3) {Animation = 0;}

  else {Animation =1;}
}
/*
 * set speed with rotaryencoder
 * @param: -
 * @return: -
 */
void Speed() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) {
      if (framecount >= 11 && framecount <= 20)
      {
       framecount -=1;
      }
      else if (framecount >= 20)
      {
       framecount -=10;
      }
      else {
        framecount = 10;
      }
     } else {
      if (framecount <= 300){ 
       framecount +=10;
      }
      else {
        framecount = 300;
      }
     }
     Serial.println(framecount);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
