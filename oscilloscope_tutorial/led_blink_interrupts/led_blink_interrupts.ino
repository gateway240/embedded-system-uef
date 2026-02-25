// From: https://forum.arduino.cc/t/nano-every-atmega4809-blink-demo-with-timer-interrupt/1179124/14
/* Blink using timer interrupt */

/* All timers are set up by the standard initialization of
the Arduino IDE with CLK_TCA at DIV64 giving 4us ticks.
I will use TCB2 to avoid messing with millis() or PWM */

ISR(TCB2_INT_vect) {
  PORTE.OUTTGL = 1 << PIN2;                           // to toggle pin PE2
  TCB2.INTFLAGS = TCB_CAPT_bm;                        // reset interrupt flag
  /* Dont ask why TCB_CAPT_bm to reset TCB2_INT_vect */
}

void setup() {
  PORTE.DIRSET = 1 << PIN2;                           // set pin PE2 (LED_BUILTIN) as output
  TCB2.CTRLA = 0;                                     // stop timer while setting up
  TCB2.CTRLB = 0;                                     // remove previous setting, default is Periodic Interrupt Mode
  TCB2.CCMP = 62500;                                  // 62500 x 4us = 250ms (max = 262ms)
  /* for longer periods use an overflow counter */
  TCB2.INTFLAGS = TCB_CAPT_bm;                        // reset possible previous interrupt
  TCB2.INTCTRL = TCB_CAPT_bm;                         // enable interrupt
  TCB2.CNT = 0;                                       // clear timer
  TCB2.CTRLA = TCB_CLKSEL_CLKTCA_gc | TCB_ENABLE_bm;  // start timer
}

void loop() {
  // put your main code here, to run repeatedly:
}