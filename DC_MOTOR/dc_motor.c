#include <lpc214x.h>  // Include LPC214x header file
#define bit(x) (1 << x)  // Macro to set a bit at position x
#include <stdint.h>  // Include stdint.h for uint32_t type

// Function to create a delay in milliseconds
void delay(unsigned int ms) {
    unsigned int j, k;
    for (j = 0; j < ms; j++) {
        for (k = 0; k < 1000; k++);  // Inner loop to waste CPU cycles for delay
    }
}
// Function to move motor forward
void motor_forward() {
    IO0SET = bit(0);  // Set IN1 high (Motor direction control)
    IO0CLR = bit(1);  // Clear IN2 (Opposite motor direction)
}
// Function to stop the motor
void motor_stop() {
    IO0CLR = bit(0) | bit(1);  // Clear both IN1 and IN2 to stop motor
}
// Function to move motor in reverse
void motor_reverse() {
    IO0SET = bit(1);  // Set IN2 high (Opposite motor direction)
    IO0CLR = bit(0);  // Clear IN1 (Motor direction control)
}
int main() {
    IO0DIR = 0xF;       // Configure P0.0 to P0.3 as outputs (binary 1111)
    IO0PIN = 0;         // Clear all output pins in Port 0

    VPBDIV = 0x01;      // Set Peripheral Clock Divider (PCLK = 60MHz)

    while (1) {
        /* Forward Motion */
        motor_forward();  // Call function to move motor forward
        delay(5000);      // Delay for 5000 milliseconds (5 seconds)

        /* Motor Off */
        motor_stop();     // Call function to stop motor
        delay(5000);      // Delay for 5000 milliseconds (5 seconds)

        /* Reverse Motion */
        motor_reverse();  // Call function to move motor in reverse
        delay(5000);      // Delay for 5000 milliseconds (5 seconds)

        /* Motor Off */
        motor_stop();     // Call function to stop motor
        delay(5000);      // Delay for 5000 milliseconds (5 seconds)
    }

    return 0;
}
