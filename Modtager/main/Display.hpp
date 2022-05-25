#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "point.h"
#include "linenoise/linenoise.h"
#include "esp_console.h"

class Display
{
public:
    void init();
    void plot_point(int16_t *new_data);

private:
    point generatePoint(int16_t *new_data);
    void moveCursor(int col, int row);
    void clearDisplay();
};