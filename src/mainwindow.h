#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "base.hpp"
#include "json.hpp"

#define IndexUrl "https://github.com/JackeyLea/"

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
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionQt_triggered();

    void on_actionIndex_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
