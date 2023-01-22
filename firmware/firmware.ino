#pragma once
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <OSCMessage.h>
#include "./credentials.h"

unsigned int localPort = 8888;
unsigned int outPort = 9011;

int sendCount;
int count;
int lastEntry;
IPAddress outIp(192, 168, 178, 255);
WiFiUDP udp;


Adafruit_MPU6050 mpu;

void sendValues(float ax, float ay, float az, float gx, float gy, float gz) {
  OSCMessage msgA("/flamingo/accel");
  OSCMessage msgG("/flamingo/gyro");

  msgA.add(gx);
  msgA.add(gy);
  msgA.add(gz);

  udp.beginPacket(outIp, outPort);
  msgA.send(udp);
  udp.endPacket();
  msgA.empty();

  udp.beginPacket(outIp, outPort);
  msgG.send(udp);
  udp.endPacket();
  msgG.empty();
}

void printValues(float ax, float ay, float az, float gx, float gy, float gz) {
  Serial.print("Acceleration: ");
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.print(az);
  Serial.print(", ");
  Serial.print("Gyro: ");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.print(gz);
  Serial.println("");
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);


  Serial.println(SECRET_SSID);

  WiFi.begin(SECRET_SSID, SECRET_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Success! Connected, IP Address is ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  sendValues(a.acceleration.x, a.acceleration.y, a.acceleration.z, a.gyro.x, a.gyro.y, a.gyro.z);
  printValues(a.acceleration.x, a.acceleration.y, a.acceleration.z, a.gyro.x, a.gyro.y, a.gyro.z);

  delay(10);
}
