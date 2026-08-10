# ⚡ ESP32 + 7-Pin OLED | BoltBunny Animation Display

A custom OLED animation project built with an ESP32 and a 0.96" 128×64 7-pin SPI OLED display.

This project brings the OLED to life with custom animations, digital rain, lightning effects, glitch transitions, subscribe animations, notification effects, particles, and the BoltBunny logo.

---

## 🎥 YouTube Video

### ▶️ Watch the Full Build

[![ESP32 + OLED Display | 7 Pins? NO PROBLEM!](https://img.youtube.com/vi/bz2c4A7cJJY/maxresdefault.jpg)](https://youtu.be/bz2c4A7cJJY)

**ESP32 + OLED Display | 7 Pins? NO PROBLEM!**

In this video, I show the complete wiring, setup, coding, and animations for the 7-pin OLED display.

---

## ✨ Features

- ⚡ BoltBunny logo animation
- 🌧️ Digital rain
- ✨ Smooth text reveal
- 📺 Controlled glitch effects
- 🔴 Subscribe animation
- ✅ Subscribed animation
- 🔔 Notification animation
- 👍 Like animation
- ↗️ Share animation
- ✨ Particle effects
- 🎬 Final logo animation

---

## 🔌 OLED Wiring

### 7-Pin OLED → ESP32

| OLED Pin | ESP32 GPIO |
| -------- | ---------- |
| GND      | GND        |
| VCC      | 3.3V       |
| D0       | GPIO 18    |
| D1       | GPIO 23    |
| RES      | GPIO 4     |
| DC       | GPIO 2     |
| CS       | GPIO 5     |

> ⚠️ This display uses **SPI**, not I2C.

---

## 📦 Components

- ESP32 Dev Board
- 0.96" 128×64 7-Pin OLED Display
- Jumper wires
- USB cable

---

## 📚 Required Library

**U8g2 by olikraus**

Install it through:

**Arduino IDE → Library Manager → Search "U8g2"**

---

## 🚀 Getting Started

1. Connect the OLED to the ESP32 using the wiring table above.
2. Install the U8g2 library.
3. Download the `.ino` file from this repository.
4. Open it in Arduino IDE.
5. Select your ESP32 board and COM port.
6. Upload the code.
7. Enjoy the BoltBunny animations! ⚡

---

## 💻 Source Code

Main Arduino sketch:

[`sketch_aug10c.ino`](sketch_aug10c.ino)

---

## ⚡ BoltBunny

**Build • Create • Experiment**

More ESP32, Arduino, electronics and DIY projects on the BoltBunny YouTube channel.

### 📺 YouTube

👉 [Watch BoltBunny on YouTube](https://youtu.be/bz2c4A7cJJY)

---

## ⭐ Support

If this project helped you:

⭐ Star this repository  
▶️ Watch the YouTube tutorial  
🔔 Subscribe to **BoltBunny**

---

Made with **ESP32 + OLED + Arduino** ⚡
