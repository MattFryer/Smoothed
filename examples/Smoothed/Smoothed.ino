/*
 Sensor Input Smoothing
 Demonstrates smoothing of a sensor input via various methods.


 Created by Matthew Fryer

 This example code is in the public domain.

 */

#include <Smoothed.h> 	// Include the library
 
#define SENSOR_PIN A0    // The input pin for the sensor. In this example we are reading from an Arduino analogue pin. 
// If you don't have a sensor you can still see the effect if the analogue pin is left floating its value will vary wildly.

// Create two instances of the class to use. 
Smoothed <float> mySensor; 
Smoothed <float> mySensor2;

/* We are using a template class that can be used with any numeric data type. 
   You can therefore replace <float> above with any other data type to suit your sensor readings and desired accuracy. 
   All of the below are valid examples:
		Smoothed <byte> mySensor;
		Smoothed <int> mySensor;
		Smoothed <unsigned int> mySensor;
		Smoothed <long> mySensor;
		Smoothed <unsigned long> mySensor;
		Smoothed <short> mySensor;	
		Smoothed <float> mySensor;
		Smoothed <double> mySensor;
*/

void setup() {
	Serial.begin(9600);

	// Initialise the first sensor value store. We want this to be the simple average of the last 10 values.
	// Note: The more values you store, the more memory will be used.
	mySensor.begin(SMOOTHED_AVERAGE, 10);	

	// Initialise the second sensor value store. We want this one to be a simple linear recursive exponential filter. 
	// We set the filter level to 10. Higher numbers will result in less filtering/smoothing. Lower number result in more filtering/smoothing
	mySensor2.begin(SMOOTHED_EXPONENTIAL, 10);
	
	/* Both parameters are optional and so both of the following are valid:
			mySensor.begin();
			mySensor.begin(SMOOTHED_AVERAGE);
			
	   The default parameters are SMOOTHED_EXPONENTIAL and 10.
	*/

    // Although it is unnecessary here, the stored values can be cleared if needed.
    mySensor.clear();
}

void loop() {
    // Read the value from the sensor
    float currentSensorValue = analogRead(SENSOR_PIN);
    
    // Add the new value to both sensor value stores
    mySensor.add(currentSensorValue);
    mySensor2.add(currentSensorValue);
    
    // Get the smoothed values
    float smoothedSensorValueAvg = mySensor.get();
    float smoothedSensorValueExp = mySensor2.get();
    
    // Output the smoothed values to the serial stream. Open the Arduino IDE Serial plotter to see the effects of the smoothing methods.
    Serial.print(currentSensorValue); Serial.print("\t"); Serial.print(smoothedSensorValueAvg); Serial.print("\t"); Serial.println(smoothedSensorValueExp);
	
    
    // If needed we can also return the last stored value which will be unsmoothed
    float lastValueStoredAvg = mySensor.getLast();
    float lastValueStoredExp = mySensor2.getLast();	

    delay(100);
}
