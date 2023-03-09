from math import sqrt

vector = list
gesture = ((1, 0, 0), (-1, 0, 0), (0, 1, 0), (0, -1, 0), (0, 0, 1), (0, 0, -1))


class missile:

    class miss_perfor:

        def __init__(self, parameter: list):
            self.rate, self.vm, \
                self.insure, self.explo, \
                self.lock, self.contr = parameter.__iter__()

    perfor: miss_perfor

    def __init__(self, parameter):
        self.perfor = self.miss_perfor(parameter)


class UAV:
    class _info:
        def __init__(self, id, group):
            self.id = id
            self.group = group

    class UAV_perfor:
        rate: tuple
        w: int
        vm: int
        visual: tuple

        def __init__(self, parameter: list):
            self.rate = parameter[0:2]
            self.w = parameter[2]
            self.vm = parameter[3]
            self.visual = parameter[4:6]

    info: _info
    perfor: UAV_perfor
    miss: missile

    def __init__(self, pos, dire_speed, parameter, missi):
        self.pos = [int(x) for x in pos]
        self.dire = dire_speed[0:3]
        self.speed = dire_speed[3:6]
        self.perfor = self.UAV_perfor(parameter)
        self.miss = missile(missi)
        self.aim = -1

    def get_speed(self):
        return sqrt(self.speed[0]**2 + self.speed[1]**2 + self.speed[2]**2)

    def cabrage():  # 俯仰
        pass

    def roll(self):  # 滚转
        pass

    def fly(self):
        pass

    def cobra_maneuver(self):
        tmp = dire
        dire = up
        up = -tmp

    def destroy(self, group: list):
        group.remove(self)


def getdis(a: UAV, b: UAV):
    return sqrt((b.pos[0]-a.pos[0])**2+(b.pos[1]-a.pos[1])**2+(b.pos[2]-a.pos[2])**2)


def aim(agroup, bgroup):
    for i in agroup:
        id = 0
        pos = 0x7fffffff
        for j in bgroup:
            id, pos = j.info.id, getdis(i, j) if pos > getdis(i, j) else id
        i.aim = j.info.id if getdis(i.pos[0], bgroup[id].pos[0]) <= i.perfor.visual[0] and \
            getdis(i.pos[1], bgroup[id].pos[1]) <= i.perfor.visual[1] and \
            getdis(i.pos[2], bgroup[id].pos[2]) <= i.perfor.visual[1] else -1


if __name__ == '__main__':
    n, T = map(int, input().split())
    UAV_A = []
    UAV_B = []
    for i in range(n):
        uav = UAV(input().split(), input().split(),
                  input().split(), input().split())
        uav.info = uav._info(i, "A")
        UAV_A.append(uav)
    for i in range(n):
        uav = UAV(input().split(), input().split(),
                  input().split(), input().split())
        uav.info = uav._info(i, "B")
        UAV_B.append(uav)

    for i in range(T):
        print(aim())
