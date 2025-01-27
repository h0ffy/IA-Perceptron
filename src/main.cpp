#include "perceptron.h"
#include <iostream> 
#include <cstdlib>
#include <string>
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
    //neuronal_and();
    //neuronal_or();
    //neuronal_xor();

    if(argc != 4) {
        std::cerr << "Invalid arguments: paerceptron <impact> <severity> <probability>" << std::endl;
        std::cerr << "Invalid arguments: paerceptron 0.4 0.5 0.7" << std::endl;
        return 1;
    }

    try {
        double impact = std::stod(argv[1]);
        double severity = std::stod(argv[2]);
        double probability = std::stod(argv[3]);
        std::cout << "Impact: " << impact << std::endl;
        std::cout << "Severity: " << severity << std::endl;
        std::cout << "Probability: " << probability << std::endl;
    } catch (...) { // Fix catch block syntax
        std::cerr << "Error in arguments" << std::endl;
        return 0;
    }

    std::cout << "Start test to..." << std::endl;
    neuronal_threat(impact, severity, probability);

    return 0;
}

// Add return type and fix the function name
int neuronal_threat(double impact, double severity, double probability) {
    srand(time(NULL));
    rand();

    std::vector<std::size_t> conf;
    conf.push_back(3); // 3 entradas (impact,probability,severity)
    conf.push_back(5); // 5 neuronas en la capa oculta que seran las que daran "inteligencia"
    conf.push_back(1); // posbilidad si 1 o 0 no y 0.01 -> 1.00  gradualmente de no a si

    std::vector<std::vector<std::vector<double>>> initial_weights; // pesos iniciales
    std::vector<std::vector<double>> hide_layer[5]; // capa oculta    
    perceptron_multilayer mp_network(conf);
    std::vector<double> data_threat;
    data_threat.push_back(impact); // 0.4 impacto
    data_threat.push_back(severity); // 0.4 severidad o dificultad
    data_threat.push_back(probability); // 0.8 probabilidad
    
    std::vector<double> outputs = mp_network.execute(data_threat);

    if(outputs[0] >= 0.5)
        std::cout << "High!!! l0l!! pwn3rs inna w0rld!! (High level of risk of being hacked)" << std::endl;
    else
        std::cout << "Bajo nivel de riesgo de pwn3d" << std::endl;

    return 0; // Ensure every non-void function returns a value
}


int neuronal_xor() {
    srand(time(NULL));
    std::vector<std::size_t> conf; 
        conf.push_back(2);  // in layer 1
        conf.push_back(2);  // in layer 2
        conf.push_back(1);  // sigmode value
    perceptron_multilayer mp(conf); // AND, OR, NOT

    std::vector<std::vector<std::vector<double>>> initial_weights; // pesos iniciales
    std::vector<std::vector<double>> hide_layer; // capa oculta

    std::vector<double> cell1;  // neurona1
        cell1.push_back(-10);
        cell1.push_back(-10);
        cell1.push_back(15);

    std::vector<double> cell2;  // neurona2
        cell2.push_back(15);
        cell2.push_back(15);
        cell2.push_back(-10);


    hide_layer.push_back(cell1);
    hide_layer.push_back(cell2);

    std::vector<std::vector<double>> outputs_layer; // capa de salida
    std::vector<double> outputs_cell;               // neurona de salida
        outputs_cell.push_back(10);
        outputs_cell.push_back(10);
        outputs_cell.push_back(-15);
    
    outputs_layer.push_back(outputs_cell);
    initial_weights.push_back(hide_layer);
    initial_weights.push_back(outputs_layer);


    std::vector<double> test1;
    test1.push_back(0);
    test1.push_back(0);
    std::cout << "0 XOR 0 : " << mp.execute(test1)[0] << std::endl;

    std::vector<double> test2;
    test2.push_back(0);
    test2.push_back(1);
    std::cout << "0 XOR 1 : " << mp.execute(test2)[0] << std::endl;


    std::vector<double> test3;
    test3.push_back(1);
    test3.push_back(0);
    std::cout << "1 XOR 0 : " << mp.execute(test3)[0] << std::endl;


    
    std::vector<double> test4;
    test4.push_back(1);
    test4.push_back(1);
    std::cout << "1 XOR 1 : " << p.execute(test4)[0] << std::endl;


    return(0);



}

int neuronal_or() {
    srand(time(NULL));
    rand();

    perceptron p(2);

    std::vector<double>initial_weights;
    initial_weights.push_back(10); // value
    initial_weights.push_back(10); // value
    initial_weights.push_back(-5); // only change this value (ES: el valor de sesgo es el unico cambio entre neuronal_or y neuronal_and)
    p.set_weights(initial_weights);


    std::vector<double> mix1;
    mix1.push_back(0);
    mix1.push_back(0);
    std::cout << "0 OR 0 : " << p.execute(mix1) << std::endl;

    std::vector<double> mix2;
    mix2.push_back(1);
    mix2.push_back(0);
    std::cout << "1 OR 0 : " << p.execute(mix2) << std::endl;

    std::vector<double> mix3;
    mix2.push_back(0);
    mix2.push_back(1);
    std::cout << "0 OR 1 : " << p.execute(mix3) << std::endl;


    std::vector<double> mix4;
    mix2.push_back(1);
    mix2.push_back(1);
    std::cout << "1 OR 1 : " << p.execute(mix4) << std::endl;


    return(0x00);
    


}

int neuronal_and() {
    srand(time(NULL));
    rand();

    perceptron p(2);

    std::vector<double>initial_weights;
    initial_weights.push_back(10);   // valo entrada
    initial_weights.push_back(10);   // valor entrada
    initial_weights.push_back(-15);  // only change this value (ES: el valor de sesgo es el unico cambio entre neuronal_or y neuronal_and)

    p.set_weights(initial_weights);


    std::vector<double> mix1;
    mix1.push_back(0);
    mix1.push_back(0);
    std::cout << "0 AND 0 : " << p.execute(mix1) << std::endl;

    std::vector<double> mix2;
    mix2.push_back(1);
    mix2.push_back(0);
    std::cout << "1 AND 0 : " << p.execute(mix2) << std::endl;

    std::vector<double> mix3;
    mix2.push_back(0);
    mix2.push_back(1);
    std::cout << "0 AND 1 : " << p.execute(mix3) << std::endl;


    std::vector<double> mix4;
    mix2.push_back(1);
    mix2.push_back(1);
    std::cout << "1 AND 1 : " << p.execute(mix4) << std::endl;

    return(0x00);
    
}
