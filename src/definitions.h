// *********************************************************************
// Holds all central definitions and globals
// *********************************************************************

Ticker display_ticker;          // Ticker that triggers redraw of the screen
Ticker timer_ticker;            // Ticker that triggers one revolution in the falling animation

// NTP
int8_t timeZone = 10;            // Timezone for NTP client
int8_t minutesTimeZone = 0;     // Minutes difference for time zone

// Globals
uint8_t init_state = 0;         // Hold the current state of the initialization process
String str_display_time = "0000"; // Holds the currently displayed time as string
bool seconds_odd = false;       // True when the seconds are currently odd

// WiFiManager
WiFiManager wifiManager;        // Global WiFiManager object
#define AP_NAME "tetris_clock"
#define AP_PASS "tetromino"
#define AP_TIMEOUT 300


#define TFT_CS     D1
#define TFT_RST    D2  // you can also connect this to the Arduino reset
                        // in which case, set this #define pin to 0!
#define TFT_DC     D3
#define TFT_SCLK   D5   // set these to be whatever pins you like!
#define TFT_MOSI   D6   // set these to be whatever pins you like!
#define TFT_LED	   D7
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
DisplayEmulator display(32, 32);
