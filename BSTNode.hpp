
/* Name: Ziying Hu & Xiaolong Zhou                                              
 * Login: cs100vat & cs100vcc
 * Date: Aug 4, 2016
 * File: BSTNode.hpp
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/*
 * BSTNode for a BST tree with pointer to left child, right child and 
 * parent with its data inside
 */
template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */
  BSTNode<Data>* successor() {

    /* case 1: X has right child */
    if( this->right != nullptr) {

      /* check whether right child have left child */
      if(this->right->left != nullptr ) {

        BSTNode<Data>* myNode;
        myNode = this->right->left;

        /* keep find left child */
        while( myNode->left != nullptr ) {

          myNode = myNode->left;

        }//end of while
        return myNode;
      }
      else
        return this->right;
    }//end of case 1

    /* case 2: X has no right child, and is left child of its parent */
    else if(this->right == nullptr && parent->left == this ) {

      return parent;

    }// end of case 2

    /* case 3: X has no right child, and is right child of its parent */
    else if( this->right == nullptr && parent->right == this) {

      BSTNode<Data>* myNode2;
      myNode2 = this->parent;

      /* check if it is root */
      while( myNode2->parent != nullptr){

        /* check if it is left child of its parent */
        if(myNode2 == myNode2->parent->left) {
          return myNode2->parent;
        }
        /* check if it is right child of its parent */
        else
          myNode2 = myNode2->parent;

      }//end of while
      return 0;
    }//end of case 3

    /* X has no right child, and has no parent */
    else {
      return 0;
    }

  }// end of successor

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
