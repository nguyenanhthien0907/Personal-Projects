#define BLYNK_TEMPLATE_ID "TMPL6vDVCkO9D"
#define BLYNK_DEVICE_NAME "DHT11"
#define BLYNK_TEMPLATE_NAME "DHT11_Template"
#define BLYNK_AUTH_TOKEN "aXZtvwd26AtS51uSCoBTNXzpX5sOOh6j"

#include <WiFi.h>             // Thư viện WiFi cho ESP32
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>  // Thư viện Blynk cho ESP32
#include <DHT.h>               // Thư viện cho cảm biến DHT
#include <string.h>

#define DHTPIN 4        // GPIO 4 kết nối với chân Data của DHT11
#define DHTTYPE DHT11   // Cảm biến DHT11

DHT dht(DHTPIN, DHTTYPE);  // Khởi tạo đối tượng DHT

#define LED 16
WidgetLED LED_ON_APP(V2);
int button;

// Thông tin WiFi và Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;   
char ssid[] = "337 NGUYEN OANH";        // Thay thế bằng tên WiFi của bạn
char pass[] = "12345689";    // Thay thế bằng mật khẩu WiFi của bạn


void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V3){
  button = param.asInt();
  if (button == 1){
    digitalWrite(LED, HIGH);
    LED_ON_APP.on();
  }
  else {
    digitalWrite(LED, LOW);
    LED_ON_APP.off();
  }
}

void loop() {
  Blynk.run();       // Chạy tiến trình Blynk
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)){
    delay(500);
    Serial.println("Failed to read from DHT sensor!\n");
    return;
  }
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V0, h);

  Serial.print("\n");
  Serial.print("Humidity: " + String(h) + "%");
  Serial.print("\t");
  Serial.print("Temperature: " + String(t) + " C");
  delay(2000);
}
