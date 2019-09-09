import unittest


# setUp method will be called before a test is called
# tearDown method will be called after a test is called
# unittest.main() will find all test cases in the script and executes them, execution order is by alphabet, ascending

# four type of assert:
# 1. TestCase.assertTrue(expr[, msg])
# 2. TestCase.assertEqual(first, second[, msg])
# 3. TestCase.assertNotEqual(first, second[, msg])
# 4. TestCase.assertRaises(exception, callable, ...)

# enhancement tool:
# nosetests will run test*.py scripts found in the current directory
# coverage measures which lines have been executed


class MyTestCase(unittest.TestCase):
    def setUp(self):
        self.seq = list(range(10))

    def test_range(self):
        for i in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:
            self.assertTrue(i in self.seq, "Missing number: %d" % i)
            self.assertEqual(self.seq.index(i), i)

    def test_range_reverse(self):
        self.seq.reverse()
        for i in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:
            self.assertTrue(i in self.seq, "Missing number: %d" % i)
            self.assertEqual(self.seq.index(i), 9 - i)


if __name__ == '__main__':
    unittest.main()
