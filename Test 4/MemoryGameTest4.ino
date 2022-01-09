//save random numbers in array and diplay them
const int ledPin[] = {12, 10, 8, 6};  // LED pins
const int nrLED = 4; // number of LEDs
int saveNr[] = {}; //empty array to save random order of LED
int count = 0; //startposition for counter
String test = "";

void setup(){
  for(int x=0; x<nrLED; x++)
  {
    pinMode(ledPin[x], OUTPUT);
  }

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  Serial.begin(9600);
}

void loop() {
  delay(2000); //wait 2 secs before starting
  byte randNr = random(0, nrLED); //random number for LED pin: 0 to <nrLED (0,1,2,3) 

  //blink random LED
  digitalWrite(ledPin[randNr], HIGH);
  delay(1000);
  digitalWrite(ledPin[randNr], LOW);
  delay(1000);

  saveNr[count] = randNr; //save random Nr to array 'saveNr' on position 'count'
  test.concat(saveNr[count]);

  Serial.print(count, DEC);
  Serial.write(": ");
  Serial.println(test);
  //Serial.println(randNr, DEC);
  count++;
}
