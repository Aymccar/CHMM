#pragma once
#include <limits>
#include <stdint.h>
#include <Eigen/Dense>

namespace probably {

#define PI 3.141592653589793

inline double fast_exp(const double x) {
    if (x < -709.0) return 0.0; // exp(-709) ~ 1e-308 (underflow limit)
    if (x > 709.0) return std::numeric_limits<double>::infinity(); // exp(709) ~ 1e+308

    // Constants for IEEE 754 double approximation
    const double a = 1512775.3951951856938;  // = (1 << 20) / ln(2)
    const double b = 1072632447;             // = 1023 * (1 << 20)

    union {
        uint64_t i;
        double d;
    } v;

    v.i = (uint64_t)(a * x + b) << 32;

    return v.d;
}

double normal_pdf(const double x, const double mu, const double sigma);

template<typename T, typename W>
double normal_pdf(const T& x, const T& mu, const W& Sigma) {
    T error = x - mu;
    double exponent = -0.5 * (error.transpose() * Sigma.inverse() * error)(0, 0);
    double det = Sigma.determinant();
    double norm_const = pow(2 * PI, x.size() / 2.0) * sqrt(det); //XXX Maybe change pow 

    return fast_exp(exponent) / norm_const;
}
    
//1D density a <= x <= b
double uniform_est(const double x, const double a, const double b, const double sigma, const int n, const double conf = 5e-1);

//1D density |x| <= b
double uniform_est(const double x, const double b, const double sigma, const int n, const double conf = 5e-1);

//Multivariate a <= ||x|| <= b densities
double uniform_est(const Eigen::Vector2d& x, const double a, const double b, const double sigma, const int n, const double conf = 5e-1);
double uniform_est(const Eigen::Vector3d& x, const double a, const double b, const double sigma, const int n, const double conf = 5e-1);

//Multivariate ||x|| <= b densities
double uniform_est(const Eigen::Vector2d& x, const double b, const double sigma, const int n, const double conf = 5e-1);
double uniform_est(const Eigen::Vector3d& x, const double b, const double sigma, const int n, const double conf = 5e-1);
}
