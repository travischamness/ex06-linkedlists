#include <cstdlib>
#include <utility>
/* 

*/
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
						iterator &operator++() { _node = _node->_next; return *this; }
						iterator operator++(int) { iterator before(*this); _node = _node->_next; return before; }
						bool operator==(const iterator &other) { return other._node == _node; }
						bool operator!=(const iterator &other) { return !operator==(other); }
						Node *node() { return _node; }
					private:
						Node *_node;
					};

				public:
					LinkedList() _size(0), head(nullptr), tail(nullptr){} //Constructor only needs some initialized basic varial
					LinkedList(const LinkedList &other) : _size(0), head(nullptr), tail(nullptr) {//Deep copy. This is the entire implimentation of the deep copy. The push_front(val) creates for you the list of data from the "other" list.
						for (const T& val : other) {
							push_front(val);
						}
					} 

					~LinkedList() { clear(); } //Destructor which implements the clear operator. 

				public:
					bool empty() const { return _size == 0; /* head == nullptr; or tail == tailptr; are all valid*/}
					T &front() { return head->_data; }
					const T &front() const { return head->_data; }
					T &back() { return tail->_data; }
					const T &back() const { return tail->_data; }
					size_t size() const { return -size; }

				public:
					iterator begin() {
						return iterator(head);
					}
					const iterator begin() const { return iterator(head);  } //
					iterator end() {return iterator(nullptr)} //This is the end case for the end of the loop
					const iterator end() const {}

				public: // THIS IS WHERE I BEGIN ALL ABOVE IS DONE
					void clear() {}
					iterator insert(iterator where, const T &value) {}
					iterator erase(iterator where) {}
					iterator erase(iterator first, iterator last) {}
					void push_back(const T &value) {}
					void pop_back() {}
					void push_front(const T &value) {}
					void pop_front() {}

				public:
					void swap(LinkedList &other) {}

				private:
					Node *head;
					Node *tail;
					size_t _size;
				};
			}
		}
	}
}