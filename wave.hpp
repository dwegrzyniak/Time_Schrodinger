#ifndef _wave_hpp_
#define _wave_hpp_

#include <iostream>
#include <fstream>
#include <cmath>

class wave {
public:
	wave(int n_, double kappa_, double omega_, double delta_tau_, int time_steps_);
	void set_init_psi();
	void set_H_real(double time_step);
	void set_H_imag(double time_step);
	void psi_step();
	void print_outfile_data();
	void print_datfile_data();
	void simulation();
	
	
protected:
	std::ofstream datFile;
	std::ofstream outFile;

	int N, time_steps;
	double kappa, omega;
	double x_min = 0., x_max = 1., n = 1.;
	double delta_x;
	double *psi_real, *psi_imag;
	double *H_real, *H_imag;
	double tau, delta_tau;
};


#endif
