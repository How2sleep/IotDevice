import serial
import time
import requests

arduino_port = 'COM3'
ser = serial.Serial(arduino_port, 9600, timeout=1)

def send_tuple_to_arduino(data_tuple):
    data_str = f"{data_tuple[0]},{data_tuple[1]}\n"
    ser.write(data_str.encode())
    time.sleep(0.1)  # Add a short delay to allow Arduino to process the data

def get_Data():
    url = 'http://localhost:8080/iot/id' # replace poll id with target
    response = requests.get(url).json()
    tuple = (response[0], response[1])
    return tuple

try:
    while True:
        data_to_send = get_Data()
        send_tuple_to_arduino(data_to_send)
        time.sleep(10) 

except KeyboardInterrupt:
    ser.close()
