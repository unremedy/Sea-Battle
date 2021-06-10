#ifndef SHIPS_SHIPSCOMPUTER_H
#define SHIPS_SHIPSCOMPUTER_H

#include "Constants.h"
#include <vector>
//#include <cmath>

class ShipsComputer {
public:
    size_t Field[Constants::Num][Constants::Num] = {0}; //0 - no ships
    size_t FieldForUser[Constants::Num][Constants::Num] = {0};
    std::vector<size_t> VectIDShip = {0};
    bool WinFlagUser = false;

    ~ShipsComputer() = default;

    void CreateShip(size_t LengthShip, size_t NumShips) {
        bool setting_is_possible = true;
        int x, y;
        size_t direction = 0;
        int temp_x;
        int temp_y;
        size_t ShipCounter = 0;
        while (ShipCounter < NumShips) {
            do {
                x = rand() % Constants::Num;
                y = rand() % Constants::Num;
                temp_x = x;
                temp_y = y;
                direction = rand() % 4;
                setting_is_possible = true;

                for (int i = 0; i < LengthShip; ++i) {
                    if (x < 0 || y < 0 || x >= Constants::Num || y >= Constants::Num) {
                        setting_is_possible = false;
                        break;
                    }
                    if (Field[x][y] >= 1 ||
                        Field[x][y + 1] >= 1 ||
                        Field[x][y - 1] >= 1 ||
                        Field[x + 1][y] >= 1 ||
                        Field[x + 1][y + 1] >= 1 ||
                        Field[x + 1][y - 1] >= 1 ||
                        Field[x - 1][y] >= 1 ||
                        Field[x - 1][y + 1] >= 1 ||
                        Field[x - 1][y - 1] >= 1) {
                        setting_is_possible = false;
                        break;
                    }
                    switch (direction) {
                        case 0:
                            x++;
                            break;
                        case 1:
                            y++;
                            break;
                        case 2:
                            x--;
                            break;
                        case 3:
                            y--;
                            break;
                    }
                }
            } while (!setting_is_possible);

            if (setting_is_possible) {
                x = temp_x;
                y = temp_y;
                for (int i = 0; i < LengthShip; ++i) {
                    Field[x][y] = VectIDShip.size();
                    switch (direction) {
                        case 0:
                            x++;
                            break;
                        case 1:
                            y++;
                            break;
                        case 2:
                            x--;
                            break;
                        case 3:
                            y--;
                            break;
                    }
                }
            }
            VectIDShip.push_back(LengthShip);
            ++ShipCounter;
        }
    }

    void CreateAllShips(size_t MaxShipLength) {
        size_t Len = MaxShipLength;
        size_t Count = 1;
        while (Len != 0) {
            CreateShip(Len, Count);
            ++Count;
            --Len;
        }
    }

    void PrintField() {
        for (int i = 0; i < Constants::Num; ++i) {
            for (int j = 0; j < Constants::Num; ++j) {
                if (Field[j][i] == 0)
                    std::cout << Constants::Sea << "  ";
                else {
                    std::cout << Field[j][i] << "  ";
                }
            }
            std::cout << std::endl;
        }
    }

    void PrintFieldForUser() {
        for (int i = 0; i < Constants::Num; ++i) {
            for (int j = 0; j < Constants::Num; ++j) {
                if (FieldForUser[j][i] == 0) {
                    std::cout << Constants::Sea << "  ";
                } else if (FieldForUser[j][i] == 2) {
                    std::cout << Constants::DSea << "  ";
                } else if (FieldForUser[j][i] == 3) {
                    std::cout << Constants::DPart << "  ";
                } else if (FieldForUser[j][i] == 4) {
                    std::cout << Constants::DShip << "  ";
                }
            }
            std::cout << std::endl;
        }
    }

    // 2 - empty was shot, 3 - part was shot, 4 - all ship was sunk
    void UserMove() {
        size_t x = 0, y = 0;
        size_t move = 0;
        size_t CounterWin = 0;
        while (move != 1) {
            CounterWin = 0;
            std::cout << "Enter x - vertical, y - horizontal" << std::endl;
            std::cout << "x: ";
            std::cin >> x;
            std::cout << std::endl;
            std::cout << "y: ";
            std::cin >> y;
            if ((x < Constants::Num) && (y < Constants::Num) && (FieldForUser[x][y] == 0)) {
                if (Field[x][y] == 0) {
                    FieldForUser[x][y] = 2;
                } else {
                    --VectIDShip.at(Field[x][y]);
                    if (VectIDShip.at(Field[x][y]) == 0) {
                        for (int i = 0; i < Constants::Num; ++i) {
                            for (int j = 0; j < Constants::Num; ++j) {
                                if (Field[j][i] == Field[x][y]) {
                                    FieldForUser[j][i] = 4;
                                }
                            }
                        }
                    } else {
                        FieldForUser[x][y] = 3;
                    }

                }
                for (size_t i = 0; i < VectIDShip.size(); ++i) {
                    if (VectIDShip[i] == 0) {
                        ++CounterWin;
                    }
                }
                if (CounterWin == VectIDShip.size()) {
                    WinFlagUser = !WinFlagUser;
                    std::cout << "you won" << std::endl;
                    break;
                }
                move = 1;
            } else {
                std::cout << "Wrong, try again" << std::endl;
            }
        }
    }
};

#endif //SHIPS_SHIPSCOMPUTER_H
