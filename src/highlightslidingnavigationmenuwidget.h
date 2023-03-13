#ifndef HIGHLIGHTSLIDINGNAVIGATIONMENUWIDGET_H
#define HIGHLIGHTSLIDINGNAVIGATIONMENUWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QDebug>
class HighlightSlidingNavigationMenuWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect sliderRect READ getSliderRect WRITE setSliderRect  MEMBER sliderRect)
public:
    HighlightSlidingNavigationMenuWidget(QWidget *parent = nullptr);
    ~HighlightSlidingNavigationMenuWidget();

    void setTitle(const QStringList &list);

    const QRect &getSliderRect() const;
    void setSliderRect(const QRect &newSliderRect);

signals:
    void currentIndexChange(int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    void updateEachArea();

    int currIndex{0};
    QRect sliderRect;
    QStringList titleList;
    QList<int> widthOfEachAreaList;
    QList<QRect> eachAreaList;


};

#endif // HIGHLIGHTSLIDINGNAVIGATIONMENUWIDGET_H
