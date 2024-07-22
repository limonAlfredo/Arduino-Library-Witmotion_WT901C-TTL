#include <HardwareSerial.h> // Keep this library
#include <Vibration.h>

// Serial1 Settings
#define BAUDIOS 9600 // Baudrate from sensor
#define RXPIN 4  // GPIO 4 => RX for Serial1
#define TXPIN 5  // GPIO 5 => TX for Serial1
// Serial1 Settings

// Instance
Vibration vibration(RXPIN, TXPIN, BAUDIOS);
// Instance

// Variables to store the data
float *pAcc, *pGyro, *pAngle, *pMagg;
// Variables to store the data


void setup() {
  // Initialize the Serial Comunication
  Serial.begin(115200);
  // Initialize the Serial Comunication
}

void loop() {

  // Update the sensor data
  vibration.getData();
  // Update the sensor data

  // Get the sensor data
  pAcc = vibration.getAcc();
  pGyro = vibration.getGyro();
  pAngle = vibration.getAngle();
  pMagg = vibration.getMagg();
  // Get the sensor data


  // Show the data on Serial Port
  Serial.print("acc:");
  for (int i = 0; i < 3; i++) {
    Serial.print(pAcc[i], 3);
    Serial.print(" ");
  }
  Serial.print("\r\n");

  Serial.print("gyro:");
  for (int i = 0; i < 3; i++) {
    Serial.print(pGyro[i], 3);
    Serial.print(" ");
  }
  Serial.print("\r\n");

  Serial.print("angle:");
  for (int i = 0; i < 3; i++) {
    Serial.print(pAngle[i], 3);
    Serial.print(" ");
  }
  Serial.print("\r\n");

  Serial.print("magg:");
  for (int i = 0; i < 3; i++) {
    Serial.print(pMagg[i], 3);
    Serial.print(" ");
  }
  Serial.print("\r\n");
  // Show the data on Serial Port

  delay(1000);
}
