/*
 * pmw3901.h
 *
 *  Created on: Sep 6, 2024
 *      Author: Admin
 */

#ifndef INC_PMW3901_H_
#define INC_PMW3901_H_

#include <stdint.h>
#include "deck_spi.h"

typedef struct motionBurst_s {
  union {
    uint8_t motion;
    struct {
      uint8_t frameFrom0    : 1;
      uint8_t runMode       : 2;
      uint8_t reserved1     : 1;
      uint8_t rawFrom0      : 1;
      uint8_t reserved2     : 2;
      uint8_t motionOccurred: 1;
    };
  };

  uint8_t observation;
  int16_t deltaX;
  int16_t deltaY;

  uint8_t squal;

  uint8_t rawDataSum;
  uint8_t maxRawData;
  uint8_t minRawData;

  uint16_t shutter;
} __attribute__((packed)) motionBurst_t;

bool pmw3901Init();
void pmw3901ReadMotion(motionBurst_t * motion);


#endif /* INC_PMW3901_H_ */
