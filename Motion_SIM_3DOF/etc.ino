// Reset Button Work
void Reset_Button() {
  if(digitalRead(Button) == LOW) {
    if(TEST_Mode == 1) {
      Serial.print("BUTTON : ");
      Serial.println(Button_Count);
    }
    Button_Count++;
    tone(Tone, 777);
  }else {
    Button_Count = 0;
    noTone(Tone);
  }

  if(TEST_Mode == 1) {
    if(Button_Count > 10) {
      noTone(Tone);
      Motor_START();
    }
  }else {
    if(Button_Count > 1000) {
      noTone(Tone);
      Motor_START();
    }
  }
}

// Millis Serial Work
void Millis_Serial_Read() {
  Millis_Current = millis();

  if(Millis_Current - Millis_Prev >= Millis_Delay) {
    Millis_Prev = Millis_Current;

    if (Serial.available() > 0) {
      for(char i=0; i<3; i++) {
        Motor_STOP(i);
      }
    
      VISA_Read = Serial.readStringUntil(';');
      
      Interrupt_Pulse_A = 0;
      Interrupt_Pulse_B = 1;
    }
  }
}

// Serial Show
void SerialShow() {
  Serial.print("Axis");
  Serial.print(" : ");
  for(char i=0; i<3; i++) {
    Serial.print(Axis_Data[i]);
    Serial.print("  ");
  }
  Serial.print("     ");

  if(Control_Mode == ENCODER) {
    Serial.print("Enc");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Encoder_Data[i]);
      Serial.print(" ");
    }
    Serial.print("     ");
    
    Serial.print("     ");
    Serial.print("EnA");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Encoder_A_Temp[i]);
      Serial.print(" ");
    }
    Serial.print("     ");
    
    Serial.print("EnB");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Encoder_B_Temp[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
  if(Control_Mode == TICODER) {
    Serial.print("TiC");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Ticoder_Data[i]);
      Serial.print(" ");
    }
    Serial.print("     ");
    
    Serial.print("     ");
    Serial.print("TiA");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Ticoder_Temp_A[i]);
      Serial.print(" ");
    }
    Serial.print("     ");
    
    Serial.print("TiB");
    Serial.print(" : ");
    for(char i=0; i<3; i++) {
      Serial.print(Ticoder_Temp_B[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
}

