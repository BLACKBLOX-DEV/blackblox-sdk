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
    "YOUR_WIFI_SSID";

const char* WifiPassword =
    "YOUR_WIFI_PASSWORD";

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

    // Zgornja vrsta.

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

    // Spodnja vrsta.

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
// Inicializacija I2C in matrik
// ============================================================

void initializeMatrices()
{
    Serial.println(
        "Inicializiram I2C ...");

    BB.begin(
        SdaPin,
        SclPin);

    // Standardna hitrost I2C za ta primer.
    Wire.setClock(I2cFrequency);

    Serial.print(
        "I2C frekvenca: ");

    Serial.print(
        I2cFrequency);

    Serial.println(
        " Hz");

    // Po inicializaciji I2C počakamo,
    // da se vodilo in moduli stabilizirajo.
    delay(500);

    Serial.println(
        "Inicializiram matrike ...");

    // begin() ponovimo ob vsakem novem poskusu zagona.

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

    // Virtualnemu zaslonu jih priključimo samo enkrat.

    attachMatrices();

    // Ob zagonu ne prižigamo vseh LED.
    // Zaslon samo počistimo, da ostane poraba majhna.

    Serial.println(
        "Pocistim matrike brez barvnega testa ...");

    display.clear();
    display.show();

    delay(100);
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

    // Ure.

    display.drawText(
        startX,
        0,
        hourText,
        font,
        ClockColor);

    // Dvopičje je prižgano pri sodih sekundah.

    if ((timeInfo.tm_sec & 1) == 0)
    {
        display.drawChar(
            colonX,
            0,
            ':',
            font,
            ClockColor);
    }

    // Minute so vedno na istem mestu.

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
// Celoten zagon ure
// ============================================================

bool initializeClock()
{
    Serial.println();

    Serial.println(
        "Zacenjam inicializacijo ure ...");

    initializeMatrices();

    // Zagonski napis prikazemo v treh zaporednih delih.

    showStartupAnimation();

    // Začasni prikaz pred povezovanjem.

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

    // Po vklopu adapterja počakamo,
    // da se napajanje in matrike stabilizirajo.

    delay(PowerUpDelayMs);

    Serial.println();
    Serial.println(
        "BLACKBLOX Matrix Clock 48x16");

    Serial.println(
        "----------------------------");

    // Prvi poskus naj se izvede takoj
    // ob prvem prehodu skozi loop().

    lastInitializationAttempt =
        millis() - InitializationRetryMs;
}

// ============================================================
// Loop
// ============================================================

void loop()
{
    // --------------------------------------------------------
    // Inicializacija
    // --------------------------------------------------------

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
                BBColor::Red());

            Serial.println(
                "Zagon ni uspel.");

            Serial.println(
                "Ponovni poskus cez 3 sekunde.");

            delay(100);
            return;
        }
    }

    // --------------------------------------------------------
    // Preverjanje Wi-Fi
    // --------------------------------------------------------

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

    // --------------------------------------------------------
    // Branje časa
    // --------------------------------------------------------

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
            BBColor::Red());

        lastInitializationAttempt =
            millis();

        delay(100);
        return;
    }

    // --------------------------------------------------------
    // Osvezitev prikaza ob spremembi sekunde
    // --------------------------------------------------------

    if (timeInfo.tm_sec != lastDisplayedSecond)
    {
        showTime(timeInfo);

        lastDisplayedSecond =
            timeInfo.tm_sec;
    }

    delay(20);
}