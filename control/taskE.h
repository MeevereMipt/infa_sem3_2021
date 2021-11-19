//
// Created by Meevere on 12.11.2021.
//

#ifndef INFA_SEM3_2021_TASKE_H
#define INFA_SEM3_2021_TASKE_H

int taskE();

class Cell {
public:
    char v;                                              // Вертикаль, от 'A' до 'H'
    unsigned short int h;                                // Горизонталь, от '1' до '8'
    Cell();
    Cell(char v, unsigned short int h);
};

class Piece {
protected:
    Cell cell;
public:
    explicit Piece(Cell cell);
    virtual bool available(Cell cell) = 0;
};

class King : public Piece {
public:
    explicit King(const Cell &cell);
    bool available(Cell cell) override;
};

class Queen : public Piece {
public:
    explicit Queen(const Cell &cell);
    bool available(Cell cell) override;
};

class Rook : public Piece {
public:
    explicit Rook(const Cell &cell);
    bool available(Cell cell) override;
};

class Bishop : public Piece {
public:
    explicit Bishop(const Cell &cell);
    bool available(Cell cell) override;
};

#endif //INFA_SEM3_2021_TASKE_H
