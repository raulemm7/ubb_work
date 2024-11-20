package org.example.labx.domain;

public class Entity<ID> {
    private ID id;

    public void setID(final ID id) {
        this.id = id;
    }

    public ID getID() {return this.id;}
}
