import time
import pyautogui


def simulate_key_presses():
    # Give some time to switch focus to the target window or webpage
    time.sleep(1.5)

    # Simulate pressing '1'
    pyautogui.press('1')

    # Simulate pressing the right arrow key
    pyautogui.press('right')

if __name__ == "__main__":
    while True:
        simulate_key_presses()