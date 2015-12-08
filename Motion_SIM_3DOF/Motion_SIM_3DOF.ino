#include <TimeInterrupt.h>

// Motor Number
#define Motor_L 0
#define Motor_C 1
#define Motor_R 2

// Tone & Button Pin Number
#define Tone 50
#define Button 51

// Axis & Motor Limit
#define Axis_Min 0
#define Axis_Max 255
#define Motor_Min 0
#define Motor_Max 50

// Encoder & Ticoder Number
#define ENCODER 0
#define TICODER 1

// Pin Number
int Motor_CW[3]  = {22,28,36}; // Motor Forword Relay
int Motor_CCW[3] = {27,12,37}; // Motor backword Relay
int Encoder_A[3] = {2,3,4};    // Motor Hall A
int Encoder_B[3] = {18,8,10};  // Motor Hall B

// Encoder
volatile int Encoder_Data[3] = {0,0,0};
volatile int Encoder_Save[3] = {0,0,0};
volatile int Encoder_A_Temp[3] = {0,0,0};
volatile int Encoder_B_Temp[3] = {0,0,0};

// Motor Work
volatile int Motor_Work[3] = {0,0,0};
volatile int Motor_Ways[3] = {0,0,0};

// Ticoder
volatile int Ticoder_Data[3] = {0,0,0};
volatile int Ticoder_Save[3] = {0,0,0};
volatile int Ticoder_Temp_A[3] = {0,0,0};
volatile int Ticoder_Temp_B[3] = {0,0,0};
volatile int Interrupt_Pulse_A = 0;
volatile int Interrupt_Pulse_B = 1;

// Time Delay Settings
int Loop_Time = 0;
int Interrupt_Time = 100;

// Axis
int Axis_Temp[3] = {0,0,0};
int Axis_Data[3] = {0,0,0};

// Etc work Settings
int Button_Count = 0;
int Work_Locker = 0;

// Millis Settings
unsigned long Millis_Prev = 0;
unsigned long Millis_Current = 0;
const long Millis_Delay = 500;

// Serial VISA Temp
String VISA_Read = "";

// Mode Settings
int TEST_Mode = 0;
int Control_Mode = 1;

void setup() {
  // put your setup code here, to run once:
  // Time set by Mode
  if(TEST_Mode == 0) Loop_Time = 0;
  else if(TEST_Mode == 1) Loop_Time = 100;

  // Serial Setup
  Serial.begin(9600);
  Serial.flush();

  // Pin Setup
  for(char i=0; i<3; i++) { 
    pinMode(Motor_CW[i], OUTPUT); 
    pinMode(Motor_CCW[i], OUTPUT); 
    pinMode(Encoder_A[i], INPUT);
    pinMode(Encoder_B[i], INPUT); 
  }
    pinMode(Tone, OUTPUT);
    pinMode(Button, INPUT);

  // Motor Reset
  Motor_START();
  
  //Time Interrupt Setup
  if(Control_Mode == ENCODER) TimeInterrupt::set(Interrupt_Time, Encoder_Interrupt);
  if(Control_Mode == TICODER) TimeInterrupt::set(Interrupt_Time, Ticoder_Interrupt);
  TimeInterrupt::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Warring - Push Reset Button
  Reset_Button();

  //Millis Time Serial Read
  Millis_Serial_Read();

  //Serial VISA Data Work
  if(VISA_Read != "") {
    if((VISA_Read == "U") || (VISA_Read == "u") || (VISA_Read == "D") || (VISA_Read == "d") || (VISA_Read == "S") || (VISA_Read == "s") || (VISA_Read == "X") || (VISA_Read == "x")) String_to_Command();
    else String_to_Axis();
  }

  //Motor Work
  if(Work_Locker == 0) {
    if(Control_Mode == ENCODER) Encoder_Move();
    
    if(Control_Mode == TICODER) Ticoder_Move();
  }

  //Serial Data Show
  if(TEST_Mode == 1) SerialShow();

  //Reset
  VISA_Read = "";
  Serial.flush();
  delay(Loop_Time);
}
