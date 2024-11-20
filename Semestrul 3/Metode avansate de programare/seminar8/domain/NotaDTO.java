package org.example.labx.domain;

public class NotaDTO {
    private String numeStudent;
    private String numeTema;
    private Double nota;
    private String numeProfesor;

    public NotaDTO(String numeStudent, String numeTema, Double nota, String numeProfesor) {
        this.numeStudent = numeStudent;
        this.numeTema = numeTema;
        this.nota = nota;
        this.numeProfesor = numeProfesor;
    }

    public String getTemaName() {
        return numeTema;
    }

    public void setNumeTema(String numeTema) {
        this.numeTema = numeTema;
    }

    public String getStudentName() {
        return numeStudent;
    }

    public void setNumeStudent(String numeStudent) {
        this.numeStudent = numeStudent;
    }

    public Double getNotaValue() {
        return nota;
    }

    public void setNota(Double nota) {
        this.nota = nota;
    }

    @Override
    public String toString() {
        return "NotaDTO{" +
                "numeStudent='" + numeStudent + '\'' +
                ", numeTema='" + numeTema + '\'' +
                ", nota=" + nota +
                ", numeProfesor='" + numeProfesor + '\'' +
                '}';
    }
}
