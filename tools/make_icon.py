# -*- coding: utf-8 -*-
"""
由原始 logo 生成 Windows 图标与界面用图：

    resources/icons/logo.png       原始 logo（1080x1080 RGBA）
        -> resources/icons/logo.ico      多尺寸图标（Windows 资源，嵌入 exe）
        -> resources/icons/logo_128.png  关于对话框用图

用法（需要 Pillow）：
    python tools/make_icon.py <工程目录>
"""
import os
import sys

from PIL import Image

# Windows 图标常用尺寸（含 256，资源管理器大图标也清晰）
SIZES = [(16, 16), (20, 20), (24, 24), (32, 32), (40, 40),
         (48, 48), (64, 64), (128, 128), (256, 256)]


def main(project_dir):
    icon_dir = os.path.join(project_dir, "resources", "icons")
    src = os.path.join(icon_dir, "logo.png")

    if not os.path.isfile(src):
        print("找不到源图: %s" % src)
        return 1

    img = Image.open(src).convert("RGBA")
    print("源图: %s (%dx%d %s)" % (src, img.width, img.height, img.mode))

    ico = os.path.join(icon_dir, "logo.ico")
    img.save(ico, format="ICO", sizes=SIZES)
    print("生成: %s (%d 字节, %d 个尺寸)" % (ico, os.path.getsize(ico), len(SIZES)))

    preview = os.path.join(icon_dir, "logo_128.png")
    img.resize((128, 128), Image.LANCZOS).save(preview)
    print("生成: %s" % preview)

    return 0


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python tools/make_icon.py <工程目录>")
        sys.exit(1)
    sys.exit(main(sys.argv[1]))
