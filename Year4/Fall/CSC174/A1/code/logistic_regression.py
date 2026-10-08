import numpy as np
import warnings
warnings.filterwarnings("ignore", category=RuntimeWarning)

class LogisticRegression:

	"""
	Object representing a logistic regression model.

	"""

	def __init__(self):

		"""
		Constructor called when object is initialized.

		"""

		###################
		## DO NOT MODIFY ##
		###################

		# initialize parameters to None
		self.w = None # 1d np.ndarray of shape (d,)
		self.b = None # float


	def sigmoid(self, x):

		"""
		Sigmoid function.

		Args:
			x (np.ndarray): NumPy array.

		Returns:
			np.ndarray: NumPy array containing the sigmoid of each value in x.

		"""

		## TODO
		probability = (1/(1+(np.exp(-x))))
		return probability


	def bce_loss(self, y, y_hat, epsilon=1e-16):

		"""
		Computes binary cross-entropy (BCE) loss.

		Args:
			y (np.ndarray): True binary target values.
			y_hat (np.ndarray): Predicted probabilities.
			epsilon (float): Small value used for numerical stability.

		Returns:
			float: Mean binary cross-entropy loss.

		"""

		# DO NOT MODIFY THIS LINE OR PLACE ANY LINES OF CODE ABOVE IT
		# clip y_hat between eps and 1-eps for numerical stability
		y_hat = np.clip(y_hat, epsilon, 1 - epsilon)

		## TODO

		bce_loss = float(-np.mean(y * np.log(y_hat) + (1-y) * np.log(1-y_hat)))

		return bce_loss


	def bce_gradients(self, y, y_hat, X):

		"""
		Compute the gradients of the BCE loss with respect to w and b.

		Args:
			y (np.ndarray): True target values with shape (n,).
			y_hat (np.ndarray): Predicted probabilities with shape (n,).
			X (np.ndarray): Input features with shape (n, d).

		Returns:
			dL_dw (np.ndarray): Gradient with respect to w, with shape (d,).
			dL_db (float): Gradient with respect to b.

		"""

		## TODO
		N = len(y)
		dL_dw = (1/N)*(X.T)@(y_hat-y)
		dL_db = float(np.mean(y_hat-y))

		return dL_dw, dL_db


	def train_batch_gradient_descent(self, X, y, learning_rate, num_epochs):

		"""
		Train a logistic regression model using BCE loss and batch gradient descent.

		1) Initialize w to a numpy array of zeros with d elements, and initialize b to a scalar value of 0.
		2) Iterate num_epochs times.
			a) Compute the predictions y_hat for all training examples
			b) Compute and store the loss
			c) Compute the gradients with respect to the parameters
			d) Update the parameters using the gradient descent update rule
		3) Compute and store the loss after the final parameter update (after the loop)
		4) Store the final w, b, and return a list of the loss history

		Args:
			X (np.ndarray): Training features with shape (n, d).
			y (np.ndarray): Training targets with shape (n,).
			learning_rate (float): Learning rate used for updates.
			num_epochs (int): Number of training epochs.

		Returns:
			list: Loss history containing the initial loss and the loss after each epoch.
		"""
		## TODO
		# list to store loss history
		loss_history = []
		d = X.shape[1] #columns of X (1 is columns, 0 is rows) 
		# store w and b
		self.w = np.zeros(d) 
		self.b = 0.0
		
		for training in range(num_epochs):
			z = X @ self.w + self.b 
			y_hat = self.sigmoid(z)
			loss = self.bce_loss(y,y_hat)
			loss_history.append(loss) 
			dL_dw, dL_db = self.bce_gradients(y,y_hat,X)
			self.w = self.w - learning_rate * dL_dw
			self.b = self.b - learning_rate * dL_db
		z = X @ self.w + self.b
		y_hat = self.sigmoid(z)
		loss = self.bce_loss(y, y_hat)
		loss_history.append(loss)
  
		return loss_history


	
	def predict(self, X, threshold=0.5):

		"""
		Compute predictions using the stored parameters. Predicted probabilities >= threshold
		should be predicted as the positive class (1) and predicted probabilities < threshold
		should be predicted as the negative class (0)


		Args:
			X (np.ndarray): Features with shape (n, d).

		Returns:
			np.ndarray: Predictions with shape (n,).
		
		"""

		## TODO
		z = X @ self.w + self.b 
		y_hat = self.sigmoid(z)
		y_hat_class = (y_hat >= threshold).astype(int)
		return y_hat_class

	

	def name(self):

		"""
		Name of model
	
		"""

		return 'Logistic Regression'


