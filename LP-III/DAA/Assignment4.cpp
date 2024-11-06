#include <bits/stdc++.h>
using namespace std;

int cnt = 0;

bool isSafe(vector<string> &board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'Q') return false;
    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') return false;
    }
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q') return false;
    }
    return true;
}

void backTracking(vector<vector<string>> &ans, vector<string> &board, int row, int n, int preRow, int preCol) {
    if (row == n) {
        ans.push_back(board);
        return;
    }

    if (row == preRow) { // Skip the pre-placed queen's row
        backTracking(ans, board, row + 1, n, preRow, preCol);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 'Q';
            backTracking(ans, board, row + 1, n, preRow, preCol);
            board[row][col] = '.';
        }
    }
}

void BNB(vector<vector<string>> &ans, int row, vector<string> &board, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, vector<int> &leftRows, int n, int preRow, int preCol) {
    if (row == n) {
        ans.push_back(board);
        cnt++;
        return;
    }

    if (row == preRow) { // Skip the pre-placed queen's row
        BNB(ans, row + 1, board, upperDiagonal, lowerDiagonal, leftRows, n, preRow, preCol);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (leftRows[col] == 0 && upperDiagonal[n - 1 + col - row] == 0 && lowerDiagonal[row + col] == 0) {
            board[row][col] = 'Q';
            leftRows[col] = 1;
            upperDiagonal[n - 1 + col - row] = 1;
            lowerDiagonal[row + col] = 1;
            BNB(ans, row + 1, board, upperDiagonal, lowerDiagonal, leftRows, n, preRow, preCol);
            board[row][col] = '.';
            leftRows[col] = 0;
            upperDiagonal[n - 1 + col - row] = 0;
            lowerDiagonal[row + col] = 0;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    vector<string> board(n, string(n, '.'));
    int preRow, preCol;
    cout << "Enter the row and column of the pre-placed queen (0-indexed): ";
    cin >> preRow >> preCol;
    board[preRow][preCol] = 'Q';  // Pre-place the queen

    int choice;
    vector<vector<string>> ans;

    // For BNB
    vector<int> leftRows(n, 0);
    vector<int> upperDiagonal(2 * n - 1, 0);
    vector<int> lowerDiagonal(2 * n - 1, 0);

    // Update constraints based on the pre-placed queen's position
    leftRows[preCol] = 1;
    upperDiagonal[n - 1 + preCol - preRow] = 1;
    lowerDiagonal[preRow + preCol] = 1;

    bool flag = true;
    while (flag) {
        cout << "---------------------------" << endl;
        cout << "Select the operation : " << endl;
        cout << "1. Backtracking" << endl;
        cout << "2. Branch and bound" << endl;
        cout << "3. Exit" << endl;
        cout << "---------------------------" << endl;

        cin >> choice;

        switch (choice) {
        case 1:
            cnt = 0;
            backTracking(ans, board, 0, n, preRow, preCol);
            cout << "Total solutions found: " << cnt << endl;
            for (const auto& solution : ans) {
                for (const auto& row : solution) {
                    cout << row << endl;
                }
                cout << endl;
            }
            ans.clear();
            break;
        case 2:
            cnt = 0;
            BNB(ans, 0, board, upperDiagonal, lowerDiagonal, leftRows, n, preRow, preCol);
            cout << "Total solutions found: " << cnt << endl;
            for (const auto& solution : ans) {
                for (const auto& row : solution) {
                    cout << row << endl;
                }
                cout << endl;
            }
            ans.clear();
            break;
        case 3:
            flag = false;
            break;
        }
    }
}
