#ifndef ISING_CORE_SIMULATION_H_
#define ISING_CORE_SIMULATION_H_

#include <iostream>
#include <vector>

#include "core/ising.h"
#include "core/ising-2d.h"
#include "core/parameter.h"

// "Windows.h" should be put after "rapidjson/document.h".
// See https://github.com/Tencent/rapidjson/issues/766
//     http://blog.csdn.net/u011519892/article/details/16985239
#include "core/timing.h"

ISING_NAMESPACE_BEGIN

// Each cell will be initialized with the same parameters (size, T, H).
// Repeat the evaluation for `repetitions` times for calculating deviation etc.
class SimulationUnit
{
public:
    SimulationUnit() = default;
    SimulationUnit(const size_t & repetitions, const size_t & lattice_size);
    
    void Run(const double & temperature, const double & magnetic_h,
        const size_t & iterations, const size_t & n_ensemble, const size_t & n_delta);
    inline std::vector<Observable> Result() { return result_list_; }

private:
    std::vector<Ising2D_PBC> eval_list_;
    std::vector<Observable>  result_list_;
};

class Simulation
{
public:
    Simulation() = default;
    Simulation(const Parameter & param);

    int Run();

private:
    // Parameters and parameter lists.
    const std::vector<size_t> size_list_;
    const std::vector<double> temperature_list_;
    const std::vector<double> magnetic_h_list_;
    const size_t              iterations_;
    const size_t              n_ensemble_;
    const size_t              n_delta_;
    const size_t              repetitions_;

    // The size (length) of `size_list_`
    const size_t size_list_size_;
    // The dimension of T * B
    const size_t eval_cell_num_;

    // 1st dimension: size
    // 2nd dimension: T * B
    // 3rd dimension (in `SimulationUnit`): repetition
    std::vector<std::vector<SimulationUnit>> eval_list_;

    // 1st dimension: size
    // 2nd dimension: T * B
    // 3rd dimension: repetition
    std::vector<std::vector<std::vector<Observable>>> result_list_;
    
    void Simulate();
    void PrintParameters(std::ostream & os);
    void PrintResults(std::ostream & os);
};

// Interface.
int RunSimulation(const Parameter & param);

ISING_NAMESPACE_END

#endif
