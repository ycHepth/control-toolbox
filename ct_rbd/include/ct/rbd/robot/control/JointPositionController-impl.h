/**********************************************************************************************************************
This file is part of the Control Toobox (https://adrlab.bitbucket.io/ct), copyright by ETH Zurich, Google Inc.
Authors:  Michael Neunert, Markus Giftthaler, Markus Stäuble, Diego Pardo, Farbod Farshidian
Licensed under Apache2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#pragma once

namespace ct {
namespace rbd {

template <size_t NJOINTS>
JointPositionController<NJOINTS>* JointPositionController<NJOINTS>::clone() const
{
    throw std::runtime_error("RBD: JointPositionController.h, clone() not implemented");
};

template <size_t NJOINTS>
JointPositionController<NJOINTS>::~JointPositionController()
{
}

template <size_t NJOINTS>
JointPositionController<NJOINTS>::JointPositionController(const Eigen::Matrix<double, NJOINTS, 1>& desiredPosition,
    const Eigen::Matrix<double, NJOINTS, 1>& desiredVelocity,
    const std::vector<core::PIDController::parameters_t>& parameters)
{
    assert(parameters.size() == NJOINTS);

    for (size_t i = 0; i < NJOINTS; i++)
    {
        jointControllers_.push_back(core::PIDController(
            parameters[i], core::PIDController::setpoint_t(desiredPosition(i), desiredVelocity(i))));
    }
}

template <size_t NJOINTS>
JointPositionController<NJOINTS>::JointPositionController(const Eigen::Matrix<double, NJOINTS, 1>& desiredPosition,
    const Eigen::Matrix<double, NJOINTS, 1>& desiredVelocity,
    const core::PIDController::parameters_t& parameters)
{
    for (size_t i = 0; i < NJOINTS; i++)
    {
        jointControllers_.push_back(
            core::PIDController(parameters, core::PIDController::setpoint_t(desiredPosition(i), desiredVelocity(i))));
    }
}

template <size_t NJOINTS>
void JointPositionController<NJOINTS>::computeControl(const core::StateVector<STATE_DIM>& state,
    const core::Time& t,
    core::ControlVector<NJOINTS>& control)
{
    ct::rbd::JointState<NJOINTS> jstate(state);

    for (size_t i = 0; i < NJOINTS; i++)
    {
        control(i) = jointControllers_[i].computeControl(jstate.getPosition(i), jstate.getVelocity(i), t);
    }
}

template <size_t NJOINTS>
void JointPositionController<NJOINTS>::setDesiredPosition(const Eigen::Matrix<double, NJOINTS, 1>& desiredPosition)
{
    for (size_t i = 0; i < NJOINTS; i++)
    {
        jointControllers_[i].setDesiredState(desiredPosition(i));
    };
}

template <size_t NJOINTS>
void JointPositionController<NJOINTS>::setDesiredPosition(double desiredPosition, int jointId)
{
    assert(0 <= jointId && jointId < NJOINTS);  // assuming first joint has index 0

    jointControllers_[jointId].setDesiredState(desiredPosition);
}

template <size_t NJOINTS>
void JointPositionController<NJOINTS>::setAllPIDGains(double kp, double ki, double kd)
{
    PIDController::parameters_t parameters;
    parameters.k_p = kp;
    parameters.k_i = ki;
    parameters.k_d = kd;

    for (size_t i = 0; i < NJOINTS; i++)
    {
        jointControllers_[i].changeParameters(parameters);
    }
}

template <size_t NJOINTS>
void JointPositionController<NJOINTS>::reset()
{
    for (size_t i = 0; i < NJOINTS; i++)
    {
        jointControllers_[i].reset();
    }
}


}  // namespace rbd
}  // namespace ct