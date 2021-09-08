
/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "gpio.h"

#include "WiFi.h"

/* USER CODE BEGIN 0 */
#include <stdarg.h>	// va_list
#include <string.h>
//#include "main_define.h"
#include "LedBlink.h"

//LBP		lbp;

		
void InitBlinkLLED(PLBP pLbp, GPIO_TypeDef* _p_port, uint32_t _gpio_pin)
{
	pLbp->is_inverted_ = 0;

	pLbp->max_period_ = MAX_LED_BLINK_PERIOD;

	pLbp->start_tick_ = 0;

	pLbp->max_blink_count_ = (MAX_LED_BLINK_PERIOD / (DEFAULT_ON_DURATION+DEFAULT_OFF_DURATION));
	pLbp->currnet_blink_count_ = 0;

	pLbp->current_led_onoff_ = 0;

	pLbp->on_duration_ = DEFAULT_ON_DURATION;
	pLbp->off_duration_ = DEFAULT_OFF_DURATION;

	pLbp->onoff_start_tick_ = 0;
	
	pLbp->p_gpio_port = _p_port;
	pLbp->gpio_pin = _gpio_pin;
}

void SetupBlinkLED(PLBP pLbp, uint32_t _is_inverted, uint32_t _max_period, uint32_t _blink_count)
{
	pLbp->start_tick_ = 0;
	pLbp->is_inverted_ = _is_inverted;
	pLbp->max_period_ = _max_period;
	pLbp->max_blink_count_ = _blink_count * 2;

	pLbp->currnet_blink_count_ = 0;
	pLbp->current_led_onoff_ = 0;

	pLbp->on_duration_ = DEFAULT_ON_DURATION;
	pLbp->off_duration_ = DEFAULT_OFF_DURATION;

	pLbp->onoff_start_tick_ = 0;
}

void SetupBlinkLEDDetail(PLBP pLbp, uint32_t _is_inverted, uint32_t _max_period, uint32_t _blink_count, uint32_t _duraion)
{
	pLbp->start_tick_ = 0;
	pLbp->is_inverted_ = _is_inverted;
	pLbp->max_period_ = _max_period;
	pLbp->max_blink_count_ = _blink_count * 2;

	pLbp->currnet_blink_count_ = 0;
	pLbp->current_led_onoff_ = 0;

	pLbp->on_duration_ = _duraion;
	pLbp->off_duration_ = _duraion;

	pLbp->onoff_start_tick_ = 0;
}

void BlinkLED(PLBP pLbp, uint32_t _tick)
{
	if(pLbp->max_period_ <= (_tick - pLbp->start_tick_)) {
		pLbp->start_tick_ = _tick;
		pLbp->onoff_start_tick_ = _tick;
		
		if(0 == pLbp->is_inverted_) {
			pLbp->current_led_onoff_ = 1;
			// LED ON
			HAL_GPIO_WritePin(pLbp->p_gpio_port, pLbp->gpio_pin, GPIO_PIN_SET);
		}
		else {
			pLbp->current_led_onoff_ = 0;
			// LED OFF
			HAL_GPIO_WritePin(pLbp->p_gpio_port, pLbp->gpio_pin, GPIO_PIN_RESET);
		}
		
		pLbp->currnet_blink_count_ = 0;
	}

	if(pLbp->max_blink_count_ <= pLbp->currnet_blink_count_) {
		return;
	}
	
	if (1 == pLbp->current_led_onoff_) {
		if (pLbp->on_duration_ <= (_tick - pLbp->onoff_start_tick_)) {
			pLbp->onoff_start_tick_ = _tick;
			pLbp->current_led_onoff_ = 0;
			// LED OFF;
			HAL_GPIO_WritePin(pLbp->p_gpio_port, pLbp->gpio_pin, GPIO_PIN_RESET);
			if (0 == pLbp->current_led_onoff_)	pLbp->currnet_blink_count_++;
		}
	}
	else {
		if (pLbp->off_duration_ <= (_tick - pLbp->onoff_start_tick_)) {
			pLbp->onoff_start_tick_ = _tick;
			pLbp->current_led_onoff_ = 1;
			// LED OFF;
			HAL_GPIO_WritePin(pLbp->p_gpio_port, pLbp->gpio_pin, GPIO_PIN_SET);
			if (1 == pLbp->current_led_onoff_)	pLbp->currnet_blink_count_++;
		}
	}
}


