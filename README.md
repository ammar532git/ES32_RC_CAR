# ESP32 Wi-Fi Controlled RC Car 🚗📡

A DIY RC car built with an **ESP32**, a **BO (Battery Operated) gear motor** pair, and an **L298N motor driver**, controlled wirelessly through a **mobile-friendly web app** hosted directly on the ESP32. No app installation needed — just connect to the car's Wi-Fi and drive from your phone's browser.

---

## 📋 Table of Contents

- [Features](#-features)
- [Hardware Used](#-hardware-used)
- [Circuit / Wiring Diagram](#-circuit--wiring-diagram)
- [Pin Connections](#-pin-connections)
- [How It Works](#-how-it-works)
- [Getting Started](#-getting-started)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Media Gallery](#-media-gallery)
- [Future Improvements](#-future-improvements)
- [License](#-license)

---

## ✨ Features

- 📱 Control via any smartphone browser — no app install required
- 📡 ESP32 hosts its own Wi-Fi Access Point (no home router needed)
- 🕹️ Touch-button control pad: Forward, Backward, Left, Right, Back-Left, Back-Right, Stop
- ⚙️ Simple and beginner-friendly wiring using an L298N motor driver
- 🔓 Fully open-source code, easy to extend (add speed control, sensors, camera, etc.)

---

## 🛠 Hardware Used

| Component | Quantity |
|---|---|
| ESP32 Dev Board | 1 |
| BO Motors (Gear Motors) | 2 (or 4 depending on chassis) |
| L298N Motor Driver Module | 1 |
| Robot Chassis + Wheels | 1 set |
| Battery Pack (e.g. 2x 18650 Li-ion / 7.4–12V) | 1 |
| Jumper Wires | as needed |
| On/Off Switch (optional) | 1 |

---

## 🔌 Circuit / Wiring Diagram

> See the wiring photos in the `media/images/` folder.

### Pin Connections

| ESP32 Pin | L298N Pin | Function |
|---|---|---|
| GPIO 14 | IN1 | Left Motor Forward |
| GPIO 12 | IN2 | Left Motor Backward |
| GPIO 26 | IN3 | Right Motor Forward |
| GPIO 27 | IN4 | Right Motor Backward |
| GPIO 32 | ENA | Left Motor Enable |
| GPIO 33 | ENB | Right Motor Enable |
| GND | GND | Common Ground |

> ⚠️ **Note:** In this version, `ENA`/`ENB` are held permanently `HIGH` (full speed, always on) because the driver board's enable jumper caps were missing. If your L298N has the jumpers intact, you can remove `ENA`/`ENB` control from the code, or better — use `analogWrite()`/`ledcWrite()` on these pins for adjustable speed control (see [Future Improvements](#-future-improvements)).

The L298N is powered separately from the battery pack (motor supply), while the ESP32 can be powered via USB or the 5V output of the L298N's onboard regulator (if present and rated for it).

---

## ⚙️ How It Works

1. On boot, the ESP32 starts a **Wi-Fi Access Point** named `ESP32_RC_Car` (password: `12345678`).
2. It hosts a lightweight **web server** that serves an HTML/JS control pad.
3. Connect your phone to the `ESP32_RC_Car` Wi-Fi network and open `192.168.4.1` in any browser.
4. Pressing a direction button sends an HTTP request (e.g. `/F` for forward) to the ESP32.
5. The ESP32 receives the request and drives the corresponding motor pins via the L298N to move the car.
6. Releasing the button sends a `/S` (stop) request, halting the motors.

---

## 🚀 Getting Started

### Option A: Using PlatformIO (recommended)

1. Install [VS Code](https://code.visualstudio.com/) + the [PlatformIO extension](https://platformio.org/install/ide?install=vscode).
2. Clone this repository:
   ```bash
   git clone https://github.com/<your-username>/<your-repo-name>.git
   cd <your-repo-name>
   ```
3. Open the folder in VS Code with PlatformIO.
4. Connect your ESP32 board via USB.
5. Click **Upload** (or run `pio run --target upload`).

### Option B: Using Arduino IDE

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add ESP32 board support via the Boards Manager ([guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)).
2. Copy the contents of `src/main.cpp` into a new sketch (rename it to match your sketch folder, e.g. `RC_Car.ino`).
3. Select your ESP32 board and correct COM port under **Tools**.
4. Click **Upload**.

---

## 📱 Usage

1. Power on the car.
2. On your phone, go to Wi-Fi settings and connect to:
   - **SSID:** `ESP32_RC_Car`
   - **Password:** `12345678`
3. Open a browser and navigate to `http://192.168.4.1`
4. Use the on-screen buttons to drive the car:
   - **FWD** / **BWD** — move forward / backward
   - **LEFT** / **RIGHT** — turn on the spot
   - **B-LFT** / **B-RGT** — arc/reverse turns
   - **STOP** — stop all motors

---

## 📁 Project Structure

```
ESP32_RC_Car/
├── src/
│   └── main.cpp          # Main firmware code
├── media/
│   ├── images/            # Build photos, wiring diagrams, screenshots
│   └── videos/            # Demo/test drive videos
├── docs/                  # Extra documentation (optional)
├── platformio.ini         # PlatformIO project configuration
├── LICENSE
└── README.md
```

---

## 🖼️ Media Gallery

Project photos and demo videos are available in the repo:

- 📷 Images: go to the `media/images/` folder
- 🎥 Videos: go to the `media/videos/` folder

---

## 🔮 Future Improvements

- [ ] PWM-based speed control using `ledcWrite()` on ENA/ENB instead of permanent HIGH
- [ ] Joystick-style control instead of button pad
- [ ] Live camera streaming (ESP32-CAM module)
- [ ] Obstacle avoidance using ultrasonic sensor
- [ ] Battery voltage monitoring/display on web UI
- [ ] Switch from Access Point mode to Station mode for control over home Wi-Fi/internet

---

## 📄 License

This project is licensed under the [MIT License](LICENSE) — feel free to use, modify, and share.

---

**Made with ❤️ and a lot of jumper wires.**
