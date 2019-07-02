void print_sensor() {
  //  Serial.println();
  DateTime now = rtc.now();

  jam = now.hour();
  menit = now.minute();
  hari = now.dayOfTheWeek();
  tanggal = now.day();
  bulan = now.month();
  tahun = now.year();
  //    lcd.clear();



  if (val_sensor <= 0)
    val_sensor = 0;


  lcd.setCursor(0, 2);
  lcd.print("Pressure:");
  lcd.print(val_kgpcm2);
  lcd.print("Kg/cm2 ");
  lcd.setCursor(0, 0);
  lcd.print("FUEL PRESSURE GAUGE");
  lcd.setCursor(0, 1);
  lcd.print("DAIHATSU PAJAJARAN");

  lcd.setCursor(0, 3);
  if (jam >= 0 && jam < 10)
    lcd.print("0");
  if (jam >= 12 )
    lcd.print(jam - 12);
  else
    lcd.print(jam);
  lcd.print(":");
  if (menit >= 0 && menit < 10)
    lcd.print("0");
  lcd.print(menit);
  if (jam < 12)
    lcd.print(" AM  ");
  else
    lcd.print(" PM  ");

  if (tanggal >= 0 && tanggal < 10)
    lcd.print("0");
  lcd.print(tanggal);
  lcd.print('/');
  if (bulan >= 0 && bulan < 10)
    lcd.print("0");
  lcd.print(bulan);
  lcd.print('/');
  lcd.print(tahun);
  delay(1000);
}


void print_1() {
  printer.justify('C');
  printer.setSize('M');
  printer.println(F("Fuel Pressure Gauge"));
  printer.justify('C');
  printer.setSize('S');


  printer.println();
  //  printer.println(F("Sabtu 4 November"));
  printer.println("Bogor");
  printer.println(daysOfTheWeek[hari]);
  printer.print(tanggal);
  printer.print(" ");
  printer.print(namaBulan[bulan - 1]);
  printer.print(" ");
  printer.println(tahun);
  int jem;
  if (jam >= 12)
    jem = jam - 12;
  else jem = jam;
  if (jem >= 0 && jem < 10)
    printer.print(0);
  printer.print(jem);
  printer.print(":");
  if (menit >= 0 && menit < 10)
    printer.print(0);
  printer.print(menit);
  if (jam >= 12)
    printer.println(" PM");
  else
    printer.println(" AM");

  printer.println();
  printer.boldOn();
  printer.println(F("Spesification"));
  printer.boldOff();

  printer.justify('L');
  printer.print(F("Fuel Pressure : "));
  printer.print(setpoint);
  printer.println(F("Kg/cm2"));
  printer.println();
  printer.justify('C');
  printer.boldOn();
  printer.println(F("Inspection"));
  printer.boldOff();
  printer.justify('L');
  printer.print(F("Fuel Pressure : "));
  printer.print(val_sensor * 10.1972);
  printer.println(F("Kg/cm2"));
  printer.println();
  printer.justify('C');

  if (val_sensor >= setpoint)
    printer.println(F("Pressure OK"));
  else {
    printer.inverseOn();
    //    printer.println(F("        Replace Filter        "));
    printer.println(F("Replace Fuel Pump <3,3Kg/cm2"));
    printer.inverseOff();
  }

  printer.setSize('M');

  printer.println();
  printer.println(F("DSO Bogor"));
  printer.feed(3);
  printer.sleep();      // Tell printer to sleep
  delay(4000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  printer.setDefault();
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void printSetDensity() {
  lcd.setCursor(0, 1);
  lcd.print("Limit Value:");
  lcd.print(setpoint + 0.1);
  lcd.print("   ");
}

int buttonAction(int pin, int tunda, int action) {
  int stat = 0;
  switch (pin) {
    case PB1:
      switch (action) {
        case 3 :
          if (!digitalRead(PB1)) {
            while (!digitalRead(PB1))
              delay(1);
            setpoint -= 0.02;
          }
          break;
      }
      break;

    case PB2:
      switch (action) {
        case 3 :
          if (!digitalRead(PB2)) {
            while (!digitalRead(PB2))
              delay(1);
            setpoint += 0.02;
          }
          break;

        case 4:
          if (!digitalRead(PB2)) {

            previousMillis = millis();
            while (!digitalRead(PB2)) {
              currentMillis = millis();
              if (currentMillis - previousMillis >= 1000) {
                previousMillis = currentMillis;
                stat = 1;
                break;
              }
            }

          }

      }
      break;


  }
  setpoint = min(setpoint, 0.5);
  setpoint = max(setpoint, 0);
  if (stat)
    return true;
  else
    return false;
}

