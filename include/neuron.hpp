/*
 * NeuroSim Library Neuron Header
 * Colby Horn
 */

#ifndef __NEURON__
#define __NEURON__

#include <ostream>
#include <string>

#include "synapse.hpp"
#include "util/iterable_wrapper.hpp"
#include "util/shared_ptr_map.hpp"
#include "util/shared_ptr_vector.hpp"

namespace neuro {

class neuron {
friend std::ostream& operator<<(std::ostream&, const neuron&);
public:
	typedef const synapse&                               const_reference;
	typedef iterable_wrapper<shared_ptr_vector<synapse>> iterable;
	typedef shared_ptr_vector<synapse>::iterator         iterator;
	typedef synapse&                                     reference;
	typedef unsigned int                                 size_type;
	typedef synapse                                      value_type;
	
	enum connection_type {
		INTERNAL = 0,
		INPUT    = 1,
		OUTPUT   = 2
	};
	
	neuron(int, connection_type = INTERNAL, float = 0.0, float = 0.0);
	
	float           activation() const;
	void            activation(float);
	float           bias() const;
	iterator        begin();
	void            connect(neuron&, float = 1.0);
	void            disconnect(neuron&);
	float           eval();
	iterator        end();
	int             id() const;
	iterable&       inputs();
	const iterable& inputs() const;
	
	// TODO implement correct indexing by source/destination id
	//reference       operator[](size_type);
	//const_reference operator[](size_type) const;
	
	bool            operator==(const neuron&) const;
	bool            operator!=(const neuron&) const;
	iterable&       outputs();
	const iterable& outputs() const;
	size_type       size() const;
	std::string     to_string() const;
	connection_type type() const;
	
private:
	int                             id_;
	connection_type                 type_;
	float                           activation_, bias_;
	shared_ptr_vector<value_type>   inputs_, outputs_;
	shared_ptr_map<int, value_type> inputs_table_, outputs_table_;
	iterable                        inputs_iterable_, outputs_iterable_;
};

inline std::string to_string(const neuron::connection_type& type) {
	std::string text[] = {"INTERNAL", "INPUT", "OUTPUT"};
	return text[type];
}

}

#endif

