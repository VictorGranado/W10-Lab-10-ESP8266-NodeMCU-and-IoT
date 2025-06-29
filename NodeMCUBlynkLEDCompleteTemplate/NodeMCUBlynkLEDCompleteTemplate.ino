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

/* ——————————————————————————————— */
/* 1) Must define these BEFORE any Blynk includes */
#define BLYNK_PRINT    Serial      // Send Blynk debug to Serial
#define BLYNK_DEBUG                   // More verbose debug

#define BLYNK_TEMPLATE_ID    "TMPL2GbwvzWj0"
#define BLYNK_TEMPLATE_NAME  "Quickstart Device"
#define BLYNK_AUTH_TOKEN     "aHxweKLup53_ywwe70xJJ_sGfU4kvOK8"
/* ——————————————————————————————— */

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your open SSID (no pass)
char ssid[] = "optix_legacy";

BLYNK_WRITE(V0) {
  int v = param.asInt();  
  // onboard LED is active-LOW
  digitalWrite(LED_BUILTIN, v ? LOW : HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(100);

  // Prep LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // 1) Wi-Fi join
  Serial.printf("Connecting to Wi-Fi \"%s\"", ssid);
  WiFi.begin(ssid);
  uint8_t tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 20) {
    Serial.print('.');
    delay(500);
    tries++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Wi-Fi FAILED");
    // Optionally halt or reboot here
    return;
  }

  // 2) Blynk connect
  Blynk.config(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  Serial.println("Connecting to Blynk Cloud...");
  if (Blynk.connect()) {
    Serial.println("✅ Blynk connected!");
  } else {
    Serial.println("❌ Blynk connection FAILED");
  }
}

void loop() {
  Blynk.run();
}

