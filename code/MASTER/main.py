import network
import espnow
import machine
import time


wifi = network.WLAN(network.STA_IF)
wifi.active(True)



print("Master MAC Címe:", wifi.config('mac'))

esp = espnow.ESPNow()
esp.active(True)


MOISTURE_THRESHOLD = 30  # 30% 

print("Master egység aktív, várakozás a Node-ok adataira...")

while True:
    
    host, msg = esp.recv(1000)
    
    if msg:
        try:
            
            data_str = msg.decode('utf-8')
            node_id, moisture_str = data_str.split(':')
            moisture = int(moisture_str)
            
            print(f"Fogadva - Node {node_id} Talajnedvesség: {moisture}%")
            
            
            try:
                esp.add_peer(host)
            except Exception:
                pass 
            
           
            if moisture < MOISTURE_THRESHOLD:
                print(f"Node {node_id} talaja száraz! Szelepnyitási parancs küldése...")
                esp.send(host, "OPEN")
                
        except Exception as e:
            print("Hiba az üzenet feldolgozásakor:", e)
            
    time.sleep(0.1)