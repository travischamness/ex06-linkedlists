#include <cstdlib>
#include <utility>

namespace edu {
	namespace vcccd {
		namespace vc {
			namespace csv15 {
				template<class T>
				class LinkedList {
				private:
					struct Node {
						Node(T data, Node *next) : _data(data), _next(next) {}
						Node* _next;
						T _data;
					};
				public:
					class iterator {
					public:
						iterator(Node *node) : _node(node) {}
						iterator(const iterator &other) : _node(other._node) {}

					public:
						const T &operator*() { return _node->_data; }
						const T &operator*() const { return _node->_data; }
						iterator &operator++() { _node = _node->_next; return *this; } //SegFualt Line 25
						iterator operator++(int) { iterator before(*this); _node = _node->_next; return before; }
						bool operator==(const iterator &other) { return other._node == _node; }
						bool operator!=(const iterator &other) { return !operator==(other); }
						bool operator<(const iterator &other) {return _node < other._node;}
						Node *node() { return _node; }
					private:
						Node *_node;
					};

				public:
					LinkedList() : _size(0), head(nullptr), tail(nullptr){} //Constructor only needs some initialized basic varial
					LinkedList(const LinkedList &other) : _size(0), head(nullptr), tail(nullptr) {//Deep copy. This is the entire implimentation of the deep copy. The push_front(val) creates for you the list of data from the "other" list.
						for (const T &val: other) push_front(val);
					}

					~LinkedList() { clear(); } //Destructor which implements the clear operator. 

				public:
					bool empty() const { return _size == 0; } // head == nullptr; or tail == tailptr; are all valid
					T &front() { return head->_data; } //writing at front
					const T &front() const { return head->_data; } //reading front
					T &back() { return tail->_data; } //writing at back
					const T &back() const { return tail->_data; } //reading at back
					size_t size() const { return _size; } //reading size

				public:
					iterator begin() {
						return iterator(head);
					}
					const iterator begin() const { return iterator(head);  } //
					iterator end() {return iterator(nullptr);} //This is the end case for the end of the loop
					const iterator end() const {return iterator(nullptr);}

				public: // THIS IS WHERE I BEGIN ALL ABOVE IS DONE
					void clear() { //Status Code: Situation Bueno
						erase(begin(),end());
						delete head;
						head = tail = nullptr;
						_size = 0;
					    }

					iterator insert(iterator where, const T &value) {//Status Code: Situation Bueno
					    if(where.node()->_next == nullptr){
					        Node *newNode = new Node(value,nullptr);
					        where.node()->_next = newNode;
					        tail = newNode;
					        _size++;
					    }
					    else{
                            Node *newNode = new Node(value,nullptr);
                            Node *holdingTheFort = where.node()->_next;
                            where.node()->_next = newNode;
                            newNode->_next = holdingTheFort;
                            _size++;
                            delete holdingTheFort;
					    }
					}
					//Erases node after where.
					iterator erase(iterator where) { // Status Code: Situation Bueno
					    if(where.node()->_next == nullptr){
					        return where;
					    }
					    else{
					        Node *Goodbye = where.node()->_next;
					        where.node()->_next = Goodbye->_next;
					        delete Goodbye;
					    }
					    _size--;
					    return where;
					}
					iterator erase(iterator first, iterator last) {
					    for(auto i = first; i < last; i++){
					        erase(i);
					        _size--;
					    }
					}
					void push_back(const T &value) { // Status Code: Situation Bueno
                        Node *newNode = new Node(value, nullptr);
					    if(_size == 0){
					     head = tail = newNode;//assign value and initialize linked list
					    }
					    else{
					        newNode->_next = head;
					        head = newNode;
					    }
                        _size++;//update size
					}
					void pop_back() {// Status Code: Situation Bueno
					    if(_size == 0) return;
					    if(_size == 1) {
					        delete tail;
					        head = tail = nullptr;
					        _size = 0;
					        return;
                        }
                        Node *n = head;
					   // Node *follow = n; dont need this
                        while(n->_next != nullptr) {
                            //follow = n;
                            n = n->_next;
                        }
                        delete tail; //remove old tail
                        n->_next = nullptr;//update n to be def of tail
                        tail = n;//reassign tail
                        _size--;//update size
					}
					void push_front(const T &value) {// Status Code: Situation Bueno
					    Node *newNode = new Node(value, nullptr); //next = nullptr for tail
					    if(head == nullptr) head = tail = newNode;
						else {
						    Node *oldTail = tail;
						    oldTail->_next = newNode;
						}
						_size++; //update size
					}
					void pop_front() { // Status Code: Situation Bueno
					    //Base Conditions
					    if(_size == 0) return; //no work to be done, list is empty by def.
					    else if(_size == 1) {
					        delete head; //destroy evidence
					        head = tail = nullptr; //sets list to our definition of empty
					        _size = 0; //resize list to our definition of empty
					        return; //exit
                        }
					    Node *oldNode = head;
					    head = oldNode->_next;
					    delete oldNode;
					    _size--;
					}

				public:
					void swap(LinkedList &other) { //Status Code: Situation Bueno

//						size_t holdsize = this->size();
//						this->size() = other.size();
//						other.size() = holdsize;
//
//						Node *holdhead = this->head;
//						this->head = other.head;
//						other.head = holdhead;
//
//						Node *holdtail = this->tail;
//						this->tail = other.tail;
//						other.tail = holdtail;
//
//						delete holdhead;
//						delete holdtail;

//						Oh HELL YES for next time! - STD::SWAP
						std::swap(this -> head, other.head);
						std::swap(this -> tail, other.tail);
						std::swap(this -> _size, other._size);

					}

				private:
					Node *head;
					Node *tail;
					size_t _size;
				};
			}
		}
	}
}