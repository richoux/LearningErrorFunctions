#include <iostream>
#include <Eigen/Dense>
#include <random>
#include <cmath>
#include <string>
#include <fstream>

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

std::vector<std::string>
get_next_line_and_split_into_tokens(std::istream &str) {
        std::vector<std::string> result;
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
                result.push_back(cell);
        }
        // This checks for a trailing comma with no data after it.
        if (!lineStream && cell.empty()) {
                // If there was a trailing comma then add an empty element.
                result.push_back("");
        }
        return result;
}

int main() {
        int d = 4;
        int k = 1296;

        MatrixXd a(d, k);

        std::ifstream file("../csv/less_than_4.csv");
        auto dummy = get_next_line_and_split_into_tokens(file);

        int tmp = 0;
        while (file.good()) {
                auto tokens = get_next_line_and_split_into_tokens(file);
                if (std::rand() % 100 < 250) {
                        // std::vector<double> x;
                        Eigen::VectorXd v(d);
                        double y = std::stod(tokens[2]);

                        int tmp2 = 0;
                        for (auto it = tokens.begin() + 3; it < tokens.end(); ++it) {
                                // x.push_back(std::stod(*it));
                                v[tmp2++] = std::stod(*it);
                        }

                        a.row(tmp++) = v;
                }
        }

        std::ifstream file2("less_than_4.csv");
        dummy = get_next_line_and_split_into_tokens(file2);

        while (file2.good()) {
                auto tokens = get_next_line_and_split_into_tokens(file2);
                std::vector<double> x;

                // double y = std::stod(tokens[2]);
        }






        MatrixXd p = Achlioptas(d, k);
        std::cout << p << std::endl;

        Eigen::VectorXd v (2);
        v << 1, 2;
        MatrixXd m(2,2);
        m.row(0) = v;
        m.row(1) << 3, 4;

        std::cout << m <<std::endl;

        std::cout << a << std::endl;
}