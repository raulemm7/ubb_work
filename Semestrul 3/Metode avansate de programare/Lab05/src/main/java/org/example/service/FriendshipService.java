package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.Utilizator;
import org.example.repository.DataBaseRepositories.FriendshipDBRepository;
import org.example.repository.DataBaseRepositories.UserDBRepository;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Optional;

/**
 * The FriendshipService class provides services for managing `Friendship` entities,
 * including ID generation, adding and deleting friendships, and retrieving a user's friends.
 */
public class FriendshipService{
    private final UserDBRepository utilizatorRepository;
    private final FriendshipDBRepository friendshipRepository;

    /**
     * Constructs a FriendshipService with the specified user and friendship repositories.
     *
     * @param utilizatorRepository the repository handling user data
     * @param friendshipRepository the repository handling friendship data
     */
    public FriendshipService(UserDBRepository utilizatorRepository, FriendshipDBRepository friendshipRepository) {
        this.utilizatorRepository = utilizatorRepository;
        this.friendshipRepository = friendshipRepository;
    }

    /**
     * Retrieves all friends of a specified user.
     *
     * @param id_user the ID of the user whose friends are to be retrieved
     * @return an Iterable collection of `Utilizator` entities representing the user's friends
     */
    public Collection<Utilizator> getAllFriends(Long id_user) {
        ArrayList<Utilizator> friends = new ArrayList<>();
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        friendships.forEach(friendship -> {
            if(friendship.getFirstUser().getId().equals(id_user)) {
                friends.add(friendship.getSecondUser());
            }
            else if(friendship.getSecondUser().getId().equals(id_user)) {
                friends.add(friendship.getFirstUser());
            }
        });

        return friends;
    }

    /**
     * Adds a new friendship between two users identified by their IDs.
     *
     * @param idFirstUser the ID of the first user
     * @param idSecondUser the ID of the second user
     * @return a string message indicating the result of the operation
     */
    public String addFriendships(Long idFirstUser, Long idSecondUser) {
        var errMsg = "Nu a fost gasit utilizatorul cu id-ul: ";
        var user1 = this.utilizatorRepository.findOne(idFirstUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idFirstUser));
        var user2 = this.utilizatorRepository.findOne(idSecondUser).orElseThrow(() -> new IllegalArgumentException(errMsg + idSecondUser));
        var friendship = new Friendship(user1, user2);

        try {
            var result = this.friendshipRepository.save(friendship);
            if (result.isEmpty()) {
                return "Prietenie salvata cu succes!";
            }
            return "Prietenia exista deja!";
        }
        catch (Exception e) {
            return e.getMessage();
        }
    }

    /**
     * Checks if a given friendship exists between two specified users.
     *
     * @param friendship the {@link Friendship} object representing the friendship to check
     * @param idFirstUser the ID of the first user in the potential friendship
     * @param idSecondUser the ID of the second user in the potential friendship
     * @return {@code true} if the friendship exists between the specified users, {@code false} otherwise
     */
    private boolean checkIfUsersHaveFriendship(Friendship friendship, Long idFirstUser, Long idSecondUser) {
        if(friendship.getFirstUser().getId().equals(idFirstUser) && friendship.getSecondUser().getId().equals(idSecondUser))
            return true;

        return friendship.getFirstUser().getId().equals(idSecondUser) && friendship.getSecondUser().getId().equals(idFirstUser);
    }

    /**
     * Deletes a friendship between two users identified by their IDs.
     *
     * @param idFirstUser the ID of the first user
     * @param idSecondUser the ID of the second user
     * @return a string message indicating whether the friendship was successfully deleted
     */
    public String deleteFriendship(Long idFirstUser, Long idSecondUser) {
        Collection<Friendship> friendships = friendshipRepository.findAll();

        if(friendships.isEmpty()) {
            return "Acest utilizator nu are prieteni pentru a putea fi stersi!";
        }

        Optional<Friendship> friendshipToDelete = friendships.stream()
                .filter(friendship -> checkIfUsersHaveFriendship(friendship, idFirstUser, idSecondUser))
                .findFirst();

        if (friendshipToDelete.isPresent()) {
            this.friendshipRepository.delete(friendshipToDelete.get().getId());
            return "Prietenie stearsa cu succes!";
        } else {
            return "Prietenia nu a fost gasita!";
        }
    }
}
