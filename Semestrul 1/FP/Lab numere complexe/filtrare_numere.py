from cautare_numere import get_parte_reala
from cautare_numere import calculeaza_modul
from modifica_elemente_lista import sterge_de_pe_pozitie


def verificare_numar_prim(numar):
    if numar < 2:
        return False
    if numar == 2:
        return True
    if numar % 2 == 0:
        return False

    for d in range(3, numar // 2, 2):
        if numar % d == 0:
            return False

    return True


def test_verificare_numar_prim():
    assert not verificare_numar_prim(-1)
    assert verificare_numar_prim(2)
    assert not verificare_numar_prim(4)
    assert verificare_numar_prim(23)


# 5.1
def filtrare_parte_reala_prim(lista_cu_nr_complexe):
    i = 0
    while i < len(lista_cu_nr_complexe):
        parte_reala = get_parte_reala(lista_cu_nr_complexe[i])

        if parte_reala == int(parte_reala):
            if verificare_numar_prim(int(parte_reala)):
                sterge_de_pe_pozitie(lista_cu_nr_complexe, i)
                i -= 1
        i += 1

    return lista_cu_nr_complexe


def test_filtrare_parte_reala_prim():
    assert filtrare_parte_reala_prim([[1, 2], [3, 4], [5, 6], [6, 7]]) == [[1, 2], [6, 7]]
    assert filtrare_parte_reala_prim([[3, 4], [5, 6], [7, 8]]) == []
    assert filtrare_parte_reala_prim([[1, 2], [9, 4], [4, 6]]) == [[1, 2], [9, 4], [4, 6]]


# 5.2
def filtrare_modul_comparatie_fata_de_numar(lista_cu_nr_complexe, comparatie, numar_modul):
    epsilon = 0.000000001
    i = 0

    if comparatie == '=':
        while i < len(lista_cu_nr_complexe):
            modul = calculeaza_modul(lista_cu_nr_complexe[i])

            if abs(modul - numar_modul) < epsilon:
                sterge_de_pe_pozitie(lista_cu_nr_complexe, i)
                i -= 1

            i += 1

    elif comparatie == '<':
        while i < len(lista_cu_nr_complexe):
            modul = calculeaza_modul(lista_cu_nr_complexe[i])

            if modul < numar_modul:
                sterge_de_pe_pozitie(lista_cu_nr_complexe, i)
                i -= 1

            i += 1

    elif comparatie == '>':
        while i < len(lista_cu_nr_complexe):
            modul = calculeaza_modul(lista_cu_nr_complexe[i])

            if modul > numar_modul:
                sterge_de_pe_pozitie(lista_cu_nr_complexe, i)
                i -= 1

            i += 1

    return lista_cu_nr_complexe


def test_filtrare_modul_comparatie_fata_de_numar():
    assert filtrare_modul_comparatie_fata_de_numar([[3, 4], [1, 1], [23, 23]], '=', 5) == [[1, 1], [23, 23]]
    assert filtrare_modul_comparatie_fata_de_numar([[2, 3], [3, 4], [4, 5]], '<', 5) == [[3, 4], [4, 5]]
    assert filtrare_modul_comparatie_fata_de_numar([[2, 3], [3, 4], [4, 5]], '>', 5) == [[2, 3], [3, 4]]
    assert filtrare_modul_comparatie_fata_de_numar([[2, 3], [3, 4], [4, 5], [5, 6]], '<', 120) == []
