#include <iostream>
#include <string>
#include <vector>
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

    public:
    PieceTable(string* initial_text, string* add_buffer)
    {
        buffer[0] = initial_text;
        buffer[1] = add_buffer;
        // cout << "initial text at the time of the contructor is " << (*buffer[0]) << "value of size is " << (*buffer[0]).size()<< endl;

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
            cout << " piece :" << count++ << endl;
            int buff = p.buffer;
            int l = p.size;
            int s = p.start_index;
            // cout << " value of l is " << l << " value of s is " << s << "value of buffer is "<< buff << endl;
            for (int i = 0; i < l; i++)
                cout << (*buffer[buff])[i + s];
            cout << endl << "----------------------------------------------------------------------------------------"<< endl;
        }

    }

    void push_back(int buff, int start_index, int length)
    {
        Piece p = Piece(buff, start_index, length);
        this->insertPiece(p);
    }
    void insert(int buff, int index, int start_index, int length)
    {
        Piece p = Piece(buff, start_index, length);
        int ptr_index = 0;
        if(index == 0)
        {
            pieces.insert(pieces.begin(), p);
            return;
        }

        int i = 0; 
        int j = 0;

        while(j < pieces.size())
        {
            // cout << " value of i is " << i << " size of peices[i] " << pieces[j].size << endl;
            if(index < i + pieces[j].size)
            {
                // cout << " the program control was here "<< endl;
                Piece p2 = Piece(buff, pieces[j].start_index + index - i, pieces[j].size - (index - i));
                pieces[j].size = index - i;
                pieces.insert(pieces.begin() + j + 1, p2);
                pieces.insert(pieces.begin() + j + 1, p);
                return;
            }
            else if(index == i + pieces[j].size)
            {
                pieces.insert(pieces.begin() + i + 1, p);
                return; 
            }
            i += pieces[j].size;
            j++; 
        } 
    }
};

int main(){
    string orignal_buffer= "This_"; 
    string addBuffer = "is_the_new_World_";

    PieceTable pt = PieceTable(&orignal_buffer, &addBuffer);
    cout << " the orignal peice table :"<< endl; 
    pt.display();
    cout << "\n\n\n\n";
    int size = addBuffer.size();
    Piece p = Piece(1, 0, size);
    pt.insertPiece(p);
    
    cout << " the peice table 2 is:"<< endl; 
    pt.display();
    cout << " the peice table 3s:"<< endl; 
    cout << "\n\n\n\n";
    addBuffer.append("Beautiful_");
    int i = 0;
    cin >> i; 
    pt.insert(1, i, size, addBuffer.size() - size);
    pt.display();
    return 1;
}