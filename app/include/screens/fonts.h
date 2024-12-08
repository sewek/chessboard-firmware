#ifndef FONTS_H
#define FONTS_H

#include <lvgl.h>

#define LV_FONT_ROBOTO_26 1
#define LV_FONT_ROBOTO_46 1

#if LV_FONT_ROBOTO_26
extern const lv_font_t lv_font_roboto_26;
#endif

#if LV_FONT_ROBOTO_46
extern const lv_font_t lv_font_roboto_46;
#endif

#endif  // FONTS_H