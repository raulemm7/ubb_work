#include "ui/ui.h"
#include "repo/store.h"
#include "teste/teste.h"

int main(){
    Lista* l=creare_lista(distruge_produs, getcopy);
    Lista* undoL = creare_lista(distruge_lista, copyList);
    run_teste();
    start_program(l, undoL);
    distruge_lista(l);
    distruge_lista(undoL);
    _CrtDumpMemoryLeaks();
}
//Severity	Code	Description	Project	File	Line	Suppression State	Details
//Error	C4996	'strcpy': This function or variable may be unsafe.Consider using strcpy_s instead.To disable deprecation, use _CRT_SECURE_NO_WARNINGS.See online help for details.ProjectTitieniMDL2	C : \Alpine Studio\ObjectOrientedP\ProjectTitieniMDL2\domain\domain.c	10
