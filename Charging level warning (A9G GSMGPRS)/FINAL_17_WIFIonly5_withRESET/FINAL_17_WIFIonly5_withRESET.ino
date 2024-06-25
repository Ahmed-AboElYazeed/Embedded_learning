#include <HardwareSerial.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <float.h> // Include float.h to use FLT_MAX

// Constants
#define BUTTON_PIN 5
#define MIN_SOC 10
#define MAX_LOCATIONS 10
#define BING_API_KEY "BING_API_KEY" // Replace with your actual Bing API key
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define MAX_RETRIES 50

// Global Variables
int SOC = 0; // State of Charge or any other relevant metric

// Structures
struct Location {
  String name;
  float latitude;
  float longitude;
  float distance;
  int duration;
};

// Special locations
Location locations[MAX_LOCATIONS]; // Array to hold up to 10 {MAX_LOCATIONn} locations
int numLocations = 0; // Number of locations added

// Hardware Serial for A9G
HardwareSerial A9G(2);

// Function Prototypes
void setup();
void loop();
void getGPSAndSendRequest();
bool getGPS(float &latitude, float &longitude, int &retries);
bool sendHTTPRequest(float originLat, float originLon, Location *locations, int numLocations);
void parseAndFindNearestLocation(String response, Location *locations, int numLocations);
void connectToWiFi();
void addLocation(String name, float latitude, float longitude);
void resetA9G();

/*******************CODE*******************/

void setup() {
  Serial.begin(115200);
  A9G.begin(115200, SERIAL_8N1, 16, 17); // RX and TX pins

  pinMode(BUTTON_PIN, INPUT_PULLUP); // System activated when the pin is connected to LOW

  Serial.println("System Initialized");

  connectToWiFi();

  // Adding initial locations
  addLocation("Helwan University", 29.851133574075643, 31.342158396219638);
  //addLocation("Helwan ElMatariya", 30.12252380856833, 31.32569019480295);
  addLocation("Home 2", 29.97272096359816, 31.252989033786637);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW || SOC < MIN_SOC) {
    getGPSAndSendRequest();
    delay(30000); // Wait for 30 seconds before next reading
  }
}

/*************<<<<<<<<<<*MAIN_SYS*>>>>>>>>>>*************/

void getGPSAndSendRequest() {
  float latitude, longitude;
  int retries = 0;
  if (getGPS(latitude, longitude, retries)) {
    Serial.printf("Got GPS: %f, %f\n", latitude, longitude);    //untill here avery thisg is good.
  } else {
    latitude = 29.000000; // Dummy value
    longitude = 31.000000; // Dummy value
    Serial.println("Using Dummy GPS values");
  }

  Serial.printf("Number of retries to get GPS: %d\n", retries);

  sendHTTPRequest(latitude, longitude, locations, numLocations);
}

/*************<<<<<<<<<<*A9G_GPS*>>>>>>>>>>*************/

bool getGPS(float &latitude, float &longitude, int &retries) {  //good
  A9G.println("AT+GPS=1"); // Turn on GPS
  delay(2000);

  retries = 0;
  while (retries < MAX_RETRIES) {
    A9G.println("AT+LOCATION=2");
    delay(2000);

    while (A9G.available()) {
      String gpsData = A9G.readStringUntil('\n');
      if (gpsData.indexOf("+LOCATION: GPS NOT FIX NOW") != -1) {
        retries++;
        break;
      } else if (gpsData.indexOf(",") != -1) {
        int commaIndex = gpsData.indexOf(",");
        latitude = gpsData.substring(0, commaIndex).toFloat();
        longitude = gpsData.substring(commaIndex + 1).toFloat();
        return true;
      }
    }
  }

  if (retries >= MAX_RETRIES) {
    resetA9G(); // Reset the A9G module if retries exceed MAX_RETRIES
  }

  return false;
}

/*************<<<<<<<<<<*HTTP_Request*>>>>>>>>>>*************/
//http://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=30.123697,31.325476&destinations=29.851133574075643,31.342158396219638  

bool sendHTTPRequest(float originLat, float originLon, Location *locations, int numLocations) {
  String url = "http://dev.virtualearth.net/REST/v1/Routes/DistanceMatrix?origins=";
  url += String(originLat) + "," + String(originLon);
  url += "&destinations=";

  for (int i = 0; i < numLocations; i++) {
    if (i > 0) url += ";";
    url += String(locations[i].latitude) + "," + String(locations[i].longitude);
  }

  url += "&travelMode=driving&key=" + String(BING_API_KEY);

  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String response = http.getString();
    parseAndFindNearestLocation(response, locations, numLocations);
    http.end();
    return true;
  } else {
    Serial.println("Error on HTTP request");
    http.end();
    return false;
  }
}

/*************<<<<<<<<<<*Nearest_Location*>>>>>>>>>>*************/

void parseAndFindNearestLocation(String response, Location *locations, int numLocations) {
  StaticJsonDocument<2048> doc;
  deserializeJson(doc, response);

  float minDistance = FLT_MAX;
  String nearestLocationName;
  for (int i = 0; i < numLocations; i++) {
    float distance = doc["resourceSets"][0]["resources"][0]["results"][i]["travelDistance"];
    int duration = doc["resourceSets"][0]["resources"][0]["results"][i]["travelDuration"];

    locations[i].distance = distance;
    locations[i].duration = duration;

    if (distance < minDistance) {
      minDistance = distance;
      nearestLocationName = locations[i].name;
    }
  }

  Serial.println("Nearest Location: " + nearestLocationName);
  Serial.print("Distance: ");
  Serial.println(minDistance);
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
}



void addLocation(String name, float latitude, float longitude) {
  if (numLocations < MAX_LOCATIONS) {
    locations[numLocations].name = name;
    locations[numLocations].latitude = latitude;
    locations[numLocations].longitude = longitude;
    numLocations++;
  } else {
    Serial.println("Location array is full. Cannot add more locations.");
  }
}



void resetA9G() {
  A9G.println("AT+RST=1");
  delay(2000);

  while (true) {
    if (A9G.available()) {
      String response = A9G.readStringUntil('\n');
      Serial.println(response); // Print the response for debugging
      if (response.indexOf("READY") != -1) {
        Serial.println("A9G Module Reset and Ready");
        break;
      }
    }
    delay(100);
  }
}
