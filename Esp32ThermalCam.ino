// Import required libraries
#include <WiFi.h>
#include <Adafruit_MLX90640.h>
#include <esp_camera.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include "html.h"

// Bolometer - Replace with your own pinout
#define I2C_SCL 13
#define I2C_SDA 12

// Camera - Currently setup according to AI-Thinker board,
// Replace with your own setup if needed.
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// Replace with your network credentials
const char *ssid = "***";
const char *password = "***";
// Replace with your preferred network name (when previous network is not available)
const char *apssid = "Thermal";

// Bolometer stuff
Adafruit_MLX90640 mlx;
const size_t thermSize = (32 * 24) * sizeof(float);
const size_t frameSize = thermSize + 30000 * sizeof(char);
size_t imageSize = 0;
char frame[frameSize]; // buffer for full frame of temperatures and image

// Websocket stuff
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Sends log messages to websockets if true
bool wsdebug = false;

void log(String text)
{
  Serial.println(text);
  if (wsdebug)
  {
    ws.textAll("SERIAL:" + text);
  }
}

void sendStatus()
{
  log("Sending status");
  String status = "STATUS:Total heap:" + String(ESP.getHeapSize()) += " | Free heap:" + String(ESP.getFreeHeap()) += " | WiFi RSSI:" + String(WiFi.RSSI()) += " | WiFi Status:" + String(WiFi.status());
  ws.textAll(status);
  log("Sent status");
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
  {
    data[len] = 0;
    String command = String((char *)data);
    if (command == "status")
    {
      sendStatus();
    }
    if (command == "debug")
    {
      wsdebug = !wsdebug;
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len)
{
  switch (type)
  {
  case WS_EVT_CONNECT:
    break;
  case WS_EVT_DISCONNECT:
    break;
  case WS_EVT_DATA:
    handleWebSocketMessage(arg, data, len);
    break;
  case WS_EVT_PONG:
  case WS_EVT_ERROR:
    break;
  }
}

void connectWifi(const char *ssidname, const char *pass)
{
  log("Connecting to " + String(ssidname));
  WiFi.begin(ssidname, pass);
  delay(5000);
}

void setupWifiAp(const char *ssidname, const char *pass)
{
  WiFi.mode(WIFI_AP);
  WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);
  WiFi.softAP(ssidname, pass);
  delay(5000);
}

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  log("Setting up bolometer");
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.beginTransmission(MLX90640_I2CADDR_DEFAULT);
  
  mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire);
  mlx.setMode(MLX90640_CHESS);
  mlx.setResolution(MLX90640_ADC_16BIT);
  mlx90640_resolution_t res = mlx.getResolution();
  mlx.setRefreshRate(MLX90640_16_HZ);
  mlx90640_refreshrate_t rate = mlx.getRefreshRate();
  Wire.setClock(1000000); // max 1 MHz
  log("Bolometer setup");

  log("Setting up camera");
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 10000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;
  esp_err_t err = esp_camera_init(&config);
  sensor_t *s = esp_camera_sensor_get();
  log("Camera setup");

  log("Setting up WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWifi(apssid, password);
    if (WiFi.status() != WL_CONNECTED)
    {
      connectWifi(ssid, password);
      if (WiFi.status() != WL_CONNECTED)
      {
        setupWifiAp(apssid, password);
      }
    }
  }
  log("WiFi setup");

  log("Setting up MDNS as thermal");
  MDNS.begin("thermal");
  log("MDNS setup");

  log("Setting web server");
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html); });
  server.begin();
  log("Webserver setup");

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
}


void take_snapshot()
{
  camera_fb_t *fb = NULL;
  fb = esp_camera_fb_get();
  if (!fb)
  {
    log("Camera capture failed. Restarting");
    ESP.restart();
  }
  log("Moving image to frame buffer " + String(fb->len) + " + " + String(thermSize) + " < " + String(frameSize));
  memcpy(&frame[thermSize], fb->buf, fb->len);
  log("Image moved to frame buffer");
  imageSize = fb->len;
  esp_camera_fb_return(fb);
  fb = NULL;
}

void take_thermal()
{
  log("Taking thermal data to buffer");
  mlx.getFrame((float *)frame);
  log("Thermal data taken");
}

unsigned long messageTimestamp = 0;
int messageCounter = 0;

void loop()
{
  ws.cleanupClients();
  uint64_t now = millis();
  if (now - messageTimestamp > 150)
  {
    memset(frame, 0, frameSize);
    take_thermal();
    take_snapshot();
    log("Sending data");
    ws.binaryAll(frame, thermSize + imageSize);
    log("Data sent");
    messageTimestamp = now;
    messageCounter++;
    if (messageCounter > 30)
    {
      sendStatus();
      messageCounter = 0;
    }
  }
}
