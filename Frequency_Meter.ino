/*
  Frequency_Meter

  To Masure Frequency of AC 230V/340V, Home Power line

  The circuit:
  - Stepped down and rectified AC Voltage "Live" connected to PIN 1(Anode) of Optocoupler
  - "Neutral" is connected to PIN 2(Cathode) of Optocoupler
  - PIN 4(Collector) of Optocoupler is connected to PIN 2 of Arduino Nano and Pulled up with 10k Resistor 
  - PIN 3(Emitter) of Optocoupler is connected to GND of Arduino Nano
  - Note: Don't Touch circuit while working, Risk of Electric shock

  Import all the Libraries before

  created 2021
  by Manu Yadav

  
*/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(void) {

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(25, 8);     // Start at top-left corner
  display.print("Hello!");

  display.display();

  delay(2000); // Pause for 2 seconds
  
  // Clear the buffer
  display.clearDisplay();
 
  // Timer1 module configuration

  
  // Timer1 module is configured to increment by 2 every 1 microsecond (prescaler = 8) and its overflow
  // interrupt is enabled in order to reset the variable tmr1 (helps when signal is removed).
  // With prescaler = 8, the clock input of Timer1 module is equal to: Timer1_CLK = 16MHz/8 = 2MHz.


  TCCR1A = 0;
  TCCR1B = 2;   // enable Timer1 module with 1/8 prescaler ( 2 ticks every 1 us)
  TCNT1  = 0;   // Set Timer1 preload value to 0 (reset)
  TIMSK1 = 1;   // enable Timer1 overflow interrupt
 
  EIFR |= 1;  // clear INT0 flag
  Serial.begin(9600);
  attachInterrupt(0, timer1_get, FALLING);  // enable external interrupt (INT0)
}
 
uint16_t tmr1 = 0;
float period, frequency;
 
void timer1_get() {
  tmr1 = TCNT1;
  TCNT1  = 0;   // reset Timer1
}
 
ISR(TIMER1_OVF_vect) {  // Timer1 interrupt service routine (ISR)
  tmr1 = 0;
}
 
// main loop
void loop() {
 
  // save current Timer1 value
  uint16_t value = tmr1;
  // calculate signal period in milliseconds
  // 8.0 is Timer1 prescaler and 16000 = MCU_CLK/1000
  // Signal period:
  //    Period (in us) = Timer1_Value/Timer1_CLK = Timer1_Value/16000000/8
  //    Period(in us) = 8 x Timer1_Value/16000000
  //    Period (in ms) = 8 x Timer1_Value/16000
  period = 8.0 * value/16000;
  
  // calculate signal frequency which is = 1/period ; or = MCU_CLK/(Prescaler * Timer_Value)
  // Signal frequency:
  //     Frequency = 1/Period
  //     Frequency (in Hz) = 16000000/(8 x Timer1_Value)
  if(value == 0)
    frequency = 0;   // aviod division by zero
  else
    frequency = 16000000.0/(8UL*value);
  Serial.print(frequency);  // to print frequency on Serial Monitor
  Serial.print(" Hz  ");
  
  Serial.print(period);     // to print period on Serial Monitor
  Serial.println(" ms  ");

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  
  display.print("Frequency: ");  // to print frequency on OLED Display
  display.print(frequency);
  display.println(" Hz  ");

  display.println();
  

  display.print("Period: ");    // to print Period on OLED Display
  display.print(period);
  display.println(" ms  ");
  display.display();
  
  delay(500);
 
}