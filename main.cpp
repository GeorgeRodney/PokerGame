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
    pGui->addButton(bet1Btn);
    pGui->addButton(bet1Btn);
    pGui->addButton(bet1Btn);
    pGui->addButton(bet1Btn);

    Button addCoinBtn(BTN_WIDTH, BTN_HEIGHT, BTN_ONE_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "Add Coin+");
    pGui->addButton(addCoinBtn);

    Button dealBtn(BTN_WIDTH, BTN_HEIGHT, BTN_TWO_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "DEAL");
    pGui->addButton(dealBtn);

    Button hitMeBtn(BTN_WIDTH, BTN_HEIGHT, BTN_THREE_COL, OPTION_ROW, sf::Color::Blue, pGui->getFont(), "HIT ME");
    pGui->addButton(dealBtn);

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
    while (pGui->getWindow().isOpen())
    {
        while (pGui->pollEvent()) {

            if (pGui->getEvent().type == sf::Event::Closed)
                pGui->closeWindow();

            if (pGui->getEvent().type == sf::Event::MouseButtonPressed) {
                if (pGui->getEvent().mouseButton.button == sf::Mouse::Left) {
                    // Check if mouse clicked inside button
                    auto mousePos = sf::Mouse::getPosition(pGui->getWindow());

                    switch(state)
                    {
                        case GameUtils::SETUP:
                            // ADD COINS
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::ADD_COIN).getLocalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Add Coin Button!" << std::endl;
                                pMike->addCoinsToBankRoll(1);
                                // addCoinDisplay.setString("bankroll: " + std::to_string(pMike->getBankroll()));
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
                            if (pGui->getButtonBound(GameUtils::ButtonLoc::DEAL).getGlobalBounds().contains(mousePos.x, mousePos.y)) {
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
                                currentBetDisplay.setString("Bet: " + std::to_string(0));

                                state = GameUtils::SETUP;

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
        pGui->getWindow().draw(title);
        // Draw discard (Layer TWO)
        pGui->getWindow().draw(btnOne);
        pGui->getWindow().draw(btnOneText);
        pGui->getWindow().draw(btnTwo);
        pGui->getWindow().draw(btnTwoText);
        pGui->getWindow().draw(btnThree);
        pGui->getWindow().draw(btnThreeText);
        pGui->getWindow().draw(btnFour);
        pGui->getWindow().draw(btnFourText);
        pGui->getWindow().draw(btnFive);
        pGui->getWindow().draw(btnFiveText);

        // Draw cards (Layer ONE)
        pGui->getWindow().draw(oneSprite);
        pGui->getWindow().draw(twoSprite);
        pGui->getWindow().draw(threeSprite);
        pGui->getWindow().draw(fourSprite);
        pGui->getWindow().draw(fiveSprite);

        // Draw options (Layer THREE)
        pGui->getWindow().draw(addCoinBtn);
        pGui->getWindow().draw(coinText);
        pGui->getWindow().draw(currentBetDisplay);
        pGui->getWindow().draw(dealBtn);
        pGui->getWindow().draw(delBtnText);
        pGui->getWindow().draw(dealNewCardsBtn);
        pGui->getWindow().draw(dealNewCardsText);

        // Draw Layer FOUR
        pGui->getWindow().draw(addCoinDisplay);

        // Draw Layer FIVE
        pGui->getWindow().draw(instructions);

        // Draw Bet button
        pGui->getWindow().draw(bet1Btn);
        pGui->getWindow().draw(bet1Text);
        pGui->getWindow().draw(bet2Btn);
        pGui->getWindow().draw(bet2Text);
        pGui->getWindow().draw(bet3Btn);
        pGui->getWindow().draw(bet3Text);
        pGui->getWindow().draw(bet4Btn);
        pGui->getWindow().draw(bet4Text);
        pGui->getWindow().draw(bet5Btn);
        pGui->getWindow().draw(bet5Text);

        pGui->getWindow().display();
    }

    // /// TERMINAL BASED GAME
    // std::unique_ptr<Player> pMike = std::make_unique<Player>("Mike", 35, "By the sword reforged! Anduril, Flame of the West!");
    // std::unique_ptr<Dealer> pDealer = std::make_unique<Dealer>("Dale", 58, "Pity....stays the blade.");
    // // pMike->emote();
    // Deck deck;
    // deck.initialize();

    // // Give the deck to the dealer
    // pDealer->setDeck(deck);

    // // Set the player at the dealers table. 
    // pDealer->setDealingTo(pMike->getName());

    // // Add initial coin to bankroll
    // pMike->addCoinsToBankRoll(10);

    // pDealer->deckSize();

    // while (pMike->getBankroll() > 0)
    // {
    //     // Declare bet
    //     int bet;
    //     std::cout << "You have have a bankroll of " << pMike->getBankroll() << " coins." << std::endl;
    //     std::cout << "How much would you like to bet?" << std::endl;
    //     std::cin >> bet;
    //     int betOut = pMike->declareBet(bet);
    //     pDealer->setCurrentBet(betOut);

    //     // Deal hand to player
    //     std::vector<Card> hand = pDealer->dealHand();
    //     pMike->getHand(hand);
    //     // pDealer->deckSize();

    //     // Look at player and decide which cards to discard
    //     int nDiscarded = pMike->discardXcards();
    //     std::cout << "Discarded " << nDiscarded << " cards." << std::endl;
        
    //     // Dealer deals player that many cards
    //     for (int j{0}; j < nDiscarded; ++j)
    //     {
    //         const Card tempCard = pDealer->dealCard();
    //         pDealer->deckSize();
    //         pMike->receiveCard(tempCard);
    //     }

    //     pMike->lookAtHand();

    //     // Show hand to dealer for judgement
    //     std::vector<Card> playerHand = pMike->showCardsToDealer();

    //     // // Test hand
    //     // DeckUtils::ID id[5];
    //     // id[0].suit = DeckUtils::HEART;
    //     // id[1].suit = DeckUtils::DIAMOND;
    //     // id[2].suit = DeckUtils::CLUB;
    //     // id[3].suit = DeckUtils::SPADE;
    //     // id[4].suit = DeckUtils::HEART;

    //     // id[0].val = DeckUtils::SEVEN;
    //     // id[1].val = DeckUtils::JACK;
    //     // id[2].val = DeckUtils::THREE;
    //     // id[3].val = DeckUtils::JACK;
    //     // id[4].val = DeckUtils::FIVE;
    //     // for (int card{0}; card < 5; ++card)
    //     // {
    //     //     playerHand[card].setCardId(id[card]);
    //     // }


    //     int winnings = pDealer->judgeHand(playerHand);

    //     std::cout << "You won "<< winnings << " coins." << std::endl;

    //     // Pay out according to judgement
    //     pMike->addCoinsToBankRoll(winnings);

    //     // Reset

    // }

    // std::cout << "Thank you for your money." << std::endl;









    return 0;
}