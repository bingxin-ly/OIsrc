import requests
import random


def get_random_image_urls(count):
    '''Generates count random image urls by querying Unsplash APT'''
    url = 'https://api.unsplash.com/photos/random'
    params = {' client_id': '你的客户端ID', 'count': count}
    response = requests.get(url, params=params)
    data = response.json()
    return [photo[' urls']['full'] for photo in data]


def save_images(urls):
    '''Downloads the images from the given urls and saves them'''
    for url in urls:

        filename = url.split('/')[-1]
        r = requests.get(url)
        with open(filename, 'wb') as f:
            f.write(r.content)


if __name__ == '__main__':
    # Get count random image urls
    count = 10  # Get 10 images
    urls = get_random_image_urls(count)
    # Save the images
    save_images(urls)
