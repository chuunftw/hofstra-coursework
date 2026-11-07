from utils import sigmoid, sigmoid_derivative, softmax, cross_entropy_loss, one_hot_encode
from neural_network import NeuralNetwork
import test_data
import numpy as np


def test_sigmoid_derivative():

	"""
	tests sigmoid derivative function

	"""

	print('-----------------------')
	print('Test Sigmoid Derivative')
	print('-----------------------')

	test_cases = [
		[np.array([-10, -1, 0, 1, 10]), np.array([4.53958077e-05, 1.96611933e-01, 2.50000000e-01, 1.96611933e-01,4.53958077e-05])]
	]

	for test_number, (k, v) in enumerate(test_cases, start=1):

		# get result
		result = sigmoid_derivative(k)
	
		if result is None:
			print(f'Case {test_number}: FAILED - output is None')
			continue

		if not np.allclose(result, v):
			print(f'Case {test_number}: FAILED')
			print(f'Expected {v} but got {result}')
		else:
			print(f'Case {test_number}: passed')

	print()


def test_softmax():

	"""
	tests softmax function

	"""

	print('------------')
	print('Test Softmax')
	print('------------')

	test_cases = [
		[np.array([[1, 2, 3], [-5, 4, 1]]), np.array([[9.00305732e-02, 2.44728471e-01, 6.65240956e-01], [1.17543168e-04, 9.52462158e-01, 4.74202986e-02]])]
	]

	for test_number, (k, v) in enumerate(test_cases, start=1):

		# get result
		result = softmax(k)
	
		if result is None:
			print(f'Case {test_number}: FAILED - output is None')
			continue

		if not np.allclose(result, v):
			print(f'Case {test_number}: FAILED')
			print(f'Expected {v} but got {result}')
		else:
			print(f'Case {test_number}: passed')

	print()


def test_cross_entropy_loss():

	"""
	tests cross entropy loss function

	"""

	print('-----------------------')
	print('Test Cross Entropy Loss')
	print('-----------------------')

	test_cases = [
		[np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]]), np.array([[.8, .1, .1], [.7, .1, .2], [.6, .3, 1]]), 0.8419095481027518]
	]

	for test_number, (y_true, y_prob, v) in enumerate(test_cases, start=1):

		# get result
		result = cross_entropy_loss(y_true, y_prob)
	
		if result is None:
			print(f'Case {test_number}: FAILED - output is None')
			continue

		if not np.allclose(result, v):
			print(f'Case {test_number}: FAILED')
			print(f'Expected {v} but got {result}')
		else:
			print(f'Case {test_number}: passed')

	print()


def test_one_hot_encode():

	"""
	tests one hot encode function

	"""

	print('-------------------')
	print('Test One Hot Encode')
	print('-------------------')

	test_cases = [
		[np.array([0, 1, 0, 2]), np.array([[1, 0, 0], [0, 1, 0], [1, 0, 0], [0, 0, 1]])],
		[np.array([0, 2, 0, 2]), np.array([[1, 0, 0], [0, 0, 1], [1, 0, 0], [0, 0, 1]])]
	]

	for test_number, (k, v) in enumerate(test_cases, start=1):

		# get result
		result = one_hot_encode(k, num_classes=3)
	
		if result is None:
			print(f'Case {test_number}: FAILED - output is None')
			continue

		if not np.allclose(result, v):
			print(f'Case {test_number}: FAILED')
			print(f'Expected {v} but got {result}')
		else:
			print(f'Case {test_number}: passed')

	print()


def test_initialize_parameters():

	"""
	tests initialize parameters

	"""

	print('-------------------------')
	print('Test Initialize Parameters')
	print('--------------------------')


	# get test data
	try:
		test_cases = test_data.initialize_parameters_data()
	except Exception as e:
		print(f'Failed: {e}\n')
		return

	for test_number, (model, w_expected, b_expected) in enumerate(test_cases, start=1):

		# get produced results
		w, b = model.w, model.b

		# test the lists
		msg = test_lists_of_arrays(
			expected_lists=[w_expected, b_expected], 
			produced_lists=[w, b], 
			list_names=['w', 'b']
		)

		print(f'Case {test_number}: {msg}')


	print()


def test_forward_pass():

	"""
	tests foward pass

	"""

	print('------------------')
	print('Test Forward Pass')
	print('------------------')

	# get test cases
	try:
		test_cases = test_data.forward_pass_data()
	except Exception as e:
		print(f'Failed: {e}\n')
		return

	for test_number, (model, X, z_expected, a_expected, y_prob_expected) in enumerate(test_cases, start=1):

		# forward pass
		z, a, y_prob = model.forward_pass(X)

		# test the lists
		msg = test_lists_of_arrays(
			expected_lists=[z_expected, a_expected, y_prob_expected], 
			produced_lists=[z, a, y_prob], 
			list_names=['z', 'a', 'y_prob']
		)

		print(f'Case {test_number}: {msg}')

	print()


def test_backward_pass():

	'''
	test backward pass

	'''

	print('------------------')
	print('Test Backward Pass')
	print('------------------')

	# get test cases
	try:
		test_cases = test_data.backward_pass_data()
	except Exception as e:
		print(f'Failed: {e}\n')
		return

	# iterate through test
	for test_number, (model, X, y, w_expected, b_expected) in enumerate(test_cases, start=1):

		# compute forward and backward passs
		z, a, y_prob = model.forward_pass(X)
		model.backward_pass(y, z, a, y_prob)

		# get parameters
		w, b = model.w, model.b

		# test the lists
		msg = test_lists_of_arrays(
			expected_lists=[w_expected, b_expected], 
			produced_lists=[w, b], 
			list_names=['w', 'b']
		)

		print(f'Case {test_number}: {msg}')

	print()

def test_train():

	'''
	test train

	'''


	print('----------------')
	print('Test Train Pass')
	print('----------------')

	# get test cases
	try:
		test_cases = test_data.train_data()
	except Exception as e:
		print(f'Failed: {e}\n')
		return

	# iterate through test
	for test_number, (model, X, y, w_expected, b_expected) in enumerate(test_cases, start=1):

		# train model
		model.train(X, y)

		# get parameters
		w, b = model.w, model.b

		# test the lists
		msg = test_lists_of_arrays(
			expected_lists=[w_expected, b_expected], 
			produced_lists=[w, b], 
			list_names=['w', 'b']
		)

		print(f'Case {test_number}: {msg}')

	print()


def test_predict():

	'''
	test predict

	'''

	print('------------')
	print('Test Predict')
	print('------------')

	# get test cases
	try:
		test_cases = test_data.predict_data()
	except Exception as e:
		print(f'Failed: {e}\n')
		return

	for test_number, (model, X, y_expected) in enumerate(test_cases, start=1):

		# get result
		y = model.predict(X)
	
		# test the lists
		msg = test_lists_of_arrays(
			expected_lists=[[y_expected]], 
			produced_lists=[[y]], 
			list_names=['y_class']
		)

		print(f'Case {test_number}: {msg}')

	print()


def test_lists_of_arrays(expected_lists, produced_lists, list_names):

	'''
	tests lists of numpy arrays 

	'''

	# iterate through corresponding lists
	for i, (expected_list, produced_list) in enumerate(zip(expected_lists, produced_lists)):

		# None
		if produced_list is None:
			return f'Failed - output is None'

		# check same number of arrays
		if len(expected_list) != len(produced_list):
			return f'FAILED - {list_names[i]} should contain {len(expected_list)} arrays but contains {len(produced_list)}.'
		

		# iterate through corresponding arrays
		for j, (expected_array, produced_array) in enumerate(zip(expected_list, produced_list)):

			# check array shapes
			if expected_array.shape != produced_array.shape:
				return (
					f'FAILED - {list_names[i]}[{j}] has shape {produced_array.shape} but expected {expected_array.shape}.'
				)

			# check array values
			if not np.allclose(expected_array, produced_array):
				return f'{list_names[i]}[{j}] contains incorrect values.'
				

	return 'passed'


def run_tests():

	"""
	runs all tests

	"""

	print('')
	print('#############')
	print('Run All Tests')
	print('#############')
	print('')

	test_sigmoid_derivative()
	test_softmax()
	test_cross_entropy_loss()
	test_one_hot_encode()
	test_initialize_parameters()
	test_forward_pass()
	test_backward_pass()
	test_train()
	test_predict()


if __name__ == '__main__':

	run_tests()




