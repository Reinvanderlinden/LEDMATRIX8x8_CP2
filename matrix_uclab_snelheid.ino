//Definiëren van de uitganspinnen
#define outputA 6
#define outputB 7



const int shiftClockPin = 5;  //SH
const int latchClockPin = 8;  //ST
const int serialInputPin = 9; //DS
const int frames = 5;
uint16_t bericht[frames][8];
uint8_t bitmapInv[frames][8];

int counter = 100; 
int aState;
int aLastState;
void snelheid ();

uint16_t col_mask[8] = {
  0b0000000000001000,
  0b0000000000000001,
  0b0000000000100000,
  0b0000000010000000,
  0b0000100000000000,
  0b0000000001000000,
  0b0010000000000000,
  0b0000000100000000
};


uint8_t bitmap[frames][8] =   {{
    0b00111100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00111100
  },
  { 0b00000000,
    0b01100110,
    0b10011001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00100100,
    0b00011000
  },
  {
    0b11000011,
    0b11100111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000
  },
  {
    0b00111100,
    0b01111110,
    0b11100111,
    0b11000011,
    0b11000011,
    0b11100111,
    0b01111110,
    0b00111100
  },
  {
    0b00000000,
    0b11000110,
    0b11000110,
    0b11000110,
    0b11000110,
    0b11000110,
    0b11111110,
    0b01111100
  }

};



byte all_off1 = 0b00000000;

boolean shiftLeftRight = false;

void setup() {
  //Instelen van de uitgangspinnen
  Serial.begin(9600);
  pinMode(shiftClockPin, OUTPUT);
  pinMode(latchClockPin, OUTPUT);
  pinMode(serialInputPin, OUTPUT);
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);

  //attachInterrupt(digitalPinToInterrupt(outputA),snelheid, RISING);
  //attachInterrupt(digitalPinToInterrupt(outputB),snelheid, RISING);
  
  for (int f = 0; f < frames; f++)
  {
    for (int x = 0; x < 8; x++)
    {
      bitmap[f][x] = ~bitmap[f][x];
    }
    int colommen = 0;
    for (int rijen = 0; rijen < 8; rijen++)
    {
      uint16_t convers = 0;
      for (colommen = 0; colommen < 8; colommen++)
      {
        uint16_t temp = bitmap[f][colommen] >> rijen;
        temp &= 0b1;
        switch (colommen)
        {
          case 0:
            temp <<= 15;
            bericht[f][rijen] |= temp;
            break;
          case 1:
            temp <<= 14;
            bericht[f][rijen] |= temp;
            break;
          case 2:
            temp <<= 10;
            bericht[f][rijen] |= temp;
            break;
          case 3:
            temp <<= 4;
            bericht[f][rijen] |= temp;
            break;
          case 4:
            temp <<= 9;
            bericht[f][rijen] |= temp;
            break;
          case 5:
            temp <<= 2;
            bericht[f][rijen] |= temp;
            break;
          case 6:
            temp <<= 1;
            bericht[f][rijen] |= temp;
            break;
          case 7:
            temp <<= 12;
            bericht[f][rijen] |= temp;
            break;

        }
        //Serial.println(bericht[colommen], BIN);
      }
      bericht[f][rijen] |= col_mask[rijen];
      Serial.println(bericht[f][rijen], BIN);
    }
  }
}
void loop() {
  for (int f = 0; f < frames; f++) {
    for (int tijd = 0; tijd < counter; tijd++) {
      for (int i = 0; i < 8; i++) {
        displayData(bericht[f][i]);
        snelheid();
      }
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

void snelheid() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) {
      if (counter <= 300)
      {
       counter ++;
      }
     } else {
      if (counter >= 10){ 
       counter --;
      }
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }

