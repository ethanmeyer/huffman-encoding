/*
 Filename: main.cpp
 Description: Program main
 Author: Ethan Meyer
 Date: 05/29/2019
 Course: Data Structures II
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "treenode.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::cerr;
using std::vector;
using std::endl;
using std::sort;
using std::cout;

struct FreqNode{
  char _character;
  int _freq;
};

struct EncodeNode{
  string _character;
  string _encode;
  int _freq;
};

bool CompareFreqNode(const FreqNode&, const FreqNode&);
int CharInVector(const char, const vector<FreqNode>&);
int FindSmallest(const vector<TreeNode*>&, size_t);
void PostOrder(const TreeNode*, vector<EncodeNode>&, string);
bool CompareEncodeNode(const EncodeNode&, const EncodeNode&);
string FindEncoding(const vector<EncodeNode>&, const string);

int main(int argc, char const *argv[]) {
  ifstream inputStream;
  ofstream outputStream;
  string command, inputFile, outputFile, encodedChar, code, carriagereturn, lf;
  char current;
  vector<FreqNode> frequencyTable;
  int position;
  TreeNode *first, *second;
  vector<EncodeNode> encode;

  command = argv[1];
  inputFile = argv[2];
  outputFile = argv[3];

  inputStream.open(inputFile);

  if(inputStream.fail()){
      cerr << "Your file " << inputFile << " could not be opened." << endl;
      return 1;
  }

  if(command == "-encode"){
  //Adds all the characters in the input stream to the frequency table
    while(true){
      if(!inputStream.get(current)){
        break;
      }
      int position = CharInVector(current, frequencyTable);
      if(position != -1){
        frequencyTable[position]._freq++;
      }else{
        FreqNode newNode;
        newNode._character = current;
        newNode._freq = 1;
        frequencyTable.push_back(newNode);
      }
    }

  //Sorts the frequency table
    sort(frequencyTable.begin(), frequencyTable.end(), CompareFreqNode);

  //Prepares vector to be the representation of my tree
    size_t huffmanSize = frequencyTable.size() * 2;

    vector<TreeNode*> huffman(huffmanSize);

    for (size_t i = 0; i < huffmanSize; i++) {
      huffman[i] = nullptr;
    }

    size_t occupied = 0;

  //Copies the leaves into the huffman tree from the frequency table
    for (size_t i = 0; i < frequencyTable.size(); i++) {
      string character;
      character += frequencyTable[i]._character;
      TreeNode* newNode = new TreeNode(character, frequencyTable[i]._freq, nullptr, nullptr, false);
      huffman[i] = newNode;
      occupied++;
    }

  //Makes all the new nodes of the leaves added together
    while(occupied != huffmanSize - 1){
      position = FindSmallest(huffman, occupied);
      first = huffman[position];
      position = FindSmallest(huffman, occupied);
      second = huffman[position];

      TreeNode* newNode = first->TreeNodeConcat(second);

      huffman[occupied] = newNode;
      occupied++;
    }

    TreeNode* root = huffman[0];

  //Finds the root by comparing the values held in TreeNode
    for (size_t i = 0; i < occupied; i++) {
      if(huffman[i]->GetValue() > root->GetValue()){
        root = huffman[i];
      }
    }

  //Recursivesly traverses the tree and makes the encoded table then sorts the tree
    PostOrder(root, encode, code);

    sort(encode.begin(), encode.end(), CompareEncodeNode);


  //Outputs the table of the tree
    carriagereturn += '\n';
    lf += '\r';

    for (size_t i = 0; i < encode.size(); i++) {
      if(encode[i]._character == carriagereturn){
        cout << "{key: CR, code: " << encode[i]._encode << "}" << endl;
      }else if(encode[i]._character == lf){
        cout << "{key: LF, code: " << encode[i]._encode << "}" << endl;
      }else{
        cout << "{key:  " << encode[i]._character << ", code: " << encode[i]._encode << "}" << endl;
      }
    }

  //Open the output file
    outputStream.open(outputFile);
    if(outputStream.fail()){
      cerr << "Your file " << inputFile << " could not be opened." << endl;
      return 1;
    }

  //Clears the End of File flag and starts at the beinging of the ifstream again
    inputStream.clear();
    inputStream.seekg(0);

    while(true){
      if(!inputStream.get(current)){
        break;
      }

      string key;
      key += current;

      encodedChar = FindEncoding(encode, key);
      outputStream << encodedChar;

    }

  //Closes istreams for the end of the program
    outputStream.close();
    inputStream.close();
  }
  return 0;
}

string FindEncoding(const vector<EncodeNode>& vect, const string key){
  for (size_t i = 0; i < vect.size(); i++) {
      if(vect[i]._character == key){
        return vect[i]._encode;
      }
  }
  return "";
}

void PostOrder(const TreeNode* tree, vector<EncodeNode>& encode, string code){
  if(tree == nullptr){
    return;
  }else if(tree->IsLeaf()){
    EncodeNode newNode;
    newNode._character = tree->GetChars();
    newNode._encode = code;
    newNode._freq = tree->GetValue();
    encode.push_back(newNode);
    return;
  }
  string temp = code;
  temp += "1";
  PostOrder(tree->GetLeft(), encode, temp);

  code += "0";
  PostOrder(tree->GetRight(), encode, code);
}

int FindSmallest(const vector<TreeNode*>& vect, size_t occupied){
  size_t position = -1;
  TreeNode* current;

  if(vect[0]->GetUsed()){
    for (size_t i = 0; i < occupied; i++) {
      if(!(vect[i]->GetUsed())){
        current = vect[i];
      }
    }
  }else{
    current = vect[0];
  }

  for (size_t i = 0; i < occupied; i++) {
    if((current->GetValue() >= vect[i]->GetValue()) && (!(vect[i]->GetUsed()))){
      current = vect[i];
      position = i;
    }
  }

  current->MakeUsed();
  return position;
}

bool CompareEncodeNode(const EncodeNode& a, const EncodeNode& b){
  if(a._freq  == b._freq )
    return a._character > b._character;

  return a._freq  > b._freq ;
}

bool CompareTreeNode(const TreeNode* a, const TreeNode* b){
  if(a->GetValue() == b->GetValue()){
    return a->GetValue() > b->GetValue();
  }
  return a->GetValue() > b->GetValue();
}

int CharInVector(const char character, const vector<FreqNode>& vect){
  for (size_t i = 0; i < vect.size(); i++) {
    if(character == vect[i]._character){
      return i;
    }
  }
  return -1;
}

bool CompareFreqNode(const FreqNode& a, const FreqNode& b){
  if(a._freq  == b._freq )
    return a._character > b._character;

  return a._freq  > b._freq ;
}
