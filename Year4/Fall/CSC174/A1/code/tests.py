from linear_regression import LinearRegression
from logistic_regression import LogisticRegression
from utils import load_lin_reg_1d_nonlinear_dataset, load_lin_reg_2d_dataset
import numpy as np

def test_linear_regression_train_closed_form():

	"""
	tests linear regression train closed form

	"""

	print('----------------------------------------')
	print('Test Linear Regression Train Closed Form')
	print('----------------------------------------')

	# get dataset
	X_1d, y_1d = load_lin_reg_1d_nonlinear_dataset()
	X_2d, y_2d = load_lin_reg_2d_dataset()

	# test cases
	test_cases = [
		(X_1d, y_1d, np.array([-3.1170472]), 68.62082693655591),
		(X_2d, y_2d, np.array([ 2.98607955, -2.05367584]), 5.066731528759307)
	]

	# iterate through test cases
	for test_number, (X, y, w, b) in enumerate(test_cases, start=1):

	
		# instantiate linear regression model
		lin_reg = LinearRegression()
		
		# train lin reg model
		lin_reg.train_closed_form(X, y)

		# get parameters
		w_pred, b_pred = lin_reg.w, lin_reg.b

		# check types
		if not isinstance(w_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - w is of type {type(w_pred)} but should be of type np.ndarray')
			continue
		if not isinstance(b_pred, float):
			print(f'Case {test_number}: FAILED - b is of type {type(b_pred)} but should be of type float')
			continue

		# check dimension of w_pred
		if w_pred.ndim != 1:
			print(f'Case {test_number}: FAILED - w has {w_pred.ndim} dimensions but should have 1 dimension')
			continue

		# check w shape
		if w_pred.shape != w.shape:
			print(f'Case {test_number}: FAILED - w has shape {w_pred.shape} but should have shape {w.shape}')
			continue

		# check if w matches up to 3 decimal places
		if not np.allclose(w_pred, w, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - w={w_pred} but expected w={w}')
			continue
		# check if b matches up to 3 decimal places
		if np.round(b_pred, 3) != np.round(b, 3):
			print(f'Case {test_number}: FAILED - b={b_pred} but expected b={b}')
			continue

		print(f'Case {test_number}: passed')

	print()



def test_mse_loss():

	"""
	tests mse loss

	"""

	print('-------------')
	print('Test MSE Loss')
	print('-------------')


	# test cases
	test_cases = [
		(np.array([4, 3, 1, -5]), np.array([3, 5, 1, 9]), 50.25),
		(np.array([10]), np.array([-1]), 121.0),
	]

	# iterate through test cases
	for test_number, (y, y_hat, loss) in enumerate(test_cases, start=1):

	
		# instantiate linear regression model
		lin_reg = LinearRegression()
		
		# compute loss
		loss_pred = lin_reg.mse_loss(y, y_hat)
	

		# check types
		if not isinstance(loss_pred, float):
			print(f'Case {test_number}: FAILED - loss is of type {type(loss_pred)} but should be of type float')
			continue
	
		# check if loss matches up to 3 decimal places
		if np.round(loss, 3) != np.round(loss_pred, 3):
			print(f'Case {test_number}: FAILED - loss={loss_pred} but expected loss={loss}')
			continue

		print(f'Case {test_number}: passed')

	print()



def test_mse_gradients():

	"""
	tests MSE gradients

	"""

	print('------------------')
	print('Test MSE Gradients')
	print('------------------')

	# get dataset
	X_1d, _ = load_lin_reg_1d_nonlinear_dataset()
	X_2d, _ = load_lin_reg_2d_dataset()


	# test cases
	test_cases = [
		(X_1d[:5], np.array([1, 2, 3, 4, 5]), np.array([9, 1, 3, 1, 4]),  np.array([16.53190811]), 1.2),
		(X_2d[:4], np.array([1, 2, 3, 4]), np.array([9, 3, 1, 4]),  np.array([ 33.61891613, -12.42849156]), 3.5)
	]

	# iterate through test cases
	for test_number, (X, y, y_hat, dl_dw, dl_db) in enumerate(test_cases, start=1):

		# instantiate linear regression model
		lin_reg = LinearRegression()
		
		# compute gradients
		dl_dw_pred, dl_db_pred = lin_reg.mse_gradients(y, y_hat, X)

		# check types
		if not isinstance(dl_dw_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - dl_dw is of type {type(dl_dw_pred)} but should be of type np.ndarray')
			continue
		if not isinstance(dl_db_pred, float):
			print(f'Case {test_number}: FAILED - dl_db is of type {type(dl_db_pred)} but should be of type float')
			continue

		# check dimension of dl_dw_pred
		if dl_dw_pred.ndim != 1:
			print(f'Case {test_number}: FAILED - dl_dw has {dl_dw_pred.ndim} dimensions but should have 1 dimension')
			continue

		# check dl_dw shape
		if dl_dw_pred.shape != dl_dw.shape:
			print(f'Case {test_number}: FAILED - dl_dw has shape {dl_dw_pred.shape} but should have shape {dl_dw.shape}')
			continue

		# check if dl_dw matches up to 3 decimal places
		if not np.allclose(dl_dw_pred, dl_dw, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - dl_dw={dl_dw_pred} but expected dl_dw={dl_dw}')
			continue
		# check if dl_db matches up to 3 decimal places
		if np.round(dl_db_pred, 3) != np.round(dl_db, 3):
			print(f'Case {test_number}: FAILED - dl_db={dl_db_pred} but expected dl_db={dl_db}')
			continue

		print(f'Case {test_number}: passed')

	print()


def test_linear_regression_train_batch_gradient_descent():

	"""
	tests linear regression train batch gradient descent

	"""

	print('---------------------------------------------------')
	print('Test Linear Regression Train Batch Gradient Descent')
	print('---------------------------------------------------')

	# get dataset
	X_1d, y_1d = load_lin_reg_1d_nonlinear_dataset()
	X_2d, y_2d = load_lin_reg_2d_dataset()

	# test cases
	test_cases = [
		(X_1d, y_1d, 0.1, 10, [np.float64(8330.04929444901), np.float64(16704.99248750257), np.float64(303489.63402306894), np.float64(8533720.572897248), np.float64(243877344.38261238), np.float64(6972991006.808152), np.float64(199376287432.72836), np.float64(5700699171520.122), np.float64(162998178007986.47), np.float64(4660552197128655.0), np.float64(1.3325760476609739e+17)]),
		(X_2d, y_2d, .01, 5, [np.float64(454.3427917544968), np.float64(84.42454194002349), np.float64(39.54291547890634), np.float64(32.917163262874325), np.float64(31.236759579824678), np.float64(30.25720098806834)])
	]

	# iterate through test cases
	for test_number, (X, y, learning_rate, num_epochs, loss_history) in enumerate(test_cases, start=1):

	
		# instantiate linear regression model
		lin_reg = LinearRegression()
		
		# train lin reg model
		loss_history_pred = lin_reg.train_batch_gradient_descent(X, y, learning_rate=learning_rate, num_epochs=num_epochs)

		# check types
		if not isinstance(loss_history_pred, list):
			print(f'Case {test_number}: FAILED - loss_history is of type {type(loss_history_pred)} but should be of type list')
			continue

		# check length
		if len(loss_history_pred) != len(loss_history):
			print(f'Case {test_number}: FAILED - loss_history has length={len(loss_history_pred)} but should have length={len(loss_history)}')
			continue

		# check if loss history matches up to 3 decimal places
		if not np.allclose(loss_history_pred, loss_history, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - loss_history={loss_history_pred} but expected loss_history={loss_history}')
			continue


		print(f'Case {test_number}: passed')

	print()



def test_linear_regression_predict():

	"""
	tests linear regression predict

	"""

	print('------------------------------')
	print('Test Linear Regression Predict')
	print('------------------------------')

	# get dataset
	X_1d, y_1d = load_lin_reg_1d_nonlinear_dataset()
	X_2d, y_2d = load_lin_reg_2d_dataset()

	# test cases
	test_cases = [
		(X_1d, y_1d, np.array([51.54214824, 72.4312027,  46.26549408, 56.31671768, 93.92019418])),
		(X_2d, y_2d, np.array([23.93830005,  18.37617078, -38.70512559,  8.91274296, -15.10508999]))
	]

	# iterate through test cases
	for test_number, (X, y, y_hat) in enumerate(test_cases, start=1):

	
		# instantiate linear regression model
		lin_reg = LinearRegression()
		
		# train lin reg model
		lin_reg.train_closed_form(X, y)

		# make predictions
		y_hat_pred = lin_reg.predict(X[:5])

		# check types
		if not isinstance(y_hat_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - y_hat is of type {type(y_hat_pred)} but should be of np.ndarray')
			continue

		# check length
		if len(y_hat_pred) != len(y_hat):
			print(f'Case {test_number}: FAILED - y_hat has length={len(y_hat_pred)} but should have length={len(y_hat)}')
			continue

		# check if y_hat matches up to 3 decimal places
		if not np.allclose(y_hat_pred, y_hat, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - y_hat={y_hat_pred} but expected y_hat={y_hat}')
			continue


		print(f'Case {test_number}: passed')

	print()



def test_sigmoid():

	"""
	tests sigmoid

	"""

	print('------------')
	print('Test Sigmoid')
	print('------------')


	# test cases
	test_cases = [
		(np.array([4, 3, 1, -5, 0]), np.array([0.98201379, 0.95257413, 0.73105858, 0.00669285, 0.5]))
	]

	# iterate through test cases
	for test_number, (x, sig) in enumerate(test_cases, start=1):

	
		# instantiate logistic regression model
		log_reg = LogisticRegression()
		
		# compute sigmoid
		sig_pred = log_reg.sigmoid(x)
	
		# check types
		if not isinstance(sig_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - sigmoid output is of type {type(sig_pred)} but should be of type np.ndarray')
			continue

		# check dimension of sig_pred
		if sig_pred.ndim != sig.ndim:
			print(f'Case {test_number}: FAILED - sigmoid output has {sig_pred.ndim} dimensions but should have {sig.ndim} dimensions')
			continue

		# check sig_pred shape
		if sig_pred.shape != sig.shape:
			print(f'Case {test_number}: FAILED - sigmoid output has shape {sig_pred.shape} but should have shape {sig.shape}')
			continue

		# check if sig matches up to 3 decimal places
		if not np.allclose(sig_pred, sig, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - sigmoid={sig_pred} but expected sigmoid={sig}')
			continue
	
		print(f'Case {test_number}: passed')

	print()



def test_bce_loss():

	"""
	tests bce loss

	"""

	print('-------------')
	print('Test BCE Loss')
	print('-------------')


	# test cases
	test_cases = [
		(np.array([1, 0, 0, 1]), np.array([.5, .2, .8, .8]), 0.6872180489056163),
		(np.array([0]), np.array([.4]), 0.5108256237659907),
	]

	# iterate through test cases
	for test_number, (y, y_hat, loss) in enumerate(test_cases, start=1):

	
		# instantiate logistic regression model
		log_reg = LogisticRegression()
		
		# compute loss
		loss_pred = log_reg.bce_loss(y, y_hat)
	

		# check types
		if not isinstance(loss_pred, float):
			print(f'Case {test_number}: FAILED - loss is of type {type(loss_pred)} but should be of type float')
			continue
	
		# check if loss matches up to 3 decimal places
		if np.round(loss, 3) != np.round(loss_pred, 3):
			print(f'Case {test_number}: FAILED - loss={loss_pred} but expected loss={loss}')
			continue

		print(f'Case {test_number}: passed')

	print()



def test_bce_gradients():

	"""
	tests BCE gradients

	"""

	print('------------------')
	print('Test BCE Gradients')
	print('------------------')

	# get dataset
	X_1d, y_1d = np.array([[3], [4], [5]]), np.array([0, 0, 1])
	X_2d, y_2d = np.array([[-1, -5], [-2, 8], [3, 8], [10, 12]]), np.array([1, 1, 0, 0])


	# test cases
	test_cases = [
		(X_1d, y_1d, np.array([.2, .3, .8]),  np.array([0.26666667]), 0.10000000000000002),
		(X_2d, y_2d, np.array([.5, .3, .1, .2]),  np.array([1.05,  0.025]), -0.22499999999999998)
	]

	# iterate through test cases
	for test_number, (X, y, y_hat, dl_dw, dl_db) in enumerate(test_cases, start=1):

		# instantiate logistic regression model
		log_reg = LogisticRegression()
		
		# compute gradients
		dl_dw_pred, dl_db_pred = log_reg.bce_gradients(y, y_hat, X)

		# check types
		if not isinstance(dl_dw_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - dl_dw is of type {type(dl_dw_pred)} but should be of type np.ndarray')
			continue
		if not isinstance(dl_db_pred, float):
			print(f'Case {test_number}: FAILED - dl_db is of type {type(dl_db_pred)} but should be of type float')
			continue

		# check dimension of dl_dw_pred
		if dl_dw_pred.ndim != 1:
			print(f'Case {test_number}: FAILED - dl_dw has {dl_dw_pred.ndim} dimensions but should have 1 dimension')
			continue

		# check dl_dw shape
		if dl_dw_pred.shape != dl_dw.shape:
			print(f'Case {test_number}: FAILED - dl_dw has shape {dl_dw_pred.shape} but should have shape {dl_dw.shape}')
			continue

		# check if dl_dw matches up to 3 decimal places
		if not np.allclose(dl_dw_pred, dl_dw, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - dl_dw={dl_dw_pred} but expected dl_dw={dl_dw}')
			continue
		# check if dl_db matches up to 3 decimal places
		if np.round(dl_db_pred, 3) != np.round(dl_db, 3):
			print(f'Case {test_number}: FAILED - dl_db={dl_db_pred} but expected dl_db={dl_db}')
			continue

		print(f'Case {test_number}: passed')

	print()


def test_logistic_regression_train_batch_gradient_descent():

	"""
	tests logistic regression train batch gradient descent

	"""

	print('-----------------------------------------------------')
	print('Test Logistic Regression Train Batch Gradient Descent')
	print('-----------------------------------------------------')

	# get dataset
	X_1d, y_1d = np.array([[3], [4], [5]]), np.array([0, 0, 1])
	X_2d, y_2d = np.array([[-1, -5], [-2, 8], [3, 8], [10, 12]]), np.array([1, 1, 0, 0])

	# test cases
	test_cases = [
		(X_1d, y_1d, 0.1, 3, [np.float64(0.6931471805599453), np.float64(0.6821602284161147), np.float64(0.6782209044973727), np.float64(0.6764858535786583)]),
		(X_2d, y_2d, .01, 5, [np.float64(0.6931471805599453), np.float64(0.6170804265053195), np.float64(0.5691209898578532), np.float64(0.5371069817221382), np.float64(0.5143008467209684), np.float64(0.4970377719975547)])
	]

	# iterate through test cases
	for test_number, (X, y, learning_rate, num_epochs, loss_history) in enumerate(test_cases, start=1):

	
		# instantiate logistic regression model
		log_reg = LogisticRegression()
		
		# train log reg model
		loss_history_pred = log_reg.train_batch_gradient_descent(X, y, learning_rate=learning_rate, num_epochs=num_epochs)

		# check types
		if not isinstance(loss_history_pred, list):
			print(f'Case {test_number}: FAILED - loss_history is of type {type(loss_history_pred)} but should be of type list')
			continue

		# check length
		if len(loss_history_pred) != len(loss_history):
			print(f'Case {test_number}: FAILED - loss_history has length={len(loss_history_pred)} but should have length={len(loss_history)}')
			continue

		# check if loss history matches up to 3 decimal places
		if not np.allclose(loss_history_pred, loss_history, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - loss_history={loss_history_pred} but expected loss_history={loss_history}')
			continue


		print(f'Case {test_number}: passed')

	print()


def test_logistic_regression_predict():

	"""
	tests logistic regression predict

	"""

	print('--------------------------------')
	print('Test Logistic Regression Predict')
	print('--------------------------------')

	# get dataset
	X_1d, y_1d = np.array([[3], [4], [5]]), np.array([0, 0, 1])
	X_2d, y_2d = np.array([[-1, -5], [-2, 8], [3, 8], [10, 12]]), np.array([1, 1, 0, 0])

	# test cases
	test_cases = [
		(X_1d, y_1d, np.array([0, 0, 0])),
		(X_2d, y_2d, np.array([1, 1, 0, 0]))
	]

	# iterate through test cases
	for test_number, (X, y, y_hat) in enumerate(test_cases, start=1):

	
		# instantiate logistic regression model
		log_reg = LogisticRegression()
		
		# train log reg model
		log_reg.train_batch_gradient_descent(X, y, learning_rate=.05, num_epochs=10)

		# make predictions
		y_hat_pred = log_reg.predict(X)

		# check types
		if not isinstance(y_hat_pred, np.ndarray):
			print(f'Case {test_number}: FAILED - y_hat is of type {type(y_hat_pred)} but should be of np.ndarray')
			continue

		# check length
		if len(y_hat_pred) != len(y_hat):
			print(f'Case {test_number}: FAILED - y_hat has length={len(y_hat_pred)} but should have length={len(y_hat)}')
			continue

		# check if y_hat matches up to 3 decimal places
		if not np.allclose(y_hat_pred, y_hat, atol=1e-3, rtol=1e-12):
			print(f'Case {test_number}: FAILED - y_hat={y_hat_pred} but expected y_hat={y_hat}')
			continue


		print(f'Case {test_number}: passed')

	print()


def run_tests():

	"""
	runs all tests

	"""

	print('')
	print('#############')
	print('Run All Tests')
	print('#############')
	print('')

	# linear regression tests
	test_linear_regression_train_closed_form()
	test_mse_loss()
	test_mse_gradients()
	test_linear_regression_train_batch_gradient_descent()
	test_linear_regression_predict()


	# logistic regression tests
	test_sigmoid()
	test_bce_loss()
	test_bce_gradients()
	test_logistic_regression_train_batch_gradient_descent()
	test_logistic_regression_predict()


if __name__ == '__main__':

	run_tests()




