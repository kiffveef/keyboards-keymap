// Copyright 2023 Daraku-Neko (@Daraku-Neko)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x74, 0x21, 0x95, 0xCB, 0x93, 0x42, 0xCF, 0x36}

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// 8レイヤー
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// ホールド判定を500msに延長 (デフォルト200msだとMod-Tapがタップと誤判定される)
#define TAPPING_TERM 300
// ホールド中に別キーを押した場合もホールド(Ctrl)として解釈する
#define HOLD_ON_OTHER_KEY_PRESS
