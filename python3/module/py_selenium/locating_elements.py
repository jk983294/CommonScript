from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select
from selenium.webdriver import ActionChains


def by_xpath(driver):
    login_form = driver.find_element(By.XPATH, "/html/body/form[1]")
    login_form = driver.find_element(By.XPATH, "//form[1]")
    login_form = driver.find_element(By.XPATH, "//form[@id='loginForm']")

    username = driver.find_element(By.XPATH, "//form[input/@name='username']")
    username = driver.find_element(By.XPATH, "//form[@id='loginForm']/input[1]")
    username = driver.find_element(By.XPATH, "//input[@name='username']")

    clear_button = driver.find_element(By.XPATH, "//input[@name='continue'][@type='button']")
    clear_button = driver.find_element(By.XPATH, "//form[@id='loginForm']/input[4]")


def by_hyperlink(driver):
    # <html>
    #  <body>
    #   <p>Are you sure you want to do this?</p>
    #   <a href="continue.html">Continue</a>
    #   <a href="cancel.html">Cancel</a>
    # </body>
    # </html>
    continue_link = driver.find_element(By.LINK_TEXT, 'Continue')


if __name__ == '__main__':
    driver = webdriver.Chrome()
    driver.get("http://www.google.com")

    driver.find_element(By.XPATH, '//button[text()="Some text"]')  # find one
    driver.find_elements(By.XPATH, '//button')  # find several

    driver.find_element(By.ID, "id")
    driver.find_element(By.NAME, "name")
    driver.find_element(By.XPATH, "xpath")
    driver.find_element(By.LINK_TEXT, "link text")
    driver.find_element(By.PARTIAL_LINK_TEXT, "partial link text")
    driver.find_element(By.TAG_NAME, "tag name")
    driver.find_element(By.CLASS_NAME, "class name")
    driver.find_element(By.CSS_SELECTOR, "css selector")

    by_xpath(driver)
    by_hyperlink(driver)

    driver.close()
