#ifndef MWIN_H
#define MWIN_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLayout>
#include <QPainter>
#include <openimage.h>

/**
 * @brief Класс основного окна программы.
 */
class mwin : public QWidget
{
    Q_OBJECT

public:
    mwin(QWidget *parent = nullptr);
    ~mwin();

private:
    /**
    * @brief Метод для очищения и обновления сцены.
    */
    void updateviewandscene();
    /**
    * @brief Метод для рисования кругов цветных кругов на сцене.
    * @param l_length Размер массива цветовю.
    * @param index Индекс в массиве, с которого производится отрисовка кругов.
    */
    void drawellips(int l_length, int index = 0);
    openimage* o_image = nullptr;
    QHBoxLayout* h_lay = nullptr;
    QVBoxLayout* v_lay = nullptr;
    QGraphicsView* m_view = nullptr;
    QGraphicsScene* m_scene = nullptr;
    QPushButton* b_open = nullptr;
    QPushButton* b_back = nullptr;
    QPushButton* b_next = nullptr;
    QPushButton* b_save = nullptr;
    /**
    * @brief Массив для определения количества кругов на сцене.
    * @note Нужен только в случае, если размер массива цветов больше 20.
    */
    QList<int> lists;
    /**
    * @brief Индекс для массива lists.
    */
    int f_index = 0;

protected:
    void createButtonBlock();
    void initconnections();

public slots:
    void firstdraw();
    void onbackclick();
    void onnextclick();
    void onsaveclick();
};
#endif // MWIN_H
