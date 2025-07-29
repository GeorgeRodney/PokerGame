#include "Person.hpp"
#include "Player.hpp"
#include "Dealer.hpp"
#include "Deck.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameUtils.hpp"

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
    // Window
    sf::RenderWindow window(sf::VideoMode(ROW, COL), "Poker Game");
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/lato/Lato-Black.ttf");
    // Text
    sf::Text title("Five Card Stud : Project 2", font, 40);
    title.setPosition((ROW/2) - title.getLocalBounds().getSize().x/2, 0);
    title.setFillColor(sf::Color::Black);
    // Button 1
    sf::RectangleShape btnOne(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    btnOne.setPosition(BTN_ONE_COL-BTN_WIDTH/2, BTN_ROW);
    btnOne.setFillColor(sf::Color::Blue);
    btnOne.setOutlineColor(sf::Color::Black);
    btnOne.setOutlineThickness(BTN_OUTLINE);
    sf::Text btnOneText("DISCARD", font, 30);
    btnOneText.setPosition(BTN_ONE_COL-BTN_WIDTH/2, BTN_ROW);
    btnOneText.setFillColor(sf::Color::White);
    // Button 2
    sf::RectangleShape btnTwo(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    btnTwo.setPosition(BTN_TWO_COL-BTN_WIDTH/2, BTN_ROW);
    btnTwo.setFillColor(sf::Color::Blue);
    btnTwo.setOutlineColor(sf::Color::Black);
    btnTwo.setOutlineThickness(BTN_OUTLINE);
    sf::Text btnTwoText("DISCARD", font, 30);
    btnTwoText.setPosition(BTN_TWO_COL-BTN_WIDTH/2, BTN_ROW);
    btnTwoText.setFillColor(sf::Color::White);
    // Button 3
    sf::RectangleShape btnThree(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    btnThree.setPosition(BTN_THREE_COL-BTN_WIDTH/2, BTN_ROW);
    btnThree.setFillColor(sf::Color::Blue);
    btnThree.setOutlineColor(sf::Color::Black);
    btnThree.setOutlineThickness(BTN_OUTLINE);
    sf::Text btnThreeText("DISCARD", font, 30);
    btnThreeText.setPosition(BTN_THREE_COL-BTN_WIDTH/2, BTN_ROW);
    btnThreeText.setFillColor(sf::Color::White);
    // Button 4
    sf::RectangleShape btnFour(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    btnFour.setPosition(BTN_FOUR_COL-BTN_WIDTH/2, BTN_ROW);
    btnFour.setFillColor(sf::Color::Blue);
    btnFour.setOutlineColor(sf::Color::Black);
    btnFour.setOutlineThickness(BTN_OUTLINE);
    sf::Text btnFourText("DISCARD", font, 30);
    btnFourText.setPosition(BTN_FOUR_COL-BTN_WIDTH/2, BTN_ROW);
    btnFourText.setFillColor(sf::Color::White);
    // Button 5
    sf::RectangleShape btnFive(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    btnFive.setPosition(BTN_FIVE_COL-BTN_WIDTH/2, BTN_ROW);
    btnFive.setFillColor(sf::Color::Blue);
    btnFive.setOutlineColor(sf::Color::Black);
    btnFive.setOutlineThickness(BTN_OUTLINE);
    sf::Text btnFiveText("DISCARD", font, 30);
    btnFiveText.setPosition(BTN_FIVE_COL-BTN_WIDTH/2, BTN_ROW);
    btnFiveText.setFillColor(sf::Color::White);
    // Add coins button
    sf::RectangleShape addCoinBtn(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    addCoinBtn.setPosition(BTN_ONE_COL-BTN_WIDTH/2, OPTION_ROW);
    addCoinBtn.setFillColor(sf::Color::Blue);
    addCoinBtn.setOutlineColor(sf::Color::Black);
    addCoinBtn.setOutlineThickness(BTN_OUTLINE);
    sf::Text coinText("Add Coin+", font, 30);
    coinText.setPosition(BTN_ONE_COL-BTN_WIDTH/2, OPTION_ROW);
    coinText.setFillColor(sf::Color::White);
    // Add coin Text
    sf::Text addCoinDisplay;
    addCoinDisplay.setFont(font);
    addCoinDisplay.setCharacterSize(30);
    addCoinDisplay.setFillColor(sf::Color::Black);
    addCoinDisplay.setPosition(BTN_ONE_COL - BTN_WIDTH / 2, OPTION_OUT_ROW);
    addCoinDisplay.setString("bankroll: " + std::to_string(pMike->getBankroll()));
    // Add coin Text
    sf::Text currentBetDisplay;
    currentBetDisplay.setFont(font);
    currentBetDisplay.setCharacterSize(30);
    currentBetDisplay.setFillColor(sf::Color::Black);
    currentBetDisplay.setPosition(BTN_TWO_COL - BTN_WIDTH / 2, OPTION_OUT_ROW);
    currentBetDisplay.setString("Bet: " + std::to_string(0));

    //-----------------------------------------BET BUTTONS-------------------------------------------//
    // Button 1
    sf::RectangleShape bet1Btn(sf::Vector2f(BET_WIDTH, BET_HEIGHT));
    bet1Btn.setPosition(BET_COL-BET_WIDTH/2, 100);
    bet1Btn.setFillColor(sf::Color::Blue);
    bet1Btn.setOutlineColor(sf::Color::Black);
    bet1Btn.setOutlineThickness(BTN_OUTLINE);
    sf::Text bet1Text("BET1", font, 30);
    bet1Text.setPosition(BET_COL-BET_WIDTH/2, 100);
    bet1Text.setFillColor(sf::Color::White);
    // Button 2
    sf::RectangleShape bet2Btn(sf::Vector2f(BET_WIDTH, BET_HEIGHT));
    bet2Btn.setPosition(BET_COL-BET_WIDTH/2, 200);
    bet2Btn.setFillColor(sf::Color::Blue);
    bet2Btn.setOutlineColor(sf::Color::Black);
    bet2Btn.setOutlineThickness(BTN_OUTLINE);
    sf::Text bet2Text("BET2", font, 30);
    bet2Text.setPosition(BET_COL-BET_WIDTH/2, 200);
    bet2Text.setFillColor(sf::Color::White);
    // Button 3
    sf::RectangleShape bet3Btn(sf::Vector2f(BET_WIDTH, BET_HEIGHT));
    bet3Btn.setPosition(BET_COL-BET_WIDTH/2, 300);
    bet3Btn.setFillColor(sf::Color::Blue);
    bet3Btn.setOutlineColor(sf::Color::Black);
    bet3Btn.setOutlineThickness(BTN_OUTLINE);
    sf::Text bet3Text("BET3", font, 30);
    bet3Text.setPosition(BET_COL-BET_WIDTH/2, 300);
    bet3Text.setFillColor(sf::Color::White);
    // Button 4
    sf::RectangleShape bet4Btn(sf::Vector2f(BET_WIDTH, BET_HEIGHT));
    bet4Btn.setPosition(BET_COL-BET_WIDTH/2, 400);
    bet4Btn.setFillColor(sf::Color::Blue);
    bet4Btn.setOutlineColor(sf::Color::Black);
    bet4Btn.setOutlineThickness(BTN_OUTLINE);
    sf::Text bet4Text("BET4", font, 30);
    bet4Text.setPosition(BET_COL-BET_WIDTH/2, 400);
    bet4Text.setFillColor(sf::Color::White);
    // Button 5
    sf::RectangleShape bet5Btn(sf::Vector2f(BET_WIDTH, BET_HEIGHT));
    bet5Btn.setPosition(BET_COL-BET_WIDTH/2, 500);
    bet5Btn.setFillColor(sf::Color::Blue);
    bet5Btn.setOutlineColor(sf::Color::Black);
    bet5Btn.setOutlineThickness(BTN_OUTLINE);
    sf::Text bet5Text("BET5", font, 30);
    bet5Text.setPosition(BET_COL-BET_WIDTH/2, 500);
    bet5Text.setFillColor(sf::Color::White);
    // Deal Button
    sf::RectangleShape dealBtn(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    dealBtn.setPosition(BTN_TWO_COL-BTN_WIDTH/2, OPTION_ROW);
    dealBtn.setFillColor(sf::Color::Blue);
    dealBtn.setOutlineColor(sf::Color::Black);
    dealBtn.setOutlineThickness(BTN_OUTLINE);
    sf::Text delBtnText("DEAL", font, 30);
    delBtnText.setPosition(BTN_TWO_COL-BTN_WIDTH/2, OPTION_ROW);
    delBtnText.setFillColor(sf::Color::White);
    // Deal new cards button
    sf::RectangleShape dealNewCardsBtn(sf::Vector2f(BTN_WIDTH, BTN_HEIGHT));
    dealNewCardsBtn.setPosition(BTN_THREE_COL-BTN_WIDTH/2, OPTION_ROW);
    dealNewCardsBtn.setFillColor(sf::Color::Blue);
    dealNewCardsBtn.setOutlineColor(sf::Color::Black);
    dealNewCardsBtn.setOutlineThickness(BTN_OUTLINE);
    sf::Text dealNewCardsText("HIT ME", font, 30);
    dealNewCardsText.setPosition(BTN_THREE_COL-BTN_WIDTH/2, OPTION_ROW);
    dealNewCardsText.setFillColor(sf::Color::White);

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

    // Instruction bar
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition((ROW/2) - title.getLocalBounds().getSize().x/2, INSTRUCTION_ROW);
    instructions.setString(ADD_COINS_BET_INSTR);

    // Start Game Loop
    //>---------------------------------------------------------------------------------------------------<
    //  Citation    : ChatGPT, July 27 2025
    //
    //  Prompt      : How do I create a game loop using SFML?
    //              : Game loop by chatGPT. Fleshed out with my structures. 
    //
    //>---------------------------------------------------------------------------------------------------<
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Window open
            if (event.type == sf::Event::Closed)
                window.close();

            // // Still has bankroll
            // if (pMike->getBankroll() <= 0)
            //     window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if mouse clicked inside button
                    auto mousePos = sf::Mouse::getPosition(window);

                    switch(state)
                    {
                        case GameUtils::SETUP:
                            // ADD COINS
                            if (addCoinBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Add Coin Button!" << std::endl;
                                pMike->addCoinsToBankRoll(1);
                                addCoinDisplay.setString("bankroll: " + std::to_string(pMike->getBankroll()));
                            }
                            // TAKE BET
                            if (bet1Btn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet One!" << std::endl;
                                int betOut = pMike->declareBet(1);
                                pDealer->setCurrentBet(betOut);
                                currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                instructions.setString(DEAL_INSTR);
                                state = GameUtils::DEAL;
                            }
                            if (bet2Btn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Two!" << std::endl;
                                int betOut = pMike->declareBet(2);
                                pDealer->setCurrentBet(betOut);
                                currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                instructions.setString(DEAL_INSTR);
                                state = GameUtils::DEAL;
                            }
                            if (bet3Btn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Three!" << std::endl;
                                int betOut = pMike->declareBet(3);
                                pDealer->setCurrentBet(betOut);
                                currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                instructions.setString(DEAL_INSTR);
                                state = GameUtils::DEAL;
                            }
                            if (bet4Btn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Four!" << std::endl;
                                int betOut = pMike->declareBet(4);
                                pDealer->setCurrentBet(betOut);
                                currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                instructions.setString(DEAL_INSTR);
                                state = GameUtils::DEAL;
                            }
                            if (bet5Btn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Bet Five!" << std::endl;
                                int betOut = pMike->declareBet(5);
                                pDealer->setCurrentBet(betOut);
                                currentBetDisplay.setString("Bet: " + std::to_string(betOut));
                                instructions.setString(DEAL_INSTR);
                                state = GameUtils::DEAL;
                            }
                            break;
                        
                        case GameUtils::DEAL:
                            if (dealBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                std::cout << "Deal!" << std::endl;
                                std::vector<Card> hand = pDealer->dealHand();
                                pMike->setHand(hand);
                                // Display current player hand
                                cardOne.loadFromFile(DeckUtils::cardToFilename(hand[0]));
                                cardTwo.loadFromFile(DeckUtils::cardToFilename(hand[1]));
                                cardThree.loadFromFile(DeckUtils::cardToFilename(hand[2]));
                                cardFour.loadFromFile(DeckUtils::cardToFilename(hand[3]));
                                cardFive.loadFromFile(DeckUtils::cardToFilename(hand[4]));
                                instructions.setString(DISCARD_INSTR);
                                state = GameUtils::DISCARD;
                            }
                            break;
                            // STOPPED HERE. CREATE SWITCH STATEMENT FOR GAME STATE OPTIONS

                        case GameUtils::DISCARD:

                            if (btnOne.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                btnOne.setFillColor(sf::Color::Red);
                                pMike->discard(0);
                                pDealer->receiveDiscard(1);
                            }
                            if (btnTwo.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                btnTwo.setFillColor(sf::Color::Red);
                                pMike->discard(1);
                                pDealer->receiveDiscard(1);
                            }
                            if (btnThree.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                btnThree.setFillColor(sf::Color::Red);
                                pMike->discard(2);
                                pDealer->receiveDiscard(1);
                            }
                            if (btnFour.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                btnFour.setFillColor(sf::Color::Red);
                                pMike->discard(3);
                                pDealer->receiveDiscard(1);
                            }
                            if (btnFive.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                btnFive.setFillColor(sf::Color::Red);
                                pMike->discard(4);
                                pDealer->receiveDiscard(1);
                            }
                            if (dealNewCardsBtn.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                // Get New Cards
                                dealNewCardsBtn.setFillColor(sf::Color::Green);
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

                                btnOne.setFillColor(sf::Color::Blue);
                                btnTwo.setFillColor(sf::Color::Blue);
                                btnThree.setFillColor(sf::Color::Blue);
                                btnFour.setFillColor(sf::Color::Blue);
                                btnFive.setFillColor(sf::Color::Blue);
                                dealNewCardsBtn.setFillColor(sf::Color::Blue);
                                addCoinDisplay.setString("bankroll: " + std::to_string(pMike->getBankroll()));
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

        window.clear(sf::Color::White);
        window.draw(title);
        // Draw discard (Layer TWO)
        window.draw(btnOne);
        window.draw(btnOneText);
        window.draw(btnTwo);
        window.draw(btnTwoText);
        window.draw(btnThree);
        window.draw(btnThreeText);
        window.draw(btnFour);
        window.draw(btnFourText);
        window.draw(btnFive);
        window.draw(btnFiveText);

        // Draw cards (Layer ONE)
        window.draw(oneSprite);
        window.draw(twoSprite);
        window.draw(threeSprite);
        window.draw(fourSprite);
        window.draw(fiveSprite);

        // Draw options (Layer THREE)
        window.draw(addCoinBtn);
        window.draw(coinText);
        window.draw(currentBetDisplay);
        window.draw(dealBtn);
        window.draw(delBtnText);
        window.draw(dealNewCardsBtn);
        window.draw(dealNewCardsText);

        // Draw Layer FOUR
        window.draw(addCoinDisplay);

        // Draw Layer FIVE
        window.draw(instructions);

        // Draw Bet button
        window.draw(bet1Btn);
        window.draw(bet1Text);
        window.draw(bet2Btn);
        window.draw(bet2Text);
        window.draw(bet3Btn);
        window.draw(bet3Text);
        window.draw(bet4Btn);
        window.draw(bet4Text);
        window.draw(bet5Btn);
        window.draw(bet5Text);

        window.display();
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