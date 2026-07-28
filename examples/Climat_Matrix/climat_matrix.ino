#include <BLACKBLOX.h>

#include <WiFi.h>
#include <Wire.h>
#include <time.h>

#include "graphics/fonts/BBFont5x7.h"
#include "graphics/fonts/BBFont8x16.h"

#include "sensors/climate/pressure/BBWSENPADS.h"
#include "sensors/climate/BBWSENHIDS.h"

using namespace blackblox;

// ============================================================
// Wi-Fi
// ============================================================

const char* WifiSsid =
    "blackbloxHQ";

const char* WifiPassword =
    "kapacitivnost";

// ============================================================
// I2C
// ============================================================

constexpr int SdaPin = 0;
constexpr int SclPin = 1;
constexpr uint32_t I2cFrequency = 400000;

// ============================================================
// Barve
// ============================================================

const BBColor ClockColor(0x00, 0x00, 0xA0);
const BBColor TemperatureColor(0x80, 0x20, 0x00);
const BBColor HumidityColor(0x00, 0x40, 0x80);
const BBColor PressureColor(0x20, 0x70, 0x20);
const BBColor ErrorColor(0x80, 0x00, 0x00);

// Barvi zagonskega napisa.
const BBColor StartupTopColor(0x10, 0x00, 0x00);
const BBColor StartupBottomColor(0x00, 0x08, 0x00);

constexpr uint32_t StartupScrollStepMs = 70;
constexpr uint32_t StartupPauseBetweenPhrasesMs = 250;

// ============================================================
// Časi prikaza strani
// ============================================================

constexpr uint32_t ClockPageDurationMs = 5000;
constexpr uint32_t SensorPageDurationMs = 2500;

// ============================================================
// Matrike
//
// Fizična postavitev:
//
// 0x11  0x12  0x13
// 0x14  0x15  0x16
//
// Skupna ločljivost: 48 x 16 pikslov
// Vse matrike so zasukane R180.
// ============================================================

BBRGBMatrix8x16 matrix11(0x11);
BBRGBMatrix8x16 matrix12(0x12);
BBRGBMatrix8x16 matrix13(0x13);

BBRGBMatrix8x16 matrix14(0x14);
BBRGBMatrix8x16 matrix15(0x15);
BBRGBMatrix8x16 matrix16(0x16);

BBMatrixDisplay display(48, 16);
BBScroller scroller(display);

// ============================================================
// Senzorji
// ============================================================

BBWSENPADS pressureSensor;
BBWSENHIDS humiditySensor;

bool pressureSensorAvailable = false;
bool humiditySensorAvailable = false;

float temperatureC = 0.0f;
float humidityPercent = 0.0f;
float pressureHpa = 0.0f;

bool temperatureValid = false;
bool humidityValid = false;
bool pressureValid = false;

// ============================================================
// NTP
// ============================================================

const char* NtpServer1 =
    "pool.ntp.org";

const char* NtpServer2 =
    "time.google.com";

const char* NtpServer3 =
    "time.cloudflare.com";

// Slovenija:
// CET pozimi, CEST poleti.
const char* TimeZone =
    "CET-1CEST,M3.5.0/2,M10.5.0/3";

// ============================================================
// Stanje programa
// ============================================================

enum class DisplayPage
{
    Clock,
    Temperature,
    Humidity,
    Pressure
};

bool matricesAttached = false;
bool clockInitialized = false;

DisplayPage currentPage = DisplayPage::Clock;

int lastDisplayedSecond = -1;

uint32_t pageStartedAt = 0;
uint32_t lastInitializationAttempt = 0;

constexpr uint32_t InitializationRetryMs = 3000;
constexpr uint32_t PowerUpDelayMs = 3000;

// ============================================================
// Prikaz besedila na sredini
// ============================================================

void showText(
    const char* text,
    BBColor color)
{
    if (!matricesAttached)
    {
        return;
    }

    const BBFont& font =
        BBFont8x16::font();

    const int16_t textWidth =
        display.getTextWidth(
            text,
            font);

    const int16_t x =
        (static_cast<int16_t>(
            display.getWidth()) -
         textWidth) / 2;

    display.clear();

    display.drawText(
        x,
        0,
        text,
        font,
        color);

    display.show();
}

void showTwoLineText(
    const char* topText,
    const char* bottomText,
    BBColor color)
{
    if (!matricesAttached)
    {
        return;
    }

    const BBFont& font =
        BBFont5x7::font();

    const int16_t topWidth =
        display.getTextWidth(
            topText,
            font);

    const int16_t bottomWidth =
        display.getTextWidth(
            bottomText,
            font);

    const int16_t topX =
        (static_cast<int16_t>(
            display.getWidth()) -
         topWidth) / 2;

    const int16_t bottomX =
        (static_cast<int16_t>(
            display.getWidth()) -
         bottomWidth) / 2;

    display.clear();

    display.drawText(
        topX,
        0,
        topText,
        font,
        color);

    display.drawText(
        bottomX,
        9,
        bottomText,
        font,
        color);

    display.show();
}

// ============================================================
// Zagonska animacija
// ============================================================

void scrollStartupText(
    const char* text,
    BBColor color)
{
    if (!matricesAttached ||
        text == nullptr)
    {
        return;
    }

    const BBFont& font =
        BBFont5x7::font();

    constexpr int16_t y = 0;

    if (!scroller.start(
            text,
            y,
            font,
            color,
            StartupScrollStepMs))
    {
        Serial.println(
            "Zagonskega napisa ni mogoce zagnati.");

        return;
    }

    while (scroller.isRunning())
    {
        scroller.update();
        delay(1);
    }

    delay(StartupPauseBetweenPhrasesMs);
}

void showStartupAnimation()
{
    if (!matricesAttached)
    {
        return;
    }

    Serial.println(
        "Prikazujem zagonski napis ...");

    scrollStartupText(
        "Another",
        StartupTopColor);

    scrollStartupText(
        "Brick",
        StartupTopColor);

    scrollStartupText(
        "in the wall",
        StartupBottomColor);

    display.clear();
    display.show();
}

// ============================================================
// Priklop matrik na skupni zaslon
// ============================================================

void attachMatrices()
{
    if (matricesAttached)
    {
        return;
    }

    display.attach(
        matrix11,
        0,
        0,
        BBMatrixRotation::R180);

    display.attach(
        matrix12,
        16,
        0,
        BBMatrixRotation::R180);

    display.attach(
        matrix13,
        32,
        0,
        BBMatrixRotation::R180);

    display.attach(
        matrix14,
        0,
        8,
        BBMatrixRotation::R180);

    display.attach(
        matrix15,
        16,
        8,
        BBMatrixRotation::R180);

    display.attach(
        matrix16,
        32,
        8,
        BBMatrixRotation::R180);

    matricesAttached = true;

    Serial.print(
        "Stevilo prikljucenih matrik: ");

    Serial.println(
        display.matrixCount());
}

// ============================================================
// Inicializacija I2C, matrik in senzorjev
// ============================================================

void initializeMatrices()
{
    Serial.println(
        "Inicializiram I2C ...");

    BB.begin(
        SdaPin,
        SclPin);

    Wire.setClock(I2cFrequency);

    Serial.print(
        "I2C frekvenca: ");

    Serial.print(
        I2cFrequency);

    Serial.println(
        " Hz");

    delay(500);

    Serial.println(
        "Inicializiram matrike ...");

    matrix11.begin();
    delay(50);

    matrix12.begin();
    delay(50);

    matrix13.begin();
    delay(50);

    matrix14.begin();
    delay(50);

    matrix15.begin();
    delay(50);

    matrix16.begin();
    delay(50);

    attachMatrices();

    display.clear();
    display.show();

    delay(100);
}

void initializeSensors()
{
    Serial.println(
        "Inicializiram klimatske senzorje ...");

    pressureSensorAvailable =
        pressureSensor.begin();

    humiditySensorAvailable =
        humiditySensor.begin();

    Serial.print(
        "WSEN-PADS: ");

    Serial.println(
        pressureSensorAvailable
            ? "OK"
            : "ni zaznan");

    Serial.print(
        "WSEN-HIDS: ");

    Serial.println(
        humiditySensorAvailable
            ? "OK"
            : "ni zaznan");
}

// ============================================================
// Branje senzorjev
// ============================================================

void readClimateSensors()
{
    temperatureValid = false;
    humidityValid = false;
    pressureValid = false;

    if (!humiditySensorAvailable)
    {
        humiditySensorAvailable =
            humiditySensor.begin();
    }

    if (humiditySensorAvailable)
    {
        float measuredTemperature = 0.0f;
        float measuredHumidity = 0.0f;

        if (humiditySensor.read(
                measuredTemperature,
                measuredHumidity))
        {
            temperatureC =
                measuredTemperature;

            humidityPercent =
                measuredHumidity;

            temperatureValid = true;
            humidityValid = true;
        }
        else
        {
            Serial.println(
                "Napaka pri branju WSEN-HIDS.");
        }
    }

    if (!pressureSensorAvailable)
    {
        pressureSensorAvailable =
            pressureSensor.begin();
    }

    if (pressureSensorAvailable)
    {
        float measuredPressureKpa = 0.0f;
        float measuredTemperature = 0.0f;

        if (pressureSensor.read(
                measuredPressureKpa,
                measuredTemperature))
        {
            pressureHpa =
                measuredPressureKpa * 10.0f;

            pressureValid = true;

            // Če HIDS ni vrnil temperature,
            // uporabimo temperaturo senzorja PADS.
            if (!temperatureValid)
            {
                temperatureC =
                    measuredTemperature;

                temperatureValid = true;
            }
        }
        else
        {
            Serial.println(
                "Napaka pri branju WSEN-PADS.");
        }
    }

    if (temperatureValid)
    {
        Serial.printf(
            "Temperatura: %.1f C\n",
            temperatureC);
    }

    if (humidityValid)
    {
        Serial.printf(
            "Vlaga: %.1f %%\n",
            humidityPercent);
    }

    if (pressureValid)
    {
        Serial.printf(
            "Tlak: %.1f hPa\n",
            pressureHpa);
    }
}

// ============================================================
// Prikaz senzorjev
// ============================================================

void showTemperature()
{
    if (!temperatureValid)
    {
        showTwoLineText(
            "TEMP",
            "--.-C",
            ErrorColor);

        return;
    }

    char text[12];

    snprintf(
        text,
        sizeof(text),
        "%.1fC",
        temperatureC);

    showTwoLineText(
        "TEMP",
        text,
        TemperatureColor);
}

void showHumidity()
{
    if (!humidityValid)
    {
        showTwoLineText(
            "VLAGA",
            "--%",
            ErrorColor);

        return;
    }

    char text[12];

    snprintf(
        text,
        sizeof(text),
        "%.0f%%",
        humidityPercent);

    showTwoLineText(
        "VLAGA",
        text,
        HumidityColor);
}

void showPressure()
{
    if (!pressureValid)
    {
        showTwoLineText(
            "TLAK",
            "----hPa",
            ErrorColor);

        return;
    }

    char text[16];

    snprintf(
        text,
        sizeof(text),
        "%.0fhPa",
        pressureHpa);

    showTwoLineText(
        "TLAK",
        text,
        PressureColor);
}

// ============================================================
// Wi-Fi
// ============================================================

bool connectToWifi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return true;
    }

    Serial.print(
        "Povezujem se na Wi-Fi: ");

    Serial.println(
        WifiSsid);

    WiFi.mode(WIFI_STA);

    WiFi.disconnect();
    delay(200);

    WiFi.begin(
        WifiSsid,
        WifiPassword);

    const uint32_t startTime =
        millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(500);

        if (millis() - startTime >= 20000)
        {
            Serial.println();

            Serial.println(
                "Wi-Fi povezava ni uspela.");

            WiFi.disconnect();

            return false;
        }
    }

    Serial.println();

    Serial.println(
        "Wi-Fi je povezan.");

    Serial.print(
        "IP naslov: ");

    Serial.println(
        WiFi.localIP());

    return true;
}

// ============================================================
// NTP sinhronizacija
// ============================================================

bool synchronizeTime()
{
    Serial.println(
        "Zaganjam NTP sinhronizacijo ...");

    configTzTime(
        TimeZone,
        NtpServer1,
        NtpServer2,
        NtpServer3);

    struct tm timeInfo;

    for (int attempt = 0;
         attempt < 30;
         ++attempt)
    {
        if (getLocalTime(
                &timeInfo,
                1000))
        {
            Serial.println();

            Serial.println(
                "Cas je sinhroniziran.");

            Serial.printf(
                "Trenutni cas: %02d:%02d:%02d\n",
                timeInfo.tm_hour,
                timeInfo.tm_min,
                timeInfo.tm_sec);

            return true;
        }

        Serial.print('.');
    }

    Serial.println();

    Serial.println(
        "NTP sinhronizacija ni uspela.");

    return false;
}

// ============================================================
// Prikaz ure
// ============================================================

void showTime(
    const struct tm& timeInfo)
{
    if (!matricesAttached)
    {
        return;
    }

    const BBFont& font =
        BBFont8x16::font();

    char hourText[3];
    char minuteText[3];

    snprintf(
        hourText,
        sizeof(hourText),
        "%02d",
        timeInfo.tm_hour);

    snprintf(
        minuteText,
        sizeof(minuteText),
        "%02d",
        timeInfo.tm_min);

    const int16_t hourWidth =
        display.getTextWidth(
            hourText,
            font);

    const int16_t colonWidth =
        display.getCharacterWidth(
            ':',
            font);

    const int16_t minuteWidth =
        display.getTextWidth(
            minuteText,
            font);

    const int16_t totalWidth =
        hourWidth +
        font.spacing +
        colonWidth +
        font.spacing +
        minuteWidth;

    const int16_t startX =
        (static_cast<int16_t>(
            display.getWidth()) -
         totalWidth) / 2;

    const int16_t colonX =
        startX +
        hourWidth +
        font.spacing;

    const int16_t minuteX =
        colonX +
        colonWidth +
        font.spacing;

    display.clear();

    display.drawText(
        startX,
        0,
        hourText,
        font,
        ClockColor);

    if ((timeInfo.tm_sec & 1) == 0)
    {
        display.drawChar(
            colonX,
            0,
            ':',
            font,
            ClockColor);
    }

    display.drawText(
        minuteX,
        0,
        minuteText,
        font,
        ClockColor);

    display.show();

    Serial.printf(
        "Prikazujem: %02d%c%02d:%02d\n",
        timeInfo.tm_hour,
        ((timeInfo.tm_sec & 1) == 0)
            ? ':'
            : ' ',
        timeInfo.tm_min,
        timeInfo.tm_sec);
}

// ============================================================
// Strani prikaza
// ============================================================

uint32_t currentPageDuration()
{
    return currentPage == DisplayPage::Clock
        ? ClockPageDurationMs
        : SensorPageDurationMs;
}

void showCurrentPage(
    const struct tm& timeInfo)
{
    switch (currentPage)
    {
    case DisplayPage::Clock:
        showTime(timeInfo);
        break;

    case DisplayPage::Temperature:
        showTemperature();
        break;

    case DisplayPage::Humidity:
        showHumidity();
        break;

    case DisplayPage::Pressure:
        showPressure();
        break;
    }
}

void advancePage(
    const struct tm& timeInfo)
{
    switch (currentPage)
    {
    case DisplayPage::Clock:
        readClimateSensors();
        currentPage =
            DisplayPage::Temperature;
        break;

    case DisplayPage::Temperature:
        currentPage =
            DisplayPage::Humidity;
        break;

    case DisplayPage::Humidity:
        currentPage =
            DisplayPage::Pressure;
        break;

    case DisplayPage::Pressure:
        currentPage =
            DisplayPage::Clock;
        break;
    }

    pageStartedAt = millis();
    showCurrentPage(timeInfo);
}

// ============================================================
// Celoten zagon ure
// ============================================================

bool initializeClock()
{
    Serial.println();

    Serial.println(
        "Zacenjam inicializacijo ure ...");

    initializeMatrices();
    initializeSensors();

    showStartupAnimation();

    showText(
        "00:00",
        ClockColor);

    if (!connectToWifi())
    {
        Serial.println(
            "Wi-Fi ni uspel.");

        return false;
    }

    if (!synchronizeTime())
    {
        Serial.println(
            "NTP ni uspel.");

        return false;
    }

    struct tm timeInfo;

    if (!getLocalTime(
            &timeInfo,
            1000))
    {
        Serial.println(
            "Lokalnega casa ni mogoce prebrati.");

        return false;
    }

    currentPage =
        DisplayPage::Clock;

    pageStartedAt =
        millis();

    showTime(timeInfo);

    lastDisplayedSecond =
        timeInfo.tm_sec;

    Serial.println(
        "Ura je inicializirana.");

    return true;
}

// ============================================================
// Setup
// ============================================================

void setup()
{
    Serial.begin(115200);

    delay(PowerUpDelayMs);

    Serial.println();
    Serial.println(
        "BLACKBLOX Matrix Clock 48x16");

    Serial.println(
        "----------------------------");

    lastInitializationAttempt =
        millis() - InitializationRetryMs;
}

// ============================================================
// Loop
// ============================================================

void loop()
{
    if (!clockInitialized)
    {
        const uint32_t now =
            millis();

        if (now - lastInitializationAttempt <
            InitializationRetryMs)
        {
            delay(50);
            return;
        }

        lastInitializationAttempt = now;

        clockInitialized =
            initializeClock();

        if (!clockInitialized)
        {
            showText(
                "--:--",
                ErrorColor);

            Serial.println(
                "Zagon ni uspel.");

            Serial.println(
                "Ponovni poskus cez 3 sekunde.");

            delay(100);
            return;
        }
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(
            "Wi-Fi povezava je izgubljena.");

        clockInitialized = false;
        lastDisplayedSecond = -1;

        WiFi.disconnect();

        showText(
            "00:00",
            ClockColor);

        lastInitializationAttempt =
            millis();

        delay(100);
        return;
    }

    struct tm timeInfo;

    if (!getLocalTime(
            &timeInfo,
            1000))
    {
        Serial.println(
            "Napaka pri branju casa.");

        clockInitialized = false;
        lastDisplayedSecond = -1;

        showText(
            "--:--",
            ErrorColor);

        lastInitializationAttempt =
            millis();

        delay(100);
        return;
    }

    const uint32_t now =
        millis();

    if (now - pageStartedAt >=
        currentPageDuration())
    {
        advancePage(timeInfo);
    }
    else if (
        currentPage == DisplayPage::Clock &&
        timeInfo.tm_sec != lastDisplayedSecond)
    {
        showTime(timeInfo);

        lastDisplayedSecond =
            timeInfo.tm_sec;
    }

    delay(20);
}