#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);
    int levelIndex;

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    //二维数组。维持每个关卡的具体数据
    int gameArray[4][4];
    //二维数组。维护每个硬币具体状态，以便进行周围硬币翻转
    MyCoin * coinBtn[4][4];

    //判断是否胜利
    bool isWin;

signals:
    void chooseSceneBack();

public slots:
};

#endif // PLAYSCENE_H
