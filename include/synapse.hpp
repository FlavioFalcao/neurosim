/*
 * NeuroSim Library Synapse Header
 * Colby Horn
 */

#ifndef __SYNAPSE__
#define __SYNAPSE__

#include <ostream>
#include <string>

namespace neuro {

class neuron;

class synapse {
friend std::ostream& operator<<(std::ostream&, const synapse&);

public:
	typedef const neuron& const_reference;
	typedef neuron&       reference;
	typedef unsigned char size_type;
	typedef neuron        value_type;
	
	synapse(reference, float, reference);
	
	reference       destination();
	const_reference destination() const;
	reference       operator[](size_type);
	const_reference operator[](size_type) const;
	bool            operator==(const synapse&) const;
	bool            operator!=(const synapse&) const;
	size_type       size() const;
	reference       source();
	const_reference source() const;
	std::string     to_string() const;
	float           weight() const;
	void            weight(float);

private:
	reference source_;
	float     weight_;
	reference destination_;
};

}

#endif

