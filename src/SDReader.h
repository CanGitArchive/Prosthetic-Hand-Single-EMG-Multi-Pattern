#include <SD.h>

class SDCard {
  public:
    SDCard();
    ~SDCard();
    float* readTheDataFromSDCardIntoDataInTheFile();
    void writeDataOnSpecificRangeIncluded(int lowerRange, int higherRange);
    float* stitchFloatArrays(float minStitch, float maxStitch, float avrgStitch, float* gripArray, float gripValue, float* unGripArray, float unGripValue, float* defaultAvgArray, float staticValue);
    void splitFloatArray(float* finalArray);

    File dataFile;
    int chipSelect = 5; // SD card CS pin SS pin
    bool onlyOnce = true;
    float dataInArduino[36];
    float dataInTheFile[36];

    float minS = 1.0;
    float maxS = 2.0;
    float avrgS = 3.0;
    float gripArrayV[10] = {4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0};
    float gripV = 14.0;
    float unGripArrayV[10] = {15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0};
    float unGripV = 25.0;
    float defaultAvgArray[10] = {26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0};
    float staticValue = 36.0;

  private: 
};

SDCard::SDCard() 
{
  // Constructor
}

SDCard::~SDCard() 
{
  // Destructor
}

float* SDCard::readTheDataFromSDCardIntoDataInTheFile() 
{
  dataFile = SD.open("/data.txt");//READ MODE
    if (dataFile) 
    {
      // Read and print each line of the file
      int i = 0;
        while (dataFile.available()) 
        {
          String line = dataFile.readStringUntil('\n');
          dataInTheFile[i] = line.toFloat();
          i++;
        }
      dataFile.close();
    } 
  return dataInTheFile;
}

void SDCard::writeDataOnSpecificRangeIncluded(int lowerRange, int higherRange) // 0 to 36
{


  const char* MY_FILE_WRITE_MODE = "w"; // Define the file write mode as a string

  dataFile = SD.open("/data.txt", MY_FILE_WRITE_MODE);
    if (dataFile) 
    {
      int i = 0;
        while (i < 36) 
        {
          if (i >= lowerRange && i <= higherRange) 
          {
            dataFile.println(dataInArduino[i]); // Write random data in the specified range
          } 
          else 
          {
            dataFile.println(dataInTheFile[i]); // Write existing data
          }
        i++;
        }
      dataFile.close();
    } 
}

float* SDCard::stitchFloatArrays(float minStitch, float maxStitch, float avrgStitch, float* gripArray, float gripValue, float* unGripArray, float unGripValue, float* defaultAvgArray, float staticValue) 
{
  float* finalArray = new float[36]; // Dynamic allocation to ensure memory persists after the function returns

  // Stitch the float variables and arrays together
  int index = 0;

  // Float variables
  finalArray[index] = minStitch;//0
  index++;
  finalArray[index] = maxStitch;//1
  index++;
  finalArray[index] = avrgStitch;//2
  index++;

  // Float arrays
  int i = 0;
    while (i < 10) 
    {
      finalArray[index] = gripArray[i];//3 ->12
      index++;
      i++;
    }

  finalArray[index] = gripValue;//13
  index++;

  i = 0;
    while (i < 10) 
    {
      finalArray[index] = unGripArray[i];//14 ->23
      index++;
      i++;
    }

  finalArray[index] = unGripValue;//24
  index++;

  i = 0;
    while (i < 10) 
    {
      finalArray[index] = defaultAvgArray[i];//25 -> 34
      index++;
      i++;
    }

    finalArray[index] = staticValue;

    i = 0;
    while (i < 36) 
    {
      dataInArduino[i] = finalArray[i];
      i++;
    }

  // Return a pointer to the final array
  return finalArray;
}

void SDCard::splitFloatArray(float* finalArray) 
{
  float minStitch = finalArray[0];
  float maxStitch = finalArray[1];
  float avrgStitch = finalArray[2];

  // Float arrays
  float gripArray[10];
  for (int i = 0; i < 10; ++i) {
    gripArray[i] = finalArray[i + 3];
  }

  float gripValue = finalArray[13];

  float unGripArray[10];
  for (int i = 0; i < 10; ++i) {
    unGripArray[i] = finalArray[i + 14];
  }

  float unGripValue = finalArray[24];

  float avgArraying[10];
  for (int i = 0; i < 10; ++i) {
    avgArraying[i] = finalArray[i + 25];
  }

  float staticData = finalArray[35];

  // Print the extracted values
  //////////////////////////////////////////////////////////min/max/avrg
  minS = minStitch;
  maxS = maxStitch;
  avrgS = avrgStitch;
  //////////////////////////////////////////////////////////GRIP ARRAY
    for (int i = 0; i < 10; ++i) 
    {
      gripArrayV[i]=gripArray[i];
    }
  //////////////////////////////////////////////////////////gripValue
  gripV = gripValue;
  //////////////////////////////////////////////////////////UNGRIP ARRAY
    for (int i = 0; i < 10; ++i) 
    {
      unGripArrayV[i] = unGripArray[i];
    }
  //////////////////////////////////////////////////////////unGripValue
  unGripV = unGripValue; 
  //////////////////////////////////////////////////////////UNGRIP ARRAY
  for (int i = 0; i < 10; ++i) 
  {
    defaultAvgArray[i] = avgArraying[i];
  }
  /////////////////////////////////////////////////////////static
  staticValue = staticData;
}
