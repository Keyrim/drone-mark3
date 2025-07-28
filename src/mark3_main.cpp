/**
 * @file mark3_main.cpp
 * @author Théo MAGNE
 * @date 2025-06-26
 * @see mark3_main.hpp
 */

#include "bsp.h"

#include "logger.hpp"
#include "mark3_main.hpp"

static mark3::Logger logger("MAIN");

void mark3_main(void)
{
    // Initialize
    bsp_init();

    // Start things
    logger.i("Starting Mark3 main...\n");

    // Log some debug information
    logger.d("Debugging information: %s\n", "This is a debug message");

    // Log some error information
    logger.e("Error occurred: %s\n", "This is an error message");

    // Log some warning
    logger.w("Warning: %s\n", "This is a warning message");

    // Main loop
    for (;;)
    {
        // Do stuff
        logger.i("Main loop iteration...\n");
        bsp_delay_ms(1000);
    }
}
