#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gomokuqgraphicsview.h"
#include "gomokuqgraphicsitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionConfig_triggered();
    void changeInfo(QString);

private:
    Ui::MainWindow *ui;
    GomokuQGraphicsView *view;
};
#endif // MAINWINDOW_H
