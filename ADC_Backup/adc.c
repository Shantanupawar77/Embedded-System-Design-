#include <lpc214x.h>

#define bit(x) (1U << (x)) // Ensure the result is an unsigned integer

// Define LCD control pins
#define LCD_RS bit(16)  // Register Select (RS) pin
#define LCD_RW bit(17)  // Read/Write (RW) pin
#define LCD_EN bit(18)  // Enable (EN) pin

// Function prototypes
void lcd_init(void);
void cmd(unsigned char a);
void dat(unsigned char b);
void show(const char *s);
void lcd_delay(void);
unsigned int adc(int no, int ch);

// Global variable to hold ADC value
unsigned int val;

int main() {
    IO1DIR = 0xFFFFFFFF;   // Set all pins of Port 1 as output for LCD
    IO0DIR = 0x00000000;   // Set all pins of Port 0 as input for ADC
    PINSEL0 = 0x0300;      // Select ADC function for pins P0.4 and P0.5
    VPBDIV = 0x02;         // Set the peripheral clock (PCLK) to half of the system clock (30 MHz)
    
    lcd_init();            // Initialize the LCD
    show("ADC Value : ");  // Display initial message on the LCD
    
    while (1) {
        cmd(0x8B);         // Move the cursor to the appropriate position on the LCD
        val = adc(0, 6);   // Read the ADC value from channel 6 of ADC0
        dat((val / 1000) + '0');      // Display the thousands place digit
        dat(((val / 100) % 10) + '0');// Display the hundreds place digit
        dat(((val / 10) % 10) + '0'); // Display the tens place digit
        dat((val % 10) + '0');        // Display the units place digit
    }
}

// Function to read ADC value
unsigned int adc(int no, int ch) {
    unsigned int val = 0; // Initialize val to 0 to avoid potential issues
    switch (no) {
        case 0:
            AD0CR = 0x00200600U | (1U << ch);  // Configure ADC0 and select the channel
            AD0CR |= (1U << 24);               // Start ADC conversion
            while ((AD0GDR & (1U << 31)) == 0);// Wait for conversion to complete
            val = AD0GDR;                      // Read the ADC result
            break;
        case 1:
            AD1CR = 0x00200600U | (1U << ch);  // Configure ADC1 and select the channel
            AD1CR |= (1U << 24);               // Start ADC conversion
            while ((AD1GDR & (1U << 31)) == 0);// Wait for conversion to complete
            val = AD1GDR;                      // Read the ADC result
            break;
        default:
            val = 0;                           // Return 0 if ADC number is invalid
            break;
    }
    val = (val >> 6) & 0x03FFU;                // Extract the 10-bit ADC result
    return val;
}

// Function to initialize the LCD
void lcd_init() {
    cmd(0x38); // 2 lines and 5x7 matrix
    cmd(0x0E); // Display on, cursor blinking
    cmd(0x01); // Clear display screen
    cmd(0x06); // Increment cursor
    cmd(0x0C); // Display on, cursor off
    cmd(0x80); // Set cursor position to 1st line, 1st column
}

// Function to send command to LCD
void cmd(unsigned char a) {
    IO1CLR = 0xFF070000;           // Clear data and control lines
    IO1SET = ((unsigned int)a << 24); // Set data lines
    IO1CLR = LCD_RS;               // RS = 0 for command
    IO1CLR = LCD_RW;               // RW = 0 for write
    IO1SET = LCD_EN;               // Enable the LCD
    lcd_delay();                   // Wait for the command to be processed
    IO1CLR = LCD_EN;               // Disable the LCD
}

// Function to send data to LCD
void dat(unsigned char b) {
    IO1CLR = 0xFF070000;           // Clear data and control lines
    IO1SET = ((unsigned int)b << 24); // Set data lines
    IO1SET = LCD_RS;               // RS = 1 for data
    IO1CLR = LCD_RW;               // RW = 0 for write
    IO1SET = LCD_EN;               // Enable the LCD
    lcd_delay();                   // Wait for the data to be processed
    IO1CLR = LCD_EN;               // Disable the LCD
}

// Function to display a string on the LCD
void show(const char *s) {
    while (*s) {
        dat(*s++); // Send each character of the string to the LCD
    }
}

// Function to create a delay
void lcd_delay() {
    volatile unsigned int i; // Ensure i is not optimized out
    for (i = 0; i <= 3000; i++); // Simple delay loop
}
