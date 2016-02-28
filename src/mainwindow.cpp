#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPdfWriter>
#include <QPainter>
#include <QPagedPaintDevice>

#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(printTableWidgetToPdf()));

    ui->plainTextEdit->clear();


    ///* Put combo boxes in each cell of a QTableWidget
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setRowCount(10);

    QLabel *label;
    QComboBox *comboBox;

    for(int i = 0; i < ui->tableWidget->columnCount(); i++)
    {
        for(int j = 0; j < ui->tableWidget->rowCount(); j++)
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
            ui->tableWidget->setCellWidget(i, j, label);
            //*/
        }
    }
    //*/


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


void MainWindow::printTableWidgetToPdf()
{
    ///* Write QTableWidget in PDF file.
    QPdfWriter test("C:/Users/benja/Desktop/test.pdf");
    test.setPageSize(QPagedPaintDevice::A4);
    const qreal horizontalMarginMM = 10.0;     // 10 mm margin on each side
    const qreal verticalMarginMM = 10.0;
    QPagedPaintDevice::Margins margins;
    margins.left = margins.right = horizontalMarginMM;
    margins.top = margins.bottom = verticalMarginMM;
    test.setMargins(margins);

    //Render the QTableWidget in a QPixmap
    QPixmap tempPixmap(ui->tableWidget->size());
    //QPixmap tempPixmap(QSize(1920,1080));
    ui->tableWidget->render(&tempPixmap);

    //Rotate the QPixmap
    QTransform t;
    QPixmap pixmap(ui->tableWidget->size().transposed());
    pixmap = tempPixmap.transformed(t.rotate(90),Qt::SmoothTransformation);


    //Draw the QPixmap with a QPainter
    QPainter painter;
    painter.begin(&test);
    painter.drawPixmap(QRectF(0, 0, test.width(), test.height()), pixmap, QRectF(0, 0,pixmap.width(), pixmap.height()));
    painter.end();

    ui->plainTextEdit->appendPlainText("PDF creation done.");
    //*/
}
