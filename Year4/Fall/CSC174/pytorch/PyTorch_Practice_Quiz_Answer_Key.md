# PyTorch Practice Quiz — Answer Key

Answers to [PyTorch_Practice_Quiz.md](PyTorch_Practice_Quiz.md). Section numbers refer to [PyTorch_demo_solutions.ipynb](PyTorch_demo_solutions.ipynb).

## 1. c — GPU use is not automatic

Importing PyTorch does not move every tensor to a GPU. The notebook selects a device and explicitly moves the model and inputs with `.to(device)`. **Sections 2, 4, 7, 9.**

## 2. False

Tensors can have more than three dimensions. The notebook's scalar, vector, matrix, and 3D examples illustrate dimensionality; they do not set a maximum. **Section 2.**

## 3. Reproducible pseudorandom draws

The seed initializes PyTorch's random-number generators so the same sequence of random operations can be repeated under the same conditions. It does not make the generated values equal to 42 or make all draws identical. A seed alone does not guarantee identical results across all devices, versions, or nondeterministic operations. **Section 4.**

## 4. b — torch.Size([2, 3])

There are two rows, each containing three elements. Shape describes the size of each dimension, not just the total element count. **Section 2.**

## 5. x[:, :, 1:]

```python
x[:, :, 1:]
```

Keep both blocks, both rows in each block, and columns starting at index 1. `x[:, :, 1:3]` also works. The output shape is `(2, 2, 2)`. This extends the notebook's slicing syntax to the 3D format in the supplied NumPy quiz. **Section 2.**

## 6. d — (6, 4)

The original tensor has 2 × 3 × 4 = 24 elements, and 6 × 4 = 24. Reshaping preserves the number of elements. **Section 2.**

## 7. a — 20, then 5

`sum()` adds all four elements; `mean()` divides that sum by four. Neither call specifies a dimension, so both reduce the entire tensor to a scalar. **Section 2.**

## 8. c — Both operands already have shape (2, 3)

Corresponding elements can be added without expanding either operand's shape. The other choices apply a vector, a single row, or a scalar across a larger tensor. The notebook uses scalar broadcasting in its multiple-input example. **Sections 2–3.**

## 9. Elementwise versus matrix multiplication

`A * B` multiplies corresponding entries, with broadcasting where applicable. `A @ B` uses row-by-column dot products. For matrix multiplication, shapes `(m, k)` and `(k, n)` produce `(m, n)`; the inner dimensions must agree. **Section 2.**

## 10. b — Different random distributions

Both outputs have shape `(2, 3)`. `rand` uses a uniform distribution in [0, 1); `randn` uses a normal distribution with mean 0 and standard deviation 1, so negative values are possible. **Sections 2, 4.**

## 11. requires_grad; backward

```python
x = torch.tensor(4.0, requires_grad=True)
y = x**2 + 3*x
y.backward()
print(x.grad)
```

`x.grad` stores the derivative of y with respect to x at the current x. It describes how sensitive y is to a small change in x. It is not y's value or an updated x. Numerical check, not required by the question: 2x + 3 = 11. **Section 3.**

## 12. d — Store an intermediate gradient

Here `z` is an intermediate, non-leaf tensor produced by multiplication. Calling `retain_grad()` allows its gradient to be stored in `z.grad` after backpropagation. Without it, autograd can still propagate through z to w, but z's `.grad` is not populated by default. **Section 3.**

## 13. b — z1 is a vector; z2 is a scalar

The scalar w1 and b1 are broadcast over three x values, giving three outputs. The dot product combines three feature contributions into one score.

In the notebook, the first pattern represents three observations sharing one weight and bias; the second represents one observation with three features and three corresponding weights. Array length alone does not tell you which interpretation is intended. **Section 3.**

## 14. a — 840 / 180 / 180

`train_end = 840`; `val_end = 1020`. The slice lengths are 840, 1020 − 840 = 180, and 1200 − 1020 = 180. A permutation contains each index once, and the slices do not overlap. `randn_like(X)` generates a whole noise tensor matching X's shape. **Section 4.**

## 15. c — 27 batches

26 × 32 = 832 observations, leaving 8 in the final batch. `batch_size` sets observations per batch, not batches per epoch. `TensorDataset` keeps each X paired with its y during shuffling. **Section 6.**

## 16. d — Three hidden layers; output shape (32, 1)

The hidden widths are 128, 128, and 128. The fourth linear layer is the output layer. Each of the 32 observations receives one prediction. ReLU does not change these shapes. **Section 7.**

## 17. Nonlinear hidden transformations; unrestricted regression output

ReLU lets the network model nonlinear relationships such as the sine curve. Without nonlinearities, a stack of affine linear layers still represents an affine linear function. A final sigmoid would restrict predictions to (0, 1), which is unsuitable for these sine targets, including negative values. **Sections 2, 7.**

## 18. b — MSE measures error; Adam updates parameters

The loss produces an error measure, backpropagation computes gradients, and the optimizer's `step()` uses them to change parameters. The learning rate is a chosen hyperparameter, not a model weight learned by backpropagation. **Sections 8–9.**

## 19. zero_grad; backward; step

```python
predictions = model(xb)
loss = loss_fn(predictions, yb)
optimizer.zero_grad()
loss.backward()
optimizer.step()
```

`optimizer.step()` changes the weights. `zero_grad()` clears previous gradients; `backward()` computes and accumulates gradients. Clearing gradients before the forward pass is also valid; the supplied blanks follow the notebook's order. **Section 9.**

## 20. c — Gradients accumulate

Backward passes add to existing parameter gradients. For this notebook's ordinary per-batch updates, clearing gradients prevents old batches from contributing again. Intentional gradient accumulation is possible, but is not what this loop implements. **Section 9.**

## 21. False

`model.eval()` selects evaluation behavior for layers that have different training and evaluation behavior. `torch.no_grad()` separately suppresses recording operations for gradient computation. Neither call trains the model.

This particular network contains Linear and ReLU layers, so switching modes alone does not change their forward behavior. **Sections 9, 11.**

## 22. a — Preserve an independent checkpoint

`clone()` copies the tensor's data so later optimizer updates do not change the saved values. `detach()` removes a gradient connection. Detaching alone does not create independent storage.

In this specific expression, `state_dict()` already returns detached tensors by default; cloning is the crucial step for protecting the saved parameter values. **Section 9.**

## 23. Epoch 10; evidence of overfitting

a) Epoch 10 has the lowest listed validation MSE: 0.18.

b) Training performance improves while validation performance worsens, suggesting the model is fitting training-specific patterns or noise and generalizing less well. More epochs do not guarantee better validation performance. **Sections 9–10.**

## 24. Grid shape, plotting conversion, and test-set role

a) `torch.Size([500, 1])`. `linspace` produces 500 evenly spaced values, and `reshape(-1, 1)` places them in one feature column.

b) `.cpu()` puts the predictions on the CPU; `.numpy()` converts the tensor to a NumPy array for the plotting code. Inside this no-grad block, the predicted outputs do not have a gradient graph requiring detachment.

c) No. The notebook selects the checkpoint using validation loss. The test set is used afterward to evaluate generalization. Repeatedly selecting models based on test performance compromises its role as an independent evaluation. **Sections 5, 9, 11–12.**

---

**Coverage:** Tensor operations (1–10), autograd (11–13), data and batches (14–15), architecture and optimization (16–20), validation and evaluation (21–24). Module imports are reviewed in the [study guide](PyTorch_Study_Guide.md).

**Verification:** Shapes, slice results, arithmetic, and training order were checked against the notebook and its saved outputs. The new practice snippets were not executed in a Python runtime.

Official references for API nuances: [Autograd](https://docs.pytorch.org/docs/stable/notes/autograd.html), [Reproducibility](https://docs.pytorch.org/docs/stable/notes/randomness.html), [DataLoader](https://docs.pytorch.org/docs/stable/data.html), [Linear](https://docs.pytorch.org/docs/stable/generated/torch.nn.Linear.html).
