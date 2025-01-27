#include "perceptron.h"


double frand() {
    return(2.0*(double)rand() / RAND_MAX - 1.0);
    //return (double)rand() / RAND_MAX;
}


perceptron::perceptron(std::size_t n_inputs, const double bias=1.0){
    /*bias = frand();
    secuencie2.reserve(n_inputs);
    for (std::size_t i = 0; i < n_inputs; i++) {
        secuencie2.push_back(frand());
    }*/
    weights.resize(n_inputs+1);
    std::generator(weights.begin(),weights.end(),frand)
}

perceptron::~perceptron(){}
    

void perceptron::set_weights(std::vector<double> initial_weight) {
    weights = initial_weight;
}


/***
    @brief Ejecucion y ponderacion del calculao matematico
    @param inputs_data Vector double Tiene como parametro los valores de entrada que pasan a la red o no...
    @return valor de la ponderacion ya calculada
*/
double perceptron::execute(std::vector<double> inputs_data) {
    weights.push_back(bias);
    double ponderation = std::inner_product(
        inputs_data.begin(),
        inputs_data.end(),
        weights.begin(),
        ponderation 
    )
    sigmoide(ponderation);
    return(ponderation);

}


/***
    @brief Esta funcion calcula el valor sigmoide
    @param x as double valor de entrada con el valor actual
    @return valor tras el calculo sigmoide
*/
double perceptron::sigmoide(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}


/***
    @brief La multi capa creada en base a la capa principal perceptron
    @param layers an Vector std::size_t Este lleva que van a entrar a la clase multicapa
    @param bias an double Se utiliza para compensar el error
*/
perceptron_multilayer::perceptron_multilayer(std::vector<std::size_t> layers, double bias) {
    this->layers = layers;
    this->bias = bias;
    for(std::size_t i=0; i<layers.size(); i++) {
        values.push_back(std::vector<double>(layers[i], 0.0));
        network.push_back(std::vector<double>(layers[i],0.0));

        if (i > 0) {
            for(std::size_t j1=0; j1<layers[i]; j1++) {
                network[i].push_back(perceptron(layers[i-1], bias));
            }
        }

    }
}

perceptron_multilayer::~perceptron_multilayer(){}

/**
* @brief Establece pesos 
*
* @return initial_weihgts as Vector de vector a vector tipo double con los valores iniciales
*/
void perceptron_multilayer::set_weights(std::vector<std::vector<std::vector<double>>> initial_weights) {

    for(std::size_t i=0;i<weights.size();i++) {

        for(std::size_t j1=0;i<weights[i].size();j1++) {
            network[i+1][j1].set_weights(weights[i][j1]);
        }

    }
}


/***
    @brief Esta funcion de ejecucion es la que ejecuta y calcula los pesos
    @param weights as Vector double con los valores
*/
std::vector<double> perceptron::execute(std::vector<double> weights) {
    values[0] = weights;
    for(std::size_t i=1; i<network.size();i++) {
        for(std::size_t j2=0; j2<layers[i];j2++) {
            values[i][j] = network[i][j].execute(values[i-1]);
            

        }

    }
    return(values.back());
}


/***
    @brief Esta funcion calcula el algorito de retro propagacion de la IA
    @param x an Vector double con la salida
    @param y an Vector double con la entrada
*/
double perceptron_multilayer::retro(std::vector<double> x, std::vector<double> y) {
    std::vector<double> error;
    double eta = 0.0;
    double qerror = 0.0;
    std::vector<double> outputs = execute(x); // push data to network (alimenta a la red neuronal con el dato por defecto)

    // calc of quadratic med error  ### calcula el valor cuadratico medio
    for(std::size_t i=0; i<y.size();i++) {
        error.push_back(y[i] - outputs[i]);
        qerror += error[i] * error[i];
    }
    qerror /= layers.back();


    // calc of error outputs  ### calcula los terminos de error de la salidas
    for(std::size_t i=0; i<outputs.size();i++) {
        d.back()[i] = outputs[i] * (1-outputs[i]) * (error[i]);
    }

    // calc of error retro ### calcula 
    for(std::size_t i=network.size()-2;i>0;i--) {
        for(std::size_t h=0;h<network[i].size();h++) {
            double retro_error = 0.0;
            for(std::size_t k=0; k<layers[i];k++) {
                retro_error += network[i+1][k].weights[h]*values[i+1][k];
            }

            d[i][h] = values[i][h]*(1-values[i][h])*retro_error;
        }

    }

    double gora=0.0;
    // calc of delta ### calcula pesos necesarios y reducir el error con el nombre gora para calcular a la ETA
    for(std::size_t i=1;i<network.size();i++){
        for (std::size_t j=0; j<layers[i];j++) {
            for(std::size_t k=0;k<layers[i-1];k++) {
                
                if (k==layers[i-1])
                    gora = eta * d[i][j] * bias;
                else
                    gora = eta * d[i][j] * values[i-1][k];

                network[i][j].set_weights += gora
            }
        }
    }
}
