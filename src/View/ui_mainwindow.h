/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Adjacency_Matrix;
    QAction *actionSave_Adjacency_Matrix;
    QAction *actionHyper_Cube;
    QAction *actionGrid;
    QAction *actionBinary_Tree;
    QAction *actionLine;
    QAction *actionForces;
    QAction *actionShow_removed_edges;
    QWidget *centralwidget;
    QTableWidget *AdjacencyMatrixTableWidget;
    QPushButton *RemoveVertexButton;
    QPushButton *AddVertexButton;
    QPushButton *ClearTableButton;
    QLabel *label;
    QLabel *label_2;
    QGroupBox *groupBox_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *ShowRemovedEdgesCheckBox;
    QCheckBox *ForcedCheckBox;
    QCheckBox *ColoringAnimationCheckBox;
    QPushButton *SplittedMatrixCopyButton;
    QPushButton *AdjacencyMatrixCopyButton;
    QPushButton *RightButton;
    QPushButton *LeftButton;
    QWidget *widget;
    QGridLayout *alla;
    QMdiArea *mdiArea;
    QPushButton *EnterGraphButton;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QCheckBox *HyperCubeCheckBox;
    QCheckBox *GridCheckBox;
    QCheckBox *LineCheckBox;
    QCheckBox *BinaryTreeCheckBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1059, 791);
        actionLoad_Adjacency_Matrix = new QAction(MainWindow);
        actionLoad_Adjacency_Matrix->setObjectName("actionLoad_Adjacency_Matrix");
        actionSave_Adjacency_Matrix = new QAction(MainWindow);
        actionSave_Adjacency_Matrix->setObjectName("actionSave_Adjacency_Matrix");
        actionHyper_Cube = new QAction(MainWindow);
        actionHyper_Cube->setObjectName("actionHyper_Cube");
        actionHyper_Cube->setCheckable(true);
        actionHyper_Cube->setEnabled(false);
        actionGrid = new QAction(MainWindow);
        actionGrid->setObjectName("actionGrid");
        actionGrid->setCheckable(true);
        actionGrid->setEnabled(false);
        actionBinary_Tree = new QAction(MainWindow);
        actionBinary_Tree->setObjectName("actionBinary_Tree");
        actionBinary_Tree->setCheckable(true);
        actionBinary_Tree->setEnabled(false);
        actionLine = new QAction(MainWindow);
        actionLine->setObjectName("actionLine");
        actionLine->setCheckable(true);
        actionLine->setEnabled(false);
        actionForces = new QAction(MainWindow);
        actionForces->setObjectName("actionForces");
        actionShow_removed_edges = new QAction(MainWindow);
        actionShow_removed_edges->setObjectName("actionShow_removed_edges");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        AdjacencyMatrixTableWidget = new QTableWidget(centralwidget);
        if (AdjacencyMatrixTableWidget->columnCount() < 4)
            AdjacencyMatrixTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        AdjacencyMatrixTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (AdjacencyMatrixTableWidget->rowCount() < 4)
            AdjacencyMatrixTableWidget->setRowCount(4);
        AdjacencyMatrixTableWidget->setObjectName("AdjacencyMatrixTableWidget");
        AdjacencyMatrixTableWidget->setGeometry(QRect(610, 40, 361, 251));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AdjacencyMatrixTableWidget->sizePolicy().hasHeightForWidth());
        AdjacencyMatrixTableWidget->setSizePolicy(sizePolicy);
        AdjacencyMatrixTableWidget->setFocusPolicy(Qt::ClickFocus);
        AdjacencyMatrixTableWidget->setLayoutDirection(Qt::LeftToRight);
        AdjacencyMatrixTableWidget->setAutoFillBackground(true);
        AdjacencyMatrixTableWidget->setStyleSheet(QString::fromUtf8("background: (255, 255, 255)"));
        AdjacencyMatrixTableWidget->setFrameShape(QFrame::StyledPanel);
        AdjacencyMatrixTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        AdjacencyMatrixTableWidget->setCornerButtonEnabled(false);
        AdjacencyMatrixTableWidget->setRowCount(4);
        AdjacencyMatrixTableWidget->setColumnCount(4);
        AdjacencyMatrixTableWidget->horizontalHeader()->setVisible(false);
        AdjacencyMatrixTableWidget->horizontalHeader()->setMinimumSectionSize(10);
        AdjacencyMatrixTableWidget->horizontalHeader()->setDefaultSectionSize(30);
        AdjacencyMatrixTableWidget->horizontalHeader()->setHighlightSections(false);
        AdjacencyMatrixTableWidget->verticalHeader()->setVisible(false);
        AdjacencyMatrixTableWidget->verticalHeader()->setMinimumSectionSize(10);
        AdjacencyMatrixTableWidget->verticalHeader()->setDefaultSectionSize(30);
        AdjacencyMatrixTableWidget->verticalHeader()->setHighlightSections(false);
        RemoveVertexButton = new QPushButton(centralwidget);
        RemoveVertexButton->setObjectName("RemoveVertexButton");
        RemoveVertexButton->setGeometry(QRect(980, 40, 31, 32));
        AddVertexButton = new QPushButton(centralwidget);
        AddVertexButton->setObjectName("AddVertexButton");
        AddVertexButton->setGeometry(QRect(1020, 40, 31, 32));
        ClearTableButton = new QPushButton(centralwidget);
        ClearTableButton->setObjectName("ClearTableButton");
        ClearTableButton->setGeometry(QRect(980, 70, 71, 32));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(607, 10, 451, 31));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(600, 450, 451, 31));
        label_2->setAlignment(Qt::AlignCenter);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(740, 330, 171, 80));
        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 19, 171, 62));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ShowRemovedEdgesCheckBox = new QCheckBox(verticalLayoutWidget);
        ShowRemovedEdgesCheckBox->setObjectName("ShowRemovedEdgesCheckBox");

        verticalLayout_2->addWidget(ShowRemovedEdgesCheckBox);

        ForcedCheckBox = new QCheckBox(verticalLayoutWidget);
        ForcedCheckBox->setObjectName("ForcedCheckBox");
        ForcedCheckBox->setChecked(true);

        verticalLayout_2->addWidget(ForcedCheckBox);

        ColoringAnimationCheckBox = new QCheckBox(verticalLayoutWidget);
        ColoringAnimationCheckBox->setObjectName("ColoringAnimationCheckBox");
        ColoringAnimationCheckBox->setChecked(true);

        verticalLayout_2->addWidget(ColoringAnimationCheckBox);

        SplittedMatrixCopyButton = new QPushButton(centralwidget);
        SplittedMatrixCopyButton->setObjectName("SplittedMatrixCopyButton");
        SplittedMatrixCopyButton->setEnabled(false);
        SplittedMatrixCopyButton->setGeometry(QRect(980, 510, 71, 32));
        AdjacencyMatrixCopyButton = new QPushButton(centralwidget);
        AdjacencyMatrixCopyButton->setObjectName("AdjacencyMatrixCopyButton");
        AdjacencyMatrixCopyButton->setGeometry(QRect(980, 100, 71, 32));
        RightButton = new QPushButton(centralwidget);
        RightButton->setObjectName("RightButton");
        RightButton->setEnabled(false);
        RightButton->setGeometry(QRect(1020, 480, 31, 32));
        LeftButton = new QPushButton(centralwidget);
        LeftButton->setObjectName("LeftButton");
        LeftButton->setEnabled(false);
        LeftButton->setGeometry(QRect(980, 480, 31, 32));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        alla = new QGridLayout(widget);
        alla->setObjectName("alla");
        alla->setSizeConstraint(QLayout::SetDefaultConstraint);
        alla->setHorizontalSpacing(-1);
        alla->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(widget);
        mdiArea->setObjectName("mdiArea");
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mdiArea->sizePolicy().hasHeightForWidth());
        mdiArea->setSizePolicy(sizePolicy1);
        mdiArea->setMaximumSize(QSize(600, 780));
        QBrush brush(QColor(238, 238, 238, 0));
        brush.setStyle(Qt::SolidPattern);
        mdiArea->setBackground(brush);

        alla->addWidget(mdiArea, 0, 0, 1, 1);

        EnterGraphButton = new QPushButton(centralwidget);
        EnterGraphButton->setObjectName("EnterGraphButton");
        EnterGraphButton->setGeometry(QRect(610, 300, 102, 32));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setEnabled(true);
        stackedWidget->setGeometry(QRect(610, 480, 361, 251));
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(false);
        groupBox->setGeometry(QRect(610, 330, 116, 125));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        HyperCubeCheckBox = new QCheckBox(groupBox);
        HyperCubeCheckBox->setObjectName("HyperCubeCheckBox");
        HyperCubeCheckBox->setEnabled(false);
        HyperCubeCheckBox->setChecked(false);
        HyperCubeCheckBox->setAutoRepeat(false);

        gridLayout->addWidget(HyperCubeCheckBox, 0, 0, 1, 1);

        GridCheckBox = new QCheckBox(groupBox);
        GridCheckBox->setObjectName("GridCheckBox");

        gridLayout->addWidget(GridCheckBox, 1, 0, 1, 1);

        LineCheckBox = new QCheckBox(groupBox);
        LineCheckBox->setObjectName("LineCheckBox");

        gridLayout->addWidget(LineCheckBox, 3, 0, 1, 1);

        BinaryTreeCheckBox = new QCheckBox(groupBox);
        BinaryTreeCheckBox->setObjectName("BinaryTreeCheckBox");

        gridLayout->addWidget(BinaryTreeCheckBox, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1059, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionLoad_Adjacency_Matrix);
        menuFile->addAction(actionSave_Adjacency_Matrix);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Split Graph Into Patterns", nullptr));
        actionLoad_Adjacency_Matrix->setText(QCoreApplication::translate("MainWindow", "Open...", nullptr));
#if QT_CONFIG(tooltip)
        actionLoad_Adjacency_Matrix->setToolTip(QCoreApplication::translate("MainWindow", "Open", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionLoad_Adjacency_Matrix->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Adjacency_Matrix->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_Adjacency_Matrix->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionHyper_Cube->setText(QCoreApplication::translate("MainWindow", "Hyper Cube", nullptr));
        actionGrid->setText(QCoreApplication::translate("MainWindow", "Grid", nullptr));
        actionBinary_Tree->setText(QCoreApplication::translate("MainWindow", "Binary Tree", nullptr));
        actionLine->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        actionForces->setText(QCoreApplication::translate("MainWindow", "Forces", nullptr));
#if QT_CONFIG(shortcut)
        actionForces->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actionShow_removed_edges->setText(QCoreApplication::translate("MainWindow", "Show Removed Edges", nullptr));
        QTableWidgetItem *___qtablewidgetitem = AdjacencyMatrixTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        RemoveVertexButton->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        AddVertexButton->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        ClearTableButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input Adjacency Matrix", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Output Adjacency Matrix", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        ShowRemovedEdgesCheckBox->setText(QCoreApplication::translate("MainWindow", "Show removed edges", nullptr));
        ForcedCheckBox->setText(QCoreApplication::translate("MainWindow", "Forces", nullptr));
#if QT_CONFIG(shortcut)
        ForcedCheckBox->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        ColoringAnimationCheckBox->setText(QCoreApplication::translate("MainWindow", "Coloring Animation", nullptr));
        SplittedMatrixCopyButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        AdjacencyMatrixCopyButton->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        RightButton->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        LeftButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        EnterGraphButton->setText(QCoreApplication::translate("MainWindow", "Enter Graph", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Patterns", nullptr));
        HyperCubeCheckBox->setText(QCoreApplication::translate("MainWindow", "Hyper Cube", nullptr));
        GridCheckBox->setText(QCoreApplication::translate("MainWindow", "Grid", nullptr));
        LineCheckBox->setText(QCoreApplication::translate("MainWindow", "Line", nullptr));
        BinaryTreeCheckBox->setText(QCoreApplication::translate("MainWindow", "Binary Tree", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
