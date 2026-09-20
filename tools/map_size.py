"""Parse a GNU ld map file and report which library / object contributes how much.

Usage: python tools/map_size.py <path-to-size.map> [topN]

ld 的内存映射有两种行式：
  1) 单行：  .text    0x140001000  0x490 D:/.../crt2.o
  2) 双行：  .text$_ZN...
                      0x14029b400   0x40 D:/.../libQt6Gui.a(qrc_qpdf.cpp.obj)
两种都要识别，否则会漏掉绝大部分内容。
"""
import re
import sys
from collections import defaultdict

# 单行形式：段名 地址 大小 文件
ONE_LINE = re.compile(
    r"^\s+(?P<sec>\.\S+)\s+0x[0-9a-fA-F]+\s+0x(?P<size>[0-9a-fA-F]+)\s+(?P<file>\S.*?)\s*$"
)
# 只有段名的一行
SEC_ONLY = re.compile(r"^\s+(?P<sec>\.\S+)\s*$")
# 数据行：地址 大小 文件
DATA_LINE = re.compile(
    r"^\s+0x[0-9a-fA-F]+\s+0x(?P<size>[0-9a-fA-F]+)\s+(?P<file>\S.*?)\s*$"
)
ARCHIVE = re.compile(r"^(.*?)\((.*)\)$")


def unit_label(path: str) -> str:
    path = path.strip()
    m = ARCHIVE.match(path)
    if m:
        lib, obj = m.group(1), m.group(2)
        return lib.replace("\\", "/").rsplit("/", 1)[-1] + "  [" + obj + "]"
    return path.replace("\\", "/").rsplit("/", 1)[-1]


def main() -> int:
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    top_n = int(sys.argv[2]) if len(sys.argv) > 2 else 25

    sizes = defaultdict(int)
    libs = defaultdict(int)
    sec_totals = defaultdict(int)
    total = 0

    # 只统计 "Linker script and memory map" 之后的正文
    started = False
    pending = None

    with open(sys.argv[1], "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            if not started:
                if "Linker script and memory map" in line:
                    started = True
                continue

            m1 = ONE_LINE.match(line)
            if m1:
                size = int(m1.group("size"), 16)
                total += size
                sec_totals[m1.group("sec").split("$")[0]] += size
                label = unit_label(m1.group("file"))
                sizes[label] += size
                libs[label.split("  [")[0]] += size
                pending = None
                continue

            m2 = SEC_ONLY.match(line)
            if m2:
                pending = m2.group("sec")
                continue

            m3 = DATA_LINE.match(line)
            if m3 and pending:
                size = int(m3.group("size"), 16)
                total += size
                sec_totals[pending.split("$")[0]] += size
                label = unit_label(m3.group("file"))
                sizes[label] += size
                libs[label.split("  [")[0]] += size
                pending = None
                continue

    def human(n: int) -> str:
        return f"{n / 1048576.0:7.2f} MB"

    print(f"=== 按段统计（合计 {human(total)}） ===")
    for name, size in sorted(sec_totals.items(), key=lambda kv: -kv[1])[:8]:
        print(f"{human(size)}  {size * 100.0 / total:5.1f}%  {name}")

    print()
    print(f"=== 按库聚合（Top {top_n}） ===")
    for name, size in sorted(libs.items(), key=lambda kv: -kv[1])[:top_n]:
        print(f"{human(size)}  {size * 100.0 / total:5.1f}%  {name}")

    print()
    print(f"=== 最大的单个目标文件（Top {top_n}） ===")
    for name, size in sorted(sizes.items(), key=lambda kv: -kv[1])[:top_n]:
        print(f"{human(size)}  {size * 100.0 / total:5.1f}%  {name}")

    return 0


if __name__ == "__main__":
    sys.exit(main())
