from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import Select
from selenium.webdriver import ActionChains


def select_demo(driver):
    # select
    select = Select(driver.find_element(By.NAME, 'name'))
    select.select_by_index(index=1)
    select.select_by_visible_text(text="text")
    select.select_by_value(value="1")

    # clear select
    select = Select(driver.find_element(By.ID, 'id'))
    select.deselect_all()

    # get all options
    options = select.options
    print(options)


def drag_drop_demo(driver):
    element = driver.find_element(By.NAME, "source")
    target = driver.find_element(By.NAME, "target")

    action_chains = ActionChains(driver)
    action_chains.drag_and_drop(element, target).perform()


if __name__ == '__main__':
    driver = webdriver.Chrome()
    driver.get("http://www.google.com")

    select_demo(driver)
    drag_drop_demo(driver)

    # submit form
    driver.find_element_by_id("submit").click()

    driver.close()
