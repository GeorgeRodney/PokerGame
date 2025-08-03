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

    Banner instructionsBanner(ADD_COINS_BET_INSTR, pGui->getFont(), ROW/2, INSTRUCTION_ROW, sf::Color::Black);
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
    pGui->addButton(dealBtn);
    // std::cout << "Button_ size: " << pGui->getButtonSize() << std::endl;


    //--------------------------------------------------------------------------------------------------------------------------------------------------
    // Card 1
    sf::Texture cardOne;
    cardOne.loadFromFile("../resources/large/card_spades_A.png");
    sf::Sprite oneSprite(cardOne);
    oneSprite.setPosition(BTN_ONE_COL-oneSprite.getLocalBounds().getSize().x/2, CARD_ROW);
    // Card 2
    sf::Texture cardTwo;
    cardTwo.loadFromFile("../resources/large/card_spades_K.png");
    sf::Sprite twoSprite(cardTwo);
    twoSprite.setPosition(BTN_TWO_COL-twoSprite.getLocalBounds().getSize().x/2, CARD_ROW);
    // Card 3
    sf::Texture cardThree;
    cardThree.loadFromFile("../resources/large/card_spades_Q.png");
    sf::Sprite threeSprite(cardThree);
    threeSprite.setPosition(BTN_THREE_COL-threeSprite.getLocalBounds().getSize().x/2, CARD_ROW);
    // Card 4
    sf::Texture cardFour;
    cardFour.loadFromFile("../resources/large/card_spades_J.png");
    sf::Sprite fourSprite(cardFour);
    fourSprite.setPosition(BTN_FOUR_COL-fourSprite.getLocalBounds().getSize().x/2, CARD_ROW);
    // Card 5
    sf::Texture cardFive;
    cardFive.loadFromFile("../resources/large/card_spades_10.png");
    sf::Sprite fiveSprite(cardFive);
    fiveSprite.setPosition(BTN_FIVE_COL-fiveSprite.getLocalBounds().getSize().x/2, CARD_ROW);

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
    //>---------------------------------------------------------------------------------------------------<
    // Start Game Loop
    //>---------------------------------------------------------------------------------------------------<
    //  Citation    : ChatGPT, July 27 2025
    //
    //  Prompt      : How do I create a game loop using SFML?
    //              : Game loop by chatGPT. Fleshed out with my structures. 
    //
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
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::ADD_COIN).getLocalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Add Coin Button!" << std::endl;
                                pMike->addCoinsToBankRoll(1);
                                pGui->setBannerText(GameUtils::BannerLoc::BANKROLL, "bankroll: " + std::to_string(pMike->getBankroll()));
                            }
                            // TAKE BET
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET1).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet One!" << std::endl;
                                int betOut = pMike->declareBet(1);
                                pDealer->setCurrentBet(betOut);
                                // currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                // instructions.setString(DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET2).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Two!" << std::endl;
                                int betOut = pMike->declareBet(2);
                                pDealer->setCurrentBet(betOut);
                                // currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                // instructions.setString(DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET3).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Three!" << std::endl;
                                int betOut = pMike->declareBet(3);
                                pDealer->setCurrentBet(betOut);
                                // currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                // instructions.setString(DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET4).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Four!" << std::endl;
                                int betOut = pMike->declareBet(4);
                                pDealer->setCurrentBet(betOut);
                                // currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                // instructions.setString(DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::BET5).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Five!" << std::endl;
                                int betOut = pMike->declareBet(5);
                                pDealer->setCurrentBet(betOut);
                                // currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                // instructions.setString(DEAL_INSTR);
                                state = GameUtils::GameState::DEAL;
                            }
                            break;
                        
                        case GameUtils::DEAL:
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DEAL_BTN).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Deal!" << std::endl;
                                std::vector<Card> hand = pDealer->dealHand();
                                pMike->setHand(hand);
                                // Display current player hand
                                cardOne.loadFromFile(DeckUtils::cardToFilename(hand[0]));
                                cardTwo.loadFromFile(DeckUtils::cardToFilename(hand[1]));
                                cardThree.loadFromFile(DeckUtils::cardToFilename(hand[2]));
                                cardFour.loadFromFile(DeckUtils::cardToFilename(hand[3]));
                                cardFive.loadFromFile(DeckUtils::cardToFilename(hand[4]));
                                // instructions.setString(DISCARD_INSTR);
                                state = GameUtils::DISCARD;
                            }
                            break;
                            // STOPPED HERE. CREATE SWITCH STATEMENT FOR GAME STATE OPTIONS

                        case GameUtils::DISCARD:

                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD1).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD1, sf::Color::Red);
                                pMike->discard(0);
                                pDealer->receiveDiscard(1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD2).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD2, sf::Color::Red);
                                pMike->discard(1);
                                pDealer->receiveDiscard(1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD3).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD3, sf::Color::Red);
                                pMike->discard(2);
                                pDealer->receiveDiscard(1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD4).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD4, sf::Color::Red);
                                pMike->discard(3);
                                pDealer->receiveDiscard(1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DISCARD5).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                pGui->setButtonColor(GameUtils::ButtonLoc::DISCARD5, sf::Color::Red);
                                pMike->discard(4);
                                pDealer->receiveDiscard(1);
                            }
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::HIT_ME).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                // Get New Cards
                                pGui->setButtonColor(GameUtils::ButtonLoc::HIT_ME, sf::Color::Green);
                                for (int j{0}; j < pDealer->getNumCardsPlayerDiscard(); ++j)
                                {
                                    const Card tempCard = pDealer->dealCard();
                                    pMike->receiveCard(tempCard);
                                }
                                // Display current player hand
                                std::vector<Card> playerHand = pMike->showCardsToDealer();
                                cardOne.loadFromFile(DeckUtils::cardToFilename(playerHand[0]));
                                cardTwo.loadFromFile(DeckUtils::cardToFilename(playerHand[1]));
                                cardThree.loadFromFile(DeckUtils::cardToFilename(playerHand[2]));
                                cardFour.loadFromFile(DeckUtils::cardToFilename(playerHand[3]));
                                cardFive.loadFromFile(DeckUtils::cardToFilename(playerHand[4]));

                                int winnings = pDealer->judgeHand(playerHand);
                                std::cout << "You won "<< winnings << " coins." << std::endl;

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
        pGui->drawScreen();
        // window.draw(title);
        // // Draw discard (Layer TWO
        // window.draw(btnOneText);
        // window.draw(btnTwo);
        // window.draw(btnTwoText);
        // window.draw(btnThree);
        // window.draw(btnThreeText);
        // window.draw(btnFour);
        // window.draw(btnFourText);
        // window.draw(btnFive);
        // window.draw(btnFiveText);

        // Draw cards (Layer ONE)
        // window.draw(oneSprite);
        // window.draw(twoSprite);
        // window.draw(threeSprite);
        // window.draw(fourSprite);
        // window.draw(fiveSprite);

        // // Draw options (Layer THREE)
        // window.draw(addCoinBtn);
        // window.draw(coinText);
        // window.draw(currentBetDisplay);
        // window.draw(dealBtn);
        // window.draw(delBtnText);
        // window.draw(dealNewCardsBtn);
        // window.draw(dealNewCardsText);

        // // Draw Layer FOUR
        // window.draw(addCoinDisplay);

        // // Draw Layer FIVE
        // window.draw(instructions);

        // // Draw Bet button
        // window.draw(bet1Btn);
        // window.draw(bet1Text);
        // window.draw(bet2Btn);
        // window.draw(bet2Text);
        // window.draw(bet3Btn);
        // window.draw(bet3Text);
        // window.draw(bet4Btn);
        // window.draw(bet4Text);
        // window.draw(bet5Btn);
        // window.draw(bet5Text);

        pGui->display();
    }

    return 0;
}