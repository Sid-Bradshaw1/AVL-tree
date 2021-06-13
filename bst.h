#ifndef BINARYSEARCHTREE_BSTDERIVED_H
#define BINARYSEARCHTREE_BSTDERIVED_H
#include "bstInterface.h"
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include "Queue.h"
#include "Deque.h"

using namespace std;
template<typename T>

class BST : public AVLInterface<T>
{
private:
    typedef struct Node
    {

        T data;
        Node* left;
        Node* right;
        int height;

        Node(T d) : data(d), left(NULL), right(NULL), height(1) {};
        ~Node() = default;

        friend ostream& operator<<(ostream& os, const struct Node& node)
        {
            os << node.data;
            return os;
        }
    };
    int sizeVar = 0;
    Node* root;




public:
    BST() { this->root = NULL; }
    ~BST() { clearTree(); }



    void rotateRight(Node* node)
    {
        if (node == NULL)
        {
            return;
        }

        Node* nodeRight = node->right;
        Node* nodeLeft = node->left;

        swap(node->data, nodeLeft->data);
        node->left = nodeLeft->left;
        node->right = nodeLeft;
        nodeLeft->left = nodeRight;
        swap(nodeLeft->right, nodeLeft->left);
        fixHeight(nodeLeft);
        fixHeight(node);
    }

    void rotateLeft(Node* node)
    {
        if (node == NULL)
        {
            return;
        }

        Node* nodeRight = node->right;
        Node* nodeLeft = node->left;

        swap(node->data, nodeRight->data);
        node->right = nodeRight->right;
        node->left = nodeRight;
        nodeRight->right = nodeLeft;
        swap(nodeRight->left, nodeRight->right);
        fixHeight(nodeRight);
        fixHeight(node);
    }

    bool balanceCheck(Node* node)
    {
        fixHeight(node);
        if (node == NULL)
        {
            return false;
        }
        int balance = getBalance(node);

        if (balance > 1 && (getBalance(node->right) != -1))
        {
            rotateLeft(node);
            return true;

        }

        if (balance < -1 && (getBalance(node->left) != 1))
        {
            rotateRight(node);
            return true;

        }

        if (balance > 1 && (getBalance(node->right) == -1))
        {
            rotateRight(node->right);
            rotateLeft(node);
            return true;


        }

        if (balance < -1 && (getBalance(node->left) == 1))
        {
            rotateLeft(node->left);
            rotateRight(node);
            return true;
        }

        else
        {
            return false;
        }
    }


    bool RecFind(Node*& node, const T& value)
    {
        if (node == NULL)
        {
            return false;
        }

        else if (value == node->data)
        {
            return true;
        }


        else if (value < node->data)
        {
            return RecFind(node->left, value);
        }

        else if (value > node->data)
        {
            return RecFind(node->right, value);
        }
    }


    bool RecInsert(Node*& node, const T& value)
    {
        //normal insertion cases
        if (node == NULL)
        {
            node = new Node(value);
            sizeVar++;
            return true;
        }
        fixHeight(node);

        if (value == node->data)
        {
            return false;
        }


        else if (value < node->data)
        {
            RecInsert(node->left, value);
            fixHeight(node);
        }

        else if (value > node->data)
        {
            RecInsert(node->right, value);
            fixHeight(node);
        }

        balanceCheck(node);

        fixHeight(node);
        return true;

    }


    /** Return true if node added to BST, else false */
    bool addNode(const T& value)
    {
        if (!RecFind(root, value))
        {
            return RecInsert(root, value);

        }

        else
        {
            return false;
        }


    }

    int max(int a, int b)
    {
        return (a > b)? a : b;
    }

    int getBalance(Node *node)
    {
        if (node == NULL)
            return -1;
        return height(node->right) - height(node->left);
    }

    size_t height(Node *node)
    {
        if (node == NULL)
            return 0;
        else
        {
            return node->height;
        }
    }

    void fixHeight(Node* node)
    {
        node->height = max(height(node->left), height(node->right)) + 1;
    }


    bool RecRemove(Node*& node, const T& value)
    {
        if (node == NULL) return false;
        fixHeight(node);
        if (value < node->data)
        {
            bool remover = RecRemove(node->left, value);
            balanceCheck(node);
            fixHeight(node);
            return remover;
        }
        if (value > node->data)
        {
            bool remover = RecRemove(node->right, value);
            balanceCheck(node);
            fixHeight(node);
            return remover;
        }

        // We found it!!!!!
        Node* oldNode = node;
        if (node->left == NULL) node = node->right;		// 1) only right (1 child or no child)
        else if (node->right == NULL) node = node->left;	// 2) only left

            // The node we want to delete has 2 children
        else
        {
            Node* predecessor = node->left;				// 3) 2 children
            while (predecessor->right != NULL) predecessor = predecessor->right;
            swap(node->data, predecessor->data);
            RecRemove(node->left, value);
            balanceCheck(node);
            fixHeight(node);
            return true;
        }
        delete oldNode;
        sizeVar--;
        return true;
    }

    /** Return true if node removed from BST, else false */
    bool removeNode(const T& value)
    {
        return RecRemove(root, value);

    }

    bool clear(Node*& node)
    {
        if (node != NULL)
        {
            clear(node->left);
            clear(node->right);
            delete node;
            sizeVar = 0;
        }

    }

    /** Return true if BST cleared of all nodes, else false */
    bool clearTree()
    {
        clear(root);
        root = NULL;

    }

    size_t sizeTree(void)
    {
        return sizeVar;
    }

    /** Return a level order traversal of a BST as a string */


    int GetTreeSize()
    {
        return sizeVar;
    }

    bool FinderFunc(const T& value)
    {
        if (RecFind(root, value))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void levelOrder()
    {
        if (root == NULL)  return;		// base Case
        Queue<Node*> q;					// create queue for level order traversal
        q.push(root);					// enque root (start)

        while (q.empty() == false)
        {

            Node* node = q.front();		// visit node
            q.pop();
            cout << " " << node->data;
            if (node->left != NULL)	q.push(node->left);
            if (node->right != NULL) q.push(node->right);
        }
        return;
    }

    bool outLevel(Node* node, int level, stringstream& out) const
    {
        if (node == NULL) return false;
        if (level == 1)
        {
            out << " " << node->data;
            if ((node->left != NULL) || (node->right != NULL)) return true;
            return false;
        }
        if ((level == 2) && !node->left && node->right) out << " _";
        bool left = outLevel(node->left, level - 1, out);
        bool right = outLevel(node->right, level - 1, out);
        if ((level == 2) && node->left && !node->right) out << " _";
        return left || right;
    } // end outLevel()

    string toString() const
    {
        stringstream out;
        if (root == NULL)
        {
            out << " empty";
        }
        else
        {
            int level = 0;
            do
            {
                out << endl << "  " << ++level << ":";
            } while (outLevel(root, level, out));
        }
        return out.str();
    }

    friend ostream& operator<< (ostream& os, BST<T>& bst)
    {
        os << bst.toString();
        return os;
    }




};

#endif //BINARYSEARCHTREE_BSTDERIVED_H
