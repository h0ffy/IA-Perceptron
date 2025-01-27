#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>
#include <numeric>
#include <cstddef>  // Add this for size_t

class perceptron {
public:
    perceptron(std::size_t n_inputs, double bias = 1.0); // Remove extra qualification
    ~perceptron();
    double execute(std::vector<double> inputs_data);
    void set_weights(std::vector<double> initial_weights);
    double activation_function(double x);
    double sigmoide(double x);
    std::vector<double> weights;
    double bias;
};

class perceptron_multilayer {
public:
    std::vector<std::vector<perceptron>> network;   //  Estructura de network
    std::vector<size_t> layers;                     //  Capa
    std::vector<std::vector<double>> values;        //  Replicar estructura de network
    std::vector<std::vector<double>> d;
    double bias;
    perceptron_multilayer(std::vector<std::size_t> layers, double bias); // Add constructor definition
    ~perceptron_multilayer();
    double retro(std::vector<double> x, std::vector<double> y);
    std::vector<double> execute(std::vector<double> weights); // Fix function signature
    void set_weights(std::vector<std::vector<std::vector<double>>> initial_weights);
};
