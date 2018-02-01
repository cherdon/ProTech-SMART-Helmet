const int redPin = 4;
const int bluePin = 3;
const int FSR_PIN1 = A0;// Pin connected to FSR/resistor divider
const int FSR_PIN2 = A1;// Pin connected to FSR/resistor divider

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor
  int counts = 0;
  int countm = 0;
  int counth = 0;
  int previousState = 0;
  int currentState = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(FSR_PIN1, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() 
{
  int fsrADC1 = analogRead(FSR_PIN1);
  int fsrADC2 = analogRead(FSR_PIN2);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
   (fsrADC1 != 0); // If the analog reading is non-zero
   (fsrADC2 != 0);

  {
    // Use ADC reading to calculate voltage:
    float fsrV1 = fsrADC1 * VCC / 1023.0;
    float fsrV2 = fsrADC2 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR1 = R_DIV * (VCC / fsrV1 - 1.0);
    float fsrR2 = R_DIV * (VCC / fsrV2 - 1.0);
    Serial.println("Resistance: " + String(fsrR1) + " ohms");
    Serial.println("Resistance: " + String(fsrR2) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    
    float force1;
    float force2;
    float fsrG1 = 1.0 / fsrR1; // Calculate conductance
    float fsrG2 = 1.0 / fsrR2;
    // Break parabolic curve down into two linear slopes:
    {
    if (fsrR1 <= 600) 
      force1 = (fsrG1 - 0.00075) / 0.00000032639;
    else
      force1 =  fsrG1 / 0.000000642857;
    }
    {
    if (fsrR2 <= 600)
      force2 = (fsrG2 - 0.00075) / 0.00000032639;
    else
      force2 = fsrG2 / 0.000000642857;
    }
    Serial.println("Force1: " + String(force1) + " g");
    Serial.println("Force2: " + String(force2) + " g");
    {
      if (force1 < 300 || force2 < 3) 
      {
        analogWrite(redPin,200);
        analogWrite(bluePin,0);
        currentState = 1;
      }
      else if (force1 >= 300 && force2 >= 3)
      {
        analogWrite(redPin,0);
        analogWrite(bluePin,200);
        currentState = 0;
      }
      }

      {
        if (currentState != previousState) {
          if (currentState == 1) {
            counts++;
          if (counts >= 60){
           counts = 0;
           countm++; 
          }
          }
        }
        }
        }
    Serial.println(String(countm)+ "m " + String(counts)+ "s ");
    Serial.println();

    delay(500);
  }

