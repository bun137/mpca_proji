
// written by shreya and anuragrao -_-
// all global variables must be in UPPERCASE
#include <LiquidCrystal.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 46
#define SS_PIN 48

/*
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             46        D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            48        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52  s      D13        ICSP-3           15

*/

MFRC522 mfrc522(SS_PIN, RST_PIN); 

#define ROAD_WIDTH 6 // the road width in cm. 
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


const int buzzer = 30;

const int pingPin0_0 = 22;
const int echoPin0_0 = 23;

const int pingPin0_1 = 24;
const int echoPin0_1 = 25;

const int pingPin1_0 = 26;
const int echoPin1_0 = 27;

const int pingPin1_1 = 28;
const int echoPin1_1 = 29;

LiquidCrystal lcd(13, 8, 9, 10, 11, 12);

// super mario 

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 200;

// change this to whichever pin you want to use



// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,


};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void playMarioTheme() {
  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}




void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init(); // Init MFRC522
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();



  // initialize the FSM_STATE
  FSM_STATE = 0;

 

  // initialize the light pins
  pinMode(light0_r, INPUT);
  pinMode(light0_g, INPUT);
  pinMode(light0_b, INPUT);

  pinMode(light1_r, INPUT);
  pinMode(light1_g, INPUT);
  pinMode(light1_b, INPUT);

  // initialize the buzzer
  pinMode(buzzer, OUTPUT);

  // initialize the ultrasonic sensors
  pinMode(pingPin0_0, OUTPUT);
  pinMode(echoPin0_0, INPUT);

  pinMode(pingPin0_1, OUTPUT);
  pinMode(echoPin0_1, INPUT);

  pinMode(pingPin1_0, OUTPUT);
  pinMode(echoPin1_0, INPUT);

  pinMode(pingPin1_1, OUTPUT);
  pinMode(echoPin1_1, INPUT);


  // setting the LCD to default text
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Everything Is");
  lcd.setCursor(0,1);
  lcd.print("Alright");
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

    Serial.print("Sensor0_0: ");
    Serial.print(cm0);
    Serial.println("cms");
    Serial.print("Sensor0_1: ");
    Serial.print(cm1);
    Serial.println("cms");
    

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
  Serial.print("Road 0 : ");
  Serial.println(TIMEOUT);


  if ( mfrc522.PICC_IsNewCardPresent()) {
    // AMBULANCE!!
    Serial.println("Ambulance!!");
    
    FSM_STATE = 2;
    IS_TIMEOUT_SET = 0;
    return;
  }



  // if the timeout is over, then change the state
  if(TIMEOUT <= 0) {
    // give road 0 people some yellow,
    analogWrite(light0_r, 0);
    analogWrite(light0_g, 0);
    analogWrite(light0_b, 255);
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

    int sensor0 = 0;
    int sensor1 = 0; 
    int timeoutValue = 0;

    Serial.print("Sensor1_0: ");
    Serial.print(cm0);
    Serial.println("cms");
    Serial.print("Sensor1_1: ");
    Serial.print(cm1);
    Serial.println("cms");

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

  Serial.print("Road 1 : ");
  Serial.println(TIMEOUT);

  if ( mfrc522.PICC_IsNewCardPresent()) {
    // AMBULANCE!!
    Serial.println("Ambulance!!");
    FSM_STATE = 2;
    IS_TIMEOUT_SET = 0;
    return;
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

  analogWrite(light0_r, 0);
  analogWrite(light0_g, 255);
  analogWrite(light0_b, 0);


  analogWrite(light1_r, 255);
  analogWrite(light1_g, 0);
  analogWrite(light1_b, 0);


  if (!IS_TIMEOUT_SET){
    TIMEOUT = 30;
    IS_TIMEOUT_SET = 1;
  }

  Serial.print("Ambulance : ");
  Serial.println(TIMEOUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("AMBULANCE HERE");

  playMarioTheme();


  // ambulance would have gone
  FSM_STATE = 1;
  IS_TIMEOUT_SET = 0;

  analogWrite(light0_r, 0);
  analogWrite(light0_g, 0);
  analogWrite(light0_b, 255);
  delay(2000);
  // give road 0 people some red
  analogWrite(light0_r, 255);
  analogWrite(light0_g, 0);
  analogWrite(light0_b, 0);


  lcd.setCursor(0, 0);
  lcd.print("Everything Is");
  lcd.setCursor(0,1);
  lcd.print("Alright");
  
}