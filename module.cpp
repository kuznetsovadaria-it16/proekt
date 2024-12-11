#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include "header.h"
using namespace std;
const unsigned short SIZE = 4; // размер игрового пол€
vector<int> in_game_map(SIZE);
vector<vector<int>> game_map(SIZE, in_game_map); // игрова€ карта
vector<int> in_right_map(SIZE);
vector<vector<int>> right_map(SIZE, in_right_map); // правильна€ итогова€ карта
struct coordinate // хранилище координат нулевого элемента
{
    unsigned x;
    unsigned y;
} zero; // объект
int move_count = 0; // переменна€ дл€ подсчета количества ходов
void create_right_map() // создаем правильную карту заполненую по пор€дку
{
    unsigned right_value = 1;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
            right_map[i][j] = right_value++;
    }
    right_map[SIZE - 1][SIZE - 1] = 0; // нулевой элемент в нижний правый угол
}
void create_game_map() // рандомно создаем игровую карту
{
    unsigned limit = SIZE * SIZE - 1; // ”меньшаем лимит на 1, чтобы оставить место дл€ нул€
    vector<int> temporary; // временный массив из которого будем брать значени€ в игровую карту
    for (unsigned i = 0; i < limit; i++)
        temporary.push_back(i + 1); // «аполн€ем числами от 1 до 15
    // ƒобавл€ем 0 в правый нижний угол
    game_map[SIZE - 1][SIZE - 1] = 0;
    int value;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (i == SIZE - 1 && j == SIZE - 1) // ѕропускаем правый нижний угол
                continue;
            value = rand() % temporary.size();
            game_map[i][j] = temporary[value];
            temporary.erase(temporary.begin() + value);
        }
    }
    // —охран€ем координаты нулевого элемента
    zero.x = SIZE - 1;
    zero.y = SIZE - 1;
}
bool check_map() // сравнение игровой и правильной карты дл€ определени€ конца игры
{
    return game_map == right_map;
}
void up_move() // ход вверх (нулевой элемент вниз)
{
    if (zero.y < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
        zero.y++;
        game_map[zero.y][zero.x] = 0;
        move_count++; // увеличиваем счетчик ходов
    }
}
void down_move() // ход вниз (нулевой элемент вверх)
{
    if (zero.y > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
        zero.y--;
        game_map[zero.y][zero.x] = 0;
        move_count++; // увеличиваем счетчик ходов
    }
}
void right_move() // ход вправо (нулевой элемент влево)
{
    if (zero.x > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
        zero.x--;
        game_map[zero.y][zero.x] = 0;
        move_count++; // увеличиваем счетчик ходов
    }
}
void left_move() // ход влево (нулевой элемент вправо)
{
    if (zero.x < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
        zero.x++;
        game_map[zero.y][zero.x] = 0;
        move_count++; // увеличиваем счетчик ходов
    }
}
void get_direction() // определ€ем нажатую игроком стрелку
{
    int move = static_cast<int>(_getch()); // UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
    switch (move)
    {
    case 80:
        up_move(); break;
    case 72:
        down_move(); break;
    case 75:
        right_move(); break;
    case 77:
        left_move(); break;
    default:
        get_direction();
    }
}
void screen() // выводим массив на экран
{
    system("cls");
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (game_map[i][j] != 0)
                cout << setw(2) << setfill('0') << game_map[i][j] << ' ';
            else
                cout << "** "; // нулевой элемент
        }
        cout << '\n';
    }
    cout << " оличество ходов: " << move_count << endl; // выводим количество ходов
}