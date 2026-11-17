# PyTorch Practice Quiz — CSC174

Original practice modeled on the supplied professor-authored M4 NumPy Quiz #4. This is not an actual exam or a prediction of its contents. Expanded to 24 questions to cover the notebook's tensor, autograd, and model-training sections.

**Source:** [PyTorch_demo_solutions.ipynb](PyTorch_demo_solutions.ipynb), sections 1–12. The companion [PyTorch_demo.ipynb](PyTorch_demo.ipynb) contains the blank exercises.

Assume snippets run independently with `import torch` and `from torch import nn` already executed. Other needed imports are shown. Use ordinary eager execution and default settings unless stated. For output questions, values and shapes matter; exact spacing and decimal formatting do not. Choose one answer for each multiple-choice question.

## 1. PyTorch capabilities

Which statement is **NOT** correct?

a) PyTorch supports elementwise operations on entire tensors.
b) PyTorch can automatically compute gradients of tracked computations.
c) Importing PyTorch automatically puts every tensor on a GPU.
d) PyTorch tensors can represent multidimensional data.

## 2. Tensor dimensions

**True or false:** A PyTorch tensor is limited to three dimensions because higher-dimensional objects cannot be visualized easily. Briefly justify.

## 3. Random seed

What is the purpose of `torch.manual_seed(42)`? Does it mean every random number generated afterward will equal 42?

## 4. Reading a shape

What is `x.shape`?

```python
x = torch.tensor([[2, 4, 6],
                  [8, 10, 12]])
```

a) `torch.Size([6])`
b) `torch.Size([2, 3])`
c) `torch.Size([3, 2])`
d) `torch.Size([1, 6])`

## 5. Slicing

Fill in `x[________]` using slices to produce the output shown.

```python
x = torch.tensor([
    [[1, 2, 3], [4, 5, 6]],
    [[7, 8, 9], [10, 11, 12]]
])
```

Desired output:

```python
tensor([[[2, 3],
         [5, 6]],

        [[8, 9],
         [11, 12]]])
```

## 6. Reshaping

A tensor has shape `(2, 3, 4)`. Which is a valid new shape for `reshape`?

a) `(5, 5)`
b) `(2, 3)`
c) `(4, 7)`
d) `(6, 4)`

## 7. Aggregation

What are the numerical values printed?

```python
x = torch.tensor([[2., 4.],
                  [6., 8.]])
print(x.sum())
print(x.mean())
```

a) `20`, then `5`
b) `[6, 14]`, then `[3, 7]`
c) `10`, then `5`
d) `20`, then `10`

## 8. Broadcasting

Which addition does **NOT** need either operand to expand its shape through broadcasting?

a) A tensor of shape `(2, 3)` plus a tensor of shape `(3,)`.
b) A tensor of shape `(2, 3)` plus a tensor of shape `(1, 3)`.
c) A tensor of shape `(2, 3)` plus a tensor of shape `(2, 3)`.
d) A tensor of shape `(2, 3)` plus a scalar tensor.

## 9. Multiplication

Explain the difference between `A * B` and `A @ B`. Assume both operations are valid for the two-dimensional tensors A and B.

## 10. Creating random tensors

Which statement is correct?

a) `torch.rand(2, 3)` and `torch.randn(2, 3)` generate the same distribution.
b) `torch.rand(2, 3)` draws uniform values in [0, 1); `torch.randn(2, 3)` draws standard-normal values.
c) `torch.randn(2, 3)` can only generate positive values.
d) Both calls create a tensor of shape `(3, 2)`.

## 11. Autograd

Fill in both blanks. Explain what information is stored in `x.grad`; you do not need to calculate its numerical value.

```python
x = torch.tensor(4.0, __________=True)
y = x**2 + 3*x
y.__________()
print(x.grad)
```

## 12. Retaining intermediate gradients

In the following code, why is `z.retain_grad()` included?

```python
w = torch.tensor(0.5, requires_grad=True)
x = torch.tensor(2.0)
z = w * x
z.retain_grad()
loss = z**2
loss.backward()
print(z.grad)
```

a) It updates `z` using gradient descent.
b) It converts `z` into a model weight.
c) It prevents any gradient from reaching `w`.
d) It keeps the intermediate tensor's gradient available in `z.grad`.

## 13. Multiple observations versus multiple features

Compare the shapes of `z1` and `z2`.

```python
x = torch.tensor([2.0, 4.0, 1.0])

w1 = torch.tensor(0.3, requires_grad=True)
b1 = torch.tensor(1.0, requires_grad=True)
z1 = w1 * x + b1

w2 = torch.tensor([0.3, 0.2, 0.1], requires_grad=True)
b2 = torch.tensor(1.0, requires_grad=True)
z2 = torch.dot(w2, x) + b2
```

a) Both have shape `(3,)`.
b) `z1` has shape `(3,)`; `z2` is a scalar.
c) `z1` is a scalar; `z2` has shape `(3,)`.
d) Both are scalars.

## 14. Generating and splitting data

Consider the notebook's data-generation code:

```python
num_samples = 1200
X = -3 + 6 * torch.rand(num_samples, 1)
y = torch.sin(X) + 0.35 * torch.randn_like(X)

indices = torch.randperm(num_samples)
train_end = int(0.70 * num_samples)
val_end = int(0.85 * num_samples)

train_idx = indices[:train_end]
val_idx = indices[train_end:val_end]
test_idx = indices[val_end:]
```

Which description is correct?

a) There are 840 training, 180 validation, and 180 test observations, with no overlapping indices.
b) There are 840 training, 1020 validation, and 180 test observations.
c) `randperm` can repeat an index, so the splits necessarily overlap.
d) `randn_like(X)` adds a single identical noise value to every observation.

## 15. Mini-batches

The training set contains 840 observations.

```python
from torch.utils.data import TensorDataset, DataLoader
train_loader = DataLoader(
    TensorDataset(X_train, y_train),
    batch_size=32,
    shuffle=True
)
```

With the default `drop_last=False`, how many batches are processed in one epoch?

a) 26 batches; the remaining observations are automatically discarded.
b) 840 batches of size 32.
c) 27 batches: 26 of size 32 and one of size 8.
d) 32 batches, because `batch_size` sets the number of batches.

## 16. Network architecture

Consider the notebook's network:

```python
network = nn.Sequential(
    nn.Linear(1, 128),
    nn.ReLU(),
    nn.Linear(128, 128),
    nn.ReLU(),
    nn.Linear(128, 128),
    nn.ReLU(),
    nn.Linear(128, 1)
)
```

For input shape `(32, 1)`, which description is correct?

a) Four hidden layers; output shape `(32, 128)`.
b) Three hidden layers; output shape `(1, 32)`.
c) One hidden layer; output shape `(32, 1)`.
d) Three hidden layers; output shape `(32, 1)`.

## 17. Activation functions

Why use ReLU between the linear layers, while leaving the final regression output without a sigmoid?

Answer in one or two sentences.

## 18. Loss and optimizer

Which statement correctly describes this code?

```python
loss_fn = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.005)
```

a) MSE changes the weights; Adam measures the prediction error.
b) MSE measures regression error; Adam uses gradients to update the model parameters.
c) Adam determines the training/validation split.
d) The learning rate is a weight learned automatically by `loss.backward()`.

## 19. Training-step order

Fill in the three missing method names.

```python
predictions = model(xb)
loss = loss_fn(predictions, yb)
optimizer.____________()
loss.____________()
optimizer.____________()
```

Which of those three calls actually changes the model weights?

## 20. Clearing gradients

What would normally happen if `optimizer.zero_grad()` were omitted across successive training batches?

a) The previous gradients would be automatically cleared by `model.train()`.
b) The weights would reset to their initial random values.
c) Gradients would accumulate across backward passes.
d) The loss could no longer be computed in the forward pass.

## 21. Validation mode

**True or false:** Calling `model.eval()` automatically disables gradient tracking, so `torch.no_grad()` has no separate purpose. Briefly justify.

## 22. Saving the best checkpoint

Why does the notebook use `value.detach().clone()` when saving the best model state?

```python
if val_loss < best_val_loss:
    best_val_loss = val_loss
    best_state = {
        name: value.detach().clone()
        for name, value in model.state_dict().items()
    }
```

a) To preserve independent copies of the best parameters without a gradient connection.
b) To double the number of hidden layers.
c) To save only the gradients while discarding the weights.
d) To guarantee that future epochs cannot have worse validation loss.

## 23. Interpreting loss curves

The table gives values from a hypothetical training run. These are practice values, not the notebook's recorded results.

| Epoch | Training MSE | Validation MSE |
|---|---:|---:|
| 1 | 0.30 | 0.32 |
| 10 | 0.16 | 0.18 |
| 30 | 0.10 | 0.20 |
| 60 | 0.07 | 0.25 |

a) Among these four epochs, which checkpoint should be saved using the notebook's selection rule?
b) What does the later combination of falling training loss and rising validation loss suggest?

## 24. Test evaluation and plotting

Consider the notebook's plotting pattern, assuming the input and model are on compatible devices:

```python
x_grid = torch.linspace(-3, 3, 500).reshape(-1, 1)
model.eval()
with torch.no_grad():
    predictions = model(x_grid.to(device)).cpu().numpy()
```

a) What is `x_grid.shape`?
b) Why are `.cpu()` and `.numpy()` used here?
c) Should the test set be used each epoch to select the best checkpoint? Briefly explain.

---

Stop here before checking answers.

[Separate answer key](PyTorch_Practice_Quiz_Answer_Key.md) · [Condensed study guide](PyTorch_Study_Guide.md)
