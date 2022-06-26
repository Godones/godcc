//
// Created by linfeng on 2022/5/24.
//

int main(int argc) {
  int a;
  int b = 2;
  int c = a + 2 + b;
  int d = a * 9 % b - 9;
  {//作用域嵌套
	int a = 1;
	{
	  int a = a;
	}
  }
  if (1) {//条件恒为真
	int c = 3;
  }
  int x;
  if (x > 4 && x < 5) {
	return 2;
  } else {
	int c = 3;
	c = 3 - 5;
  }
  if (x > 1) {
	if (x > 2) {
	  return 1;
	} else {
	  int t = 3;
	}
	int z = 5;
  }
  while (1) {//条件为真
	int a = 1;
  }
  while (x > 3) {
	int r = 2;
	if (x > 4) {
	  continue;
	  int c = 32;
	}
	break;
  }
  return 7;
}
int add(int a, int b) {
  return a + b;
}

void test(int c) {
  c = 4;
  int x = add(1, 2);
  add(add(1, 2), 3);
  return;
}

int adder(int a, int b) {

  test(a);
  test(3);
  return a + b;
}

void test_while() {
  int c = 2;
  while (c > 0) {
	c = c - 1;
  }
  return;
}
