/*
 * NeuroSim Library Neuron Source
 * Colby Horn
 */

#include <sstream>
#include <stdexcept>

#include "neuron.hpp"

using namespace std;

namespace neuro {

neuron::neuron(int id, neuron::connection_type type, float activation, float bias) : 
		id_(id), type_(type), activation_(activation), bias_(bias), 
		inputs_iterable_(inputs_), outputs_iterable_(outputs_) {}

float neuron::activation() const { return activation_; }

void neuron::activation(float activation) {
	if (type() == INPUT) {
		this->activation_ = activation;
	} else {
		throw runtime_error("neuron::activation: neuron::type != INPUT");
	}
}

float neuron::bias() const { return bias_; }

neuron::iterator neuron::begin() { return inputs().begin(); }

void neuron::connect(neuron& target, float weight) {
	if (type() != OUTPUT) {
		if (!outputs_table_.contains(target.id())) {
			
			// TODO update declaration/initialization with shared_ptr_vector/shared_ptr_map update
			shared_ptr<synapse> s(new synapse(*this, weight, target));
			
			this->outputs_.push_back(s);
			this->outputs_table_.insert(target.id(), s);
			target.inputs_.push_back(s);
			target.inputs_table_.insert(this->id(), s);
		} else {
			throw runtime_error("neuron::connect: neuron with id = " + 
					std::to_string(this->id()) + " already connected to neuron with id = " + 
					std::to_string(target.id()));
		}
	} else {
		throw runtime_error("neuron::connect: neuron::type == OUTPUT");
	}
}

void neuron::disconnect(neuron& target) {
	if (type() != OUTPUT) {
		if (outputs_table_.contains(target.id())) {
			synapse& s = outputs_table_[target.id()];
			this->outputs_.erase(s);
			this->outputs_table_.erase(target.id());
			target.inputs_.erase(s);
			target.inputs_table_.erase(this->id());
		} else {
			throw runtime_error("neuron::disconnect: neuron with id = " + 
					std::to_string(this->id()) + " is not connected to neuron with id = " + 
					std::to_string(target.id()));
		}
	} else
		throw runtime_error("neuron::disconnect: neuron::type == OUTPUT");
}

float neuron::eval() {
	if (type() != INPUT) {
		activation_ = bias();
		for (iterator synapse = begin(); 
				synapse != end(); ++synapse)
			activation_ += synapse->weight() * 
					synapse->source().activation();
	}
	return activation_;
}

neuron::iterator neuron::end() { return inputs().end(); }

int neuron::id() const { return id_; }

neuron::iterable& neuron::inputs() { return inputs_iterable_; }
const neuron::iterable& neuron::inputs() const { return inputs_iterable_; }

// TODO implement correct indexing by source/destination id
//neuron::reference neuron::operator[](neuron::size_type n) { return inputs_[n]; }
//neuron::const_reference neuron::operator[](neuron::size_type n) const { return inputs_[n]; }

bool neuron::operator==(const neuron& n) const { return id() == n.id(); }
bool neuron::operator!=(const neuron& n) const { return !(*this == n); }


ostream& operator<<(ostream& stream, const neuron& neuron) {
	return stream << "neuron(id = " << neuron.id() << ", type = " << to_string(neuron.type()) <<
			", activation = " << neuron.activation() << ", bias = " << neuron.bias() << ")";
}

neuron::iterable& neuron::outputs() { return outputs_iterable_; }
const neuron::iterable& neuron::outputs() const { return outputs_iterable_; }

neuron::size_type neuron::size() const { return inputs().size(); }

string neuron::to_string() const {
	ostringstream stream;
	stream << *this;
	return stream.str();
}

neuron::connection_type neuron::type() const { return type_; }

}

