
#ifndef SHIPS_ALLFUNC_H
#define SHIPS_ALLFUNC_H

#include "ShipsComputer.h"
#include "ShipsUser.h"

void DoComputer() {
    ShipsUser User;
    ShipsComputer Computer;
    bool Turn = true;
    std::cout << "place your ships" << std::endl;
    User.PrintField();
    User.PlaceAllShips(4);
    std::cout << "you placed all ships" << std::endl;
    Computer.CreateAllShips(4);
    Computer.PrintField();
    while (!Computer.WinFlagUser || !User.WinFlagComputer) {
        if (Turn) {
            Computer.UserMove();
            std::cout << std::endl;
            std::cout << std::endl;
            User.PrintField();
            std::cout << std::endl;
            std::cout << std::endl;
            Computer.PrintFieldForUser();
            Turn = !Turn;
        }
        User.ComputerMove();
        Turn = !Turn;
        std::cout << std::endl;
        std::cout << std::endl;
        User.PrintField();
        std::cout << std::endl;
        std::cout << std::endl;
        Computer.PrintFieldForUser();

    }

}


#endif //SHIPS_ALLFUNC_H
