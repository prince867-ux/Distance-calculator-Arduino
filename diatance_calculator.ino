#include <LedControl.h>
#define DIN 8
#define CLK 10
#define CS 9
#define TRIG_PIN 11
#define ECHO_PIN 12
LedControl lc = LedControl(DIN, CLK, CS, 1);

byte digits[10][8] = {
  { // 0
    B00111100,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B00111100,
    B00000000
  },
  { // 1
    B00011000,
    B00111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00111100,
    B00000000
  },
  { // 2
    B00111100,
    B01100110,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01111110,
    B00000000
  },
  { // 3
    B00111100,
    B01100110,
    B00000110,
    B00011100,
    B00000110,
    B01100110,
    B00111100,
    B00000000
  },
  { // 4
    B00001100,
    B00011100,
    B00101100,
    B01001100,
    B01111110,
    B00001100,
    B00001100,
    B00000000
  },
  { // 5
    B01111110,
    B01100000,
    B01111100,
    B00000110,
    B00000110,
    B01100110,
    B00111100,
    B00000000
  },
  { // 6
    B00111100,
    B01100110,
    B01100000,
    B01111100,
    B01100110,
    B01100110,
    B00111100,
    B00000000
  },
  { // 7
    B01111110,
    B00000110,
    B00001100,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00000000
  },
  { // 8
    B00111100,
    B01100110,
    B01100110,
    B00111100,
    B01100110,
    B01100110,
    B00111100,
    B00000000
  },
  { // 9
    B00111100,
    B01100110,
    B01100110,
    B00111110,
    B00000110,
    B01100110,
    B00111100,
    B00000000
  }
};

byte warning[8] = {
  B00011000,
  B00111100,
  B01111110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
};

byte danger[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};

void setup() {
  Serial.begin(9600);
  Serial.println("Ultrasonic Distance Display System");
  Serial.println("===================================");
  
  
  lc.shutdown(0, false);      // Wake up display
  lc.setIntensity(0, 8);      // Set brightness (0-15)
  lc.clearDisplay(0);         // Clear display
  Serial.println("LED Matrix: Ready");
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Ultrasonic Sensor: Ready");
  pinMode(3,OUTPUT);
  
  startupAnimation();
  
  Serial.println("\nSystem Ready!");
  Serial.println("Measuring distance...");
  Serial.println("Display shows distance in cm when < 10cm");
  Serial.println("=========================================\n");
}

void loop() {
  float distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10.0 && distance > 0) {
    int displayNumber = (int)distance;
    if (displayNumber < 0) displayNumber = 0;
    if (displayNumber > 9) displayNumber = 9;
    
    Serial.print("Displaying: ");
    Serial.println(displayNumber);

    displayDigit(displayNumber);
    if (distance < 9) {
      delay(200);
      lc.clearDisplay(0);
      delay(100);
      displayDigit(displayNumber);
      digitalWrite(3,LOW);
    }
  } 
  else if (distance >= 10.0 && distance <= 400) {
    displayDoubleDash();
    digitalWrite(3,HIGH);
    delay(1000);
  }
  else {
    displayX();
    
    
  }
  
  delay(500);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout

  float distance = duration * 0.0343 / 2.0;
  
  if (duration == 0) {
    return -1.0; 
  }
  return distance;
}
void displayDigit(int number) {
  if (number >= 0 && number <= 9) {
    for (int i = 0; i < 8; i++) {
      lc.setRow(0, i, digits[number][i]);
    }
  }
}

void displayDoubleDash() {
  byte doubleDash[8] = {
    B00000000,
    B00000000,
    B00000000,
    B01100110,
    B01100110,
    B00000000,
    B00000000,
    B00000000
  };
  
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, doubleDash[i]);
  }
}

void displayX() {
  byte xSymbol[8] = {
    B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001
  };
  
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, xSymbol[i]);
  }
}

void displayWarning() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, warning[i]);
  }
}

void displayDanger() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, danger[i]);
  }
}


void startupAnimation() {
  // Count from 0 to 9
  for (int i = 0; i < 10; i++) {
    displayDigit(i);
    delay(150);
  }
  

  byte ready[8] = {
    B00000000,
    B01111110,
    B00010010,
    B00010010,
    B00010010,
    B01111110,
    B00000000,
    B00000000
  };
  
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, ready[i]);
  }
  delay(1000);
  
  lc.clearDisplay(0);
  delay(500);
}

void displayDistanceWithDecimal(float distance) {
  if (distance < 10.0 && distance >= 0) {
    int wholePart = (int)distance;
    int decimalPart = (int)((distance - wholePart) * 10);
    
    displayDigit(wholePart);
    
    
    delay(300);
    byte rowWithDot = digits[wholePart][3] | B00000001; 
    
    delay(500);
  }
}