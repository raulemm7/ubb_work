package org.example.labx;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.labx.domain.NotaDTO;
import org.example.labx.service.ServiceManager;

import java.util.List;
import java.util.stream.Collectors;

public class HelloController {
    @FXML
    private TableView<NotaDTO> tableView;
    @FXML
    private TableColumn<NotaDTO, String> studentColumn;
    @FXML
    private TableColumn<NotaDTO, String> temaColumn;
    @FXML
    private TableColumn<NotaDTO, Double> notaColumn;
    @FXML
    private TextField studentFilterField;
    @FXML
    private TextField notaFilterField;
    @FXML
    private TextField temaFilterField;
    @FXML
    private Button butonReset;

    private void resetFilters() {
        studentFilterField.clear();
        notaFilterField.clear();
        temaFilterField.clear();
    }

    // Metodă pentru a popula tabelul cu date
    @FXML
    public void initialize() {
        // Configurarea butoanelor
        butonReset.setOnAction(event -> resetFilters());

        // Configurarea coloanelor
        studentColumn.setCellValueFactory(new PropertyValueFactory<>("studentName"));
        temaColumn.setCellValueFactory(new PropertyValueFactory<>("temaName"));
        notaColumn.setCellValueFactory(new PropertyValueFactory<>("notaValue"));

        // Popularea tabelei cu date
        ObservableList<NotaDTO> notaDTOObservableList = FXCollections.observableArrayList(getNotaDTOList());
        tableView.setItems(notaDTOObservableList);

        // Creează o listă filtrată pe baza listei originale
        FilteredList<NotaDTO> filteredList = new FilteredList<>(notaDTOObservableList, b -> true);

        // Legarea filtrării la fiecare TextField
        studentFilterField.textProperty().addListener((observable, oldValue, newValue) -> {
            filteredList.setPredicate(nota -> {
                // Dacă nu este specificat niciun filtru, se afișează toate elementele
                if (newValue == null || newValue.isEmpty()) {
                    return true;
                }
                // Filtrare după nume student
                return nota.getStudentName().toLowerCase().contains(newValue.toLowerCase());
            });
        });

        notaFilterField.textProperty().addListener((observable, oldValue, newValue) -> {
            filteredList.setPredicate(nota -> {
                // Dacă nu este specificat niciun filtru, se afișează toate elementele
                if (newValue == null || newValue.isEmpty()) {
                    return true;
                }
                try {
                    double filterValue = Double.parseDouble(newValue);
                    return nota.getNotaValue() > filterValue;
                } catch (NumberFormatException e) {
                    return true; // Dacă introducerea nu este validă, nu filtrează
                }
            });
        });

        temaFilterField.textProperty().addListener((observable, oldValue, newValue) -> {
            filteredList.setPredicate(nota -> {
                // Dacă nu este specificat niciun filtru, se afișează toate elementele
                if (newValue == null || newValue.isEmpty()) {
                    return true;
                }
                // Filtrare după tema
                return nota.getTemaName().toLowerCase().contains(newValue.toLowerCase());
            });
        });

        // Legarea listei filtrate la tabel
        tableView.setItems(filteredList);
    }

    // Metodă pentru obținerea listei de NotaDTO
    private List<NotaDTO> getNotaDTOList() {
        ServiceManager service = new ServiceManager();
        return service.findAllGrades()
                .stream()
                .map(n -> new NotaDTO(n.getStudent().getName(), n.getTema().getNumeTema(), n.getNotaValue(), n.getNumeProf()))
                .collect(Collectors.toList());
    }
}