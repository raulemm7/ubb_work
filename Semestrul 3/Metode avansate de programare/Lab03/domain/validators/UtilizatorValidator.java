package ubb.scs.map.domain.validators;


import ubb.scs.map.domain.Utilizator;

import java.util.ArrayList;
import java.util.Collection;

/**
 * Validates instances of the {@link Utilizator} class.
 * Ensures that user attributes meet specified criteria and that users are unique.
 */
public class UtilizatorValidator implements Validator<Utilizator> {
    /**
     * Validates the specified {@link Utilizator} entity against a collection of existing entities.
     *
     * @param allEntities a collection of all existing {@link Utilizator} entities
     * @param entity the {@link Utilizator} entity to validate
     * @throws ValidationException if the entity's first name or last name is invalid,
     *         or if the user already exists in the collection
     */
    @Override
    public void validate(Collection<Utilizator> allEntities, Utilizator entity) throws ValidationException {
        if (entity.getFirstName() == null || entity.getFirstName().trim().isEmpty()) {
            throw new ValidationException("Prenumele utilizatorului nu este valid");
        }

        // Validare pentru lastName
        if (entity.getLastName() == null || entity.getLastName().trim().isEmpty()) {
            throw new ValidationException("Numele de familie al utilizatorului nu este valid");
        }

        for(var ent : allEntities){
            if(ent.getFirstName().equals(entity.getFirstName()) && ent.getLastName().equals(entity.getLastName())){
                throw new ValidationException("Acest utilizator exista deja!");
            }
        }
    }
}
