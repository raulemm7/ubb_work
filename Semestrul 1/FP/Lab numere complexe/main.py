from citiri_si_afisari import *
from adauga_nr_in_lista import *
from modifica_elemente_lista import *
from cautare_numere import *
from operatii_cu_nr_din_lista import *
from filtrare_numere import *
from undo import *
from comanda_lab_6 import citire_comanda_noua


def verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_informare):
    if len(lista_cu_nr_complexe) == 0:
        tipareste_mesaj_informare(mesaj_informare)
        return False
    else:
        return True


def ruleaza_teste():
    test_adauga_la_sfarsitul_listei()
    test_inserare_la_o_pozitie_data()
    test_sterge_de_pe_pozitie()
    test_sterge_interval_pozitii()
    test_inlocuieste_aparitii()
    test_get_parte_reala()
    test_get_parte_imaginara()
    test_suma_nr_subsecventa()
    test_produs_nr_subsecvente()
    test_filtrare_parte_reala_prim()
    test_verificare_numar_prim()
    test_calculeaza_modul()
    test_filtrare_modul_comparatie_fata_de_numar()
    test_adauga_la_stiva()


def main():
    ruleaza_teste()

    mesaj_info = 'Nu exista numere in lista! Comanda nu poate fi executata!'

    stiva_cu_operatii = []
    lista_cu_nr_complexe = []

    while True:
        menu()
        comanda = citire_comanda()

        if comanda == 1:
            stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

            nr_complex = creeare_nr_complex('Introdu numarul complex:')
            lista_cu_nr_complexe = adauga_la_sfarsitul_listei(lista_cu_nr_complexe, nr_complex)
            tipareste_mesaj_informare('Element adaugat cu succes!')

        elif comanda == 2:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                nr_complex = creeare_nr_complex('Introdu numarul complex:')
                index_value = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu pozitia dorita: ')
                lista_cu_nr_complexe = inserare_la_o_pozitie_data(lista_cu_nr_complexe, nr_complex, index_value)
                tipareste_mesaj_informare('Element adaugat cu succes!')

        elif comanda == 3:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                index_value = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu pozitia dorita: ')
                lista_cu_nr_complexe = sterge_de_pe_pozitie(lista_cu_nr_complexe, index_value)
                tipareste_mesaj_informare('Element sters cu succes!')

        elif comanda == 4:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                start_index = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu o pozitie de inceput:')
                finish_index = citire_index_valid(len(lista_cu_nr_complexe), start_index, 'Introdu o pozitie de final:')
                lista_cu_nr_complexe = sterge_interval_pozitii(lista_cu_nr_complexe, start_index, finish_index)
                tipareste_mesaj_informare('Elemente sterse cu succes!')

        elif comanda == 5:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                nr_complex_de_inlocuit = creeare_nr_complex(
                    'Introdu numarul complex pe care doresti sa il inlocuiesti:')
                nr_inloc = creeare_nr_complex('Introdu numarul complex cu care doresti sa inlocuiesti:')

                lista_cu_nr_complexe = inlocuieste_aparitii(lista_cu_nr_complexe, nr_complex_de_inlocuit, nr_inloc)
                tipareste_mesaj_informare('Numar inlocuit cu succes!')

        elif comanda == 6:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                tipareste_parte_imaginara(lista_cu_nr_complexe)

        elif comanda == 7:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                tipareste_nr_modul_mai_mic_10(lista_cu_nr_complexe)

        elif comanda == 8:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                tipareste_nr_modul_egal_10(lista_cu_nr_complexe)

        elif comanda == 9:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                start_index = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu o pozitie de inceput:')
                finish_index = citire_index_valid(len(lista_cu_nr_complexe), start_index, 'Introdu o pozitie de final:')
                suma_nr_subsecventa(lista_cu_nr_complexe, start_index, finish_index)

        elif comanda == 10:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                start_index = citire_index_valid(len(lista_cu_nr_complexe), 0, 'Introdu o pozitie de inceput:')
                finish_index = citire_index_valid(len(lista_cu_nr_complexe), start_index, 'Introdu o pozitie de final:')
                produs_nr_subsecventa(lista_cu_nr_complexe, start_index, finish_index)

        elif comanda == 11:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                tipareste_descrescator(lista_cu_nr_complexe)

        elif comanda == 12:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                filtrare_parte_reala_prim(lista_cu_nr_complexe)
                tipareste_mesaj_informare('Lista filtrata cu succes!')

        elif comanda == 13:
            if verifica_optiune_valabila(lista_cu_nr_complexe, mesaj_info):
                stiva_cu_operatii = adauga_la_stiva(stiva_cu_operatii, lista_cu_nr_complexe)

                comparatie = citire_comparatie()
                numar = citire_numar_real('Introdu modulul fata de care faci comparatia: ')
                lista_cu_nr_complexe = filtrare_modul_comparatie_fata_de_numar(lista_cu_nr_complexe, comparatie, numar)
                tipareste_mesaj_informare('Lista filtrata cu succes!')

        elif comanda == 14:
            if len(stiva_cu_operatii) == 0:
                tipareste_mesaj_informare('Nu mai poti reveni la o forma anterioara a listei! Lista este deja vida!')
            else:
                stiva_cu_operatii, lista_cu_nr_complexe = sterge_din_stiva(stiva_cu_operatii)
                tipareste_mesaj_informare('Lista a revenit la forma ei anterioara cu succes!')

        elif comanda == 15:
            exit()

        elif comanda == 16:
            while True:
                stiva_cu_operatii, lista_cu_nr_complexe = citire_comanda_noua(stiva_cu_operatii, lista_cu_nr_complexe)
                tipareste_mesaj_informare('Comanda efectuata cu succes!')


main()
