// EnableInterrupt Simple example sketch
// See the Wiki at http://code.google.com/p/arduino-pinchangeint/wiki for more information.

#define COUNTEXTERNAL
volatile uint8_t externalInterruptCounter=0;
#include <EnableInterrupt.h>

volatile uint8_t anyInterruptCounter=0;

#ifdef ARDUINO_MEGA

#define PINCOUNT(x) pin ##x ##Count

#define interruptFunction(x) \
  volatile uint8_t PINCOUNT(x); \
  void interruptFunction ##x () { \
    anyInterruptCounter++; \
    interruptSaysHello(); \
    PINCOUNT(x)++; \
  }

#define updateOn(x) \
  if (PINCOUNT(x) != 0) { \
    printIt((char *) #x, PINCOUNT(x)); \
    PINCOUNT(x)=0; \
  }

#define setupPCInterrupt(x) \
  pinMode( x, INPUT_PULLUP); \
  enableInterrupt( x | PINCHANGEINTERRUPT, interruptFunction##x, CHANGE)

#define setupInterrupt(x) \
  pinMode( x, INPUT_PULLUP); \
  enableInterrupt( x, interruptFunction##x, CHANGE)

interruptFunction(SS);
interruptFunction(SCK);
interruptFunction(MOSI);
interruptFunction(MISO);
interruptFunction(10);
interruptFunction(11);
interruptFunction(12);
interruptFunction(13);
interruptFunction(14);
interruptFunction(15);
interruptFunction(A8);
interruptFunction(A9);
interruptFunction(A10);
interruptFunction(A11);
interruptFunction(A12);
interruptFunction(A13);
interruptFunction(A14);
interruptFunction(A15);
interruptFunction(70); // fake 70, trick to allow software interrupts on Port J. PJ2
interruptFunction(71); // fake 71. PJ3
interruptFunction(72); // fake 72. PJ4
interruptFunction(73); // fake 73. PJ5
interruptFunction(74); // fake 74. PJ6
// External Interrupts
interruptFunction(21);
interruptFunction(20);
interruptFunction(19);
interruptFunction(18);
interruptFunction(2);
interruptFunction(3);
interruptFunction(75); // fake 75. PE6
interruptFunction(76); // fake 76. PE7
#else
#error This sketch supports 2560-based Arduinos only.
#endif

void printIt(char *pinNumber, uint8_t count) {
    printPSTR("Pin ");
    Serial.print(pinNumber);
    printPSTR(" was interrupted: ");
    Serial.println(count, DEC);
}

// Attach the interrupt in setup()
// NOTE: PORTJ2-6 (aka, "Pin '70', '71', '72', '73', '74'" are turned on as OUTPUT.
// These are not true pins on the Arduino Mega series!
void setup() {
  //uint8_t pind, pink;
  Serial.begin(115200);
  Serial.println("---------------------------------------");
  //PORTD=pind;
  //PORTK=pink;
  pinMode(PINSIGNAL, OUTPUT);
  //pinMode(ARDUINOPIN, INPUT_PULLUP);  // Configure the pin as an input, and turn on the pullup resistor.
                                      // See http://arduino.cc/en/Tutorial/DigitalPins
  //PORTC=0x01;
  setupInterrupt(SS);
  setupInterrupt(SCK);
  setupInterrupt(MOSI);
  setupInterrupt(MISO);
  setupInterrupt(10);
  setupInterrupt(11);
  setupInterrupt(12);
  setupInterrupt(13);
  setupInterrupt(14);
  setupInterrupt(15);
  setupInterrupt(A8);
  setupInterrupt(A9);
  setupInterrupt(A10);
  setupInterrupt(A11);
  setupInterrupt(A12);
  setupInterrupt(A13);
  setupInterrupt(A14);
  setupInterrupt(A15);
  ////
  DDRJ |=0b01111100; // Non-Arduino Port J pins all become output.
  PORTJ|=0b01111100; // Turn them all high.
  enableInterrupt(70, interruptFunction70, CHANGE);
  enableInterrupt(71, interruptFunction71, CHANGE);
  enableInterrupt(72, interruptFunction72, CHANGE);
  enableInterrupt(73, interruptFunction73, CHANGE);
  enableInterrupt(74, interruptFunction74, CHANGE);
  // External Interrupts
  setupInterrupt(21);
  setupInterrupt(20);
  setupInterrupt(19);
  setupInterrupt(18);
  setupInterrupt(2);
  setupInterrupt(3);
  ////
  DDRE |=0b11000000; // Non-Arduino Port E pins all become output.
  PORTE|=0b11000000; // Turn them all high.
  enableInterrupt(75, interruptFunction75, CHANGE);
  enableInterrupt(76, interruptFunction76, CHANGE);
}

// In the loop, we just check to see where the interrupt count is at. The value gets updated by the
// interrupt routine.
void loop() {
  uint8_t jbits =0b01111110; // PJ2
  uint8_t njbits=0b00000001; // PJ2
  uint8_t ebits =0b11000000; // PE6/7
  uint8_t nebits=0b00111111; // PE6/7
  PORTE &= nebits;
  PORTJ &= njbits;
  //*out &= njbits;
  delay(1);
  PORTE |= ebits;
  PORTJ |= jbits;
  //*out |= jbits;
  delay(1);
  Serial.println("---------------------------------------");
  delay(1000);                          // Every second,
  updateOn(SS);
  updateOn(SCK);
  updateOn(MOSI);
  updateOn(MISO);
  updateOn(10);
  updateOn(11);
  updateOn(12);
  updateOn(13);
  updateOn(14);
  updateOn(15);
  updateOn(A8);
  updateOn(A9);
  updateOn(A10);
  updateOn(A11);
  updateOn(A12);
  updateOn(A13);
  updateOn(A14);
  updateOn(A15);
  // External Interrupts
  updateOn(2);
  updateOn(3);
  updateOn(18);
  updateOn(19);
  updateOn(20);
  updateOn(21);
  // Fake Arduino Pins
  updateOn(70);
  updateOn(71);
  updateOn(72);
  updateOn(73);
  updateOn(74);
  // External Interrupts
  updateOn(75);
  updateOn(76);
  printIt("XXX", anyInterruptCounter);
  if (externalInterruptCounter > 0) { printPSTR(" ext: "); Serial.println(externalInterruptCounter); }; \
  externalInterruptCounter=0;
}

