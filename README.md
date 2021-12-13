# Mini_Projects


  **Frequency_Meter**

  To Masure Frequency of AC 230V/340V, Home Power line

  The circuit:
  - Stepped down and rectified AC Voltage "Live" connected to PIN 1(Anode) of Optocoupler
  - "Neutral" is connected to PIN 2(Cathode) of Optocoupler
  - PIN 4(Collector) of Optocoupler is connected to PIN 2 of Arduino Nano and Pulled up with 10k Resistor 
  - PIN 3(Emitter) of Optocoupler is connected to GND of Arduino Nano
  - Note: Don't Touch circuit while working, Risk of Electric shock





  **Motion Control Switch with Daylight Feature**

  To Switch On light for 10 sec if motion detected during night
  Project Uses ATtiny 13A as a Microcontroller

  The circuit:

  - LDR connected with Pulldown resistor to PIN PB0 of ATtiny 13A
  - IN of Relay Module connected to PIN PB4 of ATtiny 13A
  - OUT of Proximity Sensor connected to PIN PB of ATtiny 13A

  Import all the Libraries before

  created 2021
  by Manu Yadav
