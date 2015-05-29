/********************************************************************************
** Form generated from reading UI file 'BilateralFilterSet.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILATERALFILTERSET_H
#define UI_BILATERALFILTERSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CBilateralFilterSet
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSlider *horizontalSlider_4;
    QDoubleSpinBox *doubleSpinBox_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *horizontalSlider;
    QDoubleSpinBox *doubleSpinBox;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *CBilateralFilterSet)
    {
        if (CBilateralFilterSet->objectName().isEmpty())
            CBilateralFilterSet->setObjectName(QStringLiteral("CBilateralFilterSet"));
        CBilateralFilterSet->resize(987, 744);
        gridLayout = new QGridLayout(CBilateralFilterSet);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
        label_4 = new QLabel(CBilateralFilterSet);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSlider_4 = new QSlider(CBilateralFilterSet);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_4);

        doubleSpinBox_4 = new QDoubleSpinBox(CBilateralFilterSet);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));

        horizontalLayout_3->addWidget(doubleSpinBox_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(CBilateralFilterSet);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSlider_2 = new QSlider(CBilateralFilterSet);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        doubleSpinBox_2 = new QDoubleSpinBox(CBilateralFilterSet);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        horizontalLayout_2->addWidget(doubleSpinBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CBilateralFilterSet);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSlider = new QSlider(CBilateralFilterSet);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        doubleSpinBox = new QDoubleSpinBox(CBilateralFilterSet);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        horizontalLayout->addWidget(doubleSpinBox);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame = new QFrame(CBilateralFilterSet);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(frame);


        gridLayout->addLayout(verticalLayout_2, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(CBilateralFilterSet);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton = new QPushButton(CBilateralFilterSet);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(CBilateralFilterSet);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);


        retranslateUi(CBilateralFilterSet);

        QMetaObject::connectSlotsByName(CBilateralFilterSet);
    } // setupUi

    void retranslateUi(QWidget *CBilateralFilterSet)
    {
        CBilateralFilterSet->setWindowTitle(QApplication::translate("CBilateralFilterSet", "CBilateralFilterSet", 0));
        label_4->setText(QApplication::translate("CBilateralFilterSet", "TextLabel", 0));
        label_2->setText(QApplication::translate("CBilateralFilterSet", "TextLabel", 0));
        label->setText(QApplication::translate("CBilateralFilterSet", "TextLabel", 0));
        pushButton_3->setText(QApplication::translate("CBilateralFilterSet", "PushButton", 0));
        pushButton->setText(QApplication::translate("CBilateralFilterSet", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("CBilateralFilterSet", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class CBilateralFilterSet: public Ui_CBilateralFilterSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILATERALFILTERSET_H
