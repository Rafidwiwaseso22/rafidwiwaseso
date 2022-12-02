#include <PID_v1.h>
int error;
double kp = 5.5 , ki = 0.0 , kd = 0.0;
double output, setpoint, abs_error;
PID line_follower(&abs_error, & output, & setpoint, kp, ki, kd, DIRECT);

int trigPin = 18;
int echoPin = 5;
long waktu;
int jarak;

int trigPin2 = 21;
int echoPin2 = 19;
long waktu2;
int jarak2;

const int sensor1 = 32; // sensor ir 1
const int sensor2 = 35; // sensor ir 2
const int sensor3 = 34; // sensor ir 3
const int sensor4 = 39; // sensor ir 4
const int sensor5 = 36; // sensor ir 5
const int sensor6 = 4; // sensor ir 6
const int sensor7 = 15; // sensor ir 7

// inialisasi variabel data 1 sampai 4
int data1, data2, data3, data4, data5, data6, data7;
int s1, s2, s3, s4, s5, s6, s7;

int Relay1 = 2;

int Button1 = 33; // berangkat
int Button2 = 22; // start/stop
int Button3 = 23; // pulang


int nilai1, nilai2, nilai3;

#define Rpwm1 25
#define Lpwm1 26
#define Rpwm2 14
#define Lpwm2 12
#define PWM1 27
#define PWM2 13

int Speed = 150;
int high, low;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  line_follower.SetMode(AUTOMATIC);
  pinMode (Button1, INPUT);
  pinMode (Button2, INPUT);
  pinMode (Button3, INPUT);

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
  data1 = analogRead(sensor1);
  data2 = analogRead(sensor2);
  data3 = analogRead(sensor3);
  data4 = analogRead(sensor4);
  data5 = analogRead(sensor5);
  data6 = analogRead(sensor6);
  data7 = analogRead(sensor7);
  nilai1 = digitalRead(Button1);
  nilai2 = digitalRead(Button2);
  nilai3 = digitalRead(Button3);

  if (data1 > 400)s1 = 1; else s1 = 0;
  if (data2 > 400)s2 = 1; else s2 = 0;
  if (data1 > 400)s3 = 1; else s3 = 0;
  if (data2 > 400)s4 = 1; else s4 = 0;
  if (data1 > 400)s5 = 1; else s5 = 0;
  if (data2 > 400)s6 = 1; else s6 = 0;
  if (data2 > 400)s6 = 1; else s7 = 0;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  waktu = pulseIn(echoPin, HIGH);
  jarak = waktu * 0.034 / 2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  waktu2 = pulseIn(echoPin2, HIGH);
  jarak2 = waktu2 * 0.034 / 2;
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
    readsensor ();
    pid_motor ();
    tracingline();
  }
  else if (nilai3 == HIGH) {
    readsensor ();
    pid_motor ();
    tracingback();
  }
}

void readsensor () {
  if ((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 6;
  else if ((s1 == 0) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 5;
  else if ((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 4;
  else if ((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 3;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 2;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 1;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1) && (s6 == 1) && (s7 == 1)) error = 0;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 0) && (s6 == 1) && (s7 == 1)) error = -1;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0) && (s6 == 1) && (s7 == 1)) error = -2;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0) && (s6 == 0) && (s7 == 1)) error = -3;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 0) && (s7 == 1)) error = -4;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 0) && (s7 == 0)) error = -5;
  else if ((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1) && (s6 == 1) && (s7 == 0)) error = -6;


}

void tracingback() {
  if (error > 0) {
    analogWrite(PWM1, high);
    analogWrite(PWM2, low);
    turnLeft();
    relayonmundur();
  }
  else if (error < 0) {
    analogWrite(PWM1, low);
    analogWrite(PWM2, high);
    turnRight();
    relayonmundur();
  }
  else {
    analogWrite(PWM1, Speed);
    analogWrite(PWM2, Speed);
    moveForward();
    relayonmaju();
  }
}

void tracingline () {
  if (error > 0) {
    analogWrite(PWM1, high);
    analogWrite(PWM2, low);
    turnSRight();
    relayonmaju();
  }
  else if (error < 0) {
    analogWrite(PWM1, low);
    analogWrite(PWM2, high);
    turnSLeft();
    relayonmaju();
  }
  else {
    analogWrite(PWM1, Speed);
    analogWrite(PWM2, Speed);
    moveBackward();
    relayonmaju();
  }
}



void pid_motor () {
  abs_error = abs(error) * -1;
  line_follower.Compute();

  high = Speed + output;
  low  = Speed - output;
}

void relayoff () {
  digitalWrite(Relay1, HIGH);
}

void relayonmaju () {
  digitalWrite(Relay1, LOW);
}

void relayonmundur () {
  digitalWrite(Relay1, LOW);

}

void ultrasonicmaju () {
  if (jarak <= 90) {
    Stop();
  }
}

void ultrasonicmundur () {
  if (jarak2 <= 90) {
    Stop();
  }
}

void Stop() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
}

void turnRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}

void moveForwardRight() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}

void moveForwardRight2() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}

void turnLeft() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
}

void moveForwardLeft() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}

void moveForwardLeft2() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
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
}
void turnSRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void moveBackwardSRight() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void turnSLeft() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
}

void moveBackwardSLeft() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void moveBackwardSLeft2() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void turnRightpenuh () {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}

void turnLeftpenuh () {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void turnSRightpenuh () {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
  digitalWrite(Lpwm1, LOW);
}

void turnSLeftpenuh () {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}
