//
// Created by linfeng on 2022/3/30.
//

#ifndef GODCC_JSON_JSON_H_
#define GODCC_JSON_JSON_H_
#include <iostream>
#include <fstream>

class GodJSon{
 private:
  std::fstream& file;
 public:
  GodJSon()=delete;
  GodJSon(std::fstream& file);

};
#endif//GODCC_JSON_JSON_H_
