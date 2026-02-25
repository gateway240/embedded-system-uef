// See https://wolles-elektronikkiste.de/en/arduino-nano-every-a-deep-dive#timer
ISR(TCA0_OVF_vect){  // ISR für den Timer A over
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; // Clear the interrupt flag (needed!)
    PORTE.OUTTGL = PIN2_bm; // Toggle PE2 (Board-LED) 
}

void setup() {
    PORTE.DIRSET = PIN2_bm; // PE2 auf OUTPUT
    // TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV64_gc | TCA_SINGLE_ENABLE_bm; // redundant
    // TCA0.SINGLE.CTRLB = 0; // no output, wave form: normal; redundant
    TCA0.SINGLE.PERBUF = 49999; // Set TOP for Timer A 
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; // enable Timer A overflow interrupt
}

void loop() {}