import requests
from pyfirmata2 import Arduino, util
import time
import pyfirmata2

port = 'COM3'

board = Arduino(port)


time.sleep(2)


# Define button pins
button_pin_1 = 2
button_pin_2 = 3

# Set the mode for the button pins
board.digital[button_pin_1].mode = pyfirmata2.INPUT
board.digital[button_pin_2].mode = pyfirmata2.INPUT

# Function to read button states
def read_buttons():
    state_1 = board.digital[button_pin_1].read()
    state_2 = board.digital[button_pin_2].read()
    return state_1, state_2

# Function to send HTTP request
def send_request(button_number):
    url = 'http://localhost:8080/IoT/poll_id' # replace poll id with target
    if (button_number == 1):
        payload = True
    elif(button_number== 2):   # Customize payload data
        payload = False

    headers = {'Content-Type': 'application/json'}

    response = requests.post(url, data=payload, headers=headers)
    print(f"HTTP Response for Button {button_number}: {response.status_code}")

# Main loop
try:
    while True:
        button_state_1, button_state_2 = read_buttons()
        
        if button_state_1 == 1:  # Assuming the button is active-high
            print("Button 1 pressed! Sending HTTP request...")
            send_request(1)
            time.sleep(1)  # Add a delay to avoid multiple requests in quick succession

        if button_state_2 == 1:
            print("Button 2 pressed! Sending HTTP request...")
            send_request(2)
            time.sleep(1)

except KeyboardInterrupt:
    # Close the connection on program exit
    board.exit()
