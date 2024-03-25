import unittest
from main import Functii


class Tests(unittest.TestCase):
    def test_copiere_lista(self):
        lista = ['(', '(', ')', ')']
        self.assertEqual(Functii.copiere_lista(lista), lista)

    def test_validare_solutie(self):
        lista = ['(', '(', ')', ')']
        self.assertEqual(Functii.verificare_solutie(lista), True)

        lista = ['(', '(', ')', '(']
        self.assertEqual(Functii.verificare_solutie(lista), False)

    def test_backtracking_recursiv(self):
        numar = 4
        lista = [0] * numar
        lista_solutii = []

        Functii.backtracking_recursiv(lista, 0, numar, lista_solutii)

        self.assertEqual(lista_solutii, [['(', '(', ')', ')'], ['(', ')', '(', ')']])

    def test_bkt_decoding(self):
        lista = [1, 1, 2, 2, 1, 1, 2, 2]
        self.assertEqual(Functii.bkt_decoding(lista), ['(', '(', ')', ')', '(', '(', ')', ')'])

    def test_backtracking_iterativ(self):
        numar = 4
        lista_solutii = []

        Functii.backtracking_iterativ(numar, lista_solutii)

        self.assertEqual(lista_solutii, [['(', '(', ')', ')'], ['(', ')', '(', ')']])
