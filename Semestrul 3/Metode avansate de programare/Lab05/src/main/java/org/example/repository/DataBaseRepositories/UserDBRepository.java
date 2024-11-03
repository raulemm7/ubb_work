package org.example.repository.DataBaseRepositories;


import org.example.domain.Utilizator;
import org.example.domain.validators.Validator;
import org.example.repository.Repository;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Optional;
import java.util.Set;

public class UserDBRepository implements Repository<Long, Utilizator> {
    private final String url;
    private final String usernameDB;
    private final String passwordDB;
    private final Validator<Utilizator> userValidator;

    public UserDBRepository(String url, String usernameDB, String passwordDB, Validator<Utilizator> userValidator) {
        this.url = url;
        this.usernameDB = usernameDB;
        this.passwordDB = passwordDB;
        this.userValidator = userValidator;
    }

    /**
     * Constructs an Utilizator object from the current row in the provided ResultSet.
     *
     * @param resultSet the ResultSet positioned at the current row to retrieve Utilizator data from, must not be null.
     * @return an Utilizator object constructed from the data in the current ResultSet row.
     * @throws SQLException if an SQL error occurs while retrieving data from the ResultSet.
     */
    private Utilizator getUserFromQueryResult(ResultSet resultSet) throws SQLException {
        var id_user = resultSet.getLong("id_user");
        var firstName = resultSet.getString("firstname");
        var lastName = resultSet.getString("lastname");

        var user = new Utilizator(firstName, lastName);
        user.setId(id_user);

        return user;
    }

    /**
     * Sets parameter values in the provided PreparedStatement based on the Utilizator data.
     *
     * @param stmt the PreparedStatement to set parameter values in, must not be null.
     * @param user the Utilizator object whose data is used to set the parameters in the statement.
     * @throws SQLException if an SQL error occurs while setting parameter values in the PreparedStatement.
     */
    private void setUserDataInStatement(PreparedStatement stmt, Utilizator user) throws SQLException {
        stmt.setString(1, user.getFirstName());
        stmt.setString(2, user.getLastName());
    }

    /**
     * Finds a user by their unique ID in the database.
     *
     * @param id the ID of the user to find, must not be null.
     * @return an `Optional<Utilizator>` containing the found user if present; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs while attempting to connect or execute the query.
     */
    public Optional<Utilizator> findOne(Long id) {
        String sql = "SELECT * FROM \"Users\" WHERE id_user = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            statement.setLong(1, id);
            ResultSet resultSet = statement.executeQuery();

            if (resultSet.next()) {
                return Optional.of(getUserFromQueryResult(resultSet));
            }

            return Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Eroare la găsirea utilizatorului în baza de date!", e);
        }
    }

    /**
     * Retrieves all users from the database.
     *
     * @return a `Collection<Utilizator>` containing all users in the database.
     * @throws RuntimeException if an SQL exception occurs during the connection or query execution.
     */
    public Collection<Utilizator> findAll() {
        Set<Utilizator> users = new HashSet<>();

        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
            PreparedStatement statement = connection.prepareStatement("SELECT * FROM \"Users\"");
            ResultSet resultSet = statement.executeQuery()){

            while(resultSet.next()) {
                var user = getUserFromQueryResult(resultSet);
                users.add(user);
            }

            return users;
        }
        catch (SQLException e) {
            throw new RuntimeException("Eroare la returnarea tuturor utilizatorilor din baza de date!");
        }
    }

    /**
     * Saves a new user to the database.
     *
     * @param utilizator The {@link Utilizator} object to save.
     * @return An {@link Optional} containing the {@code utilizator} if the insertion fails, or {@link Optional#empty()} if the insertion is successful.
     * @throws RuntimeException If a database access error occurs or the SQL statement is invalid.
     */
    public Optional<Utilizator> save(Utilizator utilizator) {
        this.userValidator.validate(this.findAll(), utilizator);

        String sql = "INSERT INTO \"Users\" (firstname, lastname) VALUES (?, ?)";

        try (Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
             PreparedStatement statement = connection.prepareStatement(sql)) {
            this.setUserDataInStatement(statement, utilizator);

            return statement.executeUpdate() > 0 ? Optional.empty() : Optional.of(utilizator);

        } catch (SQLException e) {
            throw new RuntimeException("Eroare la salvarea utilizatorului in baza de date!");
        }
    }

    /**
     * Deletes a user by their unique ID from the database.
     *
     * @param id the ID of the user to delete, must not be null.
     * @return an `Optional<Utilizator>` containing the deleted user if the deletion was successful; otherwise, an empty `Optional`.
     * @throws RuntimeException if an SQL exception occurs during the connection or query execution.
     */
    public Optional<Utilizator> delete(Long id) {
        String sql = "DELETE FROM \"Users\" WHERE id_user = ?";
        try(Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB)) {
            var user = this.findOne(id);
            if(user.isEmpty())
                return Optional.empty();

            PreparedStatement statement = connection.prepareStatement(sql);
            statement.setLong(1, id);

            return statement.executeUpdate() > 0 ? user : Optional.empty();
        }
        catch (SQLException e) {
            throw new RuntimeException("Eroare la stergerea utilizatorului in baza de date!");
        }
    }

    /**
     * Updates an existing user's details in the database.
     *
     * @param utilizator the user with updated details; must not be null and should have a valid ID.
     * @return an `Optional<Utilizator>` containing the updated user if the update was successful; otherwise, an empty `Optional` if the user was not found.
     * @throws RuntimeException if an SQL exception occurs during connection or query execution.
     */
    public Optional<Utilizator> update(Utilizator utilizator) {
        if (this.findOne(utilizator.getId()).isEmpty()) {
            return Optional.empty();
        }

        String sql = "UPDATE \"Users\" SET firstname = ?, lastname = ? WHERE id_user = ?";

        try (Connection connection = DriverManager.getConnection(this.url, this.usernameDB, this.passwordDB);
             PreparedStatement statement = connection.prepareStatement(sql)) {

            this.setUserDataInStatement(statement, utilizator);
            statement.setLong(3, utilizator.getId());

            return statement.executeUpdate() > 0 ? Optional.of(utilizator) : Optional.empty();
        } catch (SQLException e) {
            throw new RuntimeException("Eroare la modificarea datelor utilizatorului în baza de date!", e);
        }
    }
}