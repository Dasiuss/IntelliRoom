
//PINS
int pirPin = 8;
int pirLedPin = 10;
int timeLedPin = 9;
int buttonPin = 2;

//OPTIONS
int pirLedMaxPwm = 255;
int timeLedMaxPwm = 255;

int timeLedUpSpeed = 40;
int timeLedDownSpeed = 20;
int pirLedUpSpeed = 80;
int pirLedDownSpeed = 20;

int timeLedIntervalToAdd = 30000;

//vars
int timeLedPwm = 0;
int timeLedTargetPwm = 0;
bool timeLedIsOn = false;
long timeLedEndTime = millis();
long timeLedWhen = millis();
int pirLedPwm = 0;
int pirLedTargetPwm = 0;
long pirLedWhen = millis();
int buttonWas = 0;
long buttonWhen = millis();

//funcs
void handleMouseRoll();
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
  prepareMouseRoll();
}



void loop() {
  handlePir();
  handlePirLed();
  
  handleTimer();
  handleTimeLed();
  
  handleButton();
//  handleMouseRoll();
delay(50);
}

void handleMouseRoll(){
    timeLedTargetPwm += getRollMove();
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
  if(!timeLedIsOn && timeLedEndTime < millis()){//off and no timer
    timeLedIsOn=true;
  }else if (timeLedIsOn){//was on - turn on timer
    timeLedIsOn=false;
    timeLedEndTime = millis();
  }
  timeLedEndTime += timeLedIntervalToAdd;
}

void handleTimer() {
  if (timeLedEndTime < millis() && !timeLedIsOn) { //end of time and not turned on
    timeLedTargetPwm = 0;
  } else {
    timeLedTargetPwm = timeLedMaxPwm;
  }
}

void handleTimeLed() {
  float period = (float)(millis() - timeLedWhen) / 1000;
  if (timeLedPwm < timeLedTargetPwm) {
    timeLedPwm += timeLedUpSpeed * period;
    if (timeLedPwm > timeLedTargetPwm)timeLedPwm = timeLedTargetPwm;
  } else if (timeLedPwm > timeLedTargetPwm) {
    timeLedPwm -= timeLedDownSpeed * period;
    if (timeLedPwm < timeLedTargetPwm)timeLedPwm = timeLedTargetPwm;
  }
  analogWrite(timeLedPin, timeLedPwm);
  timeLedWhen = millis();
}

void handlePir() {
  if (digitalRead(pirPin)) {
    pirLedTargetPwm = pirLedMaxPwm;
  } else {
    pirLedTargetPwm = 0;
  }
}

void handlePirLed() {
  float period = (float)(millis() - pirLedWhen) / 1000;
  if (pirLedPwm < pirLedTargetPwm) {
    pirLedPwm += pirLedUpSpeed * period;
    if (pirLedPwm > pirLedTargetPwm) pirLedPwm = pirLedTargetPwm;
  } else if (pirLedPwm > pirLedTargetPwm) {
    pirLedPwm -= pirLedDownSpeed * period;
    if (pirLedPwm < pirLedTargetPwm) pirLedPwm = pirLedTargetPwm;
  }
  analogWrite(pirLedPin, pirLedPwm);
  pirLedWhen = millis();
}

