#pragma once

#include <cellstatus.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/prx.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <math.h>
#include <fastmath.h>
#include <cellstatus.h>
#include <sys/timer.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <spu_printf.h>
#include <ctype.h>
#include <libpsutil.h>
#include <cell\pad.h>
#include <cell\padfilter.h>
#include <cell\pad.h>
#include <cellstatus.h>
#include <sys/integertypes.h>
#include <algorithm>
#include <stack>


using namespace libpsutil::math;
using namespace libpsutil::memory;

#include "timers.h"
#include "cellpad.h"

#include "game_table.h"
#include "game_structures.h"

#include "game_calls.h"
#include "game_component.h"
#include "game_functions.h"

#include "variables.h"

#include "menu_item.h"
#include "menu_tab.h"
#include "menu_base.h"
#include "menu.h"