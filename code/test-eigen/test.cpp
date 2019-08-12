#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>

using Eigen::MatrixXd;

MatrixXd Achlioptas(int d, int k){
        MatrixXd p(d, k);

        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(1, 6);

        for (int i = 0; i < d; ++i)
        {
                for (int j = 0; j < k; ++j)
                {
                        int r = dis(gen);
                        if (r <= 1) {
                                p(i,j) = 1.;
                        } else if (r <= 5) {
                                p(i,j) = 0.;
                        } else {
                                p(i,j) = -1.;
                        }
                }
        }

        return 1./std::sqrt(k) * p;
}

int main() {
        int d = 3;
        int k = 10;

        MatrixXd p = Achlioptas(d, k);
        std::cout << p << std::endl;
}