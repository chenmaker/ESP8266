//============{Arduino wed-MySQL-Upload_Data : LED HIGI or LOW }============//
#include <SoftwareSerial.h>
SoftwareSerial UART (9,8);
#include <ArduinoJson.h>

//============= {ESP - AT Command設定} =============//
#define  AP_Connect  "AT+CWJAP=\"STUWLAN-L0615_2.4G\",\"l0615&l0615\""//AP密碼
#define  ATMode      "AT+CWMODE=1"//網卡模式
#define  ATMUX       "AT+CIPMUX=0"//單點連接
#define  CloseIP     "AT+CIPCLOSE"//關閉連線
#define  TCP """AT+CIPSTART=\"TCP\",\"120.119.73.23\",80"""/*建立 TCP/UDP 連線*/

//============= {Upload or download} =============//
#define SQL_PHP  "GET /phpMyAdmin/JP_Lin/Fire_IOT.php?key=l0615&query="
#define Send_ID_1  "UPDATE `LoRa_UP_Data` SET `Car_1`= '"+a+"',`Car_2`= '"+b+"' WHERE`ID`='0' "
#define Send_ID_2  "UPDATE `LoRa_UP_Data` SET `Car_1`= '"+c+"',`Car_2`= '"+d+"' WHERE`ID`='0' "
#define End "\r\n\r\n"

int Botton_1,Botton_2;
String a="aa",b="bb",c="cc",d="dd";
String GET , cmd ;

void setup() {
  Serial.begin(115200);
  UART.begin(115200);
  Serial.println("Initialising the Serial1...");    
  UART.println(AP_Connect);
  Serial.println(UART.readString());
}

void WiFi_Connect(){
  UART.println(ATMode);
  delay(500);
  Serial.println(UART.readString()); 
  UART.println(ATMUX);
  delay(500);
  Serial.println(UART.readString());
  UART.println(TCP);
  delay(500);
  Serial.println(UART.readString());     
}

void MySQL_BottonData_1(){ 
  WiFi_Connect();
  delay(500);
  GET = SQL_PHP;
  GET += Send_ID_1;
  GET += End;
  MySQL_SendData();
}

void MySQL_BottonData_2(){ 
  WiFi_Connect();
  delay(500);
  GET = SQL_PHP;
  GET += Send_ID_2;
  GET += End;
  MySQL_SendData();
}

void MySQL_SendData(){
  cmd="AT+CIPSEND=" + String(GET.length());  
  UART.println(cmd);
  delay(500);
  UART.println(GET);
  delay(500);
  Serial.println(GET);
  Serial.println(F("----------------------------------------------------------"));  
  GET="";  
}

void loop() { 
     MySQL_BottonData_1();
     delay(3000);  
     MySQL_BottonData_2();    
}
