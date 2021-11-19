//
// Created by Meevere on 12.11.2021.
//

#include <cmath>
#include <vector>
#include "taskE.h"
#include <iostream>

Cell::Cell(): Cell('A',1) {}                               // Конструктор клетки по умолчанию
Cell::Cell(char v, unsigned short int h): v(v), h(h) {}    // Конструктор заданной клетки поля с параметрами

Piece::Piece(Cell cell): cell(cell) {};

King::King(const Cell &cell) : Piece(cell) {}
bool King::available(Cell cell) {
    if(this->cell.v == cell.v
       && this->cell.h == cell.h) return false;

    // im worried by if char has a negative or not
    return std::abs((int)cell.v - (int)this->cell.v) <= 1
           && std::abs(cell.h - this->cell.h) <= 1;
}

Rook::Rook(const Cell &cell) : Piece(cell) {}
bool Rook::available(Cell cell) {
    if(this->cell.v == cell.v
       && this->cell.h == cell.h) return false;

    return (cell.v == this->cell.v) || (cell.h == this->cell.h);
}

Bishop::Bishop(const Cell &cell) : Piece(cell) {}
bool Bishop::available(Cell cell) {
    if(this->cell.v == cell.v
       && this->cell.h == cell.h) return false;

    return (this->cell.v + this->cell.h == cell.v + cell.h)
        || (this->cell.v - this->cell.h == cell.v - cell.h);
}

Queen::Queen(const Cell &cell) : Piece(cell) {}
bool Queen::available(Cell cell) {
    if(this->cell.v == cell.v
       && this->cell.h == cell.h) return false;

    // rock part
    return ((cell.v == this->cell.v) || (cell.h == this->cell.h))
    // bishop part
    ||    ((this->cell.v + this->cell.h == cell.v + cell.h)
        || (this->cell.v - this->cell.h == cell.v - cell.h));
}

////////////////////////////////////////////////////////////////

std::vector <bool> are_available(Cell c, std::vector<Piece*> const &pieces) {
    std::vector<bool> answ;
    for (auto p : pieces)
        answ.push_back(p->available(c));
    return answ;
}


int taskE(){
    std::vector<Piece*> pieces;
    pieces.push_back(new King(Cell('A',1)));
    pieces.push_back(new Queen(Cell('B',2)));
    pieces.push_back(new Rook(Cell('C',3)));
    pieces.push_back(new Bishop(Cell('D',4)));

    for(auto b : are_available(Cell('A',1),pieces))
        std::cout << b << ' ';
    std::cout << std::endl;

    for (auto p : pieces)
        delete p;

    return 0;
}

