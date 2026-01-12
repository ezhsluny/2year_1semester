import numpy as np

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

np.random.seed(17)

class Neuron:
    def __init__(self, input_size):
        self._weights = np.random.rand(input_size)
        self._bias = np.random.rand()
        self._input = None
        self._output = None
    
    def forward(self, x):
        self._input = x
        self._output = sigmoid(np.dot(x, self._weights) + self._bias)
        return self._output
    
    def backward(self, x, loss, lr=0.1):
        d_pred_output = loss * sigmoid_derivative(self._output)
        d_weights = np.dot(self._input.T, d_pred_output)
        d_bias = d_pred_output
        self._weights -= lr * d_weights.flatten()
        self._bias -= lr * d_bias.flatten()
        return d_pred_output * self._weights.T


class Model:
    def __init__(self):
        self.neuron1 = Neuron(2)
        self.neuron2 = Neuron(2)
        self.neuron3 = Neuron(2)
    
    def forward(self, x):
        out1 = self.neuron1.forward(x)
        out2 = self.neuron2.forward(x)
        out1w2 = np.array([[out1[0], out2[0]]])
        out3 = self.neuron3.forward(out1w2)
        return out3
    
    def backward(self, x, loss):
        out = np.array([[self.neuron1._output[0], self.neuron2._output[0]]])
        loss = self.neuron3.backward(out, loss)
        loss1, loss2 = loss[0, 0], loss[0, 1]
        self.neuron1.backward(x, loss1)
        self.neuron2.backward(x, loss2)


def loss(y_pred, y_true):
    return y_pred - y_true

X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
y = np.array([[0], [1], [1], [0]])

model = Model()

epochs = 10000

for epoch in range(epochs):
    for x, label in zip(X, y):
        x = np.array([x])
        label = np.array([label])

        y_pred = model.forward(x)
        err = loss(y_pred, label)
        model.backward(x, err)

    if epoch % 1000 == 0:
        print(f"Epoch {epoch}, Loss: {np.mean(err)}")

for x in X:
    x = np.array([x])
    print(f"Input: {x}, Output: {np.round(model.forward(x))}")