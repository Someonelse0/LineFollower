#include "motors.hpp"

namespace kc{

Motors::Motors(Motor& l, Motor& r, GPIO_TypeDef* port, uint16_t pin)
	: left(l), right(r), stbyPort(port), stbyPin(pin) {}

void Motors::init()
{
    left.init();
    right.init();
    block();
    left.setDirection(Motor::Direction::Forward);
    right.setDirection(Motor::Direction::Forward);
    left.setSpeed(0);
    right.setSpeed(0);
}

void Motors::run()
{
    HAL_GPIO_WritePin(stbyPort, stbyPin, GPIO_PIN_SET);
}

void Motors::block()
{
    HAL_GPIO_WritePin(stbyPort, stbyPin, GPIO_PIN_RESET);
}

void Motors::forward()
{
    left.setDirection(Motor::Direction::Forward);
    right.setDirection(Motor::Direction::Forward);
}

void Motors::backward()
{
    left.setDirection(Motor::Direction::Backward);
    right.setDirection(Motor::Direction::Backward);
}

void Motors::brake()
{
    left.setDirection(Motor::Direction::Brake);
    right.setDirection(Motor::Direction::Brake);
}

void Motors::setSpeed(uint8_t speedL,uint8_t speedR)
{
	left.setSpeed(speedL);
	right.setSpeed(speedR);
}
} //namespace kc
