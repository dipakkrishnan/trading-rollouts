#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ROLLOUTS 100000  // Total number of Monte Carlo simulations
#define STEPS 10         // Number of trading days
#define INIT_BALANCE 10000.0  // Starting money

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(time(NULL) + rank);   

    double balance = INIT_BALANCE;
    double stock_price = 100.0;
    double volatility = 0.2;
    double risk_free_rate = 0.05;
    double total_balance = 0.0;
    double local_sum = 0.0;
    
    for (int rollout = 0; rollout < ROLLOUTS / size; rollout++) {
        balance = INIT_BALANCE;
        stock_price = 100.0;
        
        for (int step = 0; step < STEPS; step++) {
            // Box-Muller transform for normal distribution
            double u1 = (double)rand() / RAND_MAX;
            double u2 = (double)rand() / RAND_MAX;
            double z = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
            
            // Update stock price using geometric Brownian motion
            double drift = (risk_free_rate - 0.5 * volatility * volatility) * (1.0/STEPS);
            double diffusion = volatility * z * sqrt(1.0/STEPS);
            stock_price *= exp(drift + diffusion);
            
            // Simple trading strategy: invest everything in stock
            balance *= stock_price / (stock_price - (stock_price * (drift + diffusion)));
        }
        local_sum += balance;
    }   

    // Perform reduction after all rollouts are complete
    MPI_Reduce(&local_sum, &total_balance, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double average_balance = total_balance / ROLLOUTS;
        printf("Final Average Balance: %.2f\n", average_balance);
    }

    MPI_Finalize();
    return 0;
}
