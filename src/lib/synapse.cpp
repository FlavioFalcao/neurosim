/*
 * NeuroSim Library Synapse Source
 * Colby Horn
 */

#include <sstream>
#include <stdexcept>

#include "neuron.hpp"
#include "synapse.hpp"

using namespace std;

namespace neuro {

synapse::synapse(synapse::reference source, float weight, synapse::reference destination) : 
		source_(source), weight_(weight), destination_(destination) {}

synapse::reference synapse::destination() { return destination_; }
synapse::const_reference synapse::destination() const { return destination_; }

synapse::reference synapse::operator[](synapse::size_type index) {
	if (index == 0) {
		return source_;
	} else if (index == 1) {
		return destination_;
	} else {
		throw out_of_range("synapse::operator[]: index out of range");
	}
}

synapse::const_reference synapse::operator[](synapse::size_type index) const {
	if (index == 0) {
		return source_;
	} else if (index == 1) {
		return destination_;
	} else {
		throw out_of_range("synapse::operator[]: index out of range");
	}
}

bool synapse::operator==(const synapse& s) const {
	return source() == s.source() && weight() == s.weight() && destination() == s.destination();
}

bool synapse::operator!=(const synapse& s) const {
	return !(*this == s);
}

ostream& operator<<(ostream& stream, const synapse& synapse) {
	return stream << "synapse(source.id = " << synapse.source().id() << ", weight = " << 
			synapse.weight() << ", destination.id = " << synapse.destination().id() << ")";
}

synapse::size_type synapse::size() const { return 2; }

synapse::reference synapse::source() { return source_; }
synapse::const_reference synapse::source() const { return source_; }

string synapse::to_string() const {
	ostringstream stream;
	stream << *this;
	return stream.str();
}

float synapse::weight() const { return weight_; }
void synapse::weight(float weight) { weight_ = weight; }

}

