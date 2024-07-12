#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class TrieNode{
    public:
    TrieNode* links[26];
    bool isEnd;

    TrieNode(){
        for(int i = 0; i<26; i++){
            links[i] = NULL;
        }
        isEnd = false;
    }
};

class Trie{
    public:
    TrieNode* root;

    Trie(){
        root = new TrieNode();
        ifstream dictionary;
        dictionary.open("res/custom.txt");
        string word;
        while(getline(dictionary, word)){
            this->insert(word);
        }
        dictionary.close();
    }

    void insert(string word){
        if(word.length() == 0) return;

        TrieNode* child = root;
        for(char i: word){
            int index = i>='a'? i-'a': i-'A';
            if(!child->links[index]){
                child->links[index] = new TrieNode();
            }

            child = child->links[index];
        }
        
        child->isEnd = true;
    }

    bool search(string word){
        if(word.length() == 0) return true;

        TrieNode* child = root;
        for(char i: word){
            int index = i>='a'? i-'a': i-'A';
            if(!child->links[index]) return false;

            child = child->links[index];
        }

        if(child->isEnd) return true;

        return false;
    }

    void findAllWords(TrieNode* root, vector<string>& words, string current){
        if(root->isEnd){
            words.push_back(current);
        }

        for(int i = 0; i<26; i++){
            if(root->links[i]){
                current.push_back('a'+i);
                findAllWords(root->links[i], words, current);
                current.pop_back();
            }
        }
    }

    vector<string> wordStartingWith(string word){
        vector<string> words;

        TrieNode* child = root;
        string current = "";
        for(char i: word){
            int index = i>='a'? i-'a': i-'A';
            if(!child->links[index]) return words;
            child = child->links[index];
            current.push_back('a'+index);
        }

        findAllWords(child, words, current);

        return words;
    }

};

int main(){
    Trie *t = new Trie();
    vector<string> temp = t->wordStartingWith("adv");
    for(string i: temp){
        cout<<i<<endl;
    }
    return 0;
}