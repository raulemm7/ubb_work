package org.example.labx.service;

import org.example.labx.domain.Nota;
import org.example.labx.domain.Student;
import org.example.labx.domain.Tema;
import org.example.labx.repository.Repository;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class ServiceManager {

    public ServiceManager (){}

    public ArrayList<Student> findAllStudents() {
        var allStudents = new ArrayList<Student>();

        allStudents.add(new Student("Pahomi Sebastian", "225"));
        allStudents.add(new Student("Michael Brown", "221"));
        allStudents.add(new Student("Michael Jackson", "222"));
        allStudents.add(new Student("Michael Jordan", "223"));

        return allStudents;
    }

    public ArrayList<Tema> findAllHomeWorks() {
        var allTemas = new ArrayList<Tema>();
        allTemas.add(new Tema("OOP", "OOP Project"));
        allTemas.add(new Tema("ASC", "ASC Project"));
        allTemas.add(new Tema("FP", "FP Project"));
        return allTemas;
    }

    public ArrayList<Nota> findAllGrades() {
        var allGrades = new ArrayList<Nota>();

        var allStudents = findAllStudents();
        var allHomeWorks = findAllHomeWorks();

        allGrades.add(new Nota(allStudents.get(0), allHomeWorks.get(1), 9.70, LocalDateTime.now(), "Istvan"));
        allGrades.add(new Nota(allStudents.get(1), allHomeWorks.get(0), 5.40, LocalDateTime.now(), "Istvan"));
        allGrades.add(new Nota(allStudents.get(2), allHomeWorks.get(2), 3.20, LocalDateTime.now(), "Gabi Mircea"));
        allGrades.add(new Nota(allStudents.get(3), allHomeWorks.get(2), 6.80, LocalDateTime.now(), "Gabi Mircea"));
        allGrades.add(new Nota(allStudents.get(2), allHomeWorks.get(0), 7.75, LocalDateTime.now(), "Imre"));
        allGrades.add(new Nota(allStudents.get(1), allHomeWorks.get(1), 8.60, LocalDateTime.now(), "Berinde"));

        return allGrades;
    }

    public ArrayList<Nota> getNote(Student student, Tema tema) {
        var note = this.findAllGrades().stream()
                .filter(nota -> nota.getStudent().equals(student) && nota.getTema().equals(tema))
                .collect(Collectors.toCollection(ArrayList::new));

        return note;
    }
}
