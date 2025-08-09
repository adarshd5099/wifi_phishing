ESP32 Captive Portal Wi-Fi Login Page

This project creates a fake Wi-Fi login portal using an ESP32 in Access Point (AP) mode with a DNS redirection (captive portal) feature.
When a device connects to the ESP32's hotspot, any web request will be redirected to a custom HTML login page that looks like an institutional Wi-Fi login screen.

⚠ Disclaimer
This project is for educational and security testing purposes only.
Do NOT deploy in public networks or use it to collect credentials without permission — doing so may be illegal in your country.
✨ Features

    📶 ESP32 running in AP (Access Point) mode

    🌐 DNS redirection for captive portal effect

    🎨 Custom HTML/CSS login page with a logo

    📁 Uses LittleFS to serve static files and store logs

    📝 Saves submitted usernames and passwords to log.txt

    🖼 Serves a custom logo (logo.png) on the login page

🛠 Hardware & Software Requirements

    ESP32 board (tested on ESP32 DevKit V1)

    Arduino IDE (2.3 or later)

    Libraries:

        WiFi.h (built-in)

        ESPAsyncWebServer

        DNSServer.h

        LittleFS

📂 File Structure

/ESP32-Captive-Portal
│── ESP32_CaptivePortal.ino      # Main Arduino sketch
│── data/
│    ├── logo.png            # Logo displayed on the portal
│    └── log.txt                 # Saved credentials
│── README.md

🚀 How It Works

    The ESP32 creates a Wi-Fi hotspot named ABC_Admin (no password by default).

    The DNS server redirects all requests to the ESP32’s IP address.

    The user is served a fake Wi-Fi login page.

    Any entered credentials are appended to log.txt in LittleFS.

    Logs can be viewed by visiting:

    http://192.168.4.1/ABC_Admin7901234

🔧 Setup & Installation

    Clone this repository:

    git clone https://github.com/<your-username>/<your-repo>.git

    Open the project in Arduino IDE.

    Install required libraries listed above.

    Upload logo.png and an empty log.txt to ESP32’s LittleFS:

    Using Little FS Command linetool

    Upload the sketch to your ESP32.

    Open Serial Monitor to see the assigned AP IP (default: 192.168.4.1).


⚠ Legal & Ethical Notes

    This project can capture sensitive data.

    Use only in a controlled, authorized test environment (e.g., penetration testing lab, CTF challenge).

    The author is not responsible for any misuse.


