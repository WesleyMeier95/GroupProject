#include "SplayTree.h"

using namespace std;

void SplayNode::printPreorder(ostream &os, string indent) const{
    if (this != NULL) {
	    os << indent << this->data << endl;
		this->left->printPreorder(os, indent + "  ");
		this->right->printPreorder(os, indent + "  ");
	}
	else
		os << indent << "NULL" << endl;
}

SplayNode* SplayTree::insertNode(int data, SplayNode* root){
   static SplayNode* p_node = NULL;
   if (!p_node)
       p_node = new SplayNode(data);
   else
       p_node->data = data;


   if (!root)
       root = p_node;
   else {
       root = splay(data, root);
       /* This is BST that, all data <= root->data is in root->left, all data >
       root->data is in root->right. */
       if (data < root->data)
       {
           p_node->left = root->left;
           p_node->right = root;
           root->left = NULL;
           root = p_node;
       }
       else if (data > root->data)
       {
           p_node->right = root->right;
           p_node->left = root;
           root->right = NULL;
           root = p_node;
       }
   }

   p_node = NULL;
   return root;
}

SplayNode* SplayTree::deleteNode(int data, SplayNode* root){
    SplayNode* temp;
    if (!root)
        return NULL;
    root = splay(data, root);
    if (data != root->data)
        return root;
    else
    {
       if (!root->left)
       {
           temp = root;
           root = root->right;
       }
       else
       {
           temp = root;
           /*Note: Since data == root->data,
           so after splay(data, root->left),
           the tree we get will have no right child tree.*/
           root = splay(data, root->left);
           root->right = temp->right;
       }
       //free(temp);
       return root;
    }
}

SplayNode* SplayTree::splay(int data, SplayNode* root){
    if (!root)
        return NULL;
    SplayNode header;
    /* header.right points to L tree;
    header.left points to R Tree */
    header.left = header.right = NULL;
    SplayNode* LeftTreeMax = &header;
    SplayNode* RightTreeMin = &header;
    while (1)
    {
       if (data < root->data)
       {
           if (!root->left)
               break;
           if (data < root->left->data)
           {
               root = RR_Rotate(root);
               // only zig-zig mode need to rotate once,
               if (!root->left)
                    break;
           }
           /* Link to R Tree */
           RightTreeMin->left = root;
           RightTreeMin = RightTreeMin->left;
           root = root->left;
           RightTreeMin->left = NULL;
           }
       else if (data > root->data)
       {
           if (!root->right)
               break;
           if (data > root->right->data)
           {
               root = LL_Rotate(root);
               // only zag-zag mode need to rotate once,
               if (!root->right)
                   break;
           }
           /* Link to L Tree */
           LeftTreeMax->right = root;
           LeftTreeMax = LeftTreeMax->right;
           root = root->right;
           LeftTreeMax->right = NULL;
       }
       else
           break;
    }
    /* assemble L Tree, Middle Tree and R tree */
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;
    root->left = header.right;
    root->right = header.left;
    return root;
}

SplayNode* SplayTree::LL_Rotate(){
    SplayNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    return k1;
}

SplayNode* SplayTree::RR_Rotate(){
    SplayNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    return k1;
}


