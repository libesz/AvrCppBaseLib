/* 
* EepromStorage.h
*
* Created: 2019. 01. 13. 17:37:15
* Author: Huszty Gergo
*/


#ifndef __EEPROMSTORAGE_H__
#define __EEPROMSTORAGE_H__

#include <stdint.h>
#include <avr/eeprom.h>
#include <util/crc16.h>

static void* nextEepromAddress = 0;

template<class T> class EepromStorage {
  EepromStorage( const EepromStorage &c );
  EepromStorage& operator=( const EepromStorage &c );
  void* eepromStartAddress;
  uint16_t mySize;
  struct DataWithChecksum {
    T data;
    uint16_t checksum;
  };
  struct DataWithChecksum dataWithChecksum;
public:
  T* data;
  EepromStorage() {
    eepromStartAddress = nextEepromAddress;
    nextEepromAddress = (void *)((int16_t)nextEepromAddress + sizeof(DataWithChecksum));
    data = &dataWithChecksum.data;
    eeprom_read_block(&dataWithChecksum, eepromStartAddress, sizeof(struct DataWithChecksum));
    if(getCrcOfData() != dataWithChecksum.checksum) {
      memset(&dataWithChecksum.data, 0, sizeof(T));
      save();
    }
  }
  uint16_t getCrcOfData() {
    uint8_t i = 0;
    uint16_t lastCrc = 0xffff;
    do {
      uint8_t nextByte = ((uint8_t *)data)[i];
      lastCrc = _crc16_update(lastCrc, nextByte);
    } while(++i < sizeof(*data));
    return lastCrc;
  }
  void save() {
    dataWithChecksum.checksum = getCrcOfData();
    eeprom_write_block(&dataWithChecksum, eepromStartAddress, sizeof(struct DataWithChecksum));
  }
};

#endif //__EEPROMSTORAGE_H__
