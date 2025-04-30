  #include <Arduino.h>

  
class MotorMovementFromPattern 
{
  private:
    int forwardSpinPin = 0;
    int backwardSpinPin = 0;
    
    

    unsigned long motorActivity = millis();
    unsigned long cooldownTimer = 0.0;
    


  public:
    bool resetTheLiveDTW = false;
    bool motorActiveGrip = false;
    bool motorActiveUnGrip = false;
    int millisMovementTimer = 250;
    unsigned long cooldown = 2000;
    MotorMovementFromPattern(int forwardPin, int backwardPin) 
    {
      forwardSpinPin = forwardPin;
      backwardSpinPin = backwardPin;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float dtw_distance(float array1[], float array2[], int arraySize) 
  {
    float dtw_matrix[arraySize + 1][arraySize + 1];

    // Initialize the matrix with large values
    for (int i = 0; i <= arraySize; i++) 
    {
      for (int j = 0; j <= arraySize; j++) 
      {
        dtw_matrix[i][j] = INFINITY;
      }
    }

    // Set the starting point to 0
    dtw_matrix[0][0] = 0;

    // Calculate accumulated distances
      for (int i = 1; i <= arraySize; i++) 
      {
        for (int j = 1; j <= arraySize; j++) 
        {
          float cost = distance(array1[i-1], array2[j-1]);
          dtw_matrix[i][j] = cost + min(dtw_matrix[i-1][j], min(dtw_matrix[i][j-1], dtw_matrix[i-1][j-1]));    
        }
      }

    // DTW distance is the value in the bottom-right cell of the calculated matrix
    return dtw_matrix[arraySize][arraySize];
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float distance(float x, float y) 
  {
    return sqrt(pow((x - y), 2));
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  double euclideanDistance(float data1[], float data2[], int size) 
  {
    double sum = 0.0;
      for (int i = 0; i < size; i++) 
      {
        double diff = data1[i] - data2[i];
        sum += diff * diff;
      }

    return sqrt(sum);
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void gripperListener(float DTWLive, float DTWGripValue, float sensitivity, int motorPWM)
  {
    float flactuation = (DTWGripValue*0.2);
    float bottomTolerance = DTWGripValue - flactuation;
    float topTolerance = DTWGripValue + flactuation;

    if(motorActiveGrip == false && motorActiveUnGrip == false && (millis()-cooldownTimer) >= cooldown)
    { 

      analogWrite(backwardSpinPin, 0);
      analogWrite(forwardSpinPin, 0);

      analogWrite(backwardSpinPin, 0);
      analogWrite(forwardSpinPin, motorPWM);
      motorActiveGrip = true;

      motorActivity = millis();
      cooldownTimer = millis();
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void unGripperListener(float DTWLive, float DTWUnGripValue, float sensitivity, int motorPWM)
  {
    float flactuation = (DTWUnGripValue*0.2);
    float bottomTolerance = DTWUnGripValue - flactuation;
    float topTolerance = DTWUnGripValue + flactuation;

    if(motorActiveGrip == false && motorActiveUnGrip == false && (millis()-cooldownTimer) >= cooldown)
    { 

      analogWrite(backwardSpinPin, 0);
      analogWrite(forwardSpinPin, 0);

      analogWrite(backwardSpinPin, motorPWM);
      analogWrite(forwardSpinPin, 0);
      motorActiveGrip = true;

      motorActivity = millis();
      cooldownTimer = millis();
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void gripperMotorController()
  {
    if( (millis()-motorActivity) >= millisMovementTimer && motorActiveGrip == true  && motorActiveUnGrip == false)
    {
      analogWrite(backwardSpinPin, 0);
      analogWrite(forwardSpinPin, 0);
      resetTheLiveDTW = true;
      motorActiveGrip = false;
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void unGripperMotorController()
  {
    if( (millis()-motorActivity) >= millisMovementTimer && motorActiveGrip == false  && motorActiveUnGrip == true)
    {
      analogWrite(backwardSpinPin, 0);
      analogWrite(forwardSpinPin, 0);
      resetTheLiveDTW = true;
      motorActiveUnGrip = false;
    }
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool getMotorActivityGripping()
  {
    return motorActiveGrip;
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool getMotorActivityUnGripping()
  {
    return motorActiveUnGrip;
  }
};