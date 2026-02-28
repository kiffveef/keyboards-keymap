// !!! DO NOT ADD #pragma once !!! //

RGB_MATRIX_EFFECT(RAINDROPS_WARM)
RGB_MATRIX_EFFECT(RAINDROPS_COOL)
RGB_MATRIX_EFFECT(OCEAN_GRADIENT)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// hue範囲指定raindropの共通set_color
static void custom_raindrops_set_color(uint8_t i, effect_params_t* params,
                                uint8_t hue_base, uint8_t hue_range) {
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return;
    hsv_t hsv  = rgb_matrix_config.hsv;
    hsv.h      = hue_base + random8_max(hue_range);
    hsv.s      = random8_min_max(127, 255);
    rgb_t rgb  = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

// hue範囲指定raindropの共通ランナー
static bool custom_raindrops_runner(effect_params_t* params, uint16_t* index,
                             uint8_t hue_base, uint8_t hue_range) {
    if ((params->iter == 0) && (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 10 == 0)) {
        *index = random8_max(RGB_MATRIX_LED_COUNT);
    }
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        for (uint8_t i = led_min; i < led_max; i++) {
            custom_raindrops_set_color(i, params, hue_base, hue_range);
        }
    } else if (led_min <= *index && *index < led_max) {
        custom_raindrops_set_color(*index, params, hue_base, hue_range);
        *index = RGB_MATRIX_LED_COUNT + 1;
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// ピンク〜マゼンタ〜赤 raindrop: hue 224-0, sat 127-255
static bool RAINDROPS_WARM(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;
    return custom_raindrops_runner(params, &index, 224, 32);
}

// 寒色系 raindrop: hue 128-213 (cyan, blue, purple), sat 127-255
static bool RAINDROPS_COOL(effect_params_t* params) {
    static uint16_t index = RGB_MATRIX_LED_COUNT + 1;
    return custom_raindrops_runner(params, &index, 128, 85);
}

// シアン〜ブルーグラデーション + キー押下で波紋エフェクト
extern bool matrix_is_on(uint8_t row, uint8_t col);

#define OCEAN_MAX_RIPPLES 8
#define OCEAN_RIPPLE_BAND 30
#define OCEAN_HUE_BASE    128
#define OCEAN_HUE_RANGE   42
#define OCEAN_SAT         180

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t radius;
    uint8_t strength;
} ocean_ripple_t;

static ocean_ripple_t ocean_ripples[OCEAN_MAX_RIPPLES];
static uint8_t ocean_ripple_idx;
static uint32_t ocean_prev_rows[MATRIX_ROWS];

static bool OCEAN_GRADIENT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (params->init) {
        memset(ocean_ripples, 0, sizeof(ocean_ripples));
        memset(ocean_prev_rows, 0, sizeof(ocean_prev_rows));
        ocean_ripple_idx = 0;
    }
    // フレーム先頭: 波紋更新 + 新規押下検出
    if (params->iter == 0) {
        uint8_t spd   = qadd8(rgb_matrix_config.speed >> 5, 1);
        uint8_t decay = qadd8(rgb_matrix_config.speed >> 6, 1);
        for (uint8_t r = 0; r < OCEAN_MAX_RIPPLES; r++) {
            if (ocean_ripples[r].strength == 0) continue;
            uint16_t new_r = ocean_ripples[r].radius + spd;
            if (new_r > 255) {
                ocean_ripples[r].strength = 0;
                continue;
            }
            ocean_ripples[r].radius = (uint8_t)new_r;
            if (ocean_ripples[r].strength > decay) {
                ocean_ripples[r].strength -= decay;
            } else {
                ocean_ripples[r].strength = 0;
            }
        }
        // 押した瞬間のみ波紋を生成(ホールド中は無視)
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            uint32_t current = 0;
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (matrix_is_on(row, col)) current |= ((uint32_t)1 << col);
            }
            uint32_t newly = current & ~ocean_prev_rows[row];
            ocean_prev_rows[row] = current;
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (!(newly & ((uint32_t)1 << col))) continue;
                uint8_t led = g_led_config.matrix_co[row][col];
                if (led == NO_LED) continue;
                ocean_ripples[ocean_ripple_idx].x = g_led_config.point[led].x;
                ocean_ripples[ocean_ripple_idx].y = g_led_config.point[led].y;
                ocean_ripples[ocean_ripple_idx].radius = 0;
                ocean_ripples[ocean_ripple_idx].strength = 255;
                ocean_ripple_idx = (ocean_ripple_idx + 1) % OCEAN_MAX_RIPPLES;
            }
        }
    }
    // LED描画
    for (uint8_t i = led_min; i < led_max; i++) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue;
        hsv_t hsv;
        hsv.h = OCEAN_HUE_BASE + (uint8_t)((uint16_t)g_led_config.point[i].x * OCEAN_HUE_RANGE / 224);
        hsv.s = OCEAN_SAT;
        hsv.v = rgb_matrix_config.hsv.v;
        // 全波紋からの寄与を合算
        uint8_t ripple_val = 0;
        uint8_t px = g_led_config.point[i].x;
        uint8_t py = g_led_config.point[i].y;
        for (uint8_t r = 0; r < OCEAN_MAX_RIPPLES; r++) {
            if (ocean_ripples[r].strength == 0) continue;
            int16_t dx = (int16_t)px - ocean_ripples[r].x;
            // y方向を2倍スケールして波紋を円形に近づける
            int16_t dy = ((int16_t)py - ocean_ripples[r].y) * 2;
            uint8_t adx = (dx < 0) ? -dx : dx;
            uint8_t ady = (dy < 0) ? -dy : dy;
            // 高速近似距離(オクタゴナル)
            uint8_t dist = (adx > ady) ? adx + (ady >> 1) : ady + (adx >> 1);
            uint8_t rad = ocean_ripples[r].radius;
            uint8_t diff = (dist > rad) ? dist - rad : rad - dist;
            if (diff < OCEAN_RIPPLE_BAND) {
                uint8_t prox = OCEAN_RIPPLE_BAND - diff;
                uint8_t intensity = scale8(
                    prox * (255 / OCEAN_RIPPLE_BAND),
                    ocean_ripples[r].strength
                );
                ripple_val = qadd8(ripple_val, intensity);
            }
        }
        if (ripple_val > 0) {
            hsv.s = scale8(hsv.s, 255 - ripple_val);
        }
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
