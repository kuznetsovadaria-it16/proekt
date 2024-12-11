#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include "header.h"
using namespace std;
const unsigned short SIZE = 4; // ������ �������� ����
vector<int> in_game_map(SIZE);
vector<vector<int>> game_map(SIZE, in_game_map); // ������� �����
vector<int> in_right_map(SIZE);
vector<vector<int>> right_map(SIZE, in_right_map); // ���������� �������� �����
struct coordinate // ��������� ��������� �������� ��������
{
    unsigned x;
    unsigned y;
} zero; // ������
int move_count = 0; // ���������� ��� �������� ���������� �����
void create_right_map() // ������� ���������� ����� ���������� �� �������
{
    unsigned right_value = 1;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
            right_map[i][j] = right_value++;
    }
    right_map[SIZE - 1][SIZE - 1] = 0; // ������� ������� � ������ ������ ����
}
void create_game_map() // �������� ������� ������� �����
{
    unsigned limit = SIZE * SIZE - 1; // ��������� ����� �� 1, ����� �������� ����� ��� ����
    vector<int> temporary; // ��������� ������ �� �������� ����� ����� �������� � ������� �����
    for (unsigned i = 0; i < limit; i++)
        temporary.push_back(i + 1); // ��������� ������� �� 1 �� 15
    // ��������� 0 � ������ ������ ����
    game_map[SIZE - 1][SIZE - 1] = 0;
    int value;
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (i == SIZE - 1 && j == SIZE - 1) // ���������� ������ ������ ����
                continue;
            value = rand() % temporary.size();
            game_map[i][j] = temporary[value];
            temporary.erase(temporary.begin() + value);
        }
    }
    // ��������� ���������� �������� ��������
    zero.x = SIZE - 1;
    zero.y = SIZE - 1;
}
bool check_map() // ��������� ������� � ���������� ����� ��� ����������� ����� ����
{
    return game_map == right_map;
}
void up_move() // ��� ����� (������� ������� ����)
{
    if (zero.y < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
        zero.y++;
        game_map[zero.y][zero.x] = 0;
        move_count++; // ����������� ������� �����
    }
}
void down_move() // ��� ���� (������� ������� �����)
{
    if (zero.y > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
        zero.y--;
        game_map[zero.y][zero.x] = 0;
        move_count++; // ����������� ������� �����
    }
}
void right_move() // ��� ������ (������� ������� �����)
{
    if (zero.x > 0)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
        zero.x--;
        game_map[zero.y][zero.x] = 0;
        move_count++; // ����������� ������� �����
    }
}
void left_move() // ��� ����� (������� ������� ������)
{
    if (zero.x < SIZE - 1)
    {
        game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
        zero.x++;
        game_map[zero.y][zero.x] = 0;
        move_count++; // ����������� ������� �����
    }
}
void get_direction() // ���������� ������� ������� �������
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
void screen() // ������� ������ �� �����
{
    system("cls");
    for (unsigned i = 0; i < SIZE; i++)
    {
        for (unsigned j = 0; j < SIZE; j++)
        {
            if (game_map[i][j] != 0)
                cout << setw(2) << setfill('0') << game_map[i][j] << ' ';
            else
                cout << "** "; // ������� �������
        }
        cout << '\n';
    }
    cout << "���������� �����: " << move_count << endl; // ������� ���������� �����
}