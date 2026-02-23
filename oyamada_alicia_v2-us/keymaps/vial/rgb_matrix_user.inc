// !!! DO NOT ADD #pragma once !!! //

RGB_MATRIX_EFFECT(RAINDROPS_WARM)
RGB_MATRIX_EFFECT(RAINDROPS_COOL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// 暖色系 raindrop: hue 0-60 (red, orange, yellow)
static void raindrops_warm_set_color(uint8_t i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    hsv_t hsv  = rgb_matrix_config.hsv;
    hsv.h      = random8_max(60);
    hsv.s      = 255;
    rgb_t rgb  = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

static bool RAINDROPS_WARM(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0)) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            raindrops_warm_set_color(i, params);
        }
    } else if (led_min <= index && index < led_max) {
        raindrops_warm_set_color(index, params);
        index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// 寒色系 raindrop: hue 128-213 (cyan, blue, purple)
static void raindrops_cool_set_color(uint8_t i, effect_params_t* params) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    hsv_t hsv  = rgb_matrix_config.hsv;
    hsv.h      = 128 + random8_max(85);
    hsv.s      = 255;
    rgb_t rgb  = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

static bool RAINDROPS_COOL(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0)) {
        index = random8_max(RGB_MATRIX_LED_COUNT);
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            raindrops_cool_set_color(i, params);
        }
    } else if (led_min <= index && index < led_max) {
        raindrops_cool_set_color(index, params);
        index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
