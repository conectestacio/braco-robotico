#include <SoftwareSerial.h> // TX RX software library for bluetooth

#include <Servo.h> // servo library 
Servo myservo1, myservo2; // servo name

int bluetoothTx = 10; // bluetooth tx to 10 pin
int bluetoothRx = 11; // bluetooth rx to 11 pin
#define pontH1 6
#define pontH2 7
#define sensor1 8
#define sensor2 9
#define eletroima 4
int a,b,d,e;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo1.attach(3); // attach servo signal wire to pin 9
  myservo2.attach(5);
  //Setup usb serial connection to computer
  Serial.begin(9600);
  pinMode(pontH1, OUTPUT);
  pinMode(pontH2, OUTPUT);
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);
  pinMode(eletroima, OUTPUT);

  digitalWrite(pontH1, HIGH);
  digitalWrite(pontH2, LOW);
  digitalWrite(eletroima, LOW);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()>= 2 )
  {
    unsigned int servopos = bluetooth.read();
    unsigned int servopos1 = bluetooth.read();
    unsigned int realservo = (servopos1 *256) + servopos;
    char c = bluetooth.read();
    int servo1 = realservo;
    int servo2 = realservo;
    Serial.println(realservo);

    if (realservo >= 1000 && realservo <1180) {
      servo1 = map(servo1, 1000, 1180, 0, 180);
      myservo1.write(servo1);
      Serial.println("Servo 1 ON");
      delay(10);
    }
    if (realservo >= 2000 && realservo <2180) {
      servo2 = map(servo2, 2000, 2180, 0, 180);
      myservo2.write(servo2);
      Serial.println("Servo 2 ON");
      delay(10);
    }
    if (c == 'A' && !digitalRead(sensor1)){//se nao funcionar tente 9 ou aterar para "realservo=2500"//
      digitalWrite(pontH1, HIGH);
      digitalWrite(pontH2, LOW);
      Serial.println("subindo");
      delay(10);
    }
    if (c == 'B' && !digitalRead(sensor2)){//se nao funcionar tente 10  ou aterar para "realservo=2600"//
      digitalWrite(pontH2, HIGH);
      digitalWrite(pontH1, LOW);
      Serial.println("descendo");
      delay(10);
    }
    if (c == 'C') digitalWrite(eletroima, HIGH);//se nao funcionar tente 11 ou aterar para "realservo=2700"//
    Serial.println("ima ON");
      delay(10);
    if (c == 'D') digitalWrite(eletroima, LOW);//se nao funcionar tente 12  ou aterar para "realservo=2800"//
    Serial.println("ima OFF");
      delay(10);
    if (c == 'E'){
      a = servo1;
      b = servo2;
    } 
    if (c == 'F'){
      d = servo1;
      e = servo2;
    } 
    if (c == 'G') {
      myservo1.write(a);
      myservo2.write(b);
      if (!digitalRead(sensor2)){
      digitalWrite(pontH2, HIGH);
      digitalWrite(pontH1, LOW);}
      delay(10000);
      digitalWrite(eletroima, HIGH);
      if (!digitalRead(sensor1)){
      digitalWrite(pontH1, HIGH);
      digitalWrite(pontH2, LOW);}
      delay(10000);
      myservo1.write(d);
      myservo2.write(e);
      if (!digitalRead(sensor2)){
      digitalWrite(pontH2, HIGH);
      digitalWrite(pontH1, LOW);}
      delay(10000);
      digitalWrite(eletroima, LOW);
    }
   }
}
