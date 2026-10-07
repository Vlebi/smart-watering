#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>


#define SOIL_SENSOR_PIN A0  
#define SOLENOID_PIN 2      


const int DRY_SOIL_VAL = 3200; // just guessing the value
const int WET_SOIL_VAL = 1300; // just guessing the value


typedef struct struct_node_data {
    int node_id;
    float moisture_pct;
} struct_node_data;


typedef struct struct_command {
    char command[10];
} struct_command;

struct_node_data nodeData;
struct_command incomingCommand;


uint8_t masterAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //replace with the actual MAC address of the master device


void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&incomingCommand, incomingData, sizeof(incomingCommand));
    
    if (strcmp(incomingCommand.command, "OPEN") == 0) {
        digitalWrite(SOLENOID_PIN, HIGH);
        Serial.println("Solenoid Valve Opened");
    } else if (strcmp(incomingCommand.command, "CLOSE") == 0) {
        digitalWrite(SOLENOID_PIN, LOW);
        Serial.println("Solenoid Valve Closed");
    }
}


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Telemetry Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
    
    Serial.begin(115200);

   
    pinMode(SOLENOID_PIN, OUTPUT);
    digitalWrite(SOLENOID_PIN, LOW);
    pinMode(SOIL_SENSOR_PIN, INPUT);

  
    WiFi.mode(WIFI_STA);

    
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

    
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, masterAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add Master peer");
        return;
    }

    nodeData.node_id = 1;
}

void loop() {
    
    int rawAnalog = analogRead(SOIL_SENSOR_PIN);

    
    float moisture = map(rawAnalog, DRY_SOIL_VAL, WET_SOIL_VAL, 0, 100);
    moisture = constrain(moisture, 0.0, 100.0);

    nodeData.moisture_pct = moisture;

    Serial.print("Soil Moisture: ");
    Serial.print(nodeData.moisture_pct);
    Serial.println("%");

   
    esp_now_send(masterAddress, (uint8_t *) &nodeData, sizeof(nodeData));

    
    delay(5000);
}