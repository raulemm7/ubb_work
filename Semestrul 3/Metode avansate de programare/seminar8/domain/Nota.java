package org.example.labx.domain;

import java.time.LocalDateTime;

public class Nota {
    private Student student;
    private Tema tema;
    private Double notaValue;
    private LocalDateTime date;
    private String numeProf;

    public Nota(Student student, Tema tema, Double nota, LocalDateTime data, String numeProf) {
        this.student = student;
        this.tema = tema;
        this.notaValue = nota;
        this.date = data;
        this.numeProf = numeProf;
    }

    public Student getStudent() {
        return student;
    }

    public String getNumeProf() {
        return numeProf;
    }

    public Double getNotaValue() {
        return notaValue;
    }

    public Tema getTema() {
        return tema;
    }

    public void setStudent(Student student) {
        this.student = student;
    }

    public void setTema(Tema tema) {
        this.tema = tema;
    }

    public void setNotaValue(Double notaValue) {
        this.notaValue = notaValue;
    }

    public void setNumeProf(String numeProf) {
        this.numeProf = numeProf;
    }

    @Override
    public String toString() {
        return "Nota{" +
                "student=" + student +
                ", tema=" + tema +
                ", notaValue=" + notaValue +
                ", numeProf='" + numeProf + '\'' +
                '}';
    }
}
