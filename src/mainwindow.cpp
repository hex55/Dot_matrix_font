#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    font_color = Qt::red;
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
    QString family = ui->comboBoxFont->currentFont().family();
    qDebug()<<"Current font family is: "<<family;
    font.setFamily(family); //设置字体，宋体
    font.setPixelSize(size);    //设置字号,以像素为单位
    font.setWeight(50);       //设置字型,不加粗
    font.setItalic(false);    //设置字型,不倾斜
    font.setUnderline(false); //设置字型,无下划线
    QPen pen;
    pen.setBrush(QBrush(font_color));
    painter.setFont(font);
    painter.setPen(pen);
    int flats = Qt::AlignCenter |Qt::AlignTop;
    painter.drawText(0,0,size,size,flats,text);

    //绘制表格
//    font.setPixelSize(1);
//    painter.setFont(font);
//    painter.setPen(Qt::green);
//    for(int i=0;i<size;i++){
//        painter.drawLine(i,0,i,size);
//    }
//    for(int i=0;i<size;i++){
//        painter.drawLine(0,i,size,i);
//    }

    ui->labelDisplay->setPixmap(QPixmap::fromImage(image).scaled(ui->labelDisplay->size()));

    //代码计算
    int count=0;
    QString result;
    QImage img = image;
    for(int i=0;i<size;i++){
        QByteArray byte;
        for(int j=0;j<size;j++){
            QRgb k=image.pixel(j,i);
            if(k!=backColor){
                byte.append('1');
            }
            else byte.append('0');
            if((j+1)%8==0){
                count++;
                result += toHex(byte)+',';
                byte.clear();
                if(count%8==0) result+='\n';
            }
        }
    }
    ui->textResultCpp->setPlainText(result);
}
//将QByteArray转换为十六进制字符串
QString MainWindow::toHex(QByteArray byte)
{
    int temp =1;
    int sum=0;
    for(int i=7;i>=0;i--){
        sum=sum+(byte.at(i)-'0')*temp;
        temp*=2;
    }

    return "0x"+QString::number(sum,16);
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
    if(!ui->textText->toPlainText().isEmpty()) on_textText_textChanged();
}

void MainWindow::on_comboBoxFont_currentIndexChanged(int index)
{
    Q_UNUSED(index)
    if(!ui->textText->toPlainText().isEmpty()) on_textText_textChanged();
}

void MainWindow::on_buttonChooseColor_clicked()
{
    font_color = QColorDialog::getColor(Qt::red,this,tr("Choose Color"));
}
