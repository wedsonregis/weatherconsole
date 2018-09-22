#include "WiFi.h"
#include "HTTPClient.h"
#include "ArduinoJson.h"

const char* ssid = "SSID";
const char* password = "password";
const String key = "b6907d289e10d714a6e88b30761fae22";
const String city = "porto alegre";

String JsonData = "";

void setup ()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected!");
}

void loop()
{

    if (WiFi.status() == WL_CONNECTED) {

        HTTPClient http;

        http.begin("http://openweathermap.org/data/2.5/weather?q="+city+"&appid="+key+"");
        //http://openweathermap.org/data/2.5/weather?q=recife&appid=b6907d289e10d714a6e88b30761fae22
        int httpCode = http.GET();

        if (httpCode > 0) {

            JsonData = http.getString();
            Serial.println(JsonData);

            DynamicJsonBuffer jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(JsonData);

            if (!root.success()) {
                Serial.println("parseObject() failed");
                return;
            }
            const char* cidade = root["name"];
            Serial.print("Cidade ");
            Serial.println(cidade);

            const char* temp = root["main"]["temp"];
            Serial.print("Temperatura ");
            Serial.println(temp);

            const char* minima = root["main"]["temp_min"];
            Serial.print("Minima ");
            Serial.println(minima);

            const char* maxima = root["main"]["temp_max"];
            Serial.print("Máxima ");
            Serial.println(maxima);

            const char* umidade = root["main"]["humidity"];
            Serial.print("Umidade ");
            Serial.print(umidade); Serial.println("%");
        }

        http.end();

    }
    delay(60000);
}
