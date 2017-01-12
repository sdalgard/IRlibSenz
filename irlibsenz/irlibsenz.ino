
#include <stdarg.h>

void printf_serial(char *fmt, ... ){
        char buf[512]; // resulting string limited to 512 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 512, fmt, args);
        va_end (args);
        //SerialUSB.print(buf);
        Serial.print(buf);
}

#include "IRLibSendBase.h"
#include "IRLib_P01_NEC.h"
IRsendNEC mySender;




// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  
  
} // the setup function runs once when you press reset or power the board

// the loop routine runs over and over again forever:
void loop() {
  delay(2000);
  printf_serial("Hello %d\n", 42);

  delay(2000);
  printf_serial("Send Info\n");
  mySender.send(0x00FF6897); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  Info
  delay(2000);
  printf_serial("Send Alarm\n");
  mySender.send(0x00FFC03F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  alarm
  delay(2000);
  printf_serial("Send Stjerne\n");
  mySender.send(0x00FFA857); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  stjerne
  delay(2000);
  printf_serial("Send 10\n");
  mySender.send(0x00FF48B7); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  10
  delay(2000);
  printf_serial("Send Eq\n");
  mySender.send(0x00FFA05F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  eq
  delay(2000);
  printf_serial("Send Scan\n");
  mySender.send(0x00FF609F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  scan
  delay(2000);
  printf_serial("Send Menu\n");
  mySender.send(0x00FF20DF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  menu
  delay(2000);
  printf_serial("Send Mode\n");
  mySender.send(0x00FFB04F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  Mode
  delay(2000);
  printf_serial("Send Mute\n");
  mySender.send(0x00FF30CF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  Mute
  delay(2000);
  printf_serial("Send OK\n");
  mySender.send(0x00FF7887); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  OK
  delay(2000);
  printf_serial("Send høyre\n");
  mySender.send(0x00FF708F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  høyre
  delay(2000);
  printf_serial("Send venstre\n");
  mySender.send(0x00FF50AF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  venstre
  delay(2000);
  printf_serial("Send lys\n");
  mySender.send(0x00FF40BF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  lys
  delay(2000);
  printf_serial("Send -\n");
  mySender.send(0x00FF58A7); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  -
  delay(2000);
  printf_serial("Send +\n");
  mySender.send(0x00FF00FF); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  +
  delay(2000);
  printf_serial("Send onoff\n");
  mySender.send(0x00FF08F7); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  onoff
  delay(2000);
  printf_serial("Send 9\n");
  mySender.send(0x00FF2AD5); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  9
  delay(2000);
  printf_serial("Send 8\n");
  mySender.send(0x00FF12ED); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  8
  delay(2000);
  printf_serial("Send 7\n");
  mySender.send(0x00FF28D7); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  7
  delay(2000);
  printf_serial("Send 6\n");
  mySender.send(0x00FFB24D); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  6
  delay(2000);
  printf_serial("Send 5\n");
  mySender.send(0x00FFD827); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  5
  delay(2000);
  printf_serial("Send 4\n");
  mySender.send(0x00FF9867); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  4
  delay(2000);
  printf_serial("Send 3\n");
  mySender.send(0x00FFF807); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  3
  delay(2000);
  printf_serial("Send 2\n");
  mySender.send(0x00FFB847); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  2
  delay(2000);
  printf_serial("Send 1\n");
  mySender.send(0x00FF906F); //AnalysIR Batch Export (IRLib) // AnalysIR IR Protocol: NEC, Key:  1

}





