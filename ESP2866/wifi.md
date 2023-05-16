# Connecting to WiFi with ESP2866

Be sure to connect to a 2.4 GHz network (not a 5 GHz one)

```c
#include <ESP8266WiFi.h>

const char* ssid = "MY_WIFI_NAME";
const char* password = "MY_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
```
