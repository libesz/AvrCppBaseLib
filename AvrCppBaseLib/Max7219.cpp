/* MAX7219 Interaction Code
 * ---------------------------
 * For more information see
 * http://www.adnbr.co.uk/articles/max7219-and-7-segment-displays
 *
 * Changed to C++ by Gergo Huszty
 */

// Outputs, pin definitions
#define PIN_SCK                   PORTB5
#define PIN_MOSI                  PORTB3

#define ON                        1
#define OFF                       0

#define MAX7219_MODE_DECODE       0x09
#define MAX7219_MODE_INTENSITY    0x0A
#define MAX7219_MODE_SCAN_LIMIT   0x0B
#define MAX7219_MODE_POWER        0x0C
#define MAX7219_MODE_TEST         0x0F
#define MAX7219_MODE_NOOP         0x00

// I only have 3 digits, no point having the
// rest. You could use more though.
#define MAX7219_DIGIT0            0x01
#define MAX7219_DIGIT1            0x02
#define MAX7219_DIGIT2            0x03

#define MAX7219_CHAR_BLANK        0
#define MAX7219_CHAR_NEGATIVE     0b0000001

#include <avr/io.h>
#include <string.h>
#include "Max7219.h"

const uint8_t g_num_faces[10] = {
  //    abcdefg
  0b1111110,
  0b0110000,
  0b1101101,
  0b1111001,
  0b0110011,
  0b1011011,
  0b1011111,
  0b1110000,
  0b1111111,
  0b1111011
};

Max7219::Max7219(uint8_t newDigitsInUse,
                 uint8_t newSsPin,
                 uint8_t newRefreshTime): SoftTimerHandler(false, false, true),
                                          digitsInUse(newDigitsInUse), SsPin(newSsPin), refreshTime(newRefreshTime),
                                          content(), prevContent() {
    myTimer.set(refreshTime);
    init();
}

void Max7219::handleTimeout() {
  if(memcmp(content, prevContent, 8)) {
    applyContent();
  }    
  myTimer.set(refreshTime);
}

void Max7219::setNumber(int32_t number, uint8_t dotPlace) {
    char negative = 0;
    if (number < 0) {
      negative = 1;
      number *= -1;
    }

    uint8_t i = 0;
    do {
      uint8_t data = g_num_faces[number % 10];
      if (i == dotPlace) {
        data |= (1<<7);
      }
      content[i++] = data;
      number /= 10;
    } while (number);

    if (negative) {
      content[i++] = MAX7219_CHAR_NEGATIVE;
    }
    do {
      content[i++] = MAX7219_CHAR_BLANK;
    } while (i<digitsInUse);
}

void Max7219::spiSendByte(char databyte) {
    // Copy data into the SPI data register
    SPDR = databyte;
    // Wait until transfer is complete
    while (!(SPSR & (1 << SPIF)));
}

void Max7219::writeData(char data_register, char data) {  
  PORTB &= ~(1<<SsPin);
  // Send the register where the data will be stored
  spiSendByte(data_register);
  // Send the data to be stored
  spiSendByte(data);
  PORTB |= (1<<SsPin);
}

void Max7219::clearDisplay() {
	char i = digitsInUse;
	// Loop until 0, but don't run for zero
	do {
		// Set each display in use to blank
		writeData(i, MAX7219_CHAR_BLANK);
	} while (--i);
}

void Max7219::applyContent() {
    uint8_t i = 0;
    do {
      writeData(++i, content[i]);
    } while (i<digitsInUse);
    memcpy(prevContent, content, 8);
}

void Max7219::init() {
	// SCK MOSI CS/LOAD/SS
  DDRB |= (1 << PIN_SCK) | (1 << PIN_MOSI) | (1 << SsPin);

  // SPI Enable, Master mode
  SPCR |= (1 << SPE) | (1 << MSTR)| (1<<SPR1);

  // Decode mode to "No Decode"
  writeData(MAX7219_MODE_DECODE, 0x00);
  // Scan limit runs from 0.
  writeData(MAX7219_MODE_SCAN_LIMIT, digitsInUse - 1);
  writeData(MAX7219_MODE_INTENSITY, 8);
  writeData(MAX7219_MODE_POWER, ON);
	clearDisplay();
}

