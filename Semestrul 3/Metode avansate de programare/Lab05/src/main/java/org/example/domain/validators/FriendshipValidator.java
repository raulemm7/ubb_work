package org.example.domain.validators;

import org.example.domain.Friendship;

import java.util.Collection;

/**
 * Validates instances of the {@link Friendship} class.
 * Ensures that friendships are unique within the collection of existing friendships.
 */
public class FriendshipValidator implements Validator<Friendship> {
    private boolean checkExistingFriendship(Friendship existingFriendship, Friendship newFriendship) {
        if(existingFriendship.getFirstUser().getId().equals(newFriendship.getFirstUser().getId()) &&
        existingFriendship.getSecondUser().getId().equals(newFriendship.getSecondUser().getId())) {
            return true;
        }

        return existingFriendship.getFirstUser().getId().equals(newFriendship.getSecondUser().getId()) &&
                existingFriendship.getSecondUser().getId().equals(newFriendship.getFirstUser().getId());
    }

    /**
     * Validates the specified {@link Friendship} entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing {@link Friendship} entities
     * @param friendship the {@link Friendship} entity to validate
     * @throws ValidationException if the friendship already exists in the collection
     */
    @Override
    public void validate(Collection<Friendship> allEntities, Friendship friendship) {
        allEntities.stream()
                .filter(entity -> this.checkExistingFriendship(entity, friendship))
                .findAny()
                .ifPresent(_ -> { throw new ValidationException("Aceasta prietenie exista deja!"); });
    }
}
