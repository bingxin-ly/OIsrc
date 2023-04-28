from logging import *


def setup_logger():
    logger = getLogger()
    logger.setLevel(DEBUG)

    fmt = '%(asctime)s %(levelname)-5s at%(lineno)s: %(message)s'
    datefmt = '%H:%M:%S'
    formatter = Formatter(fmt, datefmt)

    ch = StreamHandler()
    ch.setLevel(DEBUG)
    ch.setFormatter(formatter)

    logger.addHandler(ch)
    return logger
