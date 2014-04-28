/*
 * NeuroSim Library Neuron Header
 * Colby Horn
 */

#ifndef __NEURON__
#define __NEURON__

#include <ostream>
#include <string>

#include "container.hpp"
#include "synapse.hpp"

namespace neuro {

enum NeuronType {
	INTERNAL = 0,
	INPUT    = 1,
	OUTPUT   = 2
};

inline std::string getNeuronTypeText(const NeuronType& type) {
	std::string text[] = {"INTERNAL", "INPUT", "OUTPUT"};
	return text[type];
}

class neuron {
friend std::ostream& operator<<(std::ostream&, const neuron&);
public:
	typedef const synapse&                       const_reference;
	typedef shared_ptr_vector<synapse>::iterator iterator;
	typedef synapse&                             reference;
	typedef unsigned int                         size_type;
	typedef synapse                              value_type;
	
	neuron(int, NeuronType = INTERNAL, float = 0.0, float = 0.0);
	
	float           activation() const;
	void            activation(float);
	float           bias() const;
	iterator        begin();
	void            connect(neuron&, float = 1.0);
	void            disconnect(neuron&);
	float           eval();
	iterator        end();
	int             id() const;
	reference       operator[](size_type);
	const_reference operator[](size_type) const;
	bool            operator==(const neuron&) const;
	bool            operator!=(const neuron&) const;
	iterator        outputs_begin();
	iterator        outputs_end();
	size_type       size() const;
	std::string     to_string() const;
	NeuronType      type() const;
	
private:
	int                             id_;
	NeuronType                      type_;
	float                           activation_, bias_;
	shared_ptr_vector<value_type>   inputs_, outputs_;
	shared_ptr_map<int, value_type> inputs_table_, outputs_table_;
};

}

#endif

