 #ifndef HASH_H
 #define HASH_H
 #include <memory>
 #include <iostream>
 #include <list>
 #include "Primes.h"
 #include "exceptions.h"
 namespace Hash_lib{

 
 /********************************************************************************
 *  
 * 
                            Node class
 *
 *                             
********************************************************************************/
 template<class Data>
    class Node
    {
// unique case where node has to be int tagged for simplicity reasons as the other case would require
// Hash to use a decipher for converting keys to indexes matching the structure's array
/********************************************************************************
                            Node variables
********************************************************************************/
        public:
        Data data;
        int key;
        std::shared_ptr<Node> next;
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
        Node(const Data& new_data,int new_key): data(new_data),key(new_key),next(nullptr){}
        Node(const Data& new_data,int new_key,std::shared_ptr<Node> next): data(new_data),key(new_key),next(nullptr){}
        ~Node() = default;
/********************************************************************************
                    Node functions(public)
********************************************************************************/


/********************************************************************************
                            Node operators
********************************************************************************/
        bool operator<(const Node& item) const;
        bool operator<(int item) const;
    };


    template<class Data>
    bool Node<Data>::operator<(const Node<Data>& item) const
    {
        return this.key < item.key;
    }

    template<class Data>
    bool Node<Data>::operator<(int other_key) const
    {
        return this->key < other_key;
    }

 /********************************************************************************
 *  
 * 
                            Hash class
 *
 *                             
********************************************************************************/

    template<class Data>
    class Hash
    {
/********************************************************************************
                            Hash variables
********************************************************************************/
        private:
        std::shared_ptr<Node<Data>> *ptrArray;
        int capacity;
        int size;
        int primeIterator;
        
/********************************************************************************
                            Hash constructors
********************************************************************************/
        public:
        /**
         * @brief Default constructor
         * 
         */
        Hash(){
            primeIterator = 0;
            capacity = PRIMES[primeIterator];
            ptrArray = new std::shared_ptr<Node<Data>>[capacity]();
            size = 0;
            
        };
/********************************************************************************
                    Hash functions(public)
********************************************************************************/
        /**
         *@brief inserts a new singleton taged by i as key, carrying data.!note implementation does not support overriding existing key 

         */
        void insert(int key,Data data);
        void remove(int key);
        Data& find(int key);
        bool exists(int key);
        void printNullIndexes();
        void printGroup(int i);
        template<class Operation>
        void inOrderHelper(Operation func,int root);
        template<class Operation>
        void inOrder(Operation func,Node<Data>* root);
        template<class Operation,class Var>
        void inOrderHelper(Operation func,Var var,int root);
        template<class Operation,class Var>
        void inOrder(Operation func,Var var,Node<Data>* root);
        void expand();
        void shrink();
        void printCell(int cell);
        void dump(std::shared_ptr<Node<Data>>& root,std::shared_ptr<Node<Data>> *newArray, int newCapacity);
        void merge(Hash<Data>& other);
        int getSize();


    };
    template<class Data>
    void  Hash<Data>::insert(int key ,Data data)
    {
        if(exists(key))
            throw KeyExists();

       if(!(size < capacity))
            expand();

        int cell = key%capacity;
        std::shared_ptr<Node<Data>> root = ptrArray[cell];
        if(root == nullptr)
        {
             std::shared_ptr<Node<Data>> new_node = std::make_shared<Node<Data>>(data,key);
            ptrArray[cell] = new_node;
        }
            
        else
        {
            std::shared_ptr<Node<Data>> new_node = std::make_shared<Node<Data>>(data,key);
            new_node.get()->next = root;
            ptrArray[cell] = new_node;
        }     
        size ++;        
    }

    template<class Data>
    void  Hash<Data>::remove(int key)
    {
      

        int cell = key%capacity;
        std::shared_ptr<Node<Data>> root = ptrArray[cell];
        std::shared_ptr<Node<Data>> previous = nullptr;
        while(root != nullptr)
        {
            if(root.get()->key == key)
            {
                if(previous == nullptr)
                    ptrArray[cell] = root.get()-> next;
                else 
                {
                    previous.get()->next = root.get()-> next;
                }
                size --; 
                if((size < PRIMES[primeIterator-1] && capacity > 5))
                    shrink();
                return;
            }
                 root = root.get()->next;  
        }
        
               
    }

    template<class Data>
    void Hash<Data>::printNullIndexes()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            if(ptrArray[i] == nullptr)
                std::cout << i << " is empty" << std::endl;
        }
        
    }

    template<class Data>
    template<class Operation>
    void Hash<Data>::inOrderHelper(Operation func,int root)
    {
       if(ptrArray[root] != nullptr)
            inOrderHelper(func,ptrArray[root].get());
    }

    template<class Data>
    template<class Operation>
    void Hash<Data>::inOrder(Operation func,Node<Data>* root)
    {
        func(root->data);
        if(root->next != nullptr)
        inOrderHelper(func,root->next);
    }

    template<class Data>
    template<class Operation,class Var>
    void Hash<Data>::inOrderHelper(Operation func,Var var,int root)
    {
       if(ptrArray[root] != nullptr)
            inOrder(func,var,ptrArray[root].get());
    }

    template<class Data>
    template<class Operation,class Var>
    void Hash<Data>::inOrder(Operation func,Var var,Node<Data>* root)
    {
        func(root->data,var);
        if(root->next != nullptr)
        inOrder(func,var,root->next);
    }

    template<class Data>
    void Hash<Data>::expand()
    {
        int newCapacity = PRIMES[primeIterator + 1];
        std::shared_ptr<Node<Data>> *newArray = new std::shared_ptr<Node<Data>>[newCapacity];
        for (size_t i = 0; i < capacity; i++)
        {
            dump(ptrArray[i],newArray,newCapacity);
        }
       // delete(ptrArray);
        ptrArray = newArray;
        primeIterator++;
        capacity = newCapacity;
        
    }

    template<class Data>
    void Hash<Data>::shrink()
    {
        int newCapacity = PRIMES[primeIterator - 1];
        std::shared_ptr<Node<Data>> *newArray = new std::shared_ptr<Node<Data>>[newCapacity];
        for (size_t i = 0; i < capacity; i++)
        {
            dump(ptrArray[i],newArray,newCapacity);
        }
       // delete(ptrArray);
        ptrArray = newArray;
        primeIterator--;
        capacity = newCapacity;
        
    }

    template<class Data>
    void Hash<Data>::printCell(int cell)
    {
        std::shared_ptr<Node<Data>> current = ptrArray[cell];
        while(current != nullptr)
        {
            std::cout << current.get()->key << " ";
            current = current.get()->next;
        }
        std::cout <<std::endl;
    }

    template<class Data>
    void Hash<Data>::dump(std::shared_ptr<Node<Data>>& root ,std::shared_ptr<Node<Data>> *newArray, int newCapacity)
    {
        while(root != nullptr)
        {
            int current_key = (root).get()->key;
            Data data = (root).get()->data;
             int cell = (root).get()->key % newCapacity;
             std::shared_ptr<Node<Data>> new_root = newArray[cell];
             if(new_root == nullptr)
                 newArray[cell] = std::make_shared<Node<Data>>(data,current_key);
             else
            {
                std::shared_ptr<Node<Data>> new_node = std::make_shared<Node<Data>>(data,current_key);
                new_node.get()->next = new_root;
                newArray[cell] = new_node;
            }    
            root = (root).get()->next; 
        }

    }

    template<class Data>
    Data& Hash<Data>::find(int key)
    {
        int cell = key%capacity;
        std::shared_ptr<Node<Data>> root = ptrArray[cell];
        while(root != nullptr)
        {
            if(root.get()->key == key)
                return root.get()->data;
            root = root.get()->next;
        }

        throw KeyNotFound();

    }

    template<class Data>
    void Hash<Data>::merge(Hash<Data>& other)
    {
        std::shared_ptr<Node<Data>> current;
        int otherSize = other.capacity;
        int newCell;
        for (size_t i = 0; i < otherSize; i++)
        {
            current = other.ptrArray[i];
            while(current != nullptr)
            {
                insert(current.get()->key,current.get()->data);
                current = current.get()->next;
            }
                
        }
    }
    template<class Data>
    bool Hash<Data>::exists(int key)
    {
         int cell = key%capacity;
        std::shared_ptr<Node<Data>> root = ptrArray[cell];
        while(root != nullptr)
        {
            if(root.get()->key == key)
                return true;
            root = root.get()->next;
        }

        return false;
    }

    template<class Data>
    int Hash<Data>::getSize()
    {
        return size;
    }
 }
#endif