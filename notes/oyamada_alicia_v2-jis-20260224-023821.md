# Oyamada Alicia V2 JIS対応キーマップ作成

## Summary

US配列40%キーボード(Oyamada Alicia V2、46キー)をJIS認識Windowsで使用するためのVialファームウェアキーマップを設計・実装した。`keymap_japanese.h` のJIS専用キーコードとカスタムキーコードを組み合わせてUS配列記号キーのJIS変換を解決した。

## Details

### 環境

- キーボード: Oyamada Alicia V2（46キー、US配列物理キー）
- OS: Windows（JIS認識）
- ファームウェア: QMK + Vial
- 対象ファイル:
  - `/tmp/oyamada_alicia_v2/keymaps/vial/keymap.c`
  - `/tmp/oyamada_alicia_v2/keymaps/vial/vial.json`
  - `/tmp/oyamada_alicia_v2/config.h`

### レイヤー構成（最終）

| Layer | 用途 | アクセス方法 |
|-------|------|-------------|
| 0 | 通常入力 | デフォルト |
| 1 | 記号・数字 | `LT(1,SPC)` または `LT(1,DEL)` ホールド |
| 2 | Fキー・矢印・ナビ | `LT(2,SPC)` ホールド |
| 3 | Home/End/PgUp/PgDn・ファームウェア操作 | `LT(3,CAPS)` ホールド または Layer2経由 `MO(3)` |

Layer 4・5（全KC_TRNS）は削除し、`DYNAMIC_KEYMAP_LAYER_COUNT` を6→4に変更。

### カスタムキーコード

JIS認識Windowsではキーコードとシンボルの対応がUS配列と異なるため、以下を実装:

| キーコード | No-Shift | Shift | 変換ロジック |
|-----------|----------|-------|-------------|
| `MY_GRV` | `` ` ``（S(KC_LBRC)） | `~`（S(KC_EQL)） | Layer1左上 |
| `MY_MINS` | `-`（KC_MINS） | `_`（JP_UNDS） | Layer0 |
| `MY_QUOT` | `'`（S(KC_7)） | `"`（S(KC_2)） | Layer0 |
| `MY_SCLN` | `;`（KC_SCLN） | `:`（JP_COLN） | Layer0 |
| `LT(3,KC_CAPS)` tap | `=`（S(KC_MINS)） | `+`（S(KC_SCLN)） | Layer0右上 |

### DRY修正: tap_jis_key ヘルパー関数

```c
static inline void tap_jis_key(uint16_t normal, uint16_t shifted) {
    uint8_t saved = get_mods();
    if (saved & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code16(shifted);
        set_mods(saved);
    } else {
        tap_code16(normal);
    }
}
```

### 修正したバグ

1. **Shiftスタック問題**: `set_mods(MOD_MASK_SHIFT)` が左右両ShiftビットをセットしてShift固着→ `set_mods(saved_mods)` で正確に復元
2. **JP_HAT未定義**: `JP_HAT` → `JP_CIRC` に修正
3. **LT(3,CAPS)タップ出力逆転**: `S(KC_MINS)` と `S(KC_SCLN)` を入れ替え
4. **KC_ZKHK未定義**: keymap_japanese.h の `JP_ZKHK` を使用

### IMEトグルキー

- `KC_GRV` → IME Onのみで Off不可
- Vialマクロ（Alt + `~`）→ JIS認識環境では Alt+VK_KANJI として送信されOSに認識されず
- **解決**: `JP_ZKHK`（半角/全角専用キーコード）を直接割り当て

## Result

- `keymap.c`: 4レイヤー、カスタムキーコード4種、`tap_jis_key`ヘルパー関数
- `vial.json`: customKeycodes 4エントリ、`DYNAMIC_KEYMAP_LAYER_COUNT 4`
- `config.h`: `DYNAMIC_KEYMAP_LAYER_COUNT` 6→4

ビルド成功・動作確認済み（MY_MINS、MY_QUOT、MY_SCLN）

## Next

- Layer 0 右上キー（`LT(3,KC_CAPS)` = `=+`）をBackspace化するか検討中
  - `+` が Layer 1 に存在しないため、変更する場合は Layer 1 への `S(KC_SCLN)` 追加が必要
- `JP_ZKHK` でIME On/Offトグルが正しく動作するか実機確認待ち
- Microsoft IME設定（半角/全角キーの動作が「トグル」か「IME Onのみ」か）の確認
