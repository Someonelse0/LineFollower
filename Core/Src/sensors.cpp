#include "sensors.hpp"

namespace kc {

Sensors::Sensors(GPIO_TypeDef* ports[COUNT], uint16_t pins[COUNT])
{
    for (uint8_t i = 0; i < COUNT; i++) {
        m_ports[i]  = ports[i];
        m_pins[i]   = pins[i];
        m_values[i] = 0;
    }
}

void Sensors::init()
{
	HAL_GPIO_WritePin(S_ON_GPIO_Port, S_ON_Pin, GPIO_PIN_SET);
}

void Sensors::gpio_to_input(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Sensors::gpio_to_output(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void Sensors::readRaw(uint16_t raw[COUNT])
{
    uint8_t active[COUNT];
    for (uint8_t i = 0; i < COUNT; i++) active[i] = 1;

    /* 1. Charge capacitors */
    for (uint8_t i = 0; i < COUNT; i++) {
        gpio_to_output(m_ports[i], m_pins[i]);
        HAL_GPIO_WritePin(m_ports[i], m_pins[i], GPIO_PIN_SET);
    }

    HAL_Delay(1);

    /* 2. Switch to input (Hi-Z) */
    for (uint8_t i = 0; i < COUNT; i++) {
        gpio_to_input(m_ports[i], m_pins[i]);
        raw[i] = QTR_TIMEOUT;
    }

    /* 3. Measure discharge time */
    for (uint16_t t = 0; t < QTR_TIMEOUT; t++) {
        for (uint8_t i = 0; i < COUNT; i++) {
            if (active[i] &&
                HAL_GPIO_ReadPin(m_ports[i], m_pins[i]) == GPIO_PIN_RESET)
            {
                raw[i] = t;
                active[i] = 0;
            }
        }
    }

    /* 4. Restore output mode */
    for (uint8_t i = 0; i < COUNT; i++) {
        gpio_to_output(m_ports[i], m_pins[i]);
    }
}

void Sensors::read(uint8_t out[COUNT])
{
    uint16_t raw[COUNT];
    readRaw(raw);

    for (uint8_t i = 0; i < COUNT; i++) {
        out[i]      = (raw[i] > THRESHOLD) ? 1 : 0;
        m_values[i] = out[i];
    }
}

} // namespace kc
