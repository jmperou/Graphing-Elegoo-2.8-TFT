/*
  This program is based on Kris Kasprzak's Graphing project and customized for the Elegoo 2.8" TFT Touch Screen. 
  Kris Kasprzak's Graphing github page: https://github.com/KrisKasprzak/Graphing
  
  This program provides cartesian type graph function
  
  Dependencies:
    - Arduino Mega (or UNO) and an Elegoo 2.8" TFT Touch Screen
        https://www.elegoo.com/products/elegoo-2-8-inches-tft-touch-screen
    - The following Elegoo Libraries must be installed (note that the libraries are updated as of  May 2022 and are not maintained):
        Elegoo Libraries (https://github.com/jmperou/Graphing-Elegoo-2.8-TFT/tree/main/Elegoo_Libraries)
        For Library installation instructions (https://www.arduino.cc/en/Guide/Libraries#:~:text=In%20the%20Arduino%20IDE%2C%20navigate,ZIP%20Library''.)
        
Revisions
rev     date        author      description
2       5-20-2022   jmperou     customization for Elegoo 2.8" TFT Touch Screen
1       12-24-2015  kasprzak    initial creation

*/

#include <SPI.h>
#include <SD.h>
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library


// These are 'flexible' lines that can be changed

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin


#define LTBLUE    0xB6DF
#define LTTEAL    0xBF5F
#define LTGREEN   0xBFF7
#define LTCYAN    0xC7FF
#define LTRED     0xFD34
#define LTMAGENTA 0xFD5F
#define LTYELLOW  0xFFF8
#define LTORANGE  0xFE73
#define LTPINK    0xFDDF
#define LTPURPLE  0xCCFF
#define LTGREY    0xE71C

#define BLUE      0x001F
#define TEAL      0x0438
#define GREEN     0x07E0
#define CYAN      0x07FF
#define RED       0xF800
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define ORANGE    0xFC00
#define PINK      0xF81F
#define PURPLE    0x8010
#define GREY      0xC618
#define WHITE     0xFFFF
#define BLACK     0x0000

#define DKBLUE    0x000D
#define DKTEAL    0x020C
#define DKGREEN   0x03E0
#define DKCYAN    0x03EF
#define DKRED     0x6000
#define DKMAGENTA 0x8008
#define DKYELLOW  0x8400
#define DKORANGE  0x8200
#define DKPINK    0x9009
#define DKPURPLE  0x4010
#define DKGREY    0x4A49


#define ADJ_PIN A0

double a1, b1, c1, d1, r2, r1, vo, tempC, tempF, tempK;

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// this is the only external variable used by the graph
// it's a flat to draw the coordinate system only on the first pass
boolean display1 = true;
boolean display2 = true;
boolean display3 = true;
boolean display4 = true;
boolean display5 = true;
boolean display6 = true;
boolean display7 = true;
boolean display8 = true;
boolean display9 = true;
double ox , oy ;

void setup() {

  Serial.begin(9600);

  pinMode(ADJ_PIN, INPUT);
   #ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
  #endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9341;

  }
  tft.begin(identifier);
  tft.fillScreen(BLACK);

  tft.setRotation(2);
  a1 = 3.354016E-03 ;
  b1 = 2.569850E-04 ;
  c1 = 2.620131E-06 ;
  d1 = 6.383091E-08 ;


  double x, y;


  tft.setRotation(3);


  for (x = 0; x <= 6.3; x += .1) {

    y = sin(x);
    Graph(tft, x, y, 60, 290, 390, 260, 0, 6.5, 1, -1, 1, .25, "Sin Function", "x", "sin(x)", DKBLUE, RED, YELLOW, WHITE, BLACK, display1);

  }

  delay(1000);

  tft.fillScreen(BLACK);
  for (x = 0; x <= 6.3; x += .1) {

    y = sin(x);
    Graph(tft, x, y, 100, 280, 100, 240, 0, 6.5, 3.25, -1, 1, .25, "Sin Function", "x", "sin(x)", GREY, GREEN, RED, YELLOW, BLACK, display9);

  }

    delay(1000);

  tft.fillScreen(BLACK);
  for (x = 0; x <= 25.2; x += .1) {

    y = sin(x);
    Graph(tft, x, y, 50, 190, 400, 60, 0, 25, 5, -1, 1, .5, "Sin Function", "x", "sin(x)", DKYELLOW, YELLOW, GREEN, WHITE, BLACK, display8);

  }

  delay(1000);

  tft.fillScreen(BLACK);
  for (x = 0.001; x <= 10; x += .1) {

    y = log(x);
    Graph(tft, x, y, 50, 240, 300, 180, 0, 10, 1, -10, 5, 1, "Natural Log Function", "x", "ln(x)", BLUE, RED, WHITE, WHITE, BLACK, display2);

  }

  

  delay(1000);
  tft.fillScreen(BLACK);

  for (x = 0; x <= 10; x += 1) {

    y = x * x;
    Graph(tft, x, y, 50, 290, 390, 260, 0, 10, 1, 0, 100, 10, "Square Function", "x", "x^2", DKRED, RED, YELLOW, WHITE, BLACK, display3);

  }

  delay(1000);
  tft.fillScreen(BLACK);

  for (x = 0.00; x <= 20; x += .01) {

    y = ((sin(x)) * x + cos(x)) - log(x);
    Graph(tft, x, y, 50, 290, 390, 260, 0, 20, 1, -20, 20, 5, "Weird Function", "x", " y = sin(x) + cos(x) - log(x)", ORANGE, YELLOW, CYAN, WHITE, BLACK, display4);

  }

  delay(1000);
  tft.fillScreen(BLACK);
  tft.setRotation(2);
  for (x = 0; x <= 12.6; x += .1) {

    y = sin(x);
    Graph(tft, x, y, 50, 250, 150, 150, 0, 13, 3.5, -1, 1, 1, "Sin(x)", "x", "sin(x)", DKBLUE, RED, YELLOW, WHITE, BLACK, display5);

  }
  tft.setRotation(3);
  delay(1000);
  tft.fillScreen(WHITE);

  for (x = 0; x <= 6.3; x += .05) {

    y = cos(x);
    Graph(tft, x, y, 100, 250, 300, 200, 0, 6.5, 3.25, -1, 1, 1, "Cos Function", "x", "cos(x)", DKGREY, GREEN, BLUE, BLACK, WHITE, display6);

  }

  delay(1000);
  tft.fillScreen(BLACK);


  for (x = 0; x <= 60; x += 1) {
    vo = analogRead(ADJ_PIN) / 204.6;
    r1 = 9940;
    r2 = ( vo * r1) / (5 - vo);

    //equation from data sheet
    tempK = 1.0 / (a1 + (b1 * (log(r2 / 10000.0))) + (c1 * pow(log(r2 / 10000.0), 2)) + (d1 * pow(log(r2 / 10000.0), 3)));
    tempC  = ((tempK - 273.15) );
    y = tempF  = (tempC * 1.8000) + 32.00;

    Graph(tft, x, y, 50, 290, 390, 260, 0, 60, 10, 70, 90, 5, "Room Temperature", " Time [s]", "Temperature [deg F]", DKBLUE, RED, GREEN, WHITE, BLACK, display7);
    delay(250);
  }

 delay(1000);
  tft.fillScreen(BLACK);

}


void loop(void) {

}

/*
  function to draw a cartesian coordinate system and plot whatever data you want
  just pass x and y and the graph will be drawn
  huge arguement list
  &d name of your display object
  x = x data point
  y = y datapont
  gx = x graph location (lower left)
  gy = y graph location (lower left)
  w = width of graph
  h = height of graph
  xlo = lower bound of x axis
  xhi = upper bound of x asis
  xinc = division of x axis (distance not count)
  ylo = lower bound of y axis
  yhi = upper bound of y asis
  yinc = division of y axis (distance not count)
  title = title of graph
  xlabel = x asis label
  ylabel = y asis label
  gcolor = graph line colors
  acolor = axi ine colors
  pcolor = color of your plotted data
  tcolor = text color
  bcolor = background color
  &redraw = flag to redraw graph on fist call only
*/


void Graph(Elegoo_TFTLCD &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setTextSize(1);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      // precision is default Arduino--this could really use some format control
      d.println(i);
    }

    //now draw the labels
    d.setTextSize(2);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setTextSize(1);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}

/*
  End of graphing functioin
*/
