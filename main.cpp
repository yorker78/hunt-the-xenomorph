#include "gamecontroller.h"
int main() {
    bool continueGame = true;
    while(continueGame) {
        GameController* gc = new GameController();
        gc->startGame();
        std::cout << "Type e or end to stop, any other input will restart the game." << std::endl;
        std::string input = "";
        std::cin >> input;
        if(input == "e" || input == "end") {
            continueGame = false;
        }
    }
    return 0;
}