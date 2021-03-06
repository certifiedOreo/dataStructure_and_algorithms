#include <iostream>
using namespace std;


 struct Node
        {
            int data;
            struct  Node* left;
            struct Node* right;

            Node(int val)
            {
                data = val;
                left = NULL;
                right = NULL;
            };
            
        };

        void preOrder(struct Node* root){

            if(root==NULL){
                return;
            }

            cout<<root->data<<" ";
            preOrder(root->left);
            preOrder(root->right);

        }

        

        void inOrder(struct Node* root){

            if(root==NULL){
                return;
            }

            inOrder(root->left);
            cout<<root->data<<" ";
            inOrder(root->right);

        }

        void postOrder(struct Node* root){
            if(root==NULL){
                return ;
            

            postOrder(root->left);
            postOrder(root->right);

            cout<<root->data<<" ";
        }
        }


        //BUILD BINARY TREE FROM WHEN PRE-ORDER AND INORDER OF THE TREE GIVEN
        //ALGORITHM!!
        //1 Pick element from preOrder & create a node
        //2 increment preOrder index
        //3 Search for the element's pos in InOrder say it pos
        //4 call to build left subtree from inOrder's 0 to pos-1index
        //5 Call to build right subtree from inOrder's pos+1 to n index
        //6 Return the node

        int searchInorder(int inOrder[], int start, int end, int curr){
            for(int i=start; i<=end; i++){
                if(inOrder[i]==curr){
                    return i;
                }
            }
            return -1;

        }


        Node* buildTree(int preOrder[], int inOrder[], int start, int end){

            static int idx = 0;   //element's index
            int curr = preOrder[idx];
            idx++;

            if(start>end){
                return NULL;
            }
            
            Node* node = new Node(curr);
            

            if(start==end){  //if there is only one element then simply return the node
                return node;
            }


            int pos = searchInorder(inOrder, start, end, curr);
            node->left = buildTree(preOrder, inOrder, start, pos-1);   //elements before pos in inOrder are the leftSubtree of curr element
            node->right = buildTree(preOrder, inOrder, pos+1, end);    //elements after pos in inOrder are the rightSubtree of curr element

            return node;
        }

        void inOrderPrint(struct Node* root){

            if(root==NULL){
                return ;
            }

            inOrderPrint(root->left);
            cout<<root->data<<" ";
            inOrderPrint(root->right);
        }

        //BUILD BINARY TREE  WHEN POST-ORDER AND INORDER OF THE TREE GIVEN
        //ALGORITHM!!
        //1 start from the end of postOrder & pick an element to create a node
        //2 decrement preOrder index
        //3 Search for the element's pos in InOrder say it pos
        //4 call to build right subtree from inOrder's pos+1 to n index
        //5 Call to build left subtree from inOrder's 0 to pos-1 index
        //6 Return the node

         Node* buildTree2(int postOrder[], int inOrder[], int start, int end){

            static int idx = 4;   //element's index
            int curr = postOrder[idx];
            idx--;

            if(start>end){
                return NULL;
            }
            
            Node* node = new Node(curr);
            

            if(start==end){  //if there is only one element then simply return the node
                return node;
            }


            int pos = searchInorder(inOrder, start, end, curr);
            node->right = buildTree(postOrder, inOrder, pos+1, end);   //elements before pos in inOrder are the leftSubtree of curr element
            node->left = buildTree(postOrder, inOrder, start, pos-1);    //elements before pos in inOrder are the leftSubtree of curr element

            return node;
        }

        int treeHeight(Node* root){
            if(NULL==root){
                return 0;
            }

            int lHeight = treeHeight(root->left);
            int rHeight = treeHeight(root->right);

            return max(lHeight, rHeight)+1;
        }


        /*
        DIAMETER-> Number of nodes in the longest path between any 2 leaves
        case 1: either diameter is through the root node
            then diameter = height(root->left)+ height(root->right)+1;

        case 2: or not through root node
            then diameter = max(diameter(root->left), diameter(root->right));
        
        final result is max of these two cases!

        COMPLEXITY = O(n^2)

        */

       int treeDiameter(Node* root){
           if(root==NULL){
               return 0;
           }

           int lHeight = treeHeight(root->left);
           int rHeight = treeHeight(root->right);
           int currDiameter = lHeight+rHeight+1;

           int lDiameter = treeDiameter(root->left);
           int rDiameter = treeDiameter(root->right);

           return max( currDiameter, max(lDiameter, rDiameter));
       }

       int optimisedTreeDiameter(Node* root, int* height){
           if(root==NULL){
               return 0;
           }

           int lH =0; int rH=0;

           int lDiameter = optimisedTreeDiameter(root->left, &lH);
           int rDiameter  = optimisedTreeDiameter(root->right, &rH);

           int currDiameter = lH+rH+1;
           *height = max(lH, rH)+1;

           return max(currDiameter, max(lDiameter, rDiameter));
       }


int main(){

    struct Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(3);

        root->left->left = new Node(4);
        root->left->right = new Node(5);
          root->right->left = new Node(6);
        root->right->right = new Node(7);
        preOrder(root);
        cout<<endl;
        inOrder(root);
          cout<<endl;
        postOrder(root);
        cout<<endl;

        
        //buildTree from inOrder and inOrder
        int preOrder[] = {1, 2, 4, 3, 5};
        int inOrder[] = {4, 2, 1, 5, 3};
        int postOrder[] = {4, 2, 5, 3, 1};

        Node* rootNode = buildTree(preOrder, inOrder, 0, 4);

        //inOrderPrint(rootNode);
        cout<<endl;

        Node* rootNode2 =  buildTree2(postOrder, inOrder, 0, 4);

        inOrderPrint(rootNode2);
        cout<<endl;
        cout<<treeHeight(root)<<endl;

        cout<<treeDiameter(root)<<endl;

        int height = 0;
        cout<<optimisedTreeDiameter(root, &height)<<endl;

        
        


 
    return 0;
}