#include "AxiomArmDriver.hpp"

#include <cmath>

using HyPWM::PWMController;
using std::make_unique;

AxiomArmDriver::AxiomArmDriver()
{
    joints[0] = make_unique<PWMController>(0, 0);
    joints[1] = make_unique<PWMController>(0, 1);
    joints[2] = make_unique<PWMController>(0, 2);
    joints[3] = make_unique<PWMController>(1, 0);
    joints[4] = make_unique<PWMController>(1, 1);
    joints[5] = make_unique<PWMController>(1, 2);
    for (const auto& joint : joints)
    {
        if (const auto result = joint->exportPWM(); !result)
        {
            throw std::runtime_error(result.error());
        }
        if (const auto result = joint->setPeriod(20000); !result)
        {
            throw std::runtime_error(result.error());
        }
    }
}

AxiomArmDriver& AxiomArmDriver::getInstance()
{
    static AxiomArmDriver instance_;
    return instance_;
}

AxiomArmDriver::Result AxiomArmDriver::enable(const uint8_t joint) const noexcept
{
    return joints[joint]->enable();
}

AxiomArmDriver::Result AxiomArmDriver::disable(const uint8_t joint) const noexcept
{
    return joints[joint]->disable();
}

AxiomArmDriver::Result AxiomArmDriver::rotate(const uint8_t joint, const double angle) const noexcept
{
    constexpr double min_angle_deg = 0.0;
    constexpr double max_angle_deg = 180.0;
    constexpr double min_pulse_width_ns = 500.0;
    constexpr double max_pulse_width_ns = 2500.0;

    const double clamped_angle = std::clamp(angle, min_angle_deg, max_angle_deg);
    const double pulse_width_ns = min_pulse_width_ns + (clamped_angle / max_angle_deg) * (max_pulse_width_ns -
        min_pulse_width_ns);
    const auto duty_cycle_ns = static_cast<uint32_t>(std::round(pulse_width_ns));


    return joints[joint]->setDutyCycle(duty_cycle_ns);
}
