#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>

IPAddress local_IP(192, 168, 88, 180);
IPAddress gateway(192, 168, 88, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);        //optional
IPAddress secondaryDNS(204, 59, 80, 17); //optional

const char *ssid = "SSID";
const char *password = "PAss";
const char *mDNS_username = "sr01"; // sr01.local

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  // // Connect to WiFi network
  // if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  // {
  //   Serial.println("[STA]Failed to configure");
  // }
  // else
  // {
  //   Serial.println("[STA]STA to configure");
  // }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());
  if (!MDNS.begin(mDNS_username))
  {
    Serial.println("[Error]mDNS");
    return;
  }
  else
  {
    Serial.printf("[Success]mDNS%s", mDNS_username);
  }
  server.on(
      "/makemachinestates",
      HTTP_POST,
      [](AsyncWebServerRequest *request) {},
      NULL,
      [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
      {
        for (size_t i = 0; i < len; i++)
        {
          Serial.write(data[i]);
        }

        Serial.println();

        request->send(200);
      });

  server.begin();
}

void loop() {}