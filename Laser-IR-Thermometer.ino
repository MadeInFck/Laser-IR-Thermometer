#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

const int Laser_Pin=5;  //Laser Pin
int buttonState = 0; 
const int buttonPin = 2;     // the number of the pushbutton pin

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
   
  pinMode(Laser_Pin,OUTPUT);
  pinMode(buttonPin, INPUT);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  Serial.println(F(" OLED initialisé "));

  display.clearDisplay();
  display.setRotation(0);
  display.setTextColor(WHITE);
  //display.invertDisplay(true);
  display.setTextSize(1);
  display.setCursor(15, 35);
  display.print("Initialisation");
  display.setCursor(35, 45);
  display.print("du capteur");
  
  display.display();
  delay(1000);
  display.clearDisplay();

  Serial.println(" Test Adafruit MLX90614"); 
  mlx.begin(); 
  
}

void loop() {

  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  
  Serial.print("Température ambiante = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("°C\nTempérature cible = "); Serial.print(mlx.readObjectTempC()); Serial.print("°C");
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(Laser_Pin, HIGH);
    
    display.clearDisplay();
    display.setTextSize(2);  //Size 2 means each pixel is 12 width and 16 high
    display.setCursor(25, 20);
    display.print(mlx.readObjectTempC());
    display.setCursor(50, 40);
    display.print("\xA7");
    display.print("C");
    display.display();
    
  } else {
    // turn LED off:
    digitalWrite(Laser_Pin, LOW);
  
    display.clearDisplay();
    display.setTextSize(2);  //Size 2 means each pixel is 12 width and 16 high
    display.setCursor(35, 20);
    display.print("PRET !");
    display.display();
    
  }

  Serial.println();
  delay(500);
}
