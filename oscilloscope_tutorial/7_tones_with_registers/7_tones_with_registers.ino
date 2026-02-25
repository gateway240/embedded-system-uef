
#define F_CPU 16000000UL

// Note frequencies (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

void setFrequency(uint16_t freq)
{
  uint16_t per = (F_CPU / freq) - 1;

  TCA0.SINGLE.PERBUF  = per;
  TCA0.SINGLE.CMP0BUF = per / 2;   // 50% duty cycle
}

void setup() {
  // See: https://emalliab.wordpress.com/2022/01/23/arduino-nano-every-timers-and-pwm/
  pinMode(9, OUTPUT);

  PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTB_gc; // Enable "alternative" pin output PORTB[5:0] for TCA0
  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm; // SysClk and enabled
  TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_DSTOP_gc;
  TCA0.SINGLE.CTRLD = 0; // Normal (Single) mode (not split)

  setFrequency(NOTE_C4);

  TCA0.SINGLE.INTCTRL |= TCA_SINGLE_OVF_bm; // Turn on interrupts
}

void loop() {

  uint16_t melody[] = {
    NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
    NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
  };

  for (int i = 0; i < 8; i++) {
    setFrequency(melody[i]);
    delay(400);
  }

  delay(1000);
}