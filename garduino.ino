//Timing
unsigned int hours, minutes, seconds;
unsigned int totalmins;
 
void setTime();


// Timing/> 

// Moisture
const int normal_moisture = ; // set value
int pinMoisture = 0;
int pinRelayWater = ; // set value
int moistureLevel  = 0;

bool plantWatered = false;

void checkMoisture();
// Light
const int normal_light_a; // set value
const int normal_light_b; // set value
int pinPhotoresistor = 1;
int pinRelayLight = 7;
int lightLevel = 0;

void checkLight();
// output Serial
String output;



 
void setup()
{
	// Testing purposes
	Serial.begin(9600);
	
	//
	pinMode(pinRelayLight, OUTPUT);
	pinMode(pinRelayWater, OUTPUT);
}
 
 
void loop()
{
	//timing
        setTime();
	//moisture
        if(!plantWatered && totalmins %30 == 0) checkMoisture();
	if(plantWatered && totalmins %31==0) plantWatered = false;
	//light
	if(totalmins%10==0) checkLight();

	

	//print output
	output = String(" Moisture level :  " + String(moistureLevel) + "; Light level: " + String(lightLevel) );
	Serial.println(output);
}
 
//timing
void setTime()
{
        unsigned long milli = millis();
 
        unsigned long totalsecs = milli/1000;
        seconds = (totalsecs %3600)%60 ;
        minutes = (totalsecs%3600)/60;
        hours = totalsecs/3600;
        totalmins = milli/60000;
}
 
//moisture
void checkMoisture()
{
        // get moisture
        // check whether ranges are right, if not, water the plant,
        // otherwise do nothing
	moistureLevel = analogRead(pinMoisture);
	if(moistureLevel < normal_moisture )
	{ // water the plant
		plantWatered = true;
	}
}

void checkLight()
{
	lightLevel = analogRead(pinPhotoresistor);
	if(lightLevel < normal_light_a)
		digitalWrite(pinRelayLight, HIGH);
	else if(lightLevel > normal_light_b)
		digitalWrite(pinRelayLight, LOW);
}
