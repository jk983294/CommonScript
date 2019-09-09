import unittest
import errno

"""
do not catch exception and then use assertEqual(type(e), ValueError)
use assertRaises(ValueError, parse_int, 'N/A') directly
"""


def parse_int(s):
    return int(s)


class TestConversion(unittest.TestCase):
    def test_bad_int(self):
        self.assertRaises(ValueError, parse_int, 'N/A')

    def test_bad_int_regex(self):
        self.assertRaisesRegex(ValueError, 'invalid literal .*', parse_int, 'N/A')


class TestIO(unittest.TestCase):
    def test_file_not_found(self):
        try:
            f = open('/file/not/found')
        except IOError as e:
            self.assertEqual(e.errno, errno.ENOENT)
        else:
            self.fail('IOError not raised')
