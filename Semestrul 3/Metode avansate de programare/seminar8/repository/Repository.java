package org.example.labx.repository;

import org.example.labx.domain.Nota;

import java.util.ArrayList;

public class Repository {
    ArrayList<Nota> note;

    public Repository() {
        note = new ArrayList<>();
    }

    public void addNota(Nota nota) {
        note.add(nota);
    }

    public ArrayList<Nota> getNote() {
        return note;
    }
}
