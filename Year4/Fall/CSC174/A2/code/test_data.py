from neural_network import NeuralNetwork
import numpy as np

def initialize_parameters_data():

	'''
	initialize parameters data

	'''

	# create neural network model
	nn_model = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=6,
		batch_size=None,
		num_epochs=None,
		learning_rate=None,
		activation_function=None,
		random_seed=42
	)

	sol_w = [
		np.array([
			[ 0.49671415, -0.13826430],
			[ 0.64768854,  1.52302986]
		]),
		np.array([
			[-0.23415337, -0.23413696,  1.57921282],
			[ 0.76743473, -0.46947439,  0.54256004]
		]),
		np.array([
			[-0.46341769, -0.46572975,  0.24196227, -1.91328024, -1.72491783,
			 -0.56228753],
			[-1.01283112,  0.31424733, -0.90802408, -1.41230370,  1.46564877,
			 -0.22577630],
			[ 0.06752820, -1.42474819, -0.54438272,  0.11092259, -1.15099358,
			  0.37569802]
		])
	]

	sol_b = [
		np.array([0., 0.]),
		np.array([0., 0., 0.]),
		np.array([0., 0., 0., 0., 0., 0.])
	]

	test_cases = [
		[nn_model, sol_w, sol_b]
	]

	return test_cases


def forward_pass_data():

	'''
	forward pass data

	'''

	np.random.seed(42)

	# test linear
	X1 = np.random.rand(4, 2)
	nn_model_1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=6,
		batch_size=None,
		num_epochs=None,
		learning_rate=None,
		activation_function='linear',
		random_seed=42
	)

	z1 = [
		np.array([
			[0.80180614, 1.39618075],
			[0.75133599, 0.81056611],
			[0.17853253, 0.21601250],
			[0.58986331, 1.31118124]
		]),
		np.array([
			[ 0.88373198, -0.84320355,  2.02373441],
			[ 0.44612873, -0.55645555,  1.62630021],
			[ 0.12397150, -0.14321340,  0.39914061],
			[ 0.86812753, -0.75367481,  1.64291426]
		]),
		np.array([
			[ 5.81144910e-01, -3.55986668e+00, -1.22207135e-01,
			 -2.75489585e-01, -5.08951060e+00,  4.53776915e-01],
			[ 4.66672686e-01, -2.69970837e+00, -2.72108381e-01,
			  1.12708381e-01, -3.45696489e+00,  4.85779621e-01],
			[ 1.14553650e-01, -6.71416510e-01, -5.72476117e-02,
			  9.34229888e-03, -8.83149482e-01,  1.12582899e-01],
			[ 4.71982692e-01, -2.98189223e+00,  3.48435232e-05,
			 -4.14317236e-01, -4.49305498e+00,  2.99264254e-01]
		])
	]

	a1 = [
		np.array([
			[0.37454012, 0.95071431],
			[0.73199394, 0.59865848],
			[0.15601864, 0.15599452],
			[0.05808361, 0.86617615]
		]),
		np.array([
			[0.80180614, 1.39618075],
			[0.75133599, 0.81056611],
			[0.17853253, 0.21601250],
			[0.58986331, 1.31118124]
		]),
		np.array([
			[ 0.88373198, -0.84320355,  2.02373441],
			[ 0.44612873, -0.55645555,  1.62630021],
			[ 0.12397150, -0.14321340,  0.39914061],
			[ 0.86812753, -0.75367481,  1.64291426]
		])
	]

	y_prob1 = np.array([
		[0.35470123, 0.00564214, 0.17554998, 0.15060211, 0.00122216, 0.31228238],
		[0.30667213, 0.01292803, 0.14649600, 0.21525318, 0.00606262, 0.31258804],
		[0.21907174, 0.09982604, 0.18449050, 0.19719398, 0.08077731, 0.21864043],
		[0.34294269, 0.01084483, 0.21392286, 0.14135344, 0.00239295, 0.28854323]
	])

	# test sigmoid
	X2 = np.random.rand(3, 3)
	nn_model_2 = NeuralNetwork(
		input_size=3,
		hidden_layer_sizes=[4, 2], 
		output_size=2,
		batch_size=None,
		num_epochs=None,
		learning_rate=None,
		activation_function='sigmoid',
		random_seed=42
	)

	z2 = [
	    np.array([
	        [-0.64321221,  0.29274987,  1.09313440,  0.37755966],
	        [ 0.28436151, -0.13010085,  0.95937668,  1.41949567],
	        [ 0.17951121, -0.13144790,  1.08170967,  1.32305880]
	    ]),
	    np.array([
	        [-2.20174445, -1.58370500],
	        [-2.13183597, -2.26469862],
	        [-2.14750295, -2.18556351]
	    ]),
	    np.array([
	        [ 0.15746787, -0.26507983],
	        [ 0.16177227, -0.15799480],
	        [ 0.16007928, -0.16758533]
	    ])
	]

	a2 = [
	    np.array([
	        [0.06505159, 0.94888554, 0.96563203],
	        [0.80839735, 0.30461377, 0.09767211],
	        [0.68423303, 0.44015249, 0.12203823]
	    ]),
	    np.array([
	        [0.34452078, 0.57266921, 0.74897149, 0.59328439],
	        [0.57061518, 0.46752059, 0.72299699, 0.80525934],
	        [0.54475768, 0.46718526, 0.74681739, 0.78969016]
	    ]),
	    np.array([
	        [0.09959395, 0.17027140],
	        [0.10604082, 0.09408911],
	        [0.10456479, 0.10105440]
	    ])
	]

	y_prob2 = np.array([
	    [0.60409273, 0.39590727],
	    [0.57926748, 0.42073252],
	    [0.58119103, 0.41880897]
	])

	test_cases = [
		[nn_model_1, X1, z1, a1, y_prob1],
		[nn_model_2, X2, z2, a2, y_prob2]
	]

	return test_cases


def backward_pass_data():

	'''
	backward pass data

	'''

	np.random.seed(42)

	# test linear
	X1 = np.random.rand(4, 2)
	y1 = np.array([[1,0,0,0,0,0], [0,0, 1,0,0,0], [0,0,0,0,1,0], [0,0,0,0,0,1]])
	nn_model_1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=6,
		batch_size=8,
		num_epochs=1,
		learning_rate=.2,
		activation_function='linear',
		random_seed=42
	)

	w1 = [
		np.array([
			[ 0.44334871, -0.13533799],
			[ 0.62110308,  1.52554081]
		]),
		np.array([
			[-0.20242995, -0.21152959,  1.55957955],
			[ 0.80343434, -0.42904677,  0.53292430]
		]),
		np.array([
			[-0.45798873, -0.46735695,  0.24281475, -1.93209433, -1.71951307, -0.55353245],
			[-1.01701250,  0.31596840, -0.91498722, -1.39322658,  1.45937690, -0.22915809],
			[ 0.07534353, -1.42925343, -0.51399809,  0.06263336, -1.13346184,  0.37276080]
		])
	]

	b1 = [
		np.array([
			-0.11920862,
			-0.08191145
		]),
		np.array([
			 0.00422167,
			 0.11447647,
			-0.05788766
		]),
		np.array([
			-0.01116939,
			-0.00646205,
			 0.01397703,
			-0.03522014,
			 0.04547725,
			-0.00660270
		])
	]


	# test linear
	X2 = np.random.rand(3, 2)
	y2 = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1]])
	nn_model_2 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=3,
		batch_size=16,
		num_epochs=1,
		learning_rate=.4,
		activation_function='sigmoid',
		random_seed=42
	)

	w2 = [
		np.array([
			[ 0.49922129, -0.13768998],
			[ 0.64806920,  1.52312934]
		]),
		np.array([
			[-0.23904370, -0.24414657,  1.57309198],
			[ 0.76067298, -0.48328891,  0.53503081]
		]),
		np.array([
			[-0.41601090, -0.49312138,  0.22194710],
			[-1.88624309, -1.74439073, -0.56985179],
			[-0.95084849,  0.27979828, -0.93555765]
		])
	]

	b2 = [
		np.array([
			-0.00515119,
			-0.00131378
		]),
		np.array([
			-0.00429768,
			-0.01012843,
			-0.01277860
		]),
		np.array([
			 0.07519822,
			-0.04723812,
			-0.02796010
		])
	]


	test_cases = [
		[nn_model_1, X1, y1, w1, b1],
		[nn_model_2, X2, y2, w2, b2],
	]


	return test_cases


def train_data():

	'''
	train data

	'''

	np.random.seed(42)

	# test linear
	X1 = np.random.rand(4, 2)
	y1 = np.array([2, 4, 1, 5])
	nn_model_1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=6,
		batch_size=8,
		num_epochs=5,
		learning_rate=.2,
		activation_function='linear',
		random_seed=42
	)

	w1 = [
		np.array([
			[ 0.21406833, -0.39867903],
			[ 0.51477260,  1.43045688]
		]),
		np.array([
			[-0.26145735, -0.08362033,  1.51542189],
			[ 0.83143289, -0.24423939,  0.52171115]
		]),
		np.array([
			[-0.56702166, -0.50790390,  0.31065341, -1.95891414, -1.67739250, -0.48709199],
			[-0.98344218,  0.34363240, -0.94297957, -1.39959164,  1.43812057, -0.23477867],
			[-0.06251250, -1.51477505, -0.43271451,  0.05005074, -1.00039370,  0.39436934]
		])
	]

	b1 = [
		np.array([
			-0.47673314,
			-0.27341523
		]),
		np.array([
			 0.02783084,
			 0.45728521,
			-0.25758760
		]),
		np.array([
			-0.17746727,
			 0.09098496,
			 0.03156622,
			-0.09361203,
			 0.11080449,
			 0.03772363
		])
	]


	# test linear
	X2 = np.random.rand(3, 2)
	y2 = np.array([0, 1, 2])
	nn_model_2 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=3,
		batch_size=16,
		num_epochs=10,
		learning_rate=.4,
		activation_function='sigmoid',
		random_seed=42
	)

	w2 = [
		np.array([
			[ 0.52583164, -0.13413938],
			[ 0.66857708,  1.53134290]
		]),
		np.array([
			[-0.25971961, -0.28759661,  1.56213185],
			[ 0.73155536, -0.55371391,  0.51926174]
		]),
		np.array([
			[-0.25510112, -0.57533279,  0.14324873],
			[-1.81743562, -1.81329806, -0.56975192],
			[-0.75033675,  0.19358687, -1.04985798]
		])
	]

	b2 = [
		np.array([
			-0.03463850,
			-0.01072012
		]),
		np.array([
			-0.00662498,
			-0.02799095,
			-0.06226527
		]),
		np.array([
			 0.30816296,
			-0.19624885,
			-0.11191410
		])
	]

	test_cases = [
		[nn_model_1, X1, y1, w1, b1],
		[nn_model_2, X2, y2, w2, b2],
	]

	return test_cases


def predict_data():

	'''
	predict data

	'''

	np.random.seed(42)

	# test linear
	X1 = np.random.rand(4, 2)
	nn_model_1 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=6,
		batch_size=8,
		num_epochs=5,
		learning_rate=.2,
		activation_function='linear',
		random_seed=42
	)

	y1_expected = np.array([0, 5, 0, 0])
	

	# test linear
	X2 = np.random.rand(3, 2)
	nn_model_2 = NeuralNetwork(
		input_size=2,
		hidden_layer_sizes=[2, 3], 
		output_size=3,
		batch_size=16,
		num_epochs=10,
		learning_rate=.4,
		activation_function='sigmoid',
		random_seed=42
	)

	y2_expected = np.array([1, 1, 1])


	test_cases = [
		[nn_model_1, X1, y1_expected],
		[nn_model_2, X2, y2_expected],
	]

	return test_cases
