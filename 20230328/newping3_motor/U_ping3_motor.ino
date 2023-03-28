///////////////  sonar ////////////////////////////////////////

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 150 // Maximum distance (in cm) to ping.

#define Front 0
#define Left  1
#define Right 2


#define TRIG1 2  //초음파 센서 1번 Trig 핀 번호 Front
#define ECHO1 3  //초음파 센서 1번 Echo 핀 번호 Front 

#define TRIG2 4  //초음파 센서 2번 Trig 핀 번호 Left
#define ECHO2 5  //초음파 센서 2번 Echo 핀 번호 Left

#define TRIG3 6  //초음파 센서 3번 Trig 핀 번호 Right
#define ECHO3 7  //초음파 센서 3번 Echo 핀 번호 Right

////////////// L298 ///////////////////////////////////////////
#define ENA 8
#define IN1 9
#define IN2 10
#define IN3 11
#define IN4 12
#define ENB 13
NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(TRIG1, ECHO1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(TRIG2, ECHO2, MAX_DISTANCE),
  NewPing(TRIG3, ECHO3, MAX_DISTANCE)
};

void setup()
{
  //put your setup code here, to run once:
  /*
    pinMode(TRIG1, OUTPUT);
    pinMode(ECHO1,  INPUT);

    pinMode(TRIG2, OUTPUT);
    pinMode(ECHO2,  INPUT);

    pinMode(TRIG3, OUTPUT);
    pinMode(ECHO3,  INPUT);
  */
  pinMode(ENA,  OUTPUT);
  pinMode(IN1,  OUTPUT);
  pinMode(IN2,  OUTPUT);

  pinMode(IN3,  OUTPUT);
  pinMode(IN4,  OUTPUT);
  pinMode(ENB,  OUTPUT);


  Serial.begin(115200);  //통신속도를11520으로 정의함

}
long sonar_front(void) //초음파 센서1번 측정 함수
{
  float duration1, distance1;
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = ( (float)(340 * duration1) / 1000) / 2;
  return distance1;

}
long sonar2(void) //초음파 센서1번 측정 함수
{
  long duration2, distance2;
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = ( (float)(340 * duration2) / 1000) / 2;
  return distance2;

}
long sonar3(void) //초음파 센서1번 측정 함수
{
  long duration3, distance3;
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3, LOW);
  duration3 = pulseIn(ECHO3, HIGH);
  distance3 = ( (float)(340 * duration3) / 1000) / 2;
  return distance3;

}

void motor_A_control(int direction_a, int motor_speed_a) //모터 A의방향(direction)과 속도(speed)제어
{
  if (direction_a == HIGH)
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, motor_speed_a);
  }
  else
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, motor_speed_a);


  }
}

void motor_B_control(int direction_b, int motor_speed_b) //모터 B의방향(direction)과 속도(speed)제어
{
  if(direction_b == HIGH)
  {
    digitalWrite(IN3,LOW);             //모터의 방향 제어
    digitalWrite(IN4,HIGH);
    analogWrite(ENB,motor_speed_b);     //모터의 속도 제어
    }
  else
  {
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,motor_speed_b);
 }
}

void loop() {
  // put your main code here, to run repeatedly:
  float front_sonar  = 0.0;
  float left_sonar   = 0.0;
  float right_sonar  = 0.0;

  front_sonar = sonar[Front].ping_cm() * 10;
  if (front_sonar == 0.0)   front_sonar = MAX_DISTANCE;

    /*Serial.print("Distance1: ");
    Serial.println(front_sonar);
  
    Serial.print("Distance2: ");
    Serial.println(sonar2());

    Serial.print("Distance3: ");
    Serial.println(sonar3());
 */
  if ( (front_sonar > 0) && (front_sonar <= 250.0) )
  {
    // 정지
    /*
    Serial.println("Rotate stop");
    motor_A_control(HIGH, 0); 
    motor_B_control(LOW, 0); 
    delay(1000);
    
    //180도 반회전 시계 방향으로 회전
    Serial.println("Rotate CCW");
    motor_A_control(HIGH, 100); // 오른쪽 전진
    motor_B_control(LOW, 100); // 왼쪽은 후진
    delay(500);                // 일정한 시간동안 회전
*/

     //90도 시계방향 회전
    Serial.println("Rotate stop");
    motor_A_control(HIGH, 0); 
    motor_B_control(LOW, 0); 
    delay(500);
    //90도 회전 반시계 방향으로 회전
    Serial.println("Rotate CCW");
    motor_A_control(LOW, 100); // 오른쪽 전진
    motor_B_control(HIGH, 100); // 왼쪽은 후진
    delay(300);                // 일정한 시간동안 회전
    
       //90도 회전 반시계 방향으로 회전
    
    /*
    Serial.println("Rotate stop");
    motor_A_control(HIGH, 0); 
    motor_B_control(LOW, 0); 
    delay(100);
    //90도 회전 반시계 방향으로 회전
    Serial.println("Rotate CCW");
    motor_A_control(HIGH, 100); // 오른쪽 전진
    motor_B_control(LOW, 100); // 왼쪽은 후진
    delay(100);                // 일정한 시간동안 회전
    */
  }
  else
  {
    //직진
    Serial.println("GO Straigh");
    motor_A_control(HIGH, 100);
    motor_B_control(HIGH, 100);
  }
  delay(500);
}
