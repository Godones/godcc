//
// Created by linfeng on 2022/3/30.
//

#include "json.h"


GodJSon::GodJSon(): GodJSon("test.json") {}
GodJSon::GodJSon(const char *file_name) {
 file = fopen(file_name,"w");
 if (!file){
   printf("open file error\n");
   exit(1);
 }
}
void GodJSon::BeganWrite(const char * dot_name,...) {
  if (state==1) {
	fprintf(file,",");
	state = 0;
  }
  fprintf(file,"{\n \"name\": \"");
  va_list args;
  va_start(args, dot_name);
  fprintf(file,dot_name, args);
  va_end(args);
  fprintf(file,"\",\n");
  fprintf(file,"\"children\": [\n");
}
void GodJSon::EndWrite(){
  state = 1;
  fprintf(file,"]\n}\n");
}
void GodJSon::close() {
	fclose(file);
}

