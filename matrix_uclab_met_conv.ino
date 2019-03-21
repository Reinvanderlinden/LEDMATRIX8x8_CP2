//Definiëren van de uitganspinnen
const int shiftClockPin = 5;  //SH
const int latchClockPin = 6;  //ST
const int serialInputPin = 9; //DS
const int frames = 3;
uint16_t bericht[frames][8];
uint8_t bitmapInv[frames][8];

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
    0b01111000,
    0b11111100,
    0b11001100,
    0b11001100,
    0b11111100,
    0b11111000,
    0b11000000,
    0b11000000

  },
  { 0b00000000,
    0b11000110,
    0b11101110,
    0b01111100,
    0b00111000,
    0b01111100,
    0b11101110,
    0b11000110

  },
  {
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111100,
    0b11111100
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
    for (int tijd = 0; tijd < 200; tijd++) {
      for (int i = 0; i < 8; i++) {
        displayData(bericht[f][i]);
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


