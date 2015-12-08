// String to Axis
void String_to_Axis() {
  if(TEST_Mode == 1) Serial.println("VISA_Read : " + VISA_Read);

  // Comma based, string cut
  int comma_1 = VISA_Read.indexOf(',');
  int comma_2 = VISA_Read.indexOf(',', comma_1+1);
  int comma_3 = VISA_Read.indexOf(',', comma_2+1);

  // cut string save
  String string_Temp_1 = VISA_Read.substring(0, comma_1);
  String string_Temp_2 = VISA_Read.substring(comma_1+1, comma_2);
  String string_Temp_3 = VISA_Read.substring(comma_2+1, comma_3);

  // cut string save space add
  char char_Temp_1[string_Temp_1.length()+1];
  char char_Temp_2[string_Temp_2.length()+1];
  char char_Temp_3[string_Temp_3.length()+1];

  // cut string save
  string_Temp_1.substring(0).toCharArray(char_Temp_1, string_Temp_1.length()+1);
  string_Temp_2.substring(0).toCharArray(char_Temp_2, string_Temp_2.length()+1);
  string_Temp_3.substring(0).toCharArray(char_Temp_3, string_Temp_3.length()+1);

  // string to Axis, Motor L, Lxxx -> L = xxx
  if((char_Temp_1[0] == 'L') || (char_Temp_1[0] == 'l') || (char_Temp_2[0] == 'L') || (char_Temp_2[0] == 'l') || (char_Temp_3[0] == 'L') || (char_Temp_3[0] == 'l')) {
    if((char_Temp_1[0] == 'L') || (char_Temp_1[0] == 'l')) Axis_Temp[Motor_L] = strtol(char_Temp_1+1, NULL, 10);
    if((char_Temp_2[0] == 'L') || (char_Temp_2[0] == 'l')) Axis_Temp[Motor_L] = strtol(char_Temp_2+1, NULL, 10);
    if((char_Temp_3[0] == 'L') || (char_Temp_3[0] == 'l')) Axis_Temp[Motor_L] = strtol(char_Temp_3+1, NULL, 10);
    Axis_Temp[Motor_L] = constrain(Axis_Temp[Motor_L], Axis_Min, Axis_Max);
    Axis_Data[Motor_L] = map(Axis_Temp[Motor_L], Axis_Min, Axis_Max, Motor_Min, Motor_Max);
  }

  // string to Axis, Motor R, Lxxx -> R = xxx
  if((char_Temp_1[0] == 'R') || (char_Temp_1[0] == 'r') || (char_Temp_2[0] == 'R') || (char_Temp_2[0] == 'r') || (char_Temp_3[0] == 'R') || (char_Temp_3[0] == 'r')) {
    if((char_Temp_1[0] == 'R') || (char_Temp_1[0] == 'r')) Axis_Temp[Motor_R] = strtol(char_Temp_1+1, NULL, 10);
    if((char_Temp_2[0] == 'R') || (char_Temp_2[0] == 'r')) Axis_Temp[Motor_R] = strtol(char_Temp_2+1, NULL, 10);
    if((char_Temp_3[0] == 'R') || (char_Temp_3[0] == 'r')) Axis_Temp[Motor_R] = strtol(char_Temp_3+1, NULL, 10);
    Axis_Temp[Motor_R] = constrain(Axis_Temp[Motor_R], Axis_Min, Axis_Max);
    Axis_Data[Motor_R] = map(Axis_Temp[Motor_R], Axis_Min, Axis_Max, Motor_Min, Motor_Max);
  }

  // string to Axis, Motor C, Lxxx -> C = xxx
  if((char_Temp_1[0] == 'C') || (char_Temp_1[0] == 'c') || (char_Temp_2[0] == 'C') || (char_Temp_2[0] == 'c') || (char_Temp_3[0] == 'C') || (char_Temp_3[0] == 'c')) {
    if((char_Temp_1[0] == 'C') || (char_Temp_1[0] == 'c')) Axis_Temp[Motor_C] = strtol(char_Temp_1+1, NULL, 10);
    if((char_Temp_2[0] == 'C') || (char_Temp_2[0] == 'c')) Axis_Temp[Motor_C] = strtol(char_Temp_2+1, NULL, 10);
    if((char_Temp_3[0] == 'C') || (char_Temp_3[0] == 'c')) Axis_Temp[Motor_C] = strtol(char_Temp_3+1, NULL, 10);
    Axis_Temp[Motor_C] = constrain(Axis_Temp[Motor_C], Axis_Min, Axis_Max);
    Axis_Data[Motor_C] = map(Axis_Temp[Motor_C], Axis_Min, Axis_Max, Motor_Min, Motor_Max);
  }
}

// String work, Command
void String_to_Command() {
  if((VISA_Read == "U") || (VISA_Read == "u")) Motor_FULL_UP();
  if((VISA_Read == "D") || (VISA_Read == "d")) Motor_FULL_DOWN();
  if((VISA_Read == "S") || (VISA_Read == "s")) Motor_START();
  if((VISA_Read == "X") || (VISA_Read == "x")) Motor_RESET(0);;
}
