#include "GameLayer.h"

#define BALL_NUM_X 6
#define BALL_NUM_Y 5

USING_NS_CC;

//コンストラクタ
GameLayer::GameLayer()
{
    //乱数初期化および各ボールの出現の重みを指定
    std::random_device device;
    _engine = std::default_random_engine(device());
    _distForBall = std::discrete_distribution<int>{20, 20, 20, 20, 20, 10};
}

//シーンの生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    
    return scene;
}

//初期化
bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    initBackground();
    initBalls();
    
    return true;
}

//背景の初期化
void GameLayer::initBackground()
{
    //パズル部の背景
    auto bgForPuzzle = Sprite::create("Background2.png");
    bgForPuzzle->setAnchorPoint(Point::ZERO);//パズル部の背景を作成
    bgForPuzzle->setPosition(Point::ZERO);
    
    addChild(bgForPuzzle, ZOrder::BgForPuzzle);
}

//ボールの初期表示
void GameLayer::initBalls()
{
    for (int x = 1; x <= BALL_NUM_X; x++) {
        for (int y = 1; y <= BALL_NUM_Y; y++) {
            newBalls(BallSprite::PositionIndex(x, y));
        }
    }
}

//新規ボールの作成
BallSprite* GameLayer::newBalls(BallSprite::PositionIndex PositionIndex)
{
    //現在のタグを収得
    int currentTag = BallSprite::generateTag(PositionIndex);
    
    //乱数を元にランダムでタイプを収得
    int ballType;
    while (true) {
        ballType = _distForBall(_engine);
        
        //妥当性のチェック（ボールが隣り合わせにならないようにする）
        
        //左隣のボール
        auto ballX1Tag = currentTag - 10; //1つ左隣は10引いた値
        auto ballX2Tag = currentTag - 20; //2つ左隣は20引いた値
        auto ballX1 = (BallSprite*)(getChildByTag(ballX1Tag));
        auto ballX2 = (BallSprite*)(getChildByTag(ballX2Tag));
        
        //現在のボールが、1つ左隣と2つ左隣のボールと同じだとNG
        if (!(ballX1 && ballType == (int)ballX1->getBallType()) ||
            !(ballX2 && ballType == (int)ballX2->getBallType()))
        {
            //下隣のボール
            auto ballY1Tag = currentTag - 1; //1つ下隣は10引いた値
            auto ballY2Tag = currentTag - 2; //1つ下隣は10引いた値
            auto ballY1 = (BallSprite*)(getChildByTag(ballY1Tag));
            auto ballY2 = (BallSprite*)(getChildByTag(ballY2Tag));
            
            //現在のボールが、1つ下隣と2つ下隣のボールだとNG
            if (!(ballY1 && ballType == (int)ballY1->getBallType()) ||
                !(ballY2 && ballType == (int)ballY2->getBallType()))
            {
                //左隣と下隣が揃わない場合は、ループを抜ける
                break;
            }
        }
    }
    
    //ボールの表示
    auto ball = BallSprite::create((BallSprite::BallType)ballType, true);
    ball->setPositionIndexAndChangePosition(PositionIndex);
    addChild(ball, ZOrder::Ball);
    
    return ball;
}
                     
















