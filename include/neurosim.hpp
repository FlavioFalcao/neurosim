/*
 * NeuroSim Complete Library Header
 * Colby Horn
 */

#ifndef __NeuroSim__
#define __NeuroSim__

template <typename T>
T& dereference(T* pointer)  { return *pointer; }

#include "network.hpp"
#include "neuron.hpp"
#include "synapse.hpp"

#endif

