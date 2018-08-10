// get RAW data from the sensor
// Loovee
// 2016-11-10

#include <Wire.h>
#include "MutichannelGasSensor.h"

#define SENSOR_ADDR     0X04        // default to 0x04
float current_NH3;
float last_NH3 = 430; 
float NH3array[100]; 
float NH3total = 0; 
int counter = 0; 
void setup()
{
    Serial.begin(115200);
    gas.begin(SENSOR_ADDR);     // 
}
void fanblow(){
  //call the fan to blow out temporarily 
  ;
}
void loop()
{   
    current_NH3 = gas.getRs(0);
    if (counter<100){
       NH3total+= current_NH3; 
       counter++; 
    }
    else{
      if(NH3total<43000){
         Serial.println("need clean(C)"); 
         if(NH3total<30000)
         Serial.println("immediately(I)"); 
         else if(NH3total<35000)
         Serial.println("urgently(U)");
         else if(NH3total<40000)
         Serial.println("very much(V)"); 
         else
         ; 
         NH3total = 0; 
      }
    }
    if(last_NH3 - current_NH3 >10){
      Serial.println("bad smell(B)"); 
      if (last_NH3 - current_NH3 >20){
        Serial.println("terrible smell(T)"); 
      }
      fanblow(); 
      delay(200); 
    }
    last_NH3 = current_NH3; 
    delay(3000); 
}
