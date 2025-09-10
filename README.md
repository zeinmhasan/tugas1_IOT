# tugas1_IOT

buat program menggunakan Anduino IDE yang dapat: Mengukur jarak menggunakan sensor HC-SR04, membaca suhu dan kelembaban menggunakan sensor DHT11, serta menampilkan data tersebut secara real-time ke serial monitor.

## A. rancangan IOT

<img width="723" height="632" alt="Image" src="https://github.com/user-attachments/assets/f59246ae-9bed-4522-a20a-82c931173cce" />

![Image](https://github.com/user-attachments/assets/d6fad7e9-2dd0-4bcd-8c96-42ed629df811)

### ** Sensor Ultrasonik HC-SR04**
- **VCC** → **5V Arduino**
- **GND** → **GND Arduino**
- **TRIG** → **Pin 12 Arduino**
- **ECHO** → **Pin 13 Arduino**

### ** Sensor DHT11**
- **VCC** → **5V Arduino**
- **GND** → **GND Arduino**
- **Data** → **Pin 2 Arduino**

### ** LED Merah**
- **Kaki Anoda (+)** → **Resistor 220Ω** → **Pin 6 Arduino**
- **Kaki Katoda (–)** → **GND Arduino**

## B. Komponen yang Digunakan

| **No** | **Komponen**                  | **Fungsi**                                                                        |
|--------|-------------------------------|------------------------------------------------------------------------------------|
| 1      | **Arduino UNO R3**            | Sebagai mikrokontroler utama untuk memproses data dari sensor dan mengontrol LED.  |
| 2      | **Sensor Ultrasonik HC-SR04** | Mengukur jarak objek berdasarkan pantulan gelombang ultrasonik.                    |
| 3      | **Sensor DHT11**              | Mengukur suhu dan kelembapan udara di sekitar perangkat.                           |
| 4      | **LED Merah**                 | Sebagai indikator visual peringatan jika jarak objek terlalu dekat.                |
| 5      | **Resistor 220Ω**             | Mengatur arus yang mengalir ke LED agar tidak rusak.                               |
| 6      | **Kabel Jumper & Breadboard** | Untuk menghubungkan komponen.                                                      |
| 7      | **Sumber Daya 5V**            | Memberi daya pada rangkaian Arduino dan sensor.                                    |


## C. Penjelasan Kode Program

### a. Library dan Konstanta

```cpp
#include <DHT.h>
#define TRIG_PIN 12
#define ECHO_PIN 13
#define LED_PIN 6
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
```

- **DHT.h** → Library untuk membaca suhu dan kelembapan.
- **TRIG_PIN** → Pin trigger HC-SR04.
- **ECHO_PIN** → Pin echo HC-SR04.
- **LED_PIN** → Pin LED indikator.
- **DHTPIN** → Pin data sensor DHT11.

### b. Setup awal

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  dht.begin();
}
```

- **Menginisialisasi komunikasi Serial** dengan baudrate **9600**.
- **Menetapkan mode pin** untuk sensor ultrasonik dan LED.
- **Memulai sensor DHT11**.

### C. Mengukur jarak

```cpp
digitalWrite(TRIG_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);

long duration = pulseIn(ECHO_PIN, HIGH);
float distance = duration * 0.034 / 2;
```


- **Sensor HC-SR04** memancarkan gelombang ultrasonik.
- Fungsi **pulseIn()** membaca waktu pantulan gelombang.
- **Rumus perhitungan jarak:**

- jarak = waktu * 0.034 / 2

- **0.034 cm/μs** adalah kecepatan suara.

### D. Membaca Suhu dan Kelembapan

```cpp
float suhu = dht.readTemperature();
float kelembapan = dht.readHumidity();
```

- **Sensor DHT11** membaca:
  - **Suhu** → dalam °C.
  - **Kelembapan** → dalam persen (%).

### E. Menampilkan Data ke Serial Monitor

```cpp
Serial.print("Jarak: ");
Serial.print(distance);
Serial.print(" cm |");
Serial.print(" Suhu: ");
Serial.print(suhu);
Serial.print(" °C | Kelembapan: ");
Serial.print(kelembapan);
Serial.println(" %");
```
### F. Logika Kontrol LED

```cpp
if (distance < 15) {
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
} else {
  digitalWrite(LED_PIN, LOW);
}
```

- Jika **jarak < 15 cm** → **LED berkedip 10 kali**.
- Jika **jarak ≥ 15 cm** → **LED tetap mati**.


