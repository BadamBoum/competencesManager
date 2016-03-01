#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPrinter>
#include <QPrintDialog>

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
            label->setText("Test");
            ui->tableWidget->setCellWidget(i, j, label);
            //*/

            //ui->tableWidget->item(i,j)->setText("Test");
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

    print(ui->tableWidget, "test");

    ui->plainTextEdit->appendPlainText("PDF 2 creation done.");
}

void MainWindow::print(QTableWidget *tableau_a_imprimer, QString titre)
{

    QPdfWriter printer("C:/Users/benja/Desktop/test2.pdf");
    printer.setPageSize(QPagedPaintDevice::A4);
    printer.setPageOrientation(QPageLayout::Landscape);
    const qreal horizontalMarginMM = 10.0;     // 10 mm margin on each side
    const qreal verticalMarginMM = 10.0;
    QPagedPaintDevice::Margins margins;
    margins.left = margins.right = horizontalMarginMM;
    margins.top = margins.bottom = verticalMarginMM;
    printer.setMargins(margins);

    //    QPrintDialog printDialog(printer, this);
    //    if ( printDialog.exec() == 1)
    //    {
    QTextBrowser * editor = new QTextBrowser;

    //creation de formats d'écriture
    QTextCharFormat NormalFormat;

    QTextCharFormat ItalicFormat;
    ItalicFormat.setFontItalic(true);

    //On insere la date et l'heure actuelle au début de la premiere page
    QDate date;
    QTime time;
    date = date.currentDate();
    time = time.currentTime();
    QString modif ="\nFait le :\t" + date.toString("dddd dd MMMM yyyy") + " a " + time.toString();

    //changement du format d'ecriture
    editor->setCurrentCharFormat(ItalicFormat);
    editor->setAlignment(Qt::AlignLeft);

    //ajout de notre QString a l'endroit du curseur
    editor->append(modif);

    editor->setCurrentCharFormat(NormalFormat);

    //on insere le titre du tableau
    QTextCharFormat format_gros_titre;
    format_gros_titre.setFontPointSize(20);
    format_gros_titre.setFontWeight(QFont::Bold);
    format_gros_titre.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    format_gros_titre.setUnderlineStyle(QTextCharFormat::SingleUnderline);

    QString title = QString::fromUtf8(titre.toStdString().c_str())+"\n\n";

    editor->setCurrentCharFormat(format_gros_titre);
    editor->setAlignment(Qt::AlignCenter);

    editor->append(title);

    editor->setCurrentCharFormat(NormalFormat);

    //on crée un curseur a l'endroit du curseur actuel
    QTextCursor cursor = editor->textCursor();
    cursor.beginEditBlock();

    //Creation du format du tableau qui sera imprimer
    QTextTableFormat tableFormat;
    tableFormat.setAlignment(Qt::AlignHCenter);
    tableFormat.setAlignment(Qt::AlignLeft);
    tableFormat.setBackground(QColor("#ffffff"));
    tableFormat.setCellPadding(1);
    tableFormat.setCellSpacing(1);

    //Creation du tableau qui sera imprimé avec le nombre de colonne
    //et de ligne que contient le tableau mis en parametre
    QTextTable * tableau = cursor.insertTable((tableau_a_imprimer->rowCount()+1), (tableau_a_imprimer->columnCount()+1), tableFormat);

    QTextFrame *frame = cursor.currentFrame();
    QTextFrameFormat frameFormat = frame->frameFormat();
    frameFormat.setBorder(0);
    frame->setFrameFormat(frameFormat);

    //Format des HEADER du tableau
    QTextCharFormat format_entete_tableau;
    format_entete_tableau.setFontPointSize(15);
    format_entete_tableau.setFontWeight(QFont::Bold);

    //Format du texte des cellules du tableau
    QTextCharFormat format_cellule;
    format_cellule.setFontPointSize(12);

    //on ecrit les HEADERS du tableaux dans le tableau a imprimer
    for ( int i = 0 ; i < tableau_a_imprimer->columnCount() ; i++ )
    {
        //on selectionne la premiere cellule de chaque colonne
        QTextTableCell titre = tableau->cellAt(0,i+1);

        //on place le curseur a cet endroit
        QTextCursor cellCursor = titre.firstCursorPosition();

        //on écrit dans la cellule
        cellCursor.insertText(tableau_a_imprimer->horizontalHeaderItem(i)->text(),format_entete_tableau);
    }
    for ( int i = 0 ; i < tableau_a_imprimer->rowCount() ; i++ )
    {
        //on selectionne la premiere cellule de chaque colonne
        QTextTableCell titre = tableau->cellAt(i+1,0);

        //on place le curseur a cet endroit
        QTextCursor cellCursor = titre.firstCursorPosition();

        //on écrit dans la cellule
        cellCursor.insertText(tableau_a_imprimer->verticalHeaderItem(i)->text(),format_entete_tableau);
    }

    QTextTableCell cell;
    QTextCursor cellCursor;

    for (int row = 1; row < tableau->rows(); row ++)
    {
        for (int col = 1; col < tableau->columns(); col ++)
        {
            cell = tableau->cellAt(row,col);
            cellCursor = cell.firstCursorPosition();

            //cellCursor.insertText(tr("%1").arg(tableau_a_imprimer->item(row-1,col-1)->text()),format_cellule);
            QLabel *label = (QLabel *)tableau_a_imprimer->cellWidget(row-1,col-1);
            cellCursor.insertText(tr("%1").arg(label->text()),format_cellule);
        }
    }

    //fin de l'edition
    cursor.endEditBlock();

    //impression de notre editor dans le QPrinter initialisé au début de la fonction
    editor->print(&printer);
    //}
}
