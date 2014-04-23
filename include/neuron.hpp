/*
 * NeuroSim Library Neuron Header
 * Colby Horn
 */

#ifndef __Neuron__
#define __Neuron__

#include <ostream>
#include <string>
#include <vector>

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

class Neuron {
friend std::ostream& operator<<(std::ostream&, const Neuron&);
public:
	typedef std::vector<Synapse*>::iterator iterator;
	Neuron(int = 0, NeuronType = INTERNAL, float = 0.0, float = 0.0);
	int        getId() const;
	NeuronType getType() const;
	float      getActivation() const;
	void       setActivation(float);
	float      evalActivation();
	float      getBias() const;
	iterator   inputs_begin();
	iterator   inputs_end();
	iterator   outputs_begin();
	iterator   outputs_end();
	void       connect(Neuron*, float);
	void       disconnect(Neuron*);
private:
	int                   id;
	NeuronType            type;
	float                 activation, bias;
	std::vector<Synapse*> inputs, outputs;
};

}

#endif

