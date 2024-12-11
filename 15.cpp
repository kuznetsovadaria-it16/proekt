#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include "header.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(static_cast<int>(time(NULL)));
    create_right_map(); // создание правильной карты
    do
    {
        create_game_map();
    } while (check_map());
    do // игровой цикл
    {
        screen();
        get_direction();
    } while (!check_map());
    cout << "\nВы выиграли!\nИгра окончена!\n";
    _getch();
    return 0;
}