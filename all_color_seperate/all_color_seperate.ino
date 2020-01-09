

//TO DO: COMMENT 

#include <Adafruit_NeoPixel.h>

//dulled down version of the competition colors so my eyes don't go blind ;)
uint32_t yellow = Adafruit_NeoPixel::Color(79, 79, 5);
uint32_t red = Adafruit_NeoPixel::Color(79, 5, 5 );
uint32_t green = Adafruit_NeoPixel::Color(7, 79, 5);
uint32_t blue = Adafruit_NeoPixel::Color(5, 79, 77);

#define STRIP_PIN       4
#define STRIP_PIXELS    30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_PIXELS, STRIP_PIN,
                                             NEO_GRB + NEO_KHZ800);
#define RING_PIN        5
#define RING_PIXELS     12
Adafruit_NeoPixel ring = Adafruit_NeoPixel(RING_PIXELS, RING_PIN,
                                             NEO_GRB + NEO_KHZ800);

const int sensorPin = A0;  // A pin connected to a potentiomenter
int sensorValue;           // A place to store the value from the potentiometer

void setup(void)
{
    // Configure the serial terminal for debug output and user input
    Serial.begin(9600);


    // Configure the pin connected to the board's LED as an output
    pinMode(LED_BUILTIN, OUTPUT);

    // Initialize the pixels to get them ready for use
    strip.begin();
    ring.begin();

    // Clear the pixel strips to all off
    all_pixels(strip, Adafruit_NeoPixel::Color(0, 0, 0));
    all_pixels(ring, Adafruit_NeoPixel::Color(0, 0, 0));


    //turn the pixels on the strip and ring to one color
    one_color(strip, red);
    one_color(ring, blue);
    
}

    void one_color(Adafruit_NeoPixel &pixels, uint32_t color )
{
  uint16_t numPixels = pixels.numPixels();
  
  for (unsigned i=0; i<numPixels; i = i+4 )// i + 1+4 <------- spaces between the pixels
    {
        pixels.setPixelColor(i, color);
    }
  
    pixels.show();
}

void loop(void)
{
    // Read the voltage value on the sensor input pin as 0 to 1023
    sensorValue = analogRead(sensorPin);

    // Adjust the voltage value so that it goes from -512 to 511
    sensorValue = sensorValue - 512;

    // Depending on the position of the potentiometer, move the pixels
    // up or down
    if (sensorValue < 10)
    {
        rotate_down(strip);
        rotate_down(ring);
    }
    else if (sensorValue > 10)
    {
        rotate_up(strip);
        rotate_up(ring);
    }
    // If the sensor value is between the ranges above, the pixels don't move

    // Delay a value proportional to the position of the potentiometer
    delay(650 - abs(sensorValue));
}

void all_pixels(Adafruit_NeoPixel &pixels, uint32_t color)
{
    uint16_t numPixels = pixels.numPixels();

    for (unsigned i=0; i<numPixels; i++)
    {
        pixels.setPixelColor(i, color);
    }
    pixels.show();
}void rotate_up(Adafruit_NeoPixel &pixels)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels.numPixels();

    // Save the last pixel in the strip
    saved_pixel = pixels.getPixelColor(numPixels - 1);
    for (int i=0; i<numPixels; i++)
    {
        uint32_t temp;
        // Copy the pixel value at the current pixel
        temp = pixels.getPixelColor(i);
        // Store the saved value in its place
        pixels.setPixelColor(i, saved_pixel);
        // Update the saved pixel value with the one we copied out
        saved_pixel = temp;
    }
    // Show the pixels
    pixels.show();
}

void rotate_down(Adafruit_NeoPixel &pixels)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels.numPixels();

    // Save the first pixel in the strip
    saved_pixel = pixels.getPixelColor(0);
    for (int i=numPixels - 1; i>=0; i--)
    {
        uint32_t temp;
        // Copy the pixel value at the current pixel
        temp = pixels.getPixelColor(i);
        // Store the saved value in its place
        pixels.setPixelColor(i, saved_pixel);
        // Update the saved pixel value with the one we copied out
        saved_pixel = temp;
    }
    // Show the pixels
    pixels.show();
}

void shift_up(Adafruit_NeoPixel &pixels, uint32_t color)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels.numPixels();

    // Shift in the pixel color that is provided
    saved_pixel = color;
    for (int i=0; i<numPixels; i++)
    {
        uint32_t temp;
        // Copy the pixel value at the current pixel
        temp = pixels.getPixelColor(i);
        // Store the saved value in its place
        pixels.setPixelColor(i, saved_pixel);
        // Update the saved pixel value with the one we copied out
        saved_pixel = temp;
    }
    // Show the pixels
    pixels.show();
}

void shift_down(Adafruit_NeoPixel &pixels, uint32_t color)
{
    uint32_t saved_pixel;
    uint16_t numPixels = pixels.numPixels();

    // Shift in the pixel color that is provided
    saved_pixel = color;
    for (int i=numPixels - 1; i>=0; i--)
    {
        uint32_t temp;
        // Copy the pixel value at the current pixel
        temp = pixels.getPixelColor(i);
        // Store the saved value in its place
        pixels.setPixelColor(i, saved_pixel);
        // Update the saved pixel value with the one we copied out
        saved_pixel = temp;
    }
    // Show the pixels
    pixels.show();
}
