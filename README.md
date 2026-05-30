# Smart IoT Billing and Weighing System

A full-stack IoT-enabled smart billing and weighing system developed using ESP32, React.js, Node.js, and MongoDB. The system automates product weighing, QR code-based product identification, cloud database integration, and bill generation for retail and supermarket applications.

---

## Overview

Traditional billing systems require manual product identification and weight entry, leading to increased checkout time and potential human errors. This project automates the entire weighing and billing process by integrating embedded hardware with a cloud-connected software platform.

The system uses an ESP32-based weighing unit to measure product weight using a load cell and HX711 amplifier. Product information is retrieved through QR code scanning, while billing and inventory management are handled through a React frontend and Node.js backend connected to MongoDB.

---

## Key Features

* Real-time weight measurement using Load Cell and HX711
* ESP32-based embedded weighing system
* Wi-Fi enabled communication
* QR code-based product identification
* Automatic billing generation
* MongoDB cloud database integration
* Product inventory management
* LCD-based weight display
* JSON-based communication protocol
* Receipt/Banner printing support
* User-friendly billing interface

---

## System Architecture

1. Product QR code is scanned.
2. Product details are retrieved from MongoDB.
3. ESP32 acquires weight from the load cell.
4. Weight data is transmitted over Wi-Fi.
5. Billing application calculates the final amount.
6. Product details are added to the bill.
7. Billing information is displayed and stored.
8. Receipt/banner can be printed for the customer.

---

## Hardware Components

* ESP32 Development Board
* HX711 Load Cell Amplifier
* Load Cell
* 16x2 LCD Display
* Push Button
* Buzzer
* Thermal Printer Interface
* Wi-Fi Network

---

## Software Technologies

### Embedded Systems

* Embedded C/C++
* Arduino IDE
* ESP32 Wi-Fi Stack
* ArduinoJson Library
* HX711 Library

### Backend

* Node.js
* Express.js
* MongoDB
* Mongoose
* REST APIs

### Frontend

* React.js
* JavaScript
* QR Scanner Integration
* Fetch API

---

## Project Structure

```text
IoT_Weighing_Machine/
│
├── firmware/
│   └── esp32_weighing_system.ino
│
├── backend/
│   ├── index.js
│   ├── productModel.js
│   └── package.json
│
├── frontend/
│   ├── package.json
│   └── src/
│       ├── App.js
│       ├── Billing.js
│       ├── Header.js
│       ├── ProductTable.js
│       └── QrScanner.js
│
├── images/
│
└── README.md
```

---

## Applications

* Smart Retail Stores
* Automated Checkout Systems
* Supermarkets
* Inventory Management Systems
* Smart Shopping Platforms
* IoT-Based Retail Automation

---

## Skills Demonstrated

* Embedded Firmware Development
* ESP32 Programming
* Sensor Interfacing
* IoT Communication
* REST API Development
* Full-Stack Application Development
* MongoDB Database Management
* React Frontend Development
* Real-Time Data Processing

---

## Future Enhancements

* Mobile Application Integration
* RFID-Based Product Identification
* Digital Payment Gateway Integration
* Cloud Analytics Dashboard
* Inventory Forecasting
* AI-Based Customer Insights

---

## Author

**Augustin C Abraham**

MSc Electronics

Embedded Systems | IoT | Verilog HDL | Semiconductor Enthusiast
