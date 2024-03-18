#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Gamemodel.h"
#include"QMouseEvent"
#include"QPainter"
#include"math.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setMouseTracking(true);
    //设置窗口大小
    setFixedSize(MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
                 MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);
    initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*event){
    QPainter painter(this);
    //绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing,true);//抗锯齿
    for(int i=0;i<BOARD_GRAD_SIZE+1;i++){
        painter.drawLine(MARGIN+BLOCK_SIZE*i,MARGIN,
                         MARGIN+BLOCK_SIZE*i,size().height()-MARGIN);
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                         size().width()-MARGIN,MARGIN+BLOCK_SIZE*i);
    }
    //绘制选中点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    //绘制落子标记（防止鼠标出框越界）
    if(clickPosRow>0&&clickPosRow<BOARD_GRAD_SIZE&&
       clickPosCol>0&&clickPosCol<BOARD_GRAD_SIZE&&
       game->gameMapVec[clickPosRow][clickPosCol]==0)
       {
        if(game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(MARGIN+BLOCK_SIZE*clickPosCol-MARK_SIZE/2,MARGIN+BLOCK_SIZE*clickPosRow-MARK_SIZE/2,MARK_SIZE,MARK_SIZE);
        }

    }
void MainWindow::initGame(){
    //初始化游戏模型
    game=new GameModel;
    initAIGame();
}
void MainWindow::initAIGame(){
    game_type=AI;
    game->gameStatus=PLAYING;
    //在数据模型中进行初始化功能
    game->startGame(game_type);
    update();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    //通过鼠标的hover确定落子的标记
    int x=event->x();
    int y=event->y();
    if(x>=MARGIN+BLOCK_SIZE/2&&x<size().width()-MARGIN-BLOCK_SIZE/2&&
            y>=MARGIN+BLOCK_SIZE/2&&y<size().height()-MARGIN-BLOCK_SIZE/2){
        //获取最近的左上角的点
        int col=(x-MARGIN)/BLOCK_SIZE;
        int row=(y-MARGIN)/BLOCK_SIZE;
        int leftTopPosX=MARGIN+BLOCK_SIZE*col;
        int leftTopPosY=MARGIN+BLOCK_SIZE*row;
        clickPosRow=-1;
        clickPosCol=-1;
        int len=0;
        selectPos=false;
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSIZE){
            clickPosRow=row;
            clickPosCol=col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos=true;
            }
        }
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSIZE){
            clickPosRow=row;
            clickPosCol=col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos=true;
            }
        }
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSIZE){
            clickPosRow=row+1;
            clickPosCol=col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos=true;
            }
        }
        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX)-BLOCK_SIZE+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSIZE){
            clickPosRow=row+1;
            clickPosCol=col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos=true;
            }
        }

    }
    update();
}

