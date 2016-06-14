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
const int fastSwitch = 12;  //connect pin 12 to fast switch
const int selSwitch = 11;  	//connect pin 11 to select switch
const int fastLed = 10;		//connect pin 10 to fastLed Relay
const int selLed = 9;		//connect pin 9 to selectLed Relay
const int joystickPin = A0;	//connect pin A0 to joystick 

//connect to other box

const int fastSwitch2 = 8;  //connect pin 8 to second fast switch
const int selSwitch2 = 7;   //connect pin 7 to second select switch
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
  pinMode(fastSwitch, INPUT_PULLUP);
  pinMode(selSwitch, INPUT_PULLUP);
  pinMode(fastLed, OUTPUT);0
  pinMode(selLed, OUTPUT);
  pinMode(joystickPin, INPUT);//analogue in

  pinMode(fastSwitch2, INPUT_PULLUP);
  pinMode(selSwitch2, INPUT_PULLUP);
  pinMode(fastLed2, OUTPUT);
  pinMode(selLed2, OUTPUT);
  pinMode(joystickPin2, INPUT);//analogue in

  pinMode(roboteqCmd, OUTPUT);//analoue out

}

void loop() {
  // put your main code here, to run repeatedly:
  fastSwitchTemp = readButton(fastSwitch);
  fastSwitchTemp2 = readButton(fastSwitch2);
  selSwitchTemp = readButton(selSwitch);
  selSwitchTemp2 = readButton(selSwitch2);

  if (state==NONE)
  {
  	digitalWrite(selLed,LOW);
  	digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

  	if(readButton(selSwitch))
  		state=SELECTED;
    else if (readButton()) 
  }

  else if (state==SELECTED)
  {
    digitalWrite(selLed,HIGH);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

  	analogWrite(roboteqCmd, map(analogRead(joystickPin), 0, 1023, 64, 192 ));
  }
  else if(state==FAST)
  {
    digitalWrite(selLed,HIGH);
    digitalWrite(fastLed,HIGH);
    digitalWrite(selLed2,LOW);
    digitalWrite(fastLed2,LOW);

    analogWrite(roboteqCmd, map(analogRead(joystickPin), 0, 1023, 0, 255 ));
  }
  else if(state==SELECTED2)
  {
    digitalWrite(selLed,LOW);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,HIGH);
    digitalWrite(fastLed2,LOW);

    analogWrite(roboteqCmd, map(analogRead(joystickPin2), 0, 1023, 64, 192 ));
  }
  else if(state==FAST2)
  {
    digitalWrite(selLed,LOW);
    digitalWrite(fastLed,LOW);
    digitalWrite(selLed2,HIGH);
    digitalWrite(fastLed2,HIGH);

    analogWrite(roboteqCmd, map(analogRead(joystickPin2), 0, 1023, 0, 255 ));
  }

}

//returns true if a new button press is detected
//holding the button does not toggle on/off
boolean readButton(int buttonPin)
{

	boolean currentState=digitalRead(buttonPin);
	if (currentState==HIGH)
	{
    if (buttonPin==fastSwitch)
    {
      if(fastSwitchFlag==true)
      {
        return false;
      }
      else
      {
        fastSwitchFlag=true;
        return true;
      }
    }
    if (buttonPin==selSwitch)
    {
      if(selSwitchFlag==true)
      {
        return false;
      }
      else
      {
        selSwitchFlag=true;
        return true;
      }
    }
    if (buttonPin==fastSwitch2)
    {
      if(fastSwitchFlag2==true)
      {
        return false;
      }
      else
      {
        fastSwitchFlag2=true;
        return true;
      }
    }
    if (buttonPin==selSwitch2)
    {
      if(selSwitchFlag2==true)
      {
        return false;
      }
      else
      {
        selSwitchFlag2=true;
        return true;
      }
    }
	}
	else
	{
		if (buttonPin==fastSwitch)
		{
			fastSwitchFlag=false;
			return false;
		}
		if (buttonPin==selSwitch)
		{
			selSwitchFlag=false;
			return false;
		}
    if (buttonPin==fastSwitch2)
    {
      fastSwitchFlag2=false;
      return false;
    }
    if (buttonPin==selSwitch2)
    {
      selSwitchFlag2=false;
      return false;
    }
	}

	// boolean currentState = LOW;//storage for current measured button state
	// boolean lastState = LOW;//storage for last measured button state
	// boolean debouncedState = LOW;//debounced button state

	// int debounceInterval = 20;//wait 20 ms for button pin to settle
	// unsigned long timeOfLastButtonEvent = 0;//store the last time the button state changed

	// currentState = digitalRead(buttonPin);
 //  	unsigned long currentTime = millis();
  
 //  if (currentState != lastState){
 //    timeOfLastButtonEvent = currentTime;
 //  }
  
 //  if (currentTime - timeOfLastButtonEvent > debounceInterval){//if enough time has passed
 //    if (currentState != debouncedState){//if the current state is still different than our last stored debounced state
 //      debouncedState = currentState;//update the debounced state
      
 //      //trigger an event
 //      if (debouncedState == HIGH){
 //        Serial.println("pressed");
 //      } else {
 //        Serial.println("released");
 //      }
 //    }
 //  }
  
 //  lastState = currentState;
}
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
