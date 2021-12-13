/*
  Motion Control Switch with Daylight Feature

  To Switch On light for 10 sec if motion detected during night
  Project Uses ATtiny 13A as a Microcontroller

  The circuit:

  - LDR connected with Pulldown resistor to PIN PB0 of ATtiny 13A
  - IN of Relay Module connected to PIN PB4 of ATtiny 13A
  - OUT of Proximity Sensor connected to PIN PB of ATtiny 13A


  created 2021
  by Manu Yadav

  
*/


int LDR = 0; // Initialized "LDR" variable and Passed PIN No at which LDR is connected 
int Relay = 4; // Initialized "Relay" variable and Passed PIN No at which Relay IN is connected 
int Intr = 3; // Initialized "Intr" variable and Passed PIN No at which Proximity OUT is connected 


bool Light; //Variable of Boolean Data type to store light Status 
bool Motion; //Variable of Boolean Data type to store Motion Status 
 

void setup() {

  pinMode(Relay, OUTPUT); // Initialized PB4 as OUTPUT (Check Initialization for reference)
  pinMode(LDR, INPUT);  //Initialized PB0 as INPUT
  pinMode(Intr, INPUT);  //Initialized PB3 as INPUT
}

void loop() {

  // Read the Value at PB0
  // If LDR detect Daylight then it passes HIGH to PIN PB0 
  // and Relay is in OFF state even if motion Detected
  // If LDR is in Dark while loop is executing

  while(digitalRead(LDR) == LOW) 
  {
    Motion = digitalRead(Intr); // Read the Value at PB3
    if(Motion == LOW) // If motion Detected then Proximity Sensor send LOW signal
    {
      digitalWrite(Relay, HIGH); // Send HIGH signal to Relay and Switch ON the Light 
      delay(10000); // Delay of 10 sec
    }
    else
    {
      digitalWrite(Relay, LOW);
    }
  }
  digitalWrite(Relay, LOW);

}