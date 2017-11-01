/**********************************************************************************************************************
This file is part of the Control Toobox (https://adrlab.bitbucket.io/ct), copyright by ETH Zurich, Google Inc.
Authors:  Michael Neunert, Markus Giftthaler, Markus Stäuble, Diego Pardo, Farbod Farshidian
Licensed under Apache2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#define EIGEN_INITIALIZE_MATRICES_BY_NAN

#include <ct/optcon/optcon-prespec.h>
#include <gtest/gtest.h>

#include <cmath>
#include <random>

#include "ConstraintTest.h"

using namespace ct::optcon::example;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}