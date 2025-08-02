#pragma once

namespace GameUtils
{

enum GameState
{
    SETUP = 0,
    BET,
    DEAL,
    DISCARD
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
    DEAL,
    HIT_ME

};

enum BannerLoc
{  
    TITLE = 0,
    BANKROLL,
    BET,
    INSTRUCTIONS

};

}