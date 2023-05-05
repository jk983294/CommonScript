from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

if __name__ == '__main__':
    driver = webdriver.Chrome()
    driver.get("http://www.google.com")

    # find <input type="text" name="passwd" id="passwd-id" />
    element = driver.find_element(By.ID, "passwd-id")
    element = driver.find_element(By.NAME, "passwd")
    element = driver.find_element(By.XPATH, "//input[@id='passwd-id']")
    element = driver.find_element(By.CSS_SELECTOR, "input#passwd-id")

    # clear input box
    element.clear()

    # send data
    element.send_keys("some text")
    element.send_keys(" and some", Keys.ARROW_DOWN)

    driver.close()
