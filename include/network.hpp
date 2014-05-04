/*
 * NeuroSim Library Network Header
 * Colby Horn
 */

#ifndef __NETWORK__
#define __NETWORK__

#include <istream>
#include <ostream>
#include <string>

#include "neuron.hpp"
#include "util/shared_ptr_map.hpp"
#include "util/shared_ptr_vector.hpp"

namespace neuro {

class network {
friend std::ostream& operator<<(std::ostream&, network&);
friend std::istream& operator>>(std::istream&, network&);
public:
	typedef const neuron&                               const_reference;
	typedef iterable_wrapper<shared_ptr_vector<neuron>> iterable;
	typedef shared_ptr_vector<neuron>::iterator         iterator;
	typedef neuron&                                     reference;
	typedef unsigned int                                size_type;
	typedef neuron                                      value_type;
	
	network();
	
	void            add(int, neuron::connection_type = neuron::INTERNAL, float = 0.0, float = 1.0);
	void            add_input(int, float = 0.0);
	void            add_internal(int, float = 1.0);
	void            add_output(int, float = 1.0);
	iterator        begin();
	void            clear();
	bool            contains(size_type) const;
	iterator        end();
	void            erase(size_type);
	void            eval_non_rec();
	iterable&       inputs();
	const iterable& inputs() const;
	reference       operator[](size_type);
	const_reference operator[](size_type) const;
	iterable&       outputs();
	const iterable& outputs() const;
	void            read_file(std::string);
	size_type       size() const;
	void            write_file(std::string);
	
private:
	shared_ptr_vector<value_type>   neurons_, inputs_, outputs_;
	shared_ptr_map<int, value_type> neuron_table_;
	iterable                        inputs_iterable_, outputs_iterable_;
};

}

#endif

