#ifndef PARAMS_H
#define PARAMS_H

#ifndef PARAMS_DEFINED

#define N_BODIES	1000
#define G			6.6743e-11
#define EPSILON		0.1
#define STEP		0.001

#endif

static const char* fileOptions[] = {
	"2_body",
	"2_body_orbit",
	"4_body",
	"galaxy"
};

static const char* solverOptions[] = {
	"ForwardEuler",
	"SemiImplicitEuler",
	"Verlet"
};

#endif