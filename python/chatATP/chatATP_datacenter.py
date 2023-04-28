import socket
from logging import *
from log import setup_logger
from json import dumps, loads
from socketserver import BaseRequestHandler, ThreadingTCPServer

_buf = 1024
_length = 70
_encoding = 'GBK'
_version = '9db591838e0635abc46ddc828df417ac1845678ea20467df39eaf33dffd8ab76'
connected = {}


def chk_version(conn: socket.socket):
    res = conn.recv(_length).decode(_encoding).strip() == _version
    conn.sendall(dumps({'res': res}).encode(_encoding))
    return res


def chk_nick(conn: socket.socket):
    nick = conn.recv(20).decode(_encoding).strip()
    res = None
    if nick == '':
        response = dumps({
            'res': 'err',
            'reason': '昵称不可为空！'
        }, ensure_ascii=False)
    elif nick in connected.keys():
        response = dumps({
            'res': 'err',
            'reason': '这个名称已被使用！'
        }, ensure_ascii=False)
    else:
        response = dumps({
            'res': 'ok'
        }, ensure_ascii=False)
        res = nick
    response += ' ' * (_length - len(response))
    return (res, response.encode(_encoding))


def broadcast(head, data):
    ''' 我们使用三个属性来描述数据: type, sender, size '''
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

        logger.info(f'{self.nick} from {self.client_address} connected')
        msg = ('{}加入了聊天室\n当前在线的用户有: {}\n'.format
               (self.nick, '、'.join(connected.keys()))).encode(_encoding)
        head = dumps({
            'type': 'str',
            'sender': 'Server',
            'size': len(msg)
        })
        head += ' ' * (_length - len(head))
        broadcast(head.encode(_encoding), msg)

    def handle(self) -> None:
        if not self.success:
            return
        try:
            while True:
                ''' 我们使用三个属性来描述数据: type, sender, size '''
                head = self.request.recv(_length)
                prased = loads(head.decode(_encoding))
                data = b''
                while len(data) < prased['size']:
                    data += self.request.recv(_buf)
                broadcast(head, data)
        except socket.error as e:
            logger.info(f'{self.nick} lost connection\ncause: {e}')
            return
        except Exception as e:
            logger.exception('')
            return

    def finish(self) -> None:
        connected.pop(self.nick, None)
        msg = f'{self.nick}离开了聊天室，（悲\n'.encode(_encoding)
        broadcast(dumps({
            'type': 'str',
            'sender': 'Server',
            'size': len(msg)
        }).encode(_encoding), msg)
        self.request.close()


if __name__ == '__main__':
    s = ThreadingTCPServer(('192.168.6.205', 12332), ATPHandler)
    logger = setup_logger()
    logger.info('Server running...')
    s.serve_forever()
