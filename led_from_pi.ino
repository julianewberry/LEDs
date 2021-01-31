#include <Adafruit_NeoPixel.h>
 
#define NUM_LEDS              30 // 180 LED NeoPixel
#define NEOPIXEL_PIN            6 // Pin D0

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN);

boolean newData = false;
const byte numChars = 32;
char color_string[numChars]; // an array to store the received data

void show_color(int r, int g, int b){

  uint32_t color = pixels.Color(r, g, b);

   for(int i = 0; i < NUM_LEDS; i++){
      pixels.setPixelColor(i, color);
   }

   pixels.show();
}

void setup() {
   
   Serial.begin(9600);
   Serial.println("Enter rgb as 'r g b'");
   pixels.begin();
}

void loop() {
  if(Serial.available() > 0){
        String data = Serial.readStringUntil('\n');
        //Serial.print("You sent me: ");
        Serial.println(data);
        process_string(data);
  }  
  //recvWithEndMarker();
}

void process_string(String color_string){
  int r = 0;
  int g = 0;
  int b = 0;

  const char *color_char = color_string.c_str();
 
  Serial.println(color_char);

  sscanf(color_char, "%d %d %d", &r, &g, &b);

  show_color(r, g, b);
}

void recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 
 while (Serial.available() > 0 && newData == false) {
  rc = Serial.read();

  if (rc != endMarker) {
    color_string[ndx] = rc;
    ndx++;
    if (ndx >= numChars) {
      ndx = numChars - 1;
    }
  }
  else {
    color_string[ndx] = '\0'; // terminate the string
    ndx = 0;
    newData = true;
  }
 }
 if(newData){
  process_string(color_string);
  newData = false;
 }
}
