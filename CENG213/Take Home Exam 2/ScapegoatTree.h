#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod { preorder, inorder, postorder };

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T>& obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T& element);

    bool remove(const T& element);

    void removeAllNodes();

    const T& get(const T& element) const;

    void print(TraversalMethod tp = inorder) const;

    void printPretty() const;

    ScapegoatTree<T>& operator=(const ScapegoatTree<T>& rhs);

    void balance();

    const T& getCeiling(const T& element) const;

    const T& getFloor(const T& element) const;

    const T& getMin() const;

    const T& getMax() const;

    const T& getNext(const T& element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T>* node, TraversalMethod tp) const;
    void printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const;
    int getSize(Node<T>* node) const
    {
        if (node == NULL)
        {
            return 0;
        }
        return 1 + getSize(node->left) + getSize(node->right);
    }
    int getHeight(Node<T>* node) const
    {
        if (node == NULL)
        {
            return -1;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
    bool contains(Node<T>* node, const T& element) const
    {
        if (node == NULL)
        {
            return false;
        }
        if (node->element == element)
        {
            return true;
        }
        return contains(node->left, element) || contains(node->right, element);
    }

    const T& get(Node<T>* node, const T& element) const
    {
        if (!contains(node, element))
        {
            throw NoSuchItemException();
        }

        else
        {
            if (node == NULL)
            {
                std::cout << Node<T>().element;
                return Node<T>().element;
            }
            if (node->element == element)
            {
                return node->element;
            }
            else if (node->element > element)
            {
                return get(node->left, element);
            }
            else
            {
                return get(node->right, element);
            }
        }
    }
    void copy_helper(Node<T>*& copy_to, const Node<T>* copy_from) const
    {
        if (copy_from == NULL)
        {
            copy_to = NULL;
        }
        else
        {
            copy_to = new Node<T>;
            copy_to->element = copy_from->element;
            copy_helper(copy_to->left, copy_from->left);
            copy_helper(copy_to->right, copy_from->right);
        }
    }

    Node<T>* find_parent(Node<T>* r, const T& element)
    {
        if (r == NULL || r->element == element)
        {
            return NULL;
        }

        if ((r->left != NULL && r->left->element == element) || (r->right != NULL && r->right->element == element))
        {
            return r;
        }

        Node<T>* l = find_parent(r->left, element);

        if (l != NULL)
        {
            return l;
        }

        l = find_parent(r->right, element);
        return l;
    }
    Node<T>* find_scapegoat(T element)
    {
        while (true)
        {
            Node<T>* scape_goat_candidate = find_parent(root, element);
            int childSize;
            if (element > scape_goat_candidate->element)
                childSize = getSize(scape_goat_candidate->right);
            else if (element < scape_goat_candidate->element)
                childSize = getSize(scape_goat_candidate->left);
            element = scape_goat_candidate->element;
            int size = getSize(scape_goat_candidate);

            if (3 * childSize > 2 * size)
            {
                return scape_goat_candidate;
            }
        }
    }
    /*int getChildSize(Node<T>* node, const T& element) const
    {
        int size = 0;
        Node<T>* curr = node;
        while (curr)
        {
            if (curr->element > element)
                curr = curr->left;
            else if (curr->element < element)
                curr = curr->right;
            else
            {
                size++;
                break;
            }
            size++;
        }
        return size;
    }*/

    bool insert(Node<T>*& node, const T& element)
    {
        if (contains(root, element))
        {
            return false;
        }
        if (node == NULL)
        {
            node = new Node<T>(element, NULL, NULL);
            upperBound++;
        }
        else if (node->element > element)
        {
            insert(node->left, element);
        }
        else if (node->element < element)
        {
            insert(node->right, element);
        }
        else
            return false;

        int height = getHeight();
        if (pow(1.5, height) > upperBound)
        {
            Node<T>* scapegoat = find_scapegoat(element); // create find_scapegoat()
            Node<T>* parent = find_parent(root, scapegoat->element);

            if (parent->left == scapegoat)
            {
                Node<T>* balanced_tree = balance(scapegoat);
                parent->left = balanced_tree;
            }
            else if (parent->right == scapegoat)
            {
                Node<T>* balanced_tree = balance(scapegoat);
                parent->right = balanced_tree;
            }
        }
        return true;
    }
    Node<T>* balance(Node<T>*& node)
    {
        int size = getSize(node);
        Node<T>* arr = new Node<T>[size];
        convert_to_array(node, arr, 0);
        removeAllNodes(node);
        int end = size - 1;
        Node<T>* balanced_root = createBST(arr, 0, end);
        delete[] arr;
        return balanced_root;
    }

    Node<T>* createBST(Node<T>* arr, int start, int end)
    {
        if (start > end) return NULL;
        int mid = (start + end) / 2;
        Node<T>* r = new Node<T>(arr[mid].element, NULL, NULL);

        r->left = createBST(arr, start, mid - 1);
        r->right = createBST(arr, mid + 1, end);

        return r;

    }
    inline int convert_to_array(Node<T>* node, Node<T>* arr, int i)
    {
        if (node == NULL) return i;
        i = convert_to_array(node->left, arr, i);
        arr[i++] = *node;
        return convert_to_array(node->right, arr, i);
    }
    bool remove(Node<T>*& node, const T& element)
    {
        if (!contains(node, element))
            return false;
        else if (node->element > element)
            remove(node->left, element);
        else if (node->element < element)
            remove(node->right, element);
        else
        {
            if (node->left != NULL && node->right != NULL)
            {
                node->element = getMax(node->left);
                remove(node->left, node->element);
            }
            else
            {
                Node<T>* temp = node;
                node = (node->left != NULL) ? node->left : node->right;
                delete temp;
            }
        }

        int size = getSize();
        if (upperBound > 2 * size || size > upperBound)
        {
            balance();
            upperBound = size;
        }
        return true;

    }
    void removeAllNodes(Node<T>*& node)
    {
        if (node != NULL)
        {
            removeAllNodes(node->left);
            removeAllNodes(node->right);
            delete node;
            node = NULL;
        }
    }
    bool containsCeil(Node<T>* node, const T& element) const
    {
        if (node == NULL)
            return false;
        else if (node->element == element)
            return true;
        else if (node->element < element)
            return containsCeil(node->right, element);
        return true;
    }
    const T& getCeiling(Node<T>* node, const T& element) const
    {
        static T ceil;
        if (node == NULL)
            return ceil;
        if (node->element == element)
        {
            ceil = node->element;
            return ceil;
        }
        if (node->element < element)
            return getCeiling(node->right, element);
        if (node->element > element)
        {
            ceil = node->element;
            getCeiling(node->left, element);
        }
        return ceil;
    }
    bool containsFloor(Node<T>* node, const T& element) const
    {
        if (node == NULL)
            return false;
        else if (node->element == element)
            return true;
        else if (node->element > element)
            return containsFloor(node->left, element);
        return true;
    }
    const T& getFloor(Node<T>* node, const T& element) const
    {
        static T floor;
        if (node == NULL)
            return floor;
        if (node->element == element)
        {
            floor = node->element;
            return floor;
        }
        if (node->element > element)
            return getFloor(node->left, element);
        if (node->element < element)
        {
            floor = node->element;
            getFloor(node->right, element);
        }
        return floor;
    }
    Node<T>* containsNext(Node<T>* node, Node<T>* succ, const T& element) const
    {
        if (node == NULL)
            return succ;
        if (node->element == element)
        {
            if (node->right != NULL)
            {
                return getMinNode(node->right);
            }
        }
        else if (element < node->element)
        {
            succ = node;
            return containsNext(node->left, succ, element);
        } 
        else 
        {
            return containsNext(node->right, succ, element);
        }

        return succ;
    }
    const T& getNext(Node<T>* node, Node<T>* succ, const T& element) const
    {
        if (node == NULL) {
            return succ->element;
        }
        if (node->element == element)
        {
            if (node->right != NULL) {
                return getMin(node->right);
            }
        }
        else if (element < node->element)
        {
            succ = node;
            return getNext(node->left, succ, element);
        }

        else {
            return getNext(node->right, succ, element);
        }

        return succ->element;
    }
    const T& getMax(Node<T>* r) const
    {
        if (r == NULL)
            throw NoSuchItemException();
        Node<T>* curr = r;
        while (curr->right)
            curr = curr->right;
        return curr->element;
    }

    const T& getMin(Node<T>* r) const
    {
        if (r == NULL)
            throw NoSuchItemException();
        Node<T>* curr = r;
        while (curr->left)
            curr = curr->left;
        return curr->element;
    }
    Node<T>* getMinNode(Node<T>* r) const
    {
        if (r == NULL)
            throw NoSuchItemException();
        Node<T>* curr = r;
        while (curr->left)
            curr = curr->left;
        return curr;
    }

private: // DO NOT CHANGE THIS PART.
    Node<T>* root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T>& obj) {
    /* TODO */
    copy_helper(root, obj.root);
    upperBound = obj.upperBound;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    return root == NULL;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    return getHeight(root);
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    return getSize(root);
}

template<class T>
bool ScapegoatTree<T>::insert(const T& element)
{
    /* TODO */
    return insert(root, element);
}

template<class T>
bool ScapegoatTree<T>::remove(const T& element) {
    /* TODO */
    return remove(root, element);
}

template<class T>
void ScapegoatTree<T>::removeAllNodes()
{
    /* TODO */
    removeAllNodes(root);
    upperBound = 0;
}

template<class T>
const T& ScapegoatTree<T>::get(const T& element) const {
    /* TODO */
    return get(root, element);
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder)
    {
        /* TODO */
        if (isEmpty())
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == inorder)
    {
        // check if the tree is empty?
        if (isEmpty())
        {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == postorder)
    {
        /* TODO */
        if (isEmpty())
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T>* node, TraversalMethod tp) const {

    if (tp == preorder)
    {
        /* TODO */
        if (node == NULL)
            return;

        std::cout << "\t" << node->element;

        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);


        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    }
    else if (tp == inorder)
    {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == postorder)
    {
        /* TODO */
        if (node == NULL)
            return;
        print(node->left, postorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T>& ScapegoatTree<T>::operator=(const ScapegoatTree<T>& rhs) {
    /* TODO */
    if (this != &rhs)
    {
        this->removeAllNodes();
        copy_helper(this->root, rhs.root);
        upperBound = rhs.upperBound;
    }
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance()
{
    /* TODO */
    int size = getSize(root);
    Node<T>* arr = new Node<T>[size];
    convert_to_array(root, arr, 0);
    removeAllNodes(root);
    int end = size - 1;
    root = createBST(arr, 0, end);
    delete[] arr;
}

template<class T>
const T& ScapegoatTree<T>::getCeiling(const T& element) const
{
    /* TODO */
    if (!containsCeil(root, element))
        throw NoSuchItemException();
    return getCeiling(root, element);
}

template<class T>
const T& ScapegoatTree<T>::getFloor(const T& element) const {
    /* TODO */
    if (!containsFloor(root, element))
        throw NoSuchItemException();
    return getFloor(root, element);
}

template<class T>
const T& ScapegoatTree<T>::getMin() const
{
    /* TODO */
    if (isEmpty())
        throw NoSuchItemException();
    return getMin(root);
}

template<class T>
const T& ScapegoatTree<T>::getMax() const
{
    /* TODO */
    if (isEmpty())
        throw NoSuchItemException();
    return getMax(root);
}

template<class T>
const T& ScapegoatTree<T>::getNext(const T& element) const
{
    /* TODO */
    if (containsNext(root, NULL, element) == NULL)
        throw NoSuchItemException();
    return getNext(root, NULL, element);
}




