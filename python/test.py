
from urllib.parse import unquote
 
# 对字符串‘%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1’进行解密
text = unquote("file:///C:/Users/PC/Desktop/%E5%A4%87%E4%BB%BD%202023.2.28/%E5%A4%87%E4%BB%BD%202023.2.28/%E5%9B%BE%E7%89%87/wallhaven-kx82d6_1920x1080.png", 'utf-8')
print(text)

