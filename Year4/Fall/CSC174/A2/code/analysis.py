import matplotlib.pyplot as plt
import numpy as np
import time
from neural_network import NeuralNetwork
from sklearn.metrics import accuracy_score
from utils import plot_decision_boundary, create_linearly_separable_dataset,\
				create_concentric_circles_dataset, create_two_moons_dataset, plot_dataset,\
				one_hot_encode, cross_entropy_loss
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import confusion_matrix, precision_score, recall_score, f1_score
from os.path import join, dirname, abspath, exists
from os import mkdir


#######################
#### DO NOT MODIFY ####
#######################

plots_directory = join(dirname(abspath(__file__)), '..', 'plots')
if not exists(plots_directory):
	mkdir(plots_directory)

########################
########################

def part1():

	"""
	1) Train a neural network on a linearly separable dataset to confirm that your implementation can at least
	fit linearly separable training data. Use the hyperparameters indicated below

		input size: 2
		hidden layer sizes: [4]
		output size: 3
		batch size: 8 
		num epochs: 10
		learning rate: .1
		activation function: linear
		random seed: 42

	2) Create a figure of the decision boundary overlaid on the dataset
	3) Print to the console the model accuracy on the training data

	"""

	# load linearly separable dataset
	X, y = create_linearly_separable_dataset()

	# create empty figure
	fig = plt.figure()

	# instantiate accuracy
	accuracy = None

	# TODO
	model = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[4],
		output_size=3,
		batch_size=8,
		num_epochs=10,
		learning_rate=0.1,
		activation_function='linear',
		random_seed=42
	)
	model.train(X, y)

	predictions = model.predict(X)
	accuracy = accuracy_score(y, predictions)

	plt.close(fig)
	fig = plot_decision_boundary(
		X, y, model, title='Linearly Separable Data: Linear Network'
	)

	# save figure and print accuracy
	print('Part 1 - Accuracy:', accuracy)
	fig.savefig(join(plots_directory, 'part1.png'))
	

def part2():

	"""
	Compare the effect of network architecture and activation functions on a
	nonlinearly separable classification problem.

	1) Train three neural network models on the concentric circles dataset using the following hyperparameters:
	   - Model 1 (no hidden layers):
		   	input size: 2
			hidden layer sizes: [] 
			output size: 3
			batch size: 8 
			num epochs: 500
			learning rate: .02
			activation function: linear
			random seed: 42
	   - Model 2 (one hidden layer):
		   	input size: 2
			hidden layer sizes: [8] 
			output size: 3
			batch size: 8 
			num epochs: 500
			learning rate: .02
			activation function: linear
			random seed: 42
		- Model 3 (one hidden layer + sigmoid activation):
		   	input size: 2
			hidden layer sizes: [8] 
			output size: 3
			batch size: 8 
			num epochs: 500
			learning rate: .02
			activation function: sigmoid
			random seed: 42
	2) Print to the console the training accuracy for each model.
	3) For each model, create a figure of the decision boundary overlaid on the training dataset.

	"""

	# create concentric  circles dataset
	X, y = create_concentric_circles_dataset()

	# create empty figures
	fig_model1, fig_model2, fig_model3 = plt.figure(), plt.figure(), plt.figure()

	# instantiate accuracy
	training_accuracy_model1, training_accuracy_model2, training_accuracy_model3 = None, None, None

	model1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[],
		output_size=3,
		batch_size=8,
		num_epochs=500,
		learning_rate=0.02,
		activation_function='linear',
		random_seed=42
	)
	model1.train(X, y)
	predictions1 = model1.predict(X)
	training_accuracy_model1 = accuracy_score(y, predictions1)
	plt.close(fig_model1)
	fig_model1 = plot_decision_boundary(
		X, y, model1, title='Circles: No Hidden Layer (Linear)'
	)

	model2 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[8],
		output_size=3,
		batch_size=8,
		num_epochs=500,
		learning_rate=0.02,
		activation_function='linear',
		random_seed=42
	)
	model2.train(X, y)
	predictions2 = model2.predict(X)
	training_accuracy_model2 = accuracy_score(y, predictions2)
	plt.close(fig_model2)
	fig_model2 = plot_decision_boundary(
		X, y, model2, title='Circles: 8 Hidden Neurons (Linear)'
	)

	model3 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[8],
		output_size=3,
		batch_size=8,
		num_epochs=500,
		learning_rate=0.02,
		activation_function='sigmoid',
		random_seed=42
	)
	model3.train(X, y)
	predictions3 = model3.predict(X)
	training_accuracy_model3 = accuracy_score(y, predictions3)
	plt.close(fig_model3)
	fig_model3 = plot_decision_boundary(
		X, y, model3, title='Circles: 8 Hidden Neurons (Sigmoid)'
	)

	# save figure and print accuracy
	print('Part 2 - Model 1 Accuracy:', training_accuracy_model1)
	print('Part 2 - Model 2 Accuracy:', training_accuracy_model2)
	print('Part 2 - Model 3 Accuracy:', training_accuracy_model3)
	fig_model1.savefig(join(plots_directory, 'part2_model1.png'))
	fig_model2.savefig(join(plots_directory, 'part2_model2.png'))
	fig_model3.savefig(join(plots_directory, 'part2_model3.png'))



def part3():

	"""
	Compare the effect of model complexity on model training.

	1) Train six neural network models on the two moons dataset using the following hidden layer sizes:

	    - hidden layer sizes: [], [2], [4], [8], [16], [32]

	   All other hyperparameters for each neural network should be the same and set as follows:

		   	input size: 2
			hidden layer sizes: see above
			output size: 2
			batch size: 8 
			num epochs: 1000
			learning rate: .01
			activation function: sigmoid
			random seed: 42

	2) Print to the console the training accuracy for each model.
	3) Print to the console the number of parameters for each model. You may use the num_parameters function provided
	in the neural_network.py class.
	4) Print to the console the training time in seconds for each model.
	5) For each model, create a figure of the decision boundary overlaid on the training dataset.

	"""

	# hidden layer sizes
	hidden_layer_sizes_list = [
		[], 
		[2], 
		[4],
		[8], 
		[16],
		[32]
	]

	# create two moons dataset
	X, y = create_two_moons_dataset()

	# create empty figures
	fig_decision_boundary_model1, fig_decision_boundary_model2, fig_decision_boundary_model3 = plt.figure(), plt.figure(), plt.figure()
	fig_decision_boundary_model4, fig_decision_boundary_model5, fig_decision_boundary_model6 = plt.figure(), plt.figure(), plt.figure()

	# accuracies
	training_accuracy_model1, training_accuracy_model2, training_accuracy_model3 = None, None, None
	training_accuracy_model4, training_accuracy_model5, training_accuracy_model6 = None, None, None

	# num parameters
	num_params_model1, num_params_model2, num_params_model3 = None, None, None
	num_params_model4, num_params_model5, num_params_model6 = None, None, None

	# training time
	train_time_model1, train_time_model2, train_time_model3 = None, None, None
	train_time_model4, train_time_model5, train_time_model6 = None, None, None

	model1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[0],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model1.train(X, y)
	train_time_model1 = time.perf_counter() - start_time

	predictions1 = model1.predict(X)
	training_accuracy_model1 = accuracy_score(y, predictions1)
	num_params_model1 = model1.num_parameters()

	plt.close(fig_decision_boundary_model1)
	fig_decision_boundary_model1 = plot_decision_boundary(
		X, y, model1,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[0]} (Sigmoid)'
	)

	model2 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[1],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model2.train(X, y)
	train_time_model2 = time.perf_counter() - start_time

	predictions2 = model2.predict(X)
	training_accuracy_model2 = accuracy_score(y, predictions2)
	num_params_model2 = model2.num_parameters()

	plt.close(fig_decision_boundary_model2)
	fig_decision_boundary_model2 = plot_decision_boundary(
		X, y, model2,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[1]} (Sigmoid)'
	)

	model3 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[2],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model3.train(X, y)
	train_time_model3 = time.perf_counter() - start_time

	predictions3 = model3.predict(X)
	training_accuracy_model3 = accuracy_score(y, predictions3)
	num_params_model3 = model3.num_parameters()

	plt.close(fig_decision_boundary_model3)
	fig_decision_boundary_model3 = plot_decision_boundary(
		X, y, model3,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[2]} (Sigmoid)'
	)

	model4 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[3],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model4.train(X, y)
	train_time_model4 = time.perf_counter() - start_time

	predictions4 = model4.predict(X)
	training_accuracy_model4 = accuracy_score(y, predictions4)
	num_params_model4 = model4.num_parameters()

	plt.close(fig_decision_boundary_model4)
	fig_decision_boundary_model4 = plot_decision_boundary(
		X, y, model4,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[3]} (Sigmoid)'
	)

	model5 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[4],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model5.train(X, y)
	train_time_model5 = time.perf_counter() - start_time

	predictions5 = model5.predict(X)
	training_accuracy_model5 = accuracy_score(y, predictions5)
	num_params_model5 = model5.num_parameters()

	plt.close(fig_decision_boundary_model5)
	fig_decision_boundary_model5 = plot_decision_boundary(
		X, y, model5,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[4]} (Sigmoid)'
	)

	model6 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=hidden_layer_sizes_list[5],
		output_size=2,
		batch_size=8,
		num_epochs=1000,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=42
	)

	start_time = time.perf_counter()
	model6.train(X, y)
	train_time_model6 = time.perf_counter() - start_time

	predictions6 = model6.predict(X)
	training_accuracy_model6 = accuracy_score(y, predictions6)
	num_params_model6 = model6.num_parameters()

	plt.close(fig_decision_boundary_model6)
	fig_decision_boundary_model6 = plot_decision_boundary(
		X, y, model6,
		title=f'Two Moons: Hidden Layers {hidden_layer_sizes_list[5]} (Sigmoid)'
	)

	# print accuracies
	print('Part 3 - Model 1 Accuracy:', training_accuracy_model1)
	print('Part 3 - Model 2 Accuracy:', training_accuracy_model2)
	print('Part 3 - Model 3 Accuracy:', training_accuracy_model3)
	print('Part 3 - Model 4 Accuracy:', training_accuracy_model4)
	print('Part 3 - Model 5 Accuracy:', training_accuracy_model5)
	print('Part 3 - Model 6 Accuracy:', training_accuracy_model6)

	# print number of parameters
	print('Part 3 - Model 1 # Parameters:', num_params_model1)
	print('Part 3 - Model 2 # Parameters:', num_params_model2)
	print('Part 3 - Model 3 # Parameters:', num_params_model3)
	print('Part 3 - Model 4 # Parameters:', num_params_model4)
	print('Part 3 - Model 5 # Parameters:', num_params_model5)
	print('Part 3 - Model 6 # Parameters:', num_params_model6)

	# print train time
	print('Part 3 - Model 1 train time:', train_time_model1)
	print('Part 3 - Model 2 train time:', train_time_model2)
	print('Part 3 - Model 3 train time:', train_time_model3)
	print('Part 3 - Model 4 train time:', train_time_model4)
	print('Part 3 - Model 5 train time:', train_time_model5)
	print('Part 3 - Model 6 train time:', train_time_model6)

	# save figures
	fig_decision_boundary_model1.savefig(join(plots_directory, 'part3_model1.png'))
	fig_decision_boundary_model2.savefig(join(plots_directory, 'part3_model2.png'))
	fig_decision_boundary_model3.savefig(join(plots_directory, 'part3_model3.png'))
	fig_decision_boundary_model4.savefig(join(plots_directory, 'part3_model4.png'))
	fig_decision_boundary_model5.savefig(join(plots_directory, 'part3_model5.png'))
	fig_decision_boundary_model6.savefig(join(plots_directory, 'part3_model6.png'))


def part4():

	"""
	Breast Cancer Classification

	1) Train a neural network on the Breast Cancer Wisconsin Dataset using the following hyperparameters:

		input size: 30
		hidden layer sizes: [16]
		output size: 2
		batch size: 16
		num epochs: 1
		learning rate: .01
		activation function: sigmoid
		random seed: 43
	
	In order to be able to save the model parameters after each epoch, you 
	will need to train the model one epoch at a time. Train the model for
	3000 epochs. 

	2) Save the model parameters after each epoch.
	3) Plot training and validation loss across epochs.
	4) Plot training and validation accuracy across epochs.
	5) Determine the optimal epoch using validation loss.
	6) Restore the model parameters from the optimal epoch.
	7) Print training, validation, and testing accuracy.
	8) Print the confusion matrix, precision, recall, and F1-score
	   for the testing set, treating malignant tumors as positive.

	"""

	# create empty figures
	fig_loss_curves, fig_accuracy_curves = plt.figure(), plt.figure()

	# instantiate values to print
	optimal_epoch, training_accuracy, validation_accuracy, testing_accuracy = None, None, None, None
	cm, precision, recall, f1 = None, None, None, None

	# load breast cancer dataset
	X, y = load_breast_cancer(return_X_y=True)

	# change labels so malignant = 1 and benign = 0
	y = 1 - y

	# split into training and testing sets
	X_train, X_test, y_train, y_test = train_test_split(
		X, y,
		test_size=0.2,
		random_state=43,
		stratify=y
	)

	# split the training dataset into training and validation
	X_train, X_val, y_train, y_val = train_test_split(
		X_train, y_train,
		test_size=0.25,
		random_state=43,
		stratify=y_train
	)

	# standardize features
	scaler = StandardScaler()
	X_train = scaler.fit_transform(X_train)
	X_val = scaler.transform(X_val)
	X_test = scaler.transform(X_test)

	# instantiate neural network
	nn_model = NeuralNetwork(
		input_size=30,
		hidden_layer_sizes=[16],
		output_size=2,
		batch_size=16,
		num_epochs=1,
		learning_rate=0.01,
		activation_function='sigmoid',
		random_seed=43
	)

	# number of training epochs
	num_epochs = 3000

	# lists to store losses and accuracies
	training_losses = []
	validation_losses = []

	training_accuracies = []
	validation_accuracies = []

	# lists to store model parameters after each epoch
	weights_history = []
	biases_history = []

	# one-hot encode labels for loss calculations
	y_train_one_hot = one_hot_encode(y_train, num_classes=2)
	y_val_one_hot = one_hot_encode(y_val, num_classes=2)


	# TODO

	# train model one epoch at a time
	for epoch in range(num_epochs):

		# train for one epoch
		nn_model.train(X_train, y_train) 
		# save model parameters
		weights_history.append([w.copy() for w in nn_model.w])
		biases_history.append([b.copy() for b in nn_model.b])

		# compute training and validation probabilities
		y_train_prob = nn_model.forward_pass(X_train)[2]
		y_val_prob = nn_model.forward_pass(X_val)[2]

		# compute losses
		training_loss = cross_entropy_loss(y_train_one_hot, y_train_prob)
		validation_loss = cross_entropy_loss(y_val_one_hot, y_val_prob)

		training_losses.append(training_loss)
		validation_losses.append(validation_loss)

		# compute accuracies
		training_accuracy = accuracy_score(y_train, nn_model.predict(X_train))
		validation_accuracy = accuracy_score(y_val, nn_model.predict(X_val))

		training_accuracies.append(training_accuracy)
		validation_accuracies.append(validation_accuracy)

	# determine optimal epoch using validation loss
	optimal_epoch_idx = np.argmin(validation_losses)
	optimal_epoch = optimal_epoch_idx + 1

	# restore model parameters from optimal epoch
	nn_model.w = [w.copy() for w in weights_history[optimal_epoch_idx]]
	nn_model.b = [b.copy() for b in biases_history[optimal_epoch_idx]]

	# compute final predictions
	y_train_pred = nn_model.predict(X_train)
	y_val_pred = nn_model.predict(X_val)
	y_test_pred = nn_model.predict(X_test)


	# compute final accuracies
	training_accuracy = accuracy_score(y_train, y_train_pred)
	validation_accuracy = accuracy_score(y_val, y_val_pred)
	testing_accuracy = accuracy_score(y_test, y_test_pred)


	# compute metrics on testing set
	cm = confusion_matrix(y_test, y_test_pred)
	precision = precision_score(y_test, y_test_pred, pos_label=1)
	recall = recall_score(y_test, y_test_pred, pos_label=1)
	f1 = f1_score(y_test, y_test_pred, pos_label=1)
	

	# print training results
	print('Part 4 - Optimal Epoch:', optimal_epoch)
	print('Part 4 - Training Accuracy:', training_accuracy)
	print('Part 4 - Validation Accuracy:', validation_accuracy)
	print('Part 4 - Testing Accuracy:', testing_accuracy)

	# print metrics
	print('Part 4 - Confusion Matrix:', cm)
	print('Part 4 - Precision:', precision)
	print('Part 4 - Recall:', recall)
	print('Part 4 - F1-score:', f1)

	epochs = np.arange(1, num_epochs + 1)
	ax_loss = fig_loss_curves.add_subplot(1,1,1) # 1 row, 1 column, 1 plot number
	ax_loss.plot(epochs, training_losses, label='Training')
	ax_loss.plot(epochs, validation_losses, label='Validation')
	ax_loss.axvline(optimal_epoch, color='black', linestyle='--', label=f'Best Epoch: {optimal_epoch}')
	ax_loss.set_xlabel('Epoch')
	ax_loss.set_ylabel('Cross-Entropy Loss')
	ax_loss.set_title('Breast Cancer: Training and Validation Loss')
	ax_loss.legend()
	fig_loss_curves.tight_layout()

	ax_accuracy = fig_accuracy_curves.add_subplot(1,1,1)
	ax_accuracy.plot(epochs, training_accuracies, label='Training')
	ax_accuracy.plot(epochs, validation_accuracies, label='Validation')
	ax_accuracy.axvline(optimal_epoch, color='black', linestyle='--', label=f'Best Epoch: {optimal_epoch}')
	ax_accuracy.set_xlabel('Epoch')
	ax_accuracy.set_ylabel('Accuracy')
	ax_accuracy.set_title('Breast Cancer: Training and Validation Accuracy')
	ax_accuracy.legend()
	fig_accuracy_curves.tight_layout()

	# save figures
	fig_loss_curves.savefig(join(plots_directory, 'part4_loss_curves.png'))
	fig_accuracy_curves.savefig(join(plots_directory, 'part4_accuracy_curves.png'))


if __name__ == '__main__':

	part1()
	part2()
	part3()
	part4()

