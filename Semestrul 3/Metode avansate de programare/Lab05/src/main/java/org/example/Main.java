package org.example;

import org.example.domain.validators.FriendshipValidator;
import org.example.domain.validators.UtilizatorValidator;
import org.example.repository.DataBaseRepositories.FriendshipDBRepository;
import org.example.repository.DataBaseRepositories.UserDBRepository;
import org.example.service.CommunityService;
import org.example.service.FriendshipService;
import org.example.service.UserService;
import org.example.ui.UIfunctionalities;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Main {
    private static final String DATABASE_URL = "jdbc:sqlserver://localhost:1433;databaseName=socialNetworkDB;integratedSecurity=true;encrypt=false;trustServerCertificate=true";
    private static final String USERNAME = "";
    private static final String PASSWORD = "";

    public static void main(String[] args) {
        UIfunctionalities ui = new UIfunctionalities();

        UserDBRepository repoUsersDB = new UserDBRepository(DATABASE_URL, USERNAME, PASSWORD, new UtilizatorValidator());
        FriendshipDBRepository repoFriendsDB = new FriendshipDBRepository(DATABASE_URL, USERNAME, PASSWORD, new FriendshipValidator());

        UserService userService = new UserService(repoUsersDB, repoFriendsDB);
        FriendshipService friendshipService = new FriendshipService(repoUsersDB, repoFriendsDB);
        CommunityService communityService = new CommunityService(repoUsersDB, repoFriendsDB);

        Connection connection = null;

        try {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");

            connection = DriverManager.getConnection(DATABASE_URL, USERNAME, PASSWORD);
            ui.showMessage("Connected to database");

            while(true) {
                ui.showMenu();
                var opt = ui.getOption(0, 6);

                switch(opt) {
                    case 1: {
                        // add user
                        var firstName = ui.getName("Introdu prenumele noului utilizator: ");
                        var lastName = ui.getName("Introdu numele noului friendship: ");

                        var message = userService.addUser(firstName, lastName);
                        ui.showMessage(message);

                        break;
                    }
                    case 2: {
                        // remove user
                        var allUsers = userService.getAll();
                        ui.showAllUsers(allUsers);

                        long id = ui.getUserID("Introdu id-ul userului pe care vrei sa il stergi: ");
                        var message = userService.deleteUser(id);
                        ui.showMessage(message);

                        break;
                    }
                    case 3: {
                        // add prieten
                        ui.showAllUsers(userService.getAll());

                        long id1 = ui.getUserID("Introdu id-ul userului pentru care vrei sa adaugi prieten: ");
                        long id2 = ui.getUserID("Introdu id-ul userului pt a face prietenia: ");

                        try {
                            var message = friendshipService.addFriendships(id1, id2);
                            ui.showMessage(message);
                        }
                        catch (Exception e) {
                            ui.showMessage(e.getMessage());
                        }
                        break;
                    }
                    case 4: {
                        // remove prieten
                        ui.showAllUsers(userService.getAll());

                        long id1 = ui.getUserID("Introdu id-ul userului pentru care vrei sa stergi un prieten: ") ;
                        ui.showAllUsers(friendshipService.getAllFriends(id1));

                        long id2 = ui.getUserID("Introdu id-ul userului pt care vrei sa stergi prietenia: ");
                        String message = friendshipService.deleteFriendship(id1, id2);
                        ui.showMessage(message);

                        break;
                    }
                    case 5: {
                        // afisare numar comunitati (nr componente conexe)
                        var communities = communityService.getCommunityGraph();

                        try {
                            ui.showCommunities(repoUsersDB, communities);
                        }
                        catch (Exception e) {
                            ui.showMessage(e.getMessage());
                        }

                        break;
                    }
                    case 6: {
                        // cea mai sociabila comunitate (comp conexa cu cel mai lung drum)
                        var mostSociableCommunity = communityService.biggestCommunity();

                        if(mostSociableCommunity.isEmpty())
                            ui.showMessage("Nu exista cea mai sociabila comunitate");
                        else {
                            try {
                                ui.showBiggestCommunity(repoUsersDB, mostSociableCommunity);
                            } catch (Exception e) {
                                ui.showMessage(e.getMessage());
                            }
                        }

                        break;
                    }
                    case 0: {
                        return;
                    }
                    default: {
                        throw new RuntimeException();
                    }
                }
            }

        }
        catch (SQLException e) {
            System.out.println("SQL Exception: " + e.getMessage());
        }
        catch (ClassNotFoundException e) {
            System.out.println("Driver not found: " + e.getMessage());
        }
        finally {
            // Close resources in the finally block to ensure they are closed even if an exception occurs
            try {
                if (connection != null) connection.close();
                System.out.println("Database resources released");
            }
            catch (SQLException e) {
                System.out.println("Error closing resources: " + e.getMessage());
            }
        }
    }
}
