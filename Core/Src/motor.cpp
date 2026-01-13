#include "motor.hpp"

namespace kc {

Motor::Motor(GPIO_TypeDef* d1Port, uint16_t d1Pin, GPIO_TypeDef* d2Port, uint16_t d2Pin, TIM_HandleTypeDef* htim, uint32_t channel)
    : dir1Port(d1Port), dir1Pin(d1Pin), dir2Port(d2Port), dir2Pin(d2Pin), htim(htim), pwmChannel(channel) {}
Motor::Motor()

void Motor::init()
{
    HAL_TIM_PWM_Start(htim, pwmChannel);
    __HAL_TIM_SET_COMPARE(htim, pwmChannel, 0);
}

void Motor::setSpeed(uint8_t speed)
{
    if (speed > 100) speed = 100;
    __HAL_TIM_SET_COMPARE(htim, pwmChannel, speed);
}

void Motor::setDirection(Direction dir)
{
    switch (dir) {
    case Direction::Forward:
        HAL_GPIO_WritePin(dir1Port, dir1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(dir2Port, dir2Pin, GPIO_PIN_RESET);
        break;

    case Direction::Backward:
        HAL_GPIO_WritePin(dir1Port, dir1Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(dir2Port, dir2Pin, GPIO_PIN_SET);
        break;

    case Direction::Brake:
        HAL_GPIO_WritePin(dir1Port, dir1Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(dir2Port, dir2Pin, GPIO_PIN_SET);
        break;
    }
}
} //namespace kc
