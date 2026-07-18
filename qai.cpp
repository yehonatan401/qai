#include <iostream>
#include <cmath>
#include <cudaq.h> 


__qpu__ int run_quantum_neuron(float area_angle, float weight) {
    cudaq::qubit q;
    

    cudaq::rx(area_angle, q);

    cudaq::ry(weight, q);
    

    return cudaq::mz(q); 
}

int main() {

    float area_sqm = 50.0; 
    float price_millions = 8.0; 

    float area_angle = (area_sqm / 100.0) * M_PI; 
    float target_probability = price_millions / 10.0; 
    

    float weight = 0.1; 
    float learning_rate = 0.5;
    int shots = 1000; 
    
    
    for (int epoch = 0; epoch < 50; epoch++) {
        int ones_count = 0;

        for (int i = 0; i < shots; i++) {
            ones_count += run_quantum_neuron(area_angle, weight);
        }
        
        
        float prediction = (float)ones_count / shots;
        
        
        float error = prediction - target_probability;
        

        weight = weight - (learning_rate * error);
        
        std::cout << "epoch " << epoch << " err : " << error 
                  << " | new weight: " << weight<< "\n";
    }

    
    return 0;
}
