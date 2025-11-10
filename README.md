# CHMM

This project provides a minimal implementation of a **Coupled Hidden Markov Model (CHMM)**, along with basic probability density estimation using Gaussian mixtures.  
It is written in **C++** and only requires a few simple functions and types from **Eigen**.

---

## Project Structure

- **chmm** — The main library (does **not** require Eigen).  
  Implements the basic CHMM dynamics and all the required objects.

- **probably** — A utility library that implements estimated probability densities by gaussian mixture using a signal processing framework. (A list of implemented density can be found at the end)

- **chmm_test** — A minimal working example demonstrating how to use the `CHMM` and `probably` libraries.

---

## Mathematical Framework

- The emission from state \( i \) is independent of every other state in the configuration and of all previous observations:  
  P(O^i_t | X_t, O_{1:t-1}) = P(O^i_t | X^i_t)

- The transition from configuration \( X_t \) to state \( X^i_{t+1} \) is independent of every other state in the previous configuration and of the previous observations:  
  P(X^i_{t+1} | X_t, O_{t-1}) = P(X^i_{t+1} | X^i_t)

- Some configurations can be excluded:  
  Let \( X_t \) be a non-accessible configuration, i.e. \( \forall t, X_t = 0 \).  
  (See the `S_E` argument.)

---

## Building the Code

### Build Libraries Only
```bash
mkdir build && cd build
cmake ..
make -jX
```

### Build Libraries and the Example
```bash
mkdir build && cd build
cmake .. -DBUILD_EXAMPLE=on
make -jX
```

After building, you can link libchmm and libprobably in your own project.

## Implemented densities:
### Normals
- **1D Normal distribution**: normal_pdf(double x, double mu, double sigma)
- **N-D Multivariate distribution**: normal_pdf(T x, T mu, W Sigma) (T need to implement "-" operator and W need: inverse() and determinant())

### Uniform densities
- **Estimation with n gaussian of a uniform on a 1D segment convolved with a normal**, U_{(a, b)}\*N(0, sigma)(x): uniform_est(double x, double a, double b, double sigma, int n) 
- **Estimation with n gaussian of a uniform on a 1D segment convolved with a normal**, U_{(0, b)}\*N(0, sigma)(x): uniform_est(double x, double b, double sigma, int n) 
- **Estimation with n gaussian of a uniform on a hollowed 2D ball convolved with a normal**, U_{B(0, b)\\B(0, a)}\*N(0, sigma)(x): uniform_est(Eigen::Vector2d x, double a, double b, double sigma, int n) 
- **Estimation with n gaussian of a uniform on a 2D ball convolved with a normal**, U_{B(0, b)}\*N(0, sigma)(x): uniform_est(Eigen::Vector2d x, double b, double sigma, int n) 
- **Estimation with n gaussian of a uniform on a hollowed 3D ball convolved with a normal**, U_{B(0, b)\\B(0, a)}\*N(0, sigma)(x): uniform_est(Eigen::Vector3d x, double a, double b, double sigma, int n) 
- **Estimation with n gaussian of a uniform on a 3D ball convolved with a normal**, U_{B(0, b)}\*N(0, sigma)(x): uniform_est(Eigen::Vector3d x, double b, double sigma, int n) 
