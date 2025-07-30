# 🔋 Charging Level Warning & Vehicle Connectivity System  
**EVER 2024 (Electric Vehicle Rally in EGYPT) – Telemetry & Alert System**

This project documents the design and implementation of a **real-time charging level warning and vehicle telemetry system** used in Shell Eco-marathon 2025. It was designed to send data wirelessly to an online dashboard, warn the driver of critical charge levels, and offer dual connectivity via **Wi-Fi or GPRS**.

> ⚠️ This repository does not include source code or hardware schematics due to competition confidentiality. However, the workflow, system architecture, and visual documentation are provided.

---

## 🚀 Project Overview

The system was designed for integration into an electric vehicle prototype. It enables:
- Real-time data plotting (speed, current, voltage, SOC, location)
- Dual connectivity: **Wi-Fi** and/or **GPRS** fallback
- **On-vehicle display warning** for SOC drop
- Data syncing to a **cloud-based dashboard**

---

## 🛠️ System Versions

Several versions of the system were developed and tested:

- ✅ `FINAL_17_WIFIonly5_withRESET` – Stable Wi-Fi-only version with reset protection
- ✅ `FINAL_22_GPRSonly7` – Cellular-based version for remote locations
- ✅ `FINAL_23_GPRSorWIFI` – Intelligent dual-mode version with fallback support

Each version included debugging features, hardware reset control, and compatibility with the embedded display screen.

---

## 🔧 System Architecture & Visual Documentation

### 📸 1. Final In-Vehicle System Setup
![final actual system connection](https://github.com/user-attachments/assets/15e1b0f6-0e73-4422-83f3-0f5bb86c3ee7)

### 🧩 2. Full Circuit Diagram
![system circuit connection diagram](https://github.com/user-attachments/assets/50d36adb-5372-483f-8729-95b091ca67ba)

### 📈 3. Functional System Diagram
![system diagram](https://github.com/user-attachments/assets/9fd6a30f-b5bc-41d7-9da2-6243d8a71fda)

### 🌐 4. Online Dashboard (Web-based)
![vehicle online dashboard for plotting mesurments and location](https://github.com/user-attachments/assets/3ec9a8f6-5b93-4b5a-af67-87f9d70afae7)

### 🚘 5. Driver Screen During Operation
![vehicle screen (when system activated)](https://github.com/user-attachments/assets/9ad93de1-b8b3-4152-933f-52d682cf2c87)

---

## 💡 Key Features

- Real-time data collection (SOC, speed, current, voltage, GPS)
- Web-based dashboard with interactive graphs and map
- Emergency warning when SOC drops below safe threshold
- Dual communication fallback: Wi-Fi → GPRS
- Custom PCB integration with ESP32 and A9G modules

---

## 📬 Contact

If you’re building a similar telemetry or vehicle alert system and want support:

**👤 Ahmed AboElyazeed**  
📧 [aboelyazeed7777@gmail.com](mailto:aboelyazeed7777@gmail.com)  
🔗 [linkedin.com/in/ahmedaboelyazeed](https://www.linkedin.com/in/ahmed-aboelyazeed-43ba22231/)

---

## 🙏 Acknowledgements

Developed as part of the **Helwan Racing Team's** vehicle for the **EVER 2024 (Electric Vehicle Rally in EGYPT)**, this system was designed with reliability, low latency, and safety in mind — enabling a fully connected, efficient prototype EV.
