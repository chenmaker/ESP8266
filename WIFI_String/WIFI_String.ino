//============{Arduino wed-MySQL-Upload_Data : LED HIGI or LOW }============//
#include <SoftwareSerial.h>
SoftwareSerial UART (9,8);
#include <ArduinoJson.h>

//============= {ESP - AT Command設定} =============//
#define  AP_Connect  "AT+CWJAP=\"STUWLAN-L0615_2.4G\",\"l0615&l0615\""
#define  ATMode      "AT+CWMODE=1"
#define  ATMUX       "AT+CIPMUX=0"
#define  CloseIP     "AT+CIPCLOSE" 
#define  TCP """AT+CIPSTART=\"TCP\",\"120.119.73.23\",80"""/*建立 TCP/UDP 連線*/

//============= {Upload or download} =============//
#define SQL_PHP  "GET /phpMyAdmin/xu/Fire_IOT.php?key=l0615&query="
#define Send_ID_1  "UPDATE `Fire_IOT` SET `SWITCH_1`= '"+a+"', WHERE `ID`='0'"
#define End "\r\n\r\n"
#define BUFFER 96

int Botton_1;
String a="";
String GET , cmd ;
char Json_One,buffer[BUFFER];

void setup() {
  Serial.begin(115200);
  UART.begin(9600);
  Serial.println("Initialising the Serial1...");   
  //------------------------------------------
  pinMode(5,OUTPUT);   
  pinMode(Botton_1|Botton_2,INPUT);   
  //------------------------------------------   
  UART.println(AP_Connect);
  Serial.println(UART.readString());
}

void WiFi_Connect(){
  Rest:
  UART.println(ATMode);
  delay(50);
  Serial.println(UART.readString()); 
  UART.println(ATMUX);
  delay(50);
  Serial.println(UART.readString());
  UART.println(TCP);
  delay(50);
  Serial.println(UART.readString());    
    String Read = String (UART.read());
    if(Read == "ERROR"){
        goto Rest;
    }  
}

void MySQL_BottonData_1(){ 
  WiFi_Connect();
  delay(50);
  GET = SQL_PHP;
  GET += Send_ID_1;
  GET += End;
  MySQL_SendData();
}

void MySQL_SendData(){
  cmd="AT+CIPSEND=" + String(GET.length());  
  UART.println(cmd);
  delay(50);
  UART.println(GET);
  digitalWrite(5, HIGH); 
  delay(50);
  digitalWrite(5, LOW);  
  Serial.println(GET);
  Serial.println(F("----------------------------------------------------------"));  
  GET="";  
}

void loop() {
  Botton_1 = digitalRead(3);
  if(Botton_1 == HIGH){
     a=testupdate;
     Serial.println(F("----------------------------------------------------------"));
     Serial.print("Botton_1 = ");
     Serial.println(Botton_1);    
     MySQL_BottonData_1();
  }  
}
