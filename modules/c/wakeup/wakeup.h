#include "py/runtime.h"
#include "py/objstr.h"

extern mp_obj_t Wakeup_get_gpio_state(mp_obj_t button_in);
extern mp_obj_t Wakeup_reset_gpio_state();