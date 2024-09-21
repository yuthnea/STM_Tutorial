/*
 * system.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Admin
 */

#ifndef INC_SYSTEM_H_
#define INC_SYSTEM_H_

#include <stdbool.h>
#include <stdint.h>

void systemInit(void);
bool systemTest(void);

void systemLaunch(void);


void systemStart();
void systemWaitStart(void);

#endif /* INC_SYSTEM_H_ */
