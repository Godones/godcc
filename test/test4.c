//
// Created by linfeng on 2022/4/4.
//

int x = 0;
int f() {
  int x[2][3];
  x[1][2] = 0;
  return 0;
}
void T(int a, int b) {
  return;
}
int main() {
  f();
  T(1, 2);
  return 0;
}