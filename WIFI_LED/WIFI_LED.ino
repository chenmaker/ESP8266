//============{Arduino wed-MySQL-download_Data : LED HIGI or LOW }============//
#include <ArduinoJson.h>

//============= {ESP - AT Command設定} =============//
#define  AP_Connect  "AT+CWJAP=\"STUWLAN-L0615_2.4G\",\"l0615&l0615\""
#define  ATMode      "AT+CWMODE=1"
#define  ATMUX       "AT+CIPMUX=0"
#define  CloseIP     "AT+CIPCLOSE" 
#define  TCP """AT+CIPSTART=\"TCP\",\"120.119.73.23\",80"""/*建立 TCP/UDP 連線*/

//============= {Upload or download} =============//
#define SQL_PHP  "GET /phpMyAdmin/JP_Lin/Fire_IOT.php?key=l0615&query="
#define Get_ID   "SELECT * FROM `Fire_IOT` WHERE 1"
#define End "\r\n\r\n"
#define BUFFER 96

char Json_One,Json_Two,buffer[BUFFER];
int SW1,SW2,SW3,SW4;
String GET , cmd , Json="{", Mode;
const byte SWITCH1 = 9, SWITCH2 = 10, SWITCH3 = 11, SWITCH4 = 13;
const int SWITCH[5] = {9 , 10 , 11 , 12 , 13};

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Initialising the Serial1..."); 
  for(int i=0 ; i<5 ; i++){
    pinMode(SWITCH[i],OUTPUT);
  }  
  Serial1.println(AP_Connect);
  delay(500); 
  Serial.println(Serial1.readString());   
  Mode="0"; 
}

void WiFi_Connect(){ 
  Serial1.println(ATMode);
  Serial.println(Serial1.readString());
  delay(100);
  Serial1.println(ATMUX);
  Serial.println(Serial1.readString());
  delay(100);  
  Serial1.println(TCP);
  Serial.println(Serial1.readString());  
  delay(100);  
}

void MySQL_DownloadData(){ 
  WiFi_Connect();
  delay(100);
  GET = SQL_PHP;
  delay(100);
  GET += Get_ID;
  delay(100);
  GET += End;
  delay(100);
  MySQL_SendData();
}

void MySQL_SendData(){
  cmd="AT+CIPSEND=" + String(GET.length());  
  Serial1.println(cmd);
  delay(1000);
  Serial1.println(GET);
  GET=""; 
  json_Resolve();  
}

void loop() {
  Reset:
  MySQL_DownloadData();
  delay(2000);
  digitalWrite(SWITCH[0], LOW);
  digitalWrite(SWITCH[1], LOW);
  digitalWrite(SWITCH[2], LOW);
  digitalWrite(SWITCH[3], LOW);
}
