//
// Created by linfeng on 2022/6/26.
//

#include "register.h"

#include <random>

RegisterAllocator::RegisterAllocator() {
  //初始化寄存器分配器
  //临时寄存器包括$2-15
  for(int i=8;i<=15;i++){
	unusedReg.push_back(i);
	allReg.push_back(i);
  }
  unusedReg.push_back(3);allReg.push_back(3);
  unusedReg.push_back(6);allReg.push_back(6);
  unusedReg.push_back(7);allReg.push_back(7);
  unusedReg.push_back(24);allReg.push_back(24);
  unusedReg.push_back(25);allReg.push_back(25);
}

int RegisterAllocator::getReg(int virtualReg) {
  // 获取一个可用的寄存器
  if (virtualRegMap.find(virtualReg) != virtualRegMap.end()) {
	return virtualRegMap.at(virtualReg);
  }
  if (unusedReg.empty()) {
	ERROR("No available register");
	exit(-1);
  }
  int reg = unusedReg.front();
  virtualRegMap[virtualReg] = reg;
  unusedReg.pop_front();
//  INFO("Allocate register %d for virtual register %d", reg, virtualReg);
  return reg;
}
void RegisterAllocator::freeReg(int virtualReg) {
  // 释放虚拟寄存器对应的实际寄存器
  if (virtualRegMap.find(virtualReg) != virtualRegMap.end()) {
	int reg = virtualRegMap[virtualReg];
//	INFO("Free register %d for virtual register %d", reg, virtualReg);
	virtualRegMap.erase(virtualReg);
	unusedReg.push_back(reg);
  } else {
	ERROR("No register allocated for virtual register %d", virtualReg);
	exit(1);
  }
}
void RegisterAllocator::freeTempReg(int reg) {
  // 释放临时寄存器
  unusedReg.push_back(reg);
}
int RegisterAllocator::getTempReg() {
  // 获取一个可用的寄存器

  if (unusedReg.empty()) {
	ERROR("No available register");
	exit(-1);
  }
  int reg = unusedReg.front();
  unusedReg.pop_front();
//  INFO("Allocate register %d for temporary register", reg);
  return reg;
}
void RegisterAllocator::addVirtualReg(int virtualReg, int reg) {
  // 将虚拟寄存器和实际寄存器的映射加入到map中
  virtualRegMap[virtualReg] = reg;
}
std::vector<int> RegisterAllocator::getUsedReg() {
  std::vector<int>usedReg;
  std::sort(allReg.begin(), allReg.end());
  std::sort(unusedReg.begin(), unusedReg.end());
  std::set_difference(allReg.begin(), allReg.end(), unusedReg.begin(), unusedReg.end(), std::inserter(usedReg, usedReg.begin()));
  return usedReg;
}
