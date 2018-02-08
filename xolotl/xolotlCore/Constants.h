/*
 * Constants.h
 *
 *  Created on: May 6, 2013
 *      Author: bkj
 */

#include <memory>

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace xolotlCore {

//! Definitions of fundamental constants used in Xolotl

//! The Boltzmann constant in units of eV K^-1.
static const double kBoltzmann = 8.61733240000000000E-5;

//! Pi, taken from "100000 digits of Pi,"
//! at http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
static const double pi = 3.1415926535897932;

//! Lattice Parameter. Equal to 3.17 Angstroms, taken from Becquart et. al.
//! Journal of Nuclear Materials 403 (2010) 75–88. Given in units here of nm.
<<<<<<< HEAD
<<<<<<< HEAD
static const double tungstenLatticeConstant = 0.31700000000000000;

//! Lattice Parameter. Given in units here of nm.
static const double uraniumDioxydeLatticeConstant = 0.57400000000000000;

// Tungsten heat coefficient = lambda / (rho * C) in nm2 s-1
static const double tungstenHeatCoefficient = 6.835e13;

// UO2 heat coefficient = lambda / (rho * C) in nm2 s-1
static const double uo2HeatCoefficient = 0.0;

/**
 * Statically defined type names. This are used to optimize the lookup
 * calls in the maps so that new strings are not constantly created
 * dynamically. It accounts for a small but significant amount of
 * performance.
 */
static const std::string heType = "He";
static const std::string vType = "V";
static const std::string iType = "I";
static const std::string heVType = "HeV";
static const std::string heIType = "HeI";
static const std::string xeType = "Xe";
static const std::string xeVType = "XeV";
static const std::string xeIType = "XeI";
static const std::string NESuperType = "NESuper";
static const std::string PSISuperType = "PSISuper";
=======
static const double latticeConstant = 0.31700000000000000;
>>>>>>> Branch that is taking an HDF5 file as an input file. SB 20140520
=======
static const double latticeConstant = 0.31700000000000000;
>>>>>>> 25158eb3dae5d6f4f75d40ecf0714480753961f7

/**
 * Statically defined type names. This are used to optimize the lookup
 * calls in the maps so that new strings are not constantly created
 * dynamically. It accounts for a small but significant amount of
 * performance.
 */
static const std::string heType = "He";
static const std::string vType = "V";
static const std::string iType = "I";
static const std::string heVType = "HeV";
static const std::string heIType = "HeI";

} /* end namespace xolotlCore */
#endif /* CONSTANTS_H_ */
