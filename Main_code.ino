#include <dht.h>        // Include library
#define outPin 2       // Defines pin number to which the sensor is connected
#define bmppin 3
#include<LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>
dht DHT;
dht BMP;                // Creates a DHT object

SoftwareSerial B(6,7);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  B.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(10,OUTPUT);   //relay
  pinMode(8,OUTPUT);   //fan
  pinMode(9,OUTPUT);    //cpap
  pinMode(A0,INPUT);
}

void loop() {
  int readData = DHT.read11(outPin);
  int readData1 = BMP.read11(bmppin);

  float t = DHT.temperature;        // Read temperature
  float h = DHT.humidity;           // Read humidity
  B.print("Temperature:");
  B.println(t);
  B.print("Humidity:");
  B.println(h);  
  float h1 = BMP.humidity;           // Read humidity 

  int pressure=map(h1,50,100,700,850);
  B.print("Breath Pressure:");
  B.println(pressure);

  int ana=analogRead(A0);
  int hr=map(ana,300,1023,60,90);

  
  if(hr>60 && hr<90){
    lcd.setCursor(9,1);
    lcd.print("HR:");
    lcd.print(hr);
    B.print("HR:");
    B.println(hr);
  }
  else{
      lcd.setCursor(9,1);
      lcd.print("HR:");
      lcd.println("nan");
  }

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t);
  lcd.print("C");
  lcd.print(" H:");
  lcd.print(h);
  lcd.print("%");
  
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.print(pressure);
  lcd.print("Hg");
  
  
  if(t<24){
    digitalWrite(10,LOW);
    digitalWrite(8,LOW);
    B.print("Air Controller:");
    B.println("Heater On");
  
  }
  else{
    digitalWrite(10,HIGH);
    digitalWrite(8,HIGH); 
      B.print("Air Controller:");
      B.println("Cooler On");
  }
  
  if(pressure<780){     //pressure
    digitalWrite(9,HIGH);
      B.print("Cpap Status:");
      B.println("On");
  }else{
    digitalWrite(9,LOW);
      B.print("Cpap Status:");
      B.println("OFF");
  }
  
  
    Serial.print("Temperature = ");
    Serial.print(t);
    Serial.print("°C ");
    Serial.print("Humidity = ");
    Serial.print(h1);
    Serial.print("% ");
    Serial.print("Pressure:");
    Serial.println(pressure);  
  delay(1500);
  B.print("\n \n");

}
