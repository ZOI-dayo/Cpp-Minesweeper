#include <bits/stdc++.h>
using namespace std;
enum class State {
  DEFAULT,
  OPENED,
  BOMB,
};
void show(int N, vector<vector<State>> stage) {
  cout << "  ";
  for(int x=0; x<N; x++) cout << x+1 << " ";
  cout << endl;

  for(int x=0; x<N; x++) {
    cout << (char)('a' + x) << " ";
    for(int y=0; y<N; y++) {
      if(stage[x][y] == State::DEFAULT) cout << "- ";
      else if(stage[x][y] == State::OPENED) cout << "  ";
      else cout << "x ";
    }
    cout << endl;
  }
}
void open(int N, vector<vector<State>> *stage, int x, int y) {
  if((*stage)[x][y] == State::DEFAULT) (*stage)[x][y] = State::OPENED;
  else if((*stage)[x][y] == State::OPENED) cout << "opened" << endl;
  else cout << "game over" << endl;
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
  show(N, stage);
  open(N, &stage, 2, 2);
  show(N, stage);
}
