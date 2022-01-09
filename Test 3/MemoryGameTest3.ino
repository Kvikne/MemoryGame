//LEDs im Array blinken lassen
const int ledPin[] = {12, 10, 8, 6};  // LED pins
const int nrLED = 4; // number of LEDs

void setup(){
  for(int x=0; x<nrLED; x++)
  {
    pinMode(ledPin[x], OUTPUT);
  }
}

void loop() {
  for(int x=0; x<nrLED; x++)
  {
    digitalWrite(ledPin[x], HIGH);
    delay(1000);
    digitalWrite(ledPin[x], LOW);
    delay(1000);
  }
}
