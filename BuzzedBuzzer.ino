//BuzzedBuzzer by Simple Switch Labs, LLC
//Uses readings from a cheap alcohol sensor to decide when to make a buzzing noise
//looks for increasing alcohol fumes to trigger the buzz
//See http://buzzedbuzzer.com for schematics and detailed build instructions

//Created December 2012

//This code is licensed Creative Commons 3.0 ShareAlike, Attribution
//See https://creativecommons.org/licenses/by-sa/3.0/  for detailed licensing information


#include "pins.h"

unsigned int baseline = 0;
int readings[STORAGE];
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
  
  get_baseline();

}

void loop()
{
  
  take_a_reading();
  
  if((readings[0] >= (baseline + 50)) && (readings[0] >= rollingaverage + 20)) //Look for increasing alcohol signal above baseline. Stop buzzing as soon as alcohol starts to drop.
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
  for(int i=(STORAGE - 1);i>0;i--)
  {
    readings[i] = readings[i-1];
    //Serial.print(readings[i]);
    //Serial.print(", ");
  }
  
  readings[0] = analogRead(SENSOR);
  Serial.print("latest = ");
  Serial.print(readings[0],DEC);
  
  rollingaverage = 0;

  
  for(int i=1;i<STORAGE;i++)
  {
    rollingaverage += readings[i];
  }
  rollingaverage /= (STORAGE - 1);
  Serial.print(" rollingavg = ");
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
  
void get_baseline()
{
  for(int i=0;i<STORAGE;i++)
  {
    readings[i]=analogRead(SENSOR);
   /// Serial.println(readings[i]);
    delay(100);
  }
  
  for(int i=0;i<STORAGE;i++)
  {
    baseline += readings[i];
  }
  baseline /= STORAGE;
  Serial.print("baseline= "); 
  Serial.println(baseline);
}

