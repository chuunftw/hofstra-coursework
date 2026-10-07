import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib import colors
from os.path import join
from sklearn.datasets import fetch_california_housing

"""
utility functions

"""


###############################
#### DO NOT MODIFY BELOW ######
###############################

def accuracy_score(y_true, y_pred):

  """
  Calculates the accuracy score beween truth and predictions

  Args:
  y_true (1d np.array): array of truth labels
  y_pred (1d np.array): array of prediction labels

  Returns:
  float: accuracy score

  """

  accuracy = np.mean(y_true == y_pred)

  return accuracy


def load_lin_reg_1d_linear_dataset():
 
  """
  Generate a synthetic one-feature linear regression dataset.

  Returns:
    X (np.ndarray): Feature values with shape (n, 1).
    y (np.ndarray): Target values with shape (n,).

  """

  rng = np.random.default_rng(42)

  n = 200

  X = rng.uniform(-10, 10, size=(n, 1))

  # Underlying relationship: y = 3x + 5 + noise
  noise = rng.normal(0, 3, size=n)
  y = 3 * X[:, 0] + 5 + noise

  return X, y


def load_lin_reg_1d_nonlinear_dataset():

  """
  Generate a synthetic one-feature nonlinear regression dataset.

  The underlying relationship is quadratic (a parabola).

    Returns:
    X (np.ndarray): Feature values with shape (n, 1).
    y (np.ndarray): Target values with shape (n,).
  """

  rng = np.random.default_rng(42)

  n = 200

  X = rng.uniform(-10, 10, size=(n, 1))

  # Underlying relationship: y = 2x^2 - 3x + 5 + noise
  noise = rng.normal(0, 10, size=n)
  y = 2 * X[:, 0] ** 2 - 3 * X[:, 0] + 5 + noise

  return X, y


def load_lin_reg_2d_dataset():

  """
  Generate a synthetic two-feature linear regression dataset.

  Returns:
    X (np.ndarray): Feature values with shape (n, 2).
    y (np.ndarray): Target values with shape (n,).

  """

  rng = np.random.default_rng(42)

  n = 500

  X = rng.uniform(-10, 10, size=(n, 2))

  # Underlying relationship: y = 3x1 - 2x2 + 5 + noise
  noise = rng.normal(0, 3, size=n)
  y = 3 * X[:, 0] - 2 * X[:, 1] + 5 + noise

  return X, y



def load_california_housing_dataset():

  """
  Load the California Housing dataset with standardized features.

  Returns:
    X (np.ndarray): Standardized features with shape (n, d).
    y (np.ndarray): Target values with shape (n,).
  
  """

  # load dataset
  housing = fetch_california_housing()

  X = housing.data
  y = housing.target

  # standardize each feature
  X_mean = np.mean(X, axis=0)
  X_std = np.std(X, axis=0)

  X = (X - X_mean) / X_std

  return X, y




def load_log_reg_2d_dataset():

  """
  Generate a synthetic two-feature linearly separable
  binary classification dataset with a small margin,
  sparse points, and a few outliers.

  Returns:
    X (np.ndarray): Feature values with shape (n, 2).
    y (np.ndarray): Binary labels with shape (n,).
  
  """

  rng = np.random.default_rng(42)

  # Generate sparse points
  n = 100

  X = rng.uniform(-50, 50, size=(n, 2))

  # Decision boundary:
  # x1 + x2 = 5
  boundary = X[:, 0] + X[:, 1] - 5

  # Small margin
  margin = 0.75

  # Keep points away from the boundary
  mask = np.abs(boundary) > margin

  X = X[mask]
  boundary = boundary[mask]

  # Assign classes
  y = (boundary > 0).astype(float)

  # Add a few outliers far from the main group
  outliers = np.array([
  [-9.0, -8.0],
  [-8.0, 9.0],
  [9.0, -7.0],
  [8.0, 8.0]
  ])

  # Calculate which side of the boundary each outlier is on
  outlier_boundary = outliers[:, 0] + outliers[:, 1] - 5

  outlier_y = (outlier_boundary > 0).astype(float)

  # Add outliers to dataset
  X = np.vstack((X, outliers))
  y = np.hstack((y, outlier_y))

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
  ax.set_xlabel('Feature 0')
  ax.set_ylabel('Feature 1')
  ax.set_title(title)

  # Generate class labels like "Class 0", "Class 1", ...
  unique_classes = np.unique(y).astype(int)
  class_labels = [f'Class {cls}' for cls in unique_classes]

  # Create custom legend with the class labels
  handles = [plt.Line2D([0], [0], marker='o', color='w', markerfacecolor=cmap(norm(cls)), markersize=10) for cls in unique_classes]

  # Create the legend
  ax.legend(handles, class_labels, loc='best')

  return fig



def plot_dataset(X, y, title, xlabel='Feature 0', ylabel='Feature 1', legend=True):
   
  """
  Visualizes a dataset

  Parameters:
  - X: Feature matrix (2D, shape: [n_samples, 2])
  - y: Target labels (1D, shape: [n_samples])

  """

  # create figure
  fig, ax = plt.subplots()

  cmap = plt.cm.RdYlBu
  norm = colors.BoundaryNorm(boundaries=np.arange(-0.5, np.max(y) + 1.5), ncolors=cmap.N)
  
  # Plot the points in the dataset
  scatter = plt.scatter(X[:, 0], X[:, 1], c=y, edgecolors='k',norm=norm, cmap=cmap, s=50)

  # Add labels and title
  ax.set_xlabel(xlabel)
  ax.set_ylabel(ylabel)
  ax.set_title(title)

  # Generate class labels like "Class 0", "Class 1", ...
  unique_classes = np.unique(y)
  class_labels = [f'Class {cls}' for cls in unique_classes]

  # Create custom legend with the class labels
  handles = [plt.Line2D([0], [0], marker='o', color='w', markerfacecolor=cmap(norm(cls)), markersize=10) for cls in unique_classes]

  # Create the legend
  ax.legend(handles, class_labels, loc='best')

  return fig, ax


