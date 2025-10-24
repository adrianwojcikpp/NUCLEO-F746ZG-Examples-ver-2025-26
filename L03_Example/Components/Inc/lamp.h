/**
  ******************************************************************************
  * @file    lamp.h
  * @author  AW       Adrian.Wojcik@put.poznan.pl
  * @version 1.0
  * @date    30-Oct-2020
  * @brief   Simple dimmer (incandescent light bulb controller board) driver
  *          library.
  *
  ******************************************************************************
  */
#ifndef INC_LAMP_H_
#define INC_LAMP_H_

/* Config --------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Typedef -------------------------------------------------------------------*/
#define LAMP_TimerType TIM_HandleTypeDef*
#define LAMP_PortType GPIO_TypeDef*
#define LAMP_PinType uint16_t

typedef struct {
  LAMP_TimerType DelayTimer;
  LAMP_TimerType TriacTimer;
  LAMP_PortType SYNC_Port;
  LAMP_PinType SYNC_Pin;
  LAMP_PortType TRIAC_Port;
  LAMP_PinType TRIAC_Pin;
  uint32_t EXTI_IRQn;
  float TriacFiringAngle;
  float TriacFiringAngleMin;
  float TriacFiringAngleMax;
} LAMP_HandleTypeDef; 

/* Define --------------------------------------------------------------------*/
#define LAMP_LINE_FREQ   50ul  // [Hz]
#define LAMP_TRIAC_DELAY 2500  // [ticks]

/* Macro ---------------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Start lamp controller delay timer.
 * @param[in] hlamp : Lamp handler
 * @return None
 */
void LAMP_StartDelayTimer(LAMP_HandleTypeDef* hlamp);

/**
 * @brief Stop lamp controller delay timer.
 * @param[in] hlamp : Lamp handler
 * @return None
 */
void LAMP_StopDelayTimer(LAMP_HandleTypeDef* hlamp);

/**
 * @brief TRIAC firing procedure: sets TRIAC output on high and start short period (<100us) timer.
 * @param[in] hlamp : Lamp handler
 * @return None
 */
void LAMP_StartTriacFiring(LAMP_HandleTypeDef* hlamp);

/**
 * @brief TRIAC firing procedure: sets TRIAC output on low and stop short period (<100us) timer.
 * @param[in] hlamp : Lamp handler
 * @return None
 */
void LAMP_StopTriacFiring(LAMP_HandleTypeDef* hlamp);

/**
 * @brief Incandescent light bulb brightness control procedure.
 *        Linearization of lamp brightness vs. TRIAC firing angle relationship.
 * @param[out] hlamp      : Lamp handler
 * @param[in]  brightness : Light bulb power expresses in percents <0-100>
 * @return None
 */
void LAMP_SetBrightness(LAMP_HandleTypeDef* hlamp, float brightness);

#endif /* INC_LAMP_H_ */
