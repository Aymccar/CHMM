# CHMM 
This project is a small Couple Hidden Markow Chain calculator in C++. 
It is based on several assumption that would be relaxed in the future. 

## Assumption :
- Each emission is independent of the other state and of the previous observations $P(O_t| X_{1:t}, O_{1:t-1}) = P(O_t|X_t)$
- Each transition is independent on the previous observations $P(X_t | X_{t-1}, O_{t-1})  = P(X_t | X_{t-1})$

## Build the code
```bash
mkdir build && cd build
cmake ..
make -jX #Where X is the number of process
```

Then you can use `libchmm` in your project. 
