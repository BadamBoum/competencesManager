
#include <QPrinter>
#include <QPrintDialog>

#include <QPdfWriter>
#include <QPainter>
#include <QPagedPaintDevice>

#include <QtWidgets>

#include "fileprinter.h"

void FilePrinter::printTableWidgetToPdf(QTableWidget *tableau_a_imprimer)
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
    QPixmap tempPixmap(tableau_a_imprimer->size());
    tableau_a_imprimer->render(&tempPixmap);

    //Rotate the QPixmap
    QTransform t;
    QPixmap pixmap(tableau_a_imprimer->size().transposed());
    pixmap = tempPixmap.transformed(t.rotate(90),Qt::SmoothTransformation);


    //Draw the QPixmap with a QPainter
    QPainter painter;
    painter.begin(&test);
    painter.drawPixmap(QRectF(0, 0, test.width(), test.height()), pixmap, QRectF(0, 0,pixmap.width(), pixmap.height()));
    painter.end();
}


void FilePrinter::printTableWidgetToPDF(QTableWidget *tableau_a_imprimer, QString titre, QString filePath)
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
    QString modif ="Fait le :\t" + date.toString("dddd dd MMMM yyyy") + " a " + time.toString();

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

    //QString title = QString::fromUtf8(titre.toStdString().c_str())+"\n\n";
    QString title = "Nom de l'élève.\n";

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
            cellCursor.insertText(label->text(),format_cellule);
        }
    }

    //fin de l'edition
    cursor.endEditBlock();

    //impression de notre editor dans le QPrinter initialisé au début de la fonction
    editor->print(&printer);
    //}
}
