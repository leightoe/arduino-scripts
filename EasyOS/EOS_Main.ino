// 2023 leighton tegland iii
// im too lazy to fully document this one with comments but luckily its pretty easy to figure out

#include "SevSeg.h"
#include "Adafruit_SleepyDog.h"
SevSeg sevseg;
#define LED_PIN 12
#define SPEAKER_PIN 11
String printin = "printed";
bool screentoggle = true;


void setup() {
  // put your setup code here, to run once:
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {3, 2, 8, 7, 6, 4, 5, 9};
  bool resistorsOnSegments = true;
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
  tone(SPEAKER_PIN, 150, 500);
  Serial.begin(9600);
  Serial.println("====================================\nEasyOS\n'commands' for a list of commands");
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void print() {
  Serial.println("");
}

void loop() {
  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if(command == "led on")
    {
      pinMode(LED_PIN, OUTPUT);
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is turned ON"); // send action to Serial Monitor
    }
    if(command == "led off")
    {
      pinMode(LED_PIN, OUTPUT);
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is turned OFF"); // send action to Serial Monitor
    }
    if(command == "speaker")
    {
      Serial.println("playing..."); // send action to Serial Monitor
      tone(SPEAKER_PIN, 50, 200);
      delay(500);
      tone(SPEAKER_PIN, 100, 200);
      delay(250);
      tone(SPEAKER_PIN, 200, 200);
    }
    if(command == "print")
    {
      Serial.println(printin); // send action to Serial Monitor
    }
    if(command == "reboot")
    {
      Serial.println("rebooting..."); // send action to Serial Monitor
      delay(20);
      int countdownMS = Watchdog.enable(4000);
    }
    if(command == "led blink")
    {
      Serial.println("blinking led"); // send action to Serial Monitor
      pinMode(LED_PIN, OUTPUT);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
    if(command == "screen toggle")
    {
      Serial.println("screen toggled"); // send action to Serial Monitor
      screentoggle = !screentoggle;
    }
    if(command == "commands")
    {
      Serial.println("List of commands:\n commands: displays all commands and what they do\n print: serial print test\n led on/off: toggles led on or off\n led blink: blinks led\n speaker: plays speaker test tones\n screen toggle: toggles screen on or off\n reboot: preforms a soft reboot"); // send action to Serial Monitor
    }

  }

  if (screentoggle)
//Display numbers one by one with delay
   for(int i = 0; i < 10; i++)
   {
     sevseg.setNumber(i);
     sevseg.refreshDisplay(); 
     delay(20);
   }
  if(!screentoggle)
   {
     sevseg.blank(); 
   }
  
}
