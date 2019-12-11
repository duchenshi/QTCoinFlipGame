#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<QPixmap>
#include "mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include"playscene.h"
#include<QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建开始菜单的子菜单
    QAction *quiteAction = startMenu->addAction("退出");
    //点击退出按钮，退出游戏
    connect(quiteAction,&QAction::triggered,[=](){
        this->close();
    });

    //准备音效
    //选择关卡音效
    QSound *chooseSound = new QSound(":/TapButtonSound.wav",this);
    //返回按钮音效
    QSound *backSound = new QSound(":/BackButtonSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了返回";

        //告诉主场景，我返回了，主场景监听ChooseLevelScene的返回按钮
        //延时返回
        QTimer::singleShot(100,[=](){
             emit this->chooseSceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25 + i%4 * 70,130 + i/4 * 70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str = QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;

            //添加音效
            chooseSound->play();

            //进入游戏场景
            this->hide();
            play=new PlayScene(i+1);

            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(this->geometry());
                //添加音效
                backSound->play();
                this->show();
                delete play;
                play=NULL;
            });

        });

        //为每个按钮编号关卡
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4 * 70,130 + i/4 * 70);
        //设置label上的文字对齐方式，水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //鼠标穿透事件， 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/OtherSceneBg2.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

    //
}
