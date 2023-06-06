#ifndef SAPER_BOARD_H
#define SAPER_BOARD_H

#include <iostream>
#include <vector>
#include <random>
#include "globalBoard.h"

using namespace std;

class Board {
private:
    std::vector<std::vector<char>> grid;
    int rows;
    int cols;
    int totalMines;
    int uncoveredCount;

    //Generuje losową liczbę całkowitą z podanego zakresu (min do max).
    int generateRandomNumber(int min, int max);

    // Inicjalizuje planszę. Tworzy dwuwymiarowy wektor grid o rozmiarze rows na cols i wypełnia go znakiem
    // Ustawia również początkową wartość zmiennej uncoveredCount na 0.
    void initialize();

    //Losowo rozmieszcza miny na planszy. Wybiera losowe współrzędne (row, col) na planszy i
    // jeśli pole o tych współrzędnych nie zawiera już miny (grid[row][col] != '*'),
    // umieszcza minę na tym polu i zwiększa licznik count.
    // Proces powtarza się do momentu osiągnięcia wartości totalMines.
    void placeMines();

    //Zlicza miny sąsiadujące z danym polem (row, col) na planszy. Przechodzi przez sąsiadujące pola wokół (row, col)
    //(łącznie z samym polem) i jeśli są one w zakresie planszy (i >= 0 && i < rows && j >= 0 && j < cols)
    //oraz zawierają minę (grid[i][j] == '*'), zwiększa licznik count. Zwraca zliczoną wartość.
    int countAdjacentMines(int row, int col);

public:
    // inicjalizuje planszę
    Board(int numRows, int numCols, int numMines);

    //odkrywa dane pole
    void uncover(int row, int col);

    //pokazuje wszystkie
    void showMines();
};

#endif //SAPER_BOARD_H
