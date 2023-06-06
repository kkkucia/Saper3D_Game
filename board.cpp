#include "board.h"

#include <iostream>
#include <vector>
#include <random>


Board::Board(int numRows, int numCols, int numMines) : rows(numRows), cols(numCols), totalMines(numMines) {
    initialize();
    placeMines();
}


// Inicjalizacja planszy
void Board::initialize() {
    grid.assign(rows, std::vector<char>(cols, '-'));
    uncoveredCount = 0;
}

// Ustawienie min na planszy
void Board::placeMines() {
    int count = 0;
    while (count < totalMines) {
        int row = generateRandomNumber(0, rows - 1);
        int col = generateRandomNumber(0, cols - 1);
        if (grid[row][col] != '*') {
            grid[row][col] = '*';
            count++;
        }
    }
}

// Zliczanie min wokół danego pola
int Board::countAdjacentMines(int row, int col) {
    int count = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols && grid[i][j] == '*') {
                count++;
            }
        }
    }
    return count;
}

void Board::uncover(int row, int col) {
    if (grid[row][col] == '*') {
        matrix[row][col] = "BUM";
        showMines();
        fail = true;
    } else {
        int count = countAdjacentMines(row, col);
        grid[row][col] = '0' + count;
        matrix[row][col] = to_string(count);
        uncoveredCount++;
        if (count == 0) {
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < rows && j >= 0 && j < cols && grid[i][j] == '-') {
                        uncover(i, j);
                    }
                }
            }
        }
        if (uncoveredCount == rows * cols - totalMines) {
            victory = true;
        }
    }
}


// Wyświetlanie min na planszy (po przegranej)
void Board::showMines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '*') {
                matrix[i][j] = "BUM";
            }
        }
    }
}


// Funkcja generująca losową liczbę całkowitą z podanego zakresu
int Board::generateRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}