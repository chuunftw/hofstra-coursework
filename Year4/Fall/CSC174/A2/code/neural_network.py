import numpy as np
from utils import one_hot_encode, softmax, sigmoid, cross_entropy_loss, sigmoid_derivative

class NeuralNetwork:

	"""
	A fully connected neural network model for multiclass classification
	
	"""

	def __init__(
		self, 
		input_size,
		hidden_layer_sizes, 
		output_size,
		batch_size,
		num_epochs,
		learning_rate,
		activation_function,
		random_seed=42
	):

		"""
		constructor called when object is initialized

		"""

		###################
		## DO NOT MODIFY ##
		###################

		# set random seed
		np.random.seed(random_seed)

		# store hyperparameters
		self.input_size = input_size 						# number of nodes in input layer
		self.hidden_layer_sizes = hidden_layer_sizes 		# list of hidden layer sizes
		self.output_size = output_size 						# number of nodes in output layer
		self.batch_size = batch_size 						# number of samples per batch
		self.num_epochs = num_epochs 						# number of training epochs
		self.learning_rate = learning_rate 					# learning rate
		self.activation_function = activation_function 		# activation (sigmoid or linear)

		# initialize parameters
		self.w, self.b = self.initialize_parameters()


	def initialize_parameters(self):
   
		"""
		Initialize the weights and biases for each layer of the neural network

		1) Initialize the weights by sampling from a standard normal distribution with mean = 0, standard deviation = 1.
		2) Initialize the biases to zero.

		Returns:
			w (list) : List of weight matrices. Each weight matrix should be a 2d numpy array.
			b (list) : List of bias vectors. Each bias vector should be a 1d numpy array.

		"""

		# TODO

		# initialize w and b as empty lists
		w, b = [], []

		# create a list of layer sizes
		layer_sizes = ...

		# iterate through layer sizes
		# create weights for each layer
		for i in range(...):

			# initialize weights using standard normal distribution
			# with mean=0 and variance=1
			w_layer = ...
			b_layer = ...

			# append layer weights and biases
			w.append(w_layer)
			b.append(b_layer)

		return w, b

	
	def forward_pass(self, X):

		"""
		Perform a forward pass through the neural network.

		1) Iterate through each layer.
			a) Compute the pre-activations Z = A @ W + b
			b) Compute the activations for all layers except for the last. 
				- implement sigmoid activation function
		2) After the loop, apply the softmax function to the logits (final pre-activations).
		3) Return the pre-activations (z), activations (a), and probabilities (y_prob)

		Args:
			X (2d numpy array): Input feature matrix of shape (batch_size, input_size),
								where each row corresponds to one example in the batch.

		Returns:
			z (list): List of pre-activations.
			a (list): List of activations.
			y_prob (2d numpy array): Predicted probabilities after softmax.
		
		"""

		# TODO

		# initialize pre-activations, activations, and probabilities
		z, a = [], []
		y_prob = None

		# append the input to the activations list
		a.append(X)

		# iterate through layers (weights)
		for i in range(...):

			# compute pre-activations from activations in previous layer
			z_layer = ...
			z.append(z_layer)

			# compute activation (except for last layer)
			if i < len(self.w) - 1:
				if self.activation_function == 'sigmoid':
					a_layer = ...
				elif self.activation_function == 'linear':
					a_layer = z_layer.copy()
				a.append(a_layer)

		# logits should be final pre-activations
		logits = ...

		# compute probabilities by sending logits through softmax
		y_prob = ...

		return z, a, y_prob


	def backward_pass(self, y_true, z, a, y_prob):

		"""
		Computes the backward pass of the neural network and updates the
		weights and biases using gradient descent.

		1) Compute the gradient of the loss with respect to the logits.
		2) Compute the gradient of the loss with respect to the parameters in the output layer.
		3) Iterate through all previous layers to compute gradients of the loss with respect to their parameters.
		4) Update the parameters using the gradient descent update rule.

		Args:
			y_true (2D numpy array): One-hot encoded class labels of shape
				(batch_size, num_classes).

			z (list of 2D numpy arrays): Pre-activation values for each layer.

			a (list of 2D numpy arrays): Activations for each layer, including
				the input features as the first element.

			y_prob (2D numpy array): Predicted class probabilities from the
				softmax output layer.

		"""

		# TODO

		# number of training examples in the current batch
		m = y_true.shape[0]

		# initialize lists to store the weight and bias gradients
		grads_w = [None] * len(self.w)
		grads_b = [None] * len(self.b)

		# compute the gradient of the loss with respect to the
		# output layer pre-activations (logits)
		delta = ...

		# compute gradients for the output layer
		grads_w[-1] = ...
		grads_b[-1] = ...

		# propagate the error backward through each hidden layer
		for layer in range(...):

			# compute the derivative of the activation function
			activation_derivative = ...
	
			# compute the error signal for the current hidden layer
			delta = ...

			# compute gradients for the current layer
			grads_w[layer] = ...
			grads_b[layer] = ...

		# update weights and biases using gradient descent
		for i in range(...):
			self.w[i] = ...
			self.b[i] = ...


	def train(self, X, y):

		"""
		Train the neural network using mini-batch gradient descent.

		1) Convert the class labels to one-hot encoded vectors.
		2) Iterate through epochs.
			a) Iterate through batches.
				i) Perform a forward pass for a batch to compute class probabilities, pre-activations, and activations.
				ii) Compute the cross-entropy loss for the batch.
				iii) Perform the backward pass to compute gradients and update
				   the network parameters.
			b) Compute the average loss across the batches for the epoch and store it in a list.

		Args:
			X (2D numpy array): Training features of shape (num_examples, num_features).

			y (1D numpy array): Integer class labels of shape (num_examples,).

		Returns:
			list: Average training loss for each epoch.

		"""

		# TODO

		# list to store training loss
		training_loss = []

		# get shape of training data
		n, d = X.shape

		# convert y to one-hot
		y = ...

		# iterate through number of epochs
		for epoch in range(...):
			
			# keep track of batch losses
			batch_losses = []

			# iterate through batches
			batch_start_idx = 0
			while ...:

				# extract batch data
				X_batch = ...
				y_batch = ...

				# compute forward pass to get logits
				z, a, y_prob = ...
		
				# compute the cross entropy loss
				loss = ...

				# append loss for batch to batch_losses
				batch_losses.append(loss)

				# compute backward pass
				...

				# increment batch idx
				batch_start_idx += self.batch_size

			# compute average batch loss
			epoch_loss = ...
			training_loss.append(epoch_loss)
	
		return training_loss



	def predict(self, X):

		"""
		Predict the class label for each input example.

		1) Perform a forward pass to compute class probabilities.
		2) Select the class with the highest predicted probability.

		Args:
			X (2D numpy array): Input features of shape (num_examples, num_features).

		Returns:
			1D numpy array: Predicted class labels of shape (num_examples,).

		"""

		# TODO

		# compute forward pass
		_, _, y_prob = ...

		# choose class with highest probabilities
		y_class = ...

		return y_class


	def num_parameters(self):

		"""
		Computes the total number of trainable parameters in the network.

		Returns:
			int: Total number of trainable parameters.

		"""

		###################
		## DO NOT MODIFY ##
		###################

		num_params = 0

		for w in self.w:
			num_params += w.size

		for b in self.b:
			num_params += b.size

		return num_params


