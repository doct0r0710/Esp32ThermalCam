# Esp32ThermalCam

## What is it

An ESP32-CAM and Mabee MLX90640 based thermal camera implementation.

## How it works

- Sets up microbolometer and camera with predefined parameters
- ESP32 connects to a WiFi or starts its own network if connection has failed
- Starts an mDNS responder (for ease of location on a network)
- Starts a web server serving a static file and a websocket server
- The main loop begins:
    - Takes a still picture with the color camera into memory
    - Takes a reading from the microbolometer into memory (right beside the color picture)
    - Sends it to connected clients over binary WebSockets
    - Counts sent message
        - Every 30 message there's also a status message sent over clear text WebSockets 

The webpage displays the color picture with a canvas overlaid with the thermal readings. There are a few color palettes it can assign to each thermal value, a bit of legend, and some settings in limiting the displayed thermal values or manipulating the display. There's also a capture button which exports the viewfinder part of the screen into a JPEG (this part uses [dom-to-image](https://github.com/tsayen/dom-to-image) script, included in index.html and html.h).

## Files
- Esp32ThermalCam.ino - main code running on ESP32
- html.h - Served static web page, moved to another file for clarity
- index.html - The same static file that's in html.h, for ease of debugging when running a local server on a development machine  

## Libraries used

- Basic ESP32 libraries - For WiFi, camera and mDNS
-  [Adafruit MLX90640 library](https://github.com/adafruit/Adafruit_MLX90640) - for thermal module setup and use
-  [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) - for ESPAsyncWebServer
-  [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) - for serving the webpage and handling websockets
-  [dom-to-image](https://github.com/tsayen/dom-to-image) - for ease of saving images (could probably done this with only the canvas, but it was late and I was sleepy)

## Other thoughts

This is nowhere near a proper proper implementation of any of this, please do not use this in any mission critical situation. I mainly used this to figure out where the hot water pipes are in my walls.
Also, it seems like the ESP32 board I'm using is not up to running both the cameras and the WiFi at the same time, and the thing gets locked up after about 5-10 minutes of use, but keeps going strong if I don't enable the color camera. I'm currently considering removing the color camera entirely, and using my phones camera instead, while attaching the thermal module close to it to get a similar field of view. When done, I'll post that code in a different repository.