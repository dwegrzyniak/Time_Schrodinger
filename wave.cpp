#include "wave.hpp"

using namespace std;

wave::wave(int n_, double kappa_, double omega_, double delta_tau_, int time_steps_){
	N = n_;
	time_steps = time_steps_;
	
	kappa = kappa_;
	omega = omega_;
	delta_tau = delta_tau_;
	
	delta_x = 1./N;
	
	this -> psi_imag = new double[N + 1];
	this -> psi_real = new double[N + 1];
	this -> H_imag = new double[N + 1];
	this -> H_real = new double[N + 1];
	
	outFile.open("out110.out");
	datFile.open("dat110.dat");
}

void wave::simulation(){
	
	for (int i = 0; i < time_steps; i++){
		psi_step();
		print_outfile_data();
	}
	
}

void wave::set_init_psi(){
	for (int i = 0; i < N + 1; i++){
		psi_real[i] = sqrt(2) * sin(n * M_PI * delta_x * i);
		psi_imag[i] = 0;
		
	}
	
	
}

void wave::set_H_real(double time_step){
	double tmp_tau = tau + time_step;
	
	
	H_real[0] = 0;
	H_real[N + 1] = 0;

	for (int i = 1; i < N; i++){
		
		H_real[i] = -0.5 * ((psi_real[i+1] + psi_real[i-1] - 2 * psi_real[i])/(delta_x * delta_x)) + kappa * (delta_x * i - 0.5) * psi_real[i] * sin(omega * tmp_tau);		
	}
}

void wave::set_H_imag(double time_step){
	double tmp_tau = tau + time_step;
	H_imag[0] = 0;
	H_imag[N + 1] = 0;
	
	for (int i = 1; i < N; i++){
		
		H_imag[i] = -0.5 * ((psi_imag[i+1] + psi_imag[i-1] - 2 * psi_imag[i])/(delta_x * delta_x)) + kappa * (delta_x * i - 0.5) * psi_imag[i] * sin(omega * tmp_tau);
	}
}

void wave::psi_step(){
	//psi real (tau + 0.5 * delta_tau)
	
	for (int i = 0; i < N + 1; i++){
		psi_real[i] += + H_imag[i] * delta_tau / 2;
	}
	
	//H_real (tau + 0.5 * delta_tau)
	
	set_H_real(0.5 * delta_tau);
	
	//psi imag (tau + delta_tau)
	
	for (int i = 0; i < N + 1; i++){
		psi_imag[i] += -H_real[i] * delta_tau;
	}
	
	//H_imag (tau + delta_tau)
	
	set_H_imag(delta_tau);
	
	//psi real(tau + delta_tau)
	for (int i = 0; i < N + 1; i++){
		psi_real[i] += H_imag[i] * delta_tau / 2;
	}
	
	print_outfile_data();
	
	//update tau
	tau += delta_tau;
}

void wave::print_outfile_data(){
	double NN = 0, eta = 0, xx = 0, test = 0;
	for (int i = 0; i< N + 1; i++){
		NN += delta_x * (psi_real[i] * psi_real[i] + psi_imag[i] * psi_imag[i]);
		xx += delta_x * (i * delta_x) * (psi_real[i] * psi_real[i] + psi_imag[i] * psi_imag[i]);
		eta += delta_x * (psi_real[i] * H_real[i] + psi_imag[i] * H_imag[i]);
	}
	outFile << tau << '\t' << NN << '\t' << xx << '\t' << eta << endl;
}

void wave::print_datfile_data(){
	for (int i = 0; i< N + 1; i++){
		double rho = psi_real[i] * psi_real[i] + psi_imag[i] * psi_imag[i];
		datFile << rho << '\t';
	}
	datFile << '\n';
}
