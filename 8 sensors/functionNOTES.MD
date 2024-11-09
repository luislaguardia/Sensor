# Explanation of Functions

1. calculatePosition():
- Reads the active sensor positions and calculates the line position using a weighted sum.
- Each sensor has a weight based on its position; left sensors contribute negative weights, and right sensors positive.
Returns a position value that indicates the direction of the line.

2. Motor Control Functions:

moveForward(): Both motors move forward.
turnLeft(): Left motor slows down, while the right motor moves at full speed.
turnRight(): Right motor slows down, while the left motor moves at full speed.
