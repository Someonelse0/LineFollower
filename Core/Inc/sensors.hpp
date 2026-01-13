#pragma once
#include "stm32f4xx_hal.h"
#include "gpio.h"

namespace kc {

/**
 * @brief QTR reflectance sensor array driver.
 */
class Sensors {
public:
    static constexpr uint8_t  COUNT       = 8;    /**< Number of sensors */
    static constexpr uint16_t QTR_TIMEOUT = 1000; /**< Discharge timeout */
    static constexpr uint16_t THRESHOLD   = 400;  /**< Detection threshold */

    /**
     * @brief Create sensors object.
     */
    Sensors(GPIO_TypeDef* ports[COUNT], uint16_t pins[COUNT]);

    /**
     * @brief Initialize sensor GPIOs.
     */
    void init();

    /**
     * @brief Read sensor states.
     *
     * @param out Array of size COUNT (0/1 values).
     */
    void read(uint8_t out[COUNT]);

private:
    GPIO_TypeDef* m_ports[COUNT];
    uint16_t      m_pins[COUNT];
    uint8_t       m_values[COUNT];

    void gpio_to_input(GPIO_TypeDef* port, uint16_t pin);
    void gpio_to_output(GPIO_TypeDef* port, uint16_t pin);
    void readRaw(uint16_t raw[COUNT]);
};

} // namespace kc
