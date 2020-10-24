#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>

//----------------declaration-----------------------------------------------------------
template <class T>
class Vector {
private:
	size_t size;
	T* data;

	void resize(size_t new_size, size_t shift_to_right, size_t start_point);

public:
	Vector();

	Vector(size_t size);

	size_t get_size() const;

	T at(size_t id) const;

	T& operator[](size_t id);

	void pop_at(size_t id);

	void clear();

	void push_back(T value);

	void push_front(T value);

	void pop_back();

	void pop_front();

	void operator=(Vector* vect);

	~Vector();

};

template <class T>
std::ostream operator<<(const std::ostream& lhs, const Vector<T>& rhs);

//---------------------------------definition---------------------------------------

template<class T>
inline Vector<T>::Vector()
{
	this->size = 0;
	this->data = new T[1];
}

template<class T>
inline Vector<T>::Vector(size_t size) : size(size)
{
	this->size = new T[size];
}


template<class T>
inline size_t Vector<T>::get_size() const
{
	return this->size;
}

template<class T>
inline T Vector<T>::at(size_t id) const
{
	return data[id];
}

template<class T>
inline T& Vector<T>::operator[](size_t id)
{
	return data[id];
}

template<class T>
inline void Vector<T>::pop_at(size_t id)
{
	resize(this->size - 1, id, 0);
}

template<class T>
inline void Vector<T>::clear()
{
	delete[] this->data;
	this->size = 0;
}

template<class T>
inline void Vector<T>::push_back(T value)
{
	if (size == 0) {
		this->data[0] = value;
		this->size++;
	}
	else {
		resize(this->size + 1, this->size + 1, 0);
		this->data[this->size - 1] = value;
	}
}

template<class T>
inline void Vector<T>::push_front(T value)
{
	if (this->size == 0) {
		this->data[0] = value;
		this->size++;
	}
	else {
		resize(this->size + 1, this->size + 1, 1);
		this->data[0] = value;
	}
}

template<class T>
inline void Vector<T>::pop_back()
{
	resize(this->size - 1, this->size - 1, 0);
}

template<class T>
inline void Vector<T>::pop_front()
{
	resize(this->size - 1, 0, 0);
}

template<class T>
Vector<T>::~Vector()
{
	clear();
}

template<class T>
inline void Vector<T>::resize(size_t new_size, size_t ignored_elem, size_t start_point) {
	T* copy = new T[new_size];
	size_t prev_size = this->size;
	for (size_t i = start_point, id = 0; i < prev_size || i < new_size; i++, id++) {
		if (i == ignored_elem) {
			id++;
		}
		copy[i] = this->data[id];
	}
	delete[] this->data;
	this->data = copy;
	this->size = new_size;
}

template<class T>
inline void Vector<T>::operator=(Vector* rhs) {
	this->resize(rhs->size);
	for (size_t i = 0; i < rhs->size; i++) {
		this->data[i] = rhs->data[i];
	}
}

template<class T>
inline std::ostream& operator<<(std::ostream& lhs, const Vector<T>& rhs) {
	lhs << "{";
	bool is_first = 1;
	for (size_t i = 0; i < rhs.get_size(); i++) {
		if (!is_first) {
			lhs << ", ";
		}
		is_first = 0;
		lhs << rhs.at(i);
	}
	lhs << "}\n";
	return lhs;
}


#endif // VECTOR_HS