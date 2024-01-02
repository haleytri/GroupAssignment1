#ifndef HEADER_H
#define HEADER_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct node {
  string num;
  node *next;
  bool isinnocent = true;
};

class LinkedList {
private:
  node *head;
  node *tail;

public:
  int size = 0;
  LinkedList() { head = nullptr; }
  node *getHead() { return head; }

  void sort() {
    if (head == nullptr || head->next == nullptr)
      return;
    bool isSorted = false;
    node *cur;

    while (!isSorted) {
      isSorted = true;
      cur = head;

      while (cur->next != nullptr) {
        int pre_num, next_num;
        stringstream s1, s2;
        s1 << cur->num;
        s1 >> pre_num;
        s2 << cur->next->num;
        s2 >> next_num;
        // cout<<"s1: "<<pre_num<<"  "<<"cur->num: "<<cur->num<<endl;
        if (pre_num > next_num) {
          // if (cur->num > cur->next->num) {
          node *temp = new node;
          temp->num = cur->num;

          cur->num = cur->next->num;

          cur->next->num = temp->num;

          isSorted = false;
        }
        cur = cur->next;
      }
    }
  }

  void idCheck(ofstream &out) // check for repeats
  {
    if (head == nullptr || head->next == nullptr)
      return;
    node *cur = head;
    node *tmp = head;

    string gui[20], inno[20];

    while (tmp != nullptr) {
      node *tmp_ = head;
      while (tmp_ != nullptr) {
        if ((tmp_->num == tmp->num) && (tmp_ != tmp)) {
          tmp->isinnocent = false;
          tmp_->isinnocent = false;
        }
        tmp_ = tmp_->next;
      }
      tmp = tmp->next;
    }

    // organize guilty numbers into array
    int k = 0;
    while (cur != nullptr) {
      if (cur->isinnocent == false) {
        int i = 0;
        for (; i < 20; i++) {
          if (gui[i] == cur->num)
            break;
        }
        if (i == 20) {
          gui[k] = cur->num;
          k++;
        }
      }
      cur = cur->next;
    }
    // print unrepeated guilty ones
    if (gui[0] != "") {
      out << "Guilty: " << endl;
      for (int i = 0; i < 20; i++) {
        if (gui[i] != "")
          out << gui[i] << endl;
      }
    }
    // organize innocent numbers into array
    int l = 0;
    cur = head;
    while (cur != nullptr) {
      if (cur->isinnocent == true) {
        int i = 0;
        for (; i < 20; i++) {
          if (inno[i] == cur->num)
            break;
        }
        if (i == 20) {
          inno[l] = cur->num;
          l++;
        }
      }
      cur = cur->next;
    }
    // print unrepeated innocent ones
    if (inno[0] != "") {
      out << "Innocent: " << endl;
      for (int i = 0; i < 20; i++) {
        if (inno[i] != "")
          out << inno[i] << endl;
      }
    }
  }
  void insertAtEnd(node *temp) {
    temp->next = nullptr;
    if (head == nullptr) {
      head = temp;
      size++;
      return;
    } else {
      node *cur = head;

      while (cur->next != nullptr) {
        cur = cur->next;
      }
      cur->next = temp;
      size++;
    }
  }

  void swap(char &a, char &b) {
    char c = a;
    a = b;
    b = c;
  }

  void print() {
    node *cur = head;
    while (cur != nullptr) {
      cout << cur->num << endl;
      cur = cur->next;
    }
  }
};

string decoder(string &str) {
  while (str.find(')') < str.size()) {
    int i = 0;
    while (str[i] != ')') {
      i++;
    }

    int j;
    for (j = str.size() - 1; j >= 0; j--) {
      if (str[j] == '(') {
        break;
      }
    }

    for (int k = j + 1, l = i - 1; k < l; k++, l--) {
      char temp = str[k];
      str[k] = str[l];
      str[l] = temp;
    }
    str.erase(i, 1);
    str.erase(j, 1);
  }
  return str;
}

#endif