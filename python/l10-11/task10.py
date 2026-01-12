import numpy as np
import matplotlib.pyplot as plt
import torchvision
from sklearn.metrics import precision_score, recall_score
from sklearn.manifold import TSNE


transform = torchvision.transforms.Compose([
                    torchvision.transforms.ToTensor(),
                    torchvision.transforms.Normalize((0.5), (0.5))
                                            ])

train_dataset = torchvision.datasets.MNIST(
    root="./MNIST/train", train=True,
    transform=torchvision.transforms.ToTensor(),
    download=False)

test_dataset = torchvision.datasets.MNIST(
    root="./MNIST/test", train=False,
    transform=torchvision.transforms.ToTensor(),
    download=False)


def average_digit(data, digit):
    filtered_data = [x[0] for x in data if np.argmax(x[1]) == digit]
    filtered_array = np.asarray(filtered_data)
    return np.average(filtered_array, axis=0)


def encode_label(j):
    e = np.zeros((10, 1))
    e[j] = 1.0
    return e


def shape_data(data):
    features = [np.reshape(x[0].numpy(), (784, 1)) for x in data]
    labels = [encode_label(y[1]) for y in data]
    return zip(features, labels)


train = list(shape_data(train_dataset))
test = list(shape_data(test_dataset))

'''---------------------1---------------------'''
average_digits = [] # weights matrix
for digit in range(10):
    avg_digit = average_digit(train, digit)
    average_digits.append(avg_digit)


'''---------------------2---------------------
2. Создать десять классификаторов с весами "avg_digit". На вход 
классификатора подаётся цифра из тестового набора, а на выходе мы 
получаем 0 или 1, в зависимости от того принадлежит ли цифра нужному
классу ('0' - '9'). Добавить смещение (bias).
'''

def binary_step(x):
    return 1.0 if x>=0 else 0


def classif0(digit, weights, b):
    W = np.transpose(weights[0])
    res_by0 = (np.dot(W, digit) + b[0]) / np.linalg.norm(W)
    return binary_step(res_by0)


def classif1(digit, weights, b):
    W = np.transpose(weights[1])
    res_by1 = (np.dot(W, digit) + b[1]) / np.linalg.norm(W)
    return binary_step(res_by1)


def classif2(digit, weights, b):
    W = np.transpose(weights[2])
    res_by2 = (np.dot(W, digit) + b[2]) / np.linalg.norm(W)
    return binary_step(res_by2)


def classif3(digit, weights, b):
    W = np.transpose(weights[3])
    res_by3 = (np.dot(W, digit) + b[3]) / np.linalg.norm(W)
    return binary_step(res_by3)


def classif4(digit, weights, b):
    W = np.transpose(weights[4])
    res_by4 = (np.dot(W, digit) + b[4]) / np.linalg.norm(W)
    return binary_step(res_by4)


def classif5(digit, weights, b):
    W = np.transpose(weights[5])
    res_by5 = (np.dot(W, digit) + b[5]) / np.linalg.norm(W)
    return binary_step(res_by5)


def classif6(digit, weights, b):
    W = np.transpose(weights[6])
    res_by6 = (np.dot(W, digit) + b[6]) / np.linalg.norm(W)
    return binary_step(res_by6)


def classif7(digit, weights, b):
    W = np.transpose(weights[7])
    res_by7 = (np.dot(W, digit) + b[7]) / np.linalg.norm(W)
    return binary_step(res_by7)


def classif8(digit, weights, b):
    W = np.transpose(weights[8])
    res_by8 = (np.dot(W, digit) + b[8]) / np.linalg.norm(W)
    return binary_step(res_by8)


def classif9(digit, weights, b):
    W = np.transpose(weights[9])
    res_by9 = (np.dot(W, digit) + b[9]) / np.linalg.norm(W)
    return binary_step(res_by9)


classifiers = [classif0, classif1, classif2, classif3, classif4, classif5, classif6, classif7, classif8, classif9]
b = [-50, -25, -35, -35, -30, -30, -35, -30, -40, -35]
x = train[4][0]
res = classif0(x, average_digits, b)
# print(res)

'''---------------------3---------------------'''
'''3. Рассчитать точность каждого классификатора.'''
def calculate_accuracy(classifier, test_data, weights, bias):
    correct_preds = 0
    total_preds = len(test_data)

    for data in test_data:
        digit = data[0]
        label = np.argmax(data[1])
        pred_label = classifier(digit, weights, bias)
        if pred_label == 1 and label == classifier.__name__[-1]:
            correct_preds += 1
        elif pred_label == 0 and label != classifier.__name__[-1]:
            correct_preds += 1
    
    accuracy = correct_preds / total_preds
    return accuracy


accuracy_list = []
for i, classifier in enumerate(classifiers):
    accuracy = calculate_accuracy(classifier, test, average_digits, b)
    accuracy_list.append(accuracy)

print(accuracy_list)


'''4. Объеденить получившиеся классификаторы в одну модель, 
которая принимает картинку, а выдаёт вектор размера 10. 
(напр. input=[3], output = [0, 0, 0, 1, 0, 0, 0, 0, 0, 0]).
'''

def combined_classifier(classifiers, digit, weights, biases):
    result = [classifier(digit, weights, biases) for classifier in classifiers]
    return result


'''---------------------5---------------------'''
'''5. Рассчитать 𝑝𝑟𝑒𝑐𝑖𝑠𝑖𝑜𝑛 и 𝑟𝑒𝑐𝑎𝑙𝑙 получившейся модели на 
тестовом наборе.'''
def get_predictions(classifiers, test_data, weights, biases):
    predictions = []
    for data in test_data:
        digit = data[0]
        prediction = combined_classifier(classifiers, digit, weights, biases)
        predictions.append(prediction)
    return predictions

predictions = get_predictions(classifiers, test, average_digits, b)


true_labels = [np.argmax(data[1]) for data in test]
predicted_labels = [np.argmax(pred) for pred in predictions]

precision = precision_score(true_labels, predicted_labels, average='macro')
recall = recall_score(true_labels, predicted_labels, average='macro')
print(f"Precision: {precision:.4f}")
print(f"Recall: {recall:.4f}")


# '''6'''
# '''6. Визуализировать набор необработанных данных с помощью алгоритма t-SNE.
# Взять 30 изображений каждого класса, каждое изображение перевести в 
# вектор размера (784), визуализировать полученные вектора с помощью t-SNE.
# '''

# def image_to_vector(image):
#     return image.numpy().reshape(784)

# data = []
# labels = []
# for digit in range(10):
#     count = 0
#     for image, label in train_dataset:
#         if label == digit and count < 30:
#             data.append(image_to_vector(image))
#             labels.append(label)
#             count += 1

# data = np.array(data)
# labels = np.array(labels)

# tsne = TSNE(n_components=2, random_state=24)
# data_2d = tsne.fit_transform(data)

# plt.figure(figsize=(10, 8))
# scatter = plt.scatter(data_2d[:, 0], data_2d[:, 1], c=labels, cmap='tab10', s=50, alpha=0.6)
# plt.colorbar(scatter, ticks=range(10))
# plt.title('t-SNE MNIST')
# plt.show()


# '''7'''
# '''7. Визуализировать результаты работы вашей модели (логиты) с помощью 
# алгоритма t-SNE. Прогнать изображения через вашу модель, получившиеся 
# вектора размера (10) визуализировать с помощью t-SNE.
# '''

# def get_logits(data, weights, biases):
#     logits = []
#     for digit in data:
#         logit = combined_classifier(classifiers, digit, weights, biases)
#         logits.append(logit)
#     return logits

# logits = get_logits(data, average_digits, b)
# logits = np.array(logits)

# tsne = TSNE(n_components=2, random_state=24)
# logits_2d = tsne.fit_transform(logits)

# plt.figure(figsize=(10, 8))
# scatter = plt.scatter(logits_2d[:, 0], logits_2d[:, 1], c=labels, cmap='tab10', s=50, alpha=0.6)
# plt.colorbar(scatter, ticks=range(10))
# plt.title('t-SNE Logits')
# plt.show()