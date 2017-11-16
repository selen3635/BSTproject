/*
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 4, 2016
 * File: BST.hpp
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

/*
 * Build a BST tree with adding BSTNode
 */
template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */ 
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */
   virtual ~BST() {
     deleteAll(root);
     root = nullptr;
     isize = 0;
     return;
   }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  For the reasoning
   *  behind this, see the assignment writeup.
   */
  virtual bool insert(const Data& item) {

    /* check whether tree is empty */
    if(root == 0 ) {

      root = new BSTNode<Data>(item);
      isize++;
      heightHelper(root);
      return true;      
    }
    else{

      BSTNode<Data>* curNode;
      curNode = root;

      /* a loop to compare item with curNode */
      while( curNode != nullptr) {
        /* case1: item < curNode */
        if( item < curNode->data ) {
          if( curNode->left == nullptr ) {
            curNode->left = new BSTNode<Data>(item);
            curNode->left->parent = curNode;
            ++isize;
            heightHelper(root);
            return true;
          }
          else {
            curNode = curNode->left;
          }
        }
        /* case 2: curNode < item */
        else if( curNode->data < item ) {
          if( curNode->right == nullptr ) {
            curNode->right = new BSTNode<Data>(item);
            curNode->right->parent = curNode;
            ++isize;
            heightHelper(root);
            return true;
          }
          else {
            curNode = curNode->right;
          }
        }
        /* case 3: curNode = item */
        else{

          return false;
        }

      }//end of while
      return false;
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const {

    /* construct a new node point to root */
    BSTNode<Data>* curNode;
    curNode = root;
    
    while(curNode != nullptr ) {

      /* case 1: item less than curNode */
      if( item < curNode->data ) {

        curNode = curNode->left;
      }
      /* case 2: item greater than curNode */
      else if( curNode->data < item ) {
        curNode = curNode->right;
      }
      /* they are equal */
      else
        return BSTIterator<Data>(curNode);

    }//end of while

    return end();

  }


  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
  
    return isize;
  }

  /** Return the height of the BST.
   */
  unsigned int height() const {

    return iheight;
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {

    if( isize == 0 ) {
      return true;
    }
    else
      return false;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ 
  iterator begin() const {

    return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy 
      way to get started.
   */
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if( n == nullptr ) return;
    inorder(n->left);
    std::cout << n->data<< endl;
    inorder(n->right);
  }

  /** Find the first element of the BST
   */
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */

    if(n == nullptr) return;
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
    n = 0;

  }

  /**
   * helper method for finding height of BST 
   */
  unsigned int heightHelper(BSTNode<Data>* myNode) {

    /* Base case */
    if ( myNode == nullptr )
      return -1;
    
    /* recursively call method to find height */
    unsigned int leftHeight = heightHelper(myNode->left) + 1;
    unsigned int rightHeight = heightHelper(myNode->right) + 1;

    /* determine which side is larger */
    if( leftHeight < rightHeight )
      return (iheight = rightHeight);
    else
      return (iheight = leftHeight);
  }


 };


#endif //BST_HPP
