import numpy as np

class LinearRegression:

	"""
	Object representing a linear regression model.

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


	def train_closed_form(self, X, y):

		"""
		Train a linear regression model using the closed-form solution.

		1) Add a column of ones to X, creating X_tilde to account for the bias.
		2) Compute the closed-form solution for MSE loss.
		3) Extract w and b from w_tilde and store them as class attributes.

		Args:
			X (np.ndarray): Training features with shape (n, d).
			y (np.ndarray): Training targets with shape (n,).
		
		"""

		## TODO

		# store w and b 
		self.w = np.array([])
		self.b = 0.0


	def mse_loss(self, y, y_hat):

		"""
		Compute the mean squared error (MSE) loss.

		Args:
			y (np.ndarray): True target values with shape (n,).
			y_hat (np.ndarray): Predicted values with shape (n,).

		Returns:
			float: The mean squared error between y and y_hat.

		"""

		## TODO

		mse_loss = 0.0

		return mse_loss


	def mse_gradients(self, y, y_hat, X):

		"""
		Compute the gradients of the MSE loss with respect to w and b.

		Args:
			y (np.ndarray): True target values with shape (n,).
			y_hat (np.ndarray): Predicted values with shape (n,).
			X (np.ndarray): Input features with shape (n, d).

		Returns:
			dL_dw (np.ndarray): Gradient with respect to w, with shape (d,).
			dL_db (float): Gradient with respect to b.

		"""

		## TODO

		dL_dw = np.array([])
		dL_db = 0.0

		return dL_dw, dL_db


	def train_batch_gradient_descent(self, X, y, learning_rate, num_epochs):

		"""
		Train a linear regression model using MSE loss and batch gradient descent.

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
	
		# store w and b
		self.w = np.array([])
		self.b = 0.0
		
		return loss_history

		

	def predict(self, X):

		"""
		Compute predictions using the stored parameters.

		Args:
			X (np.ndarray): Features with shape (n, d).

		Returns:
			np.ndarray: Predictions with shape (n,).
		
		"""

		## TODO

		y_hat = np.array([])

		return y_hat

	

	def name(self):

		"""
		Name of model
	
		"""

		return 'Linear Regression'

