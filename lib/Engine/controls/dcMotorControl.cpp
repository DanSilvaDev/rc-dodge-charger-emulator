#include "dcMotorControl.h"
#include "driver/ledc.h"
#include "driver/gpio.h"

dcMotorControl::dcMotorControl(hBridgePins* dcPins)
{
    _pins = dcPins;
    // Not using B pins for now
    int outPutPins = ((1ULL<<dcPins->in1) | (1ULL<<dcPins->in2));
    configOutputPin(outPutPins);
    ledc_timer_config_t timerConfig = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_13_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = dcPins->pwmFrequency,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timerConfig);
    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledcChannel = {
        .gpio_num       = dcPins->enableA,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_0,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ledc_channel_config(&ledcChannel);
    
    setDirection(true);
}

void configOutputPin(int pinNumber)
{
    gpio_config_t ioConf = {
        .pin_bit_mask = (1ULL << pinNumber),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&ioConf);
}

void dcMotorControl::setDirection(bool direction)
{
    gpio_set_level(static_cast<gpio_num_t>(_pins->in1), direction);
    gpio_set_level(static_cast<gpio_num_t>(_pins->in2), !direction);
}

void dcMotorControl::setSpeed(unsigned short speed)
{
    // define pwm
    int duty = 4096 * (speed / 100);
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, LEDC_TIMER_0);
}

void dcMotorControl::stop()
{
    gpio_set_level(static_cast<gpio_num_t>(_pins->enableA), false);
}
