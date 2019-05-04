#include "config.h"
float offset = 0;
void setup()
{
  Serial.begin(9600);

  pinMode(PB1, 0);
  pinMode(PB2, 0);
  pinMode(PB1, 0);
  pinMode(PB2, 0);
  digitalWrite(LED_R, 1);
  digitalWrite(LED_G, 1);

  int val1 = EEPROM.read(MSB);
  int val2 = EEPROM.read(LSB);
  setpoint = ((val1 * 255) + val2) / 100.0;
  Serial.println(val1);
  Serial.println(val2);
  Serial.println(setpoint);
  delay(1000);
  lcd.begin();
  lcd.backlight();
  lcd.print("Welcome...");
  lcd.setCursor(0, 1);
  lcd.print("Daihatsu Pajajaran");
  delay(1500);
  lcd.setCursor(0, 2);
  lcd.print("initializing...");
  delay(1000);
  pinMode(7, 1);
  pinMode(6, 1);
  pinMode(2, 1);
  mySerial.begin(9600);  // Initialize SoftwareSerial
  printer.begin();

  Serial.println("REBOOT");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  delay(10);
  lcd.setCursor(0, 2);
  lcd.print("Set limit:");
  lcd.print(setpoint);
  lcd.print("Kg/cm2");
  delay(2000);
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  delay(10);
  lcd.clear();
}

unsigned long currentMillis;
void loop()
{
  bool led = 0;
  raw_sensor = analogRead(A0);
  val_sensor = m_ * raw_sensor - c_;
  val_kgpcm2 = abs(val_sensor * 10.1972);
  currentMillis = millis();
  if (val_sensor >= setpoint)
    led = 1;
  digitalWrite(LED_G, led);
  digitalWrite(LED_R, !led);
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    print_sensor();
  }

  if (!digitalRead(PB1))
  {
    buttonMillis = millis();
    while (!digitalRead(PB1))
    {
      currentMillis = millis();
      if (currentMillis - buttonMillis >= interval)
      {
        print_1();
      }
    }
  }

//  if (!digitalRead(PB2))
//  {
    buttonMillis = millis();
    while (!digitalRead(PB2))
    {
      currentMillis = millis();
      if (currentMillis - buttonMillis >= interval)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Set Limit");
        int stat = 0;
        while (1)
        {
          currentMillis = millis();
          if (currentMillis - previousMillis >= 50)
          {
            previousMillis = currentMillis;
            printSetDensity();
          }
          if (!digitalRead(PB2))
          {
            while (!digitalRead(PB2))
            {
              currentMillis = millis();
              if (currentMillis - previousMillis >= interval)
              {
                previousMillis = currentMillis;
                Serial.println(setpoint);
                int val1 = (int)(setpoint * 100) / 255;
                int val2 = (int)(setpoint * 100) % 255;

                Serial.println(val1);
                Serial.println(val2);

                delay(1000);

                EEPROM.write(MSB, val1);
                EEPROM.write(LSB, val2);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("set limit changed");
                delay(1500);
                stat = 1;
                break;
              }
            }
            setpoint += 0.1;
          }
          if (!digitalRead(PB1))
          {
            while (!digitalRead(PB1))
              delay(1);
            setpoint -= 0.1;
          }
          setpoint = min(setpoint, 12.2);
          setpoint = max(setpoint, 0);
          if (stat)
            break;
        }
      }
    }
  }
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == 'a')
      print_1();
  }
}
