// written by shreya and anuragrao -_-
// all global variables must be in UPPERCASE
#include <LiquidCrystal.h>
#define ROAD_WIDTH 10 // the road width in cm. Can be changed at the time of hardware build
#define TRAFFIC_LEV_0_TIME 5
#define TRAFFIC_LEV_1_TIME 10
#define TRAFFIC_LEV_2_TIME 15


int FSM_STATE = 0;
int TIMEOUT = 0;
int IS_TIMEOUT_SET = 0;


const int light0_r = 2;
const int light0_g = 3;
const int light0_b = 4;


const int light1_r = 5;
const int light1_g = 6;
const int light1_b = 7;


const int buzzer = 4;

const int pingPin0_0 = 22;
const int echoPin0_0 = 23;

const int pingPin0_1 = 24;
const int echoPin0_1 = 25;

const int pingPin1_0 = 26;
const int echoPin1_0 = 27;

const int pingPin1_1 = 28;
const int echoPin1_1 = 29;

LiquidCrystal lcd(13, 8, 9, 10, 11, 12);

// TODO : RFID BULL

void setup() {
  Serial.begin(9600);

  // initialize the FSM_STATE
  FSM_STATE = 0;

  // TODO : RFID SETUP
}

void doState0();
void doState1();
void doState2();


void loop() {

  switch(FSM_STATE) {
    case 0:
      doState0();
      break;
    case 1:
      doState1();
      break;
    case 2:
      doState2();
      break;
  }
  

  // a second passing
  delay(1000);
  TIMEOUT--;

}


void doState0() {
  //TODO: dum dum 

  // TODO : RFID CHECK AND TRANSFER CONTROL TO STATE 2 IF RFID DETECTED. ALSO RETURN FROM THIS FUNCTION IN THAT CASE

  

  // set road 0 lights to green
  analogWrite(light0_r, 0);
  analogWrite(light0_g, 255);
  analogWrite(light0_b, 0);

    
  if(!IS_TIMEOUT_SET){
    // get the sensor values for road 0 sensor 0
    digitalWrite(pingPin0_0, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin0_0, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin0_0, LOW);
    int duration0 = pulseIn(echoPin0_0, HIGH);

    // get the sensor values for road 0 sensor 1
    digitalWrite(pingPin0_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin0_1, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin0_1, LOW);
    int duration1 = pulseIn(echoPin0_1, HIGH);

    int cm0 = duration0 / 29 / 2;
    int cm1 = duration1 / 29 / 2;

    int sensor0 = 0, sensor1 = 0; // these represent if these sensors are triggered or not
    int timeoutValue = 0;
    

    if(cm0 < ROAD_WIDTH) {
      sensor0 = 1;
    }
    if(cm1 < ROAD_WIDTH) {
      sensor1 = 1;
    }



    if(sensor0 && sensor1){
      // both the sensors are triggered
      // so the traffic is at level 2
      timeoutValue = TRAFFIC_LEV_2_TIME;
    } else if(sensor0 && !sensor1){
      // only sensor 0 is triggered
      // so the traffic is at level 1
      timeoutValue = TRAFFIC_LEV_1_TIME;
    } else {
      // no sensor is triggered
      // so the traffic is at level 0,
      timeoutValue = TRAFFIC_LEV_0_TIME;
    }


    TIMEOUT = timeoutValue;
    IS_TIMEOUT_SET = 1;



  }

  // if the timeout is over, then change the state
  if(TIMEOUT <= 0) {
    // give road 0 people some yellow,
    analogWrite(light0_r, 255);
    analogWrite(light0_g, 255);
    analogWrite(light0_b, 0);
    delay(2000);
    // give road 0 people some red
    analogWrite(light0_r, 255);
    analogWrite(light0_g, 0);
    analogWrite(light0_b, 0);

    FSM_STATE = 1;
    IS_TIMEOUT_SET = 0;
  } 

}

void doState1() {
// TODO: shreya
  analogWrite(light1_r, 0);
  analogWrite(light1_g, 255);
  analogWrite(light1_b, 0);
  if(!IS_TIMEOUT_SET){
    // get the sensor values for road 1 sensor 0
    digitalWrite(pingPin1_0, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin1_0, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin1_0, LOW);
    int duration0 = pulseIn(echoPin1_0, HIGH);
    
    // get the sensor values for road 1 sensor 1
    digitalWrite(pingPin1_1, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin1_1, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin1_1, LOW);
    int duration1 = pulseIn(echoPin1_1, HIGH);

    int cm0 = duration0 / 29 / 2;
    int cm1 = duration1 / 29 / 2;

    int sensor0 = 0
    int sensor1 = 0; 
    int timeoutValue = 0;

    if(cm0 < ROAD_WIDTH) {
      sensor0 = 1;
    }
    if(cm1 < ROAD_WIDTH) {
      sensor1 = 1;
    }

    if(sensor0 && sensor1){
      // both the sensors are triggered
      // so the traffic is at level 2
      timeoutValue = TRAFFIC_LEV_2_TIME;
    } else if(sensor0 && !sensor1){
      // only sensor 0 is triggered
      // so the traffic is at level 1
      timeoutValue = TRAFFIC_LEV_1_TIME;
    } else {
      // no sensor is triggered
      // so the traffic is at level 0,
      timeoutValue = TRAFFIC_LEV_0_TIME;
    }
    TIMEOUT = timeoutValue;
    IS_TIMEOUT_SET = 1;
  }
  
  // if the timeout is over, then change the state
  if(TIMEOUT <= 0) {
    // give road 1 people some yellow,
    analogWrite(light1_r, 255);
    analogWrite(light1_g, 255);
    analogWrite(light1_b, 0);
    delay(2000);
    // give road 1 people some red
    analogWrite(light1_r, 255);
    analogWrite(light1_g, 0);
    analogWrite(light1_b, 0);

    FSM_STATE = 0;
    IS_TIMEOUT_SET = 0;
  } 

}

void doState2() {
  // TODO: shreya

  if (!IS_TIMEOUT_SET){
    TIMEOUT = 15;
    IS_TIMEOUT_SET = 1;
  }

  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("AMBULANCE HERE");
}
