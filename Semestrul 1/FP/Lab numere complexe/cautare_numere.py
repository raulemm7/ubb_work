import math


from citiri_si_afisari import citire_index_valid
from citiri_si_afisari import tipareste_nr_complex
from citiri_si_afisari import tipareste_mesaj_informare


def get_parte_reala(nr_complex):
    """
    :param nr_complex: forma a + bi
    :return: returneaza a (partea reala)
    preconditii: nr complex sa fie lista de forma [parte_reala, parte_imaginara]
    """
    return nr_complex[0]


def test_get_parte_reala():
    assert get_parte_reala([1, 2]) == 1
    assert get_parte_reala([-32, 24]) == -32
    assert get_parte_reala([0.23, -1.25]) == 0.23


def get_parte_imaginara(nr_complex):
    """
    :param nr_complex: nr de forma a + bi
    :return: returneaza i (partea_imaginara)
    preconditii: nr complex sa fie lista de forma [parte_reala, parte_imaginara]
    """
    return nr_complex[1]


def test_get_parte_imaginara():
    assert get_parte_imaginara([1, 2]) == 2
    assert get_parte_imaginara([-32, 24]) == 24
    assert get_parte_imaginara([0.23, -1.25]) == -1.25


def calculeaza_modul(nr_complex):
    a = get_parte_reala(nr_complex)
    b = get_parte_imaginara(nr_complex)

    modul = math.sqrt(a * a + b * b)
    return modul


def test_calculeaza_modul():
    assert calculeaza_modul([3, 4]) == 5
    assert calculeaza_modul([1, 2]) == math.sqrt(5)


# 3.1
def tipareste_parte_imaginara(lista_cu_nr_complexe):
    """
    :param lista_cu_nr_complexe: -
           se va afisa partea imaginara a fiecarui numar complex din subsecventa data
    preconditii: lista sa fie nevida
                 indicii de start si inceput a subsecventei de elemente ce urmeaza a
                 fi tiparite sa fie valizi:
                     0 <= start_index <= finish_index < lungimea listei
    """
    start_index = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu o pozitie de inceput: ')
    finish_index = citire_index_valid(len(lista_cu_nr_complexe), start_index, 'Introdu o pozitie de sfarsit: ')

    for i in range(start_index, finish_index + 1):
        print(get_parte_imaginara(lista_cu_nr_complexe[i]))


# 3.2
def tipareste_nr_modul_mai_mic_10(lista_cu_nr_complexe):
    """
    :param lista_cu_nr_complexe: -
           se vor afisa nr complexe al caror modul este mai mic ca 10
    preconditii: lista sa fie nevida
    """
    gasit = 0

    for i in lista_cu_nr_complexe:
        modul = calculeaza_modul(i)

        if modul < 10:
            gasit = 1
            tipareste_nr_complex(i)

    if gasit == 0:
        tipareste_mesaj_informare("Nu s-au gasit numere care sa satisfaca conditiile!")


# 3.3
def tipareste_nr_modul_egal_10(lista_cu_nr_complexe):
    """
    :param lista_cu_nr_complexe: -
           se vor afisa numerele complexe al caror modul este egal cu 10
    preconditii: lista sa fie nevida
    """
    gasit = 0
    epsilon = 0.000000001

    for i in lista_cu_nr_complexe:
        modul = calculeaza_modul(i)

        # verific daca un float este egal cu 10
        if abs(modul - 10) < epsilon:
            gasit = 1
            tipareste_nr_complex(i)

    if gasit == 0:
        tipareste_mesaj_informare('Nu s-au gasit numere care sa satisfaca conditiile!')
