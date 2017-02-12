
#include <stdarg.h>
#include "IRLibSendBase.h"
#include "IRLib_P01_NEC.h"
IRsendNEC mySender;
//#include "IRLib_P07_NECx.h"
//IRsendNECx mySender;

void printf_serial(char *fmt, ... ){
        char buf[512]; // resulting string limited to 512 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 512, fmt, args);
        va_end (args);
        //SerialUSB.print(buf);
        Serial.print(buf);
}

void send_command(int cmd_char, int repeat = 0) {    
  uint32_t cmd_code = -1;
  int   delay_time = 150;
  int   repeat_time = 150;
  switch (cmd_char) {
    case '1':
      printf_serial("1\n");
      cmd_code = 0x00FF906F;
      break;
    case '2':
      printf_serial("2\n");
      cmd_code = 0x00FFB847;
      break;
    case '3':
      printf_serial("3\n");
      cmd_code = 0x00FFF807;
      break;
    case '4':
      printf_serial("4\n");
      cmd_code = 0x00FF9867;
      break;
    case '5':
      printf_serial("5\n");
      cmd_code = 0x00FFD827;
      break;
    case '6':
      printf_serial("6\n");
      cmd_code = 0x00FFB24D;
      break;
    case '7':
      printf_serial("7\n");
      cmd_code = 0x00FF28D7;
      break;
    case '8':
      printf_serial("8\n");
      cmd_code = 0x00FF12ED;
      break;
    case '9':
      printf_serial("9\n");
      cmd_code = 0x00FF2AD5 ;
      break;
    case 'o':
      printf_serial("onoff\n");
      cmd_code = 0x00FF08F7;
      delay_time = 6000;
      break;
    case '+':
      printf_serial("+\n");
      cmd_code = 0x00FF00FF;
      repeat_time = 100;
      break;
    case '-':
      printf_serial("-\n");
      cmd_code = 0x00FF58A7;
      repeat_time = 100;
      break;
    case 'a':
      printf_serial("Alarm\n");
      cmd_code = 0x00FFC03F;
      break;
    case 'i':
      printf_serial("Info\n");
      cmd_code = 0x00FF6897;
      break;
  }
  if (cmd_code != -1) {
    mySender.send(cmd_code); 
    while (repeat > 0) {
      delay(repeat_time);
      printf_serial(".\n");
      mySender.send(cmd_code);
      repeat--; 
    }    
    delay(delay_time);
  }

  //  mySender.send(0x00FFA857); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  stjerne
  //  mySender.send(0x00FF48B7); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  10
  //  mySender.send(0x00FFA05F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  eq
  //  mySender.send(0x00FF609F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  scan
  //  mySender.send(0x00FF20DF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  menu
  //  mySender.send(0x00FFB04F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  Mode
  //  mySender.send(0x00FF30CF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  Mute
  //  mySender.send(0x00FF7887); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  OK
  //  mySender.send(0x00FF708F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  høyre
  //  mySender.send(0x00FF50AF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  venstre
  //  mySender.send(0x00FF40BF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  lys}
}

//#define TICK_PRELOAD 34286            // preload timer 65536-16MHz/256/2Hz
//#define TICK_PRELOAD 62411             // preload timer 65536-16MHz/256/20Hz
#define TICK_PRELOAD 65223             // preload timer 65536-16MHz/256/200Hz

void initTimerTick() {
  // initialize timer1 
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = TICK_PRELOAD;
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}

volatile int tickCnt = 0;
int inChar;
typedef enum {UP, DOWN, UNDEF} direction_t;
int lastEncode = -1;
direction_t lastDirection = UNDEF;
volatile int volCount = 0;
const byte encodeAPin = 5;
const byte encodeBPin = 6;
const byte onOffPin = 7;
const byte p1Pin = 13;
const byte p2Pin = 12;
const byte p3Pin = 11;
const byte p4Pin = 10;
const byte p5Pin = 9;
const byte p6Pin = 8;
volatile byte state = LOW;

ISR(TIMER1_OVF_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  int newEncode = 0;
  direction_t newDirection = UNDEF;
  
  TCNT1 = TICK_PRELOAD;            // preload timer
  //tickCnt++;

  newEncode |= digitalRead(encodeAPin); 
  newEncode <<=1;
  newEncode |= digitalRead(encodeBPin); 

  if (lastEncode != newEncode) {
    //printf_serial("New encode %d %d vol %d\n", newEncode, lastEncode, volCount);
    
    switch (lastEncode) {
      case 0:
        switch (newEncode) {
          case 1:
            newDirection = UP;
            break;
          case 2:
            newDirection = DOWN;
            break;
        }
        break;
      case 1:
        switch (newEncode) {
          case 3:
            newDirection = UP;
            break;
          case 0:
            newDirection = DOWN;
            break;
        }
        break;
      case 3:
        switch (newEncode) {
          case 2:
            newDirection = UP;
            break;
          case 1:
            newDirection = DOWN;
            break;
        }
        break;
      case 2:
        switch (newEncode) {
          case 0:
            newDirection = UP;
            break;
          case 3:
            newDirection = DOWN;
            break;
        }
        break;
    }
    //printf_serial("New encode %d %d dir %d %d\n", newEncode, lastEncode, newDirection, lastDirection);
    if (newDirection != UNDEF) {
      if (lastDirection == newDirection) {
        if (newDirection == UP) {
          volCount +=1;
        } else {
          volCount -=1;
        }
        lastDirection = UNDEF;
        //printf_serial("New encode %d vol %d\n", newEncode, volCount);
      } else {
        lastDirection = newDirection;
      }
    }
    lastEncode = newEncode;
  }
}

int readPin(int pinNum) {
  int ret = 0;
  if (digitalRead(pinNum)==0) ret |= (1 << pinNum);
  return ret; 
}

int readPins(void) {
  int ret = 0;
  ret |= readPin(onOffPin);
  ret |= readPin(p1Pin);
  ret |= readPin(p2Pin);
  ret |= readPin(p3Pin);
  ret |= readPin(p4Pin);
  ret |= readPin(p5Pin);
  ret |= readPin(p6Pin);
  return ret;
}

void testPin(int pinNum, int cmd, int currXor) {
  int pinMask = 1<<pinNum;
  if ((currXor & pinMask) != 0) {
    printf_serial("Do <%c> \n", cmd);
    send_command(cmd);    
  }
}


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(encodeAPin, INPUT_PULLUP);
  pinMode(encodeBPin, INPUT_PULLUP);
  pinMode(onOffPin, INPUT_PULLUP);
  pinMode(p1Pin, INPUT_PULLUP);
  pinMode(p2Pin, INPUT_PULLUP);
  pinMode(p3Pin, INPUT_PULLUP);
  pinMode(p4Pin, INPUT_PULLUP);
  pinMode(p5Pin, INPUT_PULLUP);
  pinMode(p6Pin, INPUT_PULLUP);
  initTimerTick();
} // the setup function runs once when you press reset or power the board

// the loop routine runs over and over again forever:
void loop() {
  static int newTick = 0;
  static int lastPins = 0;
  int currPins = 0;
  int currXorPins = 0;
  
  if (newTick != tickCnt) {
    newTick = tickCnt;
    printf_serial("New tick %d \n", newTick);
  }
  
  if (volCount != 0) {
    int diffCount = volCount;
    if (diffCount > 0) {
      if (diffCount > 2) diffCount = 2;
      send_command('+', diffCount-1);
      noInterrupts();           // disable all interrupts
      volCount -= diffCount;
      interrupts();             // enable all interrupts
    } else if (diffCount < 0) {
      if (diffCount < -2) diffCount = -2;
      send_command('-', (-diffCount)-1);
      noInterrupts();           // disable all interrupts
      volCount -= diffCount;
      interrupts();             // enable all interrupts
    }
    //printf_serial("New volCount %d \n", volCount);
  }
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    inChar = Serial.read();
    send_command(inChar);
  }
  
  currPins = readPins();
  delay(20); // Delay 20ms to debounce 
  currPins &= readPins();
  
  currXorPins = currPins ^ lastPins; // Which pins are changed
  currXorPins &= currPins; // Which pins changed to 1
  lastPins = currPins;
  
  testPin(onOffPin, 'o', currXorPins);
  testPin(p1Pin, '1', currXorPins);
  testPin(p2Pin, '2', currXorPins);
  testPin(p3Pin, '3', currXorPins);
  testPin(p4Pin, '4', currXorPins);
  testPin(p5Pin, '5', currXorPins);
  testPin(p6Pin, '6', currXorPins);
  
}





