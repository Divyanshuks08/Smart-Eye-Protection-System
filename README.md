# Smart-Eye-Protection-System
An Arduino-based smart system for eye protection, distance monitoring, and ambient light adjustment.

# Smart Eye Protection and Alert System 👁️

An Arduino-based smart eye protection system designed to promote healthy screen-viewing habits by monitoring the user's distance from the screen, ambient lighting conditions, and presence.

## 📌 Project Overview

Prolonged screen usage and improper viewing distance can cause eye strain and discomfort. The Smart Eye Protection and Alert System uses multiple sensors with an Arduino Uno to monitor the user's interaction with a screen.

The system provides alerts when:

- The user is too close to the screen.
- The surrounding light is not suitable.
- The screen brightness needs adjustment.
- The user has left the screen.
- The user has been using the screen continuously for a long period.

## ✨ Features

- 📏 Monitors the user's distance from the screen using an ultrasonic sensor.
- 🚶 Detects user movement using a PIR sensor.
- 💡 Monitors lighting conditions using LDR sensors.
- 🔔 Provides warning alerts using a buzzer.
- 📺 Displays system status on an I2C LCD.
- ⏱️ Tracks continuous screen usage time.
- 💤 Provides a long-duration usage reminder.
- ⚡ Automatic monitoring with minimal user interaction.

## 🛠️ Components Used

| Component | Quantity |
|-----------|----------|
| Arduino Uno | 1 |
| PIR Sensor | 1 |
| Ultrasonic Sensor | 1 |
| LDR Sensor | 2 |
| 10kΩ Resistor | 2 |
| I2C LCD Display | 1 |
| Buzzer | 1 |
| Jumper Wires | As required |
| Breadboard | 1 |

## 🔌 Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| PIR Sensor | D8 |
| Ultrasonic Trigger | D9 |
| Ultrasonic Echo | D10 |
| Buzzer | D11 |
| LDR 1 | A0 |
| LDR 2 | A1 |
| I2C LCD | SDA / SCL |

## ⚙️ Working Principle

The system uses several sensors to continuously monitor the user's screen-viewing environment.

### 1. User Detection

The PIR sensor detects movement and helps identify when the user starts interacting with the screen.

### 2. Distance Monitoring

The ultrasonic sensor measures the distance between the user and the screen.

If the distance becomes less than the predefined safe distance, the system generates a warning.

### 3. Light Monitoring

Two LDR sensors are used to monitor the lighting conditions.

The readings are compared to determine whether the lighting conditions are appropriate.

### 4. Alert System

When an unsafe condition is detected, the buzzer provides an alert and the LCD displays the corresponding message.

Example messages include:

- `System Ready`
- `Too Close`
- `Adjust Light`
- `Brightness Low`
- `Brightness High`
- `All Good`

### 5. Usage Timer

The system keeps track of continuous screen usage and can provide a reminder after prolonged usage.

## 🧠 System Logic

```text
             ┌─────────────────┐
             │   Arduino Uno    │
             └────────┬────────┘
                      │
       ┌──────────────┼──────────────┐
       │              │              │
       ▼              ▼              ▼
   PIR Sensor   Ultrasonic       LDR Sensors
       │           Sensor             │
       │              │              │
       └──────────────┼──────────────┘
                      │
                      ▼
              ┌───────────────┐
              │ Decision Logic│
              └───────┬───────┘
                      │
             ┌────────┴────────┐
             ▼                 ▼
        LCD Display          Buzzer
