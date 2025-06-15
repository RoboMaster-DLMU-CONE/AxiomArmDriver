#include <AxiomArmDriver.hpp>

int main()
{
    const auto& driver = AxiomArmDriver::getInstance();
    auto _ = driver.enable(0);
    _ = driver.rotate(0, 90.0);
    _ = driver.disable(0);
    return 0;
}
