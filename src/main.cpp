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

int neuronal_threat(double impact, double severity, double probability) {
    srand(time(NULL));
    rand();

    std::vector<std::size_t> conf = {3, 5, 1}; // Configuration
    double bias = 1.0; // Define bias
    //perceptron_multilayer mp_network(&conf, bias); // Include bias in constructor
    perceptron_multilayer mp_network(reinterpret_cast<std::vector<std::size_t>*>(conf), bias);

    std::vector<double> data_threat = {impact, severity, probability};
    std::vector<double> outputs = mp_network.execute(data_threat);

    if(outputs[0] >= 0.5)
        std::cout << "High!!! l0l!! pwn3rs inna w0rld!! (High level of risk of being hacked)" << std::endl;
    else
        std::cout << "Bajo nivel de riesgo de pwn3d" << std::endl;

    return 0;
}
/*
int neuronal_xor() {
    srand(time(NULL));
    std::vector<std::size_t> conf = {2, 2, 1};
    perceptron_multilayer mp(conf, 1.0);

    std::vector<std::vector<std::vector<double>>> initial_weights;
    std::vector<std::vector<double>> hide_layer;

    std::vector<double> cell1 = {-10, -10, 15};
    std::vector<double> cell2 = {15, 15, -10};

    hide_layer.push_back(cell1);
    hide_layer.push_back(cell2);

    std::vector<std::vector<double>> outputs_layer;
    std::vector<double> outputs_cell = {10, 10, -15};

    outputs_layer.push_back(outputs_cell);
    initial_weights.push_back(hide_layer);
    initial_weights.push_back(outputs_layer);

    std::vector<double> test1 = {0, 0};
    std::cout << "0 XOR 0 : " << mp.execute(test1)[0] << std::endl;

    std::vector<double> test2 = {0, 1};
    std::cout << "0 XOR 1 : " << mp.execute(test2)[0] << std::endl;

    std::vector<double> test3 = {1, 0};
    std::cout << "1 XOR 0 : " << mp.execute(test3)[0] << std::endl;

    std::vector<double> test4 = {1, 1};
    std::cout << "1 XOR 1 : " << mp.execute(test4)[0] << std::endl;

    return 0;
}

int neuronal_or() {
    srand(time(NULL));
    rand();

    perceptron p(2);

    std::vector<double> initial_weights = {10, 10, -5};
    p.set_weights(initial_weights);

    std::vector<double> mix1 = {0, 0};
    std::cout << "0 OR 0 : " << p.execute(mix1) << std::endl;

    std::vector<double> mix2 = {1, 0};
    std::cout << "1 OR 0 : " << p.execute(mix2) << std::endl;

    std::vector<double> mix3 = {0, 1};
    std::cout << "0 OR 1 : " << p.execute(mix3) << std::endl;

    std::vector<double> mix4 = {1, 1};
    std::cout << "1 OR 1 : " << p.execute(mix4) << std::endl;

    return 0x00;
}

int neuronal_and() {
    srand(time(NULL));
    rand();

    perceptron p(2);

    std::vector<double> initial_weights = {10, 10, -15};
    p.set_weights(initial_weights);

    std::vector<double> mix1 = {0, 0};
    std::cout << "0 AND 0 : " << p.execute(mix1) << std::endl;

    std::vector<double> mix2 = {1, 0};
    std::cout << "1 AND 0 : " << p.execute(mix2) << std::endl;

    std::vector<double> mix3 = {0, 1};
    std::cout << "0 AND 1 : " << p.execute(mix3) << std::endl;

    std::vector<double> mix4 = {1, 1};
    std::cout << "1 AND 1 : " << p.execute(mix4) << std::endl;

    return 0x00;
}

*/
