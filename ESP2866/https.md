# HTTPS Request with ESP2866

```c
const char* host = "swharden.com";
const char* endpoint = "/iot/test/write/";

void make_request() {
  Serial.print("Opening HTTPS connection to ");
  Serial.println(host);

  WiFiClientSecure client;
  client.setInsecure();  // WARNING

  if (!client.connect(host, 443)) {
    Serial.println("ERROR: connection failed");
    return;
  }

  String url = String(endpoint) + "?data=123";
  String request = "GET " + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n";
  Serial.print("Requesting: ");
  Serial.print(host);
  Serial.print(url);
  client.print(request);
  Serial.println();
}
```