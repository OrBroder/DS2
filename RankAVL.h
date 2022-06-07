#ifndef AVL_H
#define AVL_H
#include <memory>
#include "exceptions.h"
#include <iostream>
/********************************************************************************
*
*
                           Node class
*
*
********************************************************************************/
namespace Avl_lib{
template<class Data, class Key, class Val>
class Node
{
    /********************************************************************************
                                Node variables
    ********************************************************************************/
public:
    Data data;
    Key key;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> left;
    int height;
    int subCounter; // "rank sub tree"
    Val val;
    Val subValSum; // "sum sub tree"
    Val extra; // "sum tree"

    /********************************************************************************
                                Node constructors
    ********************************************************************************/
public:
    /**
     * @brief Constructor
     *
     * @param new_data Generic data held by node
     * @param new_next Next node
     */
    Node() = default;
    Node(const Data& new_data, const Key& new_key, const Val& new_val) : data(new_data), key(new_key), val(new_val), right(nullptr), left(nullptr), height(0), subCounter(1), subValSum(0), extra(0) {}
    //Node(const Data& new_data, const Key& new_key, std::shared_ptr<Node> parent) : data(new_data), key(new_key), right(nullptr), left(nullptr), height(0), subCounter(1), subValSum(0), Val(0), extra(0) {}
    Node(Node& other);
    ~Node() = default;
    /********************************************************************************
                        Node functions(public)
    ********************************************************************************/


    /********************************************************************************
                                Node operators
    ********************************************************************************/
    bool operator<(const Node& item) const;
    bool operator<(const Key& item) const;
};


template<class Data, class Key, class Val>
Node<Data, Key, Val>::Node(Node& other)
{
    data = other.data;
    key = other.key;
    right = nullptr;
    left = nullptr;
    height = 0;
    subCounter = other.subCounter;
    val = other.val;
    subValSum = other.subValSum;
    extra = other.extra;
}


template<class Data, class Key, class Val>
bool Node<Data, Key, Val>::operator<(const Node<Data, Key, Val>& item) const
{
    return this.key < item.key;
}

template<class Data, class Key, class Val>
bool Node<Data, Key, Val>::operator<(const Key& other_key) const
{
    return this->key < other_key;
}

/********************************************************************************
*
*
                           Tree class
*
*
********************************************************************************/

template<class Data, class Key, class Val>
class Tree
{
    /********************************************************************************
                                Tree variables
    ********************************************************************************/
public:
    std::shared_ptr<Node<Data, Key, Val>> root;
    //private:
    int size;

    /********************************************************************************
                                Tree constructors
    ********************************************************************************/
public:
    /**
     * @brief Default constructor
     *
     */
    Tree() :root(nullptr), size(0) {};
    /**
     * @brief Constructor
     *
     * @param new_data Generic data held by node
     * @param new_next Next node
     */
     /********************************************************************************
                         Tree functions(public)
     ********************************************************************************/
     /**
      * @brief Returns the tree's data size(amount)
      *
      */
    int getSize() const;

    /**
     * @brief Adds new info to the structure
     *
     * @param data The data to be stored
     * @param key The key to match the given data
     *
     */
    void insert(Data data, Key key, Val val);

    /**
     * @brief Removes data from the tree by given matching key
     *
     * @param key
     */
    void remove(Key key, Val val);

    /**
     * @brief Returns the minimal Node (by key)
     *
     * @param root
     * @return std::shared_ptr<Node<Data,Key>>
     */
    std::shared_ptr<Node<Data, Key, Val>> getMin(std::shared_ptr<Node<Data, Key, Val>> root);

    /**
     * @brief Returns the data by corresponding key
     *
     * @param key
     * @return Data&
     */
    Data& find(Key key);

    /**
     * @brief Returns the data placed in "m" index " if the nodes were in a sorted array "
     *
     * @param m
     * @return Data&
     */
    Key findDataByRank(int m) const;

    /**
     * @brief Returns the sum of all <= nodes values " if they were in a sorted array "
     *
     * @param key
     * @return Val&
     */
    Val getValSum(Key key) const;

    /**
     * @brief Returns the sum of all <= nodes values " if they were in a sorted array "
     *
     * @param key
     * @return Val&
     */
    Val getValSumByIndex(int m) const;

    /**
     * @brief Returns the index of the node " if the nodes were in a sorted array "
     *
     * @param key
     * @return int
     */
    int getRank(Key key) const;

    /**
     * @brief Merges another tree(of the same types) with the current(absorbs the other's data)
     *
     * @param other
     */
    void merge(Tree<Data, Key, Val> other);

    /**
     * @brief Merges another tree(of the same types) with the current(absorbs the other's data)
     *
     * @param current
     */
    void mergeHelper(std::shared_ptr <Node<Data, Key, Val>> current);

    /**
     * @brief Get the largest object's(by key) data
     *
     * @return Data
     */
    Data getHighest();

    /********************************************************************************
                         merge support functions
     ********************************************************************************/

    void storeInorder(Node<Data, Key, Val>* current, Node<Data, Key, Val>** arr, int* index_ptr);

    Node<Data, Key, Val>** mergeArrays(Node<Data, Key, Val>** arr1, Node<Data, Key, Val>** arr2, int n, int m);

    Node<Data, Key, Val>** treeToArray();

    Node<Data, Key, Val>* arrayToTree(Node<Data, Key, Val>**& arr, int start, int end);

    void inOrderUpdateSubValSum();

    Val& inOrderUpdateSubValSumHelper(std::shared_ptr <Node<Data, Key, Val>> current);

    void inOrderUpdateSubCounter();

    int inOrderUpdateSubCounterHelper(std::shared_ptr <Node<Data, Key, Val>> current);

    Val getValSumInArea(Key min, Key max) const;

    int getNumOfNodesInArea(Key min, Key max) const ;


    /********************************************************************************
                        Tree functions(private)
    ********************************************************************************/
private:
    /**
    * @brief Utility function. Adds new info to the structure.
    *
    * @param data The data to be stored
    * @param key The key to match the given data
    * @param root Root of the tree
    * @return std::shared_ptr<Node<Data,Key>> Returns the new root(might not stay the same based on rotations)
    */
    std::shared_ptr<Node<Data, Key, Val>> insertHelp(Data data, Key key, Val val, std::shared_ptr<Node<Data, Key, Val>> root);

    /**
     * @brief Utility function. Removes data from the tree by given matching key
     *
     * @param key
     * @param root Root of the tree
     * @return std::shared_ptr<Node<Data,Key>> Returns the new root(might not stay the same based on rotations)
     */
    std::shared_ptr<Node<Data, Key, Val>> removeHelp(Key key, std::shared_ptr<Node<Data, Key, Val>> root);

    /**
     * @brief Gets the max height of two given nodes.(null node's height set as -1, sole node set as 0)
     *
     * @param first
     * @param second
     * @return int
     */
    int getMaxHeight(std::shared_ptr<Node<Data, Key, Val>> first, std::shared_ptr<Node<Data, Key, Val>> second);

    /**
     * @brief Returns given node's balance factor
     *
     * @param node
     * @return int BF=(height(left) - height(right))
     */
    int getBalance(std::shared_ptr<Node<Data, Key, Val>> node);

    /**
     * @brief Preformes left rotation
     *
     * @param x given root
     * @return std::shared_ptr<Node<Data,Key>>
     */
    std::shared_ptr<Node<Data, Key, Val>> leftRotate(std::shared_ptr<Node<Data, Key, Val>> x);

    /**
     * @brief Preformes right rotation
     *
     * @param y given root
     * @return std::shared_ptr<Node<Data,Key>>
     */
    std::shared_ptr<Node<Data, Key, Val>> rightRotate(std::shared_ptr<Node<Data, Key, Val>> y);

    void reverseSubCounterDecrease(Key key, Val val);

    void reverseSubCounterIncrease(Key key, Val val);

};

/********************************************************************************
                    Tree functions implementations
********************************************************************************/
template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::getSize() const {
    return this->size;
}

/**
 * Algo method:
 * if the structure is empty, will set a new root as the given data+key
 * if not empty, send the data for insertion in the tree in root
 */

template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::insert(Data data, Key key, Val val)
{
    try {
        if (!root)
        {
            root = std::shared_ptr<Node<Data, Key, Val>>(new Node<Data, Key, Val>(data, key, val));
            root.get()->subValSum = val; // initialize the sum field
        }
        else
        {
            root = insertHelp(data, key, val, root);
        }
        size++;
    }
    catch (KeyExists& ex) {
        reverseSubCounterDecrease(key, val); // removes the additional subCounter added along the search path (key already exists)
        //throw KeyExists();
    }
}

/**
* Algo method:
* 1.binary search of key
* 2.sumCounter-=1 along the search path
*/
template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::reverseSubCounterDecrease(Key k, Val val) {
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    while (current.get()->key == k && current) {

        if (!current) { // key not found
            return;
        }
        current.get()->subCounter--;
        current.get()->subValSum -= val;


        if (current.get()->key > k) {
            current = current.get()->left;
        }
        else { // current->key < k
            current = current.get()->right;
        }
    }
}

/**
* Algo method:
* 1.binary search of key
* 2.sumCounter+=1 along the search path
*/
template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::reverseSubCounterIncrease(Key k, Val val) {
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    while (current.get()->key != k && current) {

        if (!current) { //key not found
            return;
        }
        current.get()->subCounter++;
        current.get()->subValSum += val;


        if (current.get()->key > k) {
            current = current.get()->left;
        }
        else { // current->key < k
            current = current.get()->right;
        }
    }
}


/**
* Algo method:
* 1.recursive insertion as in BST
* 2.update heights
* 3.check imbalance
* 4.rotate accordingly
*/
template<class Data, class Key, class Val>
std::shared_ptr<Node<Data, Key, Val>> Tree<Data, Key, Val>::insertHelp(Data data, Key key, Val val, std::shared_ptr<Node<Data, Key, Val>> current)
{
    if (current.get()->key < key)
    {
        current.get()->subCounter++;
        current.get()->subValSum += val;

        if (current.get()->right == nullptr)
        {
            current.get()->right = std::shared_ptr<Node<Data, Key, Val>>(new Node<Data, Key, Val>(data, key, val));
            (current.get()->right).get()->subValSum = val;
        }
        else
        {
            current.get()->right = insertHelp(data, key, val, current.get()->right);
        }
    }
    else if (current.get()->key > key)
    {
        current.get()->subCounter++;
        current.get()->subValSum += val;

        if (current.get()->left == nullptr)
        {
            current.get()->left = std::shared_ptr<Node<Data, Key, Val>>(new Node<Data, Key, Val>(data, key, val));
            (current.get()->left).get()->subValSum = val;
        }
        else
        {
            current.get()->left = insertHelp(data, key, val, current.get()->left);
        }
    }
    else
    {
        throw KeyExists();
    }

    current.get()->height = 1 + getMaxHeight(current.get()->right, current.get()->left);

    int balance = getBalance(current);
    int balanceR = getBalance(current.get()->right);
    int balanceL = getBalance(current.get()->left);

    //Left Left
    if (balance > 1 && balanceL >= 0)
        return rightRotate(current);

    // Right Right Case
    if (balance < -1 && balanceR <= 0)
        return leftRotate(current);

    // Left Right Case
    if (balance > 1 && balanceL < 0)
    {
        current.get()->left = leftRotate(current.get()->left);
        return rightRotate(current);
    }

    // Right Left Case
    if (balance < -1 && balanceR == 1)
    {
        current.get()->right = rightRotate(current.get()->right);
        return leftRotate(current);
    }

    return current;
}

/**
 *
 * Algo method:
 * if the structure is empty, no data to remove
 * if not empty, apply tree removale
 */
template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::remove(Key key, Val val)
{
    try {
        if (root == nullptr)
        {
            throw KeyNotFound();
        }
        else
        {
            reverseSubCounterDecrease(key, val);
            root = removeHelp(key, root);
        }
        size--;
    }
    catch (KeyNotFound& ex) {
        reverseSubCounterIncrease(key, val);
        throw KeyNotFound();
    }
}

/**
 * Algo method:
 * 1.recursive removale as in BST
 * 2.update heights
 * 3.check imbalance
 * 4.rotate accordingly
 */
template<class Data, class Key, class Val>
std::shared_ptr<Node<Data, Key, Val>> Tree<Data, Key, Val>::removeHelp(Key key, std::shared_ptr<Node<Data, Key, Val>> current)
{
    if (current.get()->key < key)
    {
        if (current.get()->right == nullptr)
        {
            throw KeyNotFound();

        }
        else
        {
            current.get()->right = removeHelp(key, current.get()->right);
        }
    }
    else if (current.get()->key > key)
    {
        if (current.get()->left == nullptr)
        {
            throw KeyNotFound();
        }
        else
        {
            current.get()->left = removeHelp(key, current.get()->left);
        }
    }
    else
    {
        if (current.get()->left == nullptr || current.get()->right == nullptr)
        {
            if (current.get()->left == nullptr)
            {
                if (current.get()->right == nullptr)
                {
                    return nullptr;
                }
                else
                {
                    return current.get()->right;
                }

            }
            else
            {
                return current.get()->left;
            }


        }
        else
        {
            std::shared_ptr<Node<Data, Key, Val>> min = getMin(current.get()->right);
            Data replaceData = min.get()->data;
            Key replaceKey = min.get()->key;
            std::shared_ptr<Node<Data, Key, Val>> res = removeHelp(replaceKey, current);
            current.get()->data = replaceData;
            current.get()->key = replaceKey;
            current.get()->height = 1 + getMaxHeight(current.get()->right, current.get()->left);
            return res;
        }
    }

    current.get()->height = 1 + getMaxHeight(current.get()->right, current.get()->left);

    int balance = getBalance(current);
    int balanceR = getBalance(current.get()->right);
    int balanceL = getBalance(current.get()->left);

    //Left Left
    if (balance > 1 && balanceL >= 0)
        return rightRotate(current);

    // Right Right Case
    if (balance < -1 && balanceR <= 0)
        return leftRotate(current);

    // Left Right Case
    if (balance > 1 && balanceL < 0)
    {
        current.get()->left = leftRotate(current.get()->left);
        return rightRotate(current);
    }

    // Right Left Case
    if (balance < -1 && balanceR == 1)
    {
        current.get()->right = rightRotate(current.get()->right);
        return leftRotate(current);
    }

    return current;
}

/**
 * Algo method:
 * null's(treated as empty trees) height defined as -1
 */
template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::getMaxHeight(std::shared_ptr<Node<Data, Key, Val>> first, std::shared_ptr<Node<Data, Key, Val>> second)
{
    int f, s;
    if (first == nullptr)
        f = -1;
    else
        f = first.get()->height;

    if (second == nullptr)
        s = -1;
    else
        s = second.get()->height;

    return f < s ? s : f;
}

template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::getBalance(std::shared_ptr<Node<Data, Key, Val>> node)
{
    int leftHeight, rightHeight;
    if (node == nullptr)
        return 0;
    if (node.get()->left == nullptr)
        leftHeight = -1;
    else
        leftHeight = node.get()->left->height;

    if (node.get()->right == nullptr)
        rightHeight = -1;
    else
        rightHeight = node.get()->right->height;

    return (leftHeight - rightHeight);
}

/**
 * Perform tree search.
 * method samiliar to BST
 */
template<class Data, class Key, class Val>
Data& Tree<Data, Key, Val>::find(Key key)
{
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    while (current != nullptr)
    {
        if (current.get()->key < key)
        {
            current = current.get()->right;
        }
        else if (current.get()->key > key)
        {
            current = current.get()->left;
        }
        else
        {
            return current.get()->data;
        }
    }
    throw KeyNotFound();
}

template<class Data, class Key, class Val>
Key Tree<Data, Key, Val>::findDataByRank(int m) const{
    int index = root.get()->subCounter;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    //std::shared_ptr<Node<Data, Key, Val>> parent = root;
    while (current != nullptr)
    {
        if (current.get()->right) { // right sub tree exists
            if ((index - (current.get()->right).get()->subCounter) > m) {
                if (!current.get()->left)
                    throw KeyNotFound();
                index += (current.get()->left).get()->subCounter - current.get()->subCounter;
                current = current.get()->left;
            }
            else if ((index - (current.get()->right).get()->subCounter) < m) {
                current = current.get()->right;
            }
            else { // == m
                return current.get()->key;
            }
        }
        else { // no right sub tree
            if (index > m) {
                if (!current.get()->left)
                    throw KeyNotFound();
                index += (current.get()->left).get()->subCounter - current.get()->subCounter;
                current = current.get()->left;
            }
            else { // == m
                return current.get()->key;
            }
        }
    }
    throw KeyNotFound();
}

template<class Data, class Key, class Val>
Val Tree<Data, Key, Val>::getValSum(Key key) const {
    int sum = root.get()->subValSum;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    //std::shared_ptr<Node<Data, Key, Val>> parent = root;
    while (current != nullptr)
    {
        if (current.get()->key > key) {
            sum += (current.get()->left).get()->subValSum - current.get()->subValSum;
            current = current.get()->left;
        }
        else if (current.get()->key < key) {
            current = current.get()->right;
        }
        else { // == key
            if (current.get()->right)
                return sum - (current.get()->right).get()->subValSum;
            else
                return sum;
        }
    }
    throw KeyNotFound();
}

template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::getRank(Key key) const {
    int index = root.get()->subCounter;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    //std::shared_ptr<Node<Data, Key, Val>> parent = root;
    while (current != nullptr)
    {
        if (current.get()->key > key) {
            index += (current.get()->left).get()->subCounter - current.get()->subCounter;
            current = current.get()->left;
        }
        else if (current.get()->key < key) {
            current = current.get()->right;
        }
        else { // == key
            if (current.get()->right)
                return index - (current.get()->right).get()->subCounter;
            else
                return index;
        }
    }
    throw KeyNotFound();
}

template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::merge(Tree<Data, Key, Val> other)
{

    int size1 = getSize();
    int size2 = other.getSize();

    Node<Data, Key, Val>** arr2 = other.treeToArray();
    Node<Data, Key, Val>** arr1 = treeToArray();
    Node<Data, Key, Val>** arr3 = mergeArrays(arr1, arr2, size1, size2);

    root.reset(arrayToTree(arr3, 0, size1 + size2 - 1));
    size = size1 + size2;

    // update the subCounters (ranks) and subValueSums of the new tree to be
    inOrderUpdateSubValSum();
    inOrderUpdateSubCounter();

    delete[] arr1;
    delete[] arr2;
    free(arr3);
}

template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::inOrderUpdateSubValSum() {
    if(root.get() != nullptr)
        inOrderUpdateSubValSumHelper(root);
}

template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::inOrderUpdateSubCounter() {
     if(root.get() != nullptr)
        inOrderUpdateSubCounterHelper(root);
}

template<class Data, class Key, class Val>
Val& Tree<Data, Key, Val>::inOrderUpdateSubValSumHelper(std::shared_ptr <Node<Data, Key, Val>> current) {

    if (current->right && current->left) {
        current.get()->subValSum = current.get()->val + inOrderUpdateSubValSumHelper(current->right) + inOrderUpdateSubValSumHelper(current->left);
    }
    else if (current->right) {
        current.get()->subValSum = current.get()->val + inOrderUpdateSubValSumHelper(current->right);
    }
    else if (current->left) {
        current.get()->subValSum = current.get()->val + inOrderUpdateSubValSumHelper(current->left);
    }
    else {
        current.get()->subValSum = current.get()->val;
    }
    return current.get()->subValSum;
}

template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::inOrderUpdateSubCounterHelper(std::shared_ptr <Node<Data, Key, Val>> current) {

    if (current->right && current->left) {
        current.get()->subCounter = 1 + inOrderUpdateSubCounterHelper(current->right) + inOrderUpdateSubCounterHelper(current->left);
    }
    else if (current->right) {
        current.get()->subCounter = 1 + inOrderUpdateSubCounterHelper(current->right);
    }
    else if (current->left) {
        current.get()->subCounter = 1 + inOrderUpdateSubCounterHelper(current->left);
    }
    else {
        current.get()->subCounter = 1;
    }
    return current.get()->subCounter;
}

template<class Data, class Key, class Val>
Data Tree<Data, Key, Val>::getHighest()
{
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    while (current != nullptr)
    {
        if (current.get()->right == nullptr)
            return current.get()->data;
        current = current.get()->right;
    }

    return nullptr;
}

template<class Data, class Key, class Val>
Node<Data, Key, Val>** Tree<Data, Key, Val>::mergeArrays(Node<Data, Key, Val>** arr1, Node<Data, Key, Val>** arr2, int n, int m)
{
    int mIndex = 0, nIndex = 0, mergedIndex = 0;
    int nodeSize = sizeof(Node<Data, Key, Val>*);
    Node<Data, Key, Val>** merged = static_cast<Node<Data, Key, Val>**>(malloc(nodeSize * (n + m)));
    while (mIndex < m && nIndex < n)
    {
        if ((arr1[nIndex])->key < arr2[mIndex]->key)
        {
            merged[mergedIndex] = arr1[nIndex];
            nIndex++;
        }
        else
        {
            merged[mergedIndex] = arr2[mIndex];
            mIndex++;
        }
        mergedIndex++;
    }

    while (mIndex < m)
    {
        merged[mergedIndex] = arr2[mIndex];
        mIndex++;
        mergedIndex++;
    }

    while (nIndex < n)
    {
        merged[mergedIndex] = arr1[nIndex];
        nIndex++;
        mergedIndex++;
    }

    return merged;

}

template<class Data, class Key, class Val>
Node<Data, Key, Val>** Tree<Data, Key, Val>::treeToArray()
{
    Node<Data, Key, Val>** array;
    int counter = 0;
    array = new Node<Data, Key, Val>*[size];
    storeInorder(root.get(), array, &counter);

    return array;
}
template<class Data, class Key, class Val>
void Tree<Data, Key, Val>::storeInorder(Node<Data, Key, Val>* current, Node<Data, Key, Val>** arr, int* index_ptr)
{
    if (current == nullptr)
        return;

    storeInorder(current->left.get(), arr, index_ptr);

    arr[*index_ptr] = current;
    (*index_ptr)++;

    storeInorder(current->right.get(), arr, index_ptr);
}

template<class Data, class Key, class Val>
Node<Data, Key, Val>* Tree<Data, Key, Val>::arrayToTree(Node<Data, Key, Val>**& arr, int start, int end)
{

    if (start > end)
        return NULL;

    int mid = (start + end) / 2;
    Node<Data, Key, Val>* root = new Node<Data, Key, Val>(*(arr[mid]));
    root->left = std::shared_ptr<Node<Data, Key, Val>>(arrayToTree(arr, start, mid - 1));
    root->right = std::shared_ptr<Node<Data, Key, Val>>(arrayToTree(arr, mid + 1, end));
    root->height = getMaxHeight(root->right, root->left) + 1;
    return root;
}




/********************************************************************************
                    AVL rotations
********************************************************************************/
/**
 * Algo method:
 * apply rotation
 * update heights
 * return new(or same) root
 */

template<class Data, class Key, class Val>
std::shared_ptr<Node<Data, Key, Val>> Tree<Data, Key, Val>::rightRotate(std::shared_ptr<Node<Data, Key, Val>> y)
{
    std::shared_ptr<Node<Data, Key, Val>> x = y.get()->left;
    std::shared_ptr<Node<Data, Key, Val>> T2 = x.get()->right;

    // Perform rotation
    x.get()->right = y;
    y.get()->left = T2;

    // Update heights
    y.get()->height = getMaxHeight(y.get()->right, y.get()->left) + 1;
    x.get()->height = getMaxHeight(x.get()->right, x.get()->left) + 1;

    // Update ranks
    if (T2 && y.get()->right) {
        y.get()->subCounter = 1 + (y.get()->right).get()->subCounter + T2.get()->subCounter;
    }
    else if (T2) {
        y.get()->subCounter = 1 + T2.get()->subCounter;
    }
    else if (y.get()->right) {
        y.get()->subCounter = 1 + (y.get()->right).get()->subCounter;
    }
    else { // y is a leaf
        y.get()->subCounter = 1;
    }

    if (x.get()->left && y) {
        x.get()->subCounter = 1 + (x.get()->right).get()->subCounter + (x.get()->left).get()->subCounter;
    }
    else if (x.get()->left) {
        x.get()->subCounter = 1 + (x.get()->left).get()->subCounter;
    }
    else if (y) {
        x.get()->subCounter = 1 + (x.get()->right).get()->subCounter;
    }
    else { // x is a leaf
        x.get()->subCounter = 1;
    }

    //update sums
    Val temp = y.get()->subValSum;

    if (y.get()->left) {
        y.get()->subValSum += (y.get()->left).get()->subValSum - x.get()->subValSum;
    }
    else { // y is a leaf
        y.get()->subValSum -= x.get()->subValSum;
    }

    x.get()->subValSum = temp;

    // Return new root
    return x;
}

template<class Data, class Key, class Val>
std::shared_ptr<Node<Data, Key, Val>> Tree<Data, Key, Val>::leftRotate(std::shared_ptr<Node<Data, Key, Val>> x)
{
    std::shared_ptr<Node<Data, Key, Val>>y = x.get()->right;
    std::shared_ptr<Node<Data, Key, Val>>T2 = y.get()->left;

    // Perform rotation
    y.get()->left = x;
    x.get()->right = T2;

    // Update heights
    x.get()->height = getMaxHeight(x.get()->right, x.get()->left) + 1;
    y.get()->height = getMaxHeight(y.get()->right, y.get()->left) + 1;

    if (T2 && x.get()->left) {
        x.get()->subCounter = 1 + (x.get()->left).get()->subCounter + T2.get()->subCounter;
    }
    else if (T2) {
        x.get()->subCounter = 1 + T2.get()->subCounter;
    }
    else if (x.get()->left) {
        x.get()->subCounter = 1 + (x.get()->left).get()->subCounter;
    }
    else { // x is a leaf
        x.get()->subCounter = 1;
    }

    if (y.get()->right && x) {
        y.get()->subCounter = 1 + (y.get()->right).get()->subCounter + (y.get()->left).get()->subCounter;
    }
    else if (x) {
        y.get()->subCounter = 1 + (y.get()->left).get()->subCounter;
    }
    else if (y.get()->right) {
        y.get()->subCounter = 1 + (y.get()->right).get()->subCounter;
    }
    else { // y is a leaf
        y.get()->subCounter = 1;
    }

    //update sums
    Val temp = x.get()->subValSum;

    if (x.get()->right) {
        x.get()->subValSum += (x.get()->right).get()->subValSum - y.get()->subValSum;
    }
    else { // y is a leaf
        x.get()->subValSum -= y.get()->subValSum;
    }

    y.get()->subValSum = temp;

    // Return new root
    return y;
}

template<class Data, class Key, class Val>
std::shared_ptr<Node<Data, Key, Val>> Tree<Data, Key, Val>::getMin(std::shared_ptr<Node<Data, Key, Val>> root)
{
    // std::shared_ptr<Node<Data,Key>> current = root.get()->left;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    if (current == nullptr)
        return nullptr;
    while (current.get()->left != nullptr)
    {
        current = current.get()->left;
    }

    return current;
}

template<class Data, class Key, class Val>
Val Tree<Data, Key, Val>::getValSumByIndex(int m) const {
    return getValSum(findDataByRank(m));
}

template<class Data, class Key, class Val>
Val Tree<Data, Key, Val>::getValSumInArea(Key min, Key max) const {
    Val highSum, lowSum, lowVal;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    if (!root)
        return 0;
    while (current != nullptr) { // finding lowSum & lowVal
        if (current.get()->key >= min) { // go left
            lowSum = getValSum(current.get()->key);
            lowVal = current.get()->val;
            if (current.get()->left)
                current = current.get()->left;
            else
                break;
        }
        else { // go right
            if (current.get()->right) {
                current = current.get()->right;
            }
            else
                break;
        }
    }
    current = root;
    while (current != nullptr) { // finding highSum
        if (current.get()->key <= max) { // go right
            highSum = getValSum(current.get()->key);
            if (current.get()->right)
                current = current.get()->right;
            else
                break;
        }
        else { // go left
            if (current.get()->left) {
                current = current.get()->left;
            }
            else
                break;
        }
    }
    return highSum - lowSum + lowVal;
}

template<class Data, class Key, class Val>
int Tree<Data, Key, Val>::getNumOfNodesInArea(Key min, Key max) const {
    int highCounter, lowCounter;
    std::shared_ptr<Node<Data, Key, Val>> current = root;
    if (!root)
        return 0;
    while (current != nullptr) { // finding lowCounter
        if (current.get()->key >= min) { // go left
            lowCounter = getRank(current.get()->key);
            if (current.get()->left)
                current = current.get()->left;
            else
                break;
        }
        else { // go right
            if (current.get()->right) {
                current = current.get()->right;
            }
            else
                break;
        }
    }
    current = root;
    while (current != nullptr) { // finding highCounter
        if (current.get()->key <= max) { // go right
            highCounter = getRank(current.get()->key);
            if (current.get()->right)
                current = current.get()->right;
            else
                break;
        }
        else { // go left
            if (current.get()->left) {
                current = current.get()->left;
            }
            else
                break;
        }
    }
    return highCounter - lowCounter + 1;
}

}
#endif