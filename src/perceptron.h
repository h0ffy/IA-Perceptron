#include <vector>
#include <numeric>


class perceptron {
public:
    perceptron::perceptron(size_t n_inputs, double bias=1.0);
    double execute(std::vector<double> inputs_data);
    void set_weights(std::vector<double> inital_weights);
    double activation_function(double x);
    double sigmoide(double x);
    std::vector<double> weights;
    double bias;

)

class perceptron_multilayer {
    public:
        std::vector<std::vector<perceptron>> network;   //  Estructura de network
        std::vector<size_t> layers;                     //  Capa
        std::vector<std::vector<double>> values;        //  Replicar estructura de network
        std::vector<std::vector<double>> d;
        double bias;
        // perceptron_multilayer(std::vector<size_t> layers);

        double perceptron_multilayer::retro(std::vector<double> x, std::vector<double> y)
        std::vector<double> perceptron::execute(std::vector<double> wieghts)
        void perceptron_multilayer::set_weights(std::vector<std::vector<std::vector<double>>> initial_weights)
        perceptron_multilayer::perceptron_multilayer(std::vector<size_t> layers, double bias)   

}