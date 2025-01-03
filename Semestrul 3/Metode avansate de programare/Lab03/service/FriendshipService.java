package ubb.scs.map.service;

import ubb.scs.map.domain.Friendship;
import ubb.scs.map.domain.Utilizator;
import ubb.scs.map.repository.FriendshipRepository;
import ubb.scs.map.repository.UtilizatorRepository;

import java.util.ArrayList;

/**
 * The FriendshipService class provides services for managing `Friendship` entities,
 * including ID generation, adding and deleting friendships, and retrieving a user's friends.
 */
public class FriendshipService implements Service<Friendship>{
    private final UtilizatorRepository utilizatorRepository;
    private final FriendshipRepository friendshipRepository;

    /**
     * Constructs a FriendshipService with the specified user and friendship repositories.
     *
     * @param utilizatorRepository the repository handling user data
     * @param friendshipRepository the repository handling friendship data
     */
    public FriendshipService(UtilizatorRepository utilizatorRepository, FriendshipRepository friendshipRepository) {
        this.utilizatorRepository = utilizatorRepository;
        this.friendshipRepository = friendshipRepository;
    }


    /**
     * Generates a unique ID for a new friendship.
     *
     * @return a unique ID of type {@link Long} for the new friendship
     */
    @Override
    public Long generateID(){
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        Long id = 0L;

        for(Friendship friendship : friendships){
            if(friendship.getId() > id)
                id = friendship.getId();
        }

        return id + 1;
    }

    /**
     * Retrieves all friends of a specified user.
     *
     * @param id_user the ID of the user whose friends are to be retrieved
     * @return an Iterable collection of `Utilizator` entities representing the user's friends
     */
    public Iterable<Utilizator> getAll(Long id_user) {
        ArrayList<Utilizator> friends = new ArrayList<>();
        Iterable<Friendship> friendships = friendshipRepository.findAll();

        for(Friendship friendship : friendships){
            if(friendship.getFirstUser().getId().equals(id_user)) {
                friends.add(friendship.getSecondUser());
            }
            else if(friendship.getSecondUser().getId().equals(id_user)) {
                friends.add(friendship.getFirstUser());
            }
        }

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
        var user1 = this.utilizatorRepository.findOne(idFirstUser);
        var user2 = this.utilizatorRepository.findOne(idSecondUser);
        var friendship = new Friendship(user1, user2);
        friendship.setId(this.generateID());

        try {
            var result = this.friendshipRepository.save(friendship);
            if (result == null) {
                return "Prietenie salvata cu succes!";
            }
            return "Prietenia exista deja!";
        }
        catch (Exception e) {
            return e.getMessage();
        }
    }

    /**
     * Deletes a friendship between two users identified by their IDs.
     *
     * @param idFirstUser the ID of the first user
     * @param idSecondUser the ID of the second user
     * @return a string message indicating whether the friendship was successfully deleted
     */
    public String deleteFriendship(Long idFirstUser, Long idSecondUser) {
        Iterable<Friendship> friendships = friendshipRepository.findAll();
        for(Friendship friendship : friendships){
            if(friendship.getFirstUser().getId().equals(idFirstUser) && friendship.getSecondUser().getId().equals(idSecondUser)) {
                this.friendshipRepository.delete(friendship.getId());
                return "Prietenie stearsa cu succes!";
            }
            else if(friendship.getFirstUser().getId().equals(idSecondUser) && friendship.getSecondUser().getId().equals(idFirstUser)) {
                this.friendshipRepository.delete(friendship.getId());
                return "Prietenie stearsa cu succes!";
            }
        }
        return "Nu exista o prietenie pentru a putea fi stearsa!";
    }
}
