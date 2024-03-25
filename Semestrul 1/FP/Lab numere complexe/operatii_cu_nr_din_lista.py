from cautare_numere import get_parte_reala
from cautare_numere import get_parte_imaginara
from citiri_si_afisari import tipareste_nr_complex
from citiri_si_afisari import tipareste_lista


def suma_nr_subsecventa(lista_cu_nr_complexe, start_index, finish_index):
    suma_parte_reala = 0
    suma_parte_imaginara = 0

    for i in range(start_index, finish_index + 1):
        suma_parte_reala += get_parte_reala(lista_cu_nr_complexe[i])
        suma_parte_imaginara += get_parte_imaginara(lista_cu_nr_complexe[i])

    suma_nr_complexe = [suma_parte_reala, suma_parte_imaginara]
    tipareste_nr_complex(suma_nr_complexe)


def test_suma_nr_subsecventa():
    pass


def produs_nr_subsecventa(lista_cu_nr_complexe, start_index, finish_index):
    produs_parte_reala = get_parte_reala(lista_cu_nr_complexe[start_index])
    produs_parte_imaginara = get_parte_imaginara(lista_cu_nr_complexe[start_index])

    for i in range(start_index + 1, finish_index + 1):
        a = produs_parte_reala
        b = produs_parte_imaginara

        c = get_parte_reala(lista_cu_nr_complexe[i])
        d = get_parte_imaginara(lista_cu_nr_complexe[i])

        # (a + bi) * (c + di) = (a * c - b * d) + (a * d + b * c)i
        produs_parte_reala = (a * c) - (b * d)
        produs_parte_imaginara = (a * d) + (b * c)

    produs_nr_complexe = [produs_parte_reala, produs_parte_imaginara]
    tipareste_nr_complex(produs_nr_complexe)


def test_produs_nr_subsecvente():
    pass


def tipareste_descrescator(lista_cu_nr_complexe):
    lista_sortata = sorted(lista_cu_nr_complexe, key=lambda x: x[1], reverse=True)
    tipareste_lista(lista_sortata)
