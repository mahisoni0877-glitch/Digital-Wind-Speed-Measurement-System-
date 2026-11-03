# Circuit Connections

## Hardware Components
- ESP32 Development Board
- Hall Effect Anemometer
- 16x2 I2C LCD
- Breadboard
- Jumper Wires

## ESP32 to LCD Connections

| LCD Pin | ESP32 Pin |
|---|---|
| VCC | 5V (VIN) |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

## Anemometer to ESP32 Connections

| Anemometer Wire | ESP32 Connection |
|---|---|
| Red | VIN (5V) |
| White | GND |
| Green | GPIO 27 (Signal) |

## Working Principle

1. Wind rotates the anemometer.
2. The Hall Effect sensor generates electrical pulses.
3. ESP32 detects and counts the pulses.
4. RPM is calculated using pulse frequency.
5. Wind speed is calculated using the sensor calibration factor.
6. RPM and wind speed readings are displayed on the 16x2 I2C LCD.

## Safety Note

The ESP32 GPIO pins are not 5V tolerant. Ensure the sensor signal reaching GPIO 27 does not exceed 3.3V. Use an appropriate voltage divider or logic-level shifter if required.
