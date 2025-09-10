#include <DHT.h>

// Konfigurasi pin HC-SR04
#define TRIG_PIN 12
#define ECHO_PIN 13

// Pin LED
#define LED_PIN 6

// Konfigurasi sensor DHT11
#define DHTPIN 2       // Pin data DHT11
#define DHTTYPE DHT11  // Tipe sensornya
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // LED sebagai OUTPUT

  dht.begin(); // Mulai sensor DHT11
}

void loop() {
  // ==== Ultrasonik ====
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;

  // ==== DHT11 ====
  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  // Tampilkan di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.print(" cm |");
  Serial.print(" Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C | Kelembapan: ");
  Serial.print(kelembapan);
  Serial.println(" %");

  // ==== LED Kelap-kelip jika jarak < 15 cm ====
  if (distance < 15) {
    // LED berkedip 5 kali
    for (int i = 0; i < 10; i++) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  } else {
    digitalWrite(LED_PIN, LOW); // LED mati jika jarak >= 15 cm
  }

  delay(1000);
}
