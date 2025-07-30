# 👁️ Blind Spot Detection System (BSD)

This project demonstrates a **low-cost Blind Spot Detection (BSD) system** for vehicles using **Arduino-based sensors** and logic. The system was designed, tested, and validated both in hardware (real-world prototyping) and virtually using **Proteus simulation**.

> ✅ Both the **Arduino sketch** and **Proteus project file** are included for reproduction and experimentation.

---

## 🧠 Project Concept

Blind spot detection is a key driver-assistance system that alerts the driver to obstacles in blind zones. This project implements a basic dual-side BSD prototype that detects objects using ultrasonic sensors and notifies the driver using LEDs and optional buzzer output.

---

## 🛠️ Technologies Used

- **Arduino UNO**
- **HC-SR04 ultrasonic sensors** for bench testing only
- **LED indicators**
- **Proteus 8.0+** for simulation
- **Simple timing and distance calculation logic**

---

## 📁 Files Included

| File | Description |
|------|-------------|
| `BSD_AZ_2sides_s_Final_s.ino` | Arduino sketch implementing BSD logic |
| `E-RALLY_EVER_blindSpotDetectionSys_2sides_Final.pdsprj` | Proteus simulation project file |

---

## 🧪 Simulation View

<img width="1107" height="853" alt="simulation" src="https://github.com/user-attachments/assets/0779556b-2e3b-404e-addc-68094320881e" />

---

## ⚙️ How It Works

- **Two ultrasonic sensors** are placed on both sides of the simulated vehicle.
- The system constantly checks for obstacles in the blind spot zone (distance < threshold).
- If an object is detected on either side:
  - Corresponding **LED turns ON**.
  - Optionally, a **buzzer** can sound for critical alerts (I didn't includle it).

---

## 🚀 How to Run

### 👉 In Simulation:
1. Open `E-RALLY_EVER_blindSpotDetectionSys_2sides_Final.pdsprj` using Proteus 8.
2. Upload the provided `.ino` file inside Proteus via the Arduino component.
3. Start the simulation and use virtual movement blocks to simulate obstacles.

### 👉 On Real Hardware:
1. Upload `BSD_AZ_2sides_s_Final_s.ino` to an Arduino Uno board.
2. Connect two HC-SR04 sensors on each side (e.g., Left = D2–D3, Right = D4–D5).
3. Wire LEDs to indicate detection.
4. Power the board and test using your hand or moving object.

---

## 📬 Contact

For questions, improvements, or using this in a real vehicle or competition:

**👤 Ahmed AboElyazeed**  
📧 [ahmed.abouelyazeed@gmail.com](mailto:aboelyazeed7777@gmail.com)  
🔗 [linkedin.com/in/ahmedaboelyazeed](https://www.linkedin.com/in/ahmed-aboelyazeed-43ba22231/)

---
