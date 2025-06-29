# 🔁 Laplace Domain RLC Circuit Analyzer

This project is a **symbolic Laplace-domain circuit analysis tool** built in Python. It supports the construction, analysis, and visualization of **RLC circuits with voltage and current sources** using fundamental cut-set and tie-set methods. The tool outputs both **Laplace-domain** and **time-domain** solutions using **inverse Laplace transforms**, with plotting support via `matplotlib`.

## 🧠 Features

* Symbolic modeling of **RLC circuits** using `sympy`
* Automatic generation of **incidence matrices**, **tie sets**, and **cut sets**
* Solves for **branch currents and voltages** in Laplace domain
* Computes **inverse Laplace transforms** to get time-domain behavior
* Evaluate expressions numerically at custom time points
* Plot **current/voltage vs. time** for any or all branches

## 🧮 Technologies Used

* Python 3.x
* SymPy – symbolic mathematics
* NumPy – numerical computations
* Matplotlib – plotting graphs

## 📦 How It Works

### 1. Define the Circuit
You are prompted to enter:
* Number of **nodes** and **branches**
* Branch type: `R` (resistor), `L` (inductor), `C` (capacitor), `V` (voltage source), `I` (current source)
* Connection nodes for each branch
* Values for each element

### 2. Laplace Transformation
Each element is modeled in the Laplace domain as:
* R → R
* L → sL
* C → 1/(sC)
* V → V/s
* I → I/s

### 3. Topological Analysis
* Constructs the **incidence matrix**
* Derives **tie sets** and **cut sets**
* Solves **mesh equations** or **node voltage equations**

### 4. Symbolic Solutions
* Solves for **branch currents** and **voltages** symbolically in `s` (Laplace domain)

### 5. Time-Domain Conversion
* Uses `inverse_laplace_transform()` to convert each result into **time-domain expressions**

### 6. Plotting & Evaluation
* Plot `i(t)` or `v(t)` for any branch using `matplotlib`
* Numerically evaluate time-domain values at chosen `t` values

## 🖥️ Example Usage

```bash
$ python laplace_circuit_solver.py
```

Sample terminal flow:

```
Enter the number of nodes: 4
Enter the number of elements (R, L, C, V, I): 5

Element 1:
Enter type (R, L, C, V, I): R
Enter the positive node (0-3): 0
Enter the negative node (0-3): 1
Enter the value: 1
...

=== Time Domain Current Solutions ===
Branch 1:
Laplace domain: (-1728.0*s - 864.0)/(s*(576.0*s**2 + ...))
Time domain: i(t) = ...
```

## 📊 Visual Output

### ➤ Single Branch Plot

```python
plot_circuit_response(time_domain_solutions, branch_number=1, response_type='current')
```

### ➤ Multiple Branch Plot

```python
plot_multiple_responses(time_domain_solutions, response_type='voltage')
```

## 📂 Project Structure

```
laplace_circuit_solver/
│
├── main.py                 # Entry script (interactive CLI)
├── analyzer.py             # Laplace domain analyzer class
├── inverse_transform.py    # Inverse Laplace & numerical evaluator
├── plotting.py             # Plotting utilities
└── README.md               # Project documentation
```

## ✅ To-Do / Future Improvements

* GUI for circuit input
* Support for mutual inductance
* Symbolic Laplace simplification enhancements
* Export results as CSV or LaTeX tables

## ✍️ Contributors

* **Sandeep** – Incidence matrix, Laplace solver
* **Yesh** – Inverse Laplace transforms, numerical evaluation, plotting

## 📘 References

* SymPy Documentation
* Signals and Systems Textbooks

## 📜 License

This project is licensed under the MIT License. See `LICENSE` for details.