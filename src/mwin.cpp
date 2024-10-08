#include "mwin.h"

mwin::mwin(QWidget *parent)
    : QWidget(parent)
{
    o_image = new openimage(this);
    v_lay = new QVBoxLayout(this);
    h_lay = new QHBoxLayout();
    m_view = new QGraphicsView(this);
    m_scene = new QGraphicsScene(m_view);
    m_view->setScene(m_scene);
    m_scene->setSceneRect(0, 0, 500, 600);

    createButtonBlock();

    v_lay->addWidget(m_view);
    v_lay->addLayout(h_lay);

    setFixedSize(600, 700);

    initconnections();
}

void mwin::createButtonBlock() {
    b_open = new QPushButton(this);
    b_open->setText("Open Image");
    b_open->setFixedSize(130, 40);
    b_back = new QPushButton(this);
    b_back->setText("<");
    b_back->setFixedSize(30, 40);
    b_back->hide();
    b_next = new QPushButton(this);
    b_next->setText(">");
    b_next->setFixedSize(30, 40);
    b_next->hide();
    b_save = new QPushButton(this);
    b_save->setText("Save");
    b_save->setFixedSize(120, 40);
    b_save->hide();

    h_lay->addWidget(b_open, 2);
    h_lay->addWidget(b_back, 1);
    h_lay->addWidget(b_next, 1);
    h_lay->addWidget(b_save, 2);
}

void mwin::initconnections() {
    if (o_image) {
        connect(b_open, &QPushButton::clicked, o_image, &openimage::initopenimage);
        connect(o_image, &openimage::colorlistdone, this, &mwin::firstdraw);
    }
    connect(b_next, &QPushButton::clicked, this, &mwin::onnextclick);
    connect(b_back, &QPushButton::clicked, this, &mwin::onbackclick);
    connect(b_save, &QPushButton::clicked, this, &mwin::onsaveclick);
}

void mwin::updateviewandscene() {
    m_scene->clear();
    m_view->update();
    m_view->viewport()->update();
}

void mwin::drawellips(int& l, int index) {
    updateviewandscene();
    short height = 90;
    short width = 90;
    short x = 25;
    short y = 25;
    short step = 0;
    for (int i = index; i < l; ++i) {
        auto color = o_image->getcolorlist()[i];
        if (color.redF() == 1 && color.greenF() == 1 && color.blueF() == 1) {
            m_scene->addEllipse(x, y, width, height, QPen(Qt::black, 5), Qt::NoBrush);
        }
        m_scene->addEllipse(x, y, width, height, QPen(color), QBrush(color));
        x += 120;
        ++step;
        if (step == 4) {
            y += 120;
            x = 25;
            step = 0;
        }
    }
}

void mwin::firstdraw() {
    updateviewandscene();
    int cl = o_image->getcolorlist().size();
    if (cl > 20) {
        b_next->show();
        f_index = 0;
        lists.clear();
        short t = cl / 20;
        for (int i = 0; i < t + 1; ++i) {
            lists.push_back(20 * i);
        }
        drawellips(cl, lists[f_index]);
    } else {
        if (!b_next->isHidden()) {
            b_next->hide();
        }
        if (!b_back->isHidden()) {
            b_back->hide();
        }
        drawellips(cl);
    }
    b_save->show();
}

void mwin::onnextclick() {
    f_index += 1;
    if (f_index == lists.size() - 1) {
        b_next->hide();
    }
    if (f_index > 0) {
        b_back->show();
    }
    int cl = o_image->getcolorlist().size();
    drawellips(cl, lists[f_index]);
}

void mwin::onbackclick() {
    f_index -= 1;
    if (f_index == 0) {
        b_back->hide();
        b_next->show();
    }
    if (f_index > 0) {
        b_next->show();
    }
    int cl = o_image->getcolorlist().size();
    drawellips(cl, lists[f_index]);
}

void mwin::onsaveclick() {
    int cl = o_image->getcolorlist().size();
    if (!m_scene->items().isEmpty() && cl <= 20) {
        QImage* image = new QImage(500, 600, QImage::Format_ARGB32);
        image->fill(Qt::white);
        QPainter* m_painter = new QPainter(image);
        m_painter->setRenderHint(QPainter::Antialiasing, true);
        m_scene->render(m_painter, QRect(0, 0, 500, 600));
        QString* puth = new QString(QFileDialog::getExistingDirectory(this, "Choose a place to save", ""));
        *puth += "/color_reff.jpg";
        image->save(*puth);
        m_painter->end();
        delete image;
        delete m_painter;
        delete puth;
    } else if (!m_scene->items().isEmpty() && cl > 20) {
        f_index = 0;
        drawellips(cl, lists[f_index]);
        QImage* image = new QImage(500, 600, QImage::Format_ARGB32);
        QPainter* m_painter = new QPainter(image);
        QString* puth = new QString();
        int ll = lists.size();
        for (int i = 0; i < ll; ++i) {
            image->fill(Qt::white);
            m_scene->render(m_painter, QRect(0, 0, 500, 600));
            if (puth->isEmpty()) {
                *puth = QFileDialog::getExistingDirectory(this, "Choose a place to save", "");
                *puth += "/color_reff%1.jpg";
            }
            image->save(puth->arg(i+1));
            if (!b_next->isHidden()) {
                b_next->click();
            }
        }
        m_painter->end();
        delete image;
        delete m_painter;
        delete puth;
    }
}

mwin::~mwin() {
    o_image = nullptr;
    delete o_image;
}
