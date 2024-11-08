# Sensor readings: 1 if on line, 0 if off line
sensors = [S1, S2, S3, S4, S5, S6, S7, S8]  # binary values from each sensor

# Convert binary array to decimal
binary_pattern = int("".join(map(str, sensors)), 2)

# Control logic based on binary patterns
if binary_pattern == 0b00011000:       # Centered
    move_forward()
elif binary_pattern in (0b11100000, 0b11000000, 0b10000000):  # line is 2 left
    turn_right()
elif binary_pattern in (0b00000011, 0b00000111, 0b00000001): # line is 2 right
    turn_left()
elif binary_pattern == 0b00000000:     # lost line, stop or look for it
    stop_or_search()
else:
    make_minor_adjustments(binary_pattern)  # For patterns close to the center
