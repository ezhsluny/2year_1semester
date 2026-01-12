#include <iostream>
#include <cstring>
#include "circ_buff.hpp"

typedef char value_type;


int CircularBuffer::index(int i) const
{
  return (this->begin + i) % this->buf_capacity;
}

// --------------------------------------------------------
//constructor
CircularBuffer::CircularBuffer() : buffer(nullptr), buf_capacity(0), begin(0), size_(0)
{
  std::cout << "New empty circullar buffer was constructed" << std::endl;
}

  //deconstructor
  CircularBuffer::~CircularBuffer()
  {
    delete[] buffer;
    std::cout << "Circular buffer was deleted" << std::endl;
  }

  //copy-constructor
  CircularBuffer::CircularBuffer(const CircularBuffer &cb) : buf_capacity(cb.buf_capacity), begin(cb.begin), size_(cb.size_) 
  {
    buffer = new value_type[buf_capacity];
    for (int i = 0; i < size_; ++i)
    {
      buffer[index(i)] = cb.buffer[cb.index(i)];
    }

    std::cout << "Buffer was copied to new-created buffer" << std::endl;
  }

  //constructor with given capacity
  CircularBuffer::CircularBuffer(int capacity) : buf_capacity(capacity), begin(0), size_(0)
  {
    if (capacity <= 0)
    {
      throw std::invalid_argument("Capacity must be positive.");
    }
    buffer = new value_type[capacity];

    std::cout << "New circullar buffer of capacity " << capacity << " was constructed" << std::endl;
  }

  //constructor with given capacity and elem
  CircularBuffer::CircularBuffer(int capacity, const value_type & elem) : buf_capacity(capacity), begin(0), size_(capacity)
  {
    if (capacity <= 0)
    {
      throw std::invalid_argument("Capacity must be positive.");
    }

    buffer = new value_type[buf_capacity];
    for (int i = 0; i < buf_capacity; ++i)
    {
      buffer[i] = elem;
    }

    std::cout << "New circullar buffer with elems " << elem << " of capacity " << capacity << " was constructed" << std::endl;
  }
// ---------------------------------------------------------

  //Доступ по индексу. Не проверяют правильность индекса.
  value_type & CircularBuffer::operator[](int i)
  {
    return buffer[index(i)];
  }
  const value_type & CircularBuffer::operator[](int i) const
  {
    return buffer[index(i)];
  }
  
  //Доступ по индексу. Методы бросают исключение в случае неверного индекса.
  value_type & CircularBuffer::at(int i)
  {
    if (i < 0 || i >= size_) 
    {
      throw std::out_of_range("Index out of range.");
    }

    return buffer[index(i)];
  }
  const value_type & CircularBuffer::at(int i) const
  {
    if (i < 0 || i >= size_) 
    {
      throw std::out_of_range("Index out of range.");
    }

    return buffer[index(i)];
  }
// -------------------------------------------------------------------

  value_type & CircularBuffer::front() //Ссылка на первый элемент.
  {
    return buffer[index(0)];
  }
  value_type & CircularBuffer::back()  //Ссылка на последний элемент.
  {
    return buffer[index(size_ - 1)];
  }
  const value_type & CircularBuffer::front() const
  {
    return buffer[index(0)];
  }
  const value_type & CircularBuffer::back() const
  {
    return buffer[index(size_ - 1)];
  }
// ----------------------------------------------------------------------

  //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
  //переместится в начало аллоцированной памяти. Возвращает указатель 
  //на первый элемент.
  value_type * CircularBuffer::linearize()
  {
    if (begin == 0) 
    {
      return buffer;
    }
    value_type * new_buffer = new value_type[buf_capacity];
    for (int i = 0; i < size_; ++i) 
    {
      new_buffer[i] = buffer[index(i)];
    }
    delete[] buffer;
    buffer = new_buffer;
    begin = 0;

    std::cout << "Buffer was linearized" << std::endl;
    return buffer;
  }

  //Проверяет, является ли буфер линеаризованным.
  bool CircularBuffer::is_linearized() const
  {
    return (begin == 0);
  }
  
  //Сдвигает буфер так, что по нулевому индексу окажется элемент 
  //с индексом new_begin.
  void CircularBuffer::rotate(int new_begin)
  {
    if (new_begin < 0 || new_begin >= buf_capacity)
    {
      throw std::out_of_range("New begin index out of range");
    }
    begin = new_begin;
  }

  //Количество элементов, хранящихся в буфере.
  int CircularBuffer::size() const
  {
    return size_;
  }

  bool CircularBuffer::empty() const
  {
    return (size_ == 0);
  }

  //true, если size_() == capacity().
  bool CircularBuffer::full() const
  {
    return (size_ == buf_capacity);
  }

  //Количество свободных ячеек в буфере.
  int CircularBuffer::reserve() const
  {
    return (buf_capacity - size_);
  }

  //ёмкость буфера
  int CircularBuffer::capacity() const
  {
    return buf_capacity;
  }
// --------------------------------------------------------------------

  void CircularBuffer::set_capacity(int new_capacity)
  {
    if (new_capacity <= 0) 
    {
      throw std::invalid_argument("Capacity must be positive.");
    }

    value_type *new_buffer = new value_type[new_capacity];
    int copy_size = std::min(size_, new_capacity);
    for (int i = 0; i < copy_size; ++i) 
    {
      new_buffer[i] = buffer[index(i)];
    }

    delete[] buffer;
    buffer = new_buffer;
    begin = 0;
    size_ = copy_size;
    buf_capacity = new_capacity;
  }

  //Изменяет размер буфера.
  //В случае расширения, новые элементы заполняются элементом item.
  void CircularBuffer::resize(int new_size, const value_type& item)
  {
    if (new_size <= 0) 
    {
      throw std::invalid_argument("New size must be positive.");
    }

    if (new_size > buf_capacity)
    {
      set_capacity(new_size);

      for (int i = size_; i < new_size; ++i)
      {
        buffer[index(i)] = item;
      }
      size_ = new_size;
    }
    else if (new_size < buf_capacity)
    {
      size_ = new_size;
    }
  }

// --------------------------------------------------------
  //Оператор присваивания.
  CircularBuffer & CircularBuffer::operator=(const CircularBuffer & cb)
  {
    if (this != &cb)
    {
      delete[] buffer;
      buf_capacity = cb.buf_capacity;
      begin = cb.begin;
      size_ = cb.size_;
      buffer = new value_type[buf_capacity];
      
      for (int i = 0; i < cb.size_; ++i)
      {
        buffer[index(i)] = cb.buffer[cb.index(i)];
      }
    }
    return *this;
  }
  //Обменивает содержимое буфера с буфером cb.
  void CircularBuffer::swap(CircularBuffer & cb)
  {
    std::swap(buffer, cb.buffer);
    std::swap(buf_capacity, cb.buf_capacity);
    std::swap(begin, cb.begin);
    std::swap(size_, cb.size_);
  }

// -------------------------------------------------

  //Добавляет элемент в конец буфера. 
  //Если текущий размер буфера равен его ёмкости, то переписывается
  //первый элемент буфера (т.е., буфер закольцован). 
  void CircularBuffer::push_back(const value_type& item) {
    if (full()) {
      begin = (begin + 1) % buf_capacity; // Сдвиг начала буфера
      --size_;
    }
    buffer[index(size_)] = item;
    ++size_;
  }

  //Добавляет новый элемент перед первым элементом буфера. 
  //Аналогично push_back, может переписать последний элемент буфера.
  void CircularBuffer::push_front(const value_type& item) {
    if (full()) {
      begin = (begin + buf_capacity - 1) % buf_capacity; // Сдвиг буфера
      --size_;
    } else {
      --begin;
      if (begin < 0) {
        begin += buf_capacity;
      }
    }
    buffer[index(0)] = item;
    ++size_;
  }
  //удаляет последний элемент буфера.
  void CircularBuffer::pop_back() {
    if (empty()) {
      throw std::out_of_range("Cannot pop from an empty buffer");
    }
    --size_;
  }
  //удаляет первый элемент буфера.
   void CircularBuffer::pop_front() {
    if (empty()) {
      throw std::out_of_range("Cannot pop from an empty buffer");
    }
    ++begin;
    if (begin >= buf_capacity) {
      begin -= buf_capacity;
    }
    --size_;
  }

  //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
  void CircularBuffer::insert(int pos, const value_type& item) {
    if (pos < 0 || pos > size_) {
      throw std::out_of_range("Invalid insertion position");
    }
    if (full()) {
      rotate(1);
    } else {
      ++size_;
    }
    for (int i = size_ - 1; i > pos; --i) {
      buffer[index(i)] = buffer[index(i - 1)];
    }
    buffer[index(pos)] = item;
  }
  //Удаляет элементы из буфера в интервале [first, last).
  void CircularBuffer::erase(int first, int last)
  {
    if (first < 0 || first >= size_ || last < 0 || last >= size_ || first > last) 
    {
      throw std::out_of_range("Invalid erase range");
    }
    for (int i = first; i < last; ++i) 
    {
      buffer[index(i)] = buffer[index(i + 1)];
    }
    size_ -= (last - first);
  }
  //Очищает буфер.
  void CircularBuffer::clear()
  {
    size_ = 0;
    begin = 0;
  }

// -----------------------------------------------------

bool operator==(const CircularBuffer & a, const CircularBuffer & b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const CircularBuffer & a, const CircularBuffer & b) {
  return !(a == b);
}