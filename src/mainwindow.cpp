#include "mainwindow.h"
#include "ui_mainwindow.h"







MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->plainTextEdit->clear();

    //Set size of table
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(10);

    QLabel *label;
    QComboBox *comboBox;

    QStringList horizontalHeaderLabels;
    for(int i = 1; i <= ui->tableWidget->columnCount(); i++)
    {
        horizontalHeaderLabels.append(QString("DS ") + QString::number(i));
    }
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeaderLabels);

    QStringList verticalHeaderLabels;
    for(int i = 1; i <= ui->tableWidget->rowCount(); i++)
    {
        verticalHeaderLabels.append(QString("Comp ") + QString::number(i));
    }
    ui->tableWidget->setVerticalHeaderLabels(verticalHeaderLabels);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            /* QTableWidget with QComboBox
            comboBox = new QComboBox(ui->tableWidget);
            comboBox->addItem("Black");
            comboBox->addItem("Red");
            comboBox->setItemData( 0, QColor( Qt::black ), Qt::DecorationRole );
            comboBox->setItemData( 1, QColor( Qt::red ), Qt::DecorationRole );
            ui->tableWidget->setCellWidget(i, j, comboBox);
            */

            ///* QTableWidget with QLabel
            label = new QLabel(ui->tableWidget);
            label->setStyleSheet("QLabel { background-color : red; color : blue; }");
            label->setText("Non Acquis");
            ui->tableWidget->setCellWidget(i, j, label);
        }
    }



    /* Write text in PDF file.
    QPdfWriter test("C:/Users/benja/Desktop/test.pdf");
    test.setPageSize(QPagedPaintDevice::A4);
    const qreal horizontalMarginMM = 10.0;     // 10 mm margin on each side
    const qreal verticalMarginMM = 10.0;
    QPagedPaintDevice::Margins margins;
    margins.left = margins.right = horizontalMarginMM;
    margins.top = margins.bottom = verticalMarginMM;
    test.setMargins(margins);

    QPainter painter;
    painter.begin(&test);

    painter.setPen(Qt::red);
    painter.drawText(0,0,"THIS IS MY RED PDF TEXT..");

    painter.setPen(Qt::green);
    painter.drawText(0,500,"THIS IS MY GREEN PDF TEXT..");

    painter.setPen(Qt::blue);
    painter.drawText(0,1000,"THIS IS MY BLUE PDF TEXT..");

    painter.end();

    ui->plainTextEdit->appendPlainText("PDF creation done.");
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}





