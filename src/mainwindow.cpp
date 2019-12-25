#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionExit_triggered() {
    this->close();
}

void MainWindow::on_actionAbout_triggered() {
    QString msg;

    QMessageBox::information(this, tr("About"), msg, QMessageBox::Ok);
}

void MainWindow::on_actionQt_triggered() {
    qApp->aboutQt();
}

void MainWindow::on_actionIndex_triggered() {
    QDesktopServices::openUrl(QUrl(IndexUrl));
}

void MainWindow::drawText(QString text,int size)
{
    QImage image(QSize(size,size),QImage::Format_Mono);
    QPainter painter(&image);
    QRgb     backColor = qRgb(255, 255, 255);
    image.fill(backColor); //将位图背景设置为白色

    QFont font;
    font.setFamily("SimSun"); //设置字体，宋体
    font.setPixelSize(size);    //设置字号16,以像素为单位
    font.setWeight(50);       //设置字型,不加粗
    font.setItalic(false);    //设置字型,不倾斜
    font.setUnderline(false); //设置字型,无下划线
    painter.setFont(font);
    int flats = Qt::AlignCenter |Qt::AlignTop;
    painter.drawText(0,0,size,size,flats,text);

    QImage img = image;
    for(int i=0;i<image.height();i++){
        QByteArray byte;
        for(int j=0;j<image.width();j++){
            QRgb k=image.pixel(j,i);
            if(k!=backColor){
                byte.append('1');
            }
            else byte.append('0');
        }
        qDebug()<<toHex(byte);
    }

    ui->labelFont->setPixmap(QPixmap::fromImage(img).scaled(ui->labelFont->size()));
}

QString MainWindow::toHex(QByteArray byte)
{
    QString result;
    qDebug()<<byte.count();
    return result;
}

void MainWindow::on_textText_textChanged()
{
    QString text = ui->textText->toPlainText();
    if(text.isEmpty()) return;
    qDebug()<<"Current text is: "<<text;
    int size = ui->comboBoxW->currentText().toInt();
    drawText(text,size);
}

void MainWindow::on_comboBoxW_activated(const QString &text)
{
    ui->comboBoxH->setCurrentText(text);
}

void MainWindow::on_comboBoxH_activated(const QString &text)
{
    ui->comboBoxW->setCurrentText(text);
}
