/*
このファームウェアは以下の仕様のCoRE-2ベースロボット用である
Arduinoシールド ：Ver.2024
  → define.h と init.ino の両方がVer.2024用であることを確認せよ
射出用モータ    ：サーボ制御
  → motor.ino 内 servo2 の設定を確認せよ
射出用ローラ    ：PWM制御
  → motor.ino 内 servo2 の設定を確認せよ
コントローラ基板：Ver.2
  → メインプログラムの入力割付設定用define文を確認せよ
  → controller.ino がVer.2用であることを確認せよ
*/

#include <Servo.h>
#include <string.h>
#include <SPI.h>
#include "define.h"

#define BITRATE 115200

//コントローラ入力の割付け Ver.2用
#define SW_ENABLE ((RxData[4] & 0b000001) >> 0) //SW1 操作禁止
#define SW_SHOT   ((RxData[4] & 0b000010) >> 1) //SW2 ディスク押出
#define SW_ROLLER ((RxData[4] & 0b000100) >> 2) //SW3 ローラー回転
#define SW4 ((RxData[4] & 0b001000) >> 3)       //SW4 予備
#define SDA ((RxData[4] & 0b010000) >> 4)       //SDA 予備
#define SCL ((RxData[4] & 0b100000) >> 5)       //SCL 予備
#define AS_Left (RxData[0])                     //A1  左スティック
#define AS_Right (RxData[1])                    //A2  右スティック
#define AS_Vol (RxData[2])                      //A3  ピッチ調整
#define A4 (RxData[3])                          //A4  予備

//モータ名とポートの割付け
#define WHEEL_L MOTOR1  //左タイヤ
#define WHEEL_R MOTOR2  //右タイヤ
#define ROLLER MOTOR3   //射出回転
#define PITCH SERVO1    //ピッチ調整
#define SHOT SERVO2     //ディスク射出

//ロボットからのデジタル入力の割付け
#define EMG_Stop digitalRead(SW12)  //非常停止スイッチ

void setup() {
  // put your setup code here, to run once:

  Serial.begin(BITRATE);     //PC-Arduino用
  Serial1.begin(BITRATE);    //コントローラ用
  Serial2.begin(BITRATE);    //オートレフェリ用
  // Serial3.begin(9600);    //予備

  //CAN-bus 初期化
  //mcp2515.reset();
  //mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  //mcp2515.setNormalMode();

  Init();                     //init.ino
  InitMotor();                //init.ino
  ServoON(SHOT, waitangle);   //射出の初期位置を待機側に
  ServoON(SERVO3, 90);        //

  //for (int i = 0; i < 8; i++){
  //  MotorTxData.data[i] = 0;  //モータの指令リセット
  //  PIDdiff[i] = 0;           //PD制御の誤差をリセット
  //}

  delay(1000);

  BuzzerInitOK();             //init.ino

  Serial.println("Init OK");
}

void loop() {
  // put your main code here, to run repeatedly:
  // 周期固定用に開始時間を取得
  StartTime = millis();

  RxController();     //controller.ino

  // if((AF_Signal1 == 0) && (SW_ENABLE == 1) && !EMG_Stop && !ControllerTimeout){
  if((AF_Signal1 == 0) && (SW_ENABLE == 1) && !ControllerTimeout){
    OperationReady = 1;
    //Serial.println("ControllerStatus: Ready");
  }else{
    OperationReady = 0;
    if(SW_ENABLE == 0){
      Serial.println("ControllerStatus: Locked");
    }
    else{
      Serial.println("ERR: Controller Connection not Successfully.");
      Serial.print("ControllerStatus: Unknown(Operation: Not Ready) ");
      Serial.print(", AF_Signal1:");
      Serial.print(AF_Signal1);
      Serial.print(", SW_ENABLE:");
      Serial.print(SW_ENABLE);
      Serial.print(", ControllerTimeout:");
      Serial.println(ControllerTimeout);
    }
  }
  SensorDebugLED();   //init.ino

  if(OperationReady == 1){
    //process.ino にて定義
    Wheel();

    Shot();

    Pitch();

    Roller();

    BuzzerOFF();

  }else{

    RollerOnOff = 0;
    ShotSeq = 0;
    Shotmove = 0;
    MotorAllOFF();    //motor.ino
    ServoON(SHOT, waitangle);
        
    if (AF_Signal1 == 1){
      Buzzer1ON();    //init.ino
    }
  }

  //RMmotorTxData();    //motor.ino
  //RMmotorRxData();    //motor.ino

  //周期固定用の待機(オーバしたら無視)
  while ((millis() - StartTime) < (period) ){
    delayMicroseconds(10);
  }  
}
