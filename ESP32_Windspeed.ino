#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// LCD
hd44780_I2Cexp lcd;

// Sensor pin
#define SENSOR_PIN 27

// Variables
volatile unsigned long pulseCount = 0;

unsigned long previousMillis = 0;

float rpm = 0.0;
float windSpeed = 0.0;

// Calibration settings
const int PULSES_PER_REV = 1;

// Temporary calibration factor
const float WIND_FACTOR = 1.0;

// Interrupt function
void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {

  Serial.begin(115200);

  // Initialize I2C
  Wire.begin(21, 22);

  // Initialize LCD
  int status = lcd.begin(16, 2);

  if (status) {
    Serial.println("LCD initialization failed");
    while (true) {
      delay(100);
    }
  }

  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("WIND SPEED SYS");

  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  // Sensor initialization
  pinMode(SENSOR_PIN, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(SENSOR_PIN),
    countPulse,
    FALLING
  );

  delay(2000);

  lcd.clear();

  previousMillis = millis();
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {

    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    // RPM calculation
    rpm = (pulses * 60.0) / PULSES_PER_REV;

    // Wind speed estimation
    windSpeed = pulses * WIND_FACTOR;

    // LCD first row
    lcd.setCursor(0, 0);
    lcd.print("Wind: ");
    lcd.print(windSpeed, 2);
    lcd.print(" m/s  ");

    // LCD second row
    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print(rpm, 0);
    lcd.print("       ");

    // Serial monitor
    Serial.print("Pulses: ");
    Serial.print(pulses);

    Serial.print(" | RPM: ");
    Serial.print(rpm);

    Serial.print(" | Wind Speed: ");
    Serial.print(windSpeed);

    Serial.println(" m/s");

    previousMillis = currentMillis;
  }
}
