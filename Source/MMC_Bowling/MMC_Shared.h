#pragma once

//Shorthands for printing debug messages to screen
#define printBlurp(a) Autil_debug::PrintBlurp(a)
#define printMessage(a) Autil_debug::PrintMessage(a)
#define printWarning(a) Autil_debug::PrintWarning(a)
#define printFatal(a) Autil_debug::PrintFatal(a)


//this is used by all the gset functions
#define OVERRIDE_TYPE_SET		0
#define OVERRIDE_TYPE_ADD		1
#define OVERRIDE_TYPE_SUBTRACT	2
#define OVERRIDE_TYPE_MULTIPLY	3
#define OVERRIDE_TYPE_NULL		4