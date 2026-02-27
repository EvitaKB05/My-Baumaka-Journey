import unittest
import main

class TestTaskFunctions(unittest.TestCase):

    def test_task1(self):
        in_data = (('Pycharm', 2013, 'Python'), ('CLion', 2014, 'Python'), ('Visual Studio', 1997, 'C++'), ('QT Creator', 1991, 'C++'), ('Vim', 1988, 'C++'), ('Visual Studio Code', 2015, 'Rust'))
        correct_out = [('Vim', 1988, 'C++'), ('QT Creator', 1991, 'C++'), ('Visual Studio', 1997, 'C++'), ('Pycharm', 2013, 'Python'), ('CLion', 2014, 'Python'), ('Visual Studio Code', 2015, 'Rust')]
        out = main.task1(in_data)
        self.assertEqual(out, correct_out)

    def test_task2(self):
        in_data = (('Pycharm', 2013, 'Python'), ('CLion', 2014, 'Python'), ('Visual Studio', 1997, 'C++'), ('QT Creator', 1991, 'C++'), ('Vim', 1988, 'C++'), ('Visual Studio Code', 2015, 'Rust'))
        correct_out = [('Rust', 1), ('Python', 2), ('C++', 3)]
        out = main.task2(in_data)
        self.assertEqual(out, correct_out)

    def test_task3(self):
        in_data = (('Pycharm', 2013, 'Python'), ('CLion', 2014, 'Python'), ('Visual Studio', 1997, 'C++'), ('QT Creator', 1991, 'C++'), ('Vim', 1988, 'C++'), ('Visual Studio Code', 2015, 'Rust'))
        correct_out = [('Pycharm', 'Python'), ('Visual Studio', 'C++'), ('QT Creator', 'C++'), ('Vim', 'C++')]
        out = main.task3(in_data)
        self.assertEqual(out, correct_out)


if __name__ == '__main__':
    unittest.main()