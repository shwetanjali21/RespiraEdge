#include <DHT.h>
#include "model_weights.h"

#define DHTPIN 4
#define DHTTYPE DHT22
#define MIC_POT_PIN 36 // VP pin on ESP32
#define RELAY_PIN 25
#define BUZZER_PIN 26
#define LED_PIN 33

DHT dht(DHTPIN, DHTTYPE);

// On-Device Forward Propagation Neural Network Engine
int predict_edge_ai(float raw_inputs[4]) {
  float layer1[16] = {0};
  float layer2[8] = {0};
  float output[3] = {0};

  // Hidden Layer 1 (ReLU)
  for (int j = 0; j < 16; j++) {
    float sum = bias1[j];
    for (int i = 0; i < 4; i++) {
      sum += raw_inputs[i] * W1[i][j];
    }
    layer1[j] = sum > 0 ? sum : 0; // ReLU
  }

  // Hidden Layer 2 (ReLU)
  for (int j = 0; j < 8; j++) {
    float sum = bias2[j];
    for (int i = 0; i < 16; i++) {
      sum += layer1[i] * W2[i][j];
    }
    layer2[j] = sum > 0 ? sum : 0; // ReLU
  }

  // Output Layer
  int max_idx = 0;
  float max_val = -99999.0;
  for (int j = 0; j < 3; j++) {
    float sum = bias3[j];
    for (int i = 0; i < 8; i++) {
      sum += layer2[i] * W3[i][j];
    }
    output[j] = sum;
    if (output[j] > max_val) {
      max_val = output[j];
      max_idx = j;
    }
  }

  return max_idx; // Returns 0: Normal, 1: Wheezing, 2: Apnea
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("==================================================");
  Serial.println(" RespiraEdge: On-Device Edge AI Active");
  Serial.println("==================================================");
}

void loop() {
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();
  int raw_pot = analogRead(MIC_POT_PIN);
  
  // Feature Normalization
  float mic_rms = (float)raw_pot / 4095.0f; // Scaled audio energy
  float mic_zcr = mic_rms * 0.8f;            // Estimated Zero Crossing Rate
  
  if (isnan(humidity) || isnan(temp)) {
    humidity = 50.0;
    temp = 24.0;
  }

  float input_features[4] = {mic_rms, mic_zcr, humidity, temp};

  // Measure Sub-Millisecond Execution Latency
  unsigned long t_start = micros();
  int predicted_class = predict_edge_ai(input_features);
  unsigned long latency_us = micros() - t_start;

  // Local Closed-Loop Autonomous Actuation Logic
  if (predicted_class == 1 || predicted_class == 2 || humidity < 40.0) {
    digitalWrite(RELAY_PIN, HIGH);   // Actuate Humidifier
    digitalWrite(BUZZER_PIN, HIGH);  // Alarm
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }

  // Telemetry Output
  const char* status_str[] = {"NORMAL", "WHEEZING DISTRESS", "APNEA EVENT"};
  Serial.printf("[RespiraEdge] Latency: %lu us (%0.2f ms) | Temp: %.1fC | Hum: %.1f%% | Class: %s\n", 
                latency_us, latency_us / 1000.0f, temp, humidity, status_str[predicted_class]);

  delay(600);
}
