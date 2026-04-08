# posttest2-praktikum-iot-unmul-2026
KELOMPOK 5 - A
Cellia Auzia Nugraha 2309106005
Oktaria Indi Cahyani 2309106015
Al Hajj Fauzan 2309106019

Perancangan Smart House dengan Sistem Pencahayaan dan Keamanan Terintegrasi Berbasis Telegram Bot Menggunakan Sensor DHT11 dan MQ-2

Sistem yang dibuat untuk mengontrol LED berfungsi untuk menyalakan dan mematikan lampu melalui Telegram Bot. Sistem ini juga dilengkapi sensor DHT11 untuk mengecek suhu dan kelembapan ruangan dan MQ-2 gas sensor untuk mendeteksi kebocoran gas. Jika terdeteksi gas bocor, sistem akan mengirimkan notifikasi peringatan kepada pengguna melalui telegram.

Pembagian tugas:

Cellia : Mengoding kedua sensor(dht11, gas sensor), membuat board schematic.

Oktaria : Merakit komponen, Mengoding bagian LED.

Al Hajj : buat dan integrasi Telegram Bot, merakit komponen.

Pembuatan sistem ini menggunakan komponen:
- 4 LED
- 1 microprocessor (ESP32) dengan tambahan expansion board 30P
- Jumper
- 1 Half Breadboard
- 1 MQ-2 Gas Sensor
- 1 DHT 11
- 1 Kabel USB C

Board Schematic:
<img width="1024" height="884" alt="Screenshot 2026-04-08 125651" src="https://github.com/user-attachments/assets/33c17c00-fd23-4e6b-b703-2ac03c804190" />

Note: Dikarenakan Wokwi tidak menyediakan komponen expansion board 30P dan sensor DHT11, board schematic dibuat semirip mungkin dengan rancangan asli menggunakan komponen alternatif yang tersedia pada platform.
