/**
 * @file mark3_main.cpp
 * @author Théo MAGNE
 * @date 2025-06-26
 * @see mark3_main.hpp
 */

#include "bsp.h"

#include "mark3_main.hpp"

void mark3_main(void)
{
    // Initialize
    bsp_init();

    // Start things

    // Main loop
    for (;;)
    {
        // Do stuff
        bsp_puts("Hello, Mark3!\n", 15);
        bsp_delay_ms(1000);
    }
}
