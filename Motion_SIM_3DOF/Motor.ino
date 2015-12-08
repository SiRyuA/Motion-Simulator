// Motor Up Work
void Motor_UP(int PORT) {
  Motor_Work[PORT] = 1;
  Motor_Ways[PORT] = 1;

  if(Control_Mode == ENCODER) Encoder_Data[PORT] = Encoder_Save[PORT];
  if(Control_Mode == TICODER) Ticoder_Data[PORT] = Ticoder_Save[PORT];

  digitalWrite(Motor_CW[PORT], HIGH);
  digitalWrite(Motor_CCW[PORT], LOW);
}

// Motor Stop Work
void Motor_STOP(int PORT) {
  Motor_Work[PORT] = 0;
  Motor_Ways[PORT] = 0;

  if(Control_Mode == ENCODER) Encoder_Data[PORT] = Encoder_Save[PORT];
  if(Control_Mode == TICODER) Ticoder_Data[PORT] = Ticoder_Save[PORT];

  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], LOW);
}

// Motor Down Work
void Motor_DOWN(int PORT) {
  Motor_Work[PORT] = 1;
  Motor_Ways[PORT] = -1;

  if(Control_Mode == ENCODER) Encoder_Data[PORT] = Encoder_Save[PORT];
  if(Control_Mode == TICODER) Ticoder_Data[PORT] = Ticoder_Save[PORT];

  digitalWrite(Motor_CW[PORT], LOW);
  digitalWrite(Motor_CCW[PORT], HIGH);
}

// Motor Full Up Work
void Motor_FULL_UP() {
  Work_Locker = 1;
  for(char i=0; i<3; i++) {
    Motor_Ways[i] = 0;
    digitalWrite(Motor_CW[i], HIGH);
    digitalWrite(Motor_CCW[i], LOW);
  }
}

// Motor Full Down Work
void Motor_FULL_DOWN() {
  Work_Locker = 1;
  for(char i=0; i<3; i++) {
    Motor_Ways[i] = 0;
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], HIGH);
  }  
}

// Motor Reset Work
void Motor_RESET(int Type) {
  for(char i=0; i<3; i++) {
    digitalWrite(Motor_CW[i], LOW);
    digitalWrite(Motor_CCW[i], LOW);
  }

  for(char i=0; i<3; i++) {
    digitalWrite(Encoder_A[i], HIGH);
    digitalWrite(Encoder_B[i], HIGH);
  }
  Interrupt_Pulse_A = 0;
  Interrupt_Pulse_B = 1;

  for(char i=0; i<3; i++) {
    Axis_Temp[i] = 0;
    Axis_Data[i] = 0;
  }

  for(char i=0; i<3; i++) {
    Ticoder_Data[i] = 0;
    Ticoder_Save[i] = 0;
    Ticoder_Temp_A[i] = 0;
    Ticoder_Temp_B[i] = 0;
  }

  for(char i=0; i<3; i++) {
    Encoder_Data[i] = 0;
    Encoder_A_Temp[i] = 0;
    Encoder_B_Temp[i] = 0;
  }

  VISA_Read = "";
  if(Type == 0) Work_Locker = 0;
}

// Motor Full Reset & Start work
void Motor_START() {
  TimeInterrupt::stop();
  
  Motor_FULL_UP();
  delay(1000);
  Motor_FULL_DOWN();
  delay(16000);
  Motor_FULL_UP();
  delay(1000);
  Motor_RESET(1);

  VISA_Read = "";
  Button_Count = 0;
  Work_Locker = 0;

  tone(Tone, 4444);
  delay(100);
  noTone(Tone);

  TimeInterrupt::set(Interrupt_Time, Ticoder_Interrupt);
  TimeInterrupt::start();
}

