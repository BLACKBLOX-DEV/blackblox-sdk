#include <BLACKBLOX.h>

#include <WiFi.h>
#include <Wire.h>
#include <time.h>

#include "graphics/fonts/BBFont5x7.h"
#include "graphics/fonts/BBFont8x16.h"

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

// Modra barva ure z omejeno svetilnostjo.
const BBColor ClockColor(0x00, 0x00, 0xA0);

// Barvi zagonskega napisa.
// Rdeča in zelena sta namenoma zmanjšani, ker sta
// na matrikah videti bistveno svetlejši od modre.
const BBColor StartupTopColor(0x10, 0x00, 0x00);
const BBColor StartupBottomColor(0x00, 0x08, 0x00);

constexpr uint32_t StartupScrollStepMs = 70;
constexpr uint32_t StartupPauseBetweenPhrasesMs = 250;

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

// Matrike priključimo virtualnemu zaslonu samo enkrat.
bool matricesAttached = false;

// Ura je pripravljena šele po uspešnem Wi-Fi in NTP zagonu.
bool clockInitialized = false;

// Zadnja prikazana sekunda.
int lastDisplayedSecond = -1;

// Čas zadnjega poskusa inicializacije.
uint32_t lastInitializationAttempt = 0;

// Ponovni poskus zagona.
constexpr uint32_t InitializationRetryMs = 3000;

// Čakanje po vklopu napajanja.
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

    // Besedilo ostane v zgornji fizicni vrsti matrik.
    // Tako ga meja pri y = 8 ne prereze in zgornji del
    // ne more prehitevati spodnjega zaradi zaporednega
    // osvezevanja posameznih modulov.
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

    // BBScroller ob vsakem klicu update() naredi najvec
    // en korak. Ta pomocna funkcija pocaka samo zato, ker
    // se zagonsko zaporedje izvede pred zagonom ure.
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

    // Napise prikazemo zaporedno, da gledalec vedno
    // bere samo eno kratko sporocilo.

    scrollStartupText(
        "Another",
        StartupTopColor);

    scrollStartupText(
        "Brick",
        StartupTopColor);

    scrollStartupText(
        "in the Wall",
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