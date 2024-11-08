# Function to read sensor data (simulated here as an input; in practice, it would come from hardware)
def read_sensors():
    # This should return an 8-element list of 1s and 0s from the sensors.
    # Replace with actual sensor reading logic.
    # Example: return [0, 0, 1, 1, 1, 0, 0, 0] where the line is near the center.
    return [0, 0, 1, 1, 1, 0, 0, 0]

# Movement functions (simulated; replace with motor control code)
def move_forward():
    print("Moving forward")

def turn_left():
    print("Turning left")

def turn_right():
    print("Turning right")

def stop_or_search():
    print("Stopping or searching for line")

# Main function to interpret sensor data and control movement
def control_robot():
    # Read sensor data
    sensors = read_sensors()
    
    # Convert sensor list to a binary pattern (e.g., [0, 0, 1, 1, 1, 0, 0, 0] -> 0b00011100)
    binary_pattern = int("".join(map(str, sensors)), 2)
    
    # Control logic based on binary patterns
    if binary_pattern == 0b00011000:       # Line is centered
        move_forward()
    elif binary_pattern in (0b11100000, 0b11000000, 0b10000000):  # Line is far left
        turn_right()
    elif binary_pattern in (0b00000011, 0b00000111, 0b00000001):  # Line is far right
        turn_left()
    elif binary_pattern == 0b00000000:     # No line detected
        stop_or_search()
    else:
        # Adjust slightly based on the line’s slight offset from center
        if binary_pattern in (0b00010000, 0b00110000):  # Slightly right of center
            turn_left()
        elif binary_pattern in (0b00001000, 0b00001100):  # Slightly left of center
            turn_right()
        else:
            # For any other cases, continue forward with minor adjustments as needed
            move_forward()

# Test loop to simulate continuous robot operation
while True:
    control_robot()
    # Add delay if needed, e.g., time.sleep(0.1)
