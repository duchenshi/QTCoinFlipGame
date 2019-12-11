#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数代表 传入的金币路径还是银币路径
    MyCoin(QString btnImg);

    //金币的属性
    int posX;
    int posY;
    bool flag;

    //改变标志的方法，正反交替
    void changeFlag();
    QTimer *timer1;//正面翻反面
    QTimer *timer2;//反面翻正面

    int min=1;
    int max=8;

    //执行动画 标志
    //必须赋初值，不然可能点击没有效果
    bool isAnimation = false;
    //重写按下
    void mousePressEvent(QMouseEvent *e);

    //判断是否胜利后，每个按钮设置为胜利按钮，不能再被翻转
    //必须赋初值，不然可能点击没有效果
    bool isWin=false;

signals:

public slots:
};

#endif // MYCOIN_H
