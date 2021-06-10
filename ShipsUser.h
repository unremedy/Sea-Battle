#ifndef SHIPS_SHIPSUSER_H
#define SHIPS_SHIPSUSER_H

#include "Constants.h"

class ShipsUser {
public:
    size_t Field[Constants::Num][Constants::Num] = {0}; //0 - no ships
    size_t FieldForComputer[Constants::Num][Constants::Num] = {0};
    std::vector<size_t> VectIDShip = {0};
    bool WinFlagComputer = false;

    ~ShipsUser() = default;

    void PlaceShip(size_t LengthShip, size_t NumShips) {
        bool setting_is_possible = true;
        int x = 0, y = 0;
        int temp_x, temp_y;
        size_t direction = 0;
        size_t ShipCounter = 0;
        //size_t Command = 0;
        //while((!(Command = 100) || (Command = 200))) {
        while (ShipCounter < NumShips) {
            setting_is_possible = true;
            std::cout << "Enter start point x - vertical, y - horizontal" << std::endl;
            std::cout << "x: ";
            std::cin >> x;
            std::cout << std::endl;
            std::cout << "y: ";
            std::cin >> y;
            temp_x = x;
            temp_y = y;
            std::cout << "Enter direction 8 - up, 2 - down, 6 - right, 4 - left" << std::endl;
            std::cin >> direction;
            //std::cout << Field[-1][9] << std::endl;
            for (int i = 0; i < LengthShip; ++i) {
                if ((x < 0) || (y < 0) || (x >= Constants::Num) || (y >= Constants::Num)) {
                    std::cout << "out of boarders" << std::endl;
                    setting_is_possible = false;
                    break;
                }

                if (Field[x][y] >= 1 ||
                    ((Field[x][y + 1] >= 1) && (y + 1 < Constants::Num)) ||
                    ((Field[x][y - 1] >= 1) && (y - 1 >= 0)) ||
                    ((Field[x + 1][y] >= 1) && (x + 1 < Constants::Num)) ||
                    ((Field[x + 1][y + 1] >= 1) && ((x + 1 < Constants::Num) && (y + 1 < Constants::Num))) ||
                    ((Field[x + 1][y - 1] >= 1) && ((x + 1 < Constants::Num) && (y - 1 >= 0))) ||
                    ((Field[x - 1][y] >= 1) && (x - 1 >= 0)) ||
                    ((Field[x - 1][y + 1] >= 1) && ((x - 1 >= 0) && (y + 1 < Constants::Num))) ||
                    ((Field[x - 1][y - 1] >= 1) && ((x - 1 >= 0) && (y - 1 >= 0)))) {

                    std::cout << "other ship" << std::endl;
                    setting_is_possible = false;
                    break;
                }

                if (!((direction == 6) || (direction == 2) || (direction == 4) || (direction == 8))) {
                    std::cout << "wrong direction" << std::endl;
                    setting_is_possible = false;
                    break;
                }
                switch (direction) {
                    case 6:
                        x++;
                        break;
                    case 2:
                        y++;
                        break;
                    case 4:
                        x--;
                        break;
                    case 8:
                        y--;
                        break;
                }
            }

            if (!setting_is_possible) {
                std::cout << "Wrong. Try again" << std::endl;
            } else if (setting_is_possible) {
                x = temp_x;
                y = temp_y;
                for (int i = 0; i < LengthShip; ++i) {
                    Field[x][y] = VectIDShip.size();
                    switch (direction) {
                        case 6:
                            x++;
                            break;
                        case 2:
                            y++;
                            break;
                        case 4:
                            x--;
                            break;
                        case 8:
                            y--;
                            break;
                    }
                }
                VectIDShip.push_back(LengthShip);
                ++ShipCounter;
            }
            PrintField();
        }
    }

    void PlaceAllShips(size_t MaxShipLength) {
        size_t Len = MaxShipLength;
        size_t Count = 1;
        while (Len != 0) {
            PlaceShip(Len, Count);
            ++Count;
            --Len;

        }
        PrintField();
        std::cout << std::endl;

    }

    void PrintField() {
        for (int i = 0; i < Constants::Num; ++i) {
            for (int j = 0; j < Constants::Num; ++j) {
                if (Field[j][i] == 0) {
                    std::cout << Constants::Sea << "  ";
                } else if (FieldForComputer[j][i] == 2) {
                    std::cout << Constants::DSea << "  ";
                } else if (FieldForComputer[j][i] == 3) {
                    std::cout << Constants::DPart << "  ";
                } else if (FieldForComputer[j][i] == 4) {
                    std::cout << Constants::DShip << "  ";
                } else {
                    std::cout << Field[j][i] << "  ";
                    //std::cout << Constants::AShip << "  ";
                }
            }
            std::cout << std::endl;
        }
    }

    void ComputerMove() {
        size_t x = 0, y = 0;
        size_t move = 0;
        size_t CounterWin = 0;
        while (move != 1) {
            CounterWin = 0;
            x = rand() % Constants::Num;
            y = rand() % Constants::Num;
            if ((x >= 0) && (y >= 0) && (x < Constants::Num) && (y < Constants::Num) && (FieldForComputer[x][y] == 0)) {
                if (Field[x][y] == 0) {
                    FieldForComputer[x][y] = 2;
                } else {
                    --VectIDShip.at(Field[x][y]);
                    if (VectIDShip.at(Field[x][y]) == 0) {
                        for (int i = 0; i < Constants::Num; ++i) {
                            for (int j = 0; j < Constants::Num; ++j) {
                                if (Field[j][i] == Field[x][y]) {
                                    FieldForComputer[j][i] = 4;
                                }
                            }
                        }
                    } else {
                        FieldForComputer[x][y] = 3;
                    }

                }
                for (size_t i = 0; i < VectIDShip.size(); ++i) {
                    if (VectIDShip[i] == 0) {
                        ++CounterWin;
                    }
                }
                if (CounterWin == VectIDShip.size()) {
                    WinFlagComputer = !WinFlagComputer;
                    std::cout << "computer won" << std::endl;
                    break;
                }
                std::cout << x << ":" << y << std::endl;
                move = 1;
            }
        }

    }


};

#endif //SHIPS_SHIPSUSER_H
