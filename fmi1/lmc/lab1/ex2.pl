female(mary).
female(sandra).
female(juliet).
female(lisa).
male(peter).
male(paul).
male(dony).
male(bob).
male(harry).
parent(bob, lisa).
parent(bob, paul).
parent(bob, mary).
parent(juliet, lisa).
parent(juliet, paul).
parent(juliet, mary).
parent(peter, harry).
parent(lisa, harry).
parent(mary, dony).
parent(mary, sandra).

father_of(Father, Child) :- parent(Father,Child), male(Father).
mother_of(Mother, Child) :- parent(Mother,Child), female(Mother).
grandfather_of(Grandfather, Child) :- parent(Parent,Child), father_of(Grandfather,Parent).
grandmother_of(Grandmother, Child) :- parent(Parent,Child), mother_of(Grandmother,Parent).
sister_of(Sister,Person):- parent(Parent,Person), parent(Parent,Sister), female(Sister), Sister \= Person.
brother_of(Brother,Person):- parent(Parent,Person), parent(Parent,Brother), male(Brother), Brother \= Person.
aunt_of(Aunt,Person) :- parent(Parent,Person), sister_of(Aunt,Parent).
uncle_of(Uncle,Person) :- parent(Parent,Person), brother_of(Uncle,Parent).
not_parent(X,Y) :- not(parent(X,Y)).
