//CONFIG =====================================================================================
#define aref_voltage 3.3         // we tie 3.3V to ARef and measure it with a multimeter!

//TMP36 Pin Variables
int tempPin = 0;        // TMP36 Center lead to Analog Pin [A1-A7] (Elegoo Nano v.3)
int tempReading;        // the analog reading from the sensor

//Relay Pin Variable
int relayPin = 2;       // Relay Singnal lead to Digital Pin [D2-D12] (Elegoo Nano v.3)

//Tempurature Range
// Its good to provide a buffer for efficiency, if the temp bounces from 79-81 constantly
// it will turn on and off the fan constantly. So set a minimum temperature that the fan
// can cool the are too before it starts checking for max temperature.

float maxTemperature = 80.00; // The Max Temperature allowed
float minTemperature = 75.00; // The Min Temperature allowed

//=============================================================================================
void setup() {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
 
  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL); // Feed the 3.3v cable back into the AREF pin

  // Pin Setup/Register
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = getTemperature();
  if(temperature >= maxTemperature){
    powerOnRelay();
  } else if (temperature <= minTemperature) {
    powerOffRelay();
  }
  delay(1000); // Check tempertature every second

}

void powerOnRelay() {
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay On");
}

void powerOffRelay() {
    digitalWrite(relayPin, LOW);
    Serial.println("Relay Off");
}

float getTemperature(){
  tempReading = analogRead(tempPin);  
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0; 
  
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset to degrees ((volatge - 500mV) times 100)
  //Serial.print(temperatureC); Serial.println(" degrees C"); // For debuging purpouses
 
  // now convert to Fahrenheight
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");

  // Choose which tempurature you would like to use.
  return temperatureF; //Fahrenheight
  //return temperatureC; // Celcius
}

