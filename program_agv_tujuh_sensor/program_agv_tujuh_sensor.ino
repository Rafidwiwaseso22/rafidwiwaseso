int trigPin = 23;
int echoPin = 22;
long waktu;
int jarak;

int trigPin2 = 21;
int echoPin2= 19;
long waktu2;
int jarak2;

const int sensor1 = 18; // sensor ir 1
const int sensor2 = 5; // sensor ir 2
const int sensor3 = 34; // sensor ir 3
const int sensor4 = 39; // sensor ir 4
const int sensor5 = 36; // sensor ir 5
const int sensor6 = 4; // sensor ir 6
const int sensor7 = 15; // sensor ir 7

// inialisasi variabel data 1 sampai 4
int data1, data2, data3,data4,data5,data6,data7;

int Relay1 = 2;

int Button1 = 33; // berangkat
int Button2 = 32; // start/stop
int Button3 = 35; // pulang


int nilai1, nilai2, nilai3;

#define Rpwm1 25
#define Lpwm1 26
#define Rpwm2 14
#define Lpwm2 12
#define PWM1 27
#define PWM2 13


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (Button1,INPUT);
  pinMode (Button2,INPUT);
  pinMode (Button3,INPUT);

  pinMode(Rpwm1, OUTPUT);
  pinMode(Lpwm1, OUTPUT);
  pinMode(Rpwm2, OUTPUT);
  pinMode(Lpwm2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  
  pinMode(Relay1, OUTPUT);

// inialisasi pin sensor sebagai input
 pinMode(sensor1, INPUT);
 pinMode(sensor2, INPUT);
 pinMode(sensor3, INPUT);
 pinMode(sensor4, INPUT);
 pinMode(sensor5, INPUT);
 pinMode(sensor6, INPUT);
 pinMode(sensor7, INPUT);
  digitalWrite(Relay1, HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 data1 = digitalRead(sensor1);
 data2 = digitalRead(sensor2);
 data3 = digitalRead(sensor3);
 data4 = digitalRead(sensor4);
 data5 = digitalRead(sensor5);
 data6 = digitalRead(sensor6);
 data7 = digitalRead(sensor7);
 nilai1 = digitalRead(Button1);
 nilai2 = digitalRead(Button2);
 nilai3 = digitalRead(Button3);
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 waktu = pulseIn(echoPin, HIGH);
 jarak = waktu*0.034/2;
 digitalWrite(trigPin2, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2, LOW);
 waktu2 = pulseIn(echoPin2, HIGH);
 jarak2 = waktu2*0.034/2;
 Serial.print("Jarak2: ");
Serial.println(jarak2);
 Serial.print("Jarak: ");
Serial.println(jarak);
 Serial.print("nilai1: ");
Serial.println(nilai1);
 Serial.print("nilai2: ");
Serial.println(nilai2);
 Serial.print("nilai3: ");
Serial.println(nilai3);
 Serial.print("data1: ");
Serial.println(data1);
 Serial.print("data2: ");
Serial.println(data2);
 Serial.print("data3: ");
Serial.println(data3);
 Serial.print("data4: ");
Serial.println(data4);
 Serial.print("data5: ");
Serial.println(data5);
 Serial.print("data6: ");
Serial.println(data6);
 Serial.print("data7: ");
Serial.println(data7);
 delay(10);
  // masing2 variabel data menyimpan hasil pembacaan sensor
 // berupa logic LOW/HIGH


 if (nilai2 == HIGH) {
Stop();  
relayoff();
 }
 else if (nilai1 == HIGH) {
 tracingline();
 }
 else if (nilai3 == HIGH) {
tracingback();
 }
}

void tracingline (){
if (jarak <= 50){
  Stop();
  relayoff();
}

else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeftpenuh();
 }
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
 //kanan

relayonmaju();
turnLeft();
 }
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeft();
 }
 
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeft();
 }

 else if (data1 == LOW && data2 == LOW && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeft();
 }

 else if (data1 == LOW && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeftpenuh();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
turnLeft();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
moveForwardLeft();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == LOW&& data7 == HIGH)
 {
 //kanan
relayonmaju();
turnRight();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmaju();
moveForwardRight();
 }
 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kiri
relayoff();
Stop();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == LOW)
 {
 //kanan
relayonmaju();
turnRightpenuh();
 }
 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == LOW && data7 == LOW)
 {
 //kanan
relayonmaju();
turnRight();
 
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == LOW && data6 == LOW && data7 == LOW)
 {
 //berhenti
 relayonmaju();
 turnRight();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW)
 {
 //berhenti
 relayonmaju();
 turnRight();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW){
  //stop
  turnRight();
  relayonmaju();
 }

  else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW){
  turnRightpenuh();
  relayonmaju();
}
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH){
  moveForward();
  relayonmaju();
}
 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveForwardRight();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveForwardLeft();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveForwardLeft2();
  relayonmaju();
 }

  else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveForwardRight2();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveForward();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveForwardRight2();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveForwardLeft2();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveForwardRight2();
  relayonmaju();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveForwardLeft2();
  relayonmaju();
 }

 else if (data1 ==LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW)
 {
  Stop();
  relayoff();
 }
}
void tracingback(){ 
if (jarak2 <= 50){
  relayoff();
  Stop();
}

else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRightpenuh();
 }
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRight();
 }
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
 
relayonmundur();
turnSRight();
 }
 else if (data1 == LOW && data2 == LOW && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRight();
 }

 else if (data1 == LOW && data2 == LOW && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRight();
 }


 else if (data1 == LOW && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRightpenuh();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRightpenuh();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSRight();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == LOW&& data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSLeftpenuh();
 }
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
 //kanan
relayonmundur();
turnSLeft();
 }
 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
 //kiri
relayoff();
Stop();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == LOW)
 {
 //kanan
relayonmundur();
turnSLeftpenuh();
 }
 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == HIGH && data6 == LOW && data7 == LOW)
 {
 //kanan
relayonmundur();
turnSLeft();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == HIGH && data5 == LOW && data6 == LOW && data7 == LOW)
 {
 //berhenti
 relayonmundur();
 turnSLeft();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW)
 {
 //berhenti
 relayonmundur();
 turnSLeft();
 }


 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW){
  //stop
  turnSLeft();
  relayonmundur();
 }

  else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW){
  turnSLeftpenuh();
  relayonmundur();
}
  else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH){
  moveBackward();
  relayonmundur();
}
 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveBackwardSLeft();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveBackwardSRight();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveBackwardSRight2();
  relayonmundur();
 }

  else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == HIGH && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveBackwardSLeft2();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveBackward();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == HIGH && data6 == HIGH && data7 == HIGH)
 {
  moveBackwardSLeft2();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == HIGH && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveBackwardSRight2();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == HIGH && data7 == HIGH)
 {
  moveBackwardSLeft2();
  relayonmundur();
 }

 else if (data1 == HIGH && data2 == HIGH && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == HIGH)
 {
  moveBackwardSRight2();
  relayonmundur();
 }

 else if (data1 ==LOW && data2 == LOW && data3 == LOW && data4 == LOW && data5 == LOW && data6 == LOW && data7 == LOW)
 {
  Stop();
  relayoff();
 }
}
void relayoff (){
 digitalWrite(Relay1, HIGH);
}

void relayonmaju (){
 digitalWrite(Relay1, LOW);
}

void relayonmundur (){
 digitalWrite(Relay1, LOW);

 
}
void Stop() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 0);
  analogWrite (PWM2, 0);
  }

void turnRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 0);   
  analogWrite (PWM2, 80);
}

void moveForwardRight() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 85);   
  analogWrite (PWM2, 90);
  }

void moveForwardRight2() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 75);   
  analogWrite (PWM2, 90);
  }

void turnLeft() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 0);
 }

void moveForwardLeft() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 85);
  }

void moveForwardLeft2() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 75);
  }

void moveForward() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 95);
  }

void moveBackward() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 110);   
  analogWrite (PWM2, 70);

}
void turnSRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 0);   
  analogWrite (PWM2, 75);
}

void moveBackwardSRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 80);   
  analogWrite (PWM2, 65);
}

void moveBackwardSRight2() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 65);   
  analogWrite (PWM2, 65);
}

void turnSLeft() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 80);   
  analogWrite (PWM2, 0);
}

void moveBackwardSLeft() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 90);   
  analogWrite (PWM2, 55);
}

void moveBackwardSLeft2() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 90);   
  analogWrite (PWM2, 60);
}

void turnRightpenuh (){
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 90);   
  analogWrite (PWM2, 95);  
}

void turnLeftpenuh (){
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 90); 
}

void turnSRightpenuh (){
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  analogWrite (PWM1, 95);   
  analogWrite (PWM2, 95);
}

void turnSLeftpenuh (){
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
  analogWrite (PWM1, 100);   
  analogWrite (PWM2, 90);
}
