#pragma once

namespace GameUtils
{

enum GameState
{
    SETUP = 0,
    BET_STATE,
    DEAL,
    DISCARD,
    DONE
};

enum ButtonLoc
{
    DISCARD1 = 0,
    DISCARD2,
    DISCARD3,
    DISCARD4,
    DISCARD5,
    BET1,
    BET2,
    BET3,
    BET4,
    BET5,
    ADD_COIN,
    DEAL_BTN,
    HIT_ME,
    CASHOUT
};

enum BannerLoc
{  
    TITLE = 0,
    BANKROLL,
    BET,
    INSTRUCTIONS,
    WINNINGS

};

enum CardLoc
{
    ONE = 0,
    TWO,
    THREE,
    FOUR,
    FIVE
};

}