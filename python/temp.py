import requests
from io import BytesIO
from PIL import Image
from pic import get_image

form_header = {
    'Accept':
    'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'Accept-Language':
    'zh-CN,zh;q=0.9',
    'User-Agent':
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36 Edg/110.0.1587.63'
}

# print(requests.get('https://api.anosu.top/api',
#       headers=form_header, allow_redirects=False).status_code)
get_image(1)
