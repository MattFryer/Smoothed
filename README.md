[![GitHub version](https://img.shields.io/github/release/MattFryer/Smoothed.svg)](https://github.com/MattFryer/Smoothed/releases/latest)
[![GitHub Release Date](https://img.shields.io/github/release-date/MattFryer/Smoothed.svg)](https://github.com/MattFryer/Smoothed/releases/latest)
[![GitHub download](https://img.shields.io/github/downloads/MattFryer/Smoothed/total.svg)](https://github.com/MattFryer/Smoothed/releases/latest)
[![GitHub stars](https://img.shields.io/github/stars/MattFryer/Smoothed.svg)](https://github.com/MattFryer/Smoothed/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/MattFryer/Smoothed.svg)](https://github.com/MattFryer/Smoothed/issues)
[![Codacy grade](https://img.shields.io/codacy/grade/d19ea847574d443a8433655ee1d17843.svg)](https://www.codacy.com/app/MattFryer/Smoothed)
[![GitHub license](https://img.shields.io/github/license/MattFryer/Smoothed.svg)](https://github.com/MattFryer/Smoothed/blob/master/LICENSE)

# Smoothed
An Arduino library to store and smooth sensor inputs using various methods including:
* a simple moving average of the last x sensor readings
*	a simple linear recursive exponential filter

Unlike many other smoothing/filtering libraries, Smoothed uses a template class to ensure sensor readings in any numerical data type can be handled.

## How to Install
For details on how to install libraries in the Arduino IDE, please see the [Arduino website](https://www.arduino.cc/en/Guide/Libraries).

## How to Use
A full example of using each smoothing method is provided with the library and can be found in the Arduino IDE under "File->Examples->Smoothed".

Firstly, you must include the library in your sketch:
```cpp
#include <Smoothed.h> 
```

Next, create an instance of the class defining what data type to use. The example below uses a type of float:
```cpp
Smoothed <float> mySensor;
```
You can replace float with any numeric data type to suit your sensor readings and desired accuracy. See the included library example for a full list of supported data types.

Within the setup function, initialize the instance, defining the smoothing method and accuracy:
```cpp
mySensor.begin(SMOOTHED_AVERAGE, 10);	
```
In the above example we are using a simple average of the last 10 sensor readings.

And finally, write in a new sensor value and read the smoothed result:
```cpp
// Read a sensor value from analogue pin 0
mySensor.add(analogRead(SENSOR_PIN));

// Output the smoothed sensor value to the serial
Serial.println(mySensor.get());
```

## Planned Improvements/Changes
1. Add a multi-sample method. Calls a passed function to obtain the sensor value x times and averages out.
2. Add a Savitzky Golay filter.
3. Add a running median filter. Best method to eliminate random spikes in an otherwise stable signal. Need to work out how to handle different data types. Rounding maybe??
4. Publishing to the Arduino IDE Library list.
