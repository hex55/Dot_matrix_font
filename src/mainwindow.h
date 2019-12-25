#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "base.hpp"

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

    void drawText(QString text, int size);
    QString toHex(QByteArray byte);

private slots:
    void on_actionExit_triggered();

    void on_actionAbout_triggered();

    void on_actionQt_triggered();

    void on_actionIndex_triggered();

    void on_textText_textChanged();

    void on_comboBoxW_activated(const QString &text);

    void on_comboBoxH_activated(const QString &text);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
