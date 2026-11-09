#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class SudokuPuzzle {
    public:

    // data
    int puzzle[9][9];

    // constructor
    SudokuPuzzle(int p[9][9]){
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                puzzle[r][c] = p[r][c];
            }
        }
    }

    // actoins
    void print(){
        for (int r = 0; r < 9; r++) {
            if (r == 3 || r == 6) {
                std::cout << "----+-----+-----" << std::endl;
            }
            for (int c = 0; c < 9; c++) {
                int clue = puzzle[r][c];
                if (c == 3 || c == 6) {
                    std::cout << " | ";
                }
            
                std::cout << clue;
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> is_num_possibility(int row, int col) {
        if (puzzle[row][col] != 0) {
        return std::vector<int>(1, puzzle[row][col]);
    }
    //std::cout << puzzle[row][col] << row << col << "!";
    std::vector<int> possibilities;
    possibilities.clear();
    for (int num = 1; num <= 9; num++) {
        bool found = false;
    for (int c = 0; c < 9; c++) {
        if (puzzle[row][c] == num) {
            found = true;
            break;
        }
    }
    for (int r = 0; r < 9; r++) {
        if (puzzle[r][col] == num) {
            found = true;
            break;
        }
    }
    int col_offset=(col/3)*3;
    int row_offset=(row/3)*3;
    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            if (puzzle[r+row_offset][c+col_offset] == num) {
                found = true;
                break;
            }
        }
    }
    if (!found) {
        possibilities.push_back(num);
    }
}
    return possibilities;
}

    bool solve_simple_first() {
    bool FoundZero = true;
    bool Foundposs = true;
    while (FoundZero && Foundposs) {
        FoundZero = false;
        Foundposs = false;
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (puzzle[row][col] == 0) {
                    FoundZero = true;
                    std::vector<int> poss = is_num_possibility(row, col);
                    if (poss.size() == 1) {
                        puzzle[row][col] = poss[0];
                        Foundposs = true;
                    }
                }
            }
        }
        if (!Foundposs and FoundZero) {
            return false;
            break;
        }
        if (!FoundZero) {
            return true;
        }
    }
    return false;
}


};

int main() {
    int total = 0;
    int puzzle[9][9];
    std::string filename = "/Users/macfinnii/Code/AsCS/sudoku-exchange-puzzle-bank/easy.txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Could not open easy.txt" << std::endl;
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.size() >= 94) {
            std::string digits = line.substr(13, 94);
            for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                    puzzle[row][col] = digits[row * 9 + col]-'0';
                }
            }
        }
        SudokuPuzzle Sudoku_puzzle(puzzle);
        if (Sudoku_puzzle.solve_simple_first()) {
            total++;
        }
    }
    file.close();
    /*
    std::vector<std::vector<int>> poss[9][9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            poss[row][col] = Sudoku_puzzle.is_num_possibility(row, col);
        }
    }
    */


    //Sudoku_puzzle.print();
    std::cout << "Total solved: " << total << std::endl;
    return 0;
}