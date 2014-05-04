/*
 * NeuroSim Library Iterable Wrapper
 * Colby Horn
 */

#ifndef __ITERABLE_WRAPPER__
#define __ITERABLE_WRAPPER__

namespace neuro {

template <typename T>
class iterable_wrapper {
public:
	// TODO add const iteration support
	//typedef typename T::const_iterator  const_iterator;
	
	typedef typename T::iterator        iterator;
	typedef typename T::size_type       size_type;
	
	iterable_wrapper(T&);
	
	iterator        begin();
	iterator        end();
	size_type       size() const;
	
private:
	T& container_;
};

template<typename T>
iterable_wrapper<T>::iterable_wrapper(T& container) : container_(container) {}

template<typename T>
typename iterable_wrapper<T>::iterator iterable_wrapper<T>::begin() { return container_.begin(); }

template<typename T>
typename iterable_wrapper<T>::iterator iterable_wrapper<T>::end() { return container_.end(); }

template<typename T>
typename iterable_wrapper<T>::size_type iterable_wrapper<T>::size() const {
	return container_.size();
}

}

#endif

