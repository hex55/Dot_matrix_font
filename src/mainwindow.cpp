#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int width = ui->labelFont->width();
    int height = ui->labelFont->height();
    QImage image(ui->labelFont->size(),QImage::Format_Mono);
    QPainter painter(&image);
    QRgb     backColor = qRgb(255, 255, 255);
    image.fill(backColor); //将位图背景设置为白色

    QFont font;
    font.setFamily("SimSun"); //设置字体，宋体
    font.setPixelSize(16);    //设置字号32,以像素为单位
    font.setWeight(50);       //设置字型,不加粗
    font.setItalic(false);    //设置字型,不倾斜
    font.setUnderline(false); //设置字型,无下划线
    painter.setFont(font);
    int flats = Qt::AlignCenter |Qt::AlignTop;
    painter.drawText(0,0,width,height,flats,"李");
    int y=0;
    QPen penR(Qt::red);
    QPen penB(Qt::blue);
    for(int i=0;i<16;i++)
    {
        unsigned char *lineByte=image.scanLine(i);
        int x=100;
        for(int j=0;j<2;j++)  {
            unsigned char tp;
            tp=lineByte[j];
            for(int z=0;z<8;z++){
                if(tp&0x01){
                    painter.setPen(penR);
                    painter.drawText(x,y,"1");
                    x+=10;
                }
                else{
                    painter.setPen(penB);
                    painter.drawText(x,y,"0");
                    x+=10;
                }
                tp>>=1;
            }
        }
        y+=10;
    }

//    for(int i=0;i<width;i+=30){
//        painter.drawLine(i,0,i,height);
//    }
//    for(int i=0;i<height;i+=30){
//        painter.drawLine(0,i,width,i);
//    }

    ui->labelFont->setPixmap(QPixmap::fromImage(image));
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

void MainWindow::drawText(QPainter *paint) {
    QString  m_qsWord = tr("QT测试");
    QImage   image(128, 64, QImage::Format_Mono);
    QPainter painter(&image); //选入绘图设备中。
    QRgb     backColor = qRgb(255, 255, 255);
    image.fill(backColor); //将位图背景设置为白色
    QFont font;
    font.setFamily("SimSun"); //设置字体，宋体
    font.setPixelSize(32);    //设置字号32,以像素为单位
    font.setWeight(50);       //设置字型,不加粗
    font.setItalic(false);    //设置字型,不倾斜
    font.setUnderline(false); //设置字型,无下划线
    painter.setFont(font);
    int flats = Qt::AlignCenter | Qt::AlignTop;
    painter.drawText(image.rect(), flats, m_qsWord); //绘制文字“好”
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 16; j++) {
            int           m_nCount       = 0;
            unsigned char m_nbyte        = 0x80;
            unsigned char m_ncurrentByte = *(image.bits() + i * 16 + j);
            // printf("m_ncurrentByte : %0x/n", m_ncurrentByte);
            while (m_nCount < 8) {
                m_nbyte = 0x80;
                m_nbyte >>= m_nCount % 8;
                // printf("m_nbyte        : %0x/n", m_nbyte);
                if (!(m_ncurrentByte & m_nbyte))
                    paint->drawPoint(j * 8 + m_nCount, i);
                m_nCount++;
            }
        }
    }
}

void MainWindow::on_buttonGenerate_clicked()
{
    //QPainter *paint = new QPainter(ui->labelFont);
    //drawText(paint);
    QString  m_qsWord = tr("QT测试");
    QImage   image(128, 64, QImage::Format_Mono);
    QPainter painter(&image); //选入绘图设备中。
    QRgb     backColor = qRgb(255, 255, 255);
    image.fill(backColor); //将位图背景设置为白色
    QFont font;
    font.setFamily("SimSun"); //设置字体，宋体
    font.setPixelSize(64);    //设置字号32,以像素为单位
    font.setWeight(50);       //设置字型,不加粗
    font.setItalic(false);    //设置字型,不倾斜
    font.setUnderline(false); //设置字型,无下划线
    painter.setFont(font);
    int flats = Qt::AlignCenter | Qt::AlignTop;
    painter.drawText(image.rect(), flats, m_qsWord); //绘制文字“好”

    ui->labelFont->setPixmap(QPixmap::fromImage(image));
}
