# PyTorch Notebook — Condensed Study Guide

**CSC174 · Neural Review**

Based on [PyTorch_demo_solutions.ipynb](PyTorch_demo_solutions.ipynb). The [blank notebook](PyTorch_demo.ipynb) has empty code cells. Follow the solution notebook for explanations, then use the blank version for practice.

Section numbers below are the notebook's own headings. Cell numbers count every markdown and code cell from 1; they are not the notebook's execution counts.

[Practice quiz — no answers](PyTorch_Practice_Quiz.md) · [Separate answer key](PyTorch_Practice_Quiz_Answer_Key.md)

## Study route

| Notebook section | Solution cells | Main idea |
|---|---|---|
| 1. Import Modules | 1–2 | Load the libraries |
| 2. Tensors | 3–6 | Shapes, creation, operations, indexing |
| 3. Computing Gradients of Tensors | 7–11 | Autograd and forward/backward passes |
| 4. Generating Noisy Sine Regression Data | 12–13 | Noise, devices, random splits |
| 5. Visualizing the Data | 14–15 | Signal versus noisy observations |
| 6. Creating a Training DataLoader | 16–17 | Paired data and mini-batches |
| 7. Defining an MLP | 18–19 | Layers, activations, forward method |
| 8. Specifying the Loss Function and Optimizer | 20–21 | MSE versus Adam |
| 9. Training and Validation | 22–23 | Updates, validation, checkpointing |
| 10. Plotting Training and Validation Loss Curves | 24–25 | Generalization and overfitting |
| 11. Evaluating on the Test Set | 26–27 | Final versus best-validation model |
| 12. Visualizing the Learned Curve | 28–29 | Learned predictions versus the true signal |

## 1) Import Modules

```python
import torch
import numpy as np
import matplotlib.pyplot as plt
```

| Import/name | Role |
|---|---|
| `torch` | Tensors, automatic differentiation, model training |
| `np` | Alias for NumPy, an array/numerical library |
| `plt` | Alias for Matplotlib's plotting interface |

An import makes library functionality available; it does not train anything. `as` assigns a shorter name. NumPy is imported here, although the shown solution does not call `np.*` functions directly.

Section 4 adds `time` for timing, `nn` for neural-network components, and `TensorDataset`/`DataLoader` for batches.

## 2) Tensors

A tensor is a multidimensional array. PyTorch adds support for tracked differentiation and accelerator computation.

| Example | Shape | Dimensions |
|---|---|---:|
| `torch.tensor(5)` | `()` | 0 |
| `torch.tensor([1, 2, 3])` | `(3,)` | 1 |
| `torch.tensor([[1, 2, 3], [4, 5, 6]])` | `(2, 3)` | 2 |
| The notebook's tensor `d` | `(2, 2, 2)` | 3 |

`torch.Size([])` is a scalar shape; it does not mean the tensor contains no value. The number of dimensions is the number of entries in the shape. Element count is the product of dimension sizes.

### Creation functions — cell 5

| Function | Values |
|---|---|
| `torch.zeros(3, 4)` | Zeros, shape (3, 4) |
| `torch.ones(2, 3, 4)` | Ones, shape (2, 3, 4) |
| `torch.rand(2, 3)` | Uniform random values in [0, 1) |
| `torch.randn(3, 4)` | Standard-normal values; negative values are possible |

### Operations — cell 6

For `a = torch.tensor([[1., 2.], [3., 4.]])`:

| Expression | Meaning/result |
|---|---|
| `a + b`, `a - b`, `a * b`, `a / b` | Elementwise arithmetic |
| `a ** 2` | Square each element |
| `a @ b` | Matrix multiplication |
| `a.T` | Swap rows and columns for this 2D matrix |
| `a.sum()`, `a.mean()`, `a.max()` | Scalars 10, 2.5, and 4 |
| `a.reshape(4)` | Shape (4,), values [1, 2, 3, 4] |
| `a.reshape(1, 4)` | Shape (1, 4), one row |
| `a[0, 1]` | Scalar 2 |
| `a[0]` | First row: [1, 2] |
| `a[:, 1]` | Second column: [2, 4] |

Indexing starts at 0; `:` means all entries along that axis. Slice stops are excluded. Reshaping preserves element count; `-1` asks PyTorch to infer one size.

`exp`, `log`, `sqrt`, `sigmoid`, and `relu` act element by element. ReLU maps negative inputs to 0 and leaves positive inputs unchanged. Sigmoid maps real inputs to (0, 1).

For 2D matrix multiplication: (m, k) @ (k, n) gives (m, n). Elementwise operations instead match corresponding positions, allowing compatible broadcasting. Broadcasting compares dimensions from the right: sizes must agree or one must be 1; missing leading dimensions behave like size 1.

**Trap:** (3,), (1, 3), and (3, 1) all hold three values but have different shapes.

## 3) Computing Gradients of Tensors

### Scalar derivative — cell 8

```python
x = torch.tensor(3.0, requires_grad=True)
y = x**2 + 2*x + 1
y.backward()
print(x.grad)
```

`requires_grad=True` enables tracking for differentiation with respect to x. The forward computation produces y; `backward()` computes its derivative. Here dy/dx = 2x + 2 = 8. This is sensitivity, not an updated x.

### Single-input prediction and loss — cell 9

The code computes `z = w*x + b`, then `y_hat = torch.sigmoid(z)`, then binary cross-entropy loss, then `loss.backward()`.

- x is the input; w is a weight; b is a bias.
- z is the score before activation; y_hat is the prediction; y is the target.
- `w.grad` and `b.grad` hold derivatives of the loss.
- `retain_grad()` preserves gradients on intermediate tensors z and y_hat for inspection.
- `.item()` extracts a Python number from a single-element tensor.

For one binary target, BCE is `-[y*log(y_hat) + (1-y)*log(1-y_hat)]`. It penalizes confident wrong predictions. This section illustrates classification; the later sine model is regression and uses MSE.

### Multiple observations — cell 10

x and y each contain three values. One scalar w and b are applied to all three inputs by broadcasting. Predictions have shape (3,). `.mean()` combines the three losses into one scalar for the backward call.

### One observation with multiple features — cell 11

x and w are vectors of length three. `torch.dot(w, x) + b` combines the features into a scalar score. `w.grad` has one entry per weight.

**Remember:** Forward computes predictions; loss measures error; backward computes gradients; an optimizer update changes weights. The gradient demonstrations themselves do not include an optimizer update.

## 4) Generating Noisy Sine Regression Data

`torch.manual_seed(42)` helps repeat random draws under the same conditions. It does not remove randomness, set every draw to 42, or guarantee identical results on all systems.

`device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')` chooses CUDA when available and otherwise CPU. Selecting a device does not move tensors by itself.

```python
X = -3 + 6 * torch.rand(1200, 1)
y = torch.sin(X) + 0.35 * torch.randn_like(X)
```

X has one feature per observation, approximately spanning [-3, 3). y has the same (1200, 1) shape. The sine is the underlying signal; the added noise has standard deviation 0.35. `randn_like` matches X's shape.

`randperm(1200)` shuffles indices without repetition. The same selected indices are used for X and y, preserving their pairing.

| Split | Index positions in the shuffled sequence | Shape |
|---|---|---|
| Train | `[:840]` | (840, 1) |
| Validation | `[840:1020]` | (180, 1) |
| Test | `[1020:]` | (180, 1) |

Training fits parameters; validation selects a checkpoint; test measures held-out performance afterward.

## 5) Visualizing the Data

`torch.linspace(-3, 3, 500).reshape(-1, 1)` creates an ordered grid with shape (500, 1). `linspace` is evenly spaced rather than random.

The plot shows x horizontally and y vertically. The dashed line is the true sine signal; colored dots are noisy observations from the three splits. Noise explains why the points do not all lie on the line. Fitting every noisy point is not the goal.

`plt.plot` draws curves; `plt.scatter` draws observations; labels and legends identify them. `.numpy()` supplies arrays to this plotting code.

## 6) Creating a Training DataLoader

```python
train_loader = DataLoader(
    TensorDataset(X_train, y_train),
    batch_size=32,
    shuffle=True
)
```

`TensorDataset` pairs each input with its target. `DataLoader` produces mini-batches and shuffles observation order for each pass without breaking those pairs.

An epoch is a complete pass through the training set. With 840 observations and the default of keeping the final incomplete batch, there are 27 batches: 26 × 32 plus 8. Typical xb and yb shapes are (32, 1); the final pair has shape (8, 1).

## 7) Defining an MLP

`SineMLP(nn.Module)` defines a PyTorch model class. `super().__init__()` initializes the parent module. `nn.Sequential` applies its layers in order. `forward(self, x)` specifies the model computation; `model(x)` invokes it through PyTorch's module machinery.

| Stage | Output shape for batch size B |
|---|---|
| Input | (B, 1) |
| Linear(1, 128), ReLU | (B, 128) |
| Linear(128, 128), ReLU | (B, 128) |
| Linear(128, 128), ReLU | (B, 128) |
| Linear(128, 1) | (B, 1) |

There are three hidden layers of width 128 and one output layer. ReLU provides nonlinearity. Without nonlinear activations, these affine layers would collapse to one affine transformation.

The output is unrestricted for regression, allowing negative sine values. A sigmoid output would restrict predictions to (0, 1).

A linear layer learns a weight matrix and bias: for input (B, in), weights have shape (out, in), bias (out,), and output (B, out). Parameter count is in × out + out. Here: 256 + 16,512 + 16,512 + 129 = **33,409**, matching the notebook's saved output. ReLU adds no learned parameters.

`model.parameters()` exposes trainable tensors to the optimizer; `p.numel()` counts scalar entries. `.to(device)` moves the model.

## 8) Specifying the Loss Function and Optimizer

```python
loss_fn = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.005)
```

MSE averages squared differences between predictions and targets. For N one-output observations, MSE = sum((prediction − target)²) / N. Matching (B, 1) shapes avoid unintended broadcasting.

Adam uses gradients to update weights and biases. Learning rate 0.005, batch size 32, hidden width 128, and epoch count 600 are chosen settings; weights and biases are learned parameters.

## 9) Training and Validation

Study this long cell in small pieces.

### Setup

`train_losses` and `val_losses` store one result per epoch. `best_val_loss = float('inf')` allows the first finite validation loss to become the initial best. Validation tensors are moved to the selected device once.

`time.perf_counter()` measures elapsed time. The CUDA synchronization before timing waits for earlier GPU work; timing details are secondary to understanding the training loop.

### One training batch

| Code | Purpose |
|---|---|
| `model.train()` | Select training mode |
| `xb, yb = xb.to(device), yb.to(device)` | Place inputs and targets with the model |
| `predictions = model(xb)` | Forward pass |
| `loss = loss_fn(predictions, yb)` | Compute error |
| `optimizer.zero_grad()` | Clear previous gradients |
| `loss.backward()` | Compute gradients |
| `optimizer.step()` | Update parameters |

Gradients otherwise accumulate across backward calls. `model.train()` does not itself perform training.

`loss.item() * len(xb)` converts each batch mean into a sum over its observations. Dividing the accumulated value by 840 gives the epoch's observation-weighted training loss, correctly handling the final small batch. Because parameters change between batches, this is a running training measure rather than one fresh evaluation of the final epoch model on the entire training set.

### Validation

`model.eval()` selects evaluation behavior. `with torch.no_grad():` separately disables recording operations for gradient computation. The validation block predicts and measures loss without backward or optimizer steps.

Training/evaluation mode matters for layers such as dropout and batch normalization. This model contains neither, but the explicit modes establish the usual workflow.

### Checkpoint

When validation loss improves, save its value, its one-based epoch number, and copies of the model state:

```python
best_state = {
    name: value.detach().clone()
    for name, value in model.state_dict().items()
}
```

Cloning makes independent copies so later updates cannot overwrite the saved values. Detaching removes a gradient connection; by default the state-dictionary tensors are already detached. Detachment alone is not an independent copy.

This saves the checkpoint in memory, not to a disk file. It does not stop training early: all 600 epochs still run.

## 10) Plotting Training and Validation Loss Curves

Horizontal axis: epoch. Vertical axis: MSE, where lower is better. The vertical dashed line marks the best validation epoch.

The stored notebook run reaches its lowest validation MSE, about 0.1265, at epoch 9. Training loss subsequently tends to fall while validation loss fluctuates at a higher level. That gap and lack of sustained validation improvement suggest increasing fit to training-specific noise. The exact best epoch and values may differ on another run.

More epochs do not guarantee better generalization. Choose the checkpoint by validation loss rather than lowest training loss.

## 11) Evaluating on the Test Set

The notebook evaluates two models without gradients:

1. `model`: the parameters left after the final epoch.
2. `best_model`: a new SineMLP loaded using `load_state_dict(best_state)`.

The saved run reports test MSE 0.1189 for the final model and 0.1106 for the best-validation model. These are stored results, not a guarantee for every run. Lower validation loss does not mathematically guarantee lower test loss.

Checkpoint selection has already used validation data. Avoid using test results to repeatedly tune or select models.

## 12) Visualizing the Learned Curve

Create a (500, 1) grid, predict with each model under no-grad, then convert outputs with `.cpu().numpy()`.

The final plot compares noisy training dots, the dashed true sine curve, the best-validation prediction, and the final prediction. In the saved plot, the final model is visibly more jagged in parts; the best-validation model is smoother. Relate this observation to validation/test performance rather than assuming smoothness alone proves correctness.

**Core distinctions to remember:** shape versus element count; elementwise versus matrix multiplication; gradients versus weight updates; batch versus epoch; loss versus optimizer; evaluation mode versus no-grad; validation selection versus test evaluation.

---

Scope comes from the notebook, not a prediction of exam coverage. The practice quiz uses fresh examples in the supplied professor's style. API nuances were cross-checked with the official [autograd](https://docs.pytorch.org/docs/stable/notes/autograd.html), [Linear](https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html), [data-loading](https://docs.pytorch.org/docs/stable/data.html), and [reproducibility](https://docs.pytorch.org/docs/stable/notes/randomness.html) documentation.
