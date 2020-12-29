#include <Arduino.h>
#include <M5Stack.h>
#include <NeoPixelBus.h>
#include <WiFi.h>

#include <vector>

#include "bell.h"
#include "clock_bg.c"
#include "clock_hand.h"
#include "credentials.h"
#include "time.h"

std::vector<int> ringTime = {815,  900,  905,  950,  1015, 1100, 1105, 1150,
                             1300, 1345, 1350, 1435, 1500, 1545, 1550, 1635};

const String ntpServer = "ch.pool.ntp.org";
const long gmtOffsetSec = 3600;
const int daylightOffsetSec = 3600;

const int pixelCount = 10;
const int pixelPin = 15;
const int colorSaturation = 128;

const RgbColor red(colorSaturation, 0, 0);
const RgbColor green(0, colorSaturation, 0);
const RgbColor blue(0, 0, colorSaturation);
const RgbColor black(0, 0, 0);

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(pixelCount, pixelPin);

struct tm saved_timeinfo;

Bell bell(1000, {395, 495, 585, 788});

ClockHand hour(160, 120, 70.0, 25.0, 4.0 * PI / 180.0, 16.0 * PI / 180.0);
ClockHand minute(160, 120, 100.0, 30.0, 2.5 * PI / 180.0, 11.0 * PI / 180.0);

void setup() {
    M5.begin();
    M5.Power.begin();
    strip.Begin();
    strip.ClearTo(blue);
    strip.Show();
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    strip.ClearTo(black);
    strip.Show();

    while (!WiFi.isConnected()) {
        strip.ClearTo(blue);
        strip.Show();
        delay(50);
        strip.ClearTo(black);
        strip.Show();
        delay(50);
    }
    strip.ClearTo(blue);
    strip.Show();
    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer.c_str());

    // WiFi.disconnect();
    strip.ClearTo(black);
    strip.Show();

    saved_timeinfo.tm_hour = -1;
    saved_timeinfo.tm_min = -1;
}

void loop() {
    M5.update();
    if (M5.BtnA.isPressed()) {
        bell.Ring();
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return;
    }

    int h = timeinfo.tm_hour;
    int m = timeinfo.tm_min;

    if (h == saved_timeinfo.tm_hour && m == saved_timeinfo.tm_min) {
        return;
    }

    memcpy(&saved_timeinfo, &timeinfo, sizeof(timeinfo));

    M5.Lcd.drawBitmap(0, 0, 320, 240, bg.pixel_data);
    hour.Draw((PI / 2.0) - (h + m / 60.0) * PI / 6.0);
    minute.Draw((PI / 2.0) - m * PI / 30.0);

    int code = h * 100 + m;
    for (auto t : ringTime) {
        if (code == t) {
            bell.Ring();
            break;
        }
    }
}