import socket
from time import strftime
from json import dumps, loads
from socketserver import BaseRequestHandler, ThreadingTCPServer

_buf = 1024
_length = 100
_version = 'd91ea1514cadc6f17ad20d241fad8c1194f97d98a96d9ba5d67fe3e4e8c47bb3'
connected = {}


def debug(x):
    print(x)
    return x


def chk_version(conn: socket.socket):
    res = conn.recv(_length).decode().strip() == _version
    conn.sendall(dumps({'res': res}).encode())
    return res


def chk_nick(conn: socket.socket):
    nick = conn.recv(30).decode().strip()
    res = None
    if nick == '':
        response = dumps({
            'res': 'err',
            'reason': '昵称不可为空！'
        })
    elif nick in connected.keys():
        response = dumps({
            'res': 'err',
            'reason': '这个名称已被使用！'
        })
    else:
        response = dumps({
            'res': 'ok'
        })
        res = nick
    response += ' ' * (_length - len(response))
    return (res, response.encode())


def broadcast(head, data):
    ''' 我们使用三个属性来描述数据: type: str, from: str, size: uint32 '''
    for v in connected.values():
        v.sendall(head)
        v.sendall(data)


class ATPHandler(BaseRequestHandler):
    def setup(self) -> None:
        self.success = False
        self.nick = None

        if not chk_version(self.request):
            return
        while self.nick == None:
            res = chk_nick(self.request)
            self.nick = res[0]
            self.request.sendall(res[1])
        connected[self.nick] = self.request
        self.success = True

        print('[{}]: {} from {} connected'
              .format(strftime('%H:%M:%S'), self.nick, self.client_address))
        msg = f'{self.nick}加入了聊天室\n'.encode()
        head = dumps({
            'type': 'str',
            'sender': 'Server',
            'size': len(msg)
        })
        head += ' ' * (_length - len(head))
        broadcast(head.encode(), msg)

    def handle(self) -> None:
        if not self.success:
            return
        try:
            while True:
                ''' 我们使用三个属性来描述数据: type: str, from: str, size: uint32 '''
                head = debug(self.request.recv(_length))
                prased = loads(head.decode())
                data = b''
                # How stupid I was | Why I was that stupid
                # for _ in range(debug(prased['size']) // _buf):
                #     data += self.request.recv(_buf)
                # data += self.request.recv(prased['size'] % _buf)
                while len(data) < prased['size']:
                    data += self.request.recv(_buf)
                debug(len(data))
                broadcast(head, data)
        except socket.error as e:
            print('[{}]: {} lost connection\ncause: {}'
                  .format(strftime('%H:%M:%S'), self.nick, e))
            return
        except Exception as e:
            print(e.args)
            return

    def finish(self) -> None:
        connected.pop(self.nick, None)
        msg = f'{self.nick}离开了聊天室，（悲\n'.encode()
        broadcast(dumps({
            'type': 'str',
            'sender': 'Server',
            'size': len(msg)
        }).encode(), msg)
        self.request.close()


if __name__ == "__main__":
    s = ThreadingTCPServer(('192.168.6.205', 12332), ATPHandler)
    print('Server running...')
    s.serve_forever()
