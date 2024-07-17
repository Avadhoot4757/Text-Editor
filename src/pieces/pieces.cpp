#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

class Piece
{
    private:
    public:
    int buffer;
    int start_index;
    int size;
    Piece(int b, int s, int l) : buffer(b), start_index(s), size(l) {}
};

class PieceTable
{
    private:
    string* buffer[2];
    vector<Piece> pieces;
    stack<string> undoStack;
    stack<string> redoStack;

    public:
    PieceTable(string* initial_text, string* add_buffer)
    {
        buffer[0] = initial_text;
        buffer[1] = add_buffer;

        if (!(*initial_text).empty())
            pieces.emplace_back(0, 0, (*initial_text).size());
    }

    void insertPiece(Piece p){
        pieces.push_back(p);
    }

    void display()
    {
        int count = 0;
        for (Piece p : pieces)
        {
            cout << " piece" << count++<<": ";
            int buff = p.buffer;
            int l = p.size;
            int s = p.start_index;
            for (int i = 0; i < l; i++)
                cout << (*buffer[buff])[i + s];
            cout<<endl;
        }
    }

    void push_back(int buff, int start_index, int length)
    {
        Piece p = Piece(buff, start_index, length);
        this->insertPiece(p);
    }

    void insert(int buff, int index, int start_index, int length)
    {
        undoStack.push(serializeState());
        while (!redoStack.empty()) {
            redoStack.pop();
        }

        Piece p = Piece(buff, start_index, length);
        if (index == 0) {
            pieces.insert(pieces.begin(), p);
            return;
        }

        int i = 0; 
        int j = 0;

        while (j < pieces.size()) {
            if (index < i + pieces[j].size) {
                Piece p2 = Piece(pieces[j].buffer, pieces[j].start_index + index - i, pieces[j].size - (index - i));
                pieces[j].size = index - i;
                pieces.insert(pieces.begin() + j + 1, p2);
                pieces.insert(pieces.begin() + j + 1, p);
                return;
            } else if (index == i + pieces[j].size) {
                pieces.insert(pieces.begin() + i + 1, p);
                return; 
            }
            i += pieces[j].size;
            j++; 
        }
    }

    string serializeState(){
        string ss;
        for(const auto& piece : pieces){
            ss += to_string(piece.buffer) + " ";
            ss += to_string(piece.start_index) + " ";
            ss += to_string(piece.size) + ";";
        }
        return ss;
    }

    void deserializeState(string& state){
        pieces.clear();
        int start = 0;
        int end = state.find(';');
        while (end != string::npos){
            string piece = state.substr(start, end - start);
            int first_space = piece.find(' ');
            int second_space = piece.find(' ', first_space + 1);
            
            int buffer = stoi(piece.substr(0, first_space));
            int start_index = stoi(piece.substr(first_space + 1, second_space - first_space - 1));
            int size = stoi(piece.substr(second_space + 1));
            
            pieces.push_back(Piece(buffer, start_index, size));
            
            start = end + 1;
            end = state.find(';', start);
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(serializeState());
            string state = undoStack.top();
            undoStack.pop();
            deserializeState(state);
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(serializeState());
            string state = redoStack.top();
            redoStack.pop();
            deserializeState(state);
        }
    }
};

int main() {
    string original_buffer = "This_";
    string addBuffer = "is_the_new_World_";

    PieceTable pt(&original_buffer, &addBuffer);
    cout << "Initial piece table:" << endl;
    pt.display();
    cout << "\n";

    int addBufferLength = addBuffer.size();
    pt.insert(1, original_buffer.size(), 0, addBufferLength);
    cout << "After inserting the new piece:" << endl;
    pt.display();
    cout << "\n";

    pt.undo();
    cout << "After undo:" << endl;
    pt.display();
    cout << "\n";

    pt.redo();
    cout << "After redo:" << endl;
    pt.display();
    cout << "\n";

    pt.undo();
    cout << "After another undo:" << endl;
    pt.display();
    cout << "\n";

    return 0;
}
