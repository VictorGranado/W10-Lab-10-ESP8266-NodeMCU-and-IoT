/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on NodeMCU.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right NodeMCU module
  in the Tools -> Board menu!

  For advanced settings please follow ESP examples :
   - ESP8266_Standalone_Manual_IP.ino
   - ESP8266_Standalone_SmartConfig.ino
   - ESP8266_Standalone_SSL.ino

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/*************************************************************
  Toggle onboard LED via Blynk switch (V0)
  Open Wi-Fi (no password) + full debug/logging
*************************************************************/

/*************************************************************
  Toggle LED (V0), Echo to V1, Send uptime to V2
*************************************************************/

/*************************************************************
  Toggle LED (V0), Echo to V1, Send uptime to V2
  — no external timer library, uses millis()
*************************************************************/

/* ——————————————————————————————— */
/* 1) Blynk device info BEFORE any includes */
#define BLYNK_TEMPLATE_ID    "TMPL2GbwvzWj0"
#define BLYNK_TEMPLATE_NAME  "Quickstart Device"
#define BLYNK_AUTH_TOKEN     "aHxweKLup53_ywwe70xJJ_sGfU4kvOK8"
/* ——————————————————————————————— */

#define BLYNK_PRINT Serial       // comment out to disable debug
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "optix_legacy";    // open 2.4 GHz network

// track when we last sent uptime
unsigned long lastUptimeMs = 0;

BLYNK_WRITE(V0) {
  int v = param.asInt();  
  digitalWrite(LED_BUILTIN, v ? LOW : HIGH); // onboard LED is active-LOW
  Blynk.virtualWrite(V1, v);                // echo to V1
}

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // off at start

  // 1) Join open Wi-Fi
  Serial.printf("Connecting to \"%s\"…", ssid);
  WiFi.begin(ssid);
  uint8_t tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 20) {
    Serial.print('.');
    delay(500);
    tries++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n❌ Wi-Fi FAILED");
    return;
  }
  Serial.println("\n✅ Wi-Fi connected");
  Serial.print("IP: "); Serial.println(WiFi.localIP());

  // 2) Connect to Blynk.Cloud
  Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  Serial.println("Connecting to Blynk…");
  if (Blynk.connect()) {
    Serial.println("✅ Blynk connected!");
  } else {
    Serial.println("❌ Blynk FAILED");
    return;
  }
}

void loop() {
  Blynk.run();

  // every 1 s, send uptime to V2
  unsigned long now = millis();
  if (now - lastUptimeMs >= 1000) {
    lastUptimeMs = now;
    Blynk.virtualWrite(V2, now / 1000);
  }
}


