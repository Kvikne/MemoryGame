//save random numbers in array and wait for button
//button has to be same as LED

//start variables
const int ledPin[] = {12, 10, 8, 6}; //LED pins
const int butPin[] = {11, 9, 7, 5}; //Button pins
const int nrLED = 4; //number of LEDs
const int nrBut = 4; //number of buttons
const int startButPin = 11; //Pin for start button
int saveNr[] = {}; //empty array to save random order of blinking LED
int count = 1; //startposition for counter //array pos 0 funktioniert nicht?
int endCheck = false; //check value for user input check

//-------------------------------------------------------------------------------------------------------------
//Setup

void setup() {
  //Setup for serial monitor for tests
  //Serial.begin(9600);

  //Setup for LEDs
  for (int x = 0; x < nrLED; x++)
  {
    pinMode(ledPin[x], OUTPUT);
  }

  //Setup for buttons
  for (int x = 0; x < nrBut; x++)
  {
    pinMode(butPin[x], INPUT_PULLUP); //INPUT_PULLUP turns on the internal pullup resistor ~50k ohm
    digitalWrite(butPin[x], HIGH);
  }

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  //Start Sequence
  startSeq(nrLED); //Execute start sequence
}


//Reset function
void(* resetFunc) (void) = 0;//declare reset function at address 0

//-------------------------------------------------------------------------------------------------------------
//Main Code

void loop() {
  byte randPin = random(0, nrLED); //random number for LED pin: 0 to <nrLED (0,1,2,3)

  saveNr[count] = randPin; //save randPin to array 'saveNr' on position 'count'
  count++;

  for (int i = 1; i < count; i++) {
    blinkOnce(saveNr[i]); //blink once for each LED in saved array
  }

  for (int i = 1; (i < count); i++) {
    butWait(saveNr[i]);
  }

  delay(1000);
}

//-------------------------------------------------------------------------------------------------------------
//Functions

//blink LED once
//pinNr = random pin each time
void blinkOnce(int pinNr)
{
  digitalWrite(ledPin[pinNr], HIGH);
  delay(1000);
  digitalWrite(ledPin[pinNr], LOW);
  delay(1000);
}

//read buttons
//waiting for button "x" to be pushed
//x == pin
void butWait(int x)
{
  int a, b, c = 0;
  switch (x) {
    case 0:
      a = 1;
      b = 2;
      c = 3;
      break;
    case 1:
      a = 0;
      b = 2;
      c = 3;
      break;
    case 2:
      a = 0;
      b = 1;
      c = 3;
      break;
    case 3:
      a = 0;
      b = 1;
      c = 2;
      break;
  }
  while (digitalRead(butPin[x]) == HIGH) {
    if (digitalRead(butPin[a]) == LOW) { //if wrong button is pushed
      wrongSeq(nrLED);
    }
    else if (digitalRead(butPin[b]) == LOW) { //if wrong button is pushed
      wrongSeq(nrLED);
    }
    else if (digitalRead(butPin[c]) == LOW) { //if wrong button is pushed
      wrongSeq(nrLED);
    }
  }
  while (digitalRead(butPin[x]) == LOW) {
    digitalWrite(ledPin[x], HIGH);
  }
  delay(200);
  digitalWrite(ledPin[x], LOW);
}

//start sequence
void startSeq(int nrLED)
{
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < nrLED; j++) {
      digitalWrite(ledPin[j], HIGH);
      delay(200);
      digitalWrite(ledPin[j], LOW);
    }
  }
  delay(2000);
}

//wrong answer sequence
//if user hits wrong button show this and then reset Arduino
void wrongSeq(int nrLED)
{
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < nrLED; j++) {
      digitalWrite(ledPin[j], HIGH);
    }
    delay(1500);
    for (int x = 0; x < nrLED; x++) {
      digitalWrite(ledPin[x], LOW);
    }
    delay(2000);
  }
  delay(1000);
  resetFunc();
}
