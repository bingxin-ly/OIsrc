from hashlib import sha256
with open('D:\src\python\chatATP\chatATP.py', 'rb') as f:
    data = f.read()
version = sha256(data).hexdigest()
print(version + ' ' * (100 - len(version)), ',')
from json import dumps
# print(dumps({'res': True}))