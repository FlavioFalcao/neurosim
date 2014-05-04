/*
 * NeuroSim Library Shared Pointer Vector
 * Colby Horn
 */

#ifndef __SHARED_PTR_VECTOR__
#define __SHARED_PTR_VECTOR__

#include <memory>
#include <stdexcept>
#include <vector>

#include <boost/function.hpp>
#include <boost/iterator/transform_iterator.hpp>

#ifndef __DEREFERENCE__
#define __DEREFERENCE__

namespace neuro {

template <typename T>
T& dereference(std::shared_ptr<T> pointer) { return *pointer; }

}

#endif

namespace neuro {

template <typename T>
class shared_ptr_vector : public std::vector< std::shared_ptr<T> > {
private:
	typedef std::vector< std::shared_ptr<T> > inherited;
	
public:
	typedef boost::transform_iterator<boost::function<T& (std::shared_ptr<T>)>, 
			typename inherited::const_iterator> const_iterator;
	typedef const T& const_reference;
	typedef boost::transform_iterator<boost::function<T& (std::shared_ptr<T>)>, 
			typename inherited::iterator> iterator;
	typedef T& reference;
	typedef typename inherited::size_type size_type;
	
	// TODO update value_type interface to hide std::shared_ptr as raw *
	typedef T value_type;
	
	reference       at(size_type);
	const_reference at(size_type) const;
	reference       back();
	const_reference back() const;
	iterator        begin();
	const_iterator  begin() const;
	iterator        end();
	const_iterator  end() const;
	void            erase(const value_type&);
	reference       front();
	const_reference front() const;
	reference       operator[](size_type);
	const_reference operator[](size_type) const;
};

template <typename T>
typename shared_ptr_vector<T>::reference 
		shared_ptr_vector<T>::at(shared_ptr_vector<T>::size_type n) {
	if (n < inherited::size()) {
		return *inherited::at(n);
	} else {
		throw std::out_of_range("shared_ptr_vector::at: index out of range");
	}
}

template <typename T>
typename shared_ptr_vector<T>::const_reference 
		shared_ptr_vector<T>::at(shared_ptr_vector<T>::size_type n) const {
	if (n < inherited::size()) {
		return *inherited::at(n);
	} else {
		throw std::out_of_range("shared_ptr_vector::at: index out of range");
	}
}

template <typename T>
typename shared_ptr_vector<T>::reference shared_ptr_vector<T>::back() {
	return operator[](inherited::size() - 1);
}

template <typename T>
typename shared_ptr_vector<T>::const_reference shared_ptr_vector<T>::back() const {
	return operator[](inherited::size() - 1);
}

template <typename T>
typename shared_ptr_vector<T>::iterator shared_ptr_vector<T>::begin() {
	return boost::make_transform_iterator(inherited::begin(), &dereference<T>);
}

template <typename T>
typename shared_ptr_vector<T>::const_iterator shared_ptr_vector<T>::begin() const {
	return boost::make_transform_iterator(inherited::begin(), &dereference<T>);
}

template <typename T>
typename shared_ptr_vector<T>::iterator shared_ptr_vector<T>::end() {
	return boost::make_transform_iterator(inherited::end(), &dereference<T>);
}

template <typename T>
typename shared_ptr_vector<T>::const_iterator shared_ptr_vector<T>::end() const {
	return boost::make_transform_iterator(inherited::end(), &dereference<T>);
}

template <typename T>
void shared_ptr_vector<T>::erase(const shared_ptr_vector<T>::value_type& r) {
	typename inherited::iterator itr = inherited::begin();
	while(itr != inherited::end() && **itr != r) {
		++itr;
	}
	inherited::erase(itr);
}

template <typename T>
typename shared_ptr_vector<T>::reference shared_ptr_vector<T>::front() {
	return operator[](0);
}

template <typename T>
typename shared_ptr_vector<T>::const_reference shared_ptr_vector<T>::front() const {
	return operator[](0);
}

template <typename T>
typename shared_ptr_vector<T>::reference 
		shared_ptr_vector<T>::operator[](shared_ptr_vector<T>::size_type n) {
	return *inherited::operator[](n);
}

template <typename T>
typename shared_ptr_vector<T>::const_reference 
		shared_ptr_vector<T>::operator[](shared_ptr_vector<T>::size_type n) const {
	return *inherited::operator[](n);
}

}

#endif

