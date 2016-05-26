
//PINS
int rollPins[2] = {3,4};

//OPTIONS

//vars
    int lastVal = 0;

//funcs

void prepareMouseRoll(){
    pinMode(rollPins[0], INPUT_PULLUP);
    pinMode(rollPins[1], INPUT_PULLUP);

    lastVal = readRoll();
}

int readRoll(){
    int val=0;
    if(pin1) val+=2;
    if(pin0) val+=1;
    return val;
}

int getRollMove(){
    int val = readRoll();
    if(lastVal = val+1) return 1;
    if(lastVal = val-1) return -1;
    return 0;
}

bool pin0(){
    return !digitalRead(rollPins[0]);
}

bool pin1(){
    return !digitalRead(rollPins[1]);
}
