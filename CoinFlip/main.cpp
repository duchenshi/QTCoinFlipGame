#include "mainscene.h"
#include <QApplication>
#include "dataconfig.h"
#include <QDebug>
#include<QSound>
#include<QMediaPlayer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    w.show();

    //添加背景音乐
    //音乐格式转化https://www.media.io/zh/
    //没安装插件，只支持.wav格式
    QSound * backgroundSound = new QSound(":/happy.wav");
    backgroundSound->setLoops(-1);
    backgroundSound->play();

//    QMediaPlayer *player=new QMediaPlayer();
//    player->setMedia(QUrl(":/happy.mp3"));
//    player->setVolume(100);
//    player->play();

    //测试关卡数据
//    dataConfig config;
//    for(int i=0;i<4;i++)
//    {
//        for(int j=0;j<4;j++)
//        {
//            qDebug()<<config.mData[1][i][j];
//        }
//        qDebug()<<"";
//    }
    return a.exec();
}
