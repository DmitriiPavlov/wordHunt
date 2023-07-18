#include <vector>
#include "globals.h"
#include <array>
#include "trie.h"
#ifndef solver_h
#define solver_h

class Pos{
public:
    int x;
    int y;
    
    Pos(int x, int y){
        this->x = x; this->y = y;
    }
    
    bool isValid(){
        return 0<= x && x< BOARD_WIDTH && 0<=y && y< BOARD_HEIGHT;
    }
    
    Pos add(int dx , int dy){
        return Pos(x +dx, y+ dy);
    }
    
    void increment(){
        x++;
        if (x == BOARD_WIDTH){
            x = 0;
            y++;
            if (y == BOARD_HEIGHT){
                x = BOARD_WIDTH -1;
                y = BOARD_HEIGHT-1;
            }
        }
    }
    
    void decrement(){
        x--;
        if (x < 0){
            x = BOARD_WIDTH-1;
            y--;
            if (y < 0){
                x = 0;
                y = 0;
            }
        }
    }
    
};

bool inVector(Pos position, std::vector<Pos> vector){
    for (Pos position2 : vector){
        if (position.x == position2.x && position.y == position2.y){
            return true;
        }
    }
    return false;
}
bool isPathInVec(const std::vector<Pos> & pathChecked, const std::vector<std::vector<Pos>> & pathList, char board[BOARD_WIDTH][BOARD_HEIGHT]);

class Path{
public:
    std::vector<Pos> currentPath;
    
    Path (Pos start){
        currentPath.push_back(start);
    }
    
    Path(){
        return;
    }
    
    std::string translateToString(char key[BOARD_WIDTH][BOARD_HEIGHT]){
        std::string out;
        for (Pos pos : currentPath){
            out.push_back(key[pos.x][pos.y]);
        }
        return out;
    }
    
    std::vector<Pos> possibleContinuations(){
        std::vector<Pos> out;
        
        Pos lastPos = currentPath[currentPath.size() -1];
        
        std::array<Pos, 8> potentialCandidates = {
            lastPos.add(-1,-1),
            lastPos.add(0,-1),
            lastPos.add(1,-1),
            lastPos.add(-1,0),
            lastPos.add(1,0),
            lastPos.add(-1,1),
            lastPos.add(0,1),
            lastPos.add(1,1),
        };
        
        for (Pos position : potentialCandidates){
            if (position.isValid() && !inVector(position,currentPath)){
                out.push_back(position);
            }
        }
        
        return out;
    }
    
    void findAllWords(char board[BOARD_WIDTH][BOARD_HEIGHT], TrieNode * root, std::vector<std::string> & out){
        if (root->canBeValidWord(translateToString(board))){
            if (root->lookUp(translateToString(board))){
                if (translateToString(board).size() >= 3){
                    out.push_back(translateToString(board));
                }
            }
            
            for (Pos nextMove : possibleContinuations()){
                currentPath.push_back(nextMove);
                findAllWords(board, root, out);
                currentPath.pop_back();
            }
        }
    }
    
    
    void findAllWords(char board[BOARD_WIDTH][BOARD_HEIGHT], TrieNode * root, std::vector<std::vector<Pos>> & out){
        if (root->canBeValidWord(translateToString(board))){
            if (root->lookUp(translateToString(board))){
                if (translateToString(board).size() >= 3){
                    //we need to initialize a new vector - then add that vector to the out vector
                    std::vector<Pos> newVec;
                    
                    for (Pos element : currentPath){
                        newVec.push_back(element);
                    }
                    
                    if (!isPathInVec(newVec, out,board)){
                        out.push_back(newVec);
                    }
                }
            }
            
            for (Pos nextMove : possibleContinuations()){
                currentPath.push_back(nextMove);
                findAllWords(board, root, out);
                currentPath.pop_back();
            }
        }
    }
};

bool comparePaths(const std::vector<Pos> & path1, const std::vector<Pos> & path2){
    return path1.size() > path2.size();
}

bool isPathInVec(const std::vector<Pos> & pathChecked, const std::vector<std::vector<Pos>> & pathList, char board[BOARD_WIDTH][BOARD_HEIGHT]){
    for (auto path : pathList){
        Path path1;
        path1.currentPath = path;
        Path path2;
        path2.currentPath = pathChecked;
        if (path1.translateToString(board) == path2.translateToString(board)){
            return true;
        }
        
    }
    return false;
}

#endif
