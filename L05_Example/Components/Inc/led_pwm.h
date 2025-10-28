/**
  ******************************************************************************
  * @file		  : led.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version  : 1.5.0
  * @date     : Nov 20, 2024
  * @brief   	: LED components driver
  *
  ******************************************************************************
  */
#ifndef INC_LED_PWM_H_
#define INC_LED_PWM_H_

/* Public includes -----------------------------------------------------------*/
#include "pwm.h"

/* Public typedef ------------------------------------------------------------*/
typedef enum { LED_ON_LOW, LED_ON_HIGH } LED_ActiveState_TypeDef;

/**
  * @brief PWM output (0.-100.%) LED handle structure definition
  */
typedef struct {
  PWM_Handle_TypeDef Output;
  LED_ActiveState_TypeDef ActiveState;
} LED_PWM_Handle_TypeDef;

/**
  * @brief PWM output (0.-100.%) LED RGB handle structure definition
  */
typedef struct {
  LED_PWM_Handle_TypeDef *R, *G, *B;
} LED_RGB_PWM_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
/**
  * @brief @brief PWM output (0.-100.%) LED handle structure initialization
  * @param[in] TIMER        : TIM handle
  *       This parameter can be one of the following values:
  *            @arg &htim1  : TIM1 (Advanced control timer, 6 channels)
  *            @arg &htim2  : TIM2 (General purpose timer, 4 channels)
  *            @arg &htim3  : TIM3 (General purpose timer, 4 channels)
  *            @arg &htim4  : TIM4 (General purpose timer, 4 channels)
  *            @arg &htim5  : TIM5 (General purpose timer, 4 channels)
  *            @arg &htim8  : TIM8 (Advanced control timer, 6 channels)
  *            @arg &htim9  : TIM9 (General purpose timer, 2 channels)
  *            @arg &htim10 : TIM10 (General purpose timer, 1 channel)
  *            @arg &htim11 : TIM11 (General purpose timer, 1 channel)
  *            @arg &htim12 : TIM12 (General purpose timer, 2 channels)
  *            @arg &htim13 : TIM13 (General purpose timer, 1 channel)
  *            @arg &htim14 : TIM14 (General purpose timer, 1 channel)
  * @param[in] CHANNEL      : TIM Channel
  *       This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  *            @arg TIM_CHANNEL_5: TIM Channel 5 selected
  *            @arg TIM_CHANNEL_6: TIM Channel 6 selected
  * @param[in] ACTIVE_STATE : Active state (polarity) of LED
  *       This parameter can be one of the following values:
  *            @arg LED_ON_LOW  : LED turns on if output state is 0
  *            @arg LED_ON_HIGH : LED turns on if output state is 1
  */
#define LED_PWM_INIT_HANDLE(TIMER, CHANNEL, ACTIVE_STATE)  \
  {                                                        \
    .Output = PWM_INIT_HANDLE((TIMER), CHANNEL),           \
    .ActiveState = ACTIVE_STATE                            \
  }

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
  * @brief Initialize PWM LED control
  * @param[in/out] hled   : LED PWM handler
  * @retval None
  */
void LED_PWM_Init(LED_PWM_Handle_TypeDef* hled);

/**
  * @brief Write PWM duty cycle
  * @param[in/out] hled   : LED PWM handler
  * @param[in]     duty   : PWM duty cycle in percents (0. - 100.)
  * @retval None
  */
void LED_PWM_WriteDuty(LED_PWM_Handle_TypeDef* hled, float duty);

/**
  * @brief Read PWM duty cycle
  * @param[in] hled   : LED PWM handler
  * @retval PWM duty cycle in percents (0. - 100.)
  */
float LED_PWM_ReadDuty(const LED_PWM_Handle_TypeDef* hled);

/**
  * @brief Initialize PWM LED RGB control
  * @param[in/out] hled   : LED RGB PWM handler
  * @retval None
  */
void LED_RGB_PWM_Init(LED_RGB_PWM_Handle_TypeDef* hled);

/**
  * @brief Write LED color
  * @param[in/out] hled   : LED RGB PWM handler
  * @param[in]     color  : 24 bit RGB color
  * @retval None
  */
void LED_RGB_PWM_WriteColor(LED_RGB_PWM_Handle_TypeDef* hled, unsigned int color);

/**
  * @brief Read LED color
  * @param[in] hled   : LED RGB PWM handler
  * @retval 24 bit RGB color
  */
unsigned int LED_RGB_PWM_ReadColor(const LED_RGB_PWM_Handle_TypeDef* hled);

#endif /* INC_LED_PWM_H_ */
