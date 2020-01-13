void Switch_State (){

  Serial.print("SWITCH_1:");Serial.println(SW1);
  Serial.print("SWITCH_2:");Serial.println(SW2);
  Serial.print("SWITCH_3:");Serial.println(SW3);
  Serial.print("SWITCH_4:");Serial.println(SW4);

   if(SW1==1){
   digitalWrite(SWITCH[0], HIGH);
   }
   if(SW1==0){
   digitalWrite(SWITCH[0], LOW);
   }
   if(SW2==1){
   digitalWrite(SWITCH[1], HIGH);
   }
   if(SW2==0){
   digitalWrite(SWITCH[1], LOW);
   }
   if(SW3==1){
   digitalWrite(SWITCH[2], HIGH);
   }
   if(SW3==0){
   digitalWrite(SWITCH[2], LOW);
   }
   if(SW4==1){
   digitalWrite(SWITCH[3], HIGH);
   }
   if(SW4==0){
   digitalWrite(SWITCH[3], LOW);
   }  
    Mode="3"; 
     Serial.println(F("----------------------------------------------------------"));   
}
