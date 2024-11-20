package org.example.labx;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import org.example.labx.domain.NotaDTO;
import org.example.labx.service.ServiceManager;

import java.io.IOException;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        checkConnectionToDataBase();

        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("hello-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 600, 400); // Dimensiuni ajustate la FXML
        stage.setTitle("Hello!");
        stage.setScene(scene);
        stage.show();
    }

    public void checkConnectionToDataBase() {
        try{
            DatabaseConfig.getConnection();
            System.out.println("Connected to database");
        }
        catch(SQLException e){
            System.out.println("Exception: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        launch();
    }
}