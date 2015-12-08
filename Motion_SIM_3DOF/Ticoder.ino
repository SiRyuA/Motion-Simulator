//Ticoder Interrupt
void Ticoder_Interrupt() {
  //Ticoder Pulse Make
  if(Interrupt_Pulse_A == 0) Interrupt_Pulse_A = 1;
  else if(Interrupt_Pulse_A == 1) Interrupt_Pulse_A = 0;

  if(Interrupt_Pulse_B == 0) Interrupt_Pulse_B = 1;
  else if(Interrupt_Pulse_B == 1) Interrupt_Pulse_B = 0;

  // Ticoder Work
  if(Motor_Work[Motor_L] == 1) Ticoder(Motor_L);
  if(Motor_Work[Motor_R] == 1) Ticoder(Motor_R);
  if(Motor_Work[Motor_C] == 1) Ticoder(Motor_C);

  if(TEST_Mode == 1) {
    if(Interrupt_Pulse_A == 1) Serial.println("A");
    if(Interrupt_Pulse_B == 1) Serial.println("B");
  }
}

// Ticoder
void Ticoder(int PORT) {
  if(Interrupt_Pulse_A == 1) { // Ticoder Pulse HIGH
    if(Motor_Ways[PORT] == 1) Ticoder_Temp_A[PORT]++; // Motor Forword
    else if(Motor_Ways[PORT] == -1) Ticoder_Temp_A[PORT]--; // Motor Backword
  }

  if(Interrupt_Pulse_B == 1) { // Ticoder Pulse HIGH
    if(Motor_Ways[PORT] == 1) Ticoder_Temp_B[PORT]++; // Motor Forword
    else if(Motor_Ways[PORT] == -1) Ticoder_Temp_B[PORT]--; // Motor Backword
  }

  Ticoder_Data[PORT] = (Ticoder_Temp_A[PORT] + Ticoder_Temp_B[PORT])/2; // Ticoder Save
  Ticoder_Save[PORT] = Ticoder_Data[PORT];

  // Ticoder Min Limit
  if(Ticoder_Data[PORT] < Motor_Min) {
    Ticoder_Data[PORT] = Motor_Min;
    Motor_STOP(PORT);
  }

  // Ticoder Max Limit
  if(Ticoder_Data[PORT] > Motor_Max) {
    Ticoder_Data[PORT] = Motor_Max;
    Motor_STOP(PORT);
  }
}
