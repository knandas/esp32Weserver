////////////////// TFT_eSPI   User_Setup.h ///////////////////////////////

//                            USER DEFINED SETTINGS
//   Set driver type, fonts to be loaded, pins used and SPI control method etc.
//
//   See the User_Setup_Select.h file if you wish to be able to define multiple
//   setups and then easily select which setup file is used by the compiler.
//
//   If this file is edited correctly then all the library example sketches should
//   run without the need to make any more changes for a particular hardware setup!
//   Note that some sketches are designed for a particular TFT pixel width/height

// User defined information reported by "Read_User_Setup" test & diagnostics example
#define USER_SETUP_INFO "User_Setup"

// Define to disable all #warnings in library (can be put in User_Setup_Select.h)
//#define DISABLE_ALL_LIBRARY_WARNINGS

// ##################################################################################
//
// Section 1. Call up the right driver file and any options for it
//
// ##################################################################################

// Define STM32 to invoke optimised processor support (only for STM32)
//#define STM32

// Defining the STM32 board allows the library to optimise the performance
// for UNO compatible "MCUfriend" style shields
//#define NUCLEO_64_TFT
//#define NUCLEO_144_TFT

// STM32 8-bit parallel only:
// If STN32 Port A or B pins 0-7 are used for 8-bit parallel data bus bits 0-7
// then this will improve rendering performance by a factor of ~8x
//#define STM_PORTA_DATA_BUS
//#define STM_PORTB_DATA_BUS

// Tell the library to use parallel mode (otherwise SPI is assumed)
//#define TFT_PARALLEL_8_BIT
//#defined TFT_PARALLEL_16_BIT // **** 16-bit parallel ONLY for RP2040 processor ****

// Display type -  only define if RPi display
//#define RPI_DISPLAY_TYPE // 20MHz maximum SPI

// Only define one driver, the other ones must be commented out
//#define ILI9341_DRIVER       // Generic driver for common displays
//#define ILI9341_2_DRIVER     // Alternative ILI9341 driver, see https://github.com/Bodmer/TFT_eSPI/issues/1172
//#define ST7735_DRIVER      // Define additional parameters below for this display
//#define ILI9163_DRIVER     // Define additional parameters below for this display
//#define S6D02A1_DRIVER
//#define RPI_ILI9486_DRIVER // 20MHz maximum SPI
//#define HX8357D_DRIVER
//#define ILI9481_DRIVER
//#define ILI9486_DRIVER
//#define ILI9488_DRIVER     // WARNING: Do not connect ILI9488 display SDO to MISO if other devices share the SPI bus (TFT SDO does NOT tristate when CS is high)
#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
//#define ST7789_2_DRIVER    // Minimal configuration option, define additional parameters below for this display
//#define R61581_DRIVER
//#define RM68140_DRIVER
//#define ST7796_DRIVER
//#define SSD1351_DRIVER
//#define SSD1963_480_DRIVER
//#define SSD1963_800_DRIVER
//#define SSD1963_800ALT_DRIVER
//#define ILI9225_DRIVER
//#define GC9A01_DRIVER

// Some displays support SPI reads via the MISO pin, other displays have a single
// bi-directional SDA pin and the library will try to read this via the MOSI line.
// To use the SDA line for reading data from the TFT uncomment the following line:

// #define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with ST7789 and GC9A01 display only

// For ST7735, ST7789 and ILI9341 ONLY, define the colour order IF the blue and red are swapped on your display
// Try ONE option at a time to find the correct colour order for your display

// #define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

// For M5Stack ESP32 module with integrated ILI9341 display ONLY, remove // in line below

// #define M5STACK

// For ST7789, ST7735, ILI9163 and GC9A01 ONLY, define the pixel width and height in portrait orientation
// #define TFT_WIDTH  80
// #define TFT_WIDTH  128
// #define TFT_WIDTH  172 // ST7789 172 x 320
// #define TFT_WIDTH  170 // ST7789 170 x 320
#define TFT_WIDTH  240 // ST7789 240 x 240 and 240 x 320
// #define TFT_HEIGHT 160
// #define TFT_HEIGHT 128
// #define TFT_HEIGHT 240 // ST7789 240 x 240
#define TFT_HEIGHT 320 // ST7789 240 x 320
// #define TFT_HEIGHT 240 // GC9A01 240 x 240

// For ST7735 ONLY, define the type of display, originally this was based on the
// colour of the tab on the screen protector film but this is not always true, so try
// out the different options below if the screen does not display graphics correctly,
// e.g. colours wrong, mirror images, or stray pixels at the edges.
// Comment out ALL BUT ONE of these options for a ST7735 display driver, save this
// this User_Setup file, then rebuild and upload the sketch to the board again:

// #define ST7735_INITB
// #define ST7735_GREENTAB
// #define ST7735_GREENTAB2
// #define ST7735_GREENTAB3
// #define ST7735_GREENTAB128    // For 128 x 128 display
// #define ST7735_GREENTAB160x80 // For 160 x 80 display (BGR, inverted, 26 offset)
// #define ST7735_ROBOTLCD       // For some RobotLCD Arduino shields (128x160, BGR, https://docs.arduino.cc/retired/getting-started-guides/TFT)
// #define ST7735_REDTAB
// #define ST7735_BLACKTAB
// #define ST7735_REDTAB160x80   // For 160 x 80 display with 24 pixel offset

// If colours are inverted (white shows as black) then uncomment one of the next
// 2 lines try both options, one of the options should correct the inversion.

//#define TFT_INVERSION_ON
#define TFT_INVERSION_OFF


// ##################################################################################
//
// Section 2. Define the pins that are used to interface with the display here
//
// ##################################################################################

// If a backlight control signal is available then define the TFT_BL pin in Section 2
// below. The backlight will be turned ON when tft.begin() is called, but the library
// needs to know if the LEDs are ON with the pin HIGH or LOW. If the LEDs are to be
// driven with a PWM signal or turned OFF/ON then this must be handled by the user
// sketch. e.g. with digitalWrite(TFT_BL, LOW);

#define TFT_BL   21            // LED back-light control pin
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)



// We must use hardware SPI, a minimum of 3 GPIO pins is needed.
// Typical setup for ESP8266 NodeMCU ESP-12 is :
//
// Display SDO/MISO  to NodeMCU pin D6 (or leave disconnected if not reading TFT)
// Display LED       to NodeMCU pin VIN (or 5V, see below)
// Display SCK       to NodeMCU pin D5
// Display SDI/MOSI  to NodeMCU pin D7
// Display DC (RS/AO)to NodeMCU pin D3
// Display RESET     to NodeMCU pin D4 (or RST, see below)
// Display CS        to NodeMCU pin D8 (or GND, see below)
// Display GND       to NodeMCU pin GND (0V)
// Display VCC       to NodeMCU 5V or 3.3V
//
// The TFT RESET pin can be connected to the NodeMCU RST pin or 3.3V to free up a control pin
//
// The DC (Data Command) pin may be labelled AO or RS (Register Select)
//
// With some displays such as the ILI9341 the TFT CS pin can be connected to GND if no more
// SPI devices (e.g. an SD Card) are connected, in this case comment out the #define TFT_CS
// line below so it is NOT defined. Other displays such at the ST7735 require the TFT CS pin
// to be toggled during setup, so in these cases the TFT_CS line must be defined and connected.
//
// The NodeMCU D0 pin can be used for RST
//
//
// Note: only some versions of the NodeMCU provide the USB 5V on the VIN pin
// If 5V is not available at a pin you can use 3.3V but backlight brightness
// will be lower.


// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP8266 SETUP ######

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
//#define TFT_MISO  PIN_D6  // Automatically assigned with ESP8266 if not defined
//#define TFT_MOSI  PIN_D7  // Automatically assigned with ESP8266 if not defined
//#define TFT_SCLK  PIN_D5  // Automatically assigned with ESP8266 if not defined

//#define TFT_CS    PIN_D8  // Chip select control pin D8
//#define TFT_DC    PIN_D3  // Data Command control pin
//#define TFT_RST   PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
//#define TFT_RST  -1     // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V


//#define TFT_BL PIN_D1  // LED back-light (only for ST7789 with backlight control pin)

//#define TOUCH_CS PIN_D2     // Chip select pin (T_CS) of touch screen

//#define TFT_WR PIN_D2       // Write strobe for modified Raspberry Pi TFT only


// ######  FOR ESP8266 OVERLAP MODE EDIT THE PIN NUMBERS IN THE FOLLOWING LINES  ######

// Overlap mode shares the ESP8266 FLASH SPI bus with the TFT so has a performance impact
// but saves pins for other functions. It is best not to connect MISO as some displays
// do not tristate that line when chip select is high!
// Note: Only one SPI device can share the FLASH SPI lines, so a SPI touch controller
// cannot be connected as well to the same SPI signals.
// On NodeMCU 1.0 SD0=MISO, SD1=MOSI, CLK=SCLK to connect to TFT in overlap mode
// On NodeMCU V3  S0 =MISO, S1 =MOSI, S2 =SCLK
// In ESP8266 overlap mode the following must be defined

//#define TFT_SPI_OVERLAP

// In ESP8266 overlap mode the TFT chip select MUST connect to pin D3
//#define TFT_CS   PIN_D3
//#define TFT_DC   PIN_D5  // Data Command control pin
//#define TFT_RST  PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)
//#define TFT_RST  -1  // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V


// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######

// For ESP32 Dev board (only tested with ILI9341 display)
// The hardware SPI can be mapped to any pins

#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
//#define TFT_RST   4  // Reset pin (could connect to RST pin)
#define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
#define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen
#define TOUCH_MOSI 32 // CHANGED: MOSI/T_DIN pin for touch
#define TOUCH_MISO 39 // MISO/T_DO pin for touch
#define TOUCH_CLK  25 // CLK/T_CLK pin for touch
#define TOUCH_IRQ 36 // Interrupt pin (T_IRQ) of touch screen

// For ESP32 Dev board (only tested with GC9A01 display)
// The hardware SPI can be mapped to any pins

//#define TFT_MOSI 15 // In some display driver board, it might be written as "SDA" and so on.
//#define TFT_SCLK 14
//#define TFT_CS   5  // Chip select control pin
//#define TFT_DC   27  // Data Command control pin
//#define TFT_RST  33  // Reset pin (could connect to Arduino RESET pin)
//#define TFT_BL   22  // LED back-light

//#define TOUCH_CS 33     // Chip select pin (T_CS) of touch screen

//#define TFT_WR 22    // Write strobe for modified Raspberry Pi TFT only

// For the M5Stack module use these #define lines
//#define TFT_MISO 19
//#define TFT_MOSI 23
//#define TFT_SCLK 18
//#define TFT_CS   14  // Chip select control pin
//#define TFT_DC   27  // Data Command control pin
//#define TFT_RST  33  // Reset pin (could connect to Arduino RESET pin)
//#define TFT_BL   32  // LED back-light (required for M5Stack)

// ######       EDIT THE PINs BELOW TO SUIT YOUR ESP32 PARALLEL TFT SETUP        ######

// The library supports 8-bit parallel TFTs with the ESP32, the pin
// selection below is compatible with ESP32 boards in UNO format.
// Wemos D32 boards need to be modified, see diagram in Tools folder.
// Only ILI9481 and ILI9341 based displays have been tested!

// Parallel bus is only supported for the STM32 and ESP32
// Example below is for ESP32 Parallel interface with UNO displays

// Tell the library to use 8-bit parallel mode (otherwise SPI is assumed)
//#define TFT_PARALLEL_8_BIT

// The ESP32 and TFT the pins used for testing are:
//#define TFT_CS   33  // Chip select control pin (library pulls permanently low
//#define TFT_DC   15  // Data Command control pin - must use a pin in the range 0-31
//#define TFT_RST  32  // Reset pin, toggles on startup

//#define TFT_WR    4  // Write strobe control pin - must use a pin in the range 0-31
//#define TFT_RD    2  // Read strobe control pin

//#define TFT_D0   12  // Must use pins in the range 0-31 for the data bus
//#define TFT_D1   13  // so a single register write sets/clears all bits.
//#define TFT_D2   26  // Pins can be randomly assigned, this does not affect
//#define TFT_D3   25  // TFT screen update performance.
//#define TFT_D4   17
//#define TFT_D5   16
//#define TFT_D6   27
//#define TFT_D7   14

// ######       EDIT THE PINs BELOW TO SUIT YOUR STM32 SPI TFT SETUP        ######

// The TFT can be connected to SPI port 1 or 2
//#define TFT_SPI_PORT 1 // SPI port 1 maximum clock rate is 55MHz
//#define TFT_MOSI PA7
//#define TFT_MISO PA6
//#define TFT_SCLK PA5

//#define TFT_SPI_PORT 2 // SPI port 2 maximum clock rate is 27MHz
//#define TFT_MOSI PB15
//#define TFT_MISO PB14
//#define TFT_SCLK PB13

// Can use Ardiuno pin references, arbitrary allocation, TFT_eSPI controls chip select
//#define TFT_CS   D5 // Chip select control pin to TFT CS
//#define TFT_DC   D6 // Data Command control pin to TFT DC (may be labelled RS = Register Select)
//#define TFT_RST  D7 // Reset pin to TFT RST (or RESET)
// OR alternatively, we can use STM32 port reference names PXnn
//#define TFT_CS   PE11 // Nucleo-F767ZI equivalent of D5
//#define TFT_DC   PE9  // Nucleo-F767ZI equivalent of D6
//#define TFT_RST  PF13 // Nucleo-F767ZI equivalent of D7

//#define TFT_RST  -1   // Set TFT_RST to -1 if the display RESET is connected to processor reset
                        // Use an Arduino pin for initial testing as connecting to processor reset
                        // may not work (pulse too short at power up?)

// ##################################################################################
//
// Section 3. Define the fonts that are to be used here
//
// ##################################################################################

// Comment out the #defines below with // to stop that font being loaded
// The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
// normally necessary. If all fonts are loaded the extra FLASH space required is
// about 17Kbytes. To save FLASH space only enable the fonts you need!

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Comment out the #define below to stop the SPIFFS filing system and smooth font code being loaded
// this will save ~20kbytes of FLASH
#define SMOOTH_FONT


// ##################################################################################
//
// Section 4. Other options
//
// ##################################################################################

// For RP2040 processor and SPI displays, uncomment the following line to use the PIO interface.
//#define RP2040_PIO_SPI // Leave commented out to use standard RP2040 SPI port interface

// For RP2040 processor and 8 or 16-bit parallel displays:
// The parallel interface write cycle period is derived from a division of the CPU clock
// speed so scales with the processor clock. This means that the divider ratio may need
// to be increased when overclocking. It may also need to be adjusted dependant on the
// display controller type (ILI94341, HX8357C etc.). If RP2040_PIO_CLK_DIV is not defined
// the library will set default values which may not suit your display.
// The display controller data sheet will specify the minimum write cycle period. The
// controllers often work reliably for shorter periods, however if the period is too short
// the display may not initialise or graphics will become corrupted.
// PIO write cycle frequency = (CPU clock/(4 * RP2040_PIO_CLK_DIV))
//#define RP2040_PIO_CLK_DIV 1 // 32ns write cycle at 125MHz CPU clock
//#define RP2040_PIO_CLK_DIV 2 // 64ns write cycle at 125MHz CPU clock
//#define RP2040_PIO_CLK_DIV 3 // 96ns write cycle at 125MHz CPU clock

// For the RP2040 processor define the SPI port channel used (default 0 if undefined)
//#define TFT_SPI_PORT 1 // Set to 0 if SPI0 pins are used, or 1 if spi1 pins used

// For the STM32 processor define the SPI port channel used (default 1 if undefined)
//#define TFT_SPI_PORT 2 // Set to 1 for SPI port 1, or 2 for SPI port 2

// Define the SPI clock frequency, this affects the graphics rendering speed. Too
// fast and the TFT driver will not keep up and display corruption appears.
// With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
// With a ST7735 display more than 27MHz may not work (spurious pixels and lines)
// With an ILI9163 display 27 MHz works OK.

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY  20000000
//#define SPI_FREQUENCY  27000000
// #define SPI_FREQUENCY  40000000
#define SPI_FREQUENCY  55000000 // STM32 SPI1 only (SPI2 maximum is 27MHz)
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
#define SPI_TOUCH_FREQUENCY  2500000

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
#define USE_HSPI_PORT

// Comment out the following #define if "SPI Transactions" do not need to be
// supported. When commented out the code size will be smaller and sketches will
// run slightly faster, so leave it commented out unless you need it!

// Transaction support is needed to work with SD library but not needed with TFT_SdFat
// Transaction support is required if other SPI devices are connected.

// Transactions are automatically enabled by the library for an ESP32 (to use HAL mutex)
// so changing it here has no effect

// #define SUPPORT_TRANSACTIONS

//end User_Setup.h 

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// tft print test ////////////////////////////////////////
///////////////////////////////////// file->example\tft_eSPI\TFT_print_Test.ino //////////////////////
/*  
 Test the tft.print() viz. embedded tft.write() function

 This sketch used font 2, 4, 7

 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
 */


#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>

#define TFT_GREY 0x5AEB // New colour

TFT_eSPI tft = TFT_eSPI();  // Invoke library


void setup(void) {
  tft.init();
  tft.setRotation(2);
}

void loop() {
  
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_GREY);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line is there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);
  // Set the font colour to be white with a black background, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);  tft.setTextSize(1);
  // We can now plot text on screen using the "print" class
  tft.println("Hello World!");
  
  // Set the font colour to be yellow with no background, set to font 7
  tft.setTextColor(TFT_YELLOW); tft.setTextFont(7);
  tft.println(1234.56);
  
  // Set the font colour to be red with black background, set to font 4
  tft.setTextColor(TFT_RED,TFT_BLACK);    tft.setTextFont(4);
  //tft.println(3735928559L, HEX); // Should print DEADBEEF

  // Set the font colour to be green with black background, set to font 4
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(4);
  tft.println("Groop");
  tft.println("I implore thee,");

  // Change to font 2
  tft.setTextFont(2);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  // This next line is deliberately made too long for the display width to test
  // automatic text wrapping onto the next line
  tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");
  
  // Test some print formatting functions
  float fnumber = 123.45;
   // Set the font colour to be blue with no background, set to font 4
  tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
  tft.print("Float = "); tft.println(fnumber);           // Print floating point number
  tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
  tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
  delay(10000);
}



//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////// esp32 2.8inch TFT_eSPI + xpt2046 test cal /////////////////////////////////////

/*
  Sketch to generate the setup() calibration values, these are reported
  to the Serial Monitor.

  The sketch has been tested on the ESP8266 and screen with XPT2046 driver.
*/
#include <XPT2046_Touchscreen.h>
#include <SPI.h>
#include <TFT_eSPI.h>      // Hardware-specific library

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
SPIClass TouchSpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

bool pressed=0;
uint16_t x = 0, y = 0 ,x_old,y_old; // To store the touch coordinates
//------------------------------------------------------------------------------------------

void setup() 
{
  // Use serial port
  Serial.begin(115200);

  // Initialise the TFT screen
  tft.init();

  // Set the rotation to the orientation you wish to use in your project before calibration
  // (the touch coordinates returned then correspond to that rotation only)
  tft.setRotation(1);
  
  TouchSpi.begin(TOUCH_CLK, TOUCH_MISO, TOUCH_MOSI, TOUCH_CS);
  ts.begin(TouchSpi);
  ts.setRotation(1);

  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  tft.drawCentreString("Touch screen to test!",tft.width()/2, tft.height()/2, 2);
}

//------------------------------------------------------------------------------------------

void loop(void) 
{
  if (ts.tirqTouched()) 
  {
    if (ts.touched()) 
    {
      TS_Point p = ts.getPoint();
      /*
      Serial.print("Pressure = ");
      Serial.println(p.z);
      */
      x=p.x;
      y=p.y;
      Serial.print("raw x,y = ");
      Serial.print(x);
      Serial.print(",");
      Serial.println(y);
      
      x=map(x,225,3673,0,320);
      y=map(y,324,3761,0,240);
      Serial.print("x,y = ");
      Serial.print(x);
      Serial.print(",");
      Serial.println(y);
      pressed=1;
    }
  }  
  // Pressed will be set true is there is a valid touch on the screen
  //bool pressed = tft.getTouch(&x, &y);

  // Draw a white spot at the detected coordinates
  if (pressed) 
  {
    tft.fillCircle(x_old,y_old, 2, TFT_BLACK);
    tft.fillCircle(x,y, 2, TFT_WHITE);
    /*Serial.print("x,y = ");
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
    */
    x_old=x;
    y_old=y;
    pressed=0;
  }
}

//------------------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// lv_conf.h ///////////////////////////////////////////////////////////

/**
 * @file lv_conf.h
 * Configuration file for v9.5.0
 */

/*
 * Copy this file as `lv_conf.h`
 * 1. simply next to `lvgl` folder
 * 2. or to any other place and
 *    - define `LV_CONF_INCLUDE_SIMPLE`;
 *    - add the path as an include path.
 */

/* clang-format off */
#if 1 /* Set this to "1" to enable content */

#ifndef LV_CONF_H
#define LV_CONF_H

/* If you need to include anything here, do it inside the `__ASSEMBLY__` guard */
#if  0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*====================
   COLOR SETTINGS
 *====================*/

/** Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888) */
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
#define LV_USE_STDLIB_STRING    LV_STDLIB_BUILTIN

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_BUILTIN

#define LV_STDINT_INCLUDE       <stdint.h>
#define LV_STDDEF_INCLUDE       <stddef.h>
#define LV_STDBOOL_INCLUDE      <stdbool.h>
#define LV_INTTYPES_INCLUDE     <inttypes.h>
#define LV_LIMITS_INCLUDE       <limits.h>
#define LV_STDARG_INCLUDE       <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    /** Size of memory available for `lv_malloc()` in bytes (>= 2kB) */
    #define LV_MEM_SIZE (64 * 1024U)          /**< [bytes] */

    /** Size of the memory expand for `lv_malloc()` in bytes */
    #define LV_MEM_POOL_EXPAND_SIZE 0

    /** Set an address for the memory pool instead of allocating it as a normal array. Can be in external SRAM too. */
    #define LV_MEM_ADR 0     /**< 0: unused*/
    /* Instead of an address give a memory allocator that will be called to get a memory pool for LVGL. E.g. my_malloc */
    #if LV_MEM_ADR == 0
        #undef LV_MEM_POOL_INCLUDE
        #undef LV_MEM_POOL_ALLOC
    #endif
#endif  /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/

/** Default display refresh, input device read and animation step period. */
#define LV_DEF_REFR_PERIOD  33      /**< [ms] */

/** Default Dots Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 * (Not so important, you can adjust it to modify default sizes and spaces.) */
#define LV_DPI_DEF 130              /**< [px/inch] */

/*=================
 * OPERATING SYSTEM
 *=================*/
/** Select operating system to use. Possible options:
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_SDL2
 * - LV_OS_CUSTOM */
#define LV_USE_OS   LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
    #define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif
#if LV_USE_OS == LV_OS_FREERTOS
    /*
     * Unblocking an RTOS task with a direct notification is 45% faster and uses less RAM
     * than unblocking a task using an intermediary object such as a binary semaphore.
     * RTOS task notifications can only be used when there is only one task that can be the recipient of the event.
     */
    #define LV_USE_FREERTOS_TASK_NOTIFY 1
#endif

/*========================
 * RENDERING CONFIGURATION
 *========================*/

/** Align stride of all layers and images to this bytes */
#define LV_DRAW_BUF_STRIDE_ALIGN                1

/** Align start address of draw_buf addresses to this bytes*/
#define LV_DRAW_BUF_ALIGN                       4

/** Using matrix for transformations.
 * Requirements:
 * - `LV_USE_MATRIX = 1`.
 * - Rendering engine needs to support 3x3 matrix transformations. */
#define LV_DRAW_TRANSFORM_USE_MATRIX            0

/* If a widget has `style_opa < 255` (not `bg_opa`, `text_opa` etc) or not NORMAL blend mode
 * it is buffered into a "simple" layer before rendering. The widget can be buffered in smaller chunks.
 * "Transformed layers" (if `transform_angle/zoom` are set) use larger buffers
 * and can't be drawn in chunks. */

/** The target buffer size for simple layer chunks. */
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE    (24 * 1024)    /**< [bytes]*/

/* Limit the max allocated memory for simple and transformed layers.
 * It should be at least `LV_DRAW_LAYER_SIMPLE_BUF_SIZE` sized but if transformed layers are also used
 * it should be enough to store the largest widget too (width x height x 4 area).
 * Set it to 0 to have no limit. */
#define LV_DRAW_LAYER_MAX_MEMORY 0  /**< No limit by default [bytes]*/

/** Stack size of drawing thread.
 * NOTE: If FreeType or ThorVG is enabled, it is recommended to set it to 32KB or more.
 */
#define LV_DRAW_THREAD_STACK_SIZE    (8 * 1024)         /**< [bytes]*/

/** Thread priority of the drawing task.
 *  Higher values mean higher priority.
 *  Can use values from lv_thread_prio_t enum in lv_os.h: LV_THREAD_PRIO_LOWEST,
 *  LV_THREAD_PRIO_LOW, LV_THREAD_PRIO_MID, LV_THREAD_PRIO_HIGH, LV_THREAD_PRIO_HIGHEST
 *  Make sure the priority value aligns with the OS-specific priority levels.
 *  On systems with limited priority levels (e.g., FreeRTOS), a higher value can improve
 *  rendering performance but might cause other tasks to starve. */
#define LV_DRAW_THREAD_PRIO LV_THREAD_PRIO_HIGH

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1
    /*
     * Selectively disable color format support in order to reduce code size.
     * NOTE: some features use certain color formats internally, e.g.
     * - gradients use RGB888
     * - bitmaps with transparency may use ARGB8888
     */
    #define LV_DRAW_SW_SUPPORT_RGB565       1
    #define LV_DRAW_SW_SUPPORT_RGB565_SWAPPED       1
    #define LV_DRAW_SW_SUPPORT_RGB565A8     1
    #define LV_DRAW_SW_SUPPORT_RGB888       1
    #define LV_DRAW_SW_SUPPORT_XRGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888_PREMULTIPLIED 1
    #define LV_DRAW_SW_SUPPORT_L8           1
    #define LV_DRAW_SW_SUPPORT_AL88         1
    #define LV_DRAW_SW_SUPPORT_A8           1
    #define LV_DRAW_SW_SUPPORT_I1           1

    /* The threshold of the luminance to consider a pixel as
     * active in indexed color format */
    #define LV_DRAW_SW_I1_LUM_THRESHOLD 127

    /** Set number of draw units.
     *  - > 1 requires operating system to be enabled in `LV_USE_OS`.
     *  - > 1 means multiple threads will render the screen in parallel. */
    #define LV_DRAW_SW_DRAW_UNIT_CNT    1

    /** Use Arm-2D to accelerate software (sw) rendering. */
    #define LV_USE_DRAW_ARM2D_SYNC      0

    /** Enable native helium assembly to be compiled. */
    #define LV_USE_NATIVE_HELIUM_ASM    0

    /**
     * - 0: Use a simple renderer capable of drawing only simple rectangles with gradient, images, text, and straight lines only.
     * - 1: Use a complex renderer capable of drawing rounded corners, shadow, skew lines, and arcs too. */
    #define LV_DRAW_SW_COMPLEX          1

    #if LV_DRAW_SW_COMPLEX == 1
        /** Allow buffering some shadow calculation.
         *  LV_DRAW_SW_SHADOW_CACHE_SIZE is the maximum shadow size to buffer, where shadow size is
         *  `shadow_width + radius`.  Caching has LV_DRAW_SW_SHADOW_CACHE_SIZE^2 RAM cost. */
        #define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

        /** Set number of maximally-cached circle data.
         *  The circumference of 1/4 circle are saved for anti-aliasing.
         *  `radius * 4` bytes are used per circle (the most often used radiuses are saved).
         *  - 0: disables caching */
        #define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
    #endif

    #define  LV_USE_DRAW_SW_ASM     LV_DRAW_SW_ASM_NONE

    #if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
        #define  LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
    #endif

    /** Enable drawing complex gradients in software: linear at an angle, radial or conical */
    #define LV_USE_DRAW_SW_COMPLEX_GRADIENTS    0

#endif

/*Use TSi's aka (Think Silicon) NemaGFX */
#define LV_USE_NEMA_GFX 0

#if LV_USE_NEMA_GFX
    /** Select which NemaGFX static library headers to use. Possible options:
     * - LV_NEMA_LIB_NONE           an alias of LV_NEMA_LIB_M33_REVC
     * - LV_NEMA_LIB_M33_REVC
     * - LV_NEMA_LIB_M33_NEMAPVG
     * - LV_NEMA_LIB_M55
     * - LV_NEMA_LIB_M7
     * You must also take care to link the correct corresponding static library
     * in libs/nema_gfx/lib/core/
     */
    #define LV_USE_NEMA_LIB LV_NEMA_LIB_NONE

    /** Select which NemaGFX HAL to use. Possible options:
     * - LV_NEMA_HAL_CUSTOM
     * - LV_NEMA_HAL_STM32 */
    #define LV_USE_NEMA_HAL LV_NEMA_HAL_CUSTOM
    #if LV_USE_NEMA_HAL == LV_NEMA_HAL_STM32
        #define LV_NEMA_STM32_HAL_INCLUDE <stm32u5xx_hal.h>

        /** Set it to a value like __attribute__((section("Nemagfx_Memory_Pool_Buffer")))
         * and define the section in the linker script if you need the GPU memory to
         * be, e.g. in a region where accesses will not be cached.
         */
        #define LV_NEMA_STM32_HAL_ATTRIBUTE_POOL_MEM
    #endif

    /*Enable Vector Graphics Operations. Available only if NemaVG library is present*/
    #define LV_USE_NEMA_VG 0
    #if LV_USE_NEMA_VG
        /*Define application's resolution used for VG related buffer allocation */
        #define LV_NEMA_GFX_MAX_RESX 800
        #define LV_NEMA_GFX_MAX_RESY 600
    #endif
#endif

/** Use NXP's PXP on iMX RTxxx platforms. */
#define LV_USE_PXP 0

#if LV_USE_PXP
    /** Use PXP for drawing.*/
    #define LV_USE_DRAW_PXP 1

    /** Use PXP to rotate display.*/
    #define LV_USE_ROTATE_PXP 0

    #if LV_USE_DRAW_PXP && LV_USE_OS
        /** Use additional draw thread for PXP processing.*/
        #define LV_USE_PXP_DRAW_THREAD 1
    #endif

    /** Enable PXP asserts. */
    #define LV_USE_PXP_ASSERT 0
#endif

/** Use NXP's G2D on MPU platforms. */
#define LV_USE_G2D 0

#if LV_USE_G2D
    /** Use G2D for drawing. **/
    #define LV_USE_DRAW_G2D 1

    /** Use G2D to rotate display. **/
    #define LV_USE_ROTATE_G2D 0

    /** Maximum number of buffers that can be stored for G2D draw unit.
     *  Includes the frame buffers and assets. */
    #define LV_G2D_HASH_TABLE_SIZE 50

    #if LV_USE_DRAW_G2D && LV_USE_OS
        /** Use additional draw thread for G2D processing.*/
        #define LV_USE_G2D_DRAW_THREAD 1
    #endif

    /** Enable G2D asserts. */
    #define LV_USE_G2D_ASSERT 0
#endif

/** Use Renesas Dave2D on RA  platforms. */
#define LV_USE_DRAW_DAVE2D 0

/** Draw using cached SDL textures*/
#define LV_USE_DRAW_SDL 0

/** Use VG-Lite GPU. */
#define LV_USE_DRAW_VG_LITE 0
#if LV_USE_DRAW_VG_LITE
    /** Enable VG-Lite custom external 'gpu_init()' function */
    #define LV_VG_LITE_USE_GPU_INIT 0

    /** Enable VG-Lite assert. */
    #define LV_VG_LITE_USE_ASSERT 0

    /** VG-Lite flush commit trigger threshold. GPU will try to batch these many draw tasks. */
    #define LV_VG_LITE_FLUSH_MAX_COUNT 8

    /** Enable border to simulate shadow.
     *  NOTE: which usually improves performance,
     *  but does not guarantee the same rendering quality as the software. */
    #define LV_VG_LITE_USE_BOX_SHADOW 1

    /** VG-Lite gradient maximum cache number.
     *  @note  The memory usage of a single gradient image is 4K bytes. */
    #define LV_VG_LITE_GRAD_CACHE_CNT 32

    /** VG-Lite stroke maximum cache number. */
    #define LV_VG_LITE_STROKE_CACHE_CNT 32

    /** VG-Lite unaligned bitmap font maximum cache number. */
    #define LV_VG_LITE_BITMAP_FONT_CACHE_CNT 256

    /** Remove VLC_OP_CLOSE path instruction (Workaround for NXP) **/
    #define LV_VG_LITE_DISABLE_VLC_OP_CLOSE 0

    /** Disable blit rectangular offset to resolve certain hardware errors. */
    #define LV_VG_LITE_DISABLE_BLIT_RECT_OFFSET 0

    /** Disable linear gradient extension for some older versions of drivers. */
    #define LV_VG_LITE_DISABLE_LINEAR_GRADIENT_EXT 0

    /** Maximum path dump print length (in points) */
    #define LV_VG_LITE_PATH_DUMP_MAX_LEN 1000

    /** Enable usage of the LVGL's built-in vg_lite driver */
    #define LV_USE_VG_LITE_DRIVER  0
    #if LV_USE_VG_LITE_DRIVER
        /** Used to pick the correct GPU series folder valid options are gc255, gc355 and gc555*/
        #define LV_VG_LITE_HAL_GPU_SERIES gc255

        /** Used to pick the correct GPU revision header it depends on the vendor */
        #define LV_VG_LITE_HAL_GPU_REVISION 0x40

        /** Base memory address of the GPU IP it depends on SoC,
         *  default value is for NXP based devices */
        #define LV_VG_LITE_HAL_GPU_BASE_ADDRESS 0x40240000
    #endif /*LV_USE_VG_LITE_DRIVER*/

    /** Use ThorVG (a software vector library) as VG-Lite driver to allow testing VGLite on PC
     *  Requires: LV_USE_THORVG_INTERNAL or LV_USE_THORVG_EXTERNAL */
    #define LV_USE_VG_LITE_THORVG   0
    #if LV_USE_VG_LITE_THORVG
        /** Enable LVGL's blend mode support */
        #define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0

        /** Enable YUV color format support */
        #define LV_VG_LITE_THORVG_YUV_SUPPORT 0

        /** Enable Linear gradient extension support */
        #define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0

        /** Enable alignment on 16 pixels */
        #define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1

        /** Buffer address alignment */
        #define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64

        /** Enable multi-thread render */
        #define LV_VG_LITE_THORVG_THREAD_RENDER 0
    #endif /*LV_USE_VG_LITE_THORVG*/
#endif

/** Accelerate blends, fills, etc. with STM32 DMA2D */
#define LV_USE_DRAW_DMA2D 0
#if LV_USE_DRAW_DMA2D
    #define LV_DRAW_DMA2D_HAL_INCLUDE "stm32h7xx_hal.h"

    /* if enabled, the user is required to call `lv_draw_dma2d_transfer_complete_interrupt_handler`
     * upon receiving the DMA2D global interrupt
     */
    #define LV_USE_DRAW_DMA2D_INTERRUPT 0
#endif

/** Draw using cached OpenGLES textures. Requires LV_USE_OPENGLES */
#define LV_USE_DRAW_OPENGLES 0
#if LV_USE_DRAW_OPENGLES
    #define LV_DRAW_OPENGLES_TEXTURE_CACHE_COUNT 64
#endif

/** Draw using espressif PPA accelerator */
#define LV_USE_PPA  0
#if LV_USE_PPA
    #define LV_USE_PPA_IMG      0
    #define LV_PPA_BURST_LENGTH    128
#endif

/* Use EVE FT81X GPU. */
#define LV_USE_DRAW_EVE 0
#if LV_USE_DRAW_EVE
    /* EVE_GEN value: 2, 3, or 4 */
    #define LV_DRAW_EVE_EVE_GENERATION 4

    /* The maximum number of bytes to buffer before a single SPI transmission.
     * Set it to 0 to disable write buffering.
     */
    #define LV_DRAW_EVE_WRITE_BUFFER_SIZE 2048
#endif

/** Use NanoVG Renderer
 * - Requires LV_USE_NANOVG, LV_USE_MATRIX.
 */
#define LV_USE_DRAW_NANOVG 0
#if LV_USE_DRAW_NANOVG
    /** Select OpenGL backend for NanoVG:
     * - LV_NANOVG_BACKEND_GL2:   OpenGL 2.0
     * - LV_NANOVG_BACKEND_GL3:   OpenGL 3.0+
     * - LV_NANOVG_BACKEND_GLES2: OpenGL ES 2.0
     * - LV_NANOVG_BACKEND_GLES3: OpenGL ES 3.0+
     */
    #define LV_NANOVG_BACKEND   LV_NANOVG_BACKEND_GLES2

    /** Draw image texture cache count. */
    #define LV_NANOVG_IMAGE_CACHE_CNT 128

    /** Draw letter texture cache count. */
    #define LV_NANOVG_LETTER_CACHE_CNT 512
#endif

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Logging
 *-----------*/

/** Enable log module */
#define LV_USE_LOG 1
#if LV_USE_LOG
    /** Set value to one of the following levels of logging detail:
     *  - LV_LOG_LEVEL_TRACE    Log detailed information.
     *  - LV_LOG_LEVEL_INFO     Log important events.
     *  - LV_LOG_LEVEL_WARN     Log if something unwanted happened but didn't cause a problem.
     *  - LV_LOG_LEVEL_ERROR    Log only critical issues, when system may fail.
     *  - LV_LOG_LEVEL_USER     Log only custom log messages added by the user.
     *  - LV_LOG_LEVEL_NONE     Do not log anything. */
    #define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

    /** - 1: Print log with 'printf';
     *  - 0: User needs to register a callback with `lv_log_register_print_cb()`. */
    #define LV_LOG_PRINTF 1

    /** Set callback to print logs.
     *  E.g `my_print`. The prototype should be `void my_print(lv_log_level_t level, const char * buf)`.
     *  Can be overwritten by `lv_log_register_print_cb`. */
    //#define LV_LOG_PRINT_CB log_print

    /** - 1: Enable printing timestamp;
     *  - 0: Disable printing timestamp. */
    #define LV_LOG_USE_TIMESTAMP 1

    /** - 1: Print file and line number of the log;
     *  - 0: Do not print file and line number of the log. */
    #define LV_LOG_USE_FILE_LINE 1

    /* Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs. */
    #define LV_LOG_TRACE_MEM        1   /**< Enable/disable trace logs in memory operations. */
    #define LV_LOG_TRACE_TIMER      1   /**< Enable/disable trace logs in timer operations. */
    #define LV_LOG_TRACE_INDEV      1   /**< Enable/disable trace logs in input device operations. */
    #define LV_LOG_TRACE_DISP_REFR  1   /**< Enable/disable trace logs in display re-draw operations. */
    #define LV_LOG_TRACE_EVENT      1   /**< Enable/disable trace logs in event dispatch logic. */
    #define LV_LOG_TRACE_OBJ_CREATE 1   /**< Enable/disable trace logs in object creation (core `obj` creation plus every widget). */
    #define LV_LOG_TRACE_LAYOUT     1   /**< Enable/disable trace logs in flex- and grid-layout operations. */
    #define LV_LOG_TRACE_ANIM       1   /**< Enable/disable trace logs in animation logic. */
    #define LV_LOG_TRACE_CACHE      1   /**< Enable/disable trace logs in cache operations. */
#endif  /*LV_USE_LOG*/

/*-------------
 * Asserts
 *-----------*/

/* Enable assertion failures if an operation fails or invalid data is found.
 * If LV_USE_LOG is enabled, an error message will be printed on failure. */
#define LV_USE_ASSERT_NULL          1   /**< Check if the parameter is NULL. (Very fast, recommended) */
#define LV_USE_ASSERT_MALLOC        1   /**< Checks is the memory is successfully allocated or no. (Very fast, recommended) */
#define LV_USE_ASSERT_STYLE         0   /**< Check if the styles are properly initialized. (Very fast, recommended) */
#define LV_USE_ASSERT_MEM_INTEGRITY 0   /**< Check the integrity of `lv_mem` after critical operations. (Slow) */
#define LV_USE_ASSERT_OBJ           0   /**< Check the object's type and existence (e.g. not deleted). (Slow) */

/** Add a custom handler when assert happens e.g. to restart MCU. */
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);     /**< Halt by default */

/*-------------
 * Debug
 *-----------*/

/** 1: Draw random colored rectangles over the redrawn areas. */
#define LV_USE_REFR_DEBUG 0

/** 1: Draw a red overlay for ARGB layers and a green overlay for RGB layers*/
#define LV_USE_LAYER_DEBUG 0

/** 1: Adds the following behaviors for debugging:
 *  - Draw overlays with different colors for each draw_unit's tasks.
 *  - Draw index number of draw unit on white background.
 *  - For layers, draws index number of draw unit on black background. */
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
    /** Header to include for custom 'lv_global' function" */
    #define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/** Default cache size in bytes.
 *  Used by image decoders such as `lv_lodepng` to keep the decoded image in memory.
 *  If size is not set to 0, the decoder will fail to decode when the cache is full.
 *  If size is 0, the cache function is not enabled and the decoded memory will be
 *  released immediately after use. */
#define LV_CACHE_DEF_SIZE       0

/** Default number of image header cache entries. The cache is used to store the headers of images
 *  The main logic is like `LV_CACHE_DEF_SIZE` but for image headers. */
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/** Number of stops allowed per gradient. Increase this to allow more stops.
 *  This adds (sizeof(lv_color_t) + 1) bytes per additional stop. */
#define LV_GRADIENT_MAX_STOPS   2

/** Adjust color mix functions rounding. GPUs might calculate color mix (blending) differently.
 *  - 0:   round down,
 *  - 64:  round up from x.75,
 *  - 128: round up from half,
 *  - 192: round up from x.25,
 *  - 254: round up */
#define LV_COLOR_MIX_ROUND_OFS  0

/** Add 2 x 32-bit variables to each `lv_obj_t` to speed up getting style properties */
#define LV_OBJ_STYLE_CACHE      0

/** Add `id` field to `lv_obj_t` */
#define LV_USE_OBJ_ID           0

/**  Enable support widget names*/
#define LV_USE_OBJ_NAME         0

/** Automatically assign an ID when obj is created */
#define LV_OBJ_ID_AUTO_ASSIGN   LV_USE_OBJ_ID

/** Use builtin obj ID handler functions:
* - lv_obj_assign_id:       Called when a widget is created. Use a separate counter for each widget class as an ID.
* - lv_obj_id_compare:      Compare the ID to decide if it matches with a requested value.
* - lv_obj_stringify_id:    Return string-ified identifier, e.g. "button3".
* - lv_obj_free_id:         Does nothing, as there is no memory allocation for the ID.
* When disabled these functions needs to be implemented by the user.*/
#define LV_USE_OBJ_ID_BUILTIN   1

/** Use obj property set/get API. */
#define LV_USE_OBJ_PROPERTY 0

/** Enable property name support. */
#define LV_USE_OBJ_PROPERTY_NAME 1

/* Enable the multi-touch gesture recognition feature */
/* Gesture recognition requires the use of floats */
#define LV_USE_GESTURE_RECOGNITION 0

/*=====================
 *  COMPILER SETTINGS
 *====================*/

/** For big endian systems set to 1 */
#define LV_BIG_ENDIAN_SYSTEM 0

/** Define a custom attribute for `lv_tick_inc` function */
#define LV_ATTRIBUTE_TICK_INC

/** Define a custom attribute for `lv_timer_handler` function */
#define LV_ATTRIBUTE_TIMER_HANDLER

/** Define a custom attribute for `lv_display_flush_ready` function */
#define LV_ATTRIBUTE_FLUSH_READY

/** Align VG_LITE buffers on this number of bytes.
 *  @note  vglite_src_buf_aligned() uses this value to validate alignment of passed buffer pointers. */
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/** Will be added where memory needs to be aligned (with -Os data might not be aligned to boundary by default).
 *  E.g. __attribute__((aligned(4)))*/
#define LV_ATTRIBUTE_MEM_ALIGN

/** Attribute to mark large constant arrays, for example for font bitmaps */
#define LV_ATTRIBUTE_LARGE_CONST

/** Compiler prefix for a large array declaration in RAM */
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/** Place performance critical functions into a faster memory (e.g RAM) */
#define LV_ATTRIBUTE_FAST_MEM

/** Export integer constant to binding. This macro is used with constants in the form of LV_<CONST> that
 *  should also appear on LVGL binding API such as MicroPython. */
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning  /**< The default value just prevents GCC warning */

/** Prefix all global extern data with this */
#define LV_ATTRIBUTE_EXTERN_DATA

/** Use `float` as `lv_value_precise_t` */
#define LV_USE_FLOAT            0

/** Enable matrix support
 *  - Requires `LV_USE_FLOAT = 1` */
#define LV_USE_MATRIX           0

/** Include `lvgl_private.h` in `lvgl.h` to access internal data and functions by default */
#ifndef LV_USE_PRIVATE_API
    #define LV_USE_PRIVATE_API  0
#endif

/*==================
 *   FONT USAGE
 *===================*/

/* Montserrat fonts with ASCII range and some symbols using bpp = 4
 * https://fonts.google.com/specimen/Montserrat */
#define LV_FONT_MONTSERRAT_8  1
#define LV_FONT_MONTSERRAT_10 1
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 1
#define LV_FONT_MONTSERRAT_28 1
#define LV_FONT_MONTSERRAT_30 1
#define LV_FONT_MONTSERRAT_32 1
#define LV_FONT_MONTSERRAT_34 1
#define LV_FONT_MONTSERRAT_36 1
#define LV_FONT_MONTSERRAT_38 1
#define LV_FONT_MONTSERRAT_40 1
#define LV_FONT_MONTSERRAT_42 1
#define LV_FONT_MONTSERRAT_44 1
#define LV_FONT_MONTSERRAT_46 1
#define LV_FONT_MONTSERRAT_48 1

/* Demonstrate special features */
#define LV_FONT_MONTSERRAT_28_COMPRESSED    0  /**< bpp = 3 */
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW    0  /**< Hebrew, Arabic, Persian letters and all their forms */
#define LV_FONT_SOURCE_HAN_SANS_SC_14_CJK   0  /**< 1338 most common CJK radicals */
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK   0  /**< 1338 most common CJK radicals */

/** Pixel perfect monospaced fonts */
#define LV_FONT_UNSCII_8  0
#define LV_FONT_UNSCII_16 0

/** Optionally declare custom fonts here.
 *
 *  You can use any of these fonts as the default font too and they will be available
 *  globally.  Example:
 *
 *  @code
 *  #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2)
 *  @endcode
 */
#define LV_FONT_CUSTOM_DECLARE

/** Always set a default font */
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/** Enable handling large font and/or fonts with a lot of characters.
 *  The limit depends on the font size, font face and bpp.
 *  A compiler error will be triggered if a font needs it. */
#define LV_FONT_FMT_TXT_LARGE 0

/** Enables/disables support for compressed fonts. */
#define LV_USE_FONT_COMPRESSED 0

/** Enable drawing placeholders when glyph dsc is not found. */
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding.
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/** While rendering text strings, break (wrap) text on these chars. */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/** If a word is at least this long, will break wherever "prettiest".
 *  To disable, set to a value <= 0. */
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/** Minimum number of characters in a long word to put on a line before a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/** Minimum number of characters in a long word to put on a line after a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/** Support bidirectional text. Allows mixing Left-to-Right and Right-to-Left text.
 *  The direction will be processed according to the Unicode Bidirectional Algorithm:
 *  https://www.w3.org/International/articles/inline-bidi-markup/uba-basics */
#define LV_USE_BIDI 0
#if LV_USE_BIDI
    /*Set the default direction. Supported values:
    *`LV_BASE_DIR_LTR` Left-to-Right
    *`LV_BASE_DIR_RTL` Right-to-Left
    *`LV_BASE_DIR_AUTO` detect text base direction*/
    #define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/** Enable Arabic/Persian processing
 *  In these languages characters should be replaced with another form based on their position in the text */
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*The control character to use for signaling text recoloring*/
#define LV_TXT_COLOR_CMD "#"

/*==================
 * WIDGETS
 *================*/
/* Documentation for widgets can be found here: https://docs.lvgl.io/master/widgets/index.html . */

/** 1: Causes these widgets to be given default values at creation time.
 *  - lv_buttonmatrix_t:  Get default maps:  {"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}, else map not set.
 *  - lv_checkbox_t    :  String label set to "Check box", else set to empty string.
 *  - lv_dropdown_t    :  Options set to "Option 1", "Option 2", "Option 3", else no values are set.
 *  - lv_roller_t      :  Options set to "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", else no values are set.
 *  - lv_label_t       :  Text set to "Text", else empty string.
 *  - lv_arclabel_t   :  Text set to "Arced Text", else empty string.
 * */
#define LV_WIDGETS_HAS_DEFAULT_VALUE  1

#define LV_USE_ANIMIMG    1

#define LV_USE_ARC        1

#define LV_USE_ARCLABEL  1

#define LV_USE_BAR        1

#define LV_USE_BUTTON        1

#define LV_USE_BUTTONMATRIX  1

#define LV_USE_CALENDAR   1
#if LV_USE_CALENDAR
    #define LV_CALENDAR_WEEK_STARTS_MONDAY 0
    #if LV_CALENDAR_WEEK_STARTS_MONDAY
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}
    #else
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
    #endif

    #define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March",  "April", "May",  "June", "July", "August", "September", "October", "November", "December"}
    #define LV_USE_CALENDAR_HEADER_ARROW 1
    #define LV_USE_CALENDAR_HEADER_DROPDOWN 1
    #define LV_USE_CALENDAR_CHINESE 0
#endif  /*LV_USE_CALENDAR*/

#define LV_USE_CANVAS     1

#define LV_USE_CHART      1

#define LV_USE_CHECKBOX   1

#define LV_USE_DROPDOWN   1   /**< Requires: lv_label */

#define LV_USE_IMAGE      1   /**< Requires: lv_label */

#define LV_USE_IMAGEBUTTON     1

#define LV_USE_KEYBOARD   1

#define LV_USE_LABEL      1
#if LV_USE_LABEL
    #define LV_LABEL_TEXT_SELECTION 1   /**< Enable selecting text of the label */
    #define LV_LABEL_LONG_TXT_HINT 1    /**< Store some extra info in labels to speed up drawing of very long text */
    #define LV_LABEL_WAIT_CHAR_COUNT 3  /**< The count of wait chart */
#endif

#define LV_USE_LED        1

#define LV_USE_LINE       1

#define LV_USE_LIST       1

#define LV_USE_LOTTIE     0  /**< Requires: lv_canvas, thorvg */

#define LV_USE_MENU       1

#define LV_USE_MSGBOX     1

#define LV_USE_ROLLER     1   /**< Requires: lv_label */

#define LV_USE_SCALE      1

#define LV_USE_SLIDER     1   /**< Requires: lv_bar */

#define LV_USE_SPAN       1
#if LV_USE_SPAN
    /** A line of text can contain this maximum number of span descriptors. */
    #define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX    1

#define LV_USE_SPINNER    1

#define LV_USE_SWITCH     1

#define LV_USE_TABLE      1

#define LV_USE_TABVIEW    1

#define LV_USE_TEXTAREA   1   /**< Requires: lv_label */
#if LV_USE_TEXTAREA != 0
    #define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500    /**< [ms] */
#endif

#define LV_USE_TILEVIEW   1

#define LV_USE_WIN        1

#define LV_USE_3DTEXTURE  0

/*==================
 * THEMES
 *==================*/
/* Documentation for themes can be found here: https://docs.lvgl.io/master/common-widget-features/styles/styles.html#themes . */

/** A simple, impressive and very complete theme */
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
    /** 0: Light mode; 1: Dark mode */
    #define LV_THEME_DEFAULT_DARK 0

    /** 1: Enable grow on press */
    #define LV_THEME_DEFAULT_GROW 1

    /** Default transition time in ms. */
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/** A very simple theme that is a good starting point for a custom theme */
#define LV_USE_THEME_SIMPLE 1

/** A theme designed for monochrome displays */
#define LV_USE_THEME_MONO 1

/*==================
 * LAYOUTS
 *==================*/
/* Documentation for layouts can be found here: https://docs.lvgl.io/master/common-widget-features/layouts/index.html . */

/** A layout similar to Flexbox in CSS. */
#define LV_USE_FLEX 1

/** A layout similar to Grid in CSS. */
#define LV_USE_GRID 1

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/
/* Documentation for libraries can be found here: https://docs.lvgl.io/master/libs/index.html . */

/* File system interfaces for common APIs */

/** Setting a default driver letter allows skipping the driver prefix in filepaths.
 *  Documentation about how to use the below driver-identifier letters can be found at
 *  https://docs.lvgl.io/master/main-modules/fs.html#lv-fs-identifier-letters . */
#define LV_FS_DEFAULT_DRIVER_LETTER '\0'

/** API for fopen, fread, etc. */
#define LV_USE_FS_STDIO 0
#if LV_USE_FS_STDIO
    #define LV_FS_STDIO_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_STDIO_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_STDIO_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for open, read, etc. */
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
    #define LV_FS_POSIX_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_POSIX_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_POSIX_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for CreateFile, ReadFile, etc. */
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
    #define LV_FS_WIN32_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_WIN32_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_WIN32_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for FATFS (needs to be added separately). Uses f_open, f_read, etc. */
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
    #define LV_FS_FATFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_FATFS_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_FATFS_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for memory-mapped file access. */
#define LV_USE_FS_MEMFS 0
#if LV_USE_FS_MEMFS
    #define LV_FS_MEMFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
#endif

/** API for LittleFs. */
#define LV_USE_FS_LITTLEFS 0
#if LV_USE_FS_LITTLEFS
    #define LV_FS_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for Arduino LittleFs. */
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
    #define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_ARDUINO_ESP_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for Arduino Sd. */
#define LV_USE_FS_ARDUINO_SD 0
#if LV_USE_FS_ARDUINO_SD
    #define LV_FS_ARDUINO_SD_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_ARDUINO_SD_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for UEFI */
#define LV_USE_FS_UEFI 0
#if LV_USE_FS_UEFI
    #define LV_FS_UEFI_LETTER '\0'      /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
#endif

#define LV_USE_FS_FROGFS 0
#if LV_USE_FS_FROGFS
    #define LV_FS_FROGFS_LETTER '\0'
#endif

/** LODEPNG decoder library */
#define LV_USE_LODEPNG 0

/** PNG decoder(libpng) library */
#define LV_USE_LIBPNG 0

/** BMP decoder library */
#define LV_USE_BMP 0

/** JPG + split JPG decoder library.
 *  Split JPG is a custom format optimized for embedded systems. */
#define LV_USE_TJPGD 0

/** libjpeg-turbo decoder library.
 *  - Supports complete JPEG specifications and high-performance JPEG decoding. */
#define LV_USE_LIBJPEG_TURBO 0

/** WebP decoder library */
#define LV_USE_LIBWEBP 0

/** GIF decoder library */
#define LV_USE_GIF 0
#if LV_USE_GIF
    /** GIF decoder accelerate */
    #define LV_GIF_CACHE_DECODE_DATA 0
#endif

/** GStreamer library */
#define LV_USE_GSTREAMER 0

/** Decode bin images to RAM */
#define LV_BIN_DECODER_RAM_LOAD 0

/** RLE decompress library */
#define LV_USE_RLE 0

/** QR code library */
#define LV_USE_QRCODE 0

/** Barcode code library */
#define LV_USE_BARCODE 0

/** FreeType library */
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
    /** Let FreeType use LVGL memory and file porting */
    #define LV_FREETYPE_USE_LVGL_PORT 0

    /** Cache count of glyphs in FreeType, i.e. number of glyphs that can be cached.
     *  The higher the value, the more memory will be used. */
    #define LV_FREETYPE_CACHE_FT_GLYPH_CNT 256
#endif

/** Built-in TTF decoder */
#define LV_USE_TINY_TTF 0
#if LV_USE_TINY_TTF
    /* Enable loading TTF data from files */
    #define LV_TINY_TTF_FILE_SUPPORT 0
    #define LV_TINY_TTF_CACHE_GLYPH_CNT 128
    #define LV_TINY_TTF_CACHE_KERNING_CNT 256
#endif

/** Rlottie library */
#define LV_USE_RLOTTIE 0

/** Requires `LV_USE_3DTEXTURE = 1` */
#define LV_USE_GLTF  0

/** Enable Vector Graphic APIs
 *  Requires `LV_USE_MATRIX = 1`
 *  and a rendering engine supporting vector graphics, e.g.
 *  (LV_USE_DRAW_SW and LV_USE_THORVG) or LV_USE_DRAW_VG_LITE or LV_USE_NEMA_VG. */
#define LV_USE_VECTOR_GRAPHIC  0

/** Enable ThorVG (vector graphics library) from the src/libs folder.
 *  Requires LV_USE_VECTOR_GRAPHIC */
#define LV_USE_THORVG_INTERNAL 0

/** Enable ThorVG by assuming that its installed and linked to the project
 *  Requires LV_USE_VECTOR_GRAPHIC */
#define LV_USE_THORVG_EXTERNAL 0

/** Enable NanoVG (vector graphics library) */
#define LV_USE_NANOVG 0

/** Use lvgl built-in LZ4 lib */
#define LV_USE_LZ4_INTERNAL  0

/** Use external LZ4 library */
#define LV_USE_LZ4_EXTERNAL  0

/*SVG library
 *  - Requires `LV_USE_VECTOR_GRAPHIC = 1` */
#define LV_USE_SVG 0
#define LV_USE_SVG_ANIMATION 0
#define LV_USE_SVG_DEBUG 0

/** FFmpeg library for image decoding and playing videos.
 *  Supports all major image formats so do not enable other image decoder with it. */
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
    /** Dump input information to stderr */
    #define LV_FFMPEG_DUMP_FORMAT 0
    /** Use lvgl file path in FFmpeg Player widget
     *  You won't be able to open URLs after enabling this feature.
     *  Note that FFmpeg image decoder will always use lvgl file system. */
    #define LV_FFMPEG_PLAYER_USE_LV_FS 0
#endif

/*==================
 * OTHERS
 *==================*/
/* Documentation for several of the below items can be found here: https://docs.lvgl.io/master/auxiliary-modules/index.html . */

/** 1: Enable API to take snapshot for object */
#define LV_USE_SNAPSHOT 0

/** 1: Enable system monitor component */
#define LV_USE_SYSMON   0
#if LV_USE_SYSMON
    /** Get the idle percentage. E.g. uint32_t my_get_idle(void); */
    #define LV_SYSMON_GET_IDLE lv_os_get_idle_percent
    /** 1: Enable usage of lv_os_get_proc_idle_percent.*/
    #define LV_SYSMON_PROC_IDLE_AVAILABLE 0
    #if LV_SYSMON_PROC_IDLE_AVAILABLE
        /** Get the applications idle percentage.
         * - Requires `LV_USE_OS == LV_OS_PTHREAD` */
        #define LV_SYSMON_GET_PROC_IDLE lv_os_get_proc_idle_percent
    #endif

    /** 1: Show CPU usage and FPS count.
     *  - Requires `LV_USE_SYSMON = 1` */
    #define LV_USE_PERF_MONITOR 0
    #if LV_USE_PERF_MONITOR
        #define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

        /** 0: Displays performance data on the screen; 1: Prints performance data using log. */
        #define LV_USE_PERF_MONITOR_LOG_MODE 0
    #endif

    /** 1: Show used memory and memory fragmentation.
     *     - Requires `LV_USE_STDLIB_MALLOC = LV_STDLIB_BUILTIN`
     *     - Requires `LV_USE_SYSMON = 1`*/
    #define LV_USE_MEM_MONITOR 0
    #if LV_USE_MEM_MONITOR
        #define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
    #endif
#endif /*LV_USE_SYSMON*/

/** 1: Enable runtime performance profiler */
#define LV_USE_PROFILER 0
#if LV_USE_PROFILER
    /** 1: Enable the built-in profiler */
    #define LV_USE_PROFILER_BUILTIN 1
    #if LV_USE_PROFILER_BUILTIN
        /** Default profiler trace buffer size */
        #define LV_PROFILER_BUILTIN_BUF_SIZE (16 * 1024)     /**< [bytes] */
        #define LV_PROFILER_BUILTIN_DEFAULT_ENABLE 1
        #define LV_USE_PROFILER_BUILTIN_POSIX 0 /**< Enable POSIX profiler port */
    #endif

    /** Header to include for profiler */
    #define LV_PROFILER_INCLUDE "lvgl/src/misc/lv_profiler_builtin.h"

    /** Profiler start point function */
    #define LV_PROFILER_BEGIN    LV_PROFILER_BUILTIN_BEGIN

    /** Profiler end point function */
    #define LV_PROFILER_END      LV_PROFILER_BUILTIN_END

    /** Profiler start point function with custom tag */
    #define LV_PROFILER_BEGIN_TAG LV_PROFILER_BUILTIN_BEGIN_TAG

    /** Profiler end point function with custom tag */
    #define LV_PROFILER_END_TAG   LV_PROFILER_BUILTIN_END_TAG

    /*Enable layout profiler*/
    #define LV_PROFILER_LAYOUT 1

    /*Enable disp refr profiler*/
    #define LV_PROFILER_REFR 1

    /*Enable draw profiler*/
    #define LV_PROFILER_DRAW 1

    /*Enable indev profiler*/
    #define LV_PROFILER_INDEV 1

    /*Enable decoder profiler*/
    #define LV_PROFILER_DECODER 1

    /*Enable font profiler*/
    #define LV_PROFILER_FONT 1

    /*Enable fs profiler*/
    #define LV_PROFILER_FS 1

    /*Enable style profiler*/
    #define LV_PROFILER_STYLE 0

    /*Enable timer profiler*/
    #define LV_PROFILER_TIMER 1

    /*Enable cache profiler*/
    #define LV_PROFILER_CACHE 1

    /*Enable event profiler*/
    #define LV_PROFILER_EVENT 1
#endif

/** 1: Enable Monkey test */
#define LV_USE_MONKEY 0

/** 1: Enable grid navigation */
#define LV_USE_GRIDNAV 0

/** 1: Enable `lv_obj` fragment logic */
#define LV_USE_FRAGMENT 0

/** 1: Support using images as font in label or span widgets */
#define LV_USE_IMGFONT 0

/** 1: Enable an observer pattern implementation */
#define LV_USE_OBSERVER 1

/** 1: Enable Pinyin input method
 *  - Requires: lv_keyboard */
#define LV_USE_IME_PINYIN 0
#if LV_USE_IME_PINYIN
    /** 1: Use default thesaurus.
     *  @note  If you do not use the default thesaurus, be sure to use `lv_ime_pinyin` after setting the thesaurus. */
    #define LV_IME_PINYIN_USE_DEFAULT_DICT 1
    /** Set maximum number of candidate panels that can be displayed.
     *  @note  This needs to be adjusted according to size of screen. */
    #define LV_IME_PINYIN_CAND_TEXT_NUM 6

    /** Use 9-key input (k9). */
    #define LV_IME_PINYIN_USE_K9_MODE      1
    #if LV_IME_PINYIN_USE_K9_MODE == 1
        #define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
    #endif /*LV_IME_PINYIN_USE_K9_MODE*/
#endif

/** 1: Enable file explorer.
 *  - Requires: lv_table */
#define LV_USE_FILE_EXPLORER                     0
#if LV_USE_FILE_EXPLORER
    /** Maximum length of path */
    #define LV_FILE_EXPLORER_PATH_MAX_LEN        (128)
    /** Quick access bar, 1:use, 0:do not use.
     *  - Requires: lv_list */
    #define LV_FILE_EXPLORER_QUICK_ACCESS        1
#endif

/** 1: Enable Font manager */
#define LV_USE_FONT_MANAGER                     0
#if LV_USE_FONT_MANAGER

/**Font manager name max length*/
#define LV_FONT_MANAGER_NAME_MAX_LEN            32

#endif

/** Enable emulated input devices, time emulation, and screenshot compares. */
#define LV_USE_TEST 0
#if LV_USE_TEST

/** Enable `lv_test_screenshot_compare`.
 * Requires lodepng and a few MB of extra RAM. */
#define LV_USE_TEST_SCREENSHOT_COMPARE 0

#if LV_USE_TEST_SCREENSHOT_COMPARE
    /** 1: Automatically create missing reference images*/
    #define LV_TEST_SCREENSHOT_CREATE_REFERENCE_IMAGE 1
#endif /*LV_USE_TEST_SCREENSHOT_COMPARE*/

#endif /*LV_USE_TEST*/

/** 1: Enable text translation support */
#define LV_USE_TRANSLATION 0

/*1: Enable color filter style*/
#define LV_USE_COLOR_FILTER     0

/*==================
 * DEVICES
 *==================*/

/** Use SDL to open window on PC and handle mouse and keyboard. */
#define LV_USE_SDL              0
#if LV_USE_SDL
    #define LV_SDL_INCLUDE_PATH     <SDL2/SDL.h>
    #define LV_SDL_RENDER_MODE      LV_DISPLAY_RENDER_MODE_DIRECT   /**< LV_DISPLAY_RENDER_MODE_DIRECT is recommended for best performance */
    #define LV_SDL_BUF_COUNT        1    /**< 1 or 2 */
    #define LV_SDL_ACCELERATED      1    /**< 1: Use hardware acceleration*/
    #define LV_SDL_FULLSCREEN       0    /**< 1: Make the window full screen by default */
    #define LV_SDL_DIRECT_EXIT      1    /**< 1: Exit the application when all SDL windows are closed */
    #define LV_SDL_MOUSEWHEEL_MODE  LV_SDL_MOUSEWHEEL_MODE_ENCODER  /*LV_SDL_MOUSEWHEEL_MODE_ENCODER/CROWN*/
#endif

/** Use X11 to open window on Linux desktop and handle mouse and keyboard */
#define LV_USE_X11              0
#if LV_USE_X11
    #define LV_X11_DIRECT_EXIT         1  /**< Exit application when all X11 windows have been closed */
    #define LV_X11_DOUBLE_BUFFER       1  /**< Use double buffers for rendering */
    /* Select only 1 of the following render modes (LV_X11_RENDER_MODE_PARTIAL preferred!). */
    #define LV_X11_RENDER_MODE_PARTIAL 1  /**< Partial render mode (preferred) */
    #define LV_X11_RENDER_MODE_DIRECT  0  /**< Direct render mode */
    #define LV_X11_RENDER_MODE_FULL    0  /**< Full render mode */
#endif

/** Use Wayland to open a window and handle input on Linux or BSD desktops */
#define LV_USE_WAYLAND          0
#if LV_USE_WAYLAND
    #define LV_WAYLAND_DIRECT_EXIT          1     /**< 1: Exit the application when all Wayland windows are closed */
#endif

/** Driver for /dev/fb */
#define LV_USE_LINUX_FBDEV      0
#if LV_USE_LINUX_FBDEV
    #define LV_LINUX_FBDEV_BSD           0
    #define LV_LINUX_FBDEV_RENDER_MODE   LV_DISPLAY_RENDER_MODE_PARTIAL
    #define LV_LINUX_FBDEV_BUFFER_COUNT  0
    #define LV_LINUX_FBDEV_BUFFER_SIZE   60
    #define LV_LINUX_FBDEV_MMAP          1
#endif

/** Use Nuttx to open window and handle touchscreen */
#define LV_USE_NUTTX    0

#if LV_USE_NUTTX
    #define LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP 0

    /** Use independent image heap for default draw buffer */
    #define LV_NUTTX_DEFAULT_DRAW_BUF_USE_INDEPENDENT_IMAGE_HEAP    0

    #define LV_USE_NUTTX_LIBUV    0

    /** Use Nuttx custom init API to open window and handle touchscreen */
    #define LV_USE_NUTTX_CUSTOM_INIT    0

    /** Driver for /dev/lcd */
    #define LV_USE_NUTTX_LCD      0
    #if LV_USE_NUTTX_LCD
        #define LV_NUTTX_LCD_BUFFER_COUNT    0
        #define LV_NUTTX_LCD_BUFFER_SIZE     60
    #endif

    /** Driver for /dev/input */
    #define LV_USE_NUTTX_TOUCHSCREEN    0

    /** Touchscreen cursor size in pixels(<=0: disable cursor) */
    #define LV_NUTTX_TOUCHSCREEN_CURSOR_SIZE    0

    /** Driver for /dev/mouse */
    #define LV_USE_NUTTX_MOUSE    0

    /** Mouse movement step (pixels) */
    #define LV_USE_NUTTX_MOUSE_MOVE_STEP    1

    /*NuttX trace file and its path*/
    #define LV_USE_NUTTX_TRACE_FILE 0
    #if LV_USE_NUTTX_TRACE_FILE
        #define LV_NUTTX_TRACE_FILE_PATH "/data/lvgl-trace.log"
    #endif

#endif

/** Driver for /dev/dri/card */
#define LV_USE_LINUX_DRM        0

#if LV_USE_LINUX_DRM

    /* Use the MESA GBM library to allocate DMA buffers that can be
     * shared across sub-systems and libraries using the Linux DMA-BUF API.
     * The GBM library aims to provide a platform independent memory management system
     * it supports the major GPU vendors - This option requires linking with libgbm */
    #define LV_USE_LINUX_DRM_GBM_BUFFERS 0
#endif

/** Interface for TFT_eSPI */
#define LV_USE_TFT_ESPI         1

/** Interface for Lovyan_GFX */
#define LV_USE_LOVYAN_GFX         0

#if LV_USE_LOVYAN_GFX
    #define LV_LGFX_USER_INCLUDE "lv_lgfx_user.hpp"

#endif /*LV_USE_LOVYAN_GFX*/

/** Driver for evdev input devices */
#define LV_USE_EVDEV    0

/** Driver for libinput input devices */
#define LV_USE_LIBINPUT    0

#if LV_USE_LIBINPUT
    #define LV_LIBINPUT_BSD    0

    /** Full keyboard support */
    #define LV_LIBINPUT_XKB             0
    #if LV_LIBINPUT_XKB
        /** "setxkbmap -query" can help find the right values for your keyboard */
        #define LV_LIBINPUT_XKB_KEY_MAP { .rules = NULL, .model = "pc101", .layout = "us", .variant = NULL, .options = NULL }
    #endif
#endif

/* Drivers for LCD devices connected via SPI/parallel port */
#define LV_USE_ST7735        0
#define LV_USE_ST7789        1
#define LV_USE_ST7796        0
#define LV_USE_ILI9341       0
#define LV_USE_FT81X         0
#define LV_USE_NV3007        0

#if (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341 | LV_USE_NV3007)
    #define LV_USE_GENERIC_MIPI 1
#else
    #define LV_USE_GENERIC_MIPI 0
#endif

/** Driver for Renesas GLCD */
#define LV_USE_RENESAS_GLCDC    0

/** Driver for ST LTDC */
#define LV_USE_ST_LTDC    0
#if LV_USE_ST_LTDC
    /* Only used for partial. */
    #define LV_ST_LTDC_USE_DMA2D_FLUSH 0
#endif

/** Driver for NXP ELCDIF */
#define LV_USE_NXP_ELCDIF   0

/** LVGL Windows backend */
#define LV_USE_WINDOWS    0

/** LVGL UEFI backend */
#define LV_USE_UEFI 0
#if LV_USE_UEFI
    #define LV_USE_UEFI_INCLUDE "myefi.h"   /**< Header that hides the actual framework (EDK2, gnu-efi, ...) */
    #define LV_UEFI_USE_MEMORY_SERVICES 0   /**< Use the memory functions from the boot services table */
#endif

/** Use a generic OpenGL driver that can be used to embed in other applications or used with GLFW/EGL
 * - Requires LV_USE_MATRIX.
 */
#define LV_USE_OPENGLES   0
#if LV_USE_OPENGLES
    #define LV_USE_OPENGLES_DEBUG        1    /**< Enable or disable debug for opengles */
#endif

/** Use GLFW to open window on PC and handle mouse and keyboard. Requires*/
#define LV_USE_GLFW   0


/** QNX Screen display and input drivers */
#define LV_USE_QNX              0
#if LV_USE_QNX
    #define LV_QNX_BUF_COUNT        1    /**< 1 or 2 */
#endif

/** Enable or disable for external data and destructor function */
#define LV_USE_EXT_DATA   0

/*=====================
* BUILD OPTIONS
*======================*/

/** Enable examples to be built with the library. */
#define LV_BUILD_EXAMPLES 1

/** Build the demos */
#define LV_BUILD_DEMOS 1

/*===================
 * DEMO USAGE
 ====================*/

#if LV_BUILD_DEMOS
    /** Show some widgets. This might be required to increase `LV_MEM_SIZE`. */
    #define LV_USE_DEMO_WIDGETS 0

    /** Demonstrate usage of encoder and keyboard. */
    #define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

    /** Benchmark your system */
    #define LV_USE_DEMO_BENCHMARK 0

    #if LV_USE_DEMO_BENCHMARK
        /** Use fonts where bitmaps are aligned 16 byte and has Nx16 byte stride */
        #define LV_DEMO_BENCHMARK_ALIGNED_FONTS 0
    #endif

    /** Render test for each primitive.
     *  - Requires at least 480x272 display. */
    #define LV_USE_DEMO_RENDER 0

    /** Stress test for LVGL */
    #define LV_USE_DEMO_STRESS 0

    /** Music player demo */
    #define LV_USE_DEMO_MUSIC 0
    #if LV_USE_DEMO_MUSIC
        #define LV_DEMO_MUSIC_SQUARE    0
        #define LV_DEMO_MUSIC_LANDSCAPE 0
        #define LV_DEMO_MUSIC_ROUND     0
        #define LV_DEMO_MUSIC_LARGE     0
        #define LV_DEMO_MUSIC_AUTO_PLAY 0
    #endif

    /** Vector graphic demo */
    #define LV_USE_DEMO_VECTOR_GRAPHIC  0

    /** GLTF demo */
    #define LV_USE_DEMO_GLTF            0

    /*---------------------------
     * Demos from lvgl/lv_demos
      ---------------------------*/

    /** Flex layout demo */
    #define LV_USE_DEMO_FLEX_LAYOUT     0

    /** Smart-phone like multi-language demo */
    #define LV_USE_DEMO_MULTILANG       0

    /*E-bike demo with Lottie animations (if LV_USE_LOTTIE is enabled)*/
    #define LV_USE_DEMO_EBIKE           0
    #if LV_USE_DEMO_EBIKE
        #define LV_DEMO_EBIKE_PORTRAIT  0    /*0: for 480x270..480x320, 1: for 480x800..720x1280*/
    #endif

    /** High-resolution demo */
    #define LV_USE_DEMO_HIGH_RES        0

    /* Smart watch demo */
    #define LV_USE_DEMO_SMARTWATCH      0
#endif /* LV_BUILD_DEMOS */

/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////  test LVGL + TFT_eSPI + xpt2046 /////////////////////////////////////////////////////////////////////

/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd-lvgl/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft-lvgl/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

/*  Install the "lvgl" library version 9.2 by kisvegabor to interface with the TFT Display - https://lvgl.io/
    *** IMPORTANT: lv_conf.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE lv_conf.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
//#include <stdint.h>
#include <lvgl.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen - Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// If logging is enabled, it will inform the user about what is happening in the library
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}

// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();

      // x=p.x;
      // y=p.y;
      // Serial.print("raw x,y = ");
      // Serial.print(x);
      // Serial.print(",");
      // Serial.println(y);
    // Calibrate Touchscreen points with map function to the correct width and height
    
    x = map(p.y, 3761,324, 1, 240); //was 200 3700
    y = map(p.x, 225,3673, 1, 320); // was 240 3800
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;

    // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
    /* Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();*/
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

int btn1_count = 0;
// Callback that is triggered when btn1 is clicked
static void event_handler_btn1(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    btn1_count++;
    LV_LOG_USER("Button clicked %d", (int)btn1_count);
  }
}

// Callback that is triggered when btn2 is clicked/toggled
static void event_handler_btn2(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_VALUE_CHANGED) {
    LV_UNUSED(obj);
    LV_LOG_USER("Toggled %s", lv_obj_has_state(obj, LV_STATE_CHECKED) ? "on" : "off");
  }
}

static lv_obj_t * slider_label;
// Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
static void slider_event_callback(lv_event_t * e) {
  lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
  char buf[8];
  lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
  lv_label_set_text(slider_label, buf);
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
  LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
}

void lv_create_main_gui(void) {
  // Create a text label aligned center on top ("Hello, world!")
  lv_obj_t * text_label = lv_label_create(lv_screen_active());
  lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);    // Breaks the long lines
  lv_label_set_text(text_label, "Hello, world!");
  lv_obj_set_width(text_label, 150);    // Set smaller width to make the lines wrap
  lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);

  lv_obj_t * btn_label;
  // Create a Button (btn1)
  lv_obj_t * btn1 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -50);
  lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

  btn_label = lv_label_create(btn1);
  lv_label_set_text(btn_label, "Button");
  lv_obj_center(btn_label);

  // Create a Toggle button (btn2)
  lv_obj_t * btn2 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 10);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);

  btn_label = lv_label_create(btn2);
  lv_label_set_text(btn_label, "Toggle");
  lv_obj_center(btn_label);
  
  // Create a slider aligned in the center bottom of the TFT display
  lv_obj_t * slider = lv_slider_create(lv_screen_active());
  lv_obj_align(slider, LV_ALIGN_CENTER, 0, 60);
  lv_obj_add_event_cb(slider, slider_event_callback, LV_EVENT_VALUE_CHANGED, NULL);
  lv_slider_set_range(slider, 0, 100);
  lv_obj_set_style_anim_duration(slider, 2000, 0);

  // Create a label below the slider to display the current slider value
  slider_label = lv_label_create(lv_screen_active());
  lv_label_set_text(slider_label, "0%");
  lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

void setup() 
{
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  Serial.println(LVGL_Arduino);
  
  // Start LVGL
  lv_init();
  // Register print function for debugging
  lv_log_register_print_cb(log_print);
  
  

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 0: touchscreen.setRotation(0);
  touchscreen.setRotation(1);

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
  tft.setRotation(1);
//tft.invertDisplay(1);// this changes the color assignment
    
  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Function to draw the GUI (text, buttons and sliders)
  lv_create_main_gui();
}

void loop() 
{
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);           // let this time pass
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





