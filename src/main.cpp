#include <Arduino.h>
#include <driver/mcpwm.h>
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define PWM_gpio16 16
float Freq_gpio16 = 1000;
float Duty16 = 0;

void pwminit2()
{
    mcpwm_config_t pwm_config2;
    pwm_config2.frequency = Freq_gpio16; // Частота
    pwm_config2.cmpr_a = Duty16;          // Заполнение MCPWM2A
    pwm_config2.cmpr_b = Duty16;     // Заполнение MCPWM2B
    pwm_config2.duty_mode = MCPWM_DUTY_MODE_0;
    pwm_config2.counter_mode = MCPWM_UP_COUNTER;
    mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_2, &pwm_config2); // Настройка MCPWM2
}

void setup()
{
    Serial.begin(115200);

    // mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, PWM_gpio21);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM2A, PWM_gpio16);
    // pwminit1();
    pwminit2();
}

void loop()
{
    while (Freq_gpio16 < 160000) {
    Freq_gpio16 += 80.0f;
    while (Duty16 < 100.0f) {
      Duty16 += 10.0f;
      delay(100);
      pwminit2();
      // Serial.println("F = " + String(Freq_gpio16) + "/t" + "D = " + String(Duty16));
      // delay(100);
    }
    Duty16 = 0.0f;
    delay(100);
  }
  delay(100);
  Freq_gpio16 = 1000.0f;
  Duty16 = 0.0f;
  pwminit2();
}