#include "mycoin.h"
#include<QDebug>

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
        return ;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer;
    timer2 = new QTimer;

    //监听正面翻反面信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，重置
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;//结束动画
            timer1->stop();
        }
    });

    //监听fan面翻zheng面信号
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果翻完了，重置
        if(this->min>this->max)
        {
            this->max=8;
            isAnimation=false;//结束动画
            timer2->stop();
        }
    });
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        return ;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}

//改变正反面标志方法

void MyCoin::changeFlag()
{
    if(this->flag)
    {
        //如果是正面，翻反面
        timer1->start(30);
        isAnimation = true;//开始做动画
        this->flag=false;
    }
    else
    {
        //如果是fan面，翻zheng面
        timer2->start(30);
        isAnimation = true;//开始做动画
        this->flag=true;
    }

}
