#!/bin/bash
# Oyamada Alicia V2 US - Vial firmware build script
#
# gpk_fwmaker API ではビルドの途中にパッチを挟めないため、
# docker exec で手動ビルドを行う。
#
# カスタムRGBエフェクトをVial GUIに表示するために
# vialrgb_effects.inc にマッピングを追記する。
#
# VIALRGB ID (Vial GUI表示名)     → 実際のエフェクト
# ─────────────────────────────────────────────────
# 42: Solid Multisplash            → RAINDROPS_WARM
# 43: Pixel Rain                   → RAINDROPS_COOL
# 44: Pixel Fractal                → OCEAN_GRADIENT

set -euo pipefail

CONTAINER="gpk_fwmaker-gpk_fwmaker-1"
KB="oyamada_alicia_v2_us"
KM="vial"
REPO_DIR="$(cd "$(dirname "$0")/.." && pwd)"
VIAL_QMK="/root/vial-qmk"
PATCH_FILE="${VIAL_QMK}/quantum/vialrgb_effects.inc"

echo "=== 1/5 Docker 起動確認 ==="
if ! docker ps --format '{{.Names}}' | grep -q "$CONTAINER"; then
    echo "ERROR: コンテナ ${CONTAINER} が起動していません"
    echo "  cd ~/workspace/github.com/darakuneko/gpk_fwmaker && docker compose up -d"
    exit 1
fi

echo "=== 2/5 キーボードファイルをコピー ==="
# docker cp はボリューム上の既存ディレクトリを正しく上書きできないため、
# 一旦削除してからコピーする
docker exec "$CONTAINER" rm -rf "/root/keyboards/${KB}"
docker cp "${REPO_DIR}/${KB}" "${CONTAINER}:/root/keyboards/${KB}"

echo "=== 3/5 vial-qmk リポジトリをリセット ==="
docker exec "$CONTAINER" bash -c "
    cd ${VIAL_QMK} && \
    python3 -m pip install --break-system-packages -r requirements.txt > /dev/null 2>&1 && \
    git fetch origin && \
    git reset --hard vial && \
    git checkout vial && \
    make git-submodule
"

echo "=== 4/5 vialrgb_effects.inc にカスタムエフェクトを追記 ==="
docker exec "$CONTAINER" bash -c "
    cd ${VIAL_QMK} && \
    rm -rf keyboards/${KB} && \
    cp -rf /root/keyboards/${KB} keyboards/ && \
    python3 -c \"
import sys
path = '${PATCH_FILE}'
with open(path) as f:
    content = f.read()
patch = '''// Custom RGB effects mapped to unused VIALRGB slots
#ifdef RGB_MATRIX_CUSTOM_USER
    { VIALRGB_EFFECT_SOLID_MULTISPLASH, RGB_MATRIX_CUSTOM_RAINDROPS_WARM },
    { VIALRGB_EFFECT_PIXEL_RAIN, RGB_MATRIX_CUSTOM_RAINDROPS_COOL },
    { VIALRGB_EFFECT_PIXEL_FRACTAL, RGB_MATRIX_CUSTOM_OCEAN_GRADIENT },
#endif
'''
# 既にパッチ済みならスキップ
if 'RGB_MATRIX_CUSTOM_RAINDROPS_WARM' in content:
    print('Already patched, skipping')
    sys.exit(0)
# supported_modes配列の最後の }; の直前に挿入
pos = content.rfind('};')
if pos == -1:
    print('ERROR: }; not found in ' + path, file=sys.stderr)
    sys.exit(1)
content = content[:pos] + patch + content[pos:]
with open(path, 'w') as f:
    f.write(content)
print('Patched ' + path)
\"
"

echo "=== 5/5 ファームウェアビルド ==="
docker exec "$CONTAINER" bash -c "
    cd ${VIAL_QMK} && \
    make ${KB}:${KM}
"

echo ""
echo "=== ビルド完了 ==="

# ファームウェアをコピー
docker exec "$CONTAINER" bash -c "
    cp ${VIAL_QMK}/${KB}_${KM}.uf2 /root/keyboards/ 2>/dev/null; \
    chmod 644 /root/keyboards/${KB}_${KM}.uf2 2>/dev/null
"

echo "ファームウェア: ~/GPKFW/${KB}_${KM}.uf2"
ls -lh ~/GPKFW/${KB}_${KM}.uf2 2>/dev/null || echo "(ファームウェアファイルが見つかりません)"
