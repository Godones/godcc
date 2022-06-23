int f(int a, int b) {
  return a + b;
}
void t() {
  return;
}
int main() {
  int res = f(1);
  res = f(1, t());
  return 0;
}