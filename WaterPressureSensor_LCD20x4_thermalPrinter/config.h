#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <EEPROM.h>
#define TX_PIN 11 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 10 // Arduino receive   GREEN WIRE   labeled TX on printer

RTC_DS1307 rtc;
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
LiquidCrystal_I2C lcd(0x27, 20, 4);


#define LED_DS 7
#define O_DS   A0
#define LED_R  2
#define LED_G  6
#define PB1 9
#define PB2 13
#define TX_PIN 11 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 10 // Arduino receive   GREEN WIRE   labeled TX on printer
#define MSB 0
#define LSB 1
#define m_ 0.0015
#define c_ 0.15



char status;
double T, P, p0, a;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char namaBulan[12][12] = {"Januari", "Fabruari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

int jam, menit,tanggal,bulan,tahun,hari;
float val_kgpcm2;
unsigned long previousMillis = 0;
const long interval = 1000;

unsigned long buttonMillis;

float setpoint=0;
int raw_sensor;
float val_sensor;
