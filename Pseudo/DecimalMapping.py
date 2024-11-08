# Sensor readings: 1 if on line, 0 if off line
sensors = [S1, S2, S3, S4, S5, S6, S7, S8]

# Sensor weights
weights = [-4, -3, -2, -1, 1, 2, 3, 4]

# Calculate weighted sum
position = sum(sensors[i] * weights[i] for i in range(8))

# Control logic
if position == 0:
    move_forward()       # The robot is centered
elif position < 0:
    turn_right(abs(position))  # Robot veers left, correct by turning right
else:
    turn_left(position)        # Robot veers right, correct by turning left
