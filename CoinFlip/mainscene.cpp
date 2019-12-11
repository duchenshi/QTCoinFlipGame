#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QDebug>
#include<QTimer>
#include<QSound>
#include<QLabel>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置主场景
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/Coin0001.png"));
    //设置标题
    setWindowTitle("阿杜带你翻金币");
    //退出按钮实现
    connect(ui->actionquite,&QAction::triggered,[=](){
        this->close();
    });

    //添加游戏规则
    QLabel * label = new QLabel;
    QLabel * label2 = new QLabel;
    QLabel * label3 = new QLabel;
    label->setParent(this);
    label2->setParent(this);
    label3->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(15);
    //将字体设置到标签
    label->setFont(font);
    label2->setFont(font);
    label3->setFont(font);
    QString str1 = "游戏规则:";
    QString str2 = "直到翻成所有金币则成功！";
    QString str3 = "奥利给！奥利给！";
    label->setText(str1);
    label2->setText(str2);
    label3->setText(str3);
    label->setGeometry(50,-100,320,588);
    label2->setGeometry(50,-50,320,588);
    label3->setGeometry(50,0,320,588);

    //准备音效文件
    QSound *startSound = new QSound(":/TapButtonSound.wav",this);


    //开始按钮
    MyPushButton *startBtn=new MyPushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){

        this->setGeometry(chooseScene->geometry());
       chooseScene->hide();//隐藏该场景
       this->show();//显示主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了开始";
        //播放音效
        startSound->play();
        //做弹起特效
        startBtn->zoom(0,3);
        startBtn->zoom(3,0);

        //延时进入到选择关卡场景中
        QTimer::singleShot(300,this,[=](){
            //设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();
        });


    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //画背景
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg2.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //左上角小背景
    pix.load((":/Title.png"));
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

MainScene::~MainScene()
{
    delete ui;
}

