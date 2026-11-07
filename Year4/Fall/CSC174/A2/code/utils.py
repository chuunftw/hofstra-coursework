import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from os.path import join
from sklearn.datasets import make_blobs, make_moons

"""
utility functions

"""


def sigmoid_derivative(x):

  """
  Compute the derivative of the sigmoid activation function. Use
  the sigmoid function provided.

  Args:
    x (numpy.ndarray): Input array of any shape.

  Returns:
    numpy.ndarray: Array of the same shape as x containing 
                   the derivative of the sigmoid function.
  
  """

  # TODO
  s = sigmoid(x)
  s_d = s*(1-s)
  return s_d


def softmax(logits):

  """
  Compute the softmax function.

  Args:
    logits (numpy.ndarray): Two-dimensional array of shape (batch_size, num_classes) 
                            containing the output logits.

  Returns:
    numpy.ndarray: Array of shape (batch_size, num_classes) containing 
                   the predicted class probabilities. Each row sums to 1.
 
  """

  # TODO
  logits = logits - np.max(logits, axis=1, keepdims=True) # cases w/ larges scores to handle 
  softmax = (np.exp(logits) / np.sum(np.exp(logits), axis = 1, keepdims=True))
  return softmax 


def cross_entropy_loss(y_true, y_prob):

  """
  Compute the average cross-entropy loss.

  Args:
    y_true (numpy.ndarray): One-hot encoded class labels of shape (n_samples, n_classes).

    y_prob (numpy.ndarray): Predicted class probabilities of shape (n_samples, n_classes).

  Returns:
    float: The average cross-entropy loss across all samples.
  
  """

  # TODO
  n_samples, n_classes = y_true.shape
  zero = 0.00000000000000000000001
  y_prob = np.clip(y_prob, zero, 1 - zero)

  loss = -np.sum(y_true * np.log(y_prob)) / n_samples
  return loss



def one_hot_encode(y, num_classes):

  """
  One-hot encode a vector of class labels.

  Args:
    y (numpy.ndarray): One-dimensional array of integer class labels of shape (n_samples,).

    num_classes (int): Total number of classes.

  Returns:
    numpy.ndarray: One-hot encoded array of shape (n_samples, num_classes).
  
  """

  # TODO
  encode = np.zeros((len(y), num_classes))
  for row, label in enumerate(y):
    encode[row,label] = 1 
  return encode



###############################
#### DO NOT MODIFY BELOW ######
###############################


def sigmoid(x):

  """
  Compute the sigmoid activation function.

  Args:
    x (numpy.ndarray): Input array of any shape.

  Returns:
    numpy.ndarray: Array of the same shape as x containing 
                   the sigmoid activations.

  """

  return 1 / (1 + np.exp(-x))


def create_linearly_separable_dataset():
   
    """
    Create a linearly separable dataset with two features and three classes.

    Returns:
        X (np.ndarray): Feature matrix of shape (n_samples, 2).
        y (np.ndarray): Class labels of shape (n_samples,).

    """

    # number of samples
    n_samples = 30

    # random state
    random_state = 42

    X, y = make_blobs(
        n_samples=n_samples,
        centers=[(-5, -5), (0, 5), (5, -5)],
        cluster_std=0.8,
        random_state=random_state
    )

    return X, y



def create_concentric_circles_dataset():

  """
  Create a concentric circles dataset with two features and three classes.

  Returns:
    X (np.ndarray): Feature matrix of shape (n_samples, 2).
 
    y (np.ndarray): Class labels of shape (n_samples,).

  """

  random_state = 42
  rng = np.random.default_rng(random_state)

  n_outer = 100
  n_inner = 100
  n_center = 100

  # outer circle (radius 5)
  theta = rng.uniform(0, 2 * np.pi, n_outer)
  outer = np.column_stack((
    5 * np.cos(theta),
    5 * np.sin(theta)
  ))
  outer += rng.normal(scale=0.05, size=outer.shape)

  # inner circle (radius 2)
  theta = rng.uniform(0, 2 * np.pi, n_inner)
  inner = np.column_stack((
    2 * np.cos(theta),
    2 * np.sin(theta)
  ))
  inner += rng.normal(scale=0.05, size=inner.shape)

  # center cluster
  center = rng.normal(scale=0.15, size=(n_center, 2))

  # combine
  X = np.vstack((inner, center, outer))
  y = np.array(
    [0] * n_inner +
    [1] * n_center +
    [2] * n_outer
  )

  return X, y


def create_two_moons_dataset():

    """
    Create a two moons dataset with two features and two classes.

    Returns:
        X (np.ndarray): Feature matrix of shape (n_samples, 2).

        y (np.ndarray): Class labels of shape (n_samples,).
    """

    # number of samples
    n_samples = 300

    # random state
    random_state = 42

    # create dataset
    X, y = make_moons(
        n_samples=n_samples,
        noise=0.15,
        random_state=random_state
    )

    return X, y

def plot_decision_boundary(X, y, model, title, resolution=0.02):
   
  """
  Visualizes the decision boundary for a 2D classification problem.

  Parameters:
  - X: Feature matrix (2D, shape: [n_samples, 2])
  - y: Target labels (1D, shape: [n_samples])
  - model: A trained classifier with a predict method
  - resolution: Resolution of the mesh grid (default is 0.02)
  """

  # create figure
  fig, ax = plt.subplots()

  # Define the mesh grid over the feature space
  x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
  y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
  xx, yy = np.meshgrid(np.arange(x_min, x_max, resolution), np.arange(y_min, y_max, resolution))

  # Predict the class labels for each point in the mesh grid
  Z = model.predict(np.c_[xx.ravel(), yy.ravel()])
  Z = Z.reshape(xx.shape)

  cmap = plt.cm.RdYlBu
  norm = colors.BoundaryNorm(boundaries=np.arange(-0.5, np.max(y) + 1.5), ncolors=cmap.N)
  
  # Plot the decision boundary
  ax.contourf(xx, yy, Z, alpha=0.75, cmap=cmap)

  # Plot the points in the dataset
  scatter = ax.scatter(X[:, 0], X[:, 1], c=y, edgecolors='k',norm=norm, cmap=cmap, s=50)

  # Add labels and title
  ax.set_xlabel('Feature 1')
  ax.set_ylabel('Feature 2')
  ax.set_title(title)

  # Generate class labels like "Class 0", "Class 1", ...
  unique_classes = np.unique(y)
  class_labels = [f'Class {cls}' for cls in unique_classes]

  # Create custom legend with the class labels
  handles = [plt.Line2D([0], [0], marker='o', color='w', markerfacecolor=cmap(norm(cls)), markersize=10) for cls in unique_classes]

  # Create the legend
  ax.legend(handles, class_labels, loc='best')

  return fig


def plot_dataset(X, y, title, xlabel='Feature 1', ylabel='Feature 2'):
   
  """
  Visualizes a dataset

  Parameters:
  - X: Feature matrix (2D, shape: [n_samples, 2])
  - y: Target labels (1D, shape: [n_samples])

  """

  cmap = plt.cm.RdYlBu
  norm = colors.BoundaryNorm(boundaries=np.arange(-0.5, np.max(y) + 1.5), ncolors=cmap.N)
  
  # Plot the points in the dataset
  scatter = plt.scatter(X[:, 0], X[:, 1], c=y, edgecolors='k',norm=norm, cmap=cmap, s=50)

  # Add labels and title
  plt.xlabel(xlabel)
  plt.ylabel(ylabel)
  plt.title(title)

  # Generate class labels like "Class 0", "Class 1", ...
  unique_classes = np.unique(y)
  class_labels = [f'Class {cls}' for cls in unique_classes]

  # Create custom legend with the class labels
  handles = [plt.Line2D([0], [0], marker='o', color='w', markerfacecolor=cmap(norm(cls)), markersize=10) for cls in unique_classes]

  # Create the legend
  plt.legend(handles, class_labels, loc='best')

  # Show the plot
  plt.show()


