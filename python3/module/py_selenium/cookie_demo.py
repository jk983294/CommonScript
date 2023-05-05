from selenium import webdriver


if __name__ == '__main__':
    driver = webdriver.Chrome()
    driver.get("http://www.google.com")

    # Now set the cookie. This one's valid for the entire domain
    cookie = {'name': 'foo', 'value': 'bar'}
    driver.add_cookie(cookie)

    # And now output all the available cookies for the current URL
    driver.get_cookies()

    driver.close()
