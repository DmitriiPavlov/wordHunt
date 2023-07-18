#include "trie.h"
#include <iostream>
#include "raylib.h"
#include "solver.h"
#include <algorithm>
#include "boardVisuals.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    TrieNode * root = new TrieNode();
    readFileIntoTrie("/Users/bison/Documents/Personal Projects/raylibprojects/wordHunt/wordHunt/words.txt", root);
    
    InitWindow(800,800,"Word Hunt");
    
    Board boardUI;
    
    for (int i = 0; i < BOARD_WIDTH; i++){
        for (int j = 0; j< BOARD_HEIGHT; j++){
            boardUI.array[i][j] = ' ';
        }
    }
    
    Pos lastPos = Pos(-1,-1);
    
    int index = 0;
    
    boardUI.x = 100; boardUI.y = 100; boardUI.w = 600; boardUI.h = 600;
    
    std::vector<std::vector<Pos>> solutions;
    
    
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLUE);
        
        if (solutions.size() != 0){
            
            boardUI.drawPath(solutions[index]);
            Path currPath; currPath.currentPath = solutions[index];
            DrawText(currPath.translateToString(boardUI.array).c_str(),100,20,80,RED);
        }
        
        boardUI.drawBoard();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && boardUI.isClickedOn(GetMouseX(), GetMouseY())){
            lastPos = boardUI.clickedOnSquare(GetMouseX(), GetMouseY());
        }
        
        int key = GetCharPressed();
        
        if(IsKeyPressed(KEY_BACKSPACE) && lastPos.isValid()){
            if (boardUI.array[lastPos.x][lastPos.y] == ' ') {
                lastPos.decrement();
                boardUI.array[lastPos.x][lastPos.y] = ' ';
            }
            else{
                boardUI.array[lastPos.x][lastPos.y] = ' ';
            }
        }
        
        
        
        if (IsKeyPressed(KEY_ENTER)){
            if (solutions.size() == 0){
                
                for (int i = 0; i< BOARD_WIDTH; i++){
                    for (int j = 0; j< BOARD_HEIGHT; j++){
                        Path firstPath = Path(Pos(i,j));
                        
                        firstPath.findAllWords(boardUI.array, root, solutions);
                    }
                }
    
                
                std::sort(solutions.begin(),solutions.end(),comparePaths);

                //purely for debugging purposes
//                for (std::vector<Pos> vector : solutions){
//                    Path newPath = Path();
//                    newPath.currentPath = vector;
//                    
//                    std::cout<<newPath.translateToString(boardUI.array)<<"\n";
//                }
            }
            else{
                if (index != solutions.size()-1){
                    index ++;
                }
            }
        }
        
        if (key>= 65 && key<=90 && lastPos.isValid()){
            boardUI.array[lastPos.x][lastPos.y] = (char)key;
            lastPos.increment();
        }
        
        if (key>= 97 && key<=120 && lastPos.isValid()){
            boardUI.array[lastPos.x][lastPos.y] = (char)(key-32);
            lastPos.increment();
        }
        
        EndDrawing();
    }


    
    
    

    

    
    return 0;
}
