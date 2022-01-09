//LED und Button Test
const int ledPin =  10;//12
const int button = 9;//11
int buttonState = 0;

void setup() {
  pinMode(ledPin, OUTPUT); // Setzt den Digitalpin 13 als Outputpin
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}

void loop() {
  buttonState = digitalRead(button);
  
  if (buttonState == LOW)
  {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  }
}
