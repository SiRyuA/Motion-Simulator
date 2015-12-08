#include <Servo.h>

#define Motor_L 0
#define Motor_C 1
#define Motor_R 2

#define Motor_L1 0
#define Motor_L2 1
#define Motor_C1 2
#define Motor_C2 3
#define Motor_R1 4
#define Motor_R2 5

// Axis & Motor Limit
#define Axis_Min 0
#define Axis_Max 255
#define Motor_Min 0
#define Motor_Max 180

// Servo Settings
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;
Servo Servo_4;
Servo Servo_5;
Servo Servo_6;

// Time Delay Settings
int Loop_Time = 100;

// Axis
int Axis_Temp[3] = {0,0,0};
int Axis_Data[6] = {90,90,90,90,90,90};

// Etc Work Settings
int Work_Locker = 0;

// Millis Settings
unsigned long Millis_Prev = 0;
unsigned long Millis_Current = 0;
const long Millis_Delay = 500;

// Serial VISA Temp
String VISA_Read = "";


// Mode Settings
int TEST_Mode = 1;


void setup() {
  // put your setup code here, to run once:
  //Serial Setup
  Serial.begin(9600);
  Serial.flush();
  Serial.println("Connected.");
  
  //Servo Setup
  Servo_Setup();
  Servo_START();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Millis Time Serial Read
  Millis_Serial_Read();

  //Serial VISA Data Work
  if(VISA_Read != "") {
    if((VISA_Read == "U") || (VISA_Read == "u") || (VISA_Read == "D") || (VISA_Read == "d") || (VISA_Read == "S") || (VISA_Read == "s") || (VISA_Read == "X") || (VISA_Read == "x")) String_to_Command();
    else String_to_Axis();
  }

  if(Work_Locker == 0) Axis_to_Move__Servo();

  //Serial Data Show
  if(TEST_Mode == 1) SerialShow();
  
  //Reset
  VISA_Read = "";
  Serial.flush();
  delay(Loop_Time);
}
