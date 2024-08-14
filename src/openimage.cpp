#include <openimage.h>

openimage::openimage(QWidget *parent) {

}

void openimage::initopenimage() {
    QString i_url = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*jpg *png *jpeg)");
    if (i_url.isEmpty()) {
        return;
    }
    m_image = new QImage(i_url);
    if (!m_image) {
        return;
    }
    takeimagecorols();
}

bool openimage::arecolorssimilar(const QColor &color1, const QColor &color2, qreal tolerance) {
    qreal r1, g1, b1;
    qreal r2, g2, b2;
    color1.getRgbF(&r1, &g1, &b1);
    color2.getRgbF(&r2, &g2, &b2);

    return (qAbs(r1 - r2) <= tolerance) && (qAbs(g1 - g2) <= tolerance) && (qAbs(g1 - g2) <= tolerance);
}

void openimage::takeimagecorols() {
    colorlist.clear();
    const short* height = new short(m_image->height());
    const short* width = new short(m_image->width());
    for (int y = 0; y < *height; ++y) {
        const QRgb* line = reinterpret_cast<QRgb*>(m_image->scanLine(y));
        for (int x = 0; x < *width; ++x) {
            QRgb pixel = line[x];
            QColor color(pixel);
            colorlist.append(color);
        }
    }

    delete height;
    delete width;

    QList<QColor>* uniccolor = new QList<QColor>;
    for (const QColor &color : qAsConst(colorlist)) {
        bool isUnique = true;
        for (const QColor &uniqueColor : qAsConst(*uniccolor)) {
            if (arecolorssimilar(color, uniqueColor)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniccolor->append(color);
        }
    }

    colorlist.clear();
    colorlist.swap(*uniccolor);
    uniccolor->clear();
    delete uniccolor;

    if (!colorlist.empty()) {
        emit colorlistdone();
    } else {
        return;
    }
}

QList<QColor> &openimage::getcolorlist() {
    return colorlist;
}

openimage::~openimage()
{
    colorlist.clear();
}
