def kelvin2fahrenheit(temperature):
    assert (temperature >= 0), "Colder than absolute zero!"
    return ((temperature - 273) * 1.8) + 32


print(kelvin2fahrenheit(1))
print(kelvin2fahrenheit(100))
print(kelvin2fahrenheit(-1))
