import torch.nn as nn
import torch

in_seq = 64
out_seq = 10
SeqModel = nn.Sequential(
    nn.Linear(in_seq, 32),
    nn.ReLU(),
    nn.Linear(32, out_seq),
    nn.ReLU()   
)

x = torch.rand(4, in_seq)  # batch size = 4
y = torch.rand(4, out_seq)

y_pred = SeqModel(x)  # Прямой проход
print(y_pred)
l1_loss = nn.L1Loss()
loss = l1_loss(y, y_pred)
print('Loss:', loss)


'''
С помощью библиотеки torch реализовать модель с прямым проходом, 
состоящую из 3 полносвязных слоёв с функциями активации: ReLU, tanh, 
Softmax. Длины векторов на входе 256, на выходе 4, промежуточные: 64 
и 16. Использовать модули - nn.Module
'''

class Model3(nn.Module):
    def __init__(self, in_ch, mid_ch1, mid_ch2, out_ch):
        super().__init__()
        self.fc1 = nn.Linear(in_ch, mid_ch1)
        self.fc2 = nn.Linear(mid_ch1, mid_ch2, bias=False)
        self.fc3 = nn.Linear(mid_ch2, out_ch, bias=False)
        self.relu = nn.ReLU()
        self.tanh = nn.Tanh()
        self.softmax = nn.Softmax(dim=1)
        
    def forward(self, x):
        h = self.fc1(x)
        h = self.relu(h)
        h = self.fc2(h)
        h = self.tanh(h)
        h = self.fc3(h)
        y = self.softmax(h)
        return y


model3 = Model3(256, 64, 16, 4)
x = torch.rand(4, 256)  # batch size = 4
y = torch.rand(4, 4)


w1_1 = model3.fc1.weight.data.clone()  # Сохранение состояния весов
y_pred = model3(x)  # Прямой проход
print(y_pred)

l1_loss = nn.L1Loss()
loss = l1_loss(y, y_pred)
print('Loss:', loss)

'''
Реализовать модель с прямым проходом, состоящую из 2 свёрток (Conv)
с функциями активации ReLU и 2 функций MaxPool. Первый слой переводит 
из 3 каналов в 8, второй из 8 слоёв в 16. На вход подаётся изображение 
размера 19х19. (19х19x3 -> 18x18x8 -> 9x9x8 -> 8x8x16 -> 4x4x16). 
Использовать модули - nn.Module
'''

class ModelConv(nn.Module):
    def __init__(self):
        super().__init__()
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=8, 
                               kernel_size=3, stride=1, padding=1)
        self.conv2 = nn.Conv2d(in_channels=8, out_channels=16,
                               kernel_size=3, stride=1, padding=1)
        self.ReLU = nn.ReLU()
        self.MaxPool = nn.MaxPool2d(kernel_size=2, stride=2)
    
    def forward(self, x):
        h = self.conv1(x)
        h = self.ReLU(h)
        h = self.MaxPool(h)
        h = self.conv2(h)
        h = self.ReLU(h)
        y = self.MaxPool(h)
        return y


modelConv = ModelConv()

x = torch.randn(1, 3, 19, 19)
y = modelConv(x)
print(y.shape)


'''
Объединить сети из п.2 и п.1. На выход изображение 
размера 19х19, на выходе вектор из 4 элементов
'''
in_seq = 19 * 19
out_seq = 32
in_ch = 32
mid_ch1 = 16
mid_ch2 = 8
out_ch = 4


SeqModel1 = nn.Sequential(
    nn.Linear(in_seq, 32),
    nn.ReLU(),
    nn.Linear(32, out_seq),
    nn.ReLU()   
)


class CombinedModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.model1 = SeqModel1
        self.model2 = Model3(in_ch, mid_ch1, mid_ch2, out_ch)

    def forward(self, x):
        x = x.view(x.size(0), -1)
        h = self.model1(x)
        y = self.model2(h)
        return y

model = CombinedModel()
x = torch.randn(1, 1, 19, 19)
y = torch.randn(1, 4)

y_pred = model(x)
print(y_pred.shape)