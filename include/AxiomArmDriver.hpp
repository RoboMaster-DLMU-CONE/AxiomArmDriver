#ifndef AXIOMARMDRRIVER_HPP
#define AXIOMARMDRRIVER_HPP

#include <HyPWM/PWMController.hpp>

#include <array>

class AxiomArmDriver
{
public:
    using Result = std::expected<void, std::string>;
    AxiomArmDriver(AxiomArmDriver&) = delete;
    AxiomArmDriver(const AxiomArmDriver&&) = delete;
    AxiomArmDriver& operator=(AxiomArmDriver&) = delete;
    AxiomArmDriver& operator=(const AxiomArmDriver&&) = delete;
    static AxiomArmDriver& getInstance();
    [[nodiscard]] Result enable(uint8_t joint) const noexcept;
    [[nodiscard]] Result disable(uint8_t joint) const noexcept;
    [[nodiscard]] Result rotate(uint8_t joint, double angle) const noexcept;

private:
    AxiomArmDriver();
    std::array<std::unique_ptr<HyPWM::PWMController>, 6> joints{};
};

#endif //AXIOMARMDRRIVER_HPP
