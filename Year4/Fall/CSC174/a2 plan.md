# A2 Plan — Neural Networks from Scratch

## How we will work

Start from zero. Learn one small concept at a time, write the code together, and check understanding before moving on. Keep explanations short and expand when needed.

Assignment files are in `A2/`. This plan stays outside that folder.

## Files you will work on

| File (inside A2) | Purpose |
| --- | --- |
| `code/utils.py` | Complete four helper functions. |
| `code/neural_network.py` | Complete five functions to build and train the network. |
| `code/analysis.py` | Run four experiments and generate graphs and results. |
| `analysis.pptx` | Add graphs and written explanations to the provided slides. Export as `analysis.pdf`. |

## Files and code to leave unchanged

- `code/tests.py` and `code/test_data.py`: supplied checks and test data.
- `a2_env.yml`: supplied environment definition; use it to set up the environment.
- The assignment PDF: reference instructions.
- Existing imports, function signatures, and code outside the functions assigned for implementation.
- `__MACOSX/` and `.DS_Store`: archive metadata; no assignment work needed.

`plots/` is where your code saves the generated graphs. Preserve the `code/` and `plots/` folder relationship.

## Part 1 — Build and check the network (60 points)

### Set up

- [x] Set up and verify the supplied environment using `a2_env.yml`.
- [x] Learn how to run the supplied tests.

Environment setup is complete on this PC. Python 3.12, NumPy, Matplotlib, and scikit-learn were installed and checked. Assignment imports and graph rendering work.

To start working:

1. Double-click `A2 terminal.cmd` in CSC174. It opens in `A2/code` with `deep-learning-a2` active.
2. Run `python tests.py` to check the assignment code.
3. For one helper function, for example, run `python -c "from tests import test_sigmoid_derivative; test_sigmoid_derivative()"`.

All four helper functions pass their supplied tests. The five network functions remain unfinished, so their tests still report failures. The environment itself is ready. Read the printed test results, since the supplied runner can report failures while still exiting normally.

If your editor asks for a Python interpreter, select:
`C:\Users\Ryan\miniconda3\envs\deep-learning-a2\python.exe`

From the VS Code PowerShell terminal, start the same ready-to-use A2 terminal with:

```powershell
& "C:\Users\Ryan\Desktop\senior\senior\Year4\Fall\CSC174\A2 terminal.cmd"
```

Wait for `(deep-learning-a2)` and a path ending in `A2\code`, then run the test commands above.

Alternative in Anaconda Prompt:

```text
conda activate deep-learning-a2
cd /d "C:\Users\Ryan\Desktop\senior\senior\Year4\Fall\CSC174\A2\code"
python tests.py
```

### Helper functions in code/utils.py

For each function: understand its purpose, work through a small example, write it, and check it.

- [x] `sigmoid_derivative` — implemented; supplied function test passed.
- [x] `softmax` — implemented; supplied function test passed. Large-score stability check also passed.
- [x] `cross_entropy_loss` — implemented; supplied function test passed.
- [x] `one_hot_encode` — implemented; both supplied test cases passed.

### Helper verification complete

All four supplied helper tests pass, including both one-hot cases. The softmax stability fix is saved and the large-score check passes.

Suggested helper-functions commit message: `Implement A2 neural network utility functions`.

### Network functions in code/neural_network.py

- [ ] `initialize_parameters` — create the weights and biases.
- [ ] `forward_pass` — turn inputs into predicted probabilities.
- [ ] `backward_pass` — calculate gradients and update weights and biases.
- [ ] `train` — repeat learning over batches and epochs.
- [ ] `predict` — choose the most likely class.
- [ ] Pass the provided tests and check behavior beyond those tests where needed.

## Part 2 — Run the experiments

Complete the four experiment functions in `code/analysis.py`. Use the exact hyperparameters and random seeds supplied there. Save professionally labeled graphs to `plots/`.

### Experiment 1: Linearly separable data

- [ ] Train the specified model.
- [ ] Plot the decision boundary over the training data.
- [ ] Print training accuracy.

### Experiment 2: Concentric circles

- [ ] Train the three specified models.
- [ ] Plot each decision boundary.
- [ ] Print each training accuracy.
- [ ] Compare the effect of hidden layers and nonlinear activation functions.

### Experiment 3: Two moons

- [ ] Train the six specified models with different hidden-layer sizes.
- [ ] Plot each decision boundary.
- [ ] Print accuracy, parameter count, and training time for each model.
- [ ] Compare how model complexity affects learning.

### Experiment 4: Breast cancer classification

- [ ] Train for 3,000 epochs, one epoch at a time.
- [ ] Save copies of the model parameters after every epoch.
- [ ] Track and plot training and validation loss and accuracy.
- [ ] Select the epoch with the lowest validation loss and restore its parameters.
- [ ] Print the selected epoch and training, validation, and testing accuracies.
- [ ] Print the test confusion matrix, precision, recall, and F1-score, with malignant tumors as the positive class.

## Part 3 — Explain, verify, and submit

Parts 2 and 3 together make up the 40-point analysis section.

- [ ] Insert the generated figures into the provided `analysis.pptx` slides.
- [ ] Explain the circles results: decision boundaries, accuracy, hidden layers, and nonlinear activations.
- [ ] Explain the moons results: decision boundaries, accuracy, parameter counts, and training time.
- [ ] Explain the breast cancer results: loss and accuracy curves, overfitting or underfitting, epoch selection, generalization, evaluation metrics, and possible improvements.
- [ ] Use only the provided slides; do not add extra slides.
- [ ] Export the slides as `analysis.pdf`.
- [ ] Run `analysis.py` and verify that its saved figures match those in the report exactly.
- [ ] Submit these four files to Canvas:
  - `analysis.py`
  - `utils.py`
  - `neural_network.py`
  - `analysis.pdf`

## Where to begin

Environment setup and the four helper implementations are done; their supplied tests pass. The softmax stability check also passes. Next, begin `initialize_parameters` in `code/neural_network.py`. Part 1 is still in progress.




