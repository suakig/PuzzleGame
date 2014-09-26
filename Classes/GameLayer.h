#ifndef __PuzzleGame__GameLayer__
#define __PuzzleGame__GameLayer__

#include "cocos2d.h"
#include <random>
#include "BallSprite.h"

class GameLayer : public cocos2d::Layer
{
protected:
    //ボールチェック方向
    enum class Direction
    {
        x,
        y,
    };
    
    //Zオーダー
    enum ZOrder
    {
        BgForCharacter = 0,
        BgForPuzzle,
        Enemy,
        EnemyHp,
        Char,
        CharHp,
        Ball,
        Level,
        Result,
    };
    
    std::default_random_engine _engine; //乱数生成エンジン
    std::discrete_distribution<int> _distForBall; //乱数の分布
    
    void initBackground(); //背景の初期化
    void initBalls(); //ボールの初期表示
    BallSprite* newBalls(BallSprite::PositionIndex positionIndex); //新規ボール作成
    
public:
    GameLayer(); //コンストラクタ
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成
    static cocos2d::Scene* createScene(); //シーン生成
};

#endif /* defined(__PuzzleGame__GameLayer__) */
