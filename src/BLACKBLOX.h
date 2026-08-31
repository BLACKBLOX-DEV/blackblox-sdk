#pragma once

#include "core/BB.h"

#include "platform/arduino/BBProcessorESP32.h"

#include "display/BBMatrixDisplay.h"

#include "graphics/BBGraphics.h"
#include "graphics/fonts/BBFont.h"
#include "graphics/fonts/BBFont5x7.h"
#include "graphics/fonts/BBFont8x16.h"
#include "graphics/BBScroller.h"

#include "drivers/BBLP5569.h"
#include "drivers/BBPCA9633.h"
#include "drivers/BBSSD1333.h" 

#include "modules/BBClimateWSENHIDS.h"

#include "sensors/climate/BBWSENHIDS.h"
#include "sensors/climate/pressure/BBWSENPADS.h"



#include "modules/BBRGBMatrix8x16.h"

// Matrix pride v M02
// #include "matrix/BBRGBMatrix8x16.h"

using blackblox::BB;
using blackblox::BBClass;

using blackblox::BBProcessorESP32;

using blackblox::BBColor;

using blackblox::BBGraphics;
using blackblox::BBScroller;

using blackblox::BBFont;
using blackblox::BBFont5x7;
using blackblox::BBFont8x16;

using blackblox::BBMatrixDisplay;
using blackblox::BBMatrixRotation;
using blackblox::BBRGBMatrix8x16;

using blackblox::BBLP5569;
using blackblox::BBPCA9633;

using blackblox::BBClimateWSENHIDS;
using blackblox::BBClimateData;
using blackblox::BBClimateStatus;

using blackblox::BBWSENHIDS;
using blackblox::BBWSENPADS;
