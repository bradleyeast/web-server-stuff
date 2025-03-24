#include <WiFi.h>
#include <Servo.h>

const char* ssid = "Spot-Mesh";  
const char* password = "Whatever1";

// Motor Control (H-Bridge)
#define MOTOR_FORWARD 11
#define MOTOR_BACKWARD 12

// Servo Six board controls
#define STEERING_PIN 3
#define TURRET_HORZ_PIN 4
#define TURRET_VERT_PIN 5
#define FIRE_PIN 6

Servo steeringServo;
Servo turretHorzServo;
Servo turretVertServo;
Servo fireServo;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.print("Pico Server IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

  // Attach servos
  steeringServo.attach(STEERING_PIN);
  turretHorzServo.attach(TURRET_HORZ_PIN);
  turretVertServo.attach(TURRET_VERT_PIN);
  fireServo.attach(FIRE_PIN);

  // Motor setup
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(MOTOR_BACKWARD, OUTPUT);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    if (request.indexOf("command=forward") != -1) moveForward();
    else if (request.indexOf("command=backward") != -1) moveBackward();
    else if (request.indexOf("command=steer_left") != -1) steeringServo.write(45);
    else if (request.indexOf("command=steer_right") != -1) steeringServo.write(135);
    else if (request.indexOf("command=turret_left") != -1) turretHorzServo.write(0);
    else if (request.indexOf("command=turret_right") != -1) turretHorzServo.write(180);
    else if (request.indexOf("command=turret_up") != -1) turretVertServo.write(180);
    else if (request.indexOf("command=turret_down") != -1) turretVertServo.write(0);
    else if (request.indexOf("command=fire") != -1) fire();

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html><body><h1>Command Executed</h1></body></html>");
    client.stop();
  }
}

void moveForward() {
  digitalWrite(MOTOR_FORWARD, HIGH);
  digitalWrite(MOTOR_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_FORWARD, LOW);
  digitalWrite(MOTOR_BACKWARD, HIGH);
}

void fire() {
  fireServo.write(45);
  delay(500);
  fireServo.write(90);
}
