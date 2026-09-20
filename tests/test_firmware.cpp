#include "firmwareimage.h"
#include <QCoreApplication>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <cstdio>

static int failures = 0;

static void check(bool cond, const QString &what)
{
    printf("%s  %s\n", cond ? "[PASS]" : "[FAIL]", what.toLocal8Bit().constData());
    if (!cond)
        failures++;
}

/* 构造一条带正确校验和的 HEX 记录 */
static QString hexRecord(unsigned addr, unsigned type, const QByteArray &data)
{
    unsigned sum = (unsigned)data.size() + ((addr >> 8) & 0xFF) + (addr & 0xFF) + type;
    for (int i = 0; i < data.size(); ++i)
        sum += (unsigned char)data[i];
    const unsigned char cs = (unsigned char)((~sum + 1) & 0xFF);

    QString s = QString(":%1%2%3")
                    .arg((unsigned)data.size(), 2, 16, QChar('0'))
                    .arg(addr, 4, 16, QChar('0'))
                    .arg(type, 2, 16, QChar('0'));
    for (int i = 0; i < data.size(); ++i)
        s += QString("%1").arg((unsigned char)data[i], 2, 16, QChar('0'));
    s += QString("%1").arg((unsigned)cs, 2, 16, QChar('0'));
    return s.toUpper();
}

static bool writeFile(const QString &path, const QByteArray &data)
{
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly))
        return false;
    return f.write(data) == data.size();
}

static QByteArray readFile(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return QByteArray();
    return f.readAll();
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    const QString dir = QDir::tempPath() + "/ch417_fwtest";
    QDir().mkpath(dir);

    /* ---------- 用例 1：带空洞的 HEX ---------- */
    {
        QByteArray a(16, '\x00');
        for (int i = 0; i < 16; ++i) a[i] = (char)(0x10 + i);
        QByteArray b(4, '\x00');
        for (int i = 0; i < 4; ++i)  b[i] = (char)(0xA0 + i);

        QByteArray upper;
        upper.append((char)0x08);
        upper.append((char)0x00);

        QStringList lines;
        lines << hexRecord(0x0000, 0x04, upper);   /* 扩展线性地址 0x08000000 */
        lines << hexRecord(0x6000, 0x00, a);       /* 0x08006000 */
        lines << hexRecord(0x6020, 0x00, b);       /* 0x08006020，中间 16 字节空洞 */
        lines << QString(":00000001FF");

        const QString path = dir + "/gap.hex";
        writeFile(path, lines.join("\r\n").toLatin1());

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(ok, QString("HEX 解析成功 (%1)").arg(err));
        check(img.fromHex, "识别为 HEX 格式");
        check(img.startAddress == 0x08006000u,
              QString("起始地址 = 0x%1").arg(img.startAddress, 8, 16, QChar('0')));
        check(img.data.size() == 36, QString("镜像大小 = %1 (期望 36)").arg(img.data.size()));
        check((unsigned char)img.data[0] == 0x10, "首字节 = 0x10");
        check((unsigned char)img.data[15] == 0x1F, "第 16 字节 = 0x1F");
        check((unsigned char)img.data[16] == 0xFF, "空洞填充为 0xFF");
        check((unsigned char)img.data[32] == 0xA0, "空洞后首字节 = 0xA0");
    }

    /* ---------- 用例 2：BIN ---------- */
    {
        QByteArray raw(300, '\x00');
        for (int i = 0; i < raw.size(); ++i) raw[i] = (char)i;

        const QString path = dir + "/plain.bin";
        writeFile(path, raw);

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(ok, QString("BIN 解析成功 (%1)").arg(err));
        check(!img.fromHex, "识别为 BIN 格式");
        check(img.startAddress == 0x08006000u, "BIN 使用指定基地址");
        check(img.data.size() == 300, QString("BIN 大小 = %1").arg(img.data.size()));
    }

    /* ---------- 用例 3：HEX 校验和错误必须被拒绝 ---------- */
    {
        QByteArray a(4, '\x11');
        const QString path = dir + "/bad.hex";
        QString text = hexRecord(0x6000, 0x00, a) + "\r\n:00000001FF";

        /* 破坏最后一条数据记录的校验和（保持行结构完整） */
        const int csPos = text.indexOf('\n') - 3;   /* [cs1][cs2][\r][\n] */
        text.replace(csPos, 2, "00");

        writeFile(path, text.toLatin1());

        FirmwareImage img;
        QString err;
        const bool ok = firmware_load(path, 0x08006000u, img, err);
        check(!ok, QString("校验和错误被拒绝 (%1)").arg(err));
    }

    /* ---------- 用例 4：空文件 / 不存在的文件 ---------- */
    {
        FirmwareImage img;
        QString err;
        check(!firmware_load(dir + "/no_such_file.bin", 0, img, err), "不存在的文件被拒绝");
    }

    printf("\n%s\n", failures == 0
                         ? "ALL TESTS PASSED"
                         : QString("%1 TEST(S) FAILED").arg(failures).toLocal8Bit().constData());
    return failures == 0 ? 0 : 1;
}
