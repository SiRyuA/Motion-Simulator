// Encoder Interrupt
void Encoder_Interrupt() {
  // Encoder Work
  if(Motor_Work[Motor_L] == 1) Encoder(Motor_L);
  if(Motor_Work[Motor_R] == 1) Encoder(Motor_R);
  if(Motor_Work[Motor_C] == 1) Encoder(Motor_C);
}

// Encoder
void Encoder(int PORT) { 
  // Hall A
  if(digitalRead(Encoder_A[PORT]) == HIGH){ // Pulse HIGH
    if(Motor_Ways[PORT] == 1) Encoder_A_Temp[PORT]++; // Motor Forword
    else if(Motor_Ways[PORT] == -1) Encoder_A_Temp[PORT]--; // Motor Backword
  }

  // Hall B
  if(digitalRead(Encoder_B[PORT]) == HIGH) { // Pulse HIGH
    if(Motor_Ways[PORT] == 1) Encoder_B_Temp[PORT]++; // Motor Forword
    else if(Motor_Ways[PORT] == -1) Encoder_B_Temp[PORT]--; // Motor Backword
  }

  // Encoder Mean, (Hall A + Hall B)/2
  Encoder_Data[PORT] = (Encoder_A_Temp[PORT] + Encoder_B_Temp[PORT])/2;
  Encoder_Save[PORT] = Encoder_Data[PORT];

  // Encoder LOW Limit
  if(Encoder_Data[PORT] < Motor_Min) {
    Encoder_Data[PORT] = Motor_Min;
    Motor_STOP(PORT);
  }

  // Encoder HIGH Limit
  if(Encoder_Data[PORT] > Motor_Max) {
    Encoder_Data[PORT] = Motor_Max;
    Motor_STOP(PORT);
  }
}
