#include "Person.hpp"
#include "Player.hpp"
#include "Dealer.hpp"
#include "Deck.hpp"
#include <memory>
#include <iostream>
#include "GameUtils.hpp"
#include "Gui.hpp"

const int ROW = 1200;
const int COL = 600;
// Button stuff (2nd layer)
const int BTN_OUTLINE = 5;
const int BTN_WIDTH = 140;
const int BTN_HEIGHT = 60;
const int BTN_ROW = 200;
const int BTN_ONE_COL = 200;
const int BTN_TWO_COL = 400;
const int BTN_THREE_COL = 600;
const int BTN_FOUR_COL = 800;
const int BTN_FIVE_COL = 1000;

// Card stuff (first layer)
const int CARD_ROW = 100;

// Options (third layer)
const int OPTION_ROW = 300;

// Fourth Layer
const int OPTION_OUT_ROW = 400;

// Instructions Row
const int INSTRUCTION_ROW = 500;
const std::string ADD_COINS_BET_INSTR = "ADD COINS and then BET";
const std::string DEAL_INSTR = "Press DEAL";
const std::string DISCARD_INSTR = "DISCARD the cards you dont want then press HIT ME";

// Bet layer
const int BET_WIDTH = 70;
const int BET_HEIGHT = 60;
const int BET_COL = 1150;

int main(void)
{
    // Initialize the poker game
    std::unique_ptr<Player> pMike = std::make_unique<Player>("Mike", 35, "By the sword reforged! Anduril, Flame of the West!");
    std::unique_ptr<Dealer> pDealer = std::make_unique<Dealer>("Dale", 58, "Pity....stays the blade.");
    Deck deck;
    deck.initialize();

    // Give the deck to the dealer
    pDealer->setDeck(deck);
    pMike->addCoinsToBankRoll(5);

    // Game State Machine
    GameUtils::GameState state(GameUtils::SETUP);

    // Init the GUI
    // std::cout << "A" << std::endl;
    std::unique_ptr<Gui> pGui = std::make_unique<Gui>(sf::VideoMode(ROW, COL), "Poker Game", "/usr/share/fonts/truetype/lato/Lato-Black.ttf");

    // BANNERS
    Banner title("Five Card Stud : Project 2", pGui->getFont(), COL/2, ROW, sf::Color::Black);
    pGui->addBanner(title);

    Banner addCoinBanner("bankroll: " + std::to_string(pMike->getBankroll()), pGui->getFont(), BTN_ONE_COL, OPTION_OUT_ROW, sf::Color::Black);
    pGui->addBanner(addCoinBanner);
 
    Banner currentBetBanner("Bet: " + std::to_string(0), pGui->getFont(), BTN_TWO_COL, OPTION_OUT_ROW, sf::Color::Black);
    pGui->addBanner(currentBetBanner);

    Banner instructionsBanner(ADD_COINS_BET_INSTR, pGui->getFont(), COL/2, INSTRUCTION_ROW, sf::Color::Black);
    pGui->addBanner(instructionsBanner);

    // BUTTONS
    Button discard1(BTN_WIDTH, BTN_HEIGHT, BTN_ONE_COL, BTN_ROW, sf::Color::Blue, pGui->getFont(), "DISCARD");
    Button discard2(BTN_WIDTH, BTN_HEIGHT, BTN_TWO_COL, BTN_ROW, sf::Color::Blue, pGui->getFont(), "DISCARD");
    Button discard3(BTN_WIDTH, BTN_HEIGHT, BTN_THREE_COL, BTN_ROW, sf::Color::Blue, pGui->getFont(), "DISCARD");
    Button discard4(BTN_WIDTH, BTN_HEIGHT, BTN_FOUR_COL, BTN_ROW, sf::Color::Blue, pGui->getFont(), "DISCARD");
    Button discard5(BTN_WIDTH, BTN_HEIGHT, BTN_FIVE_COL, BTN_ROW, sf::Color::Blue, pGui->getFont(), "DISCARD");
    pGui->addButton(discard1);
    pGui->addButton(discard2);
    pGui->addButton(discard3);
    pGui->addButton(discard4);
    pGui->addButton(discard5);

    Button bet1Btn(BET_WIDTH, BET_HEIGHT, BET_COL, 100, sf::Color::Blue, pGui->getFont(), "BET1");
    Button bet2Btn(BET_WIDTH, BET_HEIGHT, BET_COL, 200, sf::Color::Blue, pGui->getFont(), "BET2");
    Button bet3Btn(BET_WIDTH, BET_HEIGHT, BET_COL, 300, sf::Color::Blue, pGui->getFont(), "BET3");
    Button bet4Btn(BET_WIDTH, BET_HEIGHT, BET_COL, 400, sf::Color::Blue, pGui->getFont(), "BET4");
    Button bet5Btn(BET_WIDTH, BET_HEIGHT, BET_COL, 500, sf::Color::Blue, pGui->getFont(), "BET5");
    pGui->addButton(bet1Btn);
    pGui->addButton(bet2Btn);
    pGui->addButton(bet3Btn);
    pGui->addButton(bet4Btn);
    pGui->addButton(bet5Btn);
    // std::cout << "Button_ size: " << pGui->getButtonSize() << std::endl;

    Button addCoinBtn(BTN_WIDTH, BTN_HEIGHT, BTN_ONE_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "Add Coin+");
    pGui->addButton(addCoinBtn);
    // std::cout << "Button_ size: " << pGui->getButtonSize() << std::endl;

    Button dealBtn(BTN_WIDTH, BTN_HEIGHT, BTN_TWO_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "DEAL");
    pGui->addButton(dealBtn);

    Button hitMeBtn(BTN_WIDTH, BTN_HEIGHT, BTN_THREE_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "HIT ME");
    pGui->addButton(hitMeBtn);


    //--------------------------------------------------------------------------------------------------------------------------------------------------
    CardSprite card1("../resources/large/card_spades_A.png", BTN_ONE_COL, CARD_ROW);
    CardSprite card2("../resources/large/card_spades_K.png", BTN_TWO_COL, CARD_ROW);
    CardSprite card3("../resources/large/card_spades_Q.png", BTN_THREE_COL, CARD_ROW);
    CardSprite card4("../resources/large/card_spades_J.png", BTN_FOUR_COL, CARD_ROW);
    CardSprite card5("../resources/large/card_spades_10.png", BTN_FIVE_COL, CARD_ROW);
    pGui->addCard(card1);
    pGui->addCard(card2);
    pGui->addCard(card3);
    pGui->addCard(card4);
    pGui->addCard(card5);
    bool firstGo(true);

    //>---------------------------------------------------------------------------------------------------<
    //  Citation    :   ChatGPT, July 27 2025
    //
    //  Prompt      :   How on earth do I turn my C++ terminal poker game into a GUI game?
    //
    //  Outcome     :   I took quite a few ideas from chatGpt on GUI game design and modified them to my ends. 
    //                  Admittedly, I am new to GUIs and so I started with a naive copy/paste method.
    //                  My plan is to OOPify the GUI after getting it working. In the same way that I got
    //                  the poker game woring in terminal first. Baby steps.
    //
    //
    //>---------------------------------------------------------------------------------------------------<
    // Start Game Loop
    //>---------------------------------------------------------------------------------------------------<
    //  Citation    : ChatGPT, July 27 2025
    //
    //  Prompt      : How do I create a game loop using SFML?
    //              : Game loop by chatGPT. Fleshed out with my structures. 
    //
    //>---------------------------------------------------------------------------------------------------<


    //>-----------------------------------THOUGHTS--------------------------------------------------------<
    //              :   I have OOPified the GUI. I created Button, Banner, and Card objects. 
    //                  If I was going to take this project further I would:
    //                      1. Create a GameEngine object.
    //                      2. Robustness test the actual game. 
    //>---------------------------------------------------------------------------------------------------<

    pGui->debugButtons();
    while (pGui->isWindowOpen())
    {
        sf::Event event;
        while (pGui->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                pGui->closeWindow();

            if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(pGui->getWindow());
                    std::cout << mousePos.x << ", " << mousePos.y << std::endl;
                    // throw std::runtime_error("git here");
                    switch(state)
                    {
                        case GameUtils::SETUP:
                            // ADD COINS
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::ADD_COIN).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Add Coin Button!" << std::endl;
                                pMike->addCoinsToBankRoll(1);
                                pGui->setBannerText(GameUtils::BannerLoc::BANKROLL, "bankroll: " + std::to_string(pMike->getBankroll()));
                            }
                            // TAKE BET
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET1).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet One!" << std::endl;
                                int betOut = pMike->declareBet(1);
                                pDealer->setCurrentBet(betOut);
                                pGui->setBannerText(GameUtils::BannerLoc::BET,"Bet: " + std::to_string(betOut));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET2).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Two!" << std::endl;
                                int betOut = pMike->declareBet(2);
                                pDealer->setCurrentBet(betOut);
                                pGui->setBannerText(GameUtils::BannerLoc::BET,"Bet: " + std::to_string(betOut));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET3).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Three!" << std::endl;
                                int betOut = pMike->declareBet(3);
                                pDealer->setCurrentBet(betOut);
                                pGui->setBannerText(GameUtils::BannerLoc::BET,"Bet: " + std::to_string(betOut));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET4).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Four!" << std::endl;
                                int betOut = pMike->declareBet(4);
                                pDealer->setCurrentBet(betOut);
                                pGui->setBannerText(GameUtils::BannerLoc::BET,"Bet: " + std::to_string(betOut));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET5).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Five!" << std::endl;
                                int betOut = pMike->declareBet(5);
                                pDealer->setCurrentBet(betOut);
                                pGui->setBannerText(GameUtils::BannerLoc::BET,"Bet: " + std::to_string(betOut));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            break;
                        
                        case GameUtils::DEAL:
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DEAL_BTN).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Deal!" << std::endl;
                                std::vector<Card> hand = pDealer->dealHand();
                                pMike->setHand(hand);
                                // Display current player hand
                                pGui->setCard(GameUtils::CardLoc::ONE, DeckUtils::cardToFilename(hand[0]));
                                pGui->setCard(GameUtils::CardLoc::TWO, DeckUtils::cardToFilename(hand[1]));
                                pGui->setCard(GameUtils::CardLoc::THREE, DeckUtils::cardToFilename(hand[2]));
                                pGui->setCard(GameUtils::CardLoc::FOUR, DeckUtils::cardToFilename(hand[3]));
                                pGui->setCard(GameUtils::CardLoc::FIVE, DeckUtils::cardToFilename(hand[4]));
                                pGui->setBannerText(GameUtils::BannerLoc::INSTRUCTIONS, DISCARD_INSTR);
                                if (firstGo) firstGo = false;
                                state = GameUtils::DISCARD;
                            }
                            break;

                        case GameUtils::DISCARD:

                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD1).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->toggleButton(GameUtils::ButtonLoc::DISCARD1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD2).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->toggleButton(GameUtils::ButtonLoc::DISCARD2);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD3).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->toggleButton(GameUtils::ButtonLoc::DISCARD3);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD4).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->toggleButton(GameUtils::ButtonLoc::DISCARD4);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD5).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->toggleButton(GameUtils::ButtonLoc::DISCARD5);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::HIT_ME).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                // Check for discards
                                for (int j = 4; j >= 0; --j)
                                {
                                    if (pGui->getToggledState(static_cast<GameUtils::ButtonLoc>(j)) == true)
                                    {
                                        pMike->discard(j);
                                        pDealer->receiveDiscard(1);
                                    }
                                }
                                
                                std::cout << "Discarded " << pDealer->getNumCardsPlayerDiscard() << " cards." << std::endl;
                                for (int j{0}; j < pDealer->getNumCardsPlayerDiscard(); ++j)
                                {
                                    const Card tempCard = pDealer->dealCard();
                                    pMike->receiveCard(tempCard);
                                }
                                // Display current player hand
                                std::vector<Card> playerHand = pMike->showCardsToDealer();
                                pGui->setCard(GameUtils::CardLoc::ONE, DeckUtils::cardToFilename(playerHand[0]));
                                pGui->setCard(GameUtils::CardLoc::TWO, DeckUtils::cardToFilename(playerHand[1]));
                                pGui->setCard(GameUtils::CardLoc::THREE, DeckUtils::cardToFilename(playerHand[2]));
                                pGui->setCard(GameUtils::CardLoc::FOUR, DeckUtils::cardToFilename(playerHand[3]));
                                pGui->setCard(GameUtils::CardLoc::FIVE, DeckUtils::cardToFilename(playerHand[4]));

                                int winnings = pDealer->judgeHand(playerHand);
                                std::cout << "You won "<< winnings << " coins." << std::endl;
                                if (winnings > 3) pMike->emote();

                                // Pay out according to judgement
                                pMike->addCoinsToBankRoll(winnings);

                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD1, sf::Color::Blue);
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD2, sf::Color::Blue);
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD3, sf::Color::Blue);
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD4, sf::Color::Blue);
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD5, sf::Color::Blue);
                                pGui->setButtonColor(GameUtils::ButtonLoc::HIT_ME, sf::Color::Blue);

                                pGui->setBannerText(GameUtils::BannerLoc::BANKROLL, "bankroll: " + std::to_string(pMike->getBankroll()));
                                pGui->setBannerText(GameUtils::BannerLoc::BET, "Bet: " + std::to_string(0));
                                pDealer->resetGame();
                                pGui->resetToggle();
                                
                                state = GameUtils::GameState::SETUP;

                            }
                            break;

                        default:
                            throw std::logic_error("Switch statement error");
                            break;

                    }
                }
            }
        }

        pGui->clearWindow();
        pGui->drawScreen(firstGo);
        pGui->display();
    }

    return 0;
}