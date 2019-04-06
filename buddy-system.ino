// Wave to the Deakin Photon Buddy
// Used the getting started make motion detector to create a "waver"

int led = D6;
int boardLed = D7;
int waveLed = D5;
int patLed = D3;
int photosensor = A0;
int power = A5;

int intactValue;
int brokenValue;
int beamThreshold;

bool beamBroken = false;

void myHandler(const char *event, const char *data); // Declare function

void setup() {
	// Initialise Outputs
	pinMode(led, OUTPUT); 
	pinMode(boardLed, OUTPUT); 
	pinMode(power, OUTPUT); 
	pinMode(waveLed, OUTPUT);
	pinMode(patLed, OUTPUT);

	// Subscribe to the buddy event, listen for when they publish
	Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler);

	// Set Power to the Photosensor
	digitalWrite(power,HIGH);

	// Calibration
	// First, the D7 LED will go on to tell you to put your hand in front of the beam.
	digitalWrite(boardLed,HIGH);
	delay(2000);

	// Then, the D7 LED will go off and the LED will turn on.
	digitalWrite(boardLed,LOW);
	digitalWrite(led,HIGH);
	delay(500);

	// Now we'll take some readings...
	int off_1 = analogRead(photosensor); // read photosensor
	delay(200); // wait 200 milliseconds
	int off_2 = analogRead(photosensor); // read photosensor
	delay(1000); // wait 1 second

	// Now flash to let us know that you've taken the readings...
	digitalWrite(boardLed,HIGH);
	delay(100);
	digitalWrite(boardLed,LOW);
	delay(100);
	digitalWrite(boardLed,HIGH);
	delay(100);
	digitalWrite(boardLed,LOW);
	delay(100);

	// Now the D7 LED will go on to tell you to remove your hand...
	digitalWrite(boardLed,HIGH);
	delay(2000);

	// The D7 LED will turn off...
	digitalWrite(boardLed,LOW);

	// ...And we will take two more readings.
	int on_1 = analogRead(photosensor); // read photosensor
	delay(200); // wait 200 milliseconds
	int on_2 = analogRead(photosensor); // read photosensor
	delay(300); // wait 300 milliseconds

	// Now flash the D7 LED on and off three times to let us know that we're ready to go!
	digitalWrite(boardLed,HIGH);
	delay(100);
	digitalWrite(boardLed,LOW);
	delay(100);
	digitalWrite(boardLed,HIGH);
	delay(100);
	digitalWrite(boardLed,LOW);
	delay(100);
	digitalWrite(boardLed,HIGH);
	delay(100);
	digitalWrite(boardLed,LOW);

	intactValue = (on_1+on_2)/2;
	brokenValue = (off_1+off_2)/2;
	beamThreshold = (intactValue+brokenValue)/2.005;

}


void loop() {
    
	if (analogRead(photosensor) < beamThreshold) 
	{
			Particle.publish("Death_Adder_Photon_Buddy", "wave", PUBLIC);
			delay(200);
			send_wave();
			digitalWrite(led,LOW);
			delay(60000); // hold 1 min to see if a wave comes in, before sending another wave
			beamBroken = false;
		    digitalWrite(led,HIGH);
	}

	else 
    {
		    // Do nothing
	}
}

void myHandler(const char *event, const char *data)
{
	if (strcmp(data,"wave") == 0) 
	{   // if your buddy sends a wave, then blink the red LED 3 times to reckonise the wave
		digitalWrite(waveLed,HIGH);
		delay(250);
		digitalWrite(waveLed,LOW);
		delay(250);
		digitalWrite(waveLed,HIGH);
		delay(250);
		digitalWrite(waveLed,LOW);
		delay(250);
		digitalWrite(waveLed,HIGH);
		delay(250);
		digitalWrite(waveLed,LOW);
		delay(250);
	}
	if (strcmp(data,"pat") == 0) 
	{   // if your buddy sends a wave, then blink the red LED 3 times to reckonise the wave
		digitalWrite(waveLed,HIGH);
		delay(250);
		digitalWrite(patLed,HIGH);
		digitalWrite(waveLed,LOW);
		delay(250);
		digitalWrite(waveLed,HIGH);
		digitalWrite(patLed,LOW);
		delay(250);
		digitalWrite(patLed,HIGH);
		digitalWrite(waveLed,LOW);
		delay(250);
		digitalWrite(waveLed,HIGH);
		digitalWrite(patLed,LOW);
		delay(250);
		digitalWrite(waveLed,LOW);
		delay(250);
	}
	else 
	{
		// Do nothing
	}
}

void send_wave()
{
    digitalWrite(boardLed, LOW);
    delay(200);
    digitalWrite(boardLed, HIGH);
    delay(200);
    digitalWrite(boardLed, LOW);
    delay(200);
}