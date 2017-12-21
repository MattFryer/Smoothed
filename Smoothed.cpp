/*
 *  Smoothed.cpp
 *  Store and calculate smoothed values from sensors.
 *  Created by Matt Fryer on 2017-11-17.
 *  Licensed under LGPL (free to modify and use as you wish)
 */

// Constructor
Smoothed::Smoothed () { // Constructor
  
}

// Destructor
Smoothed::~Smoothed () { // Destructor
  delete[] smoothReading;
}

// Inintialise the array for storing sensor values
bool Smoothed::begin (byte mode, byte smoothFactor = 10) { 
  smoothMode = mode;
  smoothReadingsFactor = smoothFactor; 
  
  switch (smoothMode) {  
    case SMOOTHED_AVERAGE : // SMOOTHED_AVERAGE
      
      smoothReading = new float[smoothReadingsFactor]; // Create the actual array of the required size
    
      // Initialise all the values in the array to zero
      for (int thisReading = 0; thisReading < smoothReadingsNum; thisReading++) {
        smoothReading[thisReading] = 0;
      }

      return true;
      break;
      
    case SMOOTHED_EXPONENTIAL : // SMOOTHED_EXPONENTIAL

      smoothReading = new float[1];
      smoothReading[0] = 0;
      
      return true;  
      break;

    default : 
      return false;
      break;
  }
  
}

// Add a value to the array
bool Smoothed::add (float newReading) {
  switch (smoothMode) {    
    case SMOOTHED_AVERAGE : // SMOOTHED_AVERAGE
    
      if(smoothReadingsNum < smoothReadingsFactor) { smoothReadingsNum++; } // Keep record of the number of readings being averaged. This will count up to the arrany saize then stay at that number
       
      smoothReading[smoothReadingsPosition] = newReading; // Add the new value
      
      if (smoothReadingsPosition == (smoothReadingsFactor - 1)) { // If at the end of the array
        smoothReadingsPosition = 0; // Increment to the beginning of the array
      } else {
        smoothReadingsPosition++; // Increment to next array position position
      }

      return true;
      break;

    case SMOOTHED_EXPONENTIAL : // SMOOTHED_EXPONENTIAL

      if( smoothReadingsNum == 0 ) {
        smoothReadingsNum++;
        smoothReading[0] = newReading;
      } else {
        smoothReading[0] = ((float)smoothReadingsFactor/100) * newReading + (1 - ((float)smoothReadingsFactor/100)) * smoothReading[0];
      }
      
      return true;
      break;
      
    default : 
      return false;
      break;
  }    
}

// Get the smoothed result
float Smoothed::get () {
  switch (smoothMode) {
    case SMOOTHED_AVERAGE : { // SMOOTHED_AVERAGE
      double runningTotal = 0;
    
      for (int x = 0; x < smoothReadingsNum; x++) {
        runningTotal += smoothReading[x];
      }
      
      return runningTotal / smoothReadingsNum;
    }
      break;

    case SMOOTHED_EXPONENTIAL : // SMOOTHED_EXPONENTIAL
      return smoothReading[0]; // Not sure why we have to return the first element of a single value array but we get a casting error if we don't
      break;

    default : 
      return false;
      break;
  }   
}

// Gets the last result stored
float Smoothed::getLast () {
  switch (smoothMode) {  
    case SMOOTHED_AVERAGE : // SMOOTHED_AVERAGE 
      // Just return the last reading
      if (smoothReadingsPosition = 0) {
        return smoothReading[smoothReadingsFactor-1]; 
      } else {
        return smoothReading[smoothReadingsPosition-1];
      }
      break;

    case 2 : // SMOOTHED_EXPONENTIAL
      return false; 
      break;

    default : 
      return false;
      break;
  }         
}

// Clears all stored values
bool Smoothed::clear () {
  switch (smoothMode) {    
    case SMOOTHED_AVERAGE : // SMOOTHED_AVERAGE    
      // Reset the counters
      smoothReadingsPosition = 0; 
      smoothReadingsNum = 0; 
      
      // Set all the values in the array to zero.  Not really needed
      for (int thisReading = 0; thisReading < smoothReadingsNum; thisReading++) {
        smoothReading[thisReading] = 0;
      }
      break;

    case SMOOTHED_EXPONENTIAL : // SMOOTHED_EXPONENTIAL
      smoothReadingsNum = 0;
	  smoothReading = 0;
      break;

    default : 
      return false;
      break;
  }         
}