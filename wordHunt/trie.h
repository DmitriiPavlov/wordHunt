#include <unordered_map>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#ifndef trie_h
#define trie_h
class TrieNode{
public:
    std::unordered_map<char, TrieNode*> nextNodeMap;
    
    bool validWord;
    
    
    TrieNode(){
        validWord = false;
    }
    
    ~TrieNode(){
        for (const auto & [ key, value ] : nextNodeMap) {
            delete value;
        }
    }
    //checks if an std::string is in the data structure
    bool lookUpRecursive(std:: string lookUpWord){
        
        if (lookUpWord.size() == 0){
            return validWord;
        }
        
        
        char lastChar = lookUpWord[lookUpWord.size() - 1];
        lookUpWord.pop_back();
    
        if (nextNodeMap.find(lastChar) == nextNodeMap.end()){
            return false;
        }
        
        else{
            return nextNodeMap[lastChar]->lookUpRecursive(lookUpWord);
        }
    }
    
    
    //adds the word to the structure
    void addWordRecursive(std::string newWord){
        if (newWord.size() == 0){
            validWord = true;
            return;
        }
        
        char lastChar = newWord[newWord.size() - 1];
        newWord.pop_back();
        
        if (nextNodeMap.find(lastChar) == nextNodeMap.end()){
            nextNodeMap[lastChar] = new TrieNode();
        }
        
        nextNodeMap[lastChar]->addWordRecursive(newWord);
    }
    
    bool canBeValidWordRecursive(std:: string lookUpWord){
        
        if (lookUpWord.size() == 0){
            return true;
        }
        
        
        char lastChar = lookUpWord[lookUpWord.size() - 1];
        lookUpWord.pop_back();
    
        if (nextNodeMap.find(lastChar) == nextNodeMap.end()){
            return false;
        }
        
        else{
            return nextNodeMap[lastChar]->canBeValidWordRecursive(lookUpWord);
        }
    }
    
    void addWord(std::string newWord){
        std::reverse(newWord.begin(), newWord.end());
        addWordRecursive(newWord);
    }
    
    bool lookUp(std::string newWord){
        std::reverse(newWord.begin(), newWord.end());
        return lookUpRecursive(newWord);
    }
    

    bool canBeValidWord(std::string newWord){
        std::reverse(newWord.begin(), newWord.end());
        return canBeValidWordRecursive(newWord);
    }
    
};

void readFileIntoTrie(std::string filePath, TrieNode * root){
    //boring file stuff
    std::ifstream file;
    file.open(filePath);
    std::string line;

    while(file){
    std::getline(file, line);
        root->addWord(line);
        
        
    }
    file.close();
}

#endif
