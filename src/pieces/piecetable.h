// piecetable.h
#ifndef PIECETABLE_H
#define PIECETABLE_H

#include <string>
#include <vector>
#include <stack>

class Piece
{
public:
    int buffer;
    int start_index;
    int size;
    Piece(int b, int s, int l);
};

class PieceTable
{
private:
    std::string* buffer[2];
    std::vector<Piece> pieces;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;

public:
    PieceTable(std::string* initial_text, std::string* add_buffer);
    void insertPiece(Piece p);
    void display();
    void push_back(int buff, int start_index, int length);
    void insert(int buff, int index, int start_index, int length);
    std::string serializeState();
    void deserializeState(std::string& state);
    void undo();
    std::vector<Piece>& getPieces() const;
    std::string* getBuffer(int bufferIndex);
    void redo();
    // std::vector<Piece>getPieces();
    // std::string* getBuffer(int buff);
};

#endif 
