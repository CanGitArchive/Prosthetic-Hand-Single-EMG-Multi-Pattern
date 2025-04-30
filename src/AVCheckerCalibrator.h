  #include <Arduino.h>

  struct tenIntevalVoltageData 
  {
    float recordedVoltagePoints[10];
  };
  struct DefualtLimits 
  {
    float minValue;
    float maxValue;
    float averageValue;

    DefualtLimits() : minValue(1.45), maxValue(1.65), averageValue(1.55) {}
  };


class EMGMovementChecker 
{
    private:

      unsigned long wristPushTimer = 0.0;
      unsigned long wristPullTimer = 0.0;
      bool wristPulled = false;
      bool wristPushed = false;
      bool motorActive = false;

      int forwardSpinPin = 0;
      int backwardSpinPin = 0;
      int numberOfSamples = 0;

      

      float contractionTresholdModifier = 0.01;
      unsigned long previousMillis = 0; 
      unsigned long previousPrintMillis = 0;

      float liveArrayData[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      
      float rstArray[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
      

    public:
    float averageArray[10] = {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
    int emgPin = 32;
      EMGMovementChecker(int forwardPin, int backwardPin) 
      {
        forwardSpinPin = forwardPin;
        backwardSpinPin = backwardPin;
      }
/////////////////////////////////////////////////////gripSignalCalibrator///////////////////////////////////////////////////////////////////////////////
  tenIntevalVoltageData gripSignalCalibrator(int sampleInterval, int sampleDurationMilliseconds, float maxValueofEMG)
  {
    tenIntevalVoltageData dataPointArray;
    int numberOfSamples = sampleDurationMilliseconds / sampleInterval;
    float emgData[numberOfSamples];

    int i = 0;
      while (i < numberOfSamples)
      {
      emgData[i] = analogRead(emgPin) * (3.3 / 4095.0);
      delay(sampleInterval);
      i++;
      }

      // Calculate the step size for splitting the interval into 10 parts
    int stepSize = numberOfSamples / 10;

    // Record voltage data at each evenly spaced point
    int j = 0;
      while (j < 10)
      {
      int index = j * stepSize;
        switch (j)
        {
        case 0:
            dataPointArray.recordedVoltagePoints[0] = emgData[index];
            break;
        case 1:
            dataPointArray.recordedVoltagePoints[1] = emgData[index];
            break;
        case 2:
            dataPointArray.recordedVoltagePoints[2] = emgData[index];
            break;
        case 3:
            dataPointArray.recordedVoltagePoints[3] = emgData[index];
            break;
        case 4:
            dataPointArray.recordedVoltagePoints[4] = emgData[index];
            break;
        case 5:
            dataPointArray.recordedVoltagePoints[5] = emgData[index];
            break;
        case 6:
            dataPointArray.recordedVoltagePoints[6] = emgData[index];
            break;
        case 7:
            dataPointArray.recordedVoltagePoints[7] = emgData[index];
            break;
        case 8:
            dataPointArray.recordedVoltagePoints[8] = emgData[index];
            break;
        case 9:
            dataPointArray.recordedVoltagePoints[9] = emgData[index];
            break;
        }
      j++;
      }

      return dataPointArray;
  }
/////////////////////////////////////////////////////UnGripSignalCalibrator/////////////////////////////////////////////////////////////////////////////////////
  tenIntevalVoltageData UnGripSignalCalibrator(int sampleInterval, int sampleDurationMilliseconds, float maxValueofEMG)
  {
    tenIntevalVoltageData dataPointArrayUnGrip;
    int numberOfSamples = sampleDurationMilliseconds / sampleInterval;
    float emgData[numberOfSamples];

    int i = 0;
      while (i < numberOfSamples)
      {
          emgData[i] = analogRead(emgPin) * (3.3 / 4095.0);
          delay(sampleInterval);
          i++;
        }

    int stepSize = numberOfSamples / 10;

    // Record voltage data at each evenly spaced point
    int j = 0;
      while (j < 10)
      {
          int index = j * stepSize;
          switch (j)
          {
          case 0:
              dataPointArrayUnGrip.recordedVoltagePoints[0] = emgData[index];
              break;
          case 1:
              dataPointArrayUnGrip.recordedVoltagePoints[1] = emgData[index];
              break;
          case 2:
              dataPointArrayUnGrip.recordedVoltagePoints[2] = emgData[index];
              break;
          case 3:
              dataPointArrayUnGrip.recordedVoltagePoints[3] = emgData[index];
              break;
          case 4:
              dataPointArrayUnGrip.recordedVoltagePoints[4] = emgData[index];
              break;
          case 5:
              dataPointArrayUnGrip.recordedVoltagePoints[5] = emgData[index];
              break;
          case 6:
              dataPointArrayUnGrip.recordedVoltagePoints[6] = emgData[index];
              break;
          case 7:
              dataPointArrayUnGrip.recordedVoltagePoints[7] = emgData[index];
              break;
          case 8:
              dataPointArrayUnGrip.recordedVoltagePoints[8] = emgData[index];
              break;
          case 9:
              dataPointArrayUnGrip.recordedVoltagePoints[9] = emgData[index];
              break;
          }
          j++;
      }
    return dataPointArrayUnGrip;
  }
/////////////////////////////////////////////////////getDefaultValues///////////////////////////////////////////////////////////////////////////////////
  DefualtLimits getDefaultValues(int sampleInterval, int sampleDurationMilliseconds)
  {
    DefualtLimits data;
    int numberOfSamples = (int)(sampleDurationMilliseconds / sampleInterval);
    float emgData[numberOfSamples];
    

    float minValue = 5.0; 
    float maxValue = 0.0;
    float sum = 0.0;            

     int i = 0;
      while (i < numberOfSamples) 
      {
      emgData[i] = analogRead(emgPin) * (3.3 / 4095.0);
      delay(sampleInterval);

        if (emgData[i] < minValue) 
        {
            minValue = emgData[i];
        }
        if (emgData[i] > maxValue) 
        {
            maxValue = emgData[i];
        }
      sum += emgData[i];
      i++;
      }
      
    float averageValue = (float)sum / numberOfSamples;

    data.minValue = minValue;
    data.maxValue = maxValue;
    data.averageValue = averageValue;

    return data;
  }
/////////////////////////////////////////////////////liveEMGArrayUpdate///////////////////////////////////////////////////////////////////////////////////
  void liveArrayUpdate(int totalMillisPassing, int totalDelayGiven)
  {
    unsigned long currentMillis = millis();
    float totalArraySample = totalMillisPassing/totalDelayGiven;
  
    if (currentMillis - previousMillis >= totalArraySample) 
    {
        for (int i = 0; i < 9; i++) 
        {
          liveArrayData[i] = liveArrayData[i + 1];
        }
      liveArrayData[9] = analogRead(emgPin) * (3.3 / 4095.0);
      previousMillis = currentMillis;
    }
  }
/////////////////////////////////////////////////////printLiveArrayData///////////////////////////////////////////////////////////////////////////////////      
  void printLiveArrayData(unsigned int printInterval)
  {
    unsigned long currentPrintMillis = millis();

    if (currentPrintMillis - previousPrintMillis >= printInterval) 
    {
      Serial.println("Array data:");
        for (int i = 0; i < 10; i++) 
        {
          Serial.print("Index ");
          Serial.print(i);
          Serial.print(": ");
          
          Serial.println(liveArrayData[i]);
          previousPrintMillis = currentPrintMillis;
        }
    }
  }
/////////////////////////////////////////////////////getLiveArrayData///////////////////////////////////////////////////////////////////////////////////
  float* getLiveArrayData() 
  {
    return liveArrayData;
  }
  void resetLiveArrayDataZero()
  {
    for (int i = 0; i < 10; i++) 
    {
      liveArrayData[i] = rstArray[i]; 
    }
  }
  void resetLiveArrayDataAvrg()
  {
    for (int i = 0; i < 10; i++) 
    {
      liveArrayData[i] = averageArray[i]; 
    }
  }
  void setAvrgArray(float avrgNum)
  {
    for (int i = 0; i < 10; i++) 
    {
      averageArray[i] = avrgNum;
    }
  }
};