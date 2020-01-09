/*
  Description: A program to demo some bling on NeoPixels
  Written by: Riyadth Al-Kazily
*/

// Include a library to communicate with colorful LEDs
#include <Adafruit_NeoPixel.h>

//Color libary
uint32_t none = Adafruit_NeoPixel::Color(0, 0, 0);
uint32_t cyan = Adafruit_NeoPixel::Color(0, 32, 32);
uint32_t seaGreen = Adafruit_NeoPixel::Color(0, 32, 15);
uint32_t pink = Adafruit_NeoPixel::Color(245, 23, 167);
uint32_t hotPink =Adafruit_NeoPixel::Color(32, 0, 15);
uint32_t goldOrange = Adafruit_NeoPixel::Color(32, 15, 0);
uint32_t pearMeat = Adafruit_NeoPixel::Color(32, 32, 15);
uint32_t vividBlue = Adafruit_NeoPixel::Color(0, 15, 32);
uint32_t purple = Adafruit_NeoPixel::Color(15, 0, 32);
uint32_t lavender = Adafruit_NeoPixel::Color(32, 15, 32);
uint32_t mint = Adafruit_NeoPixel::Color(15, 32, 15);

//Competition color wheel colors (Warning, REALLY BRIGHT)
uint32_t yellow = Adafruit_NeoPixel::Color(255,232,0);
uint32_t red = Adafruit_NeoPixel::Color(255,0,0);
uint32_t green = Adafruit_NeoPixel::Color(0,255,0);
uint32_t blue = Adafruit_NeoPixel::Color(0,255,253);

// Tell the computer about the arrangement and type of the pixels we are using
// First a strip of pixels
#define STRIP_PIN       4
#define STRIP_PIXELS    30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_PIXELS, STRIP_PIN,
                                             NEO_GRB + NEO_KHZ800);
// Second is a NeoPixel ring
#define RING_PIN        5
#define RING_PIXELS     12
Adafruit_NeoPixel ring = Adafruit_NeoPixel(RING_PIXELS, RING_PIN,
                                             NEO_GRB + NEO_KHZ800);

// Define some constants and variables
const int sensorPin = A0;  // A pin connected to a potentiomenter
int sensorValue;           // A place to store the value from the potentiometer

/**
 *  Initialize the system when powered up.
 */
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
    
//"Rainbow" Color startup code
    strip.setPixelColor(0, hotPink);
    strip.setPixelColor(1, goldOrange);
    strip.setPixelColor(2, seaGreen);
    strip.setPixelColor(3, pearMeat);
    strip.setPixelColor(4, purple);
    strip.setPixelColor(5, vividBlue);
    strip.setPixelColor(6, cyan);
    strip.setPixelColor(7, lavender);
    strip.setPixelColor(8, mint);
    strip.show();

    // Turn on three pixels on the ring
    ring.setPixelColor(0, goldOrange);
    ring.setPixelColor(3, vividBlue);
    ring.setPixelColor(6, goldOrange);
    ring.setPixelColor(9, vividBlue);
    ring.show();

    int led = 9;
    int brightness = 0;
    int fadeAmount = 5;

    // Tell the world we're ready to go!
    Serial.println("Setup complete.");
}


/**
 *  Repeat the execution of this function over and over
 */
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

/**
 *  Set all pixels of the strip to the specified color.
 */
void all_pixels(Adafruit_NeoPixel &pixels, uint32_t color)
{
    uint16_t numPixels = pixels.numPixels();

    for (unsigned i=0; i<numPixels; i++)
    {
        pixels.setPixelColor(i, color);
    }
    pixels.show();
}

/**
 *  Rotate the pixel display up the strip by one position, rotating the
 *  highest pixel around from the top to the bottom.
 */
void rotate_up(Adafruit_NeoPixel &pixels)
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

/**
 *  Rotate the pixel display down the strip by one position, rotating the
 *  lowest pixel around from the bottom to the top.
 */
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

/**
 *  Shift the pixel display up the strip by one position, setting the
 *  first pixel to the given color.
 */
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

/**
 *  Shift the pixel display down the strip by one position, setting the
 *  last pixel to the given color.
 */
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

/**
 *  Make a rainbow of color on the pixels
 */
void make_a_rainbow(Adafruit_NeoPixel &pixels, int brightness)
{
    uint16_t numPixels = pixels.numPixels();

    // Set the NeoPixels to a rainbow of colors
    for (unsigned i=0; i<numPixels; i++)
    {
        // TODO: Compute the rainbow spectrum across all the pixels
    }
    /*
    pixels.setPixelColor(0, pixels.Color(brightness, 0, 0));
    pixels.setPixelColor(1, pixels.Color(brightness, brightness, 0));
    pixels.setPixelColor(2, pixels.Color(0, brightness, 0));
    pixels.setPixelColor(3, pixels.Color(0, brightness, brightness));
    pixels.setPixelColor(4, pixels.Color(0, 0, brightness));
    pixels.setPixelColor(5, pixels.Color(brightness, 0, brightness));
    pixels.setPixelColor(6, pixels.Color(brightness, brightness, brightness));
    pixels.setPixelColor(7, pixels.Color(0, 0, 0));
    pixels.show();
    */
}
