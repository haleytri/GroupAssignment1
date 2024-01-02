#include "ArgumentManager.h"
#include "header.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  // ifstream ifs("input1.txt");
  // ofstream ofs("output1.txt");
  ifstream ifs(input.c_str());
  ofstream ofs(output.c_str());

  LinkedList list;
  string data;

  while (getline(ifs, data)) {
    data.erase(remove(data.begin(), data.end(), '\n'), data.end());
    data.erase(remove(data.begin(), data.end(), '\r'), data.end());
    if (data != "Bar1" && data != "Bar2" && data != "") {
      decoder(data);

      node *temp = new node;
      temp->num = data;
      list.insertAtEnd(temp);
    }
  }

  cout << "\nPrint after decode:" << endl;
  list.print();
  list.sort();
  cout << "\n Print after sort:" << endl;
  list.print();
  list.idCheck(ofs);

  ifs.close();
  ofs.close();
  return 0;
}