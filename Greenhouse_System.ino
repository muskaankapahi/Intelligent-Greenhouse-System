#include<DHT.h>

#include<SoftwareSerial.h>

SoftwareSerial bt(0,1);


#define DHTPIN 2     // what pin we're connected to

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
                     

#define RELAY1  7      
#define RELAY2  6    
#define RELAY3  8
int sensorValue = 0;
int percent = 0;         
int m=0, temp=0;
int LDRstatus = 0;     
void setup()
{    
Serial.begin(9600);
bt.begin(9600);
dht.begin();
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(A0, INPUT); // Moisture Sensor Pin
  pinMode(A1, INPUT); //Temperature Sensor Pin
  pinMode(A2, INPUT); //Light Sensor Pin
  pinMode(13, OUTPUT);
}

  void loop()
{
  m=analogRead(A1);
  int k = (m*500)/1023;
  temp= k+40;
  LDRstatus = analogRead(A2);
  light(LDRstatus);
  sensorValue = analogRead(A0);
  percent = convertToPercent(sensorValue);
  printValueToSerial();
  delay(3000);
  Serial.println("\nThe temperature measured by DHT 11 is");

float t;
t= dht.readTemperature();

int tem= (int) t;

Serial.println(t);

Serial.println("The humidity measured by DHT 11  is");

float h= dht.readHumidity();
int hum= (int) h;
Serial.println(h);
  if ( percent<30 )
  {
      digitalWrite(RELAY1,0);        
      delay(1000);
      Serial.println("\nPlant is being watered");
      digitalWrite(RELAY1, 1);
      delay(2000);
  }
  if (temp>29)
  {
    digitalWrite(RELAY2, 0);
    delay(1000);
    Serial.println("\n Plant's environment is being cooled down");
   digitalWrite(RELAY2,1);
   delay(2000);
  }
}


  int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
}

void printValueToSerial()
{
  Serial.print("\n\nAnalog Moisture Value of the soil: ");
  Serial.print(sensorValue);
  Serial.print("\nPercent Moisture Value of the soil: ");
  Serial.print(percent);
  Serial.print("%");
  Serial.println("\nTemperature of the Environment: ");
  Serial.print(temp);
  Serial.println("\n Light received by the plant: ");
  Serial.print(LDRstatus);
}
void light(int LDR)
{
  if (LDR > 60)
  {
    digitalWrite(RELAY3,1);
    Serial.println("\n The plant is receiving light naturally");
    delay(4000);
  }
  else
  {
    digitalWrite(RELAY3,0);
    Serial.println("\n The plant is receiving light artificially");
    delay(2000);
  }
  
  }
