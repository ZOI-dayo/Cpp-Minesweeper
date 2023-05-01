#include <vector>
#include <random>
#include <iostream>

using namespace std;

void show(int N, vector<vector<int>> *stage) {
  cout << "   ";
  for(int i=0; i<N; i++) {
    cout << i+1 << string(2 - (i + 1)/10, ' ');
  }
  cout << endl;
  for(int i=0; i<N; i++) {
    cout << i+1 << string(2 - (i + 1)/10, ' ');
    for(int j=0; j<N; j++) {
      char result = 0;
      if((*stage)[i][j] == 5) result = 'x';
      else if((*stage)[i][j] == -1) result = '-';
      else result = (*stage)[i][j] + '0';
      cout << result << "  ";
    }
    cout << endl;
  }
}

int check(int N, int x, int y, vector<vector<int>> *stage) {
  int result = 0;
  if(y > 0 && (*stage)[x][y-1] == 5) result++;
  if(y > 0 && x > 0 && (*stage)[x-1][y-1] == 5) result++;
  if(y > 0 && x < N-1 && (*stage)[x+1][y-1] == 5) result++;
  if(y < N-1 && (*stage)[x][y+1] == 5) result++;
  if(y < N-1 && x > 0 && (*stage)[x-1][y+1] == 5) result++;
  if(y < N-1 && x < N-1 && (*stage)[x+1][y+1] == 5) result++;
  if(x > 0 && (*stage)[x-1][y] == 5) result++;
  if(x < N-1 && (*stage)[x+1][y] == 5) result++;
  return result;
}

string open(int x, int y, int N, vector<vector<int>> *stage) {
  if((*stage)[x][y] == 5) return "game over";
  else if((*stage)[x][y] != -1) return "error";
  int c = check(N, x, y, stage);
  (*stage)[x][y] = c;
  if(c == 0) {
    if(x > 0) open(x-1, y, N, stage);
    if(x < N-1) open(x+1, y, N, stage);
    if(y > 0) open(x, y-1, N, stage);
    if(y < N-1) open(x, y+1, N, stage);
  }
  return "success";
}

int main() {
  int bomb_count = 20;
  int N = 10;
  vector<vector<int>> stage(N, vector<int>(N, -1));

  random_device rnd;
  for(int i=0; i<bomb_count; i++) {
    int x = rnd() % N;
    int y = rnd() % N;
    if(stage[x][y] != 5) stage[x][y] = 5;
    else i--;
  }
  show(N, &stage);
  while(true) {
    cout << "enter x, y: ";
    int x, y;
    cin >> x >> y;
    x--;
    y--;

    string result = open(x, y, N, &stage);
    if(result == "game over") {
      cout << "game over" << endl;
      break;
    } else if(result == "error") {
      cout << "error" << endl;
      continue;
    } else if(result == "success") {
      cout << "success" << endl;
    } else {
      cout << "unknown error" << endl;
    }
    show(N, &stage);
  }
  show(N, &stage);
}
