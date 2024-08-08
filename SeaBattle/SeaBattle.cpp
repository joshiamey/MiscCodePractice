/*
You're implementing a server for your own Sea Battle game. In this game, each player has a fixed 5x5 rectangular grid with several ships on it. Each ship can be placed either horizontally or vertically. A ship can't intersect with any other ship, but it can touch them. A ship can be 1 to 4 grid cells long and will always be one grid cell wide. All values given below and in the tests are [row, col] and are zero based.

Given the first player's game grid populated with several ships and several shots made by the second player, implement a function that goes through the shots one by one and returns the effect of each:
• If a shot didnt hit a ship, the result is "Missed"
• If a shot hit a cell that has already been attacked, the result is "Already attacked"
• A cell is only "Already attacked" if there was a ship in the cell.
• A cell will continue to be "missed" no matter how many times it is attacked if there was never a ship in that cell.
• If a shot hit ship x and it's not the last remaining cell of this ship, the result is "Attacked ship x"
• If a shot hit ship x and it is the last cell of this ship, the result is "Ship x is sunk"

Code it in C++

vector soln(vector<vector> grid, vector<vector> shots)

The grid: "." means empty. If it's not empty, it is represented as a single upper case character A-Z. It is guaranteed that there is at least one ship on the grid.
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

class Solution {
private:
    vector<vector<bool>> attacked;
    void processShot(vector<vector<string>>& board,int x, int y,vector<string>& result){
            auto val = board[x][y];
            ostringstream oss;

            if(val == "."){
                oss << "Missed";
            } else {
                if(attacked[x][y]){
                    oss << "Already attacked";
                }else{
                    bool shipsunk = true;
                    attacked[x][y] = true;
                    //traverse horizontally right
                    for(auto j = x + 1 ; j < board.size() && board[j][y] == val; ++j){
                        shipsunk &= attacked[j][y];
                        if(!shipsunk) break;                           
                    }
                    //traverse horizontally left
                    for(auto j = x - 1 ; j >= 0 && board[j][y] == val ; --j){
                        shipsunk &= attacked[j][y];        
                        if(!shipsunk) break;                           
                    
                    }

                    //traverse vertically down
                    for(auto j = y + 1 ; j < board[0].size() && board[x][j] == val; ++j){
                            shipsunk &= attacked[x][j];                            
                            if(!shipsunk) break;                           
                    }

                     //traverse vertically up
                    for(auto j = y - 1 ; j >= 0 && board[x][j] == val; --j){
                            shipsunk &= attacked[x][j];                            
                            if(!shipsunk) break;                           
                    }
                    
                    
                    if(shipsunk){
                        oss << "Ship " << val << " is sunk";
                    }
                    else{
                        oss << "Attacked ship " << val ;
                    }
                }
            } 
            result.push_back(oss.str());
       
    }
public:
    vector<string> processShots(vector<vector<string>>& board,vector<vector<int>>& shots) {
        int rows = board.size();
        int cols = board[0].size();
        vector<string> ans;
        attacked.resize(rows);
        // Initialize the matrix
        for_each(attacked.begin(),attacked.end(),[cols](vector<bool>& row){
            row.assign(cols,false);
        });

        for(const auto& shot:shots){
            processShot(board,shot[0],shot[1],ans);
        }

        return ans;
    }
};

// Function to generate a 100x100 grid with densely packed ships
vector<vector<string>> generateGrid() {
    // vector<vector<string>> grid;
    vector<vector<string>> grid(100, vector<string>(100, "."));  // Initialize 100x100 grid with "."

    // grid.resize(100);
    // for_each(grid.begin(),grid.end(),[](vector<string>& col){
    //     col.assign(100,".");
    // });

    int shipId = 1;

    // Place ships horizontally and vertically
    for (int i = 0; i < 100; i += 5) {
        for (int j = 0; j < 100; j += 5) {
            string ship = to_string(shipId++);
            for (int k = 0; k < ship.length(); ++k) {
                if (j + k < 100) {
                    grid[i][j + k] = string(1, ship[k]);        // Update grid[i][j + k] with ship's part
                    grid[i + 1][j + k] = string(1, ship[k]);    // Update grid[i + 1][j + k] with ship's part
                }
            }
        }
    }
    return grid;
}

// Function to generate 10,000 shots that cover a mix of cases
vector<vector<int>> generateShots() {
    vector<vector<int>> shots;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            shots.push_back({i, j});
        }
    }

    // Add some repeated shots and misses
    shots.push_back({0, 0});
    shots.push_back({99, 99});
    shots.push_back({50, 50});
    shots.push_back({0, 0});
    shots.push_back({99, 99});
    
    // Ensure we have exactly 10,000 shots
    while (shots.size() < 10000) {
        shots.push_back({rand() % 100, rand() % 100});
    }

    return shots;
}

int main() {
    // vector<vector<string>> grid = generateGrid();
    // vector<vector<int>> shots = generateShots();
    // vector<vector<string>> grid = {{"1","."}};
    // vector<vector<int>> shots {{0,0},{0,1}};
    vector<vector<string>> grid { {".","1","2","2","."},
                                {".","1",".",".","3"},
                                {"4","4","5","5","5"}
                              };
    vector<vector<int>> shots {{0,0},{0,1},{0,2},{1,1},{0,1},{1,4},{2,2},{2,4},{0,3},{1,3},{1,4}};
    // vector<vector<string>> grid {{"10","10","10","."}};

    // vector<vector<int>> shots {{0,0},{0,1},{0,2},{0,3},{0,2}};
    Solution sol;

    auto answer = sol.processShots(grid,shots);

    cout << "The answer is";
    return 0;
}

// int main()
// {
    // vector<vector<string>> grid { {".","1","2","2","."},
    //                             {".","1",".",".","3"},
    //                             {"4","4","5","5","5"}
    //                           };
    // vector<vector<int>> shots {{0,0},{0,1},{0,2},{1,1},{0,1},{1,4},{2,2},{2,4},{0,3},{1,3},{1,4}};
    // vector<vector<string>> grid {{"10","10","10","."}};

    // vector<vector<int>> shots {{0,0},{0,1},{0,2},{0,3},{0,2}};
    // auto grid = generateGrid();
    // auto shots = generateShots();

    // return 0;
// }