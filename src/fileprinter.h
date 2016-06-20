#ifndef FILEPRINTER_H
#define FILEPRINTER_H

class QTableWidget;
class QString;

class FilePrinter
{
public:
    static void printTableWidgetToPdf(QTableWidget *tableau_a_imprimer);
    static void printTableWidgetToPDF(QTableWidget *tableau_a_imprimer, QString titre, QString filePath);
};

#endif // FILEPRINTER_H
