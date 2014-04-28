/*
 * NeuroSim Library Network Header
 * Colby Horn
 */

#ifndef __NETWORK__
#define __NETWORK__

#include <istream>
#include <ostream>
#include <string>

#include "container.hpp"
#include "neuron.hpp"

namespace neuro {

class network {
friend std::ostream& operator<<(std::ostream&, network&);
friend std::istream& operator>>(std::istream&, network&);
public:
	typedef const neuron&                       const_reference;
	typedef shared_ptr_vector<neuron>::iterator iterator;
	typedef neuron&                             reference;
	typedef unsigned int                        size_type;
	typedef neuron                              value_type;
	
	void            add(int, NeuronType = INTERNAL, float = 0.0, float = 1.0);
	void            add_input(int, float = 0.0);
	void            add_internal(int, float = 1.0);
	void            add_output(int, float = 1.0);
	iterator        begin();
	void            clear();
	bool            contains(size_type) const;
	iterator        end();
	void            erase(size_type);
	void            eval_non_rec();
	iterator        inputs_begin();
	iterator        inputs_end();
	reference       operator[](size_type);
	const_reference operator[](size_type) const;
	iterator        outputs_begin();
	iterator        outputs_end();
	void            read_file(std::string);
	size_type       size() const;
	void            write_file(std::string);

private:
	shared_ptr_vector<value_type>   neurons_, inputs_, outputs_;
	shared_ptr_map<int, value_type> neuron_table_;
};

}

#endif

