#include "perceptron.h"

static double exp_asm(const double x) {
    double result;
    __asm__ (
        "fldl2e\n\t"       // Cargar log2(e) en la pila
        "fmul %%st(1)\n\t" // st(0) = x * log2(e)
        "fld %%st(0)\n\t"  // Duplicar st(0)
        "frndint\n\t"      // Redondear a entero
        "fsub %%st(1), %%st(0)\n\t" // st(0) = fracción
        "fxch %%st(1)\n\t" // Intercambiar st(0) y st(1)
        "f2xm1\n\t"        // Calcular 2^(st(0)) - 1
        "fld1\n\t"         // Cargar 1.0
        "faddp\n\t"        // Añadir 1, st(0) = 2^(fracción)
        "fscale\n\t"       // Escalar por 2^(entero)
        "fstp %%st(1)\n\t" // Guardar resultado y limpiar la pila
        : "=t" (result)
        : "0" (x)
    );
    return result;
}

static double sigmoide_asm(const double x) {
    double result;
    __asm__ (
        "movapd %[x], %%xmm0\n\t"     // Mover x a xmm0
        "movapd %[neg_one], %%xmm1\n\t" // Mover -1.0 a xmm1
        "mulsd %%xmm1, %%xmm0\n\t"    // xmm0 = -x
        "call exp_asm\n\t"                // Llamar a exp_asm(-x)
        "addsd %[one], %%xmm0\n\t"    // xmm0 = 1 + exp(-x)
        "movapd %[one], %%xmm1\n\t"   // Mover 1.0 a xmm1
        "divsd %%xmm0, %%xmm1\n\t"    // xmm1 = 1 / (1 + exp(-x))
        "movapd %%xmm1, %[result]\n\t" // Mover resultado a la variable result
        : [result] "=m" (result)
        : [x] "m" (x), [one] "m" (1.0), [neg_one] "m" (-1.0)
    );
    return result;
}




double frand() {
    return(2.0*(double)rand() / RAND_MAX - 1.0);
}


<<<<<<< Updated upstream
<<<<<<< Updated upstream
perceptron::perceptron(std::size_t n_inputs, double bias=1.0){
=======
=======
>>>>>>> Stashed changes

static uint64_t perceptron::rdtsc () {
    uint32_t tickl , tickh ;
    asm volatile (" rdtsc ":"=a"( tickl ) ,"=d"( tickh ) ) ;
    return (( uint64_t ) tickh << 32) | tickl ;
} 


perceptron::perceptron(std::size_t n_inputs, const double bias=1.0){
    /*bias = frand();
    secuencie2.reserve(n_inputs);
    for (std::size_t i = 0; i < n_inputs; i++) {
        secuencie2.push_back(frand());
    }*/
>>>>>>> Stashed changes
    weights.resize(n_inputs+1);
    std::generator(weights.begin(),weights.end(),frand);
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
    );
    sigmoide(ponderation);
    return(ponderation);

}


/***
    @brief Esta funcion calcula el valor sigmoide
    @param x as double valor de entrada con el valor actual
    @return valor tras el calculo sigmoide
*/
/*
double perceptron::sigmoide(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}
*/
double perceptron::sigmoide(double x) {
    /*
    double result;
    __asm__ (
        "movapd %[x], %%xmm0\n\t"     // Move x to xmm0
        "movapd %[neg_one], %%xmm1\n\t" // Move -1.0 to xmm1
        "mulsd %%xmm1, %%xmm0\n\t"    // xmm0 = -x
        "call exp\n\t"                // Call exp(-x)
        "addsd %[one], %%xmm0\n\t"    // xmm0 = 1 + exp(-x)
        "movapd %[one], %%xmm1\n\t"   // Move 1.0 to xmm1
        "divsd %%xmm0, %%xmm1\n\t"    // xmm1 = 1 / (1 + exp(-x))
        "movapd %%xmm1, %[result]\n\t" // Move result to result variable
        : [result] "=m" (result)
        : [x] "m" (x), [one] "m" (1.0), [neg_one] "m" (-1.0)
    );
    return result;
    */
    return(StaticPerceptron::sigmoide_asm(x));
}


double exp_asm(double x) {
    /*
    double result;
    __asm__ (
        "fldl2e\n\t"       // Cargar log2(e) en la pila
        "fmul %%st(1)\n\t" // st(0) = x * log2(e)
        "fld %%st(0)\n\t"  // Duplicar st(0)
        "frndint\n\t"      // Redondear a entero
        "fsub %%st(1), %%st(0)\n\t" // st(0) = fraccionado
        "fxch %%st(1)\n\t" // Intercambiar st(0) y st(1)
        "f2xm1\n\t"        // Calcular 2^(st(0)) - 1
        "fld1\n\t"         // Cargar 1.0
        "faddp\n\t"        // Añadir 1, st(0) = 2^(fraccionaddo)
        "fscale\n\t"       // Escalar por 2^(entero)
        "fstp %%st(1)\n\t" // Guardar resultado y limpiar la pila
        : "=t" (result)
        : "0" (x)
    );
    */
    return(StaticPerceptron::exp_asm(x));
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
        this->values.push_back(std::vector<double>(layers[i], 0.0));
        this->network.push_back(std::vector<double>(layers[i],0.0));

        if (i > 0) {
            for(std::size_t j1=0; j1<layers[i]; j1++) {
                this->network[i].push_back(perceptron(layers[i-1], bias));
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
    for(std::size_t i=0;i<initial_weights.size();i++) {

        for(std::size_t j1=0;i<initial_weights[i].size();j1++) {
            network[i+1][j1].set_weights(initial_weights[i][j1]);
        }

    }
}


/***
    @brief Esta funcion de ejecucion es la que ejecuta y calcula los pesos
    @param weights as Vector double con los valores
*/
std::vector<double> perceptron_multilayer::execute(std::vector<double> weights) {
    this->values[0] = weights;
    for(std::size_t i=1; i<this->network.size();i++) {
        for(std::size_t j2=0; j2<this->layers[i];j2++) {
            this->values[i][j2] = this->network[i][j2].execute(this->values[i-1]);
        }

    }
    return(this->values.back());
}


/***
    @brief Esta funcion calcula el algorito de retro propagacion de la IA
    @param x an Vector double con la salida
    @param y an Vector double con la entrada
*/
double perceptron_multilayer::retro(std::vector<double> x, std::vector<double> y) {
    std::vector<double> error;
    double qerror = 0.0;
    std::vector<double> outputs = this->execute(x); // push data to network (alimenta a la red neuronal con el dato por defecto) //comprobar este this si es correcto

    // calc of quadratic med error  ### calcula el valor cuadratico medio
    for(std::size_t i=0; i<y.size();i++) {
        error.push_back(y[i] - outputs[i]);
        qerror += error[i] * error[i];
    }
    qerror /= this->layers.back();


    // calc of error outputs  ### calcula los terminos de error de la salidas
    for(std::size_t i=0; i<outputs.size();i++) {
        this->d.back()[i] = outputs[i] * (1-outputs[i]) * (error[i]);
    }

    // calc of error retro ### calcula 
    for(std::size_t i=this->network.size()-2;i>0;i--) {
        for(std::size_t h=0;h<this->network[i].size();h++) {
            double retro_error = 0.0;
            for(std::size_t k=0; k<this->layers[i];k++) {
                retro_error += this->network[i+1][k].weights[h]*this->values[i+1][k];
            }

            this->d[i][h] = this->values[i][h]*(1-this->values[i][h])*retro_error;
        }

    }
    double gora;
    double eta;
    // calc of delta ### calcula pesos necesarios y reducir el error con el nombre gora para calcular a la ETA
<<<<<<< Updated upstream
    for(std::size_t i=1;i<this->network.size();i++){
        for (std::size_t j=0; j<this->layers[i];j++) {
            for(std::size_t k=0;k<this->layers[i-1];k++) {

                if (k==this->layers[i-1])
                    gora = eta * this->d[i][j] * this->bias;
                else
                    gora = eta * this->d[i][j] * this->values[i-1][k];

                this->network[i][j].weights += gora
=======
    for(std::size_t i=1;i<network.size();i++){
        for (std::size_t j=0; j<layers[i];j++) {
            for(std::size_t k=0;k<layers[i-1];k++) {
                if (k==layers[i-1])
                    gora = eta * d[i][j] * bias;
                else
                    gora = eta * d[i][j] * values[i-1][k];
                network[i][j].set_weights += gora
>>>>>>> Stashed changes
            }
        }
    }
}


void perceptron_multilayer::training(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y, int epochs){
    for(int i=0; i<epochs; i++){
        for(std::size_t j=0; j<x.size(); j++){
            network.retro(x[j], y[j]);
        }
    }
}
