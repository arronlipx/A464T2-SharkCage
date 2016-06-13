const byte numChars = 32;
char receivedChars[numChars];  // an array to store the received data



//State Variables
const char UNSELECTED = 0;
const char SELECTED = 1;
const char FAST = 2;

//default state is unselected
char state=0;

boolean newData = false;
const int fastSwitch = 12;  //connect pin 12 to fast switch
const int selSwitch = 11;  	//connect pin 11 to select switch
const int fastLed = 10;		//connect pin 10 to fastLed Relay
const int selLed = 9;		//connect pin 9 to selectLed Relay
const int joystickPin = A0;	//connect pin A0 to joystick 
const int deactPin = 8;		//connect pin 8 to the select of the other box 


//joystick settings
const int joystickMid=512;


//debounce flags
boolean fastSwitchFlag=false;
boolean selSwitchFlag=false;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600); 
  pinMode(fastSwitch, INPUT);
  pinMode(selSwitch, INPUT);
  pinMode(fastLed, OUTPUT);
  pinMode(selLed, OUTPUT);
  pinMode(joystickPin, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:

  if (state==UNSELECTED)
  {
  	digitalWrite(selLed,LOW);
  	digitalWrite(fastLed,LOW);

  	if(readButton(selSwitch))
  		state=SELECTED;
  }

  else if (state==SELECTED)
  {
  	digitalWrite(selLed,HIGH);
  	digitalWrite(fastLed,LOW);

  	analogRead(joystickPin);
  }
  else if(state==FAST)
  {
  	digitalWrite(selLed,HIGH);
  	digitalWrite(fastLed,HIGH);
  }


}
void readDeact()
{

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
