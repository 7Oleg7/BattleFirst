#include <iostream>
using namespace std;

const string red = "\033[31m";
const string yellow = "\033[33m";
const string blue = "\033[34m";
const string nul = "\033[0m";

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

class SeaBattle {
private:
    string letters[5] = { "A","B","C","D","E" };
    char numbers[5] = { '1','2','3','4','5' };
    char playerfield[5][5];
    bool playerships[5][5] = { false };
    bool playerfieldbattle[5][5] = { false };
    int placetype = 0, placesidehor = 0, placesidever = 0;
    int x = 0, y = 0;
    bool next = false;
    int shiptype = 0;
public:
    void FirstPlayerFieldView() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                playerfield[i][j] = '~';
            }
        }
    }
    void PrintPlayerField() {
        cout << "  ";
        for (int i = 0; i < 5; i++) {
            cout << letters[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < 5; j++) {
                cout << playerfield[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        cout << "\n\n";
    }
    void PlayerShipsPlace() {
        int ships = 10;
        int battleship = 1, cruiser = 2, destroyer = 3, boats = 4;
        char cinX;
        string cinY;
        bool backcoordinates = false, backplacetype = false;
        while (ships > 0) {
            clear();
            PrintPlayerField();
            next = false;
            backplacetype = false;
            backcoordinates = false;
            cout << "Выберете тип корабля для размещения:\n1 - Линкор (осталось " << battleship << ")\n";
            cout << "2 - Крейсер (осталось " << cruiser << ")\n3 - Эсминец (осталось " << destroyer << ")\n";
            cout << "4 - Торпедные катера (осталось " << boats << ")\nВаш выбор: ";
            while (true) {
                cin >> shiptype;
                if (shiptype < 1 || shiptype>4) {
                    cout << red << "\nНедопустимый тип корабля!\n" << nul;
                    continue;
                }
                if (shiptype == 1 && battleship == 0 || shiptype == 2 && cruiser == 0 || shiptype == 3 && destroyer == 0 || shiptype == 4 && boats == 0) {
                    cout << red << "\nДанный тип уже полностью размещён!\n" << nul;
                    continue;
                }
                else break;
            }
            while (backcoordinates == false && backcoordinates != true) {
                backplacetype = false;
                while (true) {
                    cout << "\nВведите координаты размещения корабля (строка, столбец) / (x=0, y=0 => Вернуться к выбору типа): ";
                    while (true) {
                        cin >> cinX >> cinY;
                        if (cinX == '0' && cinY == "0") {
                            backcoordinates = true;
                            backplacetype = true;
                            break;
                        }
                        if (cinX < '1' || cinX > '5') {
                            cout << "Недопустимый номер строки!\n";
                            continue;
                        }
                        else if (cinY < "A" || cinY > "E") {
                            cout << "Недопустимая буква столбца!\n";
                            continue;
                        }
                        else break;
                    }
                    for (int i = 0; i < 5; i++) {
                        if (cinX == numbers[i]) x = i;
                        if (cinY == letters[i]) y = i;
                    }
                    if (playerships[x][y] == true) {
                        cout << "Данная клетка уже занята другим кораблём!\n";
                        continue;
                    }
                    else break;
                }
                while (backplacetype == false && backplacetype != true) {
                    if (shiptype != 4) {
                        cout << "Каким способом разместить корабль:\n1 - По горизонтали\n2 - По вертикали\n3 - Вернуться к выбору типа корабля\nВаш выбор: ";
                        while (true) {
                            cin >> placetype;
                            if (placetype < 1 || placetype>3) {
                                cout << "Несуществующий вариант!\n";
                                continue;
                            }
                            else break;
                        }
                        if (placetype == 3) {
                            backplacetype = true;
                            backcoordinates = true;
                            break;
                        }
                        else if (placetype == 1) {
                            cout << "В какую сторону (относительно координаты) разместить корабль:\n1 - Влево\n2 - Вправо\nВаш выбор: ";
                            while (true) {
                                cin >> placesidehor;
                                if (placesidehor < 1 || placesidehor>2) {
                                    cout << "Несуществующий вариант!\n";
                                    continue;
                                }
                                else break;
                            }
                        }
                        else if (placetype == 2) {
                            cout << "В какую сторону (относительно координаты) разместить корабль:\n1 - Вверх\n2 - Вниз\nВаш выбор: ";
                            while (true) {
                                cin >> placesidever;
                                if (placesidever < 1 || placesidever>2) {
                                    cout << "Несуществующий вариант!\n";
                                    continue;
                                }
                                else break;
                            }
                        }
                        CheckPlacePossibility();
                    }
                    if (next == true || shiptype == 4) {
                        SetShipPlace();
                        if (shiptype == 1) battleship--;
                        if (shiptype == 2) cruiser--;
                        if (shiptype == 3) destroyer--;
                        if (shiptype == 4) boats--;
                        ships--;
                        backplacetype = backcoordinates = true;
                        break;
                    }
                    if (next == false) {
                        cout << "Таким способом данный корабль разместить невозможно!\n";
                        backplacetype = false;
                        continue;
                    }
                }
            }
        }
    }
    void CheckPlacePossibility() {
        if (shiptype == 1) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 4 >= 0) next = true;
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 4 < 5) next = true;
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 4 >= 0) next = true;
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 4 < 5) next = true;
                    else next = false;
                }
            }
        }
        else if (shiptype == 2) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 3 >= 0) next = true;
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 3 < 5) next = true;
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 3 >= 0) next = true;
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 3 < 5) next = true;
                    else next = false;
                }
            }
        }
        else if (shiptype == 3) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    if (y - 2 >= 0) next = true;
                    else next = false;
                }
                if (placesidehor == 2) {
                    if (y + 2 < 5) next = true;
                    else next = false;
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    if (x - 2 >= 0) next = true;
                    else next = false;
                }
                if (placesidever == 2) {
                    if (x + 2 < 5) next = true;
                    else next = false;
                }
            }
        }
    }
    void SetShipPlace() {
        if (shiptype == 1) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 4; i--) {
                        playerfield[x][i] = 'Л';
                        playerships[x][i] = true;
                    }
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 4; i++) {
                        playerfield[x][i] = 'Л';
                        playerships[x][i] = true;
                    }
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 4; i--) {
                        playerfield[i][y] = 'Л';
                        playerships[i][y] = true;
                    }
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 4; i++) {
                        playerfield[i][y] = 'Л';
                        playerships[i][y] = true;
                    }
                }
            }
        }
        else if (shiptype == 2) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 3; i--) {
                        playerfield[x][i] = 'К';
                        playerships[x][i] = true;
                    }
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 3; i++) {
                        playerfield[x][i] = 'К';
                        playerships[x][i] = true;
                    }
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 3; i--) {
                        playerfield[i][y] = 'К';
                        playerships[i][y] = true;
                    }
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 3; i++) {
                        playerfield[i][y] = 'К';
                        playerships[i][y] = true;
                    }
                }
            }
        }
        else if (shiptype == 3) {
            if (placetype == 1) {
                if (placesidehor == 1) {
                    for (int i = y; i > y - 2; i--) {
                        playerfield[x][i] = 'Э';
                        playerships[x][i] = true;
                    }
                }
                if (placesidehor == 2) {
                    for (int i = y; i < y + 2; i++) {
                        playerfield[x][i] = 'Э';
                        playerships[x][i] = true;
                    }
                }
            }
            if (placetype == 2) {
                if (placesidever == 1) {
                    for (int i = x; i > x - 2; i--) {
                        playerfield[i][y] = 'Э';
                        playerships[i][y] = true;
                    }
                }
                if (placesidever == 2) {
                    for (int i = x; i < x + 2; i++) {
                        playerfield[i][y] = 'Э';
                        playerships[i][y] = true;
                    }
                }
            }
        }
        else if (shiptype == 4) {
            playerfield[x][y] = 'Т';
            playerships[x][y] = true;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(0));
    bool firstview = false;
    SeaBattle* game = new SeaBattle();
    game->FirstPlayerFieldView();
    game->PlayerShipsPlace();
    return 0;
}

