import torch
import torch.nn as nn
import torchvision
import numpy as np


'''
С помощью библиотеки torch создать модель с прямым проходом,
состоящую из 3 слоёв* с функциями активации: ReLu, ReLu, 
Softmax.
Обучить нейросеть распознавать рукописные цифры на 
датасете MNIST (28х28 px).
Два первых слоя могут быть полносвязные или 
свёрточные на ваш выбор. Последний слой - это FC слой 
с 10 нейронами.
'''

class Model(nn.Module):
    def __init__(self):
        super(Model, self).__init__()
        self.fc1 = nn.Linear(28*28, 512)
        self.fc2 = nn.Linear(512, 256)
        self.fc3 = nn.Linear(256, 10)
        self.relu = nn.ReLU()
        self.softmax = nn.Softmax(dim=1)

    def forward(self, x):
        x = self.relu(self.fc1(x))
        x = self.relu(self.fc2(x))
        x = self.fc3(x)
        y = self.softmax(x)
        return y

    

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


from torch.utils.data import DataLoader
import torch.optim as optim

train = DataLoader(train_dataset, batch_size=30, shuffle=True)
test = DataLoader(test_dataset, batch_size=30, shuffle=False)

num_epochs = 5
model = Model()
optimizer = optim.Adam(model.parameters(), lr=0.001)
lossf = nn.CrossEntropyLoss()

model.train()
for epoch in range(num_epochs):
    losst = 0.0
    for images, labels in train:
        print(type(images))
        images = images.view(images.size(0), -1)
        optimizer.zero_grad()
        outputs = model(images)
        loss = lossf(outputs, labels)
        loss.backward()
        optimizer.step()
        losst += loss.item()
    print(f"Epoch {epoch+1}/{num_epochs}, Loss: {losst/len(train)}")
        


model.eval()
correct = 0
total = 0
with torch.no_grad():
    for images, labels in test:
        images = images.view(images.size(0), -1)  # Преобразование изображений в вектор
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        print (predicted)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
print(f"Accuracy: {100 * correct / total}%")


# import matplotlib.pyplot as plt


# # Function to display images
# def imshow(img, title):
#     img = img / 2 + 0.5  # unnormalize
#     npimg = img.numpy()
#     plt.imshow(npimg, cmap='gray')
#     plt.title(title)
#     plt.axis('off')

# # Plot the images
# dataiter = iter(test)
# images, labels = next(dataiter)

# fig = plt.figure(figsize=(10, 10))
# for i in range(30):
#     ax = fig.add_subplot(6, 5, i + 1, xticks=[], yticks=[])
#     imshow(images[i].squeeze(), f'Label: {labels[i]}')

# plt.tight_layout()
# plt.show()