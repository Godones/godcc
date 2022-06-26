//
// Created by linfeng on 2022/6/26.
//

#include "register.h"


RegisterAllocator::RegisterAllocator() {
  //初始化寄存器分配器
  //临时寄存器包括x5-7 == t0-t2 x28-31 == t3-t6
  unused_reg.emplace(7);
  for(int i=0;i<3;i++) {
	unused_reg.emplace(5+i);
  }
  for(int i=0;i<4;i++) {
	unused_reg.emplace(28+i);
  }
}
void RegisterAllocator::add_param_reg(int params) {
  //参数寄存器x10-x17 == a0-a7
  //根据传入的参数个数，我们可以推断出剩余还有几个参数寄存器可用
  for(int i=params;i<8;i++) {
	unused_reg.emplace(10+i);
  }
}
