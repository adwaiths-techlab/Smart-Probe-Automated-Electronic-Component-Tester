/*
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Common LCD address and size

// Mode control
int buttonPins[] = {2, 3, 4};
int currentMode = 0;
bool lastButtonState[] = {HIGH, HIGH, HIGH};

// Timing for debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 70;

// Capacitance measurement pins
#define capAnalogPin      A1
#define chargePin         13
#define dischargePin      8
float resistorValue = 10000.0F; // 10k ohm

// Resistance measurement pins
#define resAnalogPin      A0
float Vin = 5.0;
float R1 = 10000.0;

// Diode tester pins
#define testPin           7
#define readPin           A3

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   SMART PROBE");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLACE COMPONENT");
  delay(1500);
  lcd.clear();

  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, INPUT);
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, HIGH);

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    bool currentState = digitalRead(buttonPins[i]);
    if (lastButtonState[i] == HIGH && currentState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
      lastDebounceTime = millis();
      if (currentMode == i + 1) {
        currentMode = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mode OFF");
      } else {
        currentMode = i + 1;
        lcd.clear();
      }
    }
    lastButtonState[i] = currentState;
  }

  switch (currentMode) {
    case 1: measureResistance(); break;
    case 2: measureCapacitance(); break;
    case 3: testDiode(); break;
  }
}

void measureResistance() {
  int raw = analogRead(resAnalogPin);
  lcd.setCursor(0, 0);
  lcd.print("Resistance Meter   ");
  lcd.setCursor(0, 1);
  if (raw == 0) {
    lcd.print("  Open Circuit     ");
  } else {
    float buffer = raw * Vin;
    float Vout = buffer / 1023.0;
    if (Vout == 0) return;
    buffer = (Vin / Vout) - 1;
    float R2 = R1 * buffer;
    lcd.print("                ");
    lcd.setCursor(0, 1);
    if (R2 > 999.99) {
      lcd.print(R2 / 1000.0, 2);
      lcd.print(" K Ohm");
    } else {
      lcd.print(R2, 1);
      lcd.print(" Ohm");
    }
  }
  delay(1000);
}

void measureCapacitance() {
  digitalWrite(chargePin, HIGH);
  unsigned long startTime = micros();
  while (analogRead(capAnalogPin) < 648) {}
  unsigned long elapsedTime = micros() - startTime;
  float microFarads = ((float)elapsedTime / resistorValue) - 0.015;

  lcd.setCursor(0, 0);
  lcd.print("SCALE:  1nF-4F     ");
  lcd.setCursor(0, 1);
  if (microFarads > 1) {
    lcd.print(microFarads);
    lcd.print(" uF         ");
  } else {
    float nanoFarads = microFarads * 1000.0;
    lcd.print(nanoFarads);
    lcd.print(" nF         ");
  }
  delay(500);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  while (analogRead(capAnalogPin) > 0) {}
  pinMode(dischargePin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("DISCHARGING.....  ");
  delay(500);
}

void testDiode() {
  int analogValue = analogRead(readPin);
  float voltage = analogValue * (5.0 / 1023.0);

  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print(" V     ");

  lcd.setCursor(0, 1);
  if (voltage > 2.3 && voltage < 3) {
    lcd.print("Diode OK       ");
  } else {
    lcd.print("Faulty/Opposite  ");
  }
  delay(1000);
}
*/
//-----------------------------------------------------------------------------------------------------

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Common LCD address and size

// Mode control
int buttonPins[] = {2, 3, 4};
int currentMode = 0;
bool lastButtonState[] = {HIGH, HIGH, HIGH};

// Timing for debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 70;

// Capacitance measurement pins
#define capAnalogPin      A1
#define chargePin         13
#define dischargePin      8
float resistorValue = 10000.0F; // 10k ohm

// Resistance measurement pins
#define resAnalogPin      A0
float Vin = 5.0;
float R1 = 10000.0;

// Diode tester pins
#define testPin           7
#define readPin           A3

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   SMART PROBE");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PLACE COMPONENT");
  delay(1500);
  lcd.clear();

  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, INPUT);
  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, HIGH);

  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 3; i++) {
    bool currentState = digitalRead(buttonPins[i]);
    if (lastButtonState[i] == HIGH && currentState == LOW && (millis() - lastDebounceTime) > debounceDelay) {
      lastDebounceTime = millis();
      if (currentMode == i + 1) {
        currentMode = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Mode OFF");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Select Mode");


      } else {
        currentMode = i + 1;
        lcd.clear();
      }
    }
    lastButtonState[i] = currentState;
  }

  switch (currentMode) {
    case 1: measureResistance(); break;
    case 2: measureCapacitance(); break;
    case 3: testDiode(); break;
  }
}

// --- Updated resistance measurement function ---
void measureResistance() {
  int raw = analogRead(resAnalogPin);

  lcd.setCursor(0, 0);
  lcd.print("Resistance Meter   ");
  lcd.setCursor(0, 1);

  if (raw == 0) {
    lcd.print("      Open      ");
  } else {
    float buffer = raw * Vin;
    float Vout = buffer / 1023.0;

    if (Vout == 0) return;

    buffer = (Vin / Vout) - 1;
    float R2 = R1 * buffer;

    lcd.print("                "); // Clear line
    lcd.setCursor(0, 1);

    if (R2 > 999.99) {
      lcd.print(R2 / 1000.0, 2);
      lcd.print(" K Ohm");
    } else {
      lcd.print(R2, 1);
      lcd.print(" Ohm");
    }
  }

  delay(1000);
}

void measureCapacitance() {
  digitalWrite(chargePin, HIGH);
  unsigned long startTime = micros();
  while (analogRead(capAnalogPin) < 648) {}
  unsigned long elapsedTime = micros() - startTime;
  float microFarads = ((float)elapsedTime / resistorValue) - 0.015;

  lcd.setCursor(0, 0);
  lcd.print("SCALE:  1nF-4F     ");
  lcd.setCursor(0, 1);
  if (microFarads > 1) {
    lcd.print(microFarads);
    lcd.print(" uF         ");
  } else {
    float nanoFarads = microFarads * 1000.0;
    lcd.print(nanoFarads);
    lcd.print(" nF         ");
  }
  delay(500);
  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);
  while (analogRead(capAnalogPin) > 0) {}
  pinMode(dischargePin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("DISCHARGING.....  ");
  delay(500);
}

void testDiode() {
  int analogValue = analogRead(readPin);
  float voltage = analogValue * (5.0 / 1023.0);

  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(voltage, 2);
  lcd.print(" V     ");

  lcd.setCursor(0, 1);
  if (voltage > 2.3 && voltage < 3) {
    lcd.print("Diode OK       ");
  } else {
    lcd.print("Faulty/Opposite  ");
  }
  delay(1000);
}

