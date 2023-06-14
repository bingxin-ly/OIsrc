def trans(str: str):
    if str.endswith('（简单）\n'):
        return (1, str.split('（')[0])
    if str.endswith('（中等）\n'):
        return (2, str.split('（')[0])
    if str.endswith('（困难）\n'):
        return (3, str.split('（')[0])


with open('D:\\src\\inf.txt', encoding='utf-8') as f:
    words = list(map(trans, f.readlines()))
words.sort()
with open('out', 'w', encoding='utf-8') as f:
    [f.write(f'{x[0]}: {x[1]}\n') for x in words]
