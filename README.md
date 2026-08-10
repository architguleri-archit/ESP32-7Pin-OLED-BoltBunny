# ⚡ ESP32 + 7-Pin OLED | BoltBunny Animation Display 🌧️

Turn a tiny **0.96" 128×64 7-pin OLED display** into a cool animated display using an **ESP32**!

This project uses an **SPI OLED connection** to create custom animations including digital rain, lightning effects, glitch transitions, subscribe animations, notifications, particles, and the BoltBunny logo.

---

## ✨ Features

- ⚡ BoltBunny lightning logo animation
- 🌧️ Digital rain effect
- ✨ Smooth BoltBunny text reveal
- 📺 Clean glitch animation
- 🔴 Subscribe animation
- ✅ Subscribed animation
- 🔔 Notification animation
- 👍 Like animation
- ↗️ Share animation
- ✨ Particle effects
- 🎬 Final BoltBunny logo animation
- 🚀 Runs directly on ESP32
- 💾 Complete Arduino source code included

---

## 🔌 OLED Wiring

### 📟 7-Pin OLED to ESP32

| **OLED Pin** | **ESP32 GPIO** |
|--------------|----------------|
| GND          | GND            |
| VCC          | 3.3V           |
| D0           | GPIO 18        |
| D1           | GPIO 23        |
| RES          | GPIO 4         |
| DC           | GPIO 2         |
| CS           | GPIO 5         |

> ⚠️ This OLED uses **SPI**, not I2C.

---

## 📦 Components Required

- ESP32 Dev Board
- 0.96" 128×64 7-Pin OLED Display
- Jumper wires
- USB cable

---

## 📚 Required Library

This project uses the **U8g2 OLED library**.

Install:

```text
U8g2 by olikraus
