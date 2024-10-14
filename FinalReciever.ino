#include <printf.h>
#include<stdbool.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "10001";

int noPressure = 5;
int lightPressure = 100;
int mediumPressure = 1000;

struct DataPack{
  int pressureReading;
  float h;
  float t;
  bool flag;
  int out;
  float ppm;
}MyData;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  
  if (radio.available()) {
    
    radio.read(&MyData, sizeof(MyData));

    Serial.println("-------------------------------------------");
    
    //Pressure Sensor Recieved 
    Serial.print("Pressure Readings : ");
    Serial.println(MyData.pressureReading);
    
    if (MyData.pressureReading < noPressure) {
      Serial.println(" - No Force Exerted");
    } else if (MyData.pressureReading < lightPressure) {
      Serial.println(" - Force Exerted is Normal");
    } else if (MyData.pressureReading < mediumPressure) {
      Serial.println(" - Medium Force Exerted");
    } else{
      Serial.println(" - High Force is being Exerted");
    }

    //Humidity and Temperature \

    Serial.print("Humidity: ");
    Serial.print(MyData.h);
    Serial.print("% || Temperature: ");
    Serial.print(MyData.t);
    Serial.print("°C ");
    Serial.println();

    //IR SENSOR

    if (MyData.flag == true){
      Serial.println("Helmet is Being Weared ! ");
    }
    if (MyData.flag == false){
      Serial.println("Helmet has been Removed ! ");
    }

    //MQ135 Sensor
    
    Serial.print("CO2 ppm value : ");
    Serial.println(MyData.ppm);
  
    if (MyData.ppm <= 150){
      Serial.println("Normal air");
    }
    if ((MyData.ppm <= 700)&&(MyData.ppm >= 150)){
      Serial.println("Alcohol Detected ! ");
    }
    if (MyData.ppm >= 700){
      Serial.println("Lighter gas Detected");
    }
    
    Serial.println("");
    
    //MQ 7 Sensor

    Serial.print("CO PPM = ");
    Serial.println(MyData.out);
    Serial.println("-------------------------------------------");

    delay(5000);
  }

}
