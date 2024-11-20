package org.example.labx;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.transformation.FilteredList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.labx.domain.NotaDTO;
import org.example.labx.service.ServiceManager;

import java.util.List;
import java.util.Set;
import java.util.function.Predicate;
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
    @FXML
    private ChoiceBox<String> dropdownFilters;

    private ObservableList<NotaDTO> originalList;
    private FilteredList<NotaDTO> filteredList;

    @FXML
    public void initialize() {
        // Obține lista de date
        originalList = FXCollections.observableArrayList(getNotaDTOList());
        filteredList = new FilteredList<>(originalList, b -> true);

        // Configurează tabelul
        configureTable();

        // Configurează filtrele
        configureFilters();

        // Configurează resetarea
        butonReset.setOnAction(event -> resetFilters());

        // Configurează dropdown-ul pentru teme
        configureDropdown();
    }

    private void configureTable() {
        // Setează coloanele tabelului
        studentColumn.setCellValueFactory(new PropertyValueFactory<>("studentName"));
        temaColumn.setCellValueFactory(new PropertyValueFactory<>("temaName"));
        notaColumn.setCellValueFactory(new PropertyValueFactory<>("notaValue"));

        // Legarea listei filtrate la tabel
        tableView.setItems(filteredList);
    }

    private void configureFilters() {
        // Legarea filtrării pentru fiecare câmp de introducere
        studentFilterField.textProperty().addListener((observable, oldValue, newValue) -> applyFilters());
        notaFilterField.textProperty().addListener((observable, oldValue, newValue) -> applyFilters());
        temaFilterField.textProperty().addListener((observable, oldValue, newValue) -> applyFilters());
    }

    private void configureDropdown() {
        // Populează dropdown-ul cu teme unice
        Set<String> uniqueTeme = originalList.stream()
                .map(NotaDTO::getTemaName)
                .collect(Collectors.toSet());
        dropdownFilters.getItems().addAll(uniqueTeme);

        // Listener pentru selectarea unei teme din dropdown
        dropdownFilters.valueProperty().addListener((observable, oldValue, newValue) -> applyFilters());
    }

    private void applyFilters() {
        String studentFilter = studentFilterField.getText().toLowerCase();
        String notaFilter = notaFilterField.getText();
        String temaFilter = temaFilterField.getText().toLowerCase();
        String selectedTema = dropdownFilters.getValue();

        filteredList.setPredicate(createCombinedPredicate(studentFilter, notaFilter, temaFilter, selectedTema));
    }

    private Predicate<NotaDTO> createCombinedPredicate(String studentFilter, String notaFilter, String temaFilter, String selectedTema) {
        return nota -> {
            boolean matchesStudent = studentFilter.isEmpty() || nota.getStudentName().toLowerCase().contains(studentFilter);
            boolean matchesNota = notaFilter.isEmpty() || isNotaAboveThreshold(nota, notaFilter);
            boolean matchesTemaField = temaFilter.isEmpty() || nota.getTemaName().toLowerCase().contains(temaFilter);
            boolean matchesDropdownTema = selectedTema == null || selectedTema.isEmpty() || nota.getTemaName().equals(selectedTema);

            return matchesStudent && matchesNota && matchesTemaField && matchesDropdownTema;
        };
    }

    private boolean isNotaAboveThreshold(NotaDTO nota, String notaFilter) {
        try {
            return nota.getNotaValue() > Double.parseDouble(notaFilter);
        } catch (NumberFormatException e) {
            return true; // Dacă valoarea introdusă nu este validă, nu se filtrează
        }
    }

    private void resetFilters() {
        studentFilterField.clear();
        notaFilterField.clear();
        temaFilterField.clear();
        dropdownFilters.setValue(null);
    }

    private List<NotaDTO> getNotaDTOList() {
        ServiceManager service = new ServiceManager();
        return service.findAllGrades()
                .stream()
                .map(n -> new NotaDTO(n.getStudent().getName(), n.getTema().getNumeTema(), n.getNotaValue(), n.getNumeProf()))
                .collect(Collectors.toList());
    }
}
