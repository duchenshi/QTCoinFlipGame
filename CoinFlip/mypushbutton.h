#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>

#include <QWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString normalImg,QString pressImg="");
    //成员属性
    QString normalImgPath;
    QString pressImgPath;

    //弹跳特效
    void zoom(int downpix,int uppix);

    //重写鼠标的按下与释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);



signals:

public slots:
};

#endif // MYPUSHBUTTON_H
