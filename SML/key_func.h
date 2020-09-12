
#ifndef KEY_FUNC_H
#define KEY_FUNC_H

#include "multi_menu.h"


void key_menu_up(struct Menu * this);
void key_menu_down(struct Menu * this);
void key_menu_ent(struct Menu * this);
void key_menu_esc(struct Menu * this);
void key_monitor_all(struct Menu * this);
void key_opera_start_ent(struct Menu * this);
void key_opera_stop_ent(struct Menu * this);
void key_opera_regenerate_ent(struct Menu * this);
void key_set_contrast_up(struct Menu * this);
void key_set_contrast_down(struct Menu * this);
void key_set_contrast_ent(struct Menu * this);
void key_set_backlight_up(struct Menu * this);
void key_set_backlight_down(struct Menu * this);
void key_set_backlight_ent(struct Menu * this);


#endif

