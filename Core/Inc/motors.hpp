#pragma once
#include "motor.hpp"

namespace kc {

/**
 * @brief Dual motor controller
 */
class Motors {
public:
    /**
     * @brief Create Motors object.
     * @param left  Reference to left motor
     * @param right Reference to right motor
     * @param stbyPort GPIO port for standby pin
     * @param stbyPin  GPIO pin for standby
     */
    Motors(Motor& left, Motor& right, GPIO_TypeDef* stbyPort, uint16_t stbyPin);

    /**
     * @brief Initialize motors and standby pin.
     */
    void init();

    /**
     * @brief Start motors.
     */
    void run();

    /**
     * @brief Disable motros.
     */
    void block();

    /**
     * @brief Set speed for left and right motors.
     * @param speedL Left motor speed (0–100%)
     * @param speedR Right motor speed (0–100%)
     */
    void setSpeed(uint8_t speedL, uint8_t speedR);

    /**
     * @brief Set direction forward.
     */
    void forward();

    /**
     * @brief Set direction backward.
     */
    void backward();

    /**
     * @brief Brake both motors.
     */
    void brake();

private:
    Motor& left;   /**< Left motor reference */
    Motor& right;  /**< Right motor reference */

    GPIO_TypeDef* stbyPort; /**< Standby GPIO port */
    uint16_t stbyPin;       /**< Standby GPIO pin */
};

} // namespace kc
