import network
import espnow
import machine
import time

soil_sensor = machine.ADC(machine.Pin(0))  


solenoid = machine.Pin(2, machine.Pin.OUT)
solenoid.value(0)


esp = espnow.ESPNow()
esp.active(True)

#  Master MAC 
master_mac = b'\xff\xff\xff\xff\xff\xff'

try:
    esp.add_peer(master_mac)
except Exception as e:
    print("Master peer beállításra vár:", e)

def read_moisture():

    raw_val = soil_sensor.read_u16() 
    
    
    percent = int((65535 - raw_val) / 65535 * 100)
    return max(0, min(100, percent))

print("Öntöző Node, mérés indul...")

while True:
    moisture = read_moisture()
    print(f"Jelenlegi talajnedvesség: {moisture}%")
    solenoid.value(0)
    
    try:
        esp.send(master_mac, f"1:{moisture}")
        print("Adat elküldve a Masternek.")
    except Exception as err:
        print("Hiba az adatküldéskor (Master nem elérhető?):", err)

    
    host, msg = esp.recv(1000)
    if msg:
        command = msg.decode('utf-8')
        if command == "OPEN":
            print("Nyitási parancs érkezett! Szelep NYITVA.")
            solenoid.value(1) # Szelep kinyitása
            time.sleep(3)     # 3 másodpercig öntöz
            solenoid.value(0) # Szelep elzárása
            print("Szelep ZÁRVA.")

    
    time.sleep(60)