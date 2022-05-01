//
// Created by linfeng on 2022/3/30.
// target: test tools lib
//
#include "log.h"
#include "dot.h"
#include "njson.hpp"


void dot_test(){

  GDot dot("test.dot");
  dot.BeganWrite("Function");
  dot.BeganWrite("Stmt");
  dot.BeganWrite("Stmt");
  dot.BeganWrite("Stmt");
  dot.EndWrite();
  dot.EndWrite();
  dot.EndWrite();
  dot.BeganWrite("Decl");
  dot.EndWrite();
  dot.EndWrite();
  dot.close();
  INFO("Dot test Ok");
}

void njson_test(){
//	nlohmann::json j;
//	j["x"] = 123;
//	j["y"] = {};
//	nlohmann::json &t = j["y"];
//	t["value"] = 12;
//	t["type"] ="int";
//	t["address"] = {};
//	nlohmann::json &x = t["address"];
//	x["line"] = 1;
//	x["col"] = {3,1};
//	std::cout << std::setw(4) << j << std::endl;

	std::stack<nlohmann::json *>jj;
	nlohmann::json * jjj = new nlohmann::json;
	jj.push(jjj);
	auto j = jj.top();
	(*j)["function"] = {};
	j = &(*j)["function"];
	(*j)["name"] = "test";
	(*j)["address"] = {{"line",1},{"col",2}};
	(*j)["paramlist"] = {};
	(*j)["returnType"] ="ss";
	(*j)["funcName"] = "sdasda";
	(*j)["paramList"] ={};
	jj.push(&(*j)["sssss"]);
	auto x = jj.top();
	(*x)["sdasdasdasd"][0] = {{"121","22"}};
	(*x)["sdasdasdasd"][1] = {{"121","22"}};

	nlohmann::json y = {{"key",1}};

	std::cout << std::setw(4) << *jjj << std::endl;
}


int main(){
  njson_test();
  dot_test();
  return 0;
}