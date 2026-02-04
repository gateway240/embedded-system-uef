//credits: Daniel Rossi, I.T. Engineering student from Modena(IT)
//YouTube: Https://youtube.com/c/ProjectoOfficial?sub_confirmation=1

/*
duty cycle in arduino is represented by a 8 bit value: 0 - 255
0 --> 0%
127 -->50%
255 --> 100%
*/

#define pwm 5
#define pot A0

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm,OUTPUT);
  pinMode(pot,INPUT);
  Serial.begin(9600);
  while (!Serial);   // important on Nano Every
  //safety speed reset of the motor
  analogWrite(pwm,0);

}

void loop() {
  // put your main code here, to run repeatedly:
  float val = analogRead(pot);
  int duty = analogRead(pot) >> 2; // 0–255
  analogWrite(pwm, duty); //here's how to generate PWM signal from Digital arduino pin
  Serial.println(duty);
  delay(10);
}
