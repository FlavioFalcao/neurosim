/*
 * NeuroSim Library Core Network Source
 * Colby Horn
 */

#include <fstream>
#include <memory>
#include <queue>
#include <sstream>
#include <stdexcept>

#include "network.hpp"

using namespace std;

namespace neuro {

network::network() : inputs_iterable_(inputs_), outputs_iterable_(outputs_) {}

void network::add(int id, neuron::connection_type type, float activation, float bias) {
	if (!contains(id)) {
	
		// TODO update declaration/initialization with shared_ptr_vector/shared_ptr_map update
		shared_ptr<neuron> n(new neuron(id, type, activation, bias));
		
		neuron_table_.insert(id, n);
		neurons_.push_back(n);
		if (n->type() == neuron::INPUT) {
			inputs_.push_back(n);
		} else if (n->type() == neuron::OUTPUT) {
			outputs_.push_back(n);
		}
	} else {
		ostringstream stream;
		stream << "network::add: <neuron id " << id << ", ...> already exists";
		throw runtime_error(stream.str());
	}
}

void network::add_input(int id, float activation) { add(id, neuron::INPUT, activation); }
void network::add_internal(int id, float bias) { add(id, neuron::INTERNAL, 0.0, bias); }
void network::add_output(int id, float bias) { add(id, neuron::OUTPUT, 0.0, bias); }

network::iterator network::begin() { return neurons_.begin(); }

void network::clear() {
	neurons_.clear();
	inputs_.clear();
	outputs_.clear();
	neuron_table_.clear();
}

bool network::contains(network::size_type id) const {
	return neuron_table_.contains(id);
}

network::iterator network::end() { return neurons_.end(); }

void network::erase(network::size_type id) {
	if (contains(id)) {
		neuron& n = neuron_table_[id];
		neuron_table_.erase(id);
		neurons_.erase(n);
		if (n.type() == neuron::INPUT) {
			inputs_.erase(n);
		} else if (n.type() == neuron::OUTPUT) {
			outputs_.erase(n);
		}
	} else {
		ostringstream stream;
		stream << "network::erase: <neuron id " << id << ", ...> does not exist";
		throw runtime_error(stream.str());
	}
}

void network::eval_non_rec() {
	queue<neuron*> frontier;
	for (iterator input = inputs().begin(); input != inputs().end(); ++input) {
		frontier.push(&*input);
	}
	while (!frontier.empty()) {
		neuron* neuron = frontier.front();
		neuron->eval();
		for (neuron::iterator child = neuron->outputs().begin(); 
				child != neuron->outputs().end(); ++child)
			frontier.push(&child->destination());
		frontier.pop();
	}
}

network::iterable& network::inputs() { return inputs_iterable_; }
const network::iterable& network::inputs() const { return inputs_iterable_; }

network::reference& network::operator[](network::size_type id) {
	return neuron_table_.at(id);
}

network::const_reference& network::operator[](network::size_type id) const {
	return neuron_table_.at(id);
}

network::iterable& network::outputs() { return outputs_iterable_; }
const network::iterable& network::outputs() const { return outputs_iterable_; }

void network::read_file(string filename) {
	ifstream stream(filename);
	clear();
	stream >> *this;
	stream.close();
}

network::size_type network::size() const {
	return neurons_.size();
}

void network::write_file(string filename) {
	ofstream stream(filename);
	stream << *this;
	stream.close();
}

}

