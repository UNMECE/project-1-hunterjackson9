#include <iostream>
#include <cmath>

struct Capacitor {
    double *time; // Time array
    double *voltage; // Voltage array
    double *current; // Current array
    double C; // Capacitance value
};

void constantCurrentCharge(Capacitor &cap, double dt, int numTimesteps, double I) {
    // Initialize initial conditions
    cap.voltage[0] = 0.0; // Initial voltage is 0
    cap.current[0] = I; // Constant current

    // Iterate over time steps
    for (int i = 1; i < numTimesteps; i++) {
        cap.time[i] = i * dt; 
        cap.voltage[i] = cap.voltage[i - 1] + cap.current[i - 1] * dt / cap.C;
        cap.current[i] = cap.current[i - 1]; // Current remains constant
    }
}

void constantVoltageCharge(Capacitor &cap, double dt, int numTimesteps, double V0, double R) {
    // Initialize initial conditions
    cap.voltage[0] = 0.0; // Initial voltage is 0
    cap.current[0] = V0 / R; // Initial current

    // Iterate over time steps
    for (int i = 1; i < numTimesteps; i++) {
        cap.time[i] = i * dt;
        cap.current[i] = cap.current[i - 1] - cap.current[i - 1] * (R * cap.C * dt);
        cap.voltage[i] = V0 - cap.current[i] * R;
    }
}

int main() {
    // Define parameters
    double dt = 1e-10; // Time step
    int numTimesteps = 50000; // Number of time steps
    double C = 100e-12; // Capacitance (100 pF)
    double R = 1000; // Resistance (1 kOhm)
    double I = 1e-2; // Constant current (10 mA)
    double V0 = 10.0; // Constant voltage (10 V)

    // Create Capacitor object
    Capacitor cap;
    cap.C = C;

    // Dynamically allocate memory for arrays
    cap.time = new double[numTimesteps];
    cap.voltage = new double[numTimesteps];
    cap.current = new double[numTimesteps];

    // Select charging scenario
    std::cout << "Choose charging scenario:\n";
    std::cout << "1. Constant Current\n";
    std::cout << "2. Constant Voltage\n";
    int choice;
    std::cin >> choice;

    // Perform charging
    if (choice == 1) {
        constantCurrentCharge(cap, dt, numTimesteps, I);
    } else if (choice == 2) {
        constantVoltageCharge(cap, dt, numTimesteps, V0, R);
    } else {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    // Print results every 200 timesteps
    for (int i = 0; i < numTimesteps; i += 200) {
        std::cout << "Time: " << cap.time[i] << " s\n";
        std::cout << "Voltage: " << cap.voltage[i] << " V\n";
        std::cout << "Current: " << cap.current[i] << " A\n\n";
    }

    // Deallocate memory
    delete[] cap.time;
    delete[] cap.voltage;
    delete[] cap.current;

    return 0;
}
