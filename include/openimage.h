#ifndef OPENIMAGE_H
#define OPENIMAGE_H

#include <QFileDialog>
#include <QImage>
#include <QList>
#include <QRgb>
#include <QDebug>

/**
 * @brief Класс для открытия изображения и создания массива цветов.
 */
class openimage : public QWidget
{
    Q_OBJECT
public:
    openimage(QWidget *parent = nullptr);
    /**
    * @brief Метод для получения массива уникальных цветов.
    * @return Массив цветов.
    */
    QList<QColor>& getcolorlist();
    ~openimage();

private:
    QImage* m_image = nullptr;
    /**
    * @brief Массив, содержащий уникальные цвета.
    */
    QList<QColor> colorlist;
    /**
    * @brief Метод создания массива уникальных цветов.
    */
    void takeimagecorols();
    /**
    * @brief Метод для добавления в массив уникальных цветов и исключения оттенков.
    * @param color1 Цвет из неотсортированного массива.
    * @param color2 Цвет сортируемого массива.
    * @param tolerance Точность сортировки.
    * @return true - неуникальный цвет, false - уникальный
    */
    bool arecolorssimilar(const QColor &color1, const QColor &color2, qreal tolerance = 0.14);

public slots:
    /**
    * @brief Метод для выбора изображения.
    */
    void initopenimage();

signals:
    /**
    * @brief Сигнал об успшном формировании массива уникальных цветов.
    */
    void colorlistdone();
};

#endif // OPENIMAGE_H
