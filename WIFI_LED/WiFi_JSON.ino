void json_Resolve()
{
  Mode="1";
  int count ;
  while(Mode=="1")
  {  
   count++;
   Serial.println(count);
   if(count == 3000){digitalWrite(SWITCH[4], LOW); count = 0; break;}   
           
     if(Serial1.available()>0){
        Json_One=Serial1.read();
        digitalWrite(SWITCH[4], HIGH);       
        while(Json_One=='{')
        {
          delay(10);
          Json_Two=char(Serial1.read());
          Json+=Json_Two;
          if(Json_Two=='}')
          {
           Serial.println(F("----------------------------------------------------------"));
            Serial.print("Json:");
            Serial.println(Json); 
            Json_One='0';         
            JsonDoing();
            digitalWrite(SWITCH[4], LOW);
         } 
        }
      }
    }
}
void JsonDoing(void)
{
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject & root = jsonBuffer.parseObject(Json);
  if(!root.success())
  {
    Serial.println("Error");
  }
 Json="{";
  SW1 = root["SWITCH_1"];
  SW2 = root["SWITCH_2"];
  SW3 = root["SWITCH_3"];
  SW4 = root["SWITCH_4"];
  
  Switch_State ();
  jsonBuffer.clear();
  Json_One=0;
}


