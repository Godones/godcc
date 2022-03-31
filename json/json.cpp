//
// Created by linfeng on 2022/3/30.
//

#include "json.h"


GodJSon::GodJSon(): GodJSon("test.json") {}
GodJSon::GodJSon(const char *file_name) {
	file.open(file_name);
	if (!file.is_open()) {
		std::cout << "open file error\n";
		return;
	}
}
void GodJSon::BeganWrite(const std::string_view&dot_name) {
  if (state==1) {
	file << ",";
	state = 0;
  }
  file << "{\n";
  file << R"("name": )" <<"\""<< dot_name << "\",\n";
  file << R"("children": )"<<"[";
}
void GodJSon::EndWrite(){
  state = 1;
  file << "]\n}\n";
}
void GodJSon::close() {
	file.close();
}
