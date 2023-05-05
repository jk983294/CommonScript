from selenium import webdriver
from selenium.webdriver.common.keys import Keys  # keys in the keyboard like RETURN
from selenium.webdriver.common.by import By  # used to locate elements within a document

if __name__ == '__main__':
    driver = webdriver.Chrome()
    driver.get("http://www.python.org")
    assert "Python" in driver.title
    elem = driver.find_element(By.NAME, "q")
    elem.clear()
    elem.send_keys("pycon")
    elem.send_keys(Keys.RETURN)
    driver.close()
