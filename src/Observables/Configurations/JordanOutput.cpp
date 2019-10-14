/*
 * JordanOutput.cpp
 *
 *  Created on: 23/mar/2016
 *      Author: Flavio 
 */

#include <sstream>
#include "JordanOutput.h"
#include "../../Particles/JordanParticle.h"


JordanOutput::JordanOutput() : Configuration() {

}


JordanOutput::~JordanOutput() {

}


void JordanOutput::get_settings(input_file &my_inp, input_file &sim_inp) {
	Configuration::get_settings(my_inp, sim_inp);
}


std::string JordanOutput::_headers(llint step) {
	std::stringstream headers;
	
	return headers.str();
}


std::string JordanOutput::_particle(BaseParticle *p) {
	std::stringstream res;
	
	JordanParticle * me = reinterpret_cast<JordanParticle *> (p);

	res << me->get_output_string();
	
	return res.str();
}



std::string JordanOutput::_configuration(llint step) {
	stringstream conf;
	for(set<int>::iterator it = this->_visible_particles.begin(); it != this->_visible_particles.end(); it ++) {
		if(it != this->_visible_particles.begin()) conf << endl;
		BaseParticle *p = this->_config_info.particles[*it];
		conf << _particle(p);
	}
	return conf.str();
}

template class JordanOutput<float>;
template class JordanOutput<double>;

