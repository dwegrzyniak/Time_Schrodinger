#include "wave.hpp"

//0.9 0.92 0.94 0.95 0.96 0.98 1 1.02 1.04 1.05 1.06 1.08 1.1

int main() {
	wave wav(100, 1, 1.1 * 1.5 * M_PI * M_PI, 0.0001, 500000); //n, kappa, omega, delta_tau, kroki czasowe
	wav.set_init_psi();
	wav.set_H_imag(0);
	wav.set_H_real(0);
	
	wav.simulation();

return 0;
}
