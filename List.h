#ifndef LIST_H
#define LIST_H

template<typename T>
class List {
 public:
     List() {};
     virtual ~List();
     List(const List& rhs);
     List& operator=(const List& rhs);

     void insertAt(int pos, const T& element) noexcept(false);
     T getAt(int pos) const noexcept(false);
     void removeAt(int pos) noexcept(false);
     bool removeElement(const T& element);
     bool findElement(const T& toFind) const;
     int length() const;
     void getAll(T arr[], int cap) noexcept(false);
 private:
     /* Inner class for nodes. */
     class Node {
      public:
          Node() {};
          Node(const T& element) : elem(element) {};
          ~Node() {};

          T elem;
          Node *link = nullptr;
    };

    /* Outer class privates. */
    Node *head = nullptr;              /* First node. */
    int len = 0;

    void deepCopy(const List& other);
    void free();
};
#endif

/* Deep copy. */
template<typename T>
void List<T>::deepCopy(const List& other) {
    Node* otherNode = other.head;

    for (int i = 0; i < other.len; i++) {
        insertAt(i, otherNode->elem);
        otherNode = otherNode->link;
    }

    this->len = other.len;
}

template<typename T>
void List<T>::free() {
    Node* prevNode = this->head;
    Node *nextNode = nullptr;

    for (int i = 0; i < this->len; i++ && prevNode) {
        nextNode = prevNode->link;
        delete prevNode;
        prevNode = nullptr;
        prevNode = nextNode;
    }

}

/* List destructor. */
template<typename T>
List<T>::~List() {
    free();
}

/* Ctor. */
template<typename T>
List<T>::List(const List& rhs) {
    deepCopy(rhs);
}

/* Overloading assignment operator. */
template<typename T>
List<T>& List<T>::operator=(const List& rhs) {
    if (this != &rhs) {
        free();
        deepCopy(rhs);
    }

    return *this;
}

template<typename T>
void List<T>::insertAt(int pos, const T& element) noexcept(false) {
    if (pos > this->len) throw "Error: Position is larger than length of list.";
    if (pos < 0) throw "Error: Position cannot be negative.";

    Node *node = new Node(element);         /* Pointer to new node. */
    node->elem = element;
    Node *nextNode = this->head;
    Node *prevNode = nullptr;


    if (pos == 0) {                         /* Insert at head. */
        node->link = (this->head) ? this->head : nullptr;
        this->head = node;
    } else {                                /* Insert at pos > 0. */
        for (int i = 0; i < pos; i++) {
            prevNode = nextNode;
            nextNode = nextNode->link;
        }

        prevNode->link = node;
        node->link = nextNode;
    }

    this->len++;
}

/* Return element at pos N. */
template<typename T>
T List<T>::getAt(int pos) const noexcept(false) {
    if (pos > this->len) throw "Error: Position is larger than length of list.";
    if (pos < 0) throw "Error: Position cannot be negative.";

    Node *node = this->head;

    /* Traverse list until iterator is at pos N. */
    for (int i = 0; i < pos; i++) {
        node = node->link;
    }

    return node->elem;
}


/* Remove element at pos N */
template<typename T>
void List<T>::removeAt(int pos) noexcept(false) {
    if (pos > this->len) throw "Error: Position is larger than length of list.";
    if (pos < 0) throw "Error: Position cannot be negative.";

    Node *node = this->head;
    Node *prevNode = nullptr;

    if (pos == 0) {
        Node *nextNode = this->head->link;
        delete this->head;
        this->head = nextNode;
    } else {
        for (int i = 0; i < pos; i++) {
            prevNode = node;        /* Node preceding the one we're removing. */
            node = node->link;      /* Node to remove. */

            if (!node->link) {       /* At tail. */
                delete node;
                prevNode->link = nullptr;
                this->len--;

                return;
            }
        }

        prevNode->link = node->link; /* Set a valid link to the next node to
                                      *  preserve sequential pattern.
                                      */

        delete node;
        node = nullptr;
    }

    this->len--;
}

/* Remove element based on element value.  */
template<typename T>
bool List<T>::removeElement(const T& element) {
    bool removed = false;
    Node *node = nullptr;
    Node *prevNode = this->head;

    for (int pos = 0; pos < this->len; pos++) {
        node = prevNode;
        prevNode = node->link;

        if (node->elem == element) {
            removeAt(pos);
            removed = true;
        }
    }

    return removed;
}

/* Check if element exists. */
template<typename T>
bool List<T>::findElement(const T& toFind) const {
    bool found = false;
    Node *prevNode = this->head;

    /* Traverse nodes and compare elements to passed arg. */
    for (int i = 0; i < this->len; i++) {
        if (prevNode->elem == toFind) {
            found = true;
        }
        prevNode = prevNode->link;
    }

    return found;
}


/* Return amount of existing elements in list. */
template<typename T>
int List<T>::length() const {
    return this->len;
}

/* Populate an array with elements from list. */
template<typename T>
void List<T>::getAll(T arr[], int cap) noexcept(false) {
    if (this->len > cap) throw "Error: Length of list is larger than cap.";

    for (int i = 0; i < (this->len); i++) {
        arr[i] = getAt(i);
    }
}

/* vim: set ts=4 sw=4 tw=79 ft=cpp ff=unix et :*/
