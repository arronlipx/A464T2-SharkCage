const byte numChars = 32;
char receivedChars[numChars];  // an array to store the received data

boolean newData = false;
const int fastSwitch = 12;  //connect pin 12 to fast switch
const int selSwitch = 11;  // connect pin 11 to select switch
const int fastLed = 10;
const int selLed =9;

//delay intervals between steps
const int hiSpd=30;
const int loSpd=100;
const int midSpd=50;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(microwave_pin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
