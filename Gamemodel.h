#ifndef GAMEMODEL_H
#define GAMEMODEL_H
//五子棋游戏模型类//
#include<vector>
//游戏类型
enum GameType{
    Man,
    AI
};
//游戏状态
enum GameStatus{
    PLAYING,
    WIN,
    DEAD
};
//棋盘尺寸
const int BOARD_GRAD_SIZE=15;
const int MARGIN=30;//棋盘边缘空隙
const int CHESS_RADIUS=15;//棋子半径
const int MARK_SIZE=6;//落子标记边长
const int BLOCK_SIZE=40;//格子大小
const int POS_OFFSIZE=BLOCK_SIZE*0.4;//鼠标点击模糊距离
const int AI_THINK_TIMR=700;//AI思考时间
class GameModel{
public:
    GameModel(){};
public:
    //存储当前游戏棋盘和棋子的情况，空白为0，黑棋为1，白棋为-1
    std::vector<std::vector<int>>gameMapVec;
    //存储各个点位的评分情况，作为AI下棋依据
    std::vector<std::vector<int>>scoreMapVec;
    //下棋方 true:黑棋 flase:白棋
    bool playerFlag;
    GameType gameType;
    GameStatus gameStatus;
    void startGame(GameType type);
};

#endif // GAMEMODEL_H
