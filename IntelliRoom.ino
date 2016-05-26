
//PINS
int pirPin = 8;
int pirLedPin = 10;
int timeLedPin = 9;
int buttonPin = 2;

//OPTIONS
int pirLedMaxPwm = 255;
int timeLedMaxPwm = 255;

int timeLedUpSpeed = 2;
int timeLedDownSpeed = 1;
int pirLedUpSpeed = 4;
int pirLedDownSpeed = 1;

int timeLedIntervalToAdd = 30000;

//vars
int timeLedPwm = 0;
int timeLedTargetPwm = 0;
long tileLedEndTime = millis();
int pirLedPwm = 0;
int pirLedTargetPwm = 0;
int buttonWas = 0;
long buttonWhen = millis();

//funcs
void handleTimeLed();
void handleTimer();
void handlePirLed();
void handlePir();
void handleButton();
void onClick();

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(timeLedPin, OUTPUT);
  pinMode(pirLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}



void loop() {
  handleTimeLed();
  handleTimer();
  handlePir();
  handlePirLed();
  handleButton();
  delay(50);
}

void handleButton() {
  if (!digitalRead(buttonPin) && buttonWas == 0 && millis() - buttonWhen > 100) {

    onClick();

    buttonWas = 1;
  } else if (digitalRead(buttonPin)) {
    buttonWhen = millis();
    buttonWas = 0;
  }

}

void onClick() {
  if (tileLedEndTime < millis()) {
    tileLedEndTime = millis();
  }
  tileLedEndTime += timeLedIntervalToAdd;
}

void handleTimer() {
  if (tileLedEndTime < millis()) { //koniec czasu
    timeLedTargetPwm = 0;
  } else {
    timeLedTargetPwm = timeLedMaxPwm;
  }
}

void handleTimeLed() {
  if (timeLedPwm < timeLedTargetPwm) {
    timeLedPwm += timeLedUpSpeed;
    if (timeLedPwm > timeLedTargetPwm)timeLedPwm = timeLedTargetPwm;
    analogWrite(timeLedPin, timeLedPwm);
  } else if (timeLedPwm > timeLedTargetPwm) {
    timeLedPwm -= timeLedDownSpeed;
    if (timeLedPwm < timeLedTargetPwm)timeLedPwm = timeLedTargetPwm;
    analogWrite(timeLedPin, timeLedPwm);
  }
}

void handlePir() {
  if (digitalRead(pirPin)) {
    pirLedTargetPwm = pirLedMaxPwm;
  } else {
    pirLedTargetPwm = 0;
  }
}

void handlePirLed() {
  if (pirLedPwm < pirLedTargetPwm) {
    pirLedPwm += pirLedUpSpeed;
    if (pirLedPwm > pirLedTargetPwm) pirLedPwm = pirLedTargetPwm;
  } else if (pirLedPwm > pirLedTargetPwm) {
    pirLedPwm -= pirLedDownSpeed;
    if (pirLedPwm < pirLedTargetPwm) pirLedPwm = pirLedTargetPwm;
  }
  analogWrite(pirLedPin, pirLedPwm);
}

