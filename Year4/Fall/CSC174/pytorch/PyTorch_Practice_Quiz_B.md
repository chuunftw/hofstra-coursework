# CSC174 · PyTorch Practice Quiz B

Name ________________________　 Date ______________

Circle one answer for each multiple-choice question. For code questions, assume `import torch` and `from torch import nn`. Each question supplies its own inputs unless it refers to the preceding question.

**1.** Circle the import that lets you write `nn.Linear(1, 128)`.

a) import torch as nn  
b) from torch import nn  
c) import numpy as nn  
d) from torch import Linear  

---

**2.** Given `a = torch.tensor(7)` and `b = torch.tensor([7])`, write `tuple(a.shape)` and `tuple(b.shape)`.

---

**3.** Which line creates two matrices, each with three rows and four columns, filled with ones?

a) torch.zeros(2, 3, 4)  
b) torch.ones(3, 4, 2)  
c) torch.ones(2, 3, 4)  
d) torch.ones(2, 12)  

---

**4.** Circle the call that could produce a negative value. What range of values can the other call produce?

| Choice 1 | Choice 2 |
|---|---|
| `torch.rand(2, 3)` | `torch.randn(2, 3)` |

---

**5.** Given the input and output, fill in the slice. Keep all three axes.

```python
x = torch.tensor([[[1, 2, 3], [4, 5, 6]],
                  [[7, 8, 9], [10, 11, 12]],
                  [[13, 14, 15], [16, 17, 18]]])
```

| Output | Solution |
|---|---|
| `tensor([[[2, 3]], [[14, 15]]])` | `x[________________]` |

---

**6.** Given `x = torch.ones(2, 3, 4)`, which reshape is valid?

a) x.reshape(3, 4)  
b) x.reshape(2, 8)  
c) x.reshape(5, 5)  
d) x.reshape(4, 6)  

---

**7.** Given `x = torch.tensor([[2., 6.], [4., 8.]])`, write the values of `x.sum()`, `x.mean()`, and `x.max()`.

---

**8.** Which addition pairs every element with an element at the same position without expanding either operand?

a) (2, 3) + (3,)  
b) (2, 3) + (2, 1)  
c) (2, 3) + (2, 3)  
d) (2, 3) + a scalar  

---

**9.** Given the matrices below, compute **only the top-left entry** of each result. Explain which entries you used.

```python
A = torch.tensor([[2, 1], [0, 3]])
B = torch.tensor([[4, 0], [5, 2]])
```

| Option 1 | Option 2 |
|---|---|
| `A * B` | `A @ B` |

---

**10.** Given `x = torch.tensor([[1, 2, 3], [4, 5, 6]])`, what is `x.T[1]`?

a) tensor([2, 5])  
b) tensor([4, 5, 6])  
c) tensor([1, 4])  
d) tensor(2)  

---

**11.** What two numbers are printed?

```python
x = torch.tensor(2., requires_grad=True)
y = x**2 + 3*x
y.backward()
print(x.item(), x.grad.item())
```

---

**12.** Fill in the line that lets you inspect the intermediate gradient `z.grad` after backpropagation.

```python
w = torch.tensor(2., requires_grad=True)
z = 3*w + 1
________________
p = torch.sigmoid(z)
loss = -torch.log(p)
loss.backward()
```

---

**13.** A binary classifier predicts `p = 0.9` for an example labeled `0`. Which expression gives its binary cross-entropy loss?

a) -torch.log(p)  
b) -torch.log(1-p)  
c) torch.log(1-p)  
d) (p-1)**2  

---

**14.** Given `x = torch.tensor([1., 3., 2.])`, a scalar weight `w`, and a scalar bias `b`, how many predictions does `torch.sigmoid(w*x + b)` produce? After averaging the three losses and calling `backward()`, how many values are in `w.grad`? Assume `w` is a leaf tensor with `requires_grad=True`.

---

**15.** The same `x` now represents **one** observation with three features. Given `w = torch.tensor([2., 1., 4.])` and `b = 1.`, write one line using `torch.dot` that computes the score before sigmoid. Give its value.

---

**16.** What are the shape and possible range of `X`? What does the factor `0.35` control?

```python
torch.manual_seed(42)
X = -3 + 6*torch.rand(1200, 1)
y = torch.sin(X) + 0.35*torch.randn_like(X)
```

---

**17.** Given `idx = torch.randperm(1200)`, complete the two slices for a 70% / 15% / 15% split. Why does the demo use the same `train_idx` for `X` and `y`?

```python
train_idx = idx[:840]
val_idx   = idx[________]
test_idx  = idx[________]
```

---

**18.** The dashed line plots `torch.sin(x_plot)`. The dots plot `X_train` against `y_train`. Why can a training dot appear below the dashed line even when the code runs correctly?

---

**19.** A `DataLoader` uses `TensorDataset(X_train, y_train)`, `batch_size=32`, and `shuffle=True`. With 840 observations and default `drop_last=False`, which describes one epoch?

a) 26 batches of 32  
b) 27 batches of 32  
c) 26 batches of 32 and one of 8  
d) 32 batches of 26 and one of 8  

---

**20.** When the loader shuffles the dataset, which item stays paired with `X_train[i]`?

a) The target at the new position before shuffling  
b) y_train[i]  
c) The first target in the batch  
d) A randomly chosen target  

---

**21.** A batch with shape `(8, 1)` enters the demo’s MLP. Fill in the shapes after the first linear layer, its ReLU, and the final linear layer.

```python
nn.Linear(1, 128)    # (____, ____)
nn.ReLU()            # (____, ____)
# two more hidden layers of width 128 with ReLU
nn.Linear(128, 1)    # (____, ____)
```

---

**22.** The final layer predicts `y = sin(x) + noise`. What restriction would adding `nn.ReLU()` immediately after the final layer impose on the predictions?

---

**23.** Given `layer = nn.Linear(3, 2)`, what does `sum(p.numel() for p in layer.parameters())` return? Include the default bias.

a) 2  
b) 5  
c) 6  
d) 8  

---

**24.** Given the following columns, what value does `nn.MSELoss()(pred, target).item()` return?

```python
pred   = torch.tensor([[3.], [1.]])
target = torch.tensor([[1.], [2.]])
```

---

**25.** A CUDA-capable machine runs `device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')` and `model = SineMLP().to(device)`. The loader returns CPU tensors. Complete the line before computing the predictions and loss.

```python
xb, yb = ____________________________
pred = model(xb)
loss = loss_fn(pred, yb)
```

---

**26.** The demo uses `torch.optim.Adam(model.parameters(), lr=0.005)`. After computing a batch loss, arrange the three lines in the demo’s order. Circle the one that changes the parameter values.

| A | B | C |
|---|---|---|
| `optimizer.step()` | `optimizer.zero_grad()` | `loss.backward()` |

---

**27.** Two training batches contain 4 and 2 examples. Their mean losses are 1.0 and 4.0. Which expression gives the mean loss across all six examples?

a) (1+4)/2  
b) (4*1+2*4)/6  
c) (1+4)/6  
d) (4*1+2*4)/2  

---

**28.** Describe the job of each line during validation. Which line controls whether PyTorch records operations for backpropagation?

```python
model.eval()
with torch.no_grad():
    val_loss = loss_fn(model(X_val_device), y_val_device)
```

---

**29.** Read the loss curves from the values below. At which epoch should the demo save its best-validation model? What training behavior do epochs 3–4 suggest?

| Epoch | Training MSE | Validation MSE |
|---|---:|---:|
| 1 | 0.44 | 0.40 |
| 2 | 0.29 | 0.26 |
| 3 | 0.21 | 0.30 |
| 4 | 0.16 | 0.35 |

---

**30.** When validation loss improves, the demo saves a copy of the model parameters. Why must those saved values stay independent of later training updates? Fill in the method that restores them.

```python
best_model = SineMLP().to(device)
best_model.________________(best_state)
```

---

**31.** The final model has test MSE 0.19. The best-validation model has test MSE 0.21. Which statement follows?

a) The final model had the lowest validation MSE.  
b) The checkpoint was saved incorrectly.  
c) The final model had lower error on this test set.  
d) The test set should determine the checkpoint after each epoch.  

---

**32.** Complete the plotting code. The grid must contain 500 one-feature observations, and the result must be a NumPy array even when the model runs on CUDA.

```python
x_grid = torch.linspace(-3, 3, 500).reshape(________)
with torch.no_grad():
    curve = best_model(x_grid.to(device)).________().numpy()
```

On the resulting plot, which line gives the underlying signal you can compare both fitted curves against?
