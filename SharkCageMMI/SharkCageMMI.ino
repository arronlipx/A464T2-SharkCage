#include <Button.h>

const byte numChars = 32;
char receivedChars[numChars];  // an array to store the received data



//State Variables
const char NONE = 0;
const char SELECTED = 1;//near side
const char FAST = 2;
const char SELECTED2 = 3;//far side
const char FAST2 = 4;

//default state is NONE
char state=0;

boolean newData = false;

Button fastSwitch (12,PULLUP);  //connect pin 12 to fast switch
Button selSwitch (11,PULLUP);  	//connect pin 11 to select switch
const int fastLed = 10;		//connect pin 10 to fastLed Relay
const int selLed = 9;		//connect pin 9 to selectLed Relay
const int joystickPin = A0;	//connect pin A0 to joystick 

//connect to other box

Button fastSwitch2 (8,PULLUP);  //connect pin 8 to second fast switch
Button selSwitch2 (7,PULLUP);   //connect pin 7 to second select switch

const int fastLed2 = 6;   //connect pin 6 to second fastLed Relay
const int selLed2 = 5;   //connect pin 5 to second selectLed Relay
const int joystickPin2 = A1; //connect pin A1 to second joystick 


//command signal to roboteq (duty cycle based)
const int roboteqCmd = 3;

//joystick settings
const int joystickMid=512;

//debounce flags
boolean fastSwitchFlag=false;
boolean selSwitchFlag=false;

boolean fastSwitchFlag2=false;
boolean selSwitchFlag2=false;

//switch temp holders
boolean fastSwitchTemp=false;
boolean selSwitchTemp=false;

boolean fastSwitchTemp2=false;
boolean selSwitchTemp2=false;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);
  pinMode(fastLed, OUTPUT);
  pinMode(selLed, OUTPUT);
  pinMode(joystickPin, INPUT);//analog in

  pinMode(fastLed2, OUTPUT);
  pinMode(selLed2, OUTPUT);
  pinMode(joystickPin2, INPUT);//analog in

  pinMode(roboteqCmd, OUTPUT);//analog out

}

void loop() {
  // put your main code here, to run repeatedly:
//
//  if(fastSwitch.uniquePress())
//  {
//    fastSwitchTemp=!fastSwitchTemp;
//
//  }
//      Serial.print("fastSwitch:");
//    Serial.println(fastSwitchTemp);
//
//  if(fastSwitch2.uniquePress())
//  {
//    fastSwitchTemp2=!fastSwitchTemp2;
//    
//  }
//  Serial.print("fastSwitch2:");
//    Serial.println(fastSwitchTemp2);
//  if(selSwitch.uniquePress())
//  {
//    selSwitchTemp=!selSwitchTemp;
//   
//  }
//   Serial.print("selSwitch:");
//    Serial.println(selSwitchTemp);
//
//  if(selSwitch2.uniquePress())
//  {
//    selSwitchTemp2=!selSwitchTemp2;
//
//  }
//      Serial.print("selSwitch2:");
//    Serial.println(selSwitchTemp2);


  if (state==NONE)
  {
  	digitalWrite(selLed,LOW);
  	digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

    analogWrite(roboteqCmd, 128);

  	if(selSwitch.uniquePress())
  		state=SELECTED;
    else if (selSwitch2.uniquePress())
      state=SELECTED2; 

    Serial.println("NONE");


  }

  else if (state==SELECTED)
  {
    digitalWrite(selLed,HIGH);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

  	analogWrite(roboteqCmd, map(analogRead(joystickPin), 0, 1023, 64, 192 ));//input is 10 bit, output is 8 bit

    if(fastSwitch.uniquePress())
      state=FAST;
    else if (selSwitch2.uniquePress())
      state=SELECTED2;
    Serial.println("SELECTED");
  }
  else if(state==FAST)
  {
    digitalWrite(selLed,HIGH);
    digitalWrite(fastLed,HIGH);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

    analogWrite(roboteqCmd, map(analogRead(joystickPin), 0, 1023, 0, 255 ));

    if(fastSwitch.uniquePress())
      state=SELECTED;
    else if (selSwitch2.uniquePress())
      state=SELECTED2;
    Serial.println("FAST");
  }
  else if(state==SELECTED2)
  {
    digitalWrite(selLed,LOW);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,HIGH);
    digitalWrite(fastLed2,LOW);

    analogWrite(roboteqCmd, map(analogRead(joystickPin2), 0, 1023, 192, 64 ));//reversed to account for side

    if(fastSwitch2.uniquePress())
      state=FAST2;
    else if (selSwitch.uniquePress())
      state=SELECTED;
    Serial.println("SELECTED2");
  }
  else if(state==FAST2)
  {
    digitalWrite(selLed,LOW);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,HIGH);
    digitalWrite(fastLed2,HIGH);

    analogWrite(roboteqCmd, map(analogRead(joystickPin2), 0, 1023, 255, 0 ));

    if(fastSwitch2.uniquePress())
      state=SELECTED2;
    else if (selSwitch.uniquePress())
      state=SELECTED;
    Serial.println("FAST2");
  }
  delay(1000);

}

//returns true if a new button press is detected
//holding the button does not toggle on/off

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  
  // if (Serial.available() > 0) 
           while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.print("This just in ... ");
    Serial.println(receivedChars);
                Serial.print("Int:");
    Serial.println(String(receivedChars).toInt());
                delay(100);
    newData = false;
  }
}
