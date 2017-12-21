/*
 *  Smoothed.h
 *  Store and calculate smoothed values from sensors.
 *  Created by Matt Fryer on 2017-11-17.
 *  Licensed under LGPL (free to modify and use as you wish)
 */

#pragma once

#define SMOOTHED_AVERAGE 1
#define SMOOTHED_EXPONENTIAL 2

// A class used to store and calculate the values to be smoothed.
class Smoothed {
  private:
    byte smoothMode;
    byte smoothReadingsFactor = 10; // The smoothing factor. In avergare mode, this is the number of readings to average. 
    byte smoothReadingsPosition = 0; // Current position in the array
    byte smoothReadingsNum = 0; // Number of readings currently being averaged
    float *smoothReading; // Array of readings
  public:
    Smoothed();
    ~Smoothed(); // Destructor to clean up when class instance killed
    bool begin (byte smoothMode, byte smoothFactor);
    bool add (float newReading);
    float get ();
    float getLast ();
    bool clear ();
};