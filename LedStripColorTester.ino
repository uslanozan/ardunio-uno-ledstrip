/* LedStripColorTester: Example Arduino sketch that lets you
 * type in a color on a PC and see it on the LED strip.
 *
 * To use this, you will need to plug an Addressable RGB LED
 * strip from Pololu into pin 12.  After uploading the sketch,
 * select "Serial Monitor" from the "Tools" menu.  In the input
 * box, type a color and press enter.
 *
 * The format of the color should be "R,G,B!" where R, G, and B
 * are numbers between 0 and 255 representing the brightnesses
 * of the red, green, and blue components respectively.
 *
 * For example, to get green, you could type:
 *   40,100,0!
 *
 * You can leave off the exclamation point if you change the
 * Serial Monitor's line ending setting to be "Newline" instead
 * of "No line ending".
 *
 * Please note that this sketch only transmits colors to the
 * LED strip after it receives them from the computer, so if
 * the LED strip loses power it will be off until you resend
 * the color.
 */

#include <PololuLedStrip.h>
#include <stdlib.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<2> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

rgb_color change_color(int redInput,int greenInput,int blueInput);
int find_max(int red,int green,int blue);
int find_min(int red,int green,int blue);
rgb_color transition_color(rgb_color color);
void colYaz(String msg, rgb_color col);

#define DELAY 500 // 0.5 saniye 
rgb_color color;
static int gap;

void setup() {
  // Start up the serial port, for communication with the PC.
  Serial.begin(115200);
  Serial.println("Ready to receive colors.");
color.red=60;
color.green=90;
color.blue=120;
}



//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
void ledGoster(rgb_color col)
{

      // Update the colors buffer.
      for (uint16_t i = 0; i < LED_COUNT; i++)
        {
        colors[i] = col;
        }

      // Write to the LED strip.
      ledStrip.write(colors, LED_COUNT);

}
//---------------------------------------------------------------------------------------
void serial_check(void)
{
   if (Serial.available()) 
    {
    char c = Serial.peek();
    if (!(c >= '0' && c <= '9')) 
      {
      Serial.read();  // Discard non-digit character
      } 
      else
      {
      // Read the color from the computer.
      color.red = Serial.parseInt();
      color.green = Serial.parseInt();
      color.blue = Serial.parseInt();
      gap=abs(color.red - color.green);
      Serial.print("Girilen color: ");
      Serial.print(color.red);
      Serial.print(",");
      Serial.print(color.green);
      Serial.print(",");
      Serial.println(color.blue);



      color=change_color(color.red,color.green,color.blue);
      


      ledGoster(color);

      Serial.print("Showing color: ");
      Serial.print(color.red);
      Serial.print(",");
      Serial.print(color.green);
      Serial.print(",");
      Serial.println(color.blue);
      }
    }

}
//---------------------------------------------------------------------------------------
void loop()
{
static int counter=0;
serial_check();

delay(4*DELAY);
switch ((counter+1)%3)
    {
    case 0:  //red
        if(counter%2==0) // arttır
          {
          color.red=color.red+gap;
          
          }
          else
          {
          color.red=color.red-gap;
          }
        break;
    case 1: //green
        if(counter%2==0)
          {
          color.green=color.green+gap;
          }
          else
          {
          color.green=color.green-gap;
          }
        break;
    case 2: //blue
        if(counter%2==0){
            color.blue=color.blue+gap;
        }else {
            color.blue=color.blue-gap;
        }
        break;
    }
ledGoster(color);
//colYaz("loop: ",color);
delay(4*DELAY);
counter++;
//Serial.println("Gap is:");
//Serial.println(gap);

}


/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
int find_max(int red,int green,int blue)
{
  if (red > green)
     {
     if (red > blue)
        {
        return red;
        }
        else
        {
        if (blue > green)
           return blue;
           else
           return green;
        }
     }
     else
     {
     if (blue > green)
        return blue;
        else
        return green;
     }
}

int find_min(int red,int green,int blue)
{
if (red < green)
   {
   if (red < blue)
      {
      return red;
      }
      else
      {
      if (blue< green)
         return blue;
         else
         return green;
      }
    }
    else
    {
    if (blue < green)
       return blue;
       else
       return green;
    }
}



rgb_color change_color(int redInput,int greenInput,int blueInput) {
    int newmin=find_min(redInput,greenInput,blueInput);
    int newmax=find_max(redInput,greenInput,blueInput);
  rgb_color col;
  col.red=newmax;
  col.green=newmin;
  col.blue=newmin;
  //redInput=newmax;
  //greenInput=newmin;
  //blueInput=newmin;
  colYaz("min max: ",col);
return col;
}

void colYaz(String msg, rgb_color col)
{
Serial.print(msg);
  Serial.print(",");
  Serial.print(col.red);
  Serial.print(",");
  Serial.print(col.green);
  Serial.print(",");
  Serial.println(col.blue);
}