from DOMAIN.entities import BallerTests
from REPOSITORY.repo import Repo, FileRepo, RepoTests
from BUSINESS.serv import Service, ServiceTests
from UI.ui_elements import Output, Input
from VALIDATOR.validare import ValiTests


class Main:
    @staticmethod
    def run_all_tests():
        BallerTests.run_all_tests()
        ServiceTests.run_all_tests()
        RepoTests.run_all_tests()
        ValiTests.run_all_tests()

    @staticmethod
    def main_app():
        Main.run_all_tests()

        lista_jucatori = Repo()
        file = FileRepo('fisier.txt')

        while True:
            # afisez meniul
            Output.menu()

            # actualizez lista cu informatiile din fisier
            lista_jucatori.clear_list()
            lista_jucatori.read_from_file(file)

            # introduc comanda de la utilizator
            command = Input.enter_command(5)

            if command == 1:
                nume, prenume = Input.enter_nume_prenume(lista_jucatori)
                post = Input.enter_post()
                inaltime = Input.enter_inaltime()

                Service.append_jucator(lista_jucatori, nume, prenume, post, inaltime)

                lista_jucatori.write_in_file(file)
            elif command == 2:
                minim = Service.find_minim_h(lista_jucatori)
                delta_h = Input.enter_delta_inaltime(minim)

                Service.modifica_inaltime_jucatori(lista_jucatori, delta_h)

                lista_jucatori.write_in_file(file)
            elif command == 3:
                rezultat, mesaj = Service.creeaza_echipa(lista_jucatori)

                if mesaj == 'ok':
                    Output.print_echipa(rezultat)
                else:
                    Output.print_mesage(mesaj)
            elif command == 4:
                file_path = Input.enter_file_name()
                new_file = FileRepo(file_path)

                nr_jucatori, nr_total = Service.importa_jucatori_din_fisier(lista_jucatori, new_file)

                info = "S-au importat "
                info += str(nr_jucatori)
                info += ' jucatori din '
                info += str(nr_total)
                info += ' persoane.'
                Output.print_mesage(info)

                lista_jucatori.write_in_file(file)
            else:
                exit()


Main.main_app()
