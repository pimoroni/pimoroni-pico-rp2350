#include "wakeup.h"
#include "hardware/gpio.h"
#include "pico/runtime_init.h"


static MP_DEFINE_CONST_FUN_OBJ_1(Wakeup_get_gpio_state_obj, Wakeup_get_gpio_state);
static MP_DEFINE_CONST_FUN_OBJ_0(Wakeup_reset_gpio_state_obj, Wakeup_reset_gpio_state);

static const mp_map_elem_t wakeup_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_wakeup) },
    { MP_ROM_QSTR(MP_QSTR_get_gpio_state), MP_ROM_PTR(&Wakeup_get_gpio_state_obj) },
    { MP_ROM_QSTR(MP_QSTR_reset_gpio_state), MP_ROM_PTR(&Wakeup_reset_gpio_state_obj) },
};
static MP_DEFINE_CONST_DICT(mp_module_wakeup_globals, wakeup_globals_table);

const mp_obj_module_t wakeup_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_wakeup_globals,
};

MP_REGISTER_MODULE(MP_QSTR_wakeup, wakeup_user_cmodule);
