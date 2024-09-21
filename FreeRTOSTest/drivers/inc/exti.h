/*
 * exti.h
 *
 *  Created on: Aug 31, 2024
 *      Author: Admin
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include <stdbool.h>

void extiInit();
bool extiTest();

void EXTI0_Callback(void);
void EXTI1_Callback(void);
void EXTI2_Callback(void);
void EXTI3_Callback(void);
void EXTI4_Callback(void);
void EXTI5_Callback(void);
void EXTI6_Callback(void);
void EXTI7_Callback(void);
void EXTI8_Callback(void);
void EXTI9_Callback(void);
void EXTI10_Callback(void);
void EXTI11_Callback(void);
void EXTI12_Callback(void);
void EXTI13_Callback(void);
void EXTI14_Callback(void);
void EXTI15_Callback(void);

#endif /* INC_EXTI_H_ */
