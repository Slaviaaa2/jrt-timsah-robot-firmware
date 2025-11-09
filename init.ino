/*
この初期設定ファイルはArduinoシールドVer.2024用である
入力SW  ： 1 ~12
LED     ： 1 ~12
SERVO   ： 1 ~ 3
*/
void Init(void){

  pinMode(LED1,  OUTPUT);
  pinMode(LED2,  OUTPUT);
  pinMode(LED3,  OUTPUT);
  pinMode(LED4,  OUTPUT);
  pinMode(LED5,  OUTPUT);
  pinMode(LED6,  OUTPUT);
  pinMode(LED7,  OUTPUT);
  pinMode(LED8,  OUTPUT);
  pinMode(LED9,  OUTPUT);
  pinMode(LED10, OUTPUT);
  pinMode(LED11, OUTPUT);
  pinMode(LED12, OUTPUT);

  pinMode(SW1,  INPUT);
  pinMode(SW2,  INPUT);
  pinMode(SW3,  INPUT);
  pinMode(SW4,  INPUT);
  pinMode(SW5,  INPUT);
  pinMode(SW6,  INPUT);
  pinMode(SW7,  INPUT);
  pinMode(SW8,  INPUT);
  pinMode(SW9,  INPUT);
  pinMode(SW10, INPUT);
  pinMode(SW11, INPUT);
  pinMode(SW12, INPUT);

  pinMode(AF1, INPUT);
  pinMode(AF2, INPUT);
  
}

/********  Debug LED  ********/
void SensorDebugLED(void){

  if(digitalRead(SW1)){
    digitalWrite(LED1, LOW);
  }else{
    digitalWrite(LED1, HIGH);
  }
  if(digitalRead(SW2)){
    digitalWrite(LED2, LOW);
  }else{
    digitalWrite(LED2, HIGH);
  }
  if(digitalRead(SW3)){
    digitalWrite(LED3, LOW);
  }else{
    digitalWrite(LED3, HIGH);
  }
  if(digitalRead(SW4)){
    digitalWrite(LED4, LOW);
  }else{
    digitalWrite(LED4, HIGH);
  }
  if(digitalRead(SW5)){
    digitalWrite(LED5, LOW);
  }else{
    digitalWrite(LED5, HIGH);
  }
  if(digitalRead(SW6)){
    digitalWrite(LED6, LOW);
  }else{
    digitalWrite(LED6, HIGH);
  }
  if(digitalRead(SW7)){
    digitalWrite(LED7, LOW);
  }else{
    digitalWrite(LED7, HIGH);
  }
  if(digitalRead(SW8)){
    digitalWrite(LED8, LOW);
  }else{
    digitalWrite(LED8, HIGH);
  }
  if(digitalRead(SW9)){
    digitalWrite(LED9, LOW);
  }else{
    digitalWrite(LED9, HIGH);
  }
  if(digitalRead(SW10)){
    digitalWrite(LED10, LOW);
  }else{
    digitalWrite(LED10, HIGH);
  }
  if(digitalRead(SW11)){
    digitalWrite(LED11, LOW);
  }else{
    digitalWrite(LED11, HIGH);
  }
  if(digitalRead(SW12)){
    digitalWrite(LED12, LOW);
  }else{
    digitalWrite(LED12, HIGH);
  }
}

/********  Buzzer  ********/
void BuzzerON(void){
  analogWrite(BUZZER, 255);
}
void BuzzerOFF(void){
  analogWrite(BUZZER, 0);
}
void Buzzer1ON(void){
  analogWrite(BUZZER, 55);
}
void BuzzerInitOK(void){
  
  BuzzerON();
  delay(100);
  BuzzerOFF();
  delay(100);
  BuzzerON();
  delay(100);
  BuzzerOFF();
  delay(100);
  BuzzerON();
  delay(100);
  BuzzerOFF();
  delay(100);

}