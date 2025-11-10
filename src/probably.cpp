#include "probably.h"

#include <cmath>
#include <Eigen/Dense>

namespace probably {
double normal_pdf(const double x, const double mu, const double sigma){
    return fast_exp(-0.5 * (x - mu) * (x - mu) / (sigma * sigma)) / (sigma * sqrt(2 * PI));
}

double uniform_est(const double x, const double a, const double b, const double sigma, const int n, const double conf){
    if (a > b) return 0;
    else if (a == b) return normal_pdf(x, a, sigma);

    double step = (b - a)/(n-1);
    double sigma_est = 2*sqrt(-2*log(conf))*(b-a)/n + sigma;
    double normalization = 1/(double)n;

    double ret = 0;
    for (int i = 0; i < n ; i++) {
        double mu = a + step * i;
        ret += normal_pdf(x, mu, sigma_est);
    }
    ret *= normalization;

    return ret;
}

double uniform_est(const double x, const double b, const double sigma, const int n, const double conf){
    return uniform_est(x, 0, b, sigma, n, conf);
}

double uniform_est(const Eigen::Vector2d& x, const double a, const double b, const double sigma, const int n, const double conf){
    double r = x.norm();

    if (a > b) return 0;
    else if (a == b) return normal_pdf(r, a, sigma);

    double step = (b-a)/(n-1);
    double sigma_est = 2*sqrt(-2*log(conf))*(b-a)/n + sigma;

    double normalization = (b-a)/(double)n;
    normalization /= PI*(b*b - a*a); //Volume of the 3d cylinder with a circular-basis

    double ret = 0;
    for (int i = 0 ; i < n; i++ ){
        double mu = a + step * i;
        ret += normal_pdf(r, mu, sigma_est);
    }
    ret *= normalization;

    return ret;
}

double uniform_est(const Eigen::Vector3d& x, const double a, const double b, const double sigma, const int n, const double conf){
    double r = x.norm();

    if (a > b) return 0;
    else if (a == b) return normal_pdf(r, a, sigma);

    double step = (b-a)/(n-1);
    double sigma_est = 2*sqrt(-2*log(conf))*(b-a)/n + sigma;

    double normalization = (b-a)/(double)n;
    normalization /= 4*PI*(b*b*b - a*a*a)/3; //Volume of the 4d cylinder with a spherical-basis

    double ret = 0;
    for (int i = 0 ; i < n; i++ ){
        double mu = a + step * i;
        ret += normal_pdf(r, mu, sigma_est);
    }
    ret *= normalization;

    return ret;
}

double uniform_est(const Eigen::Vector2d& x, const double b, const double sigma, const int n, const double conf){
    return uniform_est(x, 0.0, b, sigma, n, conf);
}

double uniform_est(const Eigen::Vector3d& x, const double b, const double sigma, const int n, const double conf){
    return uniform_est(x, 0.0, b, sigma, n, conf);
}
}
