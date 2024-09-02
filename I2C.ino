#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address
int16_t GyroZ;
float yaw = 0;
unsigned long lastTime = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    
  Wire.endTransmission(true);
  
  Wire.beginTransmission(MPU);
  Wire.write(0x1B); // GYRO_CONFIG register
  Wire.write(0x00); 
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Starting with register 0x43 (GYRO_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true);
  
  int16_t GyroX = Wire.read() << 8 | Wire.read();
  int16_t GyroY = Wire.read() << 8 | Wire.read();
  GyroZ = Wire.read() << 8 | Wire.read();
  
  unsigned long currentTime = millis();
  float elapsedTime = (currentTime - lastTime) / 1000.0; 
  lastTime = currentTime;
  
  yaw += (GyroZ / 131.0) * elapsedTime; /
  
  Serial.print("Yaw: ");
  Serial.println(yaw);
  
  delay(100);
}
