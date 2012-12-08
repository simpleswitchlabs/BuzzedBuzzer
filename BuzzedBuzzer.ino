#include "pins.h"
//#include <OneWire.h>
//OneWire ds(TSENSOR);

unsigned int baseline = 0;
int readings[5];
unsigned int rollingaverage = 0;


void setup()
{
  pinMode(TRANSMIT, OUTPUT);
  pinMode(SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600); 

  //establish a baseline
  delay(1000); //let readings stabilize a moment

  for(int i=0;i<5;i++)
  {
    readings[i]=analogRead(SENSOR);
    Serial.println(readings[i]);
    delay(100);
  }
  
  for(int i=0;i<5;i++)
  {
    baseline += readings[i];
  }
  baseline /= 5;
  Serial.println("baseline="); 
  Serial.println(baseline);

}

void loop()
{
  
  take_a_reading();
  
  if((readings[0] >= (baseline + 50)) && (readings[0] >= rollingaverage + 20))
  {
    buzz();
  }
  else
  {
    nobuzz();
  }
  
  delay(150);

}

void take_a_reading()
{
  for(int i=4;i>0;i--)
  {
    readings[i] = readings[i-1];
    Serial.print(readings[i]);
    Serial.print(", ");
  }
  
  readings[0] = analogRead(SENSOR);
  Serial.println(readings[0],DEC);
  
  rollingaverage = 0;

  
  for(int i=1;i<5;i++)
  {
    rollingaverage += readings[i];
  }
  rollingaverage /= 4;
  Serial.print("rollingavg = ");
  Serial.println(rollingaverage);
}

void buzz()
{
  digitalWrite(BUZZER,HIGH);
  digitalWrite(LED,HIGH);
  Serial.println("BUZZ!!!");
}

void nobuzz()
{
  digitalWrite(BUZZER,LOW);
  digitalWrite(LED,LOW);
  Serial.println("nobuzz");
}
  

