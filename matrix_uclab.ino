//Definiëren van de uitganspinnen
const int shiftClockPin = 5;  //SH
const int latchClockPin = 6;  //ST
const int serialInputPin = 9; //DS
const int frames = 2;
uint16_t bericht[8];
uint8_t bitmapInv[8];

uint16_t col_mask[8] = {0b0000000100000000,
                        0b0010000000000000,
                        0b0000000001000000,
                        0b0000100000000000,
                        0b0000000010000000,
                        0b0000000000100000,
                        0b0000000000000001,
                        0b0000000000001000};


uint8_t bitmap[8] =           {0b00000000,
                               0b01100110,
                               0b10011001,
                               0b10000001,
                               0b10000001,
                               0b01000010,
                               0b00100100,
                               0b00011000};
                               
                                //1111110000000110
uint16_t bericht3[8] =         {0b1101000100000110,
                                0b1011011000010010,
                                0b1001011001010100,
                                0b1100101000010110,
                                0b1100001010010110,
                                0b1001011000110100,
                                0b1001011000010011,
                                0b1101000000001110};
byte all_off1 = 0b00000000;
                    
boolean shiftLeftRight = false;

void setup() {
  //Instelen van de uitgangspinnen
  Serial.begin(9600);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);

  for(int x=0; x<8; x++)
  {
    bitmap[x]= ~bitmap[x];
  }
  int colommen =0;

  for (int rijen=0; rijen<8; rijen++)
  {
    uint16_t convers = 0;
    for (colommen =0; colommen<8; colommen++)
    {
      uint16_t temp = bitmap[colommen] >> rijen;
      temp &= 0b1;
       switch (colommen)
       {
        case 0:
         temp <<= 15;
         bericht[rijen] |= temp;
        break;
        case 1:
         temp <<= 14;
         bericht[rijen] |= temp;          
        break;
        case 2:
         temp <<= 10;
         bericht[rijen] |= temp;          
        break;
        case 3:
         temp <<= 4;
         bericht[rijen] |= temp;          
        break;
        case 4:
         temp <<= 9;
         bericht[rijen] |= temp;          
        break;
        case 5:
         temp <<= 2;
         bericht[rijen] |= temp;          
        break;
        case 6:
         temp <<= 1;
         bericht[rijen] |= temp;          
        break;
        case 7:
         temp <<= 12;
         bericht[rijen] |= temp;  
        break;
        
       }
       //Serial.println(bericht[colommen], BIN);
    }
    bericht[rijen] |= col_mask[rijen];
    Serial.println(bericht[rijen], BIN);
  }
}




void loop() {
  
    for(int tijd=0; tijd<200; tijd++){
      for(int i=0; i<8; i++){
        displayData(bericht[i]);
        //delay(1);
      }
    }
  
  
  
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


