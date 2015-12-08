// Encoder Move
void Encoder_Move() {
  Axis_to_Move__Encoder(Motor_L);
  Axis_to_Move__Encoder(Motor_R);
  Axis_to_Move__Encoder(Motor_C);
}

void Axis_to_Move__Encoder(int PORT) {
  if(Axis_Data[PORT]  > Encoder_Data[PORT]) Motor_UP(PORT);
  if(Axis_Data[PORT]  < Encoder_Data[PORT]) Motor_DOWN(PORT);
  if(Axis_Data[PORT] == Encoder_Data[PORT]) Motor_STOP(PORT);
}

// Ticoder Move
void Ticoder_Move() {
  Axis_to_Move__Ticoder(Motor_L);
  Axis_to_Move__Ticoder(Motor_R);
  Axis_to_Move__Ticoder(Motor_C);
}

void Axis_to_Move__Ticoder(int PORT) {
  if(Axis_Data[PORT]  > Ticoder_Data[PORT]) Motor_UP(PORT);
  if(Axis_Data[PORT]  < Ticoder_Data[PORT]) Motor_DOWN(PORT);
  if(Axis_Data[PORT] == Ticoder_Data[PORT]) Motor_STOP(PORT);
}





