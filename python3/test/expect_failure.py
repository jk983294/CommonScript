import unittest


class Tests(unittest.TestCase):
    def test_0(self):
        self.assertTrue(True)

    @unittest.expectedFailure
    def test_4(self):
        self.assertEqual(2+2, 5)


if __name__ == '__main__':
    unittest.main()