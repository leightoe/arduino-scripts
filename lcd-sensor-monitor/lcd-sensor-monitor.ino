// 2023 leighton tegland iii

#include <Arduino.h>
#include "DHT_Async.h" // requires "dht11 sensors non-blocking" library by toan nguyen
#include <LiquidCrystal.h> // install liquidcrystal library if you dont already have it
#define DHT_SENSOR_TYPE DHT_TYPE_11 // sets sensor model type
LiquidCrystal lcd(4, 6, 10, 11, 12, 13); // lcd pins in order of d7 to rs (d3-0 unused)
static const int DHT_PIN = 2; // dht11 sensor digital pin
static const int BACKLIGHT_PIN = 3; // backlight analog pin (3 recommended)
DHT_Async dht_sensor(DHT_PIN, DHT_SENSOR_TYPE);
char temp[]="";
char humid[]="";

void setup() {
  // put your setup code here, to run once:
  pinMode(BACKLIGHT_PIN, OUTPUT);
  analogWrite(BACKLIGHT_PIN, 50); // change 50 to however bright you want your backlight to be, or simply connect backlight to 3.3v header (note: anything above 80 not recomended, dont connect to 5v header)
  lcd.begin(16, 2); // sets amount of spaces/lines
  lcd.noAutoscroll();
}

static bool measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    /* Measure once every four seconds. */
    if (millis() - measurement_timestamp > 4000ul) { // sets how long to wait before refreshing/updating
        if (dht_sensor.measure(temperature, humidity)) {
            measurement_timestamp = millis();
            return (true);
        }
    }

    return (false);
}

void loop() {
    float temperature;
    float humidity;

    if (measure_environment(&temperature, &humidity)) {
        lcd.setCursor(0, 0); // sets to line 1
        lcd.print("T = ");
        lcd.print(temperature * 1.8 + 32, 1); // converts celsius to fahrenheit & prints it
        lcd.print((char)223); // prints degree symbol
        lcd.print("F");
        lcd.setCursor(0, 1); // sets to line 2
        lcd.print("H = ");
        lcd.print(humidity, 1);
        lcd.print("%");
    }

}
