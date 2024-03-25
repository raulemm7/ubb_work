bits 32 

global start        

extern exit, scanf, fopen, fclose, fprintf, printf               
import exit msvcrt.dll 
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 
import fprintf msvcrt.dll  
import printf msvcrt.dll

segment data use32 class=data
    nume_tastatura times 100 db 0
    nume_fisier times 100 db 0
    mod_acces db 'a+', 0
    descriptor_fisier dd -1
    
    format_str db '%s', 0
    format_char db '%c', 0
    
    numar_caractere dd 0
    numar_caractere_aux dd 0
    pointer_sir dd 0

segment code use32 class=code
    start:
        ; citesc numele fisierului
        push dword nume_tastatura
        push dword format_str
        call [scanf]
        add esp, 4 * 2
        
        ; copie sor string
        mov esi, nume_tastatura
        mov edi, nume_fisier
        cld
        cat_timp_caractere:
            lodsb    ; al = caracter
            
            cmp al, 0
            je stop
            
            ; actualizez nr de caractere
            mov ebx, [numar_caractere]
            inc ebx
            mov [numar_caractere], ebx
            mov [numar_caractere_aux], ebx
            
            mov [pointer_sir], edi
            stosb    ; stochez caracterul in nume_fisier
        jmp cat_timp_caractere
        
        stop:
            nop
        
        ; adaug extensia '.txt' pentru a crea fisierul cu succes
        mov al, '.'
        stosb
        mov al, 't'
        stosb
        mov al, 'x'
        stosb
        mov al, 't'
        stosb 
        
        ; fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4 * 2
        
        ; verific daca fisierul s a deschis corect
        cmp eax, 0
        je finish
        mov [descriptor_fisier], eax
        
        ; carpeala
        mov eax, ' '
        push eax
        push dword format_char
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 4 * 3
        
        ; afisez in fisier doar cifrele
        mov esi, [pointer_sir]
        mov ecx, [numar_caractere]
        std
        cifre:
            mov [numar_caractere], ecx
            
            mov eax, 0
            lodsb
            
            cmp eax, '0'
            jb nu_e_cifra
            cmp eax, '9'
            ja nu_e_cifra
            
            push eax
            push dword format_char
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4 * 3
            
            nu_e_cifra:
                nop
            
            mov ecx, [numar_caractere]
        loop cifre
        
        ; afisez in fisier doar literele (mari si mici)
        mov esi, [pointer_sir]
        mov ecx, [numar_caractere_aux]
        std
        caractere:
            mov [numar_caractere_aux], ecx
            
            mov eax, 0
            lodsb
            
            cmp eax, 'z'
            ja nu_e_litera
            cmp eax, 'a'
            jb litera_mare
            
            jmp afisare
            
            litera_mare:
                cmp eax, 'Z'
                ja nu_e_litera
                cmp eax, 'A'
                jb nu_e_litera
            
            afisare:
                push eax
                push dword format_char
                push dword [descriptor_fisier]
                call [fprintf]
                add esp, 4 * 3
            
            nu_e_litera:
                nop
            
            mov ecx, [numar_caractere_aux]
        loop caractere
        
        ; fclose(descriptor_fisier)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4 * 2
    
    finish:
        push dword 0    
        call [exit]       
