from os.path import join, dirname, abspath, exists
from os import mkdir
from linear_regression import LinearRegression
from logistic_regression import LogisticRegression
from utils import load_lin_reg_1d_linear_dataset, load_lin_reg_1d_nonlinear_dataset, load_lin_reg_2d_dataset, \
					load_california_housing_dataset, load_log_reg_2d_dataset, plot_decision_boundary, accuracy_score
import matplotlib.pyplot as plt
import numpy as np


# directory where plots are saved do not modify
plots_directory = join(dirname(abspath(__file__)), '..', 'plots')
if not exists(plots_directory):
	mkdir(plots_directory)


def part1():

	"""
	In this problem you will train a linear regression model with the closed form solution for three datasets. 
	Two 1D datasets (linear and nonlinear) and one 2D dataset. 

	For each of the three datasets 

		- 1d linear
		- 1d non linear
		- 2d linear

	1) Train a linear regression model with the closed form solution on the dataset. 
	2) Create a plot of the learned linear model overlaid on the training data. 
	3) Print the MSE loss. 
	4) Print the model parameters.


	"""

	# load datasets
	X_lin_reg_1d_linear_dataset, y_lin_reg_1d_linear_dataset = load_lin_reg_1d_linear_dataset()
	X_lin_reg_1d_nonlinear_dataset, y_lin_reg_1d_nonlinear_dataset = load_lin_reg_1d_nonlinear_dataset()
	X_lin_reg_2d_dataset, y_lin_reg_2d_dataset = load_lin_reg_2d_dataset()

	# instantiate figures
	fig_1d_linear, fig_1d_nonlinear, fig_2d = plt.figure(), plt.figure(), plt.figure()

	# values to be printed to the console
	lin_reg_1d_linear_mse_loss, lin_reg_1d_nonlinear_mse_loss, lin_reg_2d_mse_loss = None, None, None
	lin_reg_1d_linear_w, lin_reg_1d_nonlinear_w, lin_reg_2d_w = None, None, None
	lin_reg_1d_linear_b, lin_reg_1d_nonlinear_b, lin_reg_2d_b = None, None, None

	
	## TODO
	model_1d_linear = LinearRegression()
	model_1d_nonlinear = LinearRegression()
	model_2d_linear = LinearRegression() 
 
	#Training all 3 models 
	model_1d_linear.train_closed_form(X_lin_reg_1d_linear_dataset,y_lin_reg_1d_linear_dataset)
	model_1d_nonlinear.train_closed_form(X_lin_reg_1d_nonlinear_dataset, y_lin_reg_1d_nonlinear_dataset)
	model_2d_linear.train_closed_form(X_lin_reg_2d_dataset, y_lin_reg_2d_dataset)
 
	# save figures
	fig_1d_linear.savefig(join(plots_directory, 'part1_lin_reg_1d_linear.png'))
	fig_1d_nonlinear.savefig(join(plots_directory, 'part1_lin_reg_1d_nonlinear.png'))
	fig_2d.savefig(join(plots_directory, 'part1_lin_reg_2d.png'))

	# print values to console
	print()
	print(f'Part 1 - Linear Regression 1d linear MSE Loss:  {lin_reg_1d_linear_mse_loss}')
	print(f'Part 1 - Linear Regression 1d nonlinear MSE Loss:  {lin_reg_1d_nonlinear_mse_loss}')
	print(f'Part 1 - Linear Regression 2d MSE Loss:  {lin_reg_2d_mse_loss}')
	print(f'Part 1 - Linear Regression 1d linear parameters:  w: {lin_reg_1d_linear_w}  b: {lin_reg_1d_linear_b}')
	print(f'Part 1 - Linear Regression 1d nonlinear parameters:  w: {lin_reg_1d_nonlinear_w}  b: {lin_reg_1d_nonlinear_b}')
	print(f'Part 1 - Linear Regression 2d parameters:  w: {lin_reg_2d_w}  b: {lin_reg_2d_b}')


def part2():

	"""
	In this problem you will compare linear regression trained using the
	closed form solution and batch gradient descent on the California
	Housing dataset.

	1) Train a linear regression model using the closed form solution on the California Housing dataset.
	2) Train a linear regression model using batch gradient descent on the California Housing dataset.
		- learning rate = 0.01
		- num_epochs = 1000
	3) Compute and print the final MSE loss for both models.
	4) Print the learned parameters for both models.
	5) Create and save a loss curve for the batch gradient descent model. This curve should plot epoch number on the
	x-axis and mse loss on the y-axis.

	"""

	# load California Housing dataset
	X, y = load_california_housing_dataset()

	# instantiate figures
	fig_loss_curve = plt.figure()

	# values to be printed to the console
	mse_closed_form, mse_gradient_descent = None, None
	w_closed_form, b_closed_form = None, None
	w_gradient_descent, b_gradient_descent = None, None

	
	## TODO

	# save figure
	fig_loss_curve.savefig(join(plots_directory, 'part2_lin_reg_gradient_descent_loss_curve.png'))

	# print losses
	print()
	print(f'Part 2 - Closed Form MSE Loss: {mse_closed_form}')
	print(f'Part 2 - Gradient Descent MSE Loss: {mse_gradient_descent}')

	# print parameters
	print(f'Part 2 - Closed Form parameters:')
	print(f'    w: {w_closed_form}')
	print(f'    b: {b_closed_form}')

	print(f'Part 2 - Gradient Descent parameters:')
	print(f'    w: {w_gradient_descent}')
	print(f'    b: {b_gradient_descent}')


def part3():

	"""
	In this problem you will explore the effects of the learning rate on the convergence of
	the logistic regression gradient descent training algorithm. Follow the instructions below.

	- Train three logistic regression models, all on the provided logistic regression dataset. 
	- For each model use the following learning rates
	  		1) .00001, 
	  		2) .05, 
	  		3) 2
	- Train for 500 epochs
	- For each model, create figures for the decision boundary overlaid on the dataset 
	  using the plot_decision_boundary function provided for you in utils.py.
	- For each model, create a loss curve figure in which you will plot the training loss for each epoch. 
	  The y-axis should be the loss and the x-axis should be the epoch number.
	- For each model, print to the console and report the loss on the training dataset and the accuracy on the training dataset.

	"""

	# load dataset
	X, y = load_log_reg_2d_dataset()


	# instantiate figures
	fig_loss_curve_1, fig_loss_curve_2, fig_loss_curve_3 = plt.figure(), plt.figure(), plt.figure()
	fig_decision_boundary_1, fig_decision_boundary_2, fig_decision_boundary_3 = plt.figure(), plt.figure(), plt.figure()

	# values to be printed to the console
	loss1, loss2, loss3 = None, None, None
	acc1, acc2, acc3 = None, None, None



	# TODO


	# save figures
	fig_loss_curve_1.savefig(join(plots_directory, 'part3_loss_curve_learning_rate=.00001.png'))
	fig_loss_curve_2.savefig(join(plots_directory, 'part3_loss_curve_learning_rate=.05.png'))
	fig_loss_curve_3.savefig(join(plots_directory, 'part3_loss_curve_learning_rate=2.png'))
	fig_decision_boundary_1.savefig(join(plots_directory, 'part3_decision_boundary_learning_rate=.00001.png'))
	fig_decision_boundary_2.savefig(join(plots_directory, 'part3_decision_boundary_learning_rate=.05.png'))
	fig_decision_boundary_3.savefig(join(plots_directory, 'part3_decision_boundary_learning_rate=2.png'))

	print()
	print(f'Part 3 - learning_rate=.00001 Loss: {loss1}')
	print(f'Part 3 - learning_rate=.00001 Training Accuracy: {acc1}')
	print(f'Part 3 - learning_rate=.05 Loss: {loss2}')
	print(f'Part 3 - learning_rate=.05 Training Accuracy: {acc2}')
	print(f'Part 3 - learning_rate=2 Loss: {loss3}')
	print(f'Part 3 - learning_rate=2 Training Accuracy: {acc3}')
	print()


if __name__ == '__main__':

	part1()
	part2()
	part3()



