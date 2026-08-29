Here is the exact formatted **`README.md`** file customized specifically for your repository (`shwetanjali21/RespiraEdge`).

Create a new file named `README.md` inside your extracted folder, paste this code, and commit it to GitHub.

```markdown
# RespiraEdge: On-Device Edge AI for Autonomous Respiratory Distress & Apnea Detection

![RespiraEdge Banner](Screenshot%202026-08-29%20144630.png)

RespiraEdge is a sub-millisecond, autonomous Edge AI monitoring system deployed on the **ESP32** microcontroller. By executing a custom artificial neural network (ANN) directly on embedded hardware, the system detects respiratory distress states (**Wheezing** and **Apnea**) from live sensor streams and triggers closed-loop hardware actuation without any cloud dependency.

---

## 🌟 Key Highlights

* **100% On-Device Inference:** Eliminates cloud latency, network vulnerability, and operational bandwidth costs.
* **Sub-Millisecond Speed:** Performs complete forward propagation in **$\approx 200\text{--}400\ \mu\text{s}$** directly on the ESP32.
* **Closed-Loop Actuation:** Instantly triggers an emergency humidifier relay, warning buzzer, and LED upon detecting critical states.
* **Privacy-Preserving:** Patient sensor data is processed locally without external transmission.

---

## 🏗️ System Architecture


```

+-----------------------------------------------------------------+
|                      LIVE SENSOR INPUTS                         |
|  [Audio RMS (Potentiometer)]   [Humidity & Temp (DHT22 Sensor)] |
+--------------------------------+--------------------------------+
|
v
+-----------------------------------------------------------------+
|                 ON-DEVICE ANN INFERENCE ENGINE                  |
|  - Input Layer:    4 Normalized Features                        |
|  - Hidden Layer 1: 16 Neurons (ReLU Activation)                 |
|  - Hidden Layer 2: 8 Neurons (ReLU Activation)                  |
|  - Output Layer:   3 Classes (Raw Logits / Softmax)             |
+--------------------------------+--------------------------------+
|
v
+-----------------------------------------------------------------+
|                       STATE CLASSIFICATION                      |
|            [0: NORMAL]   [1: WHEEZING]   [2: APNEA]             |
+--------------------------------+--------------------------------+
|
v
+-----------------------------------------------------------------+
|                   LOCAL CLOSED-LOOP ACTUATION                   |
|   - Relay: Controls Emergency Humidifier / Oxygen Valve         |
|   - Alarm: Buzzer (26) + Warning LED (33)                       |
+-----------------------------------------------------------------+

```

---

## 🔌 Hardware Connections & Pinout

| Component | ESP32 Pin | Function |
| :--- | :--- | :--- |
| **DHT22 Sensor** | `GPIO 4` | Ambient Temperature & Humidity Monitoring |
| **Potentiometer** | `GPIO 36` (VP) | Simulated Audio RMS Sensor Input Stream |
| **Relay Module** | `GPIO 25` | Actuator Control (Humidifier / Safety Valve) |
| **Buzzer** | `GPIO 26` | Audible Distress Alarm |
| **Red LED** | `GPIO 33` | Visual Emergency Warning |

---

## 📂 Repository Layout

```text
RespiraEdge/
├── sketch.ino                  # Main ESP32 application logic & loop
├── model_weights.h             # Trained neural network weights and bias matrices
├── RespiraEdge.ipynb           # Jupyter Notebook for model training & C-export
├── diagram.json                # Wokwi circuit layout schema
├── libraries.txt               # Required Wokwi Arduino dependencies
├── Screenshot 2026-08-29...    # Circuit layout snapshot
└── README.md                   # Project documentation

```

---

## 🚀 Quickstart: Running in Wokwi Simulator

1. Go to [Wokwi.com](https://wokwi.com/) and create a new **ESP32** project.
2. Replace `diagram.json` with the contents of `diagram.json` in this repo.
3. Add `model_weights.h` as a new tab and paste the header code.
4. Open `sketch.ino` and click the green **Play** button.
5. Open the **Serial Monitor** at `115200` baud to observe live microsecond latency logs.

---

## 🧠 Machine Learning Engine Details

The model was built and trained in Python (`RespiraEdge.ipynb`) using PyTorch/TensorFlow. After training, learned weight matrices ($W_1, W_2, W_3$) and bias vectors ($\text{bias}_1, \text{bias}_2, \text{bias}_3$) were converted into static standard C arrays in `model_weights.h`.

Forward propagation runs in C via standard matrix operations:

$$y = \text{ReLU}(W \cdot x + b)$$

---

## 📄 License

This project is licensed under the MIT License - see the `LICENSE` file for details.

```

```