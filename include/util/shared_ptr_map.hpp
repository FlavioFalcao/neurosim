/*
 * NeuroSim Library Shared Pointer Map
 * Colby Horn
 */

#ifndef __SHARED_PTR_MAP__
#define __SHARED_PTR_MAP__

#include <memory>
#include <map>
#include <stdexcept>

namespace neuro {

template <typename K, typename V>
class shared_ptr_map : public std::map<K, std::shared_ptr<V> > {
private:
	typedef std::map<K, std::shared_ptr<V> > inherited;
	
public:
	typedef const V&                        const_reference;
	typedef K                               key_type;
	typedef V&                              reference;
	
	// TODO update mapped_type interface to hide std::shared_ptr as raw *
	typedef typename inherited::mapped_type mapped_type;
	
	reference       at(const key_type&);
	const_reference at(const key_type&) const;
	bool            contains(const key_type&) const;
	void            erase(const key_type&);
	void            insert(const key_type&, const mapped_type&);
	reference       operator[](const key_type&);
	const_reference operator[](const key_type&) const;
};

template <typename K, typename V>
typename shared_ptr_map<K, V>::reference 
		shared_ptr_map<K, V>::at(const shared_ptr_map<K, V>::key_type& k) {
	if (contains(k)) {
		return *inherited::at(k);
	} else {
		throw std::out_of_range("shared_ptr_map::at: key out of range");
	}
}

template <typename K, typename V>
typename shared_ptr_map<K, V>::const_reference 
		shared_ptr_map<K, V>::at(const shared_ptr_map<K, V>::key_type& k) const {
	if (contains(k)) {
		return *inherited::at(k);
	} else {
		throw std::out_of_range("shared_ptr_map::at: key out of range");
	}
}

template <typename K, typename V>
bool shared_ptr_map<K, V>::contains(const shared_ptr_map<K, V>::key_type& k) const {
	return inherited::find(k) != inherited::end();
}

template <typename K, typename V>
void shared_ptr_map<K, V>::erase(const shared_ptr_map<K, V>::key_type& k) {
	inherited::erase(k);
}

template <typename K, typename V>
void shared_ptr_map<K, V>::insert(const shared_ptr_map<K, V>::key_type& k, 
		const shared_ptr_map<K, V>::mapped_type& v) {
	inherited::operator[](k) = v;
}

template <typename K, typename V>
typename shared_ptr_map<K, V>::reference 
		shared_ptr_map<K, V>::operator[](const shared_ptr_map<K, V>::key_type& k) {
	return *inherited::operator[](k);
}

template <typename K, typename V>
typename shared_ptr_map<K, V>::const_reference 
		shared_ptr_map<K, V>::operator[](const shared_ptr_map<K, V>::key_type& k) const {
	return *inherited::operator[](k);
}

}

#endif

