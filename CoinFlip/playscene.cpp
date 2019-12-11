#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //初始化游戏场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    this->setWindowTitle("翻金币场景");

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

    //添加音效
    //返回按钮音效
    QSound *backSound = new QSound(":/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/LevelWinSound.wav",this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"翻金币场景中，点击了返回";

        //添加音效
        backSound->play();

        //告诉主场景，我返回了，主场景监听ChooseLevelScene的返回按钮
        //延时返回
        QTimer::singleShot(100,[=](){
             emit this->chooseSceneBack();
        });

    });

    //显示当前关卡
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //将字体设置到标签
    label->setFont(font);
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[levelIndex][i][j];
        }
    }

    //胜利后图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/LevelCompletedDialogBg.png");
    winLabel->setParent(this);
    winLabel->setPixmap(tmpPix);
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图案
            QLabel * label = new QLabel;
            label->setParent(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/BoardNode(1).png"));
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str = ":/Coin0001.png";
            }
            else
                str = ":/Coin0008.png";
            MyCoin * coin= new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];

            //将金币放入金币的二维数组中，以便于后期的维护
            coinBtn[i][j]=coin;

            //点击金币，进行反转
            connect(coin,&MyCoin::clicked,[=](){
                //添加音效
                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j]=gameArray[i][j]==0?1:0;

                //翻转周围金币

                QTimer::singleShot(100,this,[=](){
                    //添加音效
                    flipSound->play();
                    //右侧
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==1?0:1;
                    }
                    //左侧
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==1?0:1;
                    }
                    //下侧
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==1?0:1;
                    }
                    //上侧
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==1?0:1;
                    }

                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(isWin==true)
                    {
                        //添加音效
                        winSound->play();
                        qDebug()<<"游戏胜利";
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }


                        //将胜利图片跳下来
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        //持续时间
                        animation->setDuration(1000);
                        //起始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //启动
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    //创建背景
    QPixmap pix;
    pix.load(":/MenuSceneBg2.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
