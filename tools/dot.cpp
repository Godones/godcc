//
// Created by linfeng on 2022/4/11.
//

#include "dot.h"
GDot::GDot() : GDot("code.dot") {}
GDot::GDot(const char *file_name) {
  file = fopen(file_name, "w");
  if (!file) {
	printf("open file error\n");
	exit(1);
  }
  fprintf(file, "digraph first2{\nnode[shape=box];\n");
}
void GDot::BeganWrite(const char *fmt) {
  // 定义节点
  fprintf(file, "node%d[label=\"%s\"];\n", node_id, fmt);
  if (!id_stack.empty()) {
	//如果栈不空，则连接
	int father_id = id_stack.top();
	fprintf(file, "node%d->node%d;\n", father_id, node_id);
  }
  id_stack.push(node_id);//把当前节点名字压入栈
  node_id++;
}
void GDot::close() {
  fprintf(file, "}");
  fclose(file);
}
void GDot::EndWrite() {
  assert(!id_stack.empty());
  id_stack.pop();
}
