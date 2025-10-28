/**
  ******************************************************************************
  * @file		  : led_pwm_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version  : 1.4.0
  * @date     : Oct 30, 2024
  * @brief   	: LED components configuration file
  *
  ******************************************************************************
  */
#ifndef INC_LED_PWM_CONFIG_H_
#define INC_LED_PWM_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "led_pwm.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern LED_PWM_Handle_TypeDef hldr; //!< Red channel of RGB THT LED on breadboard
extern LED_PWM_Handle_TypeDef hldg; //!< Green channel of RGB THT LED on breadboard
extern LED_PWM_Handle_TypeDef hldb; //!< Blue channel of RGB THT LED on breadboard

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_LED_PWM_CONFIG_H_ */
