import os
import random
res = os.listdir('./pics')
ret = random.choice(res)
print(ret)