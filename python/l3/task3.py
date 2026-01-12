#1-2
class Item():
    def __init__(self, count=3, max_count=16):
        self._count = count
        self._max_count = 16
    
    @property
    def count(self):
        return self._count

    def update_count(self, val):
        if val < self._max_count:
            self._count = val
            return True
        else:
            return False
        
    def __add__(self, num):
        return self._count + num
    
    def __sub__(self, num):
        return self._count - num

    def __mul__(self, num):
            return self._count * num
    
    def __lt__(self, num):
        return self._count < num
    
    def __gt__(self, num):
        return self._count > num
    
    def __le__(self, num):
        return self._count <= num
    
    def __ge__(self, num):
        return self._count >= num
    
    def __eq__(self, num):
        return self._count == num
    
    def __iadd__(self, num):
        self._count += num
        self._count = max(0, min(self._count, self._max_count))
        return self

    def __isub__(self, num):
        self._count -= num
        self._count = max(0, min(self._count, self._max_count))
        return self

    def __imul__(self, num):
        self._count *= num
        self._count = max(0, min(self._count, self._max_count))
        return self

item = Item()
print(item.count)
print(item.update_count(4), item.count)
print(item + 2)
print(item - 1)
print(item * 10)

print(item < 1)
print(item > 1)
print(item >= 4)

item += 2
print(item._count)
item -= 2
print(item.count)
item *= 10
print(item.count)
print('-------------------')


#3
class Fruit(Item):
    def __init__(self, ripe=True, **kwargs):
        super().__init__(**kwargs)
        self._ripe = ripe


class Food(Item):
    def __init__(self, saturation, **kwargs):
        super().__init__(**kwargs)
        self._saturation = saturation
        
    @property
    def eatable(self):
        return self._saturation > 0
    
    def __call__(self):
        """ Вызов как функции """
        if self.eatable:
            new_count = max(self.count - 1, 0)
            self.update_count(new_count)            
          
    def __len__(self):
        """ Получение длины объекта """
        return self.count
    

class Orange(Fruit, Food):
    def __init__(self, ripe, count=1, max_count=32, color='orange', saturation=17):
        super().__init__(saturation=saturation, ripe=ripe, count=count, max_count=max_count)
        self._color = color
    
    @property
    def color(self):
        return self._color
    
    @property
    def eatable(self):
        return super().eatable and self._ripe
    
    def __str__(self):
        """ Вызов как строки """
        return f'Stack of {self.count} {self.color} oranges' 


class Grape(Fruit, Food):
    def __init__(self, ripe, count=1, max_count=32, color='purple', saturation=11):
        super().__init__(saturation=saturation, ripe=ripe, count=count, max_count=max_count)
        self._color = color
    
    @property
    def color(self):
        return self._color
    
    @property
    def eatable(self):
        return super().eatable and self._ripe

    def __str__(self):
        """ Вызов как строки """
        return f'Stack of {self.count} {self.color} bunches of grape' 
    

class Bread(Food):
    def __init__(self, count=1, max_count=32, color='brown', saturation=13):
        super().__init__(saturation=saturation, count=count, max_count=max_count)
        self._color = color
    
    @property
    def color(self):
        return self._color
    
    def __str__(self):
        """ Вызов как строки """
        return f'Stack of {self.count} {self.color} pieces of bread' 
    

class Egg(Food):
    def __init__(self, count=1, max_count=32, saturation=13):
        super().__init__(saturation=saturation, count=count, max_count=max_count)

    def __str__(self):
        """ Вызов как строки """
        return f'Stack of {self.count} eggs' 
    

orange = Orange(True, color='yellow')
print('Orange')
print(orange.color)
print(orange.eatable)
grape = Grape(False, count=12)
print('Grape')
print(grape.count)
print(grape.eatable)
print(grape + 6)
bread = Bread()
print('Bread')
print(bread.count)
bread()
print(bread.count)
egg = Egg(count=4, saturation=0)
print('Egg')
print(egg.count)
egg()
print(egg.count)
print(egg.eatable)
print('---------------------------')


#4
class Inventory:
    def __init__(self, len=10):
        self._len = len
        self._lst = [None]*len
        
    def __getitem__(self, index):
        """ Получение элемента по индексу """
        if index > len(self):
            raise IndexError(f'Index {index} more then {len(self)}')
        return self._lst[index]
        
    def __len__(self):
        return self._len
    
    def __setitem__(self, index, item):
        if index > len(self):
            raise IndexError(f'Index {index} more then {len(self)}')
        elif item.eatable == False:
            print(f'Item {item} is not eatable')
        else:
            self._lst[index] = item
    
    def __str__(self):
        """ Вызов как строки """
        return str([str(x) for x in self._lst])
    
    def dec_item(self, index):
        if self._lst[index].count == 1:
            self._lst.pop(index)
        else:
            new_count = max(self._lst[index].count - 1, 0)
            self._lst[index].update_count(new_count)   



orange = Orange(True, count=10, color='yellow')
inventory = Inventory()
inventory[2] = orange
print(inventory)
print(inventory[2])
orange()
print(inventory[2])
egg = Egg(saturation=0)
inventory[3] = egg
grape = Grape(True)
inventory[3] = grape
print(inventory)
inventory.dec_item(2)
print(inventory[2])
inventory.dec_item(3)
print(inventory)