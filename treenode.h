/*
 Filename: treenode.h
 Description: Declaration of the class TreeNode to represent an element with a character and number of those characters
 Author: Ethan Meyer
 Date: 05/29/2019
 Course: Data Structures II
*/
#ifndef TREENODE_H
#define TREENODE_H

#include <string>
using std::string;

class TreeNode{
  string _characters;
  size_t _value;
  TreeNode* _left;
  TreeNode* _right;
  bool _used;
public:
  TreeNode();
  TreeNode(const string, const size_t, TreeNode*, TreeNode*, bool);
  ~TreeNode();
  string ToString()const;
  int GetValue()const;
  string GetChars()const;
  void MakeUsed();
  bool GetUsed();
  TreeNode* TreeNodeConcat(TreeNode*);
  TreeNode* GetLeft()const;
  TreeNode* GetRight()const;
  bool IsLeaf()const;
};

#endif
