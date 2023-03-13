#include "highlightslidingnavigationmenuwidget.h"

HighlightSlidingNavigationMenuWidget::HighlightSlidingNavigationMenuWidget(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);

    QFont font = this->font();
    font.setPixelSize(22);
    font.setBold(true);
    setFont(font);

    setTitle(QStringList() << "Home" << "Blog" << "More About My Portfolio" << "Contact");
}

HighlightSlidingNavigationMenuWidget::~HighlightSlidingNavigationMenuWidget()
{

}

void HighlightSlidingNavigationMenuWidget::setTitle(const QStringList &list)
{
    if(list.isEmpty())
        return;
    titleList = list;
    widthOfEachAreaList.clear();
    auto fontMetics = this->fontMetrics();
    int width{0};
    for(const auto &title : titleList)
    {
        width += (fontMetics.size(Qt::AlignCenter, title).width() + 60);
        widthOfEachAreaList << width;
    }
    updateEachArea();
    update();
}

const QRect &HighlightSlidingNavigationMenuWidget::getSliderRect() const
{
    return sliderRect;
}

void HighlightSlidingNavigationMenuWidget::setSliderRect(const QRect &newSliderRect)
{
    sliderRect = newSliderRect;
}

void HighlightSlidingNavigationMenuWidget::paintEvent(QPaintEvent *event)
{
    const QRect drawRect = event->rect();
    const int drawHeight = drawRect.height();
    QPainter painter(this);

    /* 尽可能消除锯齿边缘 */
    painter.setRenderHint(QPainter::Antialiasing);
    /* 尽可能消除文本锯齿边缘 */
    painter.setRenderHint(QPainter::TextAntialiasing);
    /* 启用线性插值算法以此来平滑图片 */
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.save();
    painter.fillRect(drawRect.adjusted(0, 10, 0, -10), QColor("#e6eae3")); // 灰黄绿
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(QPen(QColor("#d4dcda"),2)); // 薄云鼠
    for(int i = 0; i < widthOfEachAreaList.size();++i)
    {
        painter.drawLine(QPoint(widthOfEachAreaList.at(i), 12), QPoint(widthOfEachAreaList.at(i), drawHeight - 12));
    }
    painter.restore();

    QLinearGradient linearGradient(sliderRect.topLeft(), sliderRect.bottomLeft());
    linearGradient.setColorAt(0.0, QColor("#2ca9e1")); // 天色
    linearGradient.setColorAt(1.0, QColor("#3e62ad")); // 杜若
    painter.save();
    painter.setBrush(linearGradient);
    painter.drawRoundedRect(sliderRect, 6, 6);

    auto font = this->font();
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(QColor("#524748")); // 红消鼠
    for(int i = 0; i < eachAreaList.size();++i)
    {
        painter.drawText(eachAreaList.at(i), Qt::AlignCenter, titleList.at(i));
    }
    painter.restore();


}

QSize HighlightSlidingNavigationMenuWidget::sizeHint() const
{
    auto fontMetics = this->fontMetrics();
    int width{0};
    for(const auto &title : titleList)
    {
        width += (fontMetics.size(Qt::AlignCenter, title).width() + 60);
    }
    return QSize(width, 100);
}

void HighlightSlidingNavigationMenuWidget::resizeEvent(QResizeEvent *event)
{
    updateEachArea();
    QWidget::resizeEvent(event);
}

void HighlightSlidingNavigationMenuWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto nowPos = event->pos();
    int lastIndex = currIndex;
    for(int i = 0; i < widthOfEachAreaList.size(); ++i)
    {
        // 判断鼠标位置
        if(eachAreaList.at(i).contains(nowPos))
        {
            currIndex = i;
            break;
        }
    }
    if(lastIndex != currIndex)
    {
        auto animationSliderRect = new QPropertyAnimation(this, "sliderRect");
        animationSliderRect->setStartValue(sliderRect);
        animationSliderRect->setEndValue(eachAreaList.at(currIndex));
        animationSliderRect->setDuration(200);
        emit currentIndexChange(currIndex);
        // 定时重绘
        connect(animationSliderRect, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
        animationSliderRect->start(QAbstractAnimation::DeleteWhenStopped);
    }
    QWidget::mouseMoveEvent(event);
}

void HighlightSlidingNavigationMenuWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse press"<<endl;
    auto nowPos = event->pos();
    int lastIndex = currIndex;
    for(int i = 0; i < widthOfEachAreaList.size(); ++i)
    {
        // 判断鼠标位置
        if(eachAreaList.at(i).contains(nowPos))
        {
            currIndex = i;
            break;
        }
    }
    qDebug()<<"index"<<currIndex;
    QWidget::mousePressEvent(event);
}

void HighlightSlidingNavigationMenuWidget::updateEachArea()
{
    eachAreaList.clear();
    auto height = this->height();
    for(int i = 0; i <widthOfEachAreaList.size(); ++i)
    {
        QRect rect{i == 0 ? 0 : widthOfEachAreaList.at(i - 1), 0,
                   i == 0 ? widthOfEachAreaList.at(i) : widthOfEachAreaList.at(i) - widthOfEachAreaList.at(i - 1), height
            };
        eachAreaList << rect;
    }
    sliderRect = eachAreaList.first();
    currIndex = 0;
    emit currentIndexChange(currIndex);

}
