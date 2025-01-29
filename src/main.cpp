#include "perceptron.h"
#include <iostream> 
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
int neuronal_threat(double impact, double severity, double probability);

int main(int argc, char *argv[]) {
    double impact = 0.0;
    double severity = 0.0;
    double probability = 0.0;

    if(argc != 4) {
        std::cerr << "Invalid arguments: perceptron <impact> <severity> <probability>" << std::endl;
        std::cerr << "Invalid arguments: perceptron 0.4 0.5 0.7" << std::endl;
        return 1;
    }

    try {
        impact = std::stod(argv[1]);
        severity = std::stod(argv[2]);
        probability = std::stod(argv[3]);
        std::cout << "Impact: " << impact << std::endl;
        std::cout << "Severity: " << severity << std::endl;
        std::cout << "Probability: " << probability << std::endl;
    } catch (...) {
        std::cerr << "Error in arguments" << std::endl;
        return 0;
    }

    std::cout << "Start test to..." << std::endl;
    neuronal_threat(impact, severity, probability);

    return 0;
}

int neuronal_threat(double impact, double severity, double probability){
    srand(time(NULL));
    rand();
    std::vector<std::size_t> conf = {3, 5, 1};
    double bias = 1.0; // Define bias
    //perceptron_multilayer mp_network(&conf, bias); // Include bias in constructor
    perceptron_multilayer mp_network(&reinterpret_cast<std::vector<std::size_t>*>(conf), bias);
    std::vector<double> data_threat = {impact, severity, probability};
    std::vector<double> outputs = mp_network.execute(data_threat);

    if(outputs[0] >= 0.5){
        std::cout << "High!!! l0l!! pwn3rs inna w0rld!! (High level of risk of being hacked)" << std::endl;
    } else {
        std::cout << "Bajo nivel de riesgo de pwn3d" << std::endl;
    }

    return 0;
}
