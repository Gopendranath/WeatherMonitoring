#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h> //changes

#define BAND 433E6
#define rain_sensor A0
#define ir_sensor A1
#define DHTPIN 3
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

char device_id[12] = "MyDevice123";

LiquidCrystal_I2C lcd(0x27, 16, 4); //changes
Adafruit_BMP280 bmp; // I2C
#define BMP280_ADDRESS 0x76

void setup() {
  Serial.begin(115200);
  pinMode(rain_sensor, INPUT);
  pinMode(ir_sensor, INPUT);
  dht.begin();
  lcd.init(); //changes
  lcd.backlight();
  while (!Serial);

  Serial.println(F("LoRa Sender")); //changes

  // Check for BMP280 sensor
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println(F("Could not find a valid BMP280 sensor!"));
    while (1);
  }

  // Configure BMP280 settings (optional, adjust as needed)
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);

  if (!LoRa.begin(BAND)) {
    Serial.println(F("Starting LoRa failed!"));
    while (1);
  }
}

void loop() {
  int rainfall = map(analogRead(rain_sensor), 780, 0, 0, 100);
  if (rainfall >= 100) {
    rainfall = 100;
  }
  if (rainfall <= 0) {
    rainfall = 0;
  }

  int irValue = analogRead(ir_sensor);

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read data from BMP280 sensor
  float bmp_temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float altitude = bmp.readAltitude(1013.25); // Adjust pressure for altitude calculation

  Serial.print(F("Device ID: "));
  Serial.println(device_id);

  Serial.print(F("Rainfall = "));
  Serial.print(rainfall);
  Serial.println(F("%"));

  Serial.print(F("LDR Sensor Value = "));
  Serial.println(irValue);

  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(F("°C (DHT)"));

  Serial.print(F("BMP280 Temperature = "));
  Serial.print(bmp_temperature);
  Serial.println(F("°C"));

  Serial.print(F("Pressure = "));
  Serial.print(pressure);
  Serial.println(F(" Pa"));

  Serial.print(F("Approx altitude = "));
  Serial.print(altitude);
  Serial.println(F(" m"));

  Serial.print(F("Humidity = "));
  Serial.print(humidity);
  Serial.println(F("%"));

  Serial.println();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rain: ");
  lcd.print(rainfall);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("LDR: ");
  lcd.print(irValue);
  lcd.print("     ");

  delay(3000); // Delay before displaying the next set of data

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("BMP Temp: ");
  lcd.print(bmp_temperature);
  lcd.print("C   ");

  delay(3000); // Delay before displaying the next set of data

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("Pressure: ");
  lcd.print(pressure);
  lcd.print("Pa   ");

  delay(3000); // Delay before displaying the next set of data

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Altitude: ");
  lcd.print(altitude);
  lcd.print("m   ");

  String LoRaMessage = String(device_id) + "/" + String(rainfall) + "/" + String(irValue) + "/" + String(temperature) + "/" + String(humidity) + "/" + String(bmp_temperature) + "/" + String(pressure) + "/" + String(altitude);

  // Send packet with all sensor data
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  delay(10000);
}