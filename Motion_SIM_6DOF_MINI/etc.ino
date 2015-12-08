// Millis Serial Work
void Millis_Serial_Read() {
  Millis_Current = millis();

  if(Millis_Current - Millis_Prev >= Millis_Delay) {
    Millis_Prev = Millis_Current;
  }

  if (Serial.available() > 0) {
    VISA_Read = Serial.readStringUntil(';');
  }
}

// Serial Show
void SerialShow() {
  Serial.print("Axis");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Axis_Temp[i]);
    Serial.print("  ");
  }
  Serial.print("    ");
  
  Serial.print("Servo");
  Serial.print(" : ");
  for(char i=0; i<6; i++) {
    Serial.print(Axis_Data[i]);
    Serial.print("  ");
  }
  Serial.print("\n");
}

