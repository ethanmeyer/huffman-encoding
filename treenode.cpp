/*
 Filename: treenode.cpp
 Description: Declaration of the class TreeNode methods
 Author: Ethan Meyer
 Date: 05/29/2019
 Course: Data Structures II
*/
#include "treenode.h"
#include <string>
#include <cstring>
#include <sstream>

using std::stringstream;

TreeNode::TreeNode(const string chars, const size_t num, TreeNode* left, TreeNode* right, bool used){
  _characters = chars;
  _value = num;
  _left = left;
  _right = right;
  _used = used;
}

TreeNode::~TreeNode(){

}

TreeNode* TreeNode::GetLeft()const{
  return _left;
}

TreeNode* TreeNode::GetRight()const{
  return _right;
}

bool TreeNode::IsLeaf()const{
  return (_left == nullptr) && (_right == nullptr);
}

TreeNode* TreeNode::TreeNodeConcat(TreeNode* b){
  string newChars = _characters + b->_characters;
  size_t newValue = _value + b->_value;

  TreeNode* newNode = new TreeNode(newChars, newValue, this, b, false);
  return newNode;
}

string TreeNode::ToString()const{
  stringstream ss;
  ss << "{" << _characters << ", " << _value << ", " << _left << ", " << _right << " }";
  return ss.str();
}

int TreeNode::GetValue()const{
  return _value;
}

string TreeNode::GetChars()const{
  return _characters;
}

void TreeNode::MakeUsed(){
  _used = true;
}

bool TreeNode::GetUsed(){
  return _used;
}
