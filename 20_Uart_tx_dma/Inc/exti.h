/*
 * exti.h
 *
 *  Created on: Feb 26, 2025
 *      Author: gaston
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f4xx.h"

void pc13_exti_init(void);

#define LINE13 		(1<<13)


#endif /* EXTI_H_ */
