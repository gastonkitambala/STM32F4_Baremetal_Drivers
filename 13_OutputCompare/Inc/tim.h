/*
 * tim.h
 *
 *  Created on: Feb 14, 2025
 *      Author: gaston
 */

#ifndef TIM_H_
#define TIM_H_


#define SR_UIF (1U<<0)

void tim2_1hz_init(void);
void tim2_pa5_output_compare(void);

#endif /* TIM_H_ */
