void Servo_Setup() {
  //L
  Servo_1.attach(3);
  Servo_2.attach(5);
  //C
  Servo_3.attach(6);
  Servo_4.attach(9);
  //R
  Servo_5.attach(10);
  Servo_6.attach(11);
}

void Axis_to_Move__Servo() {
  Servo_1.write(Axis_Data[Motor_L1]);
  Servo_2.write(Axis_Data[Motor_L2]);
  Servo_3.write(Axis_Data[Motor_C1]);
  Servo_4.write(Axis_Data[Motor_C2]);
  Servo_5.write(Axis_Data[Motor_R1]);
  Servo_6.write(Axis_Data[Motor_R2]);
}

void Servo_FULL_UP() {
  Work_Locker = 1;
  
  Servo_1.write(0);
  Servo_2.write(180);
  Servo_3.write(0);
  Servo_4.write(180);
  Servo_5.write(0);
  Servo_6.write(180);
}

void Servo_FULL_DOWN() {
  Work_Locker = 1;
  
  Servo_1.write(180);
  Servo_2.write(0);
  Servo_3.write(180);
  Servo_4.write(0);
  Servo_5.write(180);
  Servo_6.write(0);
}

void Servo_RESET(int Type) {
  for(char i=0; i<3; i++) {
    Axis_Temp[i] = 0;
  }
  for(char i=0; i<6; i++) {
    Axis_Data[i] = 90;
  }
  VISA_Read = "";
  if(Type == 0) Work_Locker = 0;
}

void Servo_START() {
  Servo_FULL_UP();
  delay(1000);
  Servo_FULL_DOWN();
  delay(1000);
  Servo_1.write(90);
  Servo_2.write(90);
  Servo_3.write(90);
  Servo_4.write(90);
  Servo_5.write(90);
  Servo_6.write(90);
  Servo_RESET(1);
  delay(2000);
  VISA_Read = "";
  Work_Locker = 0;
  Serial.println("START");
}

