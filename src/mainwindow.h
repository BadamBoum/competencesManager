#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void printTableWidgetToPdf();
private:
    Ui::MainWindow *ui;
    void print(QTableWidget *tableau_a_imprimer, QString titre);
};

#endif // MAINWINDOW_H
