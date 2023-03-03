import os
import json
import requests

url_set = [
    'https://api.anosu.top/api', 'https://moe.anosu.top/api',
    'https://api.anosu.top/img', 'https://moe.anosu.top/img',
    'https://api.jitsu.top/api', 'https://moe.jitsu.top/api',
    'https://api.jitsu.top/img', 'https://moe.jitsu.top/img'
]
form_header = {
    'User-Agent':
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36',
    'Host':
    '',
    'Accept-Language':
    'zh-CN,zh;q=0.9',
    'Accept':
    'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9'
}


def bar(i, num):
    print('\r[%3.2f%%]: |%-50s|' % (100 * i / num, '▋' * (50 * i // num)),
          end='',
          flush=True)


def get_image(num):
    not_module = __name__ == '__main__'
    url = ""
    for url in url_set:
        code = requests.get(url, allow_redirects=False).status_code
        if code // 100 == 3:
            print('The link being used now is: %s' % url)
            break
        else:
            if url == url_set[-1]:
                print('All the links is not available')
                exit(-1)
            continue

    form_header['Host'] = url.split('//')[1]
    response = requests.get(url + '/?num=%d' % num)
    if response.url == url:
        print('Unable to access the server, please try again later')
        exit(-1)

    # save the image
    img_names = []
    try:
        imageurls = json.loads(response.content)['pics']
    except UnicodeDecodeError:
        imageurls = [response.url]
    for i in range(len(imageurls)):
        image_name = imageurls[i].split('/')[-1]
        img_names.append(image_name)
        image = requests.get(imageurls[i]).content

        if not os.path.exists('./pics/'):
            os.mkdir('./pics/')
        with open('./pics/%s' % image_name, 'wb') as file:
            file.write(image)

        # process bar
        if not_module:
            bar(i + 1, num)
    return img_names


if __name__ == '__main__':
    n = int(input('获取图片数量（整数）：'))
    get_image(n)
