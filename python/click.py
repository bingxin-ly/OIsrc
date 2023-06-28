import pyautogui
import keyboard

while True:
    if keyboard.is_pressed('esc'):
        break
pos = pyautogui.position()

while True:
    pyautogui.click(pos[0], pos[1])
    if keyboard.is_pressed('esc'):
        break
