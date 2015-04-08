#pragma once

/*
 * This contains everything needed to initialize the program before the program loop
 * It also contains all cleanup needed to be done when exiting
 */

#include "dots.h"

void initialize(progVars* pv);
void cleanup();
