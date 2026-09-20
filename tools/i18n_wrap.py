# -*- coding: utf-8 -*-
"""
批量给 C++ 源文件中的用户可见字符串套上 Qt 翻译函数。

仅用于本项目内部的一次性改造，不做通用化。
"""
import re
import sys

def convert_iapworker(text):
    # log("...") -> log(tr("..."))
    text = re.sub(r'log\("((?:[^"\\]|\\.)*)"\)', r'log(tr("\1"))', text)
    # log(QString("...").arg(..)) -> log(tr("...").arg(..))  括号数不变
    text = text.replace('log(QString("', 'log(tr("')
    # updateProgress(N, "...") -> updateProgress(N, tr("..."))
    text = re.sub(r'updateProgress\((\d+), "((?:[^"\\]|\\.)*)"\)',
                  r'updateProgress(\1, tr("\2"))', text)
    # updateProgress(N, QString("...")) -> tr(...)
    text = re.sub(r'updateProgress\((\d+), QString\("', r'updateProgress(\1, tr("', text)
    # Q_EMIT finished(cond, "...")
    text = re.sub(r'Q_EMIT finished\((\w+), "((?:[^"\\]|\\.)*)"\)',
                  r'Q_EMIT finished(\1, tr("\2"))', text)
    # 匿名命名空间内的字符串：改用 QCoreApplication::translate
    text = text.replace('return QString("未知错误");',
                        'return QCoreApplication::translate("IapWorker", "未知错误");')
    text = text.replace('image.fromHex ? "Intel HEX" : "BIN"',
                        'image.fromHex ? tr("Intel HEX") : tr("BIN")')
    return text


def convert_ch375dev(text):
    # errorMessage = "..."（单行赋值）
    text = re.sub(r'errorMessage = "((?:[^"\\]|\\.)*)";',
                  r'errorMessage = QCoreApplication::translate("Ch375Dev", "\1");', text)
    # errorMessage = QString("...").arg(...)
    text = re.sub(r'errorMessage = QString\("((?:[^"\\]|\\.)*)"\)',
                  r'errorMessage = QCoreApplication::translate("Ch375Dev", "\1")', text)
    return text


def add_include(text, header):
    if header in text:
        return text
    # 插到第一个 #include 之前或之后
    m = re.search(r'^#include ".*?"\n', text, re.M)
    if m:
        return text[:m.end()] + '#include %s\n' % header + text[m.end():]
    return text


def main():
    path, mode = sys.argv[1], sys.argv[2]
    with open(path, 'r', encoding='utf-8') as f:
        text = f.read()

    if mode == 'iapworker':
        text = convert_iapworker(text)
        text = add_include(text, '<QCoreApplication>')
    elif mode == 'ch375dev':
        text = convert_ch375dev(text)
        text = add_include(text, '<QCoreApplication>')
    else:
        raise SystemExit('unknown mode')

    with open(path, 'w', encoding='utf-8', newline='\n') as f:
        f.write(text)
    print('converted:', path)


if __name__ == '__main__':
    main()
