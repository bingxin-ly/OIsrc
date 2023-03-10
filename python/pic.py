import os
from io import BytesIO
from json import loads
import requests

out_module = __name__ == '__main__'
url_set = [
    'https://api.anosu.top/api', 'https://moe.anosu.top/api',
    'https://api.anosu.top/img', 'https://moe.anosu.top/img',
    'https://api.jitsu.top/api', 'https://moe.jitsu.top/api',
    'https://api.jitsu.top/img', 'https://moe.jitsu.top/img'
]
form_header = {
    'Accept':
    'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'Accept-Language':
    'zh-CN,zh;q=0.9',
    'User-Agent':
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36'
}


def bar(i, num):
    print('\r[%3.2f%%]: |%-50s|' % (100 * i / num, '▋' * (50 * i // num)),
          end='',
          flush=True)


def get_image(num):
    # 找到可用的url
    for url in url_set:
        if requests.get(url, headers=form_header, allow_redirects=False
                        ).status_code // 100 == 3:
            if out_module:
                print('The link being used now is: %s' % url)
            break
        else:
            if url == url_set[-1]:
                print('All the links is not available')
                exit(-1)
            continue

    response = requests.get(url + '/?num=%d' % num, headers=form_header)
    if response.url == url:
        print('Unable to access the server, please try again later')
        exit(-1)

    # save the image
    imageurls = [response.url] if num == 1 else loads(response.content)['pics']
    imgs = []
    for i in range(len(imageurls)):
        image_name = imageurls[i].split('/')[-1]
        image = requests.get(imageurls[i], headers=form_header).content
        imgs.append((image_name, BytesIO(image)))

        # process bar
        if out_module:
            bar(i + 1, num)
    return imgs


def save(imgs):
    for i in range(len(imgs)):
        image_name = imgs[i][0]
        image = imgs[i][1]

        if not os.path.exists('./pics/'):
            os.mkdir('./pics/')
        with open('./pics/%s' % image_name, 'wb') as file:
            file.write(image.getbuffer())


if out_module:
    n = int(input('获取图片数量（整数）：'))
    save(get_image(n))
