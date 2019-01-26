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
  //abcdefg
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
    init();
    if(refreshTime) {
      myTimer.set(refreshTime);
    }      
}

void Max7219::handleTimeout() {
  applyContent();
  myTimer.set(refreshTime);
}

void Max7219::setNumber(int32_t number, uint8_t offset, uint8_t dotPlace) {
    if(offset>digitsInUse)
      return;
    char negative = 0;
    if (number < 0) {
      negative = 1;
      number *= -1;
    }

    uint8_t i = offset;
    dotPlace += offset;
    do {
      uint8_t data = g_num_faces[number % 10];
      if (i == dotPlace) {
        data |= (1<<7);
      }
      content[i++] = data;
      number /= 10;
    } while (number && i<digitsInUse);

    if (negative && i<digitsInUse) {
      content[i++] = MAX7219_CHAR_NEGATIVE;
    }
    do {
      content[i++] = MAX7219_CHAR_BLANK;
    } while (i<digitsInUse);
}

void Max7219::setRawChar(int8_t data, uint8_t offset) {
  content[offset] = data;
}

void Max7219::setString(const char *str, uint8_t startAt) {
  uint8_t i = 0;
  while(((startAt + i) < 8) && i < strlen(str)) {
    content[7-(startAt+i)] = SevenSegmentASCII[str[i]-32];
    i++;
  }
}

void Max7219::spiSendByte(uint8_t databyte) {
    // Copy data into the SPI data register
    SPDR = databyte;
    // Wait until transfer is complete
    while (!(SPSR & (1 << SPIF)));
}

void Max7219::writeData(uint8_t data_register, uint8_t data) {  
  PORTB &= ~(1<<SsPin);
  // Send the register where the data will be stored
  spiSendByte(data_register);
  // Send the data to be stored
  spiSendByte(data);
  PORTB |= (1<<SsPin);
}

void Max7219::clearDisplay() {
  memset(content, MAX7219_CHAR_BLANK, digitsInUse);
}

void Max7219::applyContent() {
    uint8_t i = 0;
    do {
      uint8_t item = content[i];
      if(prevContent[i] != item) {
        writeData(++i, item);
      } else {
        i++;
      }
    } while (i<digitsInUse);
    memcpy(prevContent, content, digitsInUse);
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
  writeData(MAX7219_MODE_INTENSITY, 4);
  writeData(MAX7219_MODE_POWER, ON);
	clearDisplay();
	for(uint8_t i=0; i<digitsInUse; i++) {
	  writeData(i+1, MAX7219_CHAR_BLANK);
	}
}

