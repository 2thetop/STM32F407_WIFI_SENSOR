/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_BLINK_H__
#define __LED_BLINK_H__
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */


/* USER CODE BEGIN Private defines */


#define MAX_LED_BLINK_PERIOD				1000
#define DEFAULT_ON_DURATION					50		//100
#define DEFAULT_OFF_DURATION				50		//100

#define LED_BLINK_PERIODICALLY				0
#define LED_BLINK_ONESHOT					1



typedef struct LED_BLINK_PACK {
	uint32_t is_inverted_;

	uint32_t blink_type_;
	
	uint32_t max_period_;
	uint32_t start_tick_;

	uint32_t max_blink_count_;
	uint32_t currnet_blink_count_;

	uint32_t current_led_onoff_;

	uint32_t on_duration_;
	uint32_t off_duration_;

	uint32_t onoff_start_tick_;

	GPIO_TypeDef*	p_gpio_port;
	uint32_t	gpio_pin;
} LBP, *PLBP;

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

void InitBlinkLLED(PLBP pLbp, GPIO_TypeDef* _p_port, uint32_t _gpio_pin);
void SetupBlinkLEDDetail(PLBP pLbp, uint32_t _blink_type, uint32_t _is_inverted, uint32_t _max_period, uint32_t _blink_count, uint32_t _duraion);
void SetupBlinkLED(PLBP pLbp, uint32_t _is_inverted, uint32_t _max_period, uint32_t _blink_count);
void SetupOneShotBlinkLED(PLBP pLbp, uint32_t _is_inverted, uint32_t _max_period, uint32_t _blink_count, uint32_t _duraion);
void BlinkLED(PLBP pLbp, uint32_t _tick);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /* __LED_BLINK_H__ */

/**
  * @}
  */

/**
  * @}
  */
