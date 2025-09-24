#include <FastLED.h>
#define LED_PIN     5
#define NUM_LEDS    60
#define BRIGHTNESS  244
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//CRGBPalette16 currentPalette;
TBlendType LinearBlend;

uint8_t i = 0;
uint8_t colorNum = 0;

uint8_t colors[5][3];

void setup() {
  
    delay( 3000 ); // power-up safety delay
    Serial.begin(9600);

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}

void loop()
{
    uint8_t red = map(analogRead(A0), 0, 1023, 0, 255);
    uint8_t green = map(analogRead(A1), 0, 1023, 0, 255);
    uint8_t blue = map(analogRead(A2), 0, 1023, 0, 255);

    FillLEDs(red, green, blue);
    FastLED.show();
    FastLED.delay(20);
    
     Serial.println(analogRead(A5));
    if(analogRead(A5)>900){
      saveLEDs(red, green, blue);
   }
}

void FillLEDs(int red, int green, int blue)
{
  if(i > 59){
    i=0;
  }
  if(colorNum == 0){
    leds[i].setRGB(red, green, blue);
  }else if(colorNum == 1){
    leds[i].setRGB(red, green, blue);
    if(i <30)
      leds[i+30].setRGB(colors[0][0],colors[0][1],colors[0][2]);
    else
      leds[i-30].setRGB(colors[0][0],colors[0][1],colors[0][2]);
  }else if(colorNum ==2){
    leds[i].setRGB(red, green, blue);
    if(i <20)
      leds[i+40].setRGB(colors[0][0],colors[0][1],colors[0][2]);
    else
      leds[i-20].setRGB(colors[0][0],colors[0][1],colors[0][2]);
    if(i<40)
      leds[i+20].setRGB(colors[1][0],colors[1][1],colors[1][2]);
    else
      leds[i-40].setRGB(colors[1][0],colors[1][1],colors[1][2]);
  }else if(colorNum == 3){
    colorNum = 0;
  }
  i++;
}

void saveLEDs(int red, int green, int blue)
{
  FastLED.clear();
  for(i = 0; i<65; i++){
    FastLED.delay(10);
    if(i <60)
      leds[i].setRGB(red, green, blue);
    if(i >=5)
      leds[i-5].setRGB(0,0,0);
    FastLED.show();
  }
  FastLED.clear();
    colors[colorNum][0] = red;
    colors[colorNum][1] = green;
    colors[colorNum][2] = blue;
    colorNum++;
  FastLED.delay(1000);
}


