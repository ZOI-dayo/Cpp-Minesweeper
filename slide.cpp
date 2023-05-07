#include <bits/stdc++.h>
using namespace std;
enum class State {
  DEFAULT,
  OPENED,
  BOMB,
};
int opened = 0;
bool game_finished = false;
int count(int N, vector<vector<State>> stage, int x, int y) {
  int ans = 0;
  for(int i = -1; i <= 1; i++) {
    for(int j = -1; j <= 1; j++) {
      if(i == 0 && j == 0) continue;
      if(x+i < 0 || N <= x+i) continue;
      if(y+j < 0 || N <= y+j) continue;
      if(stage[x+i][y+j] == State::BOMB) ans++;
    }
  }
  return ans;
}
void show(int N, vector<vector<State>> stage) {
  cout << "  ";
  for(int x=0; x<N; x++) cout << x+1 << " ";
  cout << endl;

  for(int x=0; x<N; x++) {
    cout << (char)('a' + x) << " ";
    for(int y=0; y<N; y++) {
      if(stage[x][y] == State::DEFAULT || stage[x][y] == State::BOMB) cout << "- ";
      else if(stage[x][y] == State::OPENED) {
        int c = count(N, stage, x, y);
        if(c == 0) cout << "  ";
        else cout << c << " ";
      }
      // else cout << "x ";
    }
    cout << endl;
  }
}
void open(int N, vector<vector<State>> *stage, int x, int y) {
  if((*stage)[x][y] == State::DEFAULT)  {
    (*stage)[x][y] = State::OPENED;
    opened++;
    if(count(N, *stage, x, y) == 0) {
      for(int i = -1; i <= 1; i++) {
        for(int j = -1; j <= 1; j++) {
          if(i == 0 && j == 0) continue;
          if(x+i < 0 || N <= x+i) continue;
          if(y+j < 0 || N <= y+j) continue;
          if((*stage)[x+i][y+j] != State::OPENED) open(N, stage, x+i, y+j);
        }
      }
    }
  } else if((*stage)[x][y] == State::OPENED) cout << "opened" << endl;
  else {
    game_finished = true;
    cout << "game over" << endl;
  }
}
int main() {
  int N = 10;
  vector<vector<State>> stage(N, vector<State>(N, State::DEFAULT));
  int bomb_count = 5;
  random_device rnd;
  for (int i=0; i < bomb_count; i++) {
    int x = rnd() % N;
    int y = rnd() % N;
    if (stage[x][y] != State::BOMB) stage[x][y] = State::BOMB;
    else i--;
  }
  while(!game_finished) {
    show(N, stage);
    cout << "x y : ";
    char x_char;
    string y_char;
    cin >> x_char >> y_char;
    int x = x_char - 'a', y = stoi(y_char) - 1;
    open(N, &stage, x, y);
    if(opened == N * N - bomb_count) {
      cout << "clear!" << endl;
      game_finished = true;
    }
  }
}
