/*
 * Time Keeper: By Bjorn Westlund
 */

// constants won't change. They're used here to set pin numbers:
const int buttonPin[] = {4,5,6,7};    // the number of the pushbutton pins
const int ledPin = 13;      // the number of the LED pin


// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState[4];             // the current reading from the input pins
int lastButtonState[] = {LOW, LOW, LOW, LOW};   // the previous reading from the input pins
int reading[4];

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime[] = {0,0,0,0};  // the last time the output pin was toggled
unsigned long debounceDelay[] = {50, 50, 50, 50};    // the debounce time; increase if the output flickers

void setup() {
  // Sets the 4 input Pins for Switch to Ground
  for (int i=0; i < 4; i++){
    pinMode(buttonPin[i], INPUT_PULLUP);
  }
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < 4; i++){
    reading[i] = digitalRead(buttonPin[i]);
  }
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  for (int i=0; i < 4; i++){
    if (reading[i] != lastButtonState[i]) {
      // reset the debouncing timer
      lastDebounceTime[i] = millis();
    }
  }
  for (int i=0; i < 4; i++){ 
    if ((millis() - lastDebounceTime[i]) > debounceDelay[i]) {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:
  
      // if the button state has changed:
      if (reading[i] != buttonState[i]) {
        buttonState[i] = reading[i];
  
        // only toggle the LED if the new button state is HIGH
        if (buttonState[i] == HIGH) {
          ledState = !ledState;
        }
      }
    }
  }
  // set the LED:
  digitalWrite(ledPin, ledState);
  for (int i=0; i < 4; i++){
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState[i] = reading[i];  
  }
  
}
