package org.example.labx.domain;

import java.util.Objects;

public class Tema {
    private String numeTema;
    private String descriere;

    public Tema(String nume, String descriere) {
        this.numeTema = nume;
        this.descriere = descriere;
    }

    public String getNumeTema() {
        return numeTema;
    }

    public void setNumeTema(String numeTema) {
        this.numeTema = numeTema;
    }

    public String getDescriere() {
        return descriere;
    }

    public void setDescriere(String descriere) {
        this.descriere = descriere;
    }

    @Override
    public String toString() {
        return numeTema + "\t" + descriere;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Tema tema)) return false;
        return Objects.equals(numeTema, tema.numeTema) && Objects.equals(descriere, tema.descriere);
    }

    @Override
    public int hashCode() {
        return Objects.hash(numeTema, descriere);
    }
}
