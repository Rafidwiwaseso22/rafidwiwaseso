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
// Initial Values of Sensors
int sensor[7] = {0, 0, 0, 0, 0, 0, 0};

int Relay1 = 2;

int Button1 = 33; // berangkat
int Button2 = 32; // start/stop
int Button3 = 35; // pulang


int nilai1, nilai2, nilai3;

#define Rpwm1 25
#define Lpwm1 26
#define Rpwm2 14
#define Lpwm2 12
#define pwm1 27
#define pwm2 13

int initial_motor_speed = 140;

// PID Constants
float Kp = 25;
float Ki = 0;
float Kd = 15;

float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;

int flag = 0;

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
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  
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

  Serial.println("Started !!");
  delay(500);
}

void loop() {
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
 delay(10);
  // masing2 variabel data menyimpan hasil pembacaan sensor
 // berupa logic LOW/HIGH


 if (nilai2 == HIGH) {
Stop();  
relayoff();
 }
 else if (nilai1 == HIGH) {
 tracingline();
 relayonmaju();
 }
 else if (nilai3 == HIGH) {
tracingback();
relayonmundur();
 }
}

void tracingline (){
if (jarak <= 50){
  Stop();
  relayoff();
}
}
void tracingback(){ 
 read_sensor_values();
  Serial.print(error);
  if (error == 100) {               // Make left turn untill it detects straight path
    //Serial.print("\t");
    //Serial.println("Left");
    do {
      read_sensor_values();
      analogWrite(pwm1, 110); //Left Motor Speed
      analogWrite(pwm2, 90); //Right Motor Speed
      turnSLeftpenuh();
    } while (error != 0);

  } else if (error == 101) {          // Make right turn in case of it detects only right path (it will go into forward direction in case of staright and right "|--")
                                      // untill it detects straight path.
    //Serial.print("\t");
    //Serial.println("Right");
    analogWrite(pwm1, 110); //Left Motor Speed
    analogWrite(pwm2, 90); //Right Motor Speed
    moveBackward();
    delay(200);
    Stop();
    read_sensor_values();
    if (error == 102) {
      do {
        analogWrite(pwm1, 110); //Left Motor Speed
        analogWrite(pwm2, 90); //Right Motor Speed
        turnSRightpenuh();
        read_sensor_values();
      } while (error != 0);
    }
  } else if (error == 102) {        // Make left turn untill it detects straight path
    //Serial.print("\t");
    //Serial.println("Sharp Left Turn");
    do {
      analogWrite(pwm1, 110); //Left Motor Speed
      analogWrite(pwm2, 90); //Right Motor Speed
      turnSLeftpenuh();
      read_sensor_values();
      if (error == 0) {
        Stop();
        delay(200);
      }
    } while (error != 0);
  } else if (error == 103) {        // Make left turn untill it detects straight path or stop if dead end reached.
    if (flag == 0) {
      analogWrite(pwm1, 110); //Left Motor Speed
      analogWrite(pwm2, 90); //Right Motor Speed
      moveBackward();
      delay(200);
      Stop();
      read_sensor_values();
      if (error == 103) {     /**** Dead End Reached, Stop! ****/
        Stop();
        digitalWrite(Relay1, HIGH);
        flag = 1;
      } else {        /**** Move Left ****/
        analogWrite(pwm1, 110); //Left Motor Speed
        analogWrite(pwm2, 90); //Right Motor Speed
        turnSLeftpenuh();
        delay(200);
        do {
          //Serial.print("\t");
          //Serial.println("Left Here");
          read_sensor_values();
          analogWrite(pwm1, 110); //Left Motor Speed
          analogWrite(pwm2, 90); //Right Motor Speed
          turnSLeftpenuh();
        } while (error != 0);
      }
    }
  } else {
    calculate_pid();
    motor_control();
  }
}

void read_sensor_values()
{
  sensor[0] = !digitalRead(sensor1);
  sensor[1] = !digitalRead(sensor2);
  sensor[2] = !digitalRead(sensor3);
  sensor[3] = !digitalRead(sensor4);
  sensor[4] = !digitalRead(sensor5);
  sensor[5] = !digitalRead(sensor6);
  sensor[6] = !digitalRead(sensor7);

  /*
    Serial.print(sensor[0]);
    Serial.print("\t");
    Serial.print(sensor[1]);
    Serial.print("\t");
    Serial.print(sensor[2]);
    Serial.print("\t");
    Serial.println(sensor[3]);*/

  if ((sensor[0] == 0) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 6;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 5;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 4;
  else if ((sensor[0] == 1) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 0) && (sensor[3] == 0)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 1;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1))
    error = 0;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 0)&& (sensor[4] == 0) && (sensor[5] == 1) && (sensor[6] == 1))
    error = -1;
   else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 0) && (sensor[5] == 1) && (sensor[6] == 1))
    error = -2;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 0) && (sensor[5] == 0) && (sensor[6] == 1))
    error = -3;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 0) && (sensor[6] == 1))
    error = -4;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 0) && (sensor[6] == 0))
    error = -5;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 0))
    error = -6;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1)) // Turn robot left side
    error = 100;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 0) && (sensor[5] == 0) && (sensor[6] == 0)) // Turn robot right side
    error = 101;
  else if ((sensor[0] == 0) && (sensor[1] == 0) && (sensor[2] == 0) && (sensor[3] == 0)&& (sensor[4] == 0) && (sensor[5] == 0) && (sensor[6] == 0)) // Make U turn
    error = 102;
  else if ((sensor[0] == 1) && (sensor[1] == 1) && (sensor[2] == 1) && (sensor[3] == 1)&& (sensor[4] == 1) && (sensor[5] == 1) && (sensor[6] == 1)) // Turn left side or stop
    error = 103;
}

void calculate_pid()
{
  P = error;
  I = I + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  // Calculating the effective motor speed:
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;

  // The motor speed should not exceed the max PWM value
  left_motor_speed = constrain(left_motor_speed, 0, 250);
  right_motor_speed = constrain(right_motor_speed, 0, 250);

  /*Serial.print(PID_value);
    Serial.print("\t");
    Serial.print(left_motor_speed);
    Serial.print("\t");
    Serial.println(right_motor_speed);*/

  analogWrite(pwm1, left_motor_speed); //Left Motor Speed
  analogWrite(pwm2, right_motor_speed - 30); //Right Motor Speed

  //following lines of code are to make the bot move forward
  moveBackward();
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
  }

void turnRight() {
  digitalWrite(Rpwm1, LOW);
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

void moveForward() {
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
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

void turnSLeft() {
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, LOW);
}

void turnRightpenuh (){
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW); 
}

void turnLeftpenuh (){
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Lpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void turnSRightpenuh (){
  digitalWrite(Rpwm1, HIGH);
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Rpwm2, LOW);
  digitalWrite(Lpwm2, HIGH);
}

void turnSLeftpenuh (){
  digitalWrite(Rpwm1, LOW);
  digitalWrite(Lpwm1, HIGH);
  digitalWrite(Rpwm2, HIGH);
  digitalWrite(Lpwm2, LOW);
}
