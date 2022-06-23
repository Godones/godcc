//
// Created by linfeng on 2022/4/14.
//

int fibonacci(int n) {
  if (n < 2)
	return n;
  int f = 0, g = 1;
  int result = 0;
  int i = 0;
  while (i < n) {
	result = f + g;
	f = g;
	g = result;
  }
  return result;
}

int main(int argc, int x) {
  int a = 0x12;
  int res = fibonacci(a);
  _OUTPUT(res);
  if (2 > 3) {
	;
  } else {
	;
  }
  return 0;
}