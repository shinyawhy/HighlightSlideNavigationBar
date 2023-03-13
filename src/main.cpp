#include "highlightslidingnavigationmenuwidget.h"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget widget;
    QVBoxLayout * vb = new QVBoxLayout(&widget);
    HighlightSlidingNavigationMenuWidget * w = new HighlightSlidingNavigationMenuWidget;
    vb->addWidget(w);
    QStackedLayout * stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(new QLabel("第1页"));
    stackedLayout->addWidget(new QLabel("第2页"));
    stackedLayout->addWidget(new QLabel("第3页"));
    stackedLayout->addWidget(new QLabel("第4页"));
    vb->addLayout(stackedLayout);
    QWidget::connect(w,&HighlightSlidingNavigationMenuWidget::currentIndexChange,[stackedLayout](int currIndex)
    {
        stackedLayout->setCurrentIndex(currIndex);
    });
    widget.show();

    return a.exec();
}
