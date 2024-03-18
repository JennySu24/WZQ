#include"Gamemodel.h"
void GameModel::startGame(GameType type){
    gameType=type;
    //初始棋盘
    gameMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++){
        std::vector<int>lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);
    }
    //AI模式初始化评分数组
    if(gameType==AI){
        scoreMapVec.clear();
        for(int i=0;i<BOARD_GRAD_SIZE;i++){
            std::vector<int>lineScores;
            for(int j=0;j<BOARD_GRAD_SIZE;j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
    }
    //轮到黑方下棋为true,白方下棋为false
    playerFlag=true;
}
