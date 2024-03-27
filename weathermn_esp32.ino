#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>
#include <WebServer.h>
// #include <HTTPClient.h>

#define SS 5
#define RST 14
#define DI0 2
#define BAND 433E6

String device_id;
String rainfall;
String irValue;
String temperature;
String humidity;
String bmp_temperature;
String pressure;
String altitude;

const char* ssid = "";
const char* password = "";

WebServer server(80);

// String GOOGLE_SCRIPT_ID = "";

// const int sendInterval = 10000;

// const char * root_ca=\
// "-----BEGIN CERTIFICATE-----\n" \
// "MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
// "A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
// "Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
// "MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
// "A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
// "hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
// "v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
// "eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
// "tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
// "C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
// "zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
// "mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
// "V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
// "bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
// "3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
// "J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
// "291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
// "ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
// "AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
// "TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
// "-----END CERTIFICATE-----\n";


// WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  Serial.println("LoRa Receiver");

  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Received packet:");

    while (LoRa.available()) {
      device_id = LoRa.readStringUntil('/');
      rainfall = LoRa.readStringUntil('/');
      irValue = LoRa.readStringUntil('/');
      temperature = LoRa.readStringUntil('/');
      humidity = LoRa.readStringUntil('/');
      bmp_temperature = LoRa.readStringUntil('/');
      pressure = LoRa.readStringUntil('/');
      altitude = LoRa.readStringUntil('\0');
    }

    Serial.print("Device ID: ");
    Serial.println(device_id);
    Serial.print("Rainfall: ");
    Serial.println(rainfall);
    Serial.print("LDR Sensor Value: ");
    Serial.println(irValue);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("BMP Temperature: ");
    Serial.println(bmp_temperature);
    Serial.print("pressure: ");
    Serial.println(pressure);
    Serial.print("altitude: ");
    Serial.println(altitude);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    
    server.handleClient();
  }
  // sendData("tag=adc_A0&rainfall=" + rainfall +
  //        "&irValue=" + irValue +
  //        "&bmp_temperature=" + bmp_temperature +
  //        "&pressure=" + pressure +
  //        "&altitude=" + altitude +
  //        "&humidity=" + humidity);
  // delay(sendInterval);
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML(rainfall.toFloat(), irValue.toInt(), temperature.toFloat(), humidity.toFloat()));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

// void sendData(String params) {
//    HTTPClient http;
//    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
//    Serial.print(url);
//     Serial.print("Making a request");
//     http.begin(url, root_ca); //Specify the URL and certificate
//     int httpCode = http.GET();  
//     http.end();
//     Serial.println(": done "+httpCode);
// }

String SendHTML(float rainfall, int irValue, float temperature, float humidity) {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><title>Rainfall</title>";
  html += "<style>body{text-align:center;}</style>";
  html += "</head><body>";
  html += "<h1>Rainfall Percentage</h1>";
  html += "<p>Rainfall: ";
  html += rainfall;
  html += "%</p>";
  html += "<p>LDR Sensor Value: ";
  html += irValue;
  html += "</p>";
  html += "<p>BMP temperature: ";
  html += bmp_temperature;
  html += "°C</p>";
  html += "</p>";
  html += "<p>Altitude: ";
  html += altitude;
  html += "</p>";
  html += "<p>Pressure: ";
  html += pressure;
  html += "pascale</p>";
  html += "</p>";
  html += "<p>Temperature: ";
  html += temperature;
  html += "°C</p>";
  html += "<p>Humidity: ";
  html += humidity;
  html += "%</p>";
  html += "</body></html>";
  return html;
}
