#pragma once
#include "stm32f4xx_hal.h"

namespace kc {

/**
 * @brief DC motor control using GPIO and PWM.
 */
class Motor {
public:
    /**
     * @brief Motor direction.
     */
    enum class Direction {
        Forward,   /**< Forward rotation */
        Backward,  /**< Backward rotation */
        Brake      /**< Motor brake */
    };

    /**
     * @brief Create motor object.
     */
    Motor(GPIO_TypeDef* dir1Port, uint16_t dir1Pin, GPIO_TypeDef* dir2Port, uint16_t dir2Pin, TIM_HandleTypeDef* htim, uint32_t pwmChannel);

    /**
     * @brief Initialize motor (start PWM).
     */
    void init();

    /**
     * @brief Set motor speed (0–100%).
     */
    void setSpeed(uint8_t speed);

    /**
     * @brief Set motor direction.
     */
    void setDirection(Direction dir);

private:
    GPIO_TypeDef* dir1Port;
    uint16_t dir1Pin;
    GPIO_TypeDef* dir2Port;
    uint16_t dir2Pin;
    TIM_HandleTypeDef* htim;
    uint32_t pwmChannel;
};

} // namespace kc
