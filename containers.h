#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <utility>
#include <vector>
#include <cassert>

namespace containers {

// --------------------------------------------------------------------------

template <typename T>
class BiDirectionalList {  // class of BiDirectionalList
 public:
  struct Node {  // structure of one element
   public:
    T value;
   private:
    Node* next_;
    Node* previous_;
    explicit Node(const T& new_value) : value(new_value) {  // Node constructor
      next_ = nullptr;
      previous_ = nullptr;
    }
    friend BiDirectionalList;
  };  // structure of one element

  BiDirectionalList();  // constructor without arguments
  BiDirectionalList(const std::initializer_list<T>&);  // initializer_list
                                                       // constructor
  BiDirectionalList(const BiDirectionalList<T>&);  // copy constructor
  BiDirectionalList(BiDirectionalList<T>&&);  // move constructor

  ~BiDirectionalList();  // destructor

  BiDirectionalList& operator=(const BiDirectionalList<T>&);  // operator= with
                                                              // const reference
  BiDirectionalList& operator=(BiDirectionalList<T>&&);  // operator= with
                                                         // moved object

  int Size() const;  // gets size of BiDirectionalList
  bool IsEmpty() const;  // checks if BiDirectionalList is empty

  void PushFront(const T& value);  // pushes element at the front side
                                   // of the BiDirectionalList
  void PushBack(const T& value);  // pushes element at the back side
                                  // of the BiDirectionalList

  Node* Front();  // gets the pointer of the first element
  Node* Back();  // gets the pointer of the last element
  Node* operator[](int index);  // gets the pointer of the element at this index

  void PopFront();  // removes the first element
  void PopBack();  // removes the last element

  std::vector<T> ToVector() const;  // transforms BiDirectionalList to vector

  int Find(const T& value) const;  // finds an index of the first element
                                   // with this value
  std::vector<int> FindAll(const T& value) const;  // finds all indexes of
  // elements with this value and converts them into vector

  void InsertBefore(Node* element, const T& value);  // inserts an element with
  // this value before this element
  void InsertAfter(Node* element, const T& value);  // inserts an element with
  // this value after this element
  void Erase(Node* element);  // removes element by pointer

  const Node* Front() const;  // gets the const pointer of the first element
  const Node* Back() const;  // gets the const pointer of the last element
  const Node* operator[](int index) const;  // gets the const pointer of the
                                            // element at this index

  bool operator==(const BiDirectionalList<T>&) const;  // checks if two lists
                                                       // are equal
  bool operator!=(const BiDirectionalList<T>&) const;  // checks if two lists
                                                       // are not equal

 private:
  int size_ = 0;
  Node* head_;
  Node* tail_;
  void CleanList();  // method of cleaning BiDirectionalList
};  // class of BiDirectionalList

template<typename T>
BiDirectionalList<T>::BiDirectionalList() {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}
template<typename T>
BiDirectionalList<T>::BiDirectionalList(const std::initializer_list<T>& list) {
  size_ = list.size();
  if (size_ > 0) {
    head_ = new Node(*list.begin());
    head_->previous_ = nullptr;
    Node* node_ptr = head_;
    for (auto ptr = list.begin() + 1; ptr != list.end(); ++ptr) {
      node_ptr->next_ = new Node(*ptr);
      node_ptr->next_->previous_ = node_ptr;
      node_ptr = node_ptr->next_;
    }
    tail_ = node_ptr;
    tail_->next_ = nullptr;
  } else {
    BiDirectionalList();
  }
}
template<typename T>
BiDirectionalList<T>::BiDirectionalList(const BiDirectionalList<T>& list) {
  size_ = list.size_;
  if (size_ > 0) {
    head_ = new Node(list.head_->value);
    head_->previous_ = nullptr;
    Node* node_ptr = head_;
    Node* list_ptr = list.head_;
    for (int i = 0; i < list.size_ - 1; ++i) {
      node_ptr->next_ = new Node(list_ptr->next_->value);
      node_ptr->next_->previous_ = node_ptr;
      node_ptr = node_ptr->next_;
      list_ptr = list_ptr->next_;
    }
    tail_ = node_ptr;
    tail_->next_ = nullptr;
  } else {
    BiDirectionalList();
  }
}
template<typename T>
BiDirectionalList<T>::BiDirectionalList(BiDirectionalList<T>&& list) {
  size_ = list.size_;
  head_ = list.head_;
  head_->previous_ = nullptr;
  tail_ = list.tail_;
  tail_->next_ = nullptr;
  list.size_ = 0;
  list.head_ = nullptr;
  list.tail_ = nullptr;
}

template<typename T>
BiDirectionalList<T>::~BiDirectionalList() {
  Node* pointer = head_;
  while (pointer != tail_) {
    pointer = pointer->next_;
    delete pointer->previous_;
  }
  delete pointer;
  head_ = nullptr;
  tail_ = nullptr;
}

template<typename T>
BiDirectionalList<T>&
    BiDirectionalList<T>::operator=(const BiDirectionalList<T>& list) {
  if (this == &list) {
    return *this;
  }
  this->CleanList();
  size_ = list.size_;
  if (size_ > 0) {
    head_ = new Node(list.head_->value);
    Node* node_ptr = head_;
    Node* list_ptr = list.head_;
    for (int i = 0; i < list.size_ - 1; ++i) {
      node_ptr->next_ = new Node(list_ptr->next_->value);
      node_ptr->next_->previous_ = node_ptr;
      node_ptr = node_ptr->next_;
      list_ptr = list_ptr->next_;
    }
    tail_ = node_ptr;
  }
  return *this;
}

template<typename T>
BiDirectionalList<T>&
    BiDirectionalList<T>::operator=(BiDirectionalList<T>&& list) {
  if (this == &list) {
    return *this;
  }
  this->CleanList();
  size_ = list.size_;
  head_ = list.head_;
  tail_ = list.tail_;
  list.size_ = 0;
  list.head_ = nullptr;
  list.tail_ = nullptr;
  return *this;
}

template<typename T>
int BiDirectionalList<T>::Size() const {
  return size_;
}
template<typename T>
bool BiDirectionalList<T>::IsEmpty() const {
  return size_ == 0;
}

template<typename T>
void BiDirectionalList<T>::PushFront(const T& value) {
  if (size_ != 0) {
    head_->previous_ = new Node(value);
    head_->previous_->next_ = head_;
    head_ = head_->previous_;
  } else {
    head_ = new Node(value);
    tail_ = head_;
  }
  ++size_;
}
template<typename T>
void BiDirectionalList<T>::PushBack(const T& value) {
  if (size_ != 0) {
    tail_->next_ = new Node(value);
    tail_->next_->previous_ = tail_;
    tail_ = tail_->next_;
  } else {
    tail_ = new Node(value);
    head_ = tail_;
  }
  ++size_;
}

template<typename T>
typename BiDirectionalList<T>::Node* BiDirectionalList<T>::Front() {
  return head_;
}
template<typename T>
typename BiDirectionalList<T>::Node* BiDirectionalList<T>::Back() {
  return tail_;
}
template<typename T>
typename BiDirectionalList<T>::Node*
         BiDirectionalList<T>::operator[](int index) {
  Node* ptr = head_;
  for (int i = 0; i < index; ++i) {
    ptr = ptr->next_;
  }
  return ptr;
}

template<typename T>
void BiDirectionalList<T>::PopFront() {
  if (size_ > 1) {
    head_ = head_->next_;
    delete head_->previous_;
    head_->previous_ = nullptr;
    --size_;
  } else if (size_ == 1) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    --size_;
  }
}
template<typename T>
void BiDirectionalList<T>::PopBack() {
  if (size_ > 1) {
    tail_ = tail_->previous_;
    delete tail_->next_;
    tail_->next_ = nullptr;
    --size_;
  } else if (size_ == 1) {
    delete tail_;
    tail_ = nullptr;
    head_ = nullptr;
    --size_;
  }
}
template<typename T>
std::vector<T> BiDirectionalList<T>::ToVector() const {
  std::vector<T> vector;
  Node* ptr = head_;
  for (int i = 0; i < size_; ++i) {
    vector.push_back(ptr->value);
    ptr = ptr->next_;
  }
  return vector;
}

template<typename T>
int BiDirectionalList<T>::Find(const T& value) const {
  Node* ptr = head_;
  for (int i = 0; i < size_; ++i) {
    if (ptr->value == value) {
      return i;
    }
    ptr = ptr->next_;
  }
  return -1;
}
template<typename T>
std::vector<int> BiDirectionalList<T>::FindAll(const T& value) const {
  std::vector<int> vector;
  Node* ptr = head_;
  for (int i = 0; i < size_; ++i) {
    if (ptr->value == value) {
      vector.push_back(i);
    }
    ptr = ptr->next_;
  }
  return vector;
}

template<typename T>
void BiDirectionalList<T>::InsertBefore(BiDirectionalList<T>::Node* element,
                                        const T& value) {
  Node* ptr = new Node(value);
  ptr->next_ = element;
  if (element != head_) {
    ptr->previous_ = element->previous_;
    element->previous_->next_ = ptr;
  } else {
    head_ = ptr;
  }
  element->previous_ = ptr;
  ++size_;
}
template<typename T>
void BiDirectionalList<T>::InsertAfter(BiDirectionalList<T>::Node* element,
                                       const T& value) {
  Node* ptr = new Node(value);
  ptr->previous_ = element;
  if (element != tail_) {
    ptr->next_ = element->next_;
    element->next_->previous_ = ptr;
  } else {
    tail_ = ptr;
  }
  element->next_ = ptr;
  ++size_;
}
template<typename T>
void BiDirectionalList<T>::Erase(BiDirectionalList<T>::Node* element) {
  if (element == head_ && element == tail_) {
    head_ = nullptr;
    tail_ = nullptr;
    delete element;
  } else if (element == head_) {
    head_ = element->next_;
    head_->previous_ = nullptr;
    delete element;
  } else if (element == tail_) {
    tail_ = element->previous_;
    tail_->next_ = nullptr;
    delete element;
  } else {
    element->previous_->next_ = element->next_;
    element->next_->previous_ = element->previous_;
    delete element;
  }
  --size_;
}

template<typename T>
const typename BiDirectionalList<T>::Node* BiDirectionalList<T>::Front() const {
  return head_;
}
template<typename T>
const typename BiDirectionalList<T>::Node* BiDirectionalList<T>::Back() const {
  return tail_;
}
template<typename T>
const typename BiDirectionalList<T>::Node*
               BiDirectionalList<T>::operator[](int index) const {
  Node* ptr = head_;
  for (int i = 0; i < index; ++i) {
    ptr = ptr->next_;
  }
  return ptr;
}

template<typename T>
bool BiDirectionalList<T>::operator==(const BiDirectionalList<T>& list) const {
  if (size_ != list.size_) {
    return false;
  }
  Node* this_ptr = head_;
  Node* list_ptr = list.head_;
  for (int i = 0; i < size_; ++i) {
    if (this_ptr->value != list_ptr->value) {
      return false;
    }
    this_ptr = this_ptr->next_;
    list_ptr = list_ptr->next_;
  }
  return true;
}
template<typename T>
bool BiDirectionalList<T>::operator!=(const BiDirectionalList<T>& list) const {
  return !(*this == list);
}

template<typename T>
void BiDirectionalList<T>::CleanList() {
  if (size_ > 0) {
    Node* pointer = head_;
    while (pointer != tail_) {
      pointer = pointer->next_;
      delete pointer->previous_;
    }
    delete pointer;
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
  }
}

// --------------------------------------------------------------------------

template <typename T>
class Queue {  // class of Queue
 public:
    Queue() : queue_(BiDirectionalList<T>()) {}  // constructor without
                                                 // arguments
    Queue(const std::initializer_list<T>& list) :
          queue_(BiDirectionalList<T>(list)) {}  // initializer_list constructor


    void Push(const T& value);  // pushes element at the front side of the Queue
    void Pop();  // removes element from the back side of the Queue
    const T& Get() const;  // gets element from the back side of the Queue

    int Size() const;  // gets size of the Queue
    bool IsEmpty() const;  // checks if Queue is empty

    bool operator==(const Queue&);  // checks if two queues are equal
    bool operator!=(const Queue&);  // checks if two queues are not equal

 private:
    BiDirectionalList<T> queue_;
};  // class of Queue

template<typename T>
void Queue<T>::Push(const T& value) {
  queue_.PushFront(value);
}
template<typename T>
void Queue<T>::Pop() {
  queue_.PopBack();
}
template<typename T>
const T& Queue<T>::Get() const {
  return queue_.Back()->value;
}

template<typename T>
int Queue<T>::Size() const {
  return queue_.Size();
}
template<typename T>
bool Queue<T>::IsEmpty() const {
  return queue_.IsEmpty();
}

template<typename T>
bool Queue<T>::operator==(const Queue& eq_queue) {
  return queue_ == eq_queue.queue_;
}
template<typename T>
bool Queue<T>::operator!=(const Queue& neq_queue) {
  return queue_ != neq_queue.queue_;
}

// --------------------------------------------------------------------------

// Раскоментируйте нужные строки ниже для выбора варианта

enum class Variant {
  kQueue,
  kStack,
};

Variant GetVariant() {
  return Variant::kQueue;
  // return Variant::kStack;
}

template<typename T>
using Container = Queue<T>;

// template<typename T>
// using Container = Stack<T>;

// --------------------------------------------------------------------------

}  // namespace containers

#endif  // CONTAINERS_H_
