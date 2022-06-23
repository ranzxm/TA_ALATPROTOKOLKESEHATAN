#include <Bildr-MLX90614.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int trigPin = 2;
int echoPin = 3; 
LiquidCrystal_I2C lcd(0x27,16,2);
MLX90614 sensor;
int BUZZER = 5;
const byte SIMBOLDERAJAT = B11011111;

void setup()
{
  lcd.init();                  
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop()
{
  float celsius = sensor.getC();
  //Tampilkan di serial monitor untuk suhu
  Serial.print("Object = ");
  Serial.print(celsius);
  Serial.println("*C");
  
  
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(duration);
  Serial.print("Jarak Telapak Tangan : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
   
  //Apabila Jarak dibawah 8 cm dan suhu >37 celcius
  if (distance < 8){
  if(celsius > 30)
  
  {
    
    //apabila ingin menambahkan Alarm
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- ANDA DEMAM --");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(celsius*1.090); //*1.125 (UNTUK PENGALI KALIBRASI)
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");

    delay(100);
    
  }
  }

  //Apabila Jarak dibawah 8 cm dan suhu <37 celcius
  if (distance < 8){
  if(celsius < 30)
   {
    digitalWrite(BUZZER, LOW);
    delay(1000);
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- ANDA SEHAT --");
    lcd.setCursor(0, 1);
    lcd.print("Suhu: ");
    lcd.setCursor(7, 1);
    lcd.print(celsius);
    lcd.setCursor(12, 1);
    lcd.write(SIMBOLDERAJAT);
    lcd.setCursor(13, 1);
    lcd.print("C");

    delay(100);
    
  }
  }

  
   if (distance > 8) {
    delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DEKATKAN TELAPAK");
    lcd.setCursor(0, 1);
    lcd.print("TANGAN ANDA");
    delay(0);
    }
  
}
