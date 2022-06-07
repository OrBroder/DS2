 #ifndef UNION_H
 #define UNION_H
 #include <memory>
 #include <iostream>
 #include <list>
 #include "exceptions.h"
 namespace Union_lib
 {

 
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
// union to use a decipher for converting keys to indexes matching the structure's array
/********************************************************************************
                            Node variables
********************************************************************************/
        public:
        Data data;
        int key;
        Node* next;
        Node* head;
        int counter;
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
        Node(const Data& new_data,int new_key): data(new_data),key(new_key),next(nullptr),head(nullptr){
            counter = 1;
        }
        Node(const Data& new_data,int new_key,std::shared_ptr<Node> next,std::shared_ptr<Node> head): data(new_data),key(new_key),next(nullptr),head(nullptr){
            counter = 1;
        }
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
                            Union class
 *
 *                             
********************************************************************************/

    template<class Data>
    class Union
    {
/********************************************************************************
                            Union variables
********************************************************************************/
        private:
        std::shared_ptr<Node<Data>> *ptrArray;
        const int capacity;
        
/********************************************************************************
                            Union constructors
********************************************************************************/
        public:
        /**
         * @brief Default constructor
         * 
         */
        Union(int capacity):capacity(capacity){
            ptrArray = new std::shared_ptr<Node<Data>>[capacity]();
        };
/********************************************************************************
                    Union functions(public)
********************************************************************************/
        /**
         *@brief inserts a new singleton taged by i as key, carrying data.!note implementation does not support overriding existing key 

         */
        void makeSet(int key,Data data);
        Node<Data>* find(int i);
        Data& get(int i);
        void printNullIndexes();
        void unite(int host,int absorbed);
        void printGroup(int i);
        template<class Operation>
        void inOrderHelper(Operation func,int root);
        template<class Operation>
        void inOrder(Operation func,Node<Data>* root);
        template<class Operation,class Var>
        void inOrderHelper(Operation func,Var var,int root);
        template<class Operation,class Var>
        void inOrder(Operation func,Var var,Node<Data>* root);
        int getCapacity();
        

    };
    template<class Data>
    void  Union<Data>::makeSet(int key ,Data data)
    {
       
            ptrArray[key] = std::make_shared<Node<Data>>(data,key);
            ptrArray[key].get()->head = ptrArray[key].get();
            ptrArray[key].get()->next = nullptr;
        
    }

    template<class Data>
    void Union<Data>::printNullIndexes()
    {
        for (size_t i = 0; i < capacity; i++)
        {
            if(ptrArray[i] == nullptr)
                std::cout << i << " is empty" << std::endl;
        }
        
    }

    template<class Data>
    Node<Data>* Union<Data>:: find(int i)
    {
        
        if(ptrArray[i] != nullptr)
        {
            Node<Data>* current = ptrArray[i].get();
           //skip to known head if known(! might point to self. algorithm still holds)
           current = current->head;
           //initial search
           while(current->next != nullptr)
                current = current->next;
            Node<Data>* root = current;
            //update head 
            current = ptrArray[i].get();
             while(current->next != nullptr && current->head != root)
             {
                 std::cout << current->key << " updated head" << std::endl;
                 current->head = root;
                 current = current->next;
             }

             return root;
                
        }
        else
        {
            //!!!! handle
            return nullptr;
        }
    }

    template<class Data>
    void Union<Data>::unite(int host_key,int absorbed_key)
    {
        Node<Data>* host = find(host_key);
        Node<Data>* absorbed = find(absorbed_key);
        if(host == absorbed)
            throw KeyExists();
        if(host->counter >= absorbed->counter)
        {
            absorbed->next = host;
            host->counter += absorbed->counter;
        }
        else
        {
            host->next = absorbed;
            absorbed->counter += host->counter;
        }
        
    }


    template<class Data>
    void Union<Data>::printGroup(int i)
    {
        Node<Data>* current = find(i);
        if(current == nullptr)
            return;
        do
        {
            std::cout << current->key << " ";
            current = current->next;
        } 
        while(current != nullptr);
        std::cout << std::endl;
    }

    template<class Data>
    template<class Operation>
    void Union<Data>::inOrderHelper(Operation func,int root)
    {
       if(ptrArray[root] != nullptr)
            inOrderHelper(func,ptrArray[root].get());
    }

    template<class Data>
    template<class Operation>
    void Union<Data>::inOrder(Operation func,Node<Data>* root)
    {
        func(root->data);
        if(root->next != nullptr)
        inOrderHelper(func,root->next);
    }

    template<class Data>
    template<class Operation,class Var>
    void Union<Data>::inOrderHelper(Operation func,Var var,int root)
    {
       if(ptrArray[root] != nullptr)
            inOrder(func,var,ptrArray[root].get());
    }

    template<class Data>
    template<class Operation,class Var>
    void Union<Data>::inOrder(Operation func,Var var,Node<Data>* root)
    {
        func(*(root->data.get()),var);
        if(root->next != nullptr)
        inOrder(func,var,root->next);
    }

     template<class Data>
     Data& Union<Data>::get(int key)
     {
         return find(key)->data;
     }

     template<class Data>
     int Union<Data>::getCapacity()
     {
         return capacity;
     }

 }
#endif