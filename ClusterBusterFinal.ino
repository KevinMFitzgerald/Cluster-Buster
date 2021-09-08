#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Wire.h>
#include "DHT.h"
#include "MAX30105.h"
#include "heartRate.h"
#include "time.h"
#include "ClusterBuster.h"
#include "homePage.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <Adafruit_BMP280.h>

#define DHTPIN 16 //pin 16 of ESP32 to read data
#define DHTTYPE DHT11 //our sensor is DHT11 type 
DHT dht(DHTPIN, DHTTYPE);//create an instance of DHT sensor

//this creats instances from my libaray
Level_Leds Leds(33, 27, 13, 17);
LMT35 LM35(34);
LEDS ON_LEDS(32);

//removing adder dc offset
const int Adder_Offset=2410;

Adafruit_BMP280 bmp;

MAX30105 particleSensor;

//pin for vibartion motors
const int Motor = 25;
const int Motor2 = 26;

//pin for buttons
const int button_Off = 14;
const int button_On = 15;

const int Pot = 35;

//string for wifi connection
const char* ssid = "Fitzgerald";
const char* password = "Sandyhill?12";

WebServer server(80); //creats an instance of Server on port 80

int On_Flag = 0;

String Sd_Message;
String Side_Of_Head;

//heart rate varibles
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte Rates[RATE_SIZE]; //Array of heart rates
byte Rate_Spot = 0;
long last_Beat = 0; //Time at which the last beat occurred
float Beats_Per_Minute;
int Beat_Avg;

//varibles for ntpServer
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

int Motor_Speed;
int Pot_Vaule;

int Side_Of_Head_Effected_Right;
int Side_Of_Head_Effected_Left;

//bmp varibles
long Pressure;
int Bmp_Temp;

//time varibles stored as char arrays
char Time_Week_Day[10];//largest week day in charcters is 9 char long + end char
char Time_Month[10];
char Time_Hour[3];
char Time_Min[3];
char Time_Date_Month[3];
char Time_Date_Day[3];
//raw time varibles
int Hour, Min, Sec;
unsigned long Start, End, Total;

unsigned long Duration() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}

void LocalTime()//parasing time object into char arrays ie human readable
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(Time_Week_Day, 10, "%A", &timeinfo);//strftime() is a function in C which is used to format date and time
  strftime(Time_Month, 10, "%B", &timeinfo);//returns a char array
  strftime(Time_Hour, 3, "%H", &timeinfo);
  strftime(Time_Min, 3, "%M", &timeinfo);
  strftime(Time_Date_Month, 3, "%m", &timeinfo);
  strftime(Time_Date_Day, 3, "%d", &timeinfo);
}

void initSDCard() { //initialise the sd card
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void sendMonth() {
  String message = Time_Month;
  server.send(200, "text/plain", message);
}
void sendDate() {
  String message = String(Time_Date_Day) + ' ' + String(Time_Month);
  server.send(200, "text/plain", message);
}
void sendTime() {
  LocalTime();//refreshes time before
  String message = String(Time_Hour) + ':' + String(Time_Min);
  server.send(200, "text/plain", message);
}
void sendHeartRate() {
  String message =  String(Beat_Avg);
  server.send(200, "text/plain", message);          //Returns the HTTP response
}
void sendTemp() {
  float a = dht.readTemperature();
  String message =  String(a);
  server.send(200, "text/plain", message);         //Returns the HTTP response
}
void sendPressure() {
  String message =  String(Pressure);
  server.send(200, "text/plain", message); //Returns the HTTP response
}

void sendHomePage() {
  server.send(200, "text/html", homePage);
}
void HandlebuttonL() {
  Side_Of_Head_Effected_Left++;
  server.send(200, "text/html", homePage);
}
void HandlebuttonR() {
  Side_Of_Head_Effected_Right++;
  server.send(200, "text/html", homePage);
}

void handleNotFound() {
  String message = "Address not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  //init and get the time

  initSDCard();

  WiFi.mode(WIFI_STA);//sation mode
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }  Serial.println(" CONNECTED");







  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  LocalTime();

  server.on("/Time", sendTime);
  server.on("/Date", sendDate);
  server.on("/Month", sendMonth);
  server.on("/temp", sendTemp);
  server.on("/sendPressure", sendPressure);
  server.on("/getData", sendHeartRate);
  server.on("/", sendHomePage);
  server.on("/L", HandlebuttonL);
  server.on("/R", HandlebuttonR);

  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if (!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Time,     Temperature, Humidity, Pressure, Duration\t Average Heart Rate\t Hand temp\t Side Of Head \r\n");
  }
  else {
    Serial.println("File already exists");
  }
  file.close();

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  dht.begin();
  bmp.begin();
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */


  pinMode(Pot, INPUT);
  pinMode(button_Off, INPUT);
  pinMode(button_On, INPUT);


  float h = dht.readHumidity();
  float t = dht.readTemperature();// Read temperature as Celsius (the default)
  float f = dht.readTemperature(true); // Read temperature as Fahrenheit (isFahrenheit = true)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  \nTemperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("\n\rHeat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.print(F("°F\n\r"));
  Serial.print("Temprature from bmp280: ");
  Serial.println(bmp.readTemperature());
  Serial.print("Pressure from bmp280 = ");
  Serial.println(bmp.readPressure());
  Serial.print("Approx altitude from bmp280 = ");
  Serial.println(bmp.readAltitude(1013.25));//readAltitude needs your above sea level as it only reads pressure and calultes the diffrence for your current altitude.

}

void loop(void) {
  server.handleClient();
  if (digitalRead(button_On) == HIGH) {
    if (On_Flag == 0) { //stops function running multiple times

      Start = Duration(); //current time from epoch
    }
    On_Flag = 1;
  }
  //heart rate code
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    const int Mins_Beat = 60;
    const float millisec_Seconds = 1000.0;
    long delta = millis() - last_Beat;//delta is time between beats
    last_Beat = millis();

    Beats_Per_Minute = 60 / (delta / millisec_Seconds);

    if (Beats_Per_Minute < 255 && Beats_Per_Minute > 20)//accpetable heart rate
    {
      Rates[Rate_Spot++] = (byte)Beats_Per_Minute; //Store this reading in the array
      Rate_Spot %= RATE_SIZE; //Wrap variable, rate_spot modulas of 4. if rate_spot is 4 it is reset to 0.

      //Take average of readings
      Beat_Avg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
      Beat_Avg += Rates[x];//adds the last 4 readings
      Beat_Avg /= RATE_SIZE;//divdes by 4 for average 
    }

  }
  if (irValue < 50000) // if no finger present ir vaules are larger
  {
    Beat_Avg = 0;
    Beats_Per_Minute = 0;
  }

  irValue;
  Pressure = bmp.readPressure();
  Pressure=Pressure/100;//gets hpa instead of pa
  Bmp_Temp = bmp.readTemperature();
  int Temprature = dht.readTemperature();
  int Humidity = dht.readHumidity();
  int Hand_Temp = LM35.get_temp_adder(Adder_Offset);

  if (On_Flag == 1) {
    ON_LEDS.LEDS_ON();
    Pot_Vaule = analogRead(Pot);
    Motor_Speed = Leds.Speed_Level(Pot_Vaule); //
    
    if (digitalRead(button_Off) == HIGH) {
      On_Flag = 0;
      Motor_Speed = 0;
      ON_LEDS.LEDS_OFF();
      Leds.Leds_Off();
      End = Duration();
      Total = End - Start;//total duration of attack 
      Hour = (Total / 3600);
      Min = (Total - (3600 * Hour)) / 60;
      Sec = (Total - (3600 * Hour) - (Min * 60));

      if (Side_Of_Head_Effected_Right > 0)
      {
        Side_Of_Head = "Right";
      }
      else if (Side_Of_Head_Effected_Left > 0)
      {
        Side_Of_Head = "Left";
      }
      else {
        Side_Of_Head = "None Recoreded";
      }
      
      Sd_Message = (String(Time_Hour) + ':' + String(Time_Min) + ' ' + String(Time_Date_Day) + '/' + String(Time_Month) + '\t' +
                    String(Temprature) + 'c' + '\t' + String(Humidity) + '%' + '\t' + String(Pressure) + "Pa" + ' ' + ' ' + String(Hour) + ':' + String(Min) + ':'
                    + String(Sec) + "\t\t" + String(Beat_Avg) + "Bmp" + "\t\t    " + String(Hand_Temp) + 'c' + "\t\t\t" + String(Side_Of_Head) + "\r\n");

      
      File file = SD.open("/data.txt");
      if (!file) {
        Serial.println("No SD card");
      }
      else {
        appendFile(SD, "/data.txt", Sd_Message.c_str());//sends Message with charactor return.
      }
      file.close();

    }
    dacWrite(Motor, Motor_Speed); //uses Esp32 dac to write to motors, takes an 8bit
    dacWrite(Motor2, Motor_Speed);//uses Esp32 dac to write to motors, takes an 8bit
  }
}
