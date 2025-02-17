/*
TC : O(1)
SC : O(N)
*/
class LRUCache {
public:
    class Node{
        public:
        int key, value;
        Node *prev, *next;
        public:
        Node(int key, int value){
            this->key = key;
            this->value = value;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    map<int, Node*> store;
    Node *head, *tail;
    int capacity;

    void addToHead(Node *node){ 

        
        node->next = head->next;
        node->next->prev =  node;
        head->next = node;
        node->prev = head;
    }

    void removeNode(Node *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    LRUCache(int capacity) {
        this->capacity = capacity;
        head = new Node(-1,-1);
        tail = new Node(-1,-1);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if(store.find(key)==store.end()){
            return -1;
        }

        Node *node = store[key];
        removeNode(node);
        addToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if(store.find(key)!=store.end()){
            Node *node = store[key];
            removeNode(node);
            addToHead(node);
            node->value = value;
            return;
        }

        if(store.size() == this->capacity){
            Node *tailPrev = tail->prev;
            removeNode(tailPrev);
            store.erase(tailPrev->key);
        }


        Node *node = new Node(key, value);
        addToHead(node);
        store.insert({key, node});
        Node *temp = head;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */